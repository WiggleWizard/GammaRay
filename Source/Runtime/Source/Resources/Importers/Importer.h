#pragma once

#include "Resources/ResPath.h"

class FileIO;

class Importer : public Object
{
public:
    virtual void Import(const std::filesystem::path& source, ObjectPtr<FileIO> fileIO) = 0;
    virtual ObjectPtr<FileIO> CreateFileIO(const String& file, bool isLoadingFromDisk) = 0;
};
