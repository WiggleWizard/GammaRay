#include "grpch.h"
#include "RenderServer.h"

#include "Servers/SceneServer.h"

#include "Scene/Components/Transform.h"
#include "Scene/Components/3D/Mesh.h"

#include "Core/Renderer/Shaders/default.gen.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glfw/glfw3.h>

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

RenderServer* RenderServer::m_singleton = nullptr;

void RenderServer::OnUpdate()
{
    SceneServer* sceneServer = SceneServer::GetSingleton();

    entt::registry& registry = sceneServer->GetRawRegistry();

    // Bind default shader
    // TODO: At some point this obviously needs to be the active rendering component's material shader
    m_shader->Bind();

    // Get camera in scene
    // TODO: How do we ensure this is our "active camera"
    {
        const auto& view = registry.view<ComponentTransform3D, ComponentRenderTransform3D>();

        // TODO: Set projection matrix (if camera dirty) of the shader
    }

    // Calculate matrices if dirty
    {
        const auto& view = registry.view<ComponentTransform3D, ComponentRenderTransform3D, ComponentMesh3D>();
        for(entt::entity entity : view)
        {
            ComponentTransform3D transform3D = view.get<ComponentTransform3D>(entity);

            // Take the transform3D and push it into the matrix if the component is dirty
            //if(transform3D.isDirty())
            {
                ComponentRenderTransform3D renderTransform3D = view.get<ComponentRenderTransform3D>(entity);
                ComponentMesh3D mesh3D = view.get<ComponentMesh3D>(entity);

                glm::mat4 model = glm::mat4(1.0f);
                glm::mat4 view = glm::mat4(1.0f);
                glm::mat4 projection = glm::mat4(1.0f);

                //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
                view = glm::translate(view, transform3D.position);
                projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

                // Retrieve the matrix uniform locations
                int modelLoc = glGetUniformLocation(m_shader->GetRendererId(), "model");
                int viewLoc  = glGetUniformLocation(m_shader->GetRendererId(), "view");

                // pass them to the shaders (3 different ways)
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

                // TODO: Only set this when the camera projection changes
                m_shader->setMat4("projection", projection);

                if(mesh3D.vertexArray.get())
                {
                    mesh3D.vertexArray->Bind();
                    glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
                }
            }
        }
    }
}

RenderServer::RenderServer()
{
    m_singleton = this;

    m_shader.reset(new RendererShaderDefault());
    m_shader->Compile();
}
