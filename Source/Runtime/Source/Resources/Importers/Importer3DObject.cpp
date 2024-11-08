#include "Importer3DObject.h"

#include "Resources/FileIO/FileIO3DObject.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void Importer3DObject::Import(const std::filesystem::path& source, ObjectPtr<FileIO> fileIO)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(source.string(),
         aiProcess_Triangulate | // Ensure all faces are triangles
         aiProcess_GenNormals | // Generate normals if not present
         aiProcess_CalcTangentSpace | // Calculate tangents and bitangents
         aiProcess_JoinIdenticalVertices // Optimize mesh
    );

    auto fileIO3DObject = Cast<FileIO3DObject>(fileIO);
    if (!IsValid(fileIO3DObject))
    {
        throw std::runtime_error("Invalid FileIO object");
    }
    
    fileIO3DObject->Write(scene);
}

ObjectPtr<FileIO> Importer3DObject::CreateFileIO(const ResPath& resPath)
{
    return NewObject<FileIO3DObject>(resPath, false);
}
