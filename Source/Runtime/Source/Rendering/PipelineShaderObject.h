#pragma once

#include <Graphics/GraphicsTools/interface/MapHelper.hpp>

struct PSOConstantsPSBase;

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

    template<class ConstantsType>
    Diligent::MapHelper<ConstantsType> WriteVS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext)
    {
        return Dg::MapHelper<ConstantsType>(deviceContext, GetConstantBufferVS(), Dg::MAP_WRITE, Dg::MAP_FLAG_DISCARD);
    }

    template<class ConstantsType>
    Dg::MapHelper<ConstantsType> WritePS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext)
    {
        return Dg::MapHelper<ConstantsType>(deviceContext, GetConstantBufferPS(), Dg::MAP_WRITE, Dg::MAP_FLAG_DISCARD);
    }

protected:
    virtual void ModifyPSOCreationInfo(Dg::GraphicsPipelineStateCreateInfo& creationInfo) {}
    
    virtual void SetupConstantsBuffer(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice);
    virtual size_t GetConstantBufferSizeVS() { return 0; }
    virtual size_t GetConstantBufferSizePS() { return 0; }

    virtual String GetShaderSourceVertex();
    virtual String GetShaderSourcePixel();
    
    virtual Dg::RefCntAutoPtr<Dg::IBuffer> GetConstantBufferVS() { return {}; }
    virtual Dg::RefCntAutoPtr<Dg::IBuffer> GetConstantBufferPS() { return {}; }

    bool initialized = false;

    Dg::RefCntAutoPtr<Dg::IPipelineState> pso;
    Dg::RefCntAutoPtr<Diligent::IShaderResourceBinding> shaderBinding;

    Dg::RefCntAutoPtr<Dg::IBuffer> constantsBufferVS;
    Dg::RefCntAutoPtr<Dg::IBuffer> constantsBufferPS;
};
