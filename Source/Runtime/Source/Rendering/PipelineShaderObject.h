#pragma once

class PipelineShaderObject : public Object
{
public:
    PipelineShaderObject();
    
    bool Initialize(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice, Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain);
    virtual std::vector<Dg::LayoutElement> GetLayoutElements();

protected:
    String GetShaderSourceVertex();
    String GetShaderSourcePixel();
    
    Dg::RefCntAutoPtr<Dg::IPipelineState> pso;
    Dg::RefCntAutoPtr<Dg::IBuffer> constantsBuffer;
    Dg::RefCntAutoPtr<Diligent::IShaderResourceBinding> shaderBinding;
};
