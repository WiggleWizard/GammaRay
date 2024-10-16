#include "GameWorld.h"

#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/SimpleMeshComponent.h"
#include "Scene/Components/StaticMeshComponent.h"
#include "Scene/Components/TransformComponent.h"

#include <entt/entity/registry.hpp>

GameWorld::GameWorld()
{
    auto cameraEntity = registry->create();
    registry->emplace<TransformComponent>(cameraEntity);
    registry->emplace<CameraComponent>(cameraEntity);

    auto simpleMeshEntity = registry->create();
    TransformComponent xformComponent = registry->emplace<TransformComponent>(simpleMeshEntity);
    xformComponent.matrix.Translation(0, 0, -5.f);
    SimpleMeshComponent simpleMeshComponent = registry->emplace<SimpleMeshComponent>(simpleMeshEntity);
    simpleMeshComponent.GenerateMesh();
}
