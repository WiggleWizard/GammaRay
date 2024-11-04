#include "ResourceMasterMaterialGrid.h"

#include "Rendering/PSOs/PSOGrid.h"

ResourceMasterMaterialGrid::ResourceMasterMaterialGrid()
{
    pso = NewObject<PSOGrid>();
}
