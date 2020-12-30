#pragma once

#include <string>


class RendererShader : public Object
{
public:
    RendererShader();
    ~RendererShader();

    bool LoadFromDisk(const std::string& filePath);

    void Setup(const char* vertShaderSrc, const char* fragShaderSrc, const char* _, const char* shaderName);
    bool Compile();

    void Bind() const;
    void Unbind() const;

protected:
    std::string name = "";
    const char* vertexShaderSrc = nullptr;
    const char* fragmentShaderSrc = nullptr;

private:
    uint32_t m_rendererId = 0;
};

