#include "FileIO.h"

void FileMetadataHeader::Serialize(Archive& archive)
{
    archive << fileType;
    archive << sourcePath;
}

FileIO::FileIO(const ResPath& inResPath, bool loadFromDisk)
    : archive(loadFromDisk)
    , resPath(inResPath)
{
}

void FileIO::SetSavingToDisk(bool isLoadingFromDisk)
{
    archive = Archive(isLoadingFromDisk);
}

void FileIO::WriteMetadata(FileMetadataHeader& metadata)
{
    archive << metadata;
}

void FileIO::Finalize()
{
    
}
