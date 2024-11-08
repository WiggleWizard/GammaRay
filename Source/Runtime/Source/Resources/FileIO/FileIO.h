#pragma once

struct FileMetadataHeader
{
    uint32 fileType;
    String sourcePath;

    void Serialize(Archive& archive);
};

class FileIO : public Object
{
public:
    FileIO(const String& inFilePath, bool isLoadingFromDisk);
    
    void SetSavingToDisk(bool isLoadingFromDisk);
    
    virtual void WriteMetadata(const FileMetadataHeader& metadata);
    virtual void Finalize();

protected:
    Archive archive;
    String filePath;
};
