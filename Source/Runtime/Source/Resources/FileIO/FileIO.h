#pragma once

#include "Resources/ResPath.h"

struct FileMetadataHeader
{
    String fileType;
    String sourcePath;

    void Serialize(Archive& archive);
};

class FileIO : public Object
{
public:
    FileIO(const ResPath& inResPath, bool loadFromDisk);
    
    void SetSavingToDisk(bool isLoadingFromDisk);
    
    virtual void WriteMetadata(FileMetadataHeader& metadata);
    virtual void Finalize();

protected:
    Archive archive;
    ResPath resPath;
};
