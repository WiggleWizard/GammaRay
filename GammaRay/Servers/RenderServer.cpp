#include "grpch.h"
#include "RenderServer.h"

#include "Servers/SceneServer.h"

#include "Scene/Components/Transform.h"

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
        const auto& view = registry.view<ComponentTransform3D, ComponentRenderTransform3D>();
        for(entt::entity entity : view)
        {
            ComponentTransform3D transform3D = view.get<ComponentTransform3D>(entity);

            // Take the transform3D and push it into the matrix if the component is dirty
            //if(transform3D.isDirty())
            {
                ComponentRenderTransform3D renderTransform3D = view.get<ComponentRenderTransform3D>(entity);

                glm::mat4 model = glm::mat4(1.0f);
                glm::mat4 view = glm::mat4(1.0f);
                glm::mat4 projection = glm::mat4(1.0f);
                //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
                view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
                projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

                // Retrieve the matrix uniform locations
                int modelLoc = glGetUniformLocation(m_shader->GetRendererId(), "model");
                int viewLoc  = glGetUniformLocation(m_shader->GetRendererId(), "view");

                // pass them to the shaders (3 different ways)
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

                // TODO: Only set this when the camera projection changes
                m_shader->setMat4("projection", projection);
            }
        }
    }

    // Render
    {
        const auto& view = registry.view<ComponentRenderTransform3D>();
        for(entt::entity entity : view)
        {
            ComponentRenderTransform3D renderTransform3D = view.get<ComponentRenderTransform3D>(entity);
            
        }
    }

    m_vertexArray->Bind();
    //m_squareVA->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

RenderServer::RenderServer()
{
    m_singleton = this;

    m_shader.reset(new RendererShaderDefault());
    m_shader->Compile();


    m_vertexArray.reset(VertexArray::Create());

    float vertices[] = {
        // positions          // texture coords
        0.5f,  0.5f, 0.0f,   0.8, 0.2, 0.8, 1.0,
        0.5f, -0.5f, 0.0f,   0.2, 0.3, 0.8, 1.0,
        -0.5f, -0.5f, 0.0f,   0.8, 0.8, 0.2, 1.0,
        -0.5f,  0.5f, 0.0f,  1.0, 0.8, 0.2, 1.0,
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    BufferLayout layout = {
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float4, "a_Color" },
    };
    m_vertexBuffer->SetLayout(layout);
    m_vertexArray->AddVertexBuffer(m_vertexBuffer);

    m_indexBuffer.reset(IndexBuffer::Create(indices, 3));
    m_vertexArray->AddIndexBuffer(m_indexBuffer);




    /*

    m_squareVA.reset(VertexArray::Create());

    float squareVertices[3 * 3 * 4] = {
        -0.5f, -0.5f, 0.0f,  0.8, 0.2, 0.8, 1.0,
        0.5f, -0.5f, 0.0f,   0.2, 0.3, 0.8, 1.0,
        0.0f, 0.5f, 0.0f,    0.8, 0.8, 0.2, 1.0,
        0.5f, 0.5f, 0.0f,    1.0, 0.8, 0.2, 1.0,
    };
    std::shared_ptr<VertexBuffer> squareVB;
    squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float4, "a_Color" },
    });
    m_squareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    std::shared_ptr<IndexBuffer> squareIB;
    squareIB.reset(IndexBuffer::Create(squareIndices, 6));
    m_squareVA->AddIndexBuffer(squareIB);
    */
}
