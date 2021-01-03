#include "grpch.h"
#include "RenderServer.h"

#include "Servers/SceneServer.h"

#include "Scene/Components/Transform.h"
#include "Scene/Components/3D/Mesh.h"

#include "Core/Renderer/Shaders/default.gen.h"
#include "Drivers/OpenGL3/Shaders/depth.gen.h"

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

    glBindFramebuffer(GL_FRAMEBUFFER, m_fboDepth);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind default shader
    // TODO: At some point this obviously needs to be the active rendering component's material shader
    //m_shader->Bind();
    m_shaderDepth->Bind();

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
                int modelLoc = m_shader->GetUniformLoc("model");
                int viewLoc  = m_shader->GetUniformLoc("view");

                // pass them to the shaders (3 different ways)
                m_shader->SetMat4(modelLoc, model);
                m_shader->SetMat4(viewLoc, view);

                // TODO: Only set this when the camera projection changes
                m_shader->SetMat4("projection", projection);

                if(mesh3D.vertexArray)
                {
                    mesh3D.vertexArray->Bind();
                    glDrawElements(GL_TRIANGLES, mesh3D.indices->GetCount(), GL_UNSIGNED_INT, nullptr);
                    m_drawCallsThisFrame++;
                }
            }
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderServer::RenderServer()
{
    m_singleton = this;

    m_shader.reset(new RendererShaderDefault());
    m_shader->Compile();

    m_shaderDepth.reset(new RendererShaderDepth());
    m_shaderDepth->Compile();

    // Gen FBO
    glGenFramebuffers(1, &m_fboDepth);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboDepth);

    // Gen RBO for depth and stencil access
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    // Gen and attach texture
    glGenTextures(1, &m_texDepth);
    glBindTexture(GL_TEXTURE_2D, m_texDepth);

    glEnable(GL_DEPTH_TEST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texDepth, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderServer::~RenderServer()
{
    glDeleteFramebuffers(1, &m_fboDepth);
}
