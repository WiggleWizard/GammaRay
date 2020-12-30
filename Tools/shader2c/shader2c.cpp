#define _CRT_SECURE_NO_WARNINGS

#define VERSION_MAJOR 1
#define VERSION_MINOR 2

#include <fstream>
#include <string>
#include <string_view>


static const char* newShaderClassPrefix = "RendererShader";

struct InOutPair
{
    std::string_view inFilePath;
    std::string_view outFilePath;
    std::string_view outClassName;
    std::string_view outInheritsClassName;
    std::string_view inheritsHeaderFilePath;
};

void PrintHelp()
{
    printf("shader2c --in=<filepath> --out=<filepath> --class=<classname> --inherits=<classname> --inheritshpath=<filepath>\n");
}

void WriteShaderBytesToStream(std::ofstream& ofs, const std::string& s, const char* sourceName)
{
    unsigned int i = 0;
    ofs << "        static const char " << sourceName << "[] = {\n            ";
    for(const char& c : s)
    {
        ofs << (int)c << ", ";
        i++;
        if(i % 24 == 0)
            ofs << "\n            ";
    }
    ofs << "\n        };";
}

int main(int argc, char** argv)
{
    InOutPair out;

    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0)
        {
            printf("%d.%d", VERSION_MAJOR, VERSION_MINOR);
            return 0;
        }

        std::string_view key = strtok(argv[i], "=");
        if(key.compare("--in") == 0)
            out.inFilePath = strtok(nullptr, "=");
        else if(key.compare("--out") == 0)
            out.outFilePath = strtok(nullptr, "=");
        else if(key.compare("--class") == 0)
            out.outClassName = strtok(nullptr, "=");
        else if(key.compare("--inherits") == 0)
            out.outInheritsClassName = strtok(nullptr, "=");
        else if(key.compare("--inheritshpath") == 0)
            out.inheritsHeaderFilePath = strtok(nullptr, "=");
    }

    bool validArgs = true;
    if(out.inFilePath.size() == 0)
        validArgs = false;
    else if(out.outClassName.size() == 0)
        validArgs = false;
    else if(out.outFilePath.size() == 0)
        validArgs = false;
    else if(out.outInheritsClassName.size() == 0)
        validArgs = false;
    else if(out.inheritsHeaderFilePath.size() == 0)
        validArgs = false;

    if(!validArgs)
    {
        PrintHelp();
        return 0;
    }

    std::ofstream outStream(out.outFilePath.data(), std::ios::trunc);
    outStream << "// Generated with GammaRay shader2c.\n";
    outStream << "// Probably best if you don't touch this file.\n";
    outStream << "#pragma once\n\n";
    outStream << "#include \"" << out.inheritsHeaderFilePath.data() << "\"\n\n\n";

    outStream << "class " << newShaderClassPrefix << out.outClassName.data() << " : public " << out.outInheritsClassName.data() << "\n{\n";
    outStream << "public:\n";
    outStream << "    " << newShaderClassPrefix << out.outClassName.data() << "()\n";
    outStream << "    {\n";

    std::string outVertexStr;
    std::string outFragmentStr;
    std::string* outStr = nullptr;

    // Read shader file
    std::ifstream inStream(out.inFilePath.data());
    for(std::string line; std::getline(inStream, line); )
    {
        if(line.compare("#[fragment]") == 0)
        {
            outStr = &outFragmentStr;
            continue;
        }
        else if(line.compare("#[vertex]") == 0)
        {
            outStr = &outVertexStr;
            continue;
        }

        if(outStr)
            *outStr += line + "\n";
    }
    inStream.close();

    WriteShaderBytesToStream(outStream, outVertexStr, "_vertexSource");
    outStream << "\n";
    WriteShaderBytesToStream(outStream, outFragmentStr, "_fragmentSource");

    outStream << "\n        Setup(_vertexSource, _fragmentSource, nullptr, \"" << out.outClassName << "\");";
    outStream << "\n    }\n";
    outStream << "};";
}
