#define _CRT_SECURE_NO_WARNINGS

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>


// TODO: Make this tool a bit more complex in allowing the inputs to be shoved into specific classes and generated files
//       so we don't end up with one horrible monolithic header that includes all resources.

enum class OutType
{
    OUTTYPE_BIN = 0,
    OUTTYPE_STRING // Currently processing is no different with the string option
};

struct InOutPair
{
    std::string_view inFilePath;
    std::string_view outVariableName;
    OutType outType = OutType::OUTTYPE_BIN;
};

int main(int argc, char** argv)
{
    printf("// Generated with GammaRay bin2c.\n");
    printf("// Probably best if you don't touch this file.\n\n");
    printf("#pragma once\n\n");
    printf("namespace CoreData {\n\n");

    std::vector<InOutPair> args;

    for(int i = 1; i < argc; i++)
    {
        InOutPair inOutPair;

        char* pch = strtok(argv[i], "|");
        inOutPair.inFilePath = pch;
        pch = strtok(nullptr, "|");
        inOutPair.outVariableName = pch;
        pch = strtok(nullptr, "|");

        if(pch)
        {
            if(strcmp(pch, "string") == 0)
                inOutPair.outType = OutType::OUTTYPE_STRING;
        }

        args.push_back(inOutPair);
    }

    // TODO: Variable name collision testing

    for(const auto& arg : args)
    {
        std::ifstream ifs(arg.inFilePath.data(), std::ios::binary | std::ios::ate);

        std::streampos end = ifs.tellg();
        ifs.seekg(0, std::ios::beg);
        size_t size = size_t(end - ifs.tellg());

        // TODO: If size is 0, does this mean the file doesn't exist too???
        if(size == 0)
            continue;
        
        std::vector<std::byte> buffer(size);

        if(!ifs.read((char*)buffer.data(), buffer.size()))
            continue;

        printf("// File: %s\n", arg.inFilePath.data());
        printf("char %s_data[] = {\n    ", arg.outVariableName.data());

        unsigned int n = 0;
        for(const std::byte& c : buffer)
        {
            printf("0x%.2X,", (int)c);
            ++n;
            if(n % 16 == 0) printf("\n    ");
        }

        printf("};\nconst char* %s = &%s_data[0];\n", arg.outVariableName.data(), arg.outVariableName.data());
    }

    printf("\n};");
}
