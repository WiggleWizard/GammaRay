#pragma once

class PipelineShaderObject;

class Material : public Object
{
public:
    ObjectPtr<PipelineShaderObject> pso = nullptr;
};
