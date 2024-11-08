#include "FileIO3DObject.h"

#include "Core/Memory/Archive.h"

#include <assimp/scene.h>

FileIO3DObject::FileIO3DObject(const String& inFilePath, bool isLoadingFromDisk) : FileIO(inFilePath, isLoadingFromDisk)
{
}

void FileIO3DObject::Write(const aiScene* scene)
{
    Archive a;
    int b = 3;
    a << b;

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        //throw std::runtime_error("Assimp error: " + std::string(importer.GetErrorString()));
    }

    // For simplicity, we'll just process the first mesh
    if (scene->mNumMeshes == 0)
    {
        throw std::runtime_error("No meshes found in file");
    }

    const aiMesh* mesh = scene->mMeshes[0];
}
