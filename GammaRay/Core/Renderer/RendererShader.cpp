#include "grpch.h"
#include "RendererShader.h"

#include <glad/glad.h>

#include <filesystem>
#include <fstream>


RendererShader::RendererShader()
{
}

RendererShader::~RendererShader()
{
    glDeleteProgram(m_rendererId);
}

bool RendererShader::LoadFromDisk(const std::string& filePath)
{
    std::ifstream ifs(filePath, std::ios::binary|std::ios::ate);
    std::streampos end = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    size_t size = size_t(end - ifs.tellg());

    // TODO: If size is 0, does this mean the file doesnt exist too???
    if(size == 0)
        return true;

    std::vector<char> buffer(size);

    if(!ifs.read((char*)buffer.data(), buffer.size()))
    {
        GR_CORE_ERROR("Could not load file {0}", filePath.c_str());
        GR_CORE_ASSERT(false, "Error loading file");
        return false;
    }

    // TODO: Do something with buffer


    return false;
}

void RendererShader::Setup(const char* vertShaderSrc, const char* fragShaderSrc, const char* _, const char* shaderName)
{
    vertexShaderSrc   = vertShaderSrc;
    fragmentShaderSrc = fragShaderSrc;
    name = shaderName;
}

bool RendererShader::Compile()
{
    // Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const GLchar* source = (const GLchar*)vertexShaderSrc;
    glShaderSource(vertexShader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(vertexShader);

        GR_CORE_ERROR("{0}", infoLog.data());
        GR_CORE_ASSERT(false, "Error compiling vertex shader");

        return false;
    }

    // Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar*)fragmentShaderSrc;
    glShaderSource(fragmentShader, 1, &source, 0);

    // Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);

        GR_CORE_ERROR("{0}", infoLog.data());
        GR_CORE_ASSERT(false, "Error compiling fragment shader");

        return false;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    GLuint program = glCreateProgram();
    m_rendererId = (uint32_t)program;

    // Attach our shaders to our program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        GR_CORE_ERROR("{0}", infoLog.data());
        GR_CORE_ASSERT(false, "Error linking shader");

        return false;
    }

    // Always detach shaders after a successful link.
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    return true;
}

void RendererShader::Bind() const
{
    glUseProgram(m_rendererId);
}

void RendererShader::Unbind() const
{
    glUseProgram(0);
}
