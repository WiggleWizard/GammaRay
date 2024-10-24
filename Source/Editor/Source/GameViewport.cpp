#include "GameViewport.h"

#include "Engine/World.h"
#include "Input/InputEvent.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/CameraComponent.h"

#include <SDL_mouse.h>
#include <entt/entity/registry.hpp>

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
        camPitch += (float)mouseMotion.y * -0.01f;
        camYaw += (float)mouseMotion.x * 0.01f;

        Dg::float3 position = { xform.matrix._41, xform.matrix._42, xform.matrix._43 };
        
        Dg::float4x4 rotationMatrix;
        rotationMatrix = Dg::float4x4::RotationX(camPitch) * Dg::float4x4::RotationY(camYaw);

        Dg::float3 forwardVec = GetForwardVector(rotationMatrix);
        Dg::float3 rightVec = GetRightVector(rotationMatrix);

        if (Dg::length(inputDir) > 0.f)
        {
            Dg::float3 moveDir = forwardVec * inputDir.y + rightVec * inputDir.x;
            position += moveDir * cameraMoveSpeed;
        }

        xform.matrix = rotationMatrix * Dg::float4x4::Translation(position.x, position.y, position.z);

        // Consume
        mouseMotion = { 0, 0 };
        // inputDir = { 0.f, 0.f };
    });
}

void GameViewport::OnInputEvent(const ObjectPtr<InputEvent> inputEvent)
{
    // When the mouse is focused on the viewport and the user presses mouse button 1, then store that state
    ObjectPtr<InputEventMouseButton> inputEventMouseButton = Cast<InputEventMouseButton>(inputEvent);
    if (IsValid(inputEventMouseButton))
    {
        if (inputEventMouseButton->buttonIndex == 3)
        {
            if (inputEventMouseButton->pressed && mouseFocused)
            {
                controllingCamera = true;
                SDL_GetGlobalMouseState(&initialDown.x, &initialDown.y);
                SDL_SetRelativeMouseMode(SDL_TRUE);
            }
            
            // Mouse button was released if was controlling camera
            if (controllingCamera && !inputEventMouseButton->pressed)
            {
                controllingCamera = false;
                SDL_SetRelativeMouseMode(SDL_FALSE);
                SDL_WarpMouseGlobal(initialDown.x, initialDown.y);
            }
            
            inputEvent->Handled();
        }
    }

    // While the user holds mouse 1, then update some internal trackers
    if (controllingCamera)
    {
        ObjectPtr<InputEventMouseMotion> inputEventMouseMotion = Cast<InputEventMouseMotion>(inputEvent);
        if (IsValid(inputEventMouseMotion))
        {
            mouseMotion += inputEventMouseMotion->velocity;
        }

        ObjectPtr<InputEventKey> inputEventKey = Cast<InputEventKey>(inputEvent);
        if (IsValid(inputEventKey))
        {
            if (!inputEventKey->echo)
            {
                if (inputEventKey->pressed)
                {
                    if (inputEventKey->scancode == SDL_SCANCODE_W)
                        inputDir.y += 1.f;
                    else if (inputEventKey->scancode == SDL_SCANCODE_S)
                        inputDir.y -= 1.f;
                    else if (inputEventKey->scancode == SDL_SCANCODE_A)
                        inputDir.x -= 1.f;
                    else if (inputEventKey->scancode == SDL_SCANCODE_D)
                        inputDir.x += 1.f;
                }
                else
                {
                    if (inputEventKey->scancode == SDL_SCANCODE_W)
                        inputDir.y -= 1.f;
                    else if (inputEventKey->scancode == SDL_SCANCODE_S)
                        inputDir.y += 1.f;
                    else if (inputEventKey->scancode == SDL_SCANCODE_A)
                        inputDir.x += 1.f;
                    else if (inputEventKey->scancode == SDL_SCANCODE_D)
                        inputDir.x -= 1.f;
                }
            }
        }
    }
}
