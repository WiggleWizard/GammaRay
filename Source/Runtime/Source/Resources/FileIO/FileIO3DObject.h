#pragma once

#include "FileIO.h"

struct aiScene;

class FileIO3DObject : public FileIO
{
public:
    FileIO3DObject(const ResPath& inResPath, bool isLoadingFromDisk);
    
    void Write(const aiScene* scene);
};
