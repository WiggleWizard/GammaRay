#pragma once

#include "Core/Object/Component.h"
#include "Servers/SceneServer.h"
#include "Core/Input/Input.h"
#include "Core/Input/InputKeyCode.h"

#include "Scene/Components/Transform.h"
#include "Scene/Components/Camera.h"


struct ComponentEditorCamera3DMovement : public Component
{
    float moveSpeed = 1.f;
    float rotationSpeed = 20.f;
    bool isActiveCamera = true; // TODO: Needs to be false by default. But currently there's only one of these in the scene
    Vector2i mouseDelta = {0.f, 0.f};

    virtual void OnInit() override
    {
        //SceneServer::GetSingleton()->RegisterForOnUpdate(std::bind(&ComponentEditorCamera3DMovement::OnUpdate, this));
    }

    void OnUpdate()
    {
    }

    void UpdateRotationAndPosition(const Vector2i& mouseDelta, const Timestep& timestep)
    {
        float deltaTime = timestep.GetSeconds();

        ComponentTransform3D& transform3D = owner.GetComponent<ComponentTransform3D>();
        ComponentCamera3D& camera = owner.GetComponent<ComponentCamera3D>();

        // Rotate camera
        transform3D.rotation.y += mouseDelta.x * rotationSpeed * deltaTime;
        transform3D.rotation.p -= mouseDelta.y * rotationSpeed * deltaTime;

        transform3D.rotation.p = glm::fclamp(transform3D.rotation.p, -89.f, 89.f);

        // Calc forward vector from pitch and yaw input
        camera.forward.x = cos(glm::radians(transform3D.rotation.y)) * cos(glm::radians(transform3D.rotation.p));
        camera.forward.y = sin(glm::radians(transform3D.rotation.p));
        camera.forward.z = sin(glm::radians(transform3D.rotation.y)) * cos(glm::radians(transform3D.rotation.p));
        camera.forward = glm::normalize(camera.forward);

        // Recalc other direction vectors
        camera.right = glm::normalize(glm::cross(camera.forward, {0.f, 1.f, 0.f}));
        camera.up = glm::normalize(glm::cross(camera.right, camera.forward));

        // Move camera
        glm::vec2 wishDir = {0.f, 0.f};
        Input* input = Input::GetSingleton();
        if(input->IsKeyPressed(GR_KEY_A))
            wishDir.x = -1.f;
        if(input->IsKeyPressed(GR_KEY_D))
            wishDir.x = 1.f;
        if(input->IsKeyPressed(GR_KEY_W))
            wishDir.y = 1.f;
        if(input->IsKeyPressed(GR_KEY_S))
            wishDir.y = -1.f;

        transform3D.position += camera.forward * wishDir.y * moveSpeed * deltaTime;
        transform3D.position += camera.right * wishDir.x * moveSpeed * deltaTime;
    }
};
