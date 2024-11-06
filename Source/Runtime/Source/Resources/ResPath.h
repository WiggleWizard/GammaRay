#pragma once

#include <filesystem>

class ResPath
{
public:
    ResPath(String p) : path(p) {}

    void Back()
    {
        path = path.parent_path();
    }

    String ToString() const
    {
        return path.string();
    }

protected:
    std::filesystem::path path;
};
