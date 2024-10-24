#pragma once

class PipelineShaderObject : public Object
{
public:
    PipelineShaderObject();
    
    bool Initialize(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice, Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain);
    virtual std::vector<Dg::LayoutElement> GetLayoutElements();

    virtual void SetupCustomConstantsBuffer(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice, size_t bufferSize);
    virtual void Commit(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext);

    bool Validate();

protected:
    virtual void SetupConstantsBuffer(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice) {}
    
    virtual String GetShaderSourceVertex();
    virtual String GetShaderSourcePixel();

    bool initialized = false;

    Dg::RefCntAutoPtr<Dg::IPipelineState> pso;
    Dg::RefCntAutoPtr<Dg::IBuffer> constantsBuffer;
    Dg::RefCntAutoPtr<Diligent::IShaderResourceBinding> shaderBinding;
};
