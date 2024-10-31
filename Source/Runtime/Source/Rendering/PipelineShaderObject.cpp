#include "PipelineShaderObject.h"

DEFINE_LOGGER_STATIC(LogPipelineShaderObject, LogVerbosity::Verbose)

PipelineShaderObject::PipelineShaderObject() = default;

bool PipelineShaderObject::Initialize(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice, Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain)
{
    Dg::GraphicsPipelineStateCreateInfo psoCreateInfo;

    // Pipeline state name is used by the engine to report issues.
    // It is always a good idea to give objects descriptive names.
    psoCreateInfo.PSODesc.Name = "Simple triangle PSO";

    // This is a graphics pipeline
    psoCreateInfo.PSODesc.PipelineType = Dg::PIPELINE_TYPE_GRAPHICS;

    // clang-format off
    // This tutorial will render to a single render target
    psoCreateInfo.GraphicsPipeline.NumRenderTargets             = 1;
    // Set render target format which is the format of the swap chain's color buffer
    psoCreateInfo.GraphicsPipeline.RTVFormats[0]                = swapChain->GetDesc().ColorBufferFormat;
    // Use the depth buffer format from the swap chain
    psoCreateInfo.GraphicsPipeline.DSVFormat                    = swapChain->GetDesc().DepthBufferFormat;
    psoCreateInfo.GraphicsPipeline.PrimitiveTopology            = Dg::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    psoCreateInfo.GraphicsPipeline.RasterizerDesc.CullMode      = Dg::CULL_MODE_NONE;
    
    psoCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = true;
    psoCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthWriteEnable = true;

    ModifyPSOCreationInfo(psoCreateInfo);

    String shaderSourceCodeVertex = GetShaderSourceVertex();
    if (shaderSourceCodeVertex.empty())
    {
        LogPipelineShaderObject.Error("Vertex shader empty");
        return false;
    }
    
    String shaderSourceCodePixel = GetShaderSourcePixel();
    if (shaderSourceCodePixel.empty())
    {
        LogPipelineShaderObject.Error("Pixel shader empty");
        return false;
    }

    Dg::ShaderCreateInfo ShaderCI;
    ShaderCI.SourceLanguage = Dg::SHADER_SOURCE_LANGUAGE_GLSL;
    // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
    ShaderCI.Desc.UseCombinedTextureSamplers = true;
    
    // Create a vertex shader
    Dg::RefCntAutoPtr<Dg::IShader> shaderVertex;
    {
        Dg::RefCntAutoPtr<Dg::IDataBlob> shaderCompilerOutput;
        
        ShaderCI.Desc.ShaderType = Dg::SHADER_TYPE_VERTEX;
        ShaderCI.EntryPoint      = "main";
        ShaderCI.Desc.Name       = "Vertex shader";
        ShaderCI.Source          = shaderSourceCodeVertex.c_str();
        renderDevice->CreateShader(ShaderCI, &shaderVertex, &shaderCompilerOutput);

        if (shaderCompilerOutput)
        {
            LogPipelineShaderObject.Error("An error occurred during vertex shader compilation: {}", (char*)shaderCompilerOutput->GetDataPtr());
            return false;
        }
    }

    // Create a pixel shader
    Dg::RefCntAutoPtr<Dg::IShader> shaderPixel;
    {
        Dg::RefCntAutoPtr<Dg::IDataBlob> shaderCompilerOutput;
        
        ShaderCI.Desc.ShaderType = Dg::SHADER_TYPE_PIXEL;
        ShaderCI.EntryPoint      = "main";
        ShaderCI.Desc.Name       = "PP Pixel shader";
        ShaderCI.Source          = shaderSourceCodePixel.c_str();
        renderDevice->CreateShader(ShaderCI, &shaderPixel);

        if (shaderCompilerOutput)
        {
            LogPipelineShaderObject.Error("An error occurred during pixel shader compilation: {}", (char*)shaderCompilerOutput->GetDataPtr());
            return false;
        }
    }

    SetupConstantsBuffer(renderDevice);

    // When creating the PSO, make sure to set up the resource layout
    Dg::PipelineResourceLayoutDesc resourceLayoutDesc;
    Dg::ShaderResourceVariableDesc variables[] = {
        { Dg::SHADER_TYPE_VERTEX, "ConstantsVS", Dg::SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE },
        //{ Dg::SHADER_TYPE_PIXEL, "ConstantsPS", Dg::SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE }
    };
    resourceLayoutDesc.Variables = variables;
    resourceLayoutDesc.NumVariables = _countof(variables);

    auto layoutElems = GetLayoutElements();
    psoCreateInfo.GraphicsPipeline.InputLayout.LayoutElements = layoutElems.data();
    psoCreateInfo.GraphicsPipeline.InputLayout.NumElements = layoutElems.size();
    
    psoCreateInfo.PSODesc.ResourceLayout = resourceLayoutDesc;
    psoCreateInfo.pVS = shaderVertex;
    psoCreateInfo.pPS = shaderPixel;
    renderDevice->CreateGraphicsPipelineState(psoCreateInfo, &pso);

    if (!pso)
    {
        LogPipelineShaderObject.Error("Failed to make PSO");
        return false;
    }

    pso->CreateShaderResourceBinding(&shaderBinding, true);
    if (const auto shaderVarConstants = shaderBinding->GetVariableByName(Dg::SHADER_TYPE_VERTEX, "ConstantsVS"))
    {
        shaderVarConstants->Set(constantsBufferVS);
    }

    // pso->CreateShaderResourceBinding(&shaderBinding, true);
    // if (const auto shaderVarConstants = shaderBinding->GetVariableByName(Dg::SHADER_TYPE_PIXEL, "ConstantsPS"))
    // {
    //     shaderVarConstants->Set(constantsBufferPS);
    // }

    initialized = true;

    return true;
}

std::vector<Dg::LayoutElement> PipelineShaderObject::GetLayoutElements()
{
    return {};
}

void PipelineShaderObject::Bind(Dg::RefCntAutoPtr<Dg::IDeviceContext> ctx)
{
    ctx->SetPipelineState(pso);
}

void PipelineShaderObject::SetupCustomConstantsBuffer(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice, size_t bufferSize)
{
}

void PipelineShaderObject::Commit(Dg::RefCntAutoPtr<Dg::IDeviceContext> ctx)
{
    ctx->CommitShaderResources(shaderBinding, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
}

bool PipelineShaderObject::Validate()
{
    if (!initialized)
        return false;
    return true;
}

void PipelineShaderObject::SetupConstantsBuffer(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice)
{
    {
        size_t buffSize = GetConstantBufferSizeVS();
        
        Dg::BufferDesc constantsBufferDesc;
        constantsBufferDesc.Name = "VS constants buffer";
        constantsBufferDesc.Size = buffSize;
        constantsBufferDesc.Usage = Dg::USAGE_DYNAMIC;
        constantsBufferDesc.BindFlags = Dg::BIND_UNIFORM_BUFFER;
        constantsBufferDesc.CPUAccessFlags = Dg::CPU_ACCESS_WRITE;
        renderDevice->CreateBuffer(constantsBufferDesc, nullptr, &constantsBufferVS);
    }

    {
        size_t buffSize = GetConstantBufferSizePS();
        
        Dg::BufferDesc constantsBufferDesc;
        constantsBufferDesc.Name = "PS constants buffer";
        constantsBufferDesc.Size = buffSize;
        constantsBufferDesc.Usage = Dg::USAGE_DYNAMIC;
        constantsBufferDesc.BindFlags = Dg::BIND_UNIFORM_BUFFER;
        constantsBufferDesc.CPUAccessFlags = Dg::CPU_ACCESS_WRITE;
        renderDevice->CreateBuffer(constantsBufferDesc, nullptr, &constantsBufferPS);
    }
}

String PipelineShaderObject::GetShaderSourceVertex()
{
    return "";
}

String PipelineShaderObject::GetShaderSourcePixel()
{
    return "";
}
