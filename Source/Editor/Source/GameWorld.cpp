#include "GameWorld.h"

#include "Engine/Engine.h"
#include "Resources/ResourceManager.h"
#include "Resources/ResourceMasterMaterialGrid.h"
#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/MaterialComponent.h"
#include "Scene/Components/SimpleMeshComponent.h"
#include "Scene/Components/StaticMeshComponent.h"
#include "Scene/Components/TransformComponent.h"

#include <entt/entity/registry.hpp>

GameWorld::GameWorld()
{

}

void GameWorld::Initialize()
{
    Res<ResourceMasterMaterialGrid> resMMGrid = GEngine->GetResourceManager()->GetResource("/Editor/Materials/MM_Grid");
    
    auto cameraEntity = registry->create();
    registry->emplace<TransformComponent>(cameraEntity);
    registry->emplace<CameraComponent>(cameraEntity);

    auto simpleMeshEntity1 = registry->create();
    auto xformComponent1 = &registry->emplace<TransformComponent>(simpleMeshEntity1);
    xformComponent1->matrix = xformComponent1->matrix.Translation(0.f, 0.f, 5.f);
    auto simpleMeshComponent1 = &registry->emplace<SimpleMeshComponent>(simpleMeshEntity1);
    simpleMeshComponent1->GenerateMesh(SimpleMeshComponent::Quad);

    auto componentMaterial = registry->emplace<MaterialComponent>(simpleMeshEntity1);
    componentMaterial.material = ResourceMaterialInstance::FromMasterMaterial(resMMGrid);

    // auto simpleMeshEntity2 = registry->create();
    // auto xformComponent2 = &registry->emplace<TransformComponent>(simpleMeshEntity2);
    // xformComponent2->matrix = xformComponent2->matrix.Translation(5.f, 0.f, 0.f);
    // auto simpleMeshComponent2 = &registry->emplace<SimpleMeshComponent>(simpleMeshEntity2);
    // simpleMeshComponent2->GenerateMesh(SimpleMeshComponent::Cube);
}

void GameWorld::Process()
{
    // const Dg::float4x4 rotationMatrix = rotationMatrix.RotationArbitrary(Dg::float3{0.f, 1.f, 0.f}, rotation);
    // const Dg::float4x4 translationMatrix = translationMatrix.Translation(0.f, 0.f, 5.f);
    //
    // xformComponent->matrix = rotationMatrix * translationMatrix;
    //
    // rotation += 0.01f;
}
