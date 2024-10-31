#pragma once

#include "Resources/ResourceMasterMaterial.h"

class ResourceMasterMaterialGrid : public ResourceMasterMaterial
{
public:
    ResourceMasterMaterialGrid();

    virtual ObjectPtr<PipelineShaderObject> GetPSO() override { return psoGrid; }

protected:
    ObjectPtr<PipelineShaderObject> psoGrid = nullptr;
};
