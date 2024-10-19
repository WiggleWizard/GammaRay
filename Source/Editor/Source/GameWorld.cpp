#include "GameWorld.h"

#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/SimpleMeshComponent.h"
#include "Scene/Components/StaticMeshComponent.h"
#include "Scene/Components/TransformComponent.h"

#include <entt/entity/registry.hpp>

GameWorld::GameWorld()
{

}

void GameWorld::Initialize()
{
    auto cameraEntity = registry->create();
    registry->emplace<TransformComponent>(cameraEntity);
    registry->emplace<CameraComponent>(cameraEntity);

    auto simpleMeshEntity = registry->create();
    xformComponent = &registry->emplace<TransformComponent>(simpleMeshEntity);
    SimpleMeshComponent simpleMeshComponent = registry->emplace<SimpleMeshComponent>(simpleMeshEntity);
    simpleMeshComponent.GenerateMesh();
}

void GameWorld::Process()
{
    const Dg::float4x4 rotationMatrix = rotationMatrix.RotationArbitrary(Dg::float3{0.f, 1.f, 0.f}, rotation);
    const Dg::float4x4 translationMatrix = translationMatrix.Translation(0.f, 0.f, 5.f);
    
    xformComponent->matrix = rotationMatrix * translationMatrix;

    rotation += 0.01f;
}
