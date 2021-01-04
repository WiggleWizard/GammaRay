#pragma once

#include "Servers/SceneServer.h"
#include "Core/Object/Entity.h"
#include "Scene/Components/Transform.h"
#include "Scene/Components/3D/Mesh.h"


class ConceptMesh3D : public Entity
{
public:
    virtual void InitComponents() override
    {
        AddComponent<ComponentRenderTransform3D>();
        AddComponent<ComponentTransform3D>();
        InitMesh(AddComponent<ComponentMesh3D>());
    }

    virtual void InitMesh(ComponentMesh3D& componentMesh3D) {}
};

class ConceptMesh3DBox : public ConceptMesh3D
{
public:
    virtual void InitMesh(ComponentMesh3D& componentMesh3D) override
    {
        componentMesh3D.vertexArray.reset(VertexArray::Create());

        float vertices[] = {
            -0.5f, -0.5f, -0.5f,     1.0, 1.0, 1.0, 1.0,
             0.5f, -0.5f, -0.5f,     1.0, 1.0, 1.0, 1.0,
             0.5f,  0.5f, -0.5f,     1.0, 1.0, 1.0, 1.0,
            -0.5f,  0.5f, -0.5f,     1.0, 1.0, 1.0, 1.0,

            -0.5f, -0.5f,  0.5f,     1.0, 1.0, 1.0, 1.0,
             0.5f, -0.5f,  0.5f,     1.0, 1.0, 1.0, 1.0,
             0.5f,  0.5f,  0.5f,     1.0, 1.0, 1.0, 1.0,
            -0.5f,  0.5f,  0.5f,     1.0, 1.0, 1.0, 1.0,

            -0.5f,  0.5f, -0.5f,     1.0, 1.0, 1.0, 1.0,
            -0.5f, -0.5f, -0.5f,     1.0, 1.0, 1.0, 1.0,
            -0.5f, -0.5f,  0.5f,     1.0, 1.0, 1.0, 1.0,
            -0.5f,  0.5f,  0.5f,     1.0, 1.0, 1.0, 1.0,

             0.5f, -0.5f, -0.5f,     1.0, 1.0, 1.0, 1.0,
             0.5f,  0.5f, -0.5f,     1.0, 1.0, 1.0, 1.0,
             0.5f,  0.5f,  0.5f,     1.0, 1.0, 1.0, 1.0,
             0.5f, -0.5f,  0.5f,     1.0, 1.0, 1.0, 1.0,

            -0.5f, -0.5f, -0.5f,     1.0, 1.0, 1.0, 1.0,
             0.5f, -0.5f, -0.5f,     1.0, 1.0, 1.0, 1.0,
             0.5f, -0.5f,  0.5f,     1.0, 1.0, 1.0, 1.0,
            -0.5f, -0.5f,  0.5f,     1.0, 1.0, 1.0, 1.0,

             0.5f,  0.5f, -0.5f,     1.0, 1.0, 1.0, 1.0,
            -0.5f,  0.5f, -0.5f,     1.0, 1.0, 1.0, 1.0,
            -0.5f,  0.5f,  0.5f,     1.0, 1.0, 1.0, 1.0,
             0.5f,  0.5f,  0.5f,     1.0, 1.0, 1.0, 1.0,
        };

        unsigned int indices[] = {
            0, 3, 2,
            2, 1, 0,
            4, 5, 6,
            6, 7 ,4,
            11, 8, 9,
            9, 10, 11,
            12, 13, 14,
            14, 15, 12,
            16, 17, 18,
            18, 19, 16,
            20, 21, 22,
            22, 23, 20,
        };

        componentMesh3D.vertices.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
        };
        componentMesh3D.vertices->SetLayout(layout);
        componentMesh3D.vertexArray->AddVertexBuffer(componentMesh3D.vertices);

        componentMesh3D.indices.reset(IndexBuffer::Create(indices, sizeof(indices)));
        componentMesh3D.vertexArray->AddIndexBuffer(componentMesh3D.indices);
    }
};
