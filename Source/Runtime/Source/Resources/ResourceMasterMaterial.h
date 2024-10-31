#pragma once

#include "Resource.h"

class PipelineShaderObject;

// A Master Material provides a "template" for a material instance to tie shader/PSO with data such as textures, floats, matrices, etc.
// When it comes to the data, a Master Material simply provides the defaults. A ResourceMaterialInstance must be made to modify this
// data per instance.
class ResourceMasterMaterial : public Resource
{
public:
    virtual ObjectPtr<PipelineShaderObject> GetPSO() { return nullptr; }
};
