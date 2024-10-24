#include "PipelineShaderObject.h"

DEFINE_LOGGER_STATIC(LogPipelineShaderObject, LogVerbosity::Verbose)

PipelineShaderObject::PipelineShaderObject()
{
    
}

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
    
    // Disable depth testing
    psoCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = true;
    psoCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthWriteEnable = true;

    String shaderSourceCodeVertex = GetShaderSourceVertex();
    String shaderSourceCodePixel = GetShaderSourcePixel();

    Dg::ShaderCreateInfo ShaderCI;
    // Tell the system that the shader source code is in HLSL.
    // For OpenGL, the engine will convert this into GLSL under the hood
    ShaderCI.SourceLanguage = Dg::SHADER_SOURCE_LANGUAGE_GLSL;
    // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
    ShaderCI.Desc.UseCombinedTextureSamplers = true;
    // Create a vertex shader
    Dg::RefCntAutoPtr<Dg::IShader> shaderVertex;
    {
        Dg::RefCntAutoPtr<Dg::IDataBlob> shaderCompilerOutput;
        
        ShaderCI.Desc.ShaderType = Dg::SHADER_TYPE_VERTEX;
        ShaderCI.EntryPoint      = "main_vs";
        ShaderCI.Desc.Name       = "Triangle vertex shader";
        ShaderCI.Source          = shaderSourceCodeVertex.c_str();
        renderDevice->CreateShader(ShaderCI, &shaderVertex, &shaderCompilerOutput);

        if (shaderCompilerOutput)
        {
            LogPipelineShaderObject.Error("An error occurred during vertex shader compilation: {}", (char*)shaderCompilerOutput->GetDataPtr());
        }
    }

    // Create a pixel shader
    Dg::RefCntAutoPtr<Dg::IShader> shaderPixel;
    {
        Dg::RefCntAutoPtr<Dg::IDataBlob> shaderCompilerOutput;
        
        ShaderCI.Desc.ShaderType = Dg::SHADER_TYPE_PIXEL;
        ShaderCI.EntryPoint      = "main_ps";
        ShaderCI.Desc.Name       = "Triangle pixel shader";
        ShaderCI.Source          = shaderSourceCodePixel.c_str();
        renderDevice->CreateShader(ShaderCI, &shaderPixel);

        if (shaderCompilerOutput)
        {
            LogPipelineShaderObject.Error("An error occurred during pixel shader compilation: {}", (char*)shaderCompilerOutput->GetDataPtr());
        }
    }

    // Create constant buffer for the vertex shader
    Dg::BufferDesc constantsBufferDesc;
    constantsBufferDesc.Name = "VS constants buffer";
    constantsBufferDesc.Size = sizeof(VSConstants);
    constantsBufferDesc.Usage = Dg::USAGE_DYNAMIC;
    constantsBufferDesc.BindFlags = Dg::BIND_UNIFORM_BUFFER;
    constantsBufferDesc.CPUAccessFlags = Dg::CPU_ACCESS_WRITE;

    renderDevice->CreateBuffer(constantsBufferDesc, nullptr, &constantsBuffer);
    
    // When creating the PSO, make sure to set up the resource layout
    Dg::PipelineResourceLayoutDesc resourceLayoutDesc;
    Dg::ShaderResourceVariableDesc Variables[] = {
        {Dg::SHADER_TYPE_VERTEX, "VSConstants", Dg::SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE}
    };
    resourceLayoutDesc.Variables = Variables;
    resourceLayoutDesc.NumVariables = _countof(Variables);

    auto layoutElems = GetLayoutElements();
    psoCreateInfo.GraphicsPipeline.InputLayout.LayoutElements = layoutElems.data();
    psoCreateInfo.GraphicsPipeline.InputLayout.NumElements = layoutElems.size();
    
    psoCreateInfo.PSODesc.ResourceLayout = resourceLayoutDesc;
    psoCreateInfo.pVS = shaderVertex;
    psoCreateInfo.pPS = shaderPixel;
    renderDevice->CreateGraphicsPipelineState(psoCreateInfo, &pso);

    pso->CreateShaderResourceBinding(&shaderBinding, true);
    auto shaderVarConstants = shaderBinding->GetVariableByName(Dg::SHADER_TYPE_VERTEX, "VSConstants");
    if (shaderVarConstants)
    {
        shaderVarConstants->Set(constantsBuffer);
    }

    return true;
}

std::vector<Dg::LayoutElement> PipelineShaderObject::GetLayoutElements()
{
    return
    {
        // Attribute 0 - vertex position
        Dg::LayoutElement{0, 0, 3, Dg::VT_FLOAT32, false},
        // Attribute 1 - vertex normal
        Dg::LayoutElement{1, 0, 3, Dg::VT_FLOAT32, false},
        // Attribute 2 - texture coordinates
        Dg::LayoutElement{2, 0, 2, Dg::VT_FLOAT32, false},
        // Attribute 3 - vertex colors
        Dg::LayoutElement{3, 0, 4, Dg::VT_FLOAT32, false}
    };
}

String PipelineShaderObject::GetShaderSourceVertex()
{
    return "";
}

String PipelineShaderObject::GetShaderSourcePixel()
{
    return "";
}
