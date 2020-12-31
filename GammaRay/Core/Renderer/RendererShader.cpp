#include "grpch.h"
#include "RendererShader.h"

#include <fstream>


RendererShader::RendererShader()
{
}

RendererShader::~RendererShader()
{
}

void RendererShader::Setup(const char* vertShaderSrc, const char* fragShaderSrc, const char* _, const char* shaderName)
{
    m_name = shaderName;

    // TODO: This method is mostly called from derived classes that were generated with shader2c. In these cases
    //       we kinda want these std::strings to repoint their internal pointers to the method arguments.
    m_vertexShaderSrc   = vertShaderSrc;
    m_fragmentShaderSrc = fragShaderSrc;
}

void RendererShader::LoadFromFile(const std::string& filePath)
{
    std::ifstream ifs(filePath);

    // TODO: File validity checks!

    m_vertexShaderSrc   = "";
    m_fragmentShaderSrc = "";

    std::string* outStr = nullptr;
    for(std::string line; std::getline(ifs, line); )
    {
        // Direct the output into specific buffers and skip the line
        if(line.compare("#[fragment]") == 0)
        {
            outStr = &m_fragmentShaderSrc;
            continue;
        }
        else if(line.compare("#[vertex]") == 0)
        {
            outStr = &m_vertexShaderSrc;
            continue;
        }

        // Append to the appropriate shader source string
        if(outStr)
            *outStr += line + "\n";
    }
    ifs.close();

    Compile();
}
