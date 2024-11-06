#pragma once

#include <filesystem>
#include <string>
#include <vector>

class ResPath
{
public:
    // Constructor
    ResPath() : path("")
    {
        
    }
    
    ResPath(const std::string& p) : path(p)
    {
    }

    ResPath(const char* p) : path(p)
    {
    }

    ResPath(const std::filesystem::path p) : path(p)
    {
    }

    // Back navigation
    void Back()
    {
        path = path.parent_path();
    }

    bool HasParentPath() const
    {
        return path.has_parent_path();
    }

    bool IsEmpty() const
    {
        return path.empty();
    }

    // Path combination operator
    ResPath operator/(const ResPath& other) const
    {
        return {(path / other.ToString()).string()};
    }

    ResPath operator/(const std::string& other) const
    {
        return {(path / other).string()};
    }

    ResPath operator/(const char* other) const
    {
        return {(path / other).string()};
    }

    ResPath& operator/=(const ResPath& other)
    {
        path /= other.path;
        return *this;
    }

    ResPath& operator/=(const std::string& other)
    {
        path /= other;
        return *this;
    }

    ResPath& operator/=(const char* other)
    {
        path /= other;
        return *this;
    }

    // String conversion with normalization
    std::string ToString() const
    {
        std::string result = path.string();
        // Replace backslashes with forward slashes
        std::replace(result.begin(), result.end(), '\\', '/');
        return result;
    }

    std::filesystem::path ToPath()
    {
        return path;
    }

    void Normalize()
    {
        // Convert to string and normalize slashes
        std::string normalized = path.string();
        std::replace(normalized.begin(), normalized.end(), '\\', '/');
        path = normalized;
    }

    ResPath Filename() const
    {
        return { path.filename() };
    }

    String Ext() const
    {
        return path.extension().string();
    }

public:
    class iterator
    {
    public:
        iterator(const std::filesystem::path& p, const std::filesystem::path::iterator& it)
            : path(p), pathIt(it)
        {
            if (pathIt != path.end())
            {
                current = pathIt->string();
            }
        }

        iterator& operator++()
        {
            ++pathIt;
            if (pathIt != path.end())
            {
                current = pathIt->string();
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const
        {
            return pathIt == other.pathIt;
        }

        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

        const std::string& operator*() const
        {
            return current;
        }

    private:
        const std::filesystem::path& path; // Reference to the original path
        std::filesystem::path::iterator pathIt;
        std::string current;
    };

    iterator begin() const
    {
        return iterator(path, path.begin());
    }

    iterator end() const
    {
        return iterator(path, path.end());
    }

private:
    std::filesystem::path path;
};
