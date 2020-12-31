#include "grpch.h"
#include "RendererShaderOpenGL3.h"

#include <glad/glad.h>


bool RendererShaderOpenGL3::Compile()
{
    // Destroy and release the shader program on the GPU
    if(m_rendererId != INVALID_SHADER_ID)
    {
        // TODO: I'm sure I've gone overboard with trying to clean up here, and I'm sure that
        //       half these calls are probably not even needed. Double check if this is the case.

        Unbind();

        glDeleteProgram(m_rendererId);
        glDeleteShader(m_vertexShaderId);
        glDeleteShader(m_fragmentShaderId);

        m_rendererId = INVALID_SHADER_ID;
        m_vertexShaderId = INVALID_SHADER_ID;
        m_fragmentShaderId = INVALID_SHADER_ID;
    }

    // Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_vertexShaderId = (uint32_t)vertexShader;

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const GLchar* source = (const GLchar*)m_vertexShaderSrc.c_str();
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
    m_fragmentShaderId = (uint32_t)fragmentShader;

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar*)m_fragmentShaderSrc.c_str();
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

void RendererShaderOpenGL3::Bind() const
{
    glUseProgram(m_rendererId);
}

void RendererShaderOpenGL3::Unbind() const
{
    glUseProgram(0);
}


RendererShaderOpenGL3::~RendererShaderOpenGL3()
{
    glDeleteProgram(m_rendererId);
}
