#pragma once

class PipelineShaderObject : public Object
{
public:
    PipelineShaderObject();
    
    bool Initialize(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice, Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain);
    virtual std::vector<Dg::LayoutElement> GetLayoutElements();

    virtual void Bind(Dg::RefCntAutoPtr<Dg::IDeviceContext> ctx);
    virtual void SetupCustomConstantsBuffer(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice, size_t bufferSize);
    virtual void Commit(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext);

    bool Validate();

protected:
    virtual void SetupConstantsBuffer(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice);
    virtual size_t GetConstantBufferSizeVS() { return 0; }
    virtual size_t GetConstantBufferSizePS() { return 0; }

    virtual String GetShaderSourceVertex();
    virtual String GetShaderSourcePixel();

    bool initialized = false;

    Dg::RefCntAutoPtr<Dg::IPipelineState> pso;
    Dg::RefCntAutoPtr<Diligent::IShaderResourceBinding> shaderBinding;

    Dg::RefCntAutoPtr<Dg::IBuffer> constantsBufferVS;
    Dg::RefCntAutoPtr<Dg::IBuffer> constantsBufferPS;
};
