#pragma once

#include "Core/Object/Component.h"
#include "Servers/SceneServer.h"
#include "Core/Input/Input.h"


struct ComponentEditorCamera3DMovement : public Component
{
    float moveSpeed = .04f;
    float rotationSpeed = 0.2f;

    // TODO: This is just temporary largely because GetMouseVelocity is broken
    glm::ivec2 prevMousePos = {0.f, 0.f};

    virtual void OnInit() override
    {
        SceneServer::GetSingleton()->RegisterForOnUpdate(std::bind(&ComponentEditorCamera3DMovement::OnUpdate, this));
    }

    void OnUpdate()
    {
        ComponentTransform3D& transform3D = owner.GetComponent<ComponentTransform3D>();
        ComponentCamera3D& camera = owner.GetComponent<ComponentCamera3D>();

        Input* input = Input::GetSingleton();

        glm::ivec2 mouseVelocity = input->GetMousePosition() - prevMousePos;

        // Rotate camera
        transform3D.rotation.y += mouseVelocity.x * rotationSpeed;
        transform3D.rotation.p -= mouseVelocity.y * rotationSpeed;

        transform3D.rotation.p = glm::fclamp(transform3D.rotation.p, -89.f, 89.f);

        // Calc forward vector from pitch and yaw input
        camera.forward.x = cos(glm::radians(transform3D.rotation.y)) * cos(glm::radians(transform3D.rotation.p));
        camera.forward.y = sin(glm::radians(transform3D.rotation.p));
        camera.forward.z = sin(glm::radians(transform3D.rotation.y)) * cos(glm::radians(transform3D.rotation.p));
        camera.forward = glm::normalize(camera.forward);

        // Recalc other direction vectors
        camera.right = glm::normalize(glm::cross(camera.forward, {0.f, 1.f, 0.f}));
        camera.up    = glm::normalize(glm::cross(camera.right, camera.forward));

        // Move camera
        glm::vec2 wishDir = {0.f, 0.f};

        if(input->IsKeyPressed(GR_KEY_A))
            wishDir.x = -1.f;
        if(input->IsKeyPressed(GR_KEY_D))
            wishDir.x = 1.f;
        if(input->IsKeyPressed(GR_KEY_W))
            wishDir.y = 1.f;
        if(input->IsKeyPressed(GR_KEY_S))
            wishDir.y = -1.f;

        transform3D.position += camera.forward * wishDir.y * moveSpeed;
        transform3D.position += camera.right * wishDir.x * moveSpeed;

        prevMousePos = input->GetMousePosition();
    }
};
