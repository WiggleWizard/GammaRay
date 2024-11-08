#include "FileIO3DObject.h"

#include "Core/Memory/Archive.h"
#include "Core/Types/ConversionAIDG.h"

#include <assimp/scene.h>

void SerializeMesh(aiMesh* mesh, Archive& ar)
{
    for (uint32 i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex v;
        
        v.position = ConversionAIDG(mesh->mVertices[i]);
        v.normal = ConversionAIDG(mesh->mNormals[i]);

        if (mesh->mTextureCoords[0] != nullptr)
            v.uv = ConversionAIDG(mesh->mTextureCoords[0][i]);

        if (mesh->mColors[0] != nullptr)
            v.color = ConversionAIDG(mesh->mColors[0][i]);
        
        ar << v;
    }
}

FileIO3DObject::FileIO3DObject(const ResPath& inResPath, bool isLoadingFromDisk) : FileIO(inResPath, isLoadingFromDisk)
{
}

void FileIO3DObject::Write(const aiScene* scene)
{
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        //throw std::runtime_error("Assimp error: " + std::string(importer.GetErrorString()));
    }

    // For simplicity, we'll just process the first mesh
    if (scene->mNumMeshes == 0)
    {
        throw std::runtime_error("No meshes found in file");
    }

    aiMesh* mesh = scene->mMeshes[0];
    SerializeMesh(mesh, archive);
}
