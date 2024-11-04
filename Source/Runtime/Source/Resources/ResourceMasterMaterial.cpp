#include "ResourceMasterMaterial.h"

#include "Rendering/PipelineShaderObject.h"

bool ResourceMasterMaterial::IsPSOInitialized()
{
    if (IsValid(pso))
    {
        return pso->Validate();
    }
    return false;
}

void ResourceMasterMaterial::InitializePSO(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice, Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain)
{
    if (IsValid(pso))
    {
        pso->Initialize(renderDevice, swapChain);
    }
}
