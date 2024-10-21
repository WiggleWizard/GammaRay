#include "GameViewport.h"

#include "Engine/World.h"
#include "Input/InputEvent.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/CameraComponent.h"

#include <entt/entity/registry.hpp>

class CameraComponent;

GameViewport::GameViewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice)
    : Super(swapChain, renderDevice)
{
    
}

void GameViewport::PreProcess()
{
    if (!IsValid(world))
    {
        return;
    }

    auto registry = world->GetRegistry();
    auto viewCameras = registry->view<TransformComponent, CameraComponent>();
    viewCameras.each([&](const auto& entity, TransformComponent& xform, CameraComponent& camera)
    {
        camPitch += (float)mouseMotion.y * 0.01f;
        camYaw += (float)mouseMotion.x * -0.01f;

        Dg::float3 position = { xform.matrix._41, xform.matrix._42, xform.matrix._43 };
        
        Dg::float4x4 rotationMatrix;
        rotationMatrix = Dg::float4x4::RotationY(camYaw) * Dg::float4x4::RotationX(camPitch);

        xform.matrix = rotationMatrix;
        xform.matrix._41 = position.x;
        xform.matrix._42 = position.y;
        xform.matrix._43 = position.z;

        // Consume
        mouseMotion = { 0, 0 };
    });
}

void GameViewport::OnInputEvent(const ObjectPtr<InputEvent> inputEvent)
{
    // When the mouse is focused on the viewport and the user presses mouse button 1, then store that state
    ObjectPtr<InputEventMouseButton> inputEventMouseButton = Cast<InputEventMouseButton>(inputEvent);
    if (IsValid(inputEventMouseButton))
    {
        if (inputEventMouseButton->buttonIndex == 1)
        {
            if (inputEventMouseButton->pressed && mouseFocused)
            {
                holdingLeftMouse = true;
            }
            else if (!inputEventMouseButton->pressed)
            {
                holdingLeftMouse = false;
            }
            
            inputEvent->Handled();
        }
    }

    // While the user holds mouse 1, then update some internal trackers
    if (holdingLeftMouse)
    {
        ObjectPtr<InputEventMouseMotion> inputEventMouseMotion = Cast<InputEventMouseMotion>(inputEvent);
        if (IsValid(inputEventMouseMotion))
        {
            mouseMotion += inputEventMouseMotion->velocity;
        }
    }
}
