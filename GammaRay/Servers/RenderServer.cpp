#include "grpch.h"
#include "RenderServer.h"

#include "Servers/SceneServer.h"

#include "Scene/Components/Transform.h"
#include "Scene/Components/Camera.h"
#include "Scene/Components/3D/Mesh.h"

#include "Core/Renderer/Shaders/default.gen.h"
#include "Drivers/OpenGL/Shaders/depth.gen.h"

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
    float time = (float)glfwGetTime();
    m_frameTime = time - m_lastFrameTime;
    m_lastFrameTime = time;

    m_drawCallsThisFrame = 0;

    SceneServer* sceneServer = SceneServer::GetSingleton();

    entt::registry& registry = sceneServer->GetRawRegistry();

    // Bind default shader
    // TODO: At some point this obviously needs to be the active rendering component's material shader
    m_shader->Bind();
    m_fboMain->Bind();

    const Color& clearColor = {0.075f, 0.075f, 0.075f};
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 cameraMatrix;
    glm::vec3 cameraPosition, cameraFront, cameraUp;
    float cameraFov = 0.f;

    // Get camera in scene
    // TODO: How do we ensure this is our "active camera"
    {
        const auto& view = registry.view<ComponentTransform3D, ComponentCamera3D>();

        // TODO: Set projection matrix (if camera dirty) of the shader
        for(entt::entity entity : view)
        {
            ComponentTransform3D& cameraTransform = view.get<ComponentTransform3D>(entity);
            ComponentCamera3D& camera = view.get<ComponentCamera3D>(entity);

            cameraPosition = cameraTransform.position;
            cameraFront    = camera.forward;
            cameraUp       = camera.up;

            cameraMatrix   = camera.GetViewMatrix();
            cameraFov      = camera.fov;
        }
    }

    // Calculate matrices if dirty
    {
        const auto& view = registry.view<ComponentTransform3D, ComponentRenderTransform3D, ComponentMesh3D>();
        for(entt::entity entity : view)
        {
            ComponentTransform3D& transform3D = view.get<ComponentTransform3D>(entity);

            // Take the transform3D and push it into the matrix if the component is dirty
            //if(transform3D.isDirty())
            {
                ComponentRenderTransform3D& renderTransform3D = view.get<ComponentRenderTransform3D>(entity);
                ComponentMesh3D& mesh3D = view.get<ComponentMesh3D>(entity);

                glm::mat4 projection = glm::perspective(glm::radians(cameraFov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
                m_shader->SetMat4("projection", projection);

                glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
                m_shader->SetMat4("view", view);

                glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                model = glm::translate(model, transform3D.position);
                //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                m_shader->SetMat4("model", model);

                if(mesh3D.vertexArray)
                {
                    mesh3D.vertexArray->Bind();
                    glDrawElements(GL_TRIANGLES, mesh3D.indices->GetCount(), GL_UNSIGNED_INT, nullptr);
                    m_drawCallsThisFrame++;
                }
            }
        }
    }

    m_shader->Unbind();
    m_fboMain->Unbind();
}

RenderServer::RenderServer()
{
    m_singleton = this;

    m_shader.reset(new RendererShaderDefault());
    m_shader->Compile();

    m_shaderDepth.reset(new RendererShaderDepth());
    m_shaderDepth->Compile();

    // Gen FBO
    m_fboMain.reset(FrameBuffer::Create());
    m_fboMain->Bind();

    // Gen RBO for depth and stencil access
    m_rboDepth.reset(RenderBuffer::Create());
    //m_rboDepth->Bind();
    //m_rboDepth->SetStorage(GL_DEPTH24_STENCIL8, {800, 600});
    //m_fboDepth->AttachRenderBuffer(m_rboDepth.get(), GL_DEPTH_STENCIL_ATTACHMENT);

    // TODO: Abstract this
    glEnable(GL_DEPTH_TEST);

    // Gen and attach texture
    m_texDepth.reset(TextureBuffer::Create());
    m_texDepth->Bind();
    m_texDepth->BindRGBTexture({800, 600}, GL_DEPTH_COMPONENT);

    m_texColor.reset(TextureBuffer::Create());
    m_texColor->Bind();
    m_texColor->BindRGBTexture({800, 600}, GL_RGB);

    m_fboMain->AttachTextureBuffer(m_texDepth.get(), GL_DEPTH_ATTACHMENT);
    m_fboMain->AttachTextureBuffer(m_texColor.get(), GL_COLOR_ATTACHMENT0);

    m_fboMain->Unbind();
}

RenderServer::~RenderServer()
{
}
