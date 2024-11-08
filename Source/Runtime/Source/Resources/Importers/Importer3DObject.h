#pragma once

#include "Importer.h"

class Importer3DObject : public Importer
{
public:
    void Import(const std::filesystem::path& source, ObjectPtr<FileIO> fileIO) override;
    ObjectPtr<FileIO> CreateFileIO(const ResPath& file) override;
};
