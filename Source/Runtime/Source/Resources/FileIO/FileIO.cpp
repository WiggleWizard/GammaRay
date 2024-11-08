#include "FileIO.h"

void FileMetadataHeader::Serialize(Archive& archive)
{
    archive << fileType;
    archive << sourcePath;
}

FileIO::FileIO(const String& inFilePath, bool isLoadingFromDisk)
    : archive(isLoadingFromDisk)
    , filePath(inFilePath)
{
}

void FileIO::SetSavingToDisk(bool isLoadingFromDisk)
{
    archive = Archive(isLoadingFromDisk);
}

void FileIO::WriteMetadata(const FileMetadataHeader& metadata)
{
    
}

void FileIO::Finalize()
{
    
}
