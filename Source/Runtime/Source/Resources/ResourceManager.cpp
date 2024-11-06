#include "ResourceManager.h"

#include <filesystem>

ResourceManager::ResourceManager()
    : rootNode(std::make_unique<VirtualNode>())
{
    rootNode->isDirectory = true;
}

bool ResourceManager::CreateVirtualDirectory(const ResPath& path)
{
    if (!IsValidPath(path))
        return false;

    VirtualNode* node = CreateNodePath(path);
    if (!node)
        return false;

    node->isDirectory = true;
    return true;
}

void ResourceManager::AddVirtualResource(const ResPath& virtualPath, Resource* res)
{
    AddVirtualResource(virtualPath, Res{res});
}

void ResourceManager::AddVirtualResource(const ResPath& destPath, Res<Resource> res)
{
    VirtualNode* node = CreateNodePath(destPath);
    if (node)
    {
        node->isDirectory = false;
        node->resource = res;
    }
}

Res<Resource> ResourceManager::GetResource(const ResPath& virtualPath)
{
    VirtualNode* node = FindNode(virtualPath);
    if (!node || node->isDirectory)
    {
        return Res<Resource>{};
    }

    if (node->resource)
    {
        return node->resource;
    }

    // If no virtual resource but we have a physical path, load it
    if (!node->physicalPath.empty())
    {
        //ImportSource(node->physicalPath);
    }

    return node->resource;
}

std::vector<DirectoryInfo> ResourceManager::ListDirectories(const ResPath& path, const ListOptions& options) const
{
    DirectoryContents contents;
    const VirtualNode* node = FindNode(path);
    if (node && node->isDirectory)
    {
        ListContentsRecursive(path, node, contents, options, 0);
    }
    return contents.directories;
}

std::vector<FileInfo> ResourceManager::ListFiles(const ResPath& path, const ListOptions& options) const
{
    DirectoryContents contents;
    VirtualNode* node = FindNode(path);
    if (node && node->isDirectory)
    {
        ListContentsRecursive(path, node, contents, options, 0);
    }
    return contents.files;
}

ResourceManager::DirectoryContents ResourceManager::ListContents(const ResPath& path, const ListOptions& options) const
{
    DirectoryContents contents;
    VirtualNode* node = FindNode(path);
    if (node && node->isDirectory)
    {
        ListContentsRecursive(path, node, contents, options, 0);
    }
    return contents;
}

ResourceManager::VirtualNode* ResourceManager::FindNode(const ResPath& path) const
{
    if (path.IsEmpty())
    {
        return rootNode.get();
    }

    VirtualNode* current = rootNode.get();

    for (const auto& component : path)
    {
        if (component.empty() || component == "." || component == "/")
        {
            continue;
        }

        auto it = current->children.find(component);
        if (it == current->children.end())
        {
            return nullptr;
        }
        current = it->second.get();
    }

    return current;
}

std::vector<String> ResourceManager::SplitPath(const String& path) const
{
    std::vector<std::string> components;

    const std::filesystem::path fsPath(path);
    for (const auto& component : fsPath)
    {
        if (!component.empty())
        {
            components.push_back(component.string());
        }
    }

    return components;
}

bool ResourceManager::IsValidPath(const ResPath& path) const
{
    if (path.IsEmpty())
    {
        return false;
    }

    return true;
}

ResourceManager::VirtualNode* ResourceManager::CreateNodePath(const ResPath& path)
{
    VirtualNode* current = rootNode.get();

    for (const auto& component : path)
    {
        if (component.empty() || component == "." || component == "/")
        {
            continue;
        }

        auto& child = current->children[component];
        if (!child)
        {
            child = std::make_unique<VirtualNode>();
            child->isDirectory = true;
        }
        current = child.get();
    }

    return current;
}

bool ResourceManager::MatchesPattern(const String& filename, const String& pattern) const
{
    if (pattern.empty())
        return true;

    // Simple pattern matching
    if (pattern == "*")
        return true;

    if (pattern.starts_with("*."))
    {
        String ext = pattern.substr(2);
        return filename.ends_with(ext);
    }

    // Add more pattern matching rules as needed
    return filename == pattern;
}

FileInfo ResourceManager::GetFileInfo(const ResPath& virtualPath, const VirtualNode* node) const
{
    FileInfo info;
    info.name = virtualPath.Filename().ToString();
    info.virtualPath = virtualPath;
    info.physicalPath = node->physicalPath;
    info.isVirtual = node->physicalPath.empty();
    info.extension = GetExtension(virtualPath);

    if (!info.isVirtual)
    {
        try
        {
            auto fileStatus = std::filesystem::status(info.physicalPath);
            auto lastWriteTime = std::filesystem::last_write_time(info.physicalPath);
            info.size = std::filesystem::file_size(info.physicalPath);
            info.lastModified = std::chrono::system_clock::to_time_t(
                std::chrono::clock_cast<std::chrono::system_clock>(lastWriteTime));
        }
        catch (...)
        {
            // TODO: Handle filesystem errors gracefully
        }
    }

    return info;
}

DirectoryInfo ResourceManager::GetDirectoryInfo(const ResPath& virtualPath, const VirtualNode* node) const
{
    DirectoryInfo info;
    info.name         = virtualPath.Filename().ToString();
    info.virtualPath  = virtualPath;
    info.physicalPath = node->physicalPath;
    info.isVirtual    = node->physicalPath.empty();
    info.numChildren  = node->children.size();

    // If it's a physical directory, add physical children count
    if (!info.isVirtual)
    {
        try
        {
            size_t physicalChildren = 0;
            for (const auto& entry : std::filesystem::directory_iterator(info.physicalPath))
            {
                physicalChildren++;
            }
            info.numChildren += physicalChildren;
        }
        catch (...)
        {
            // TODO: Handle filesystem errors gracefully
        }
    }

    return info;
}

void ResourceManager::ListContentsRecursive(const ResPath& currentPath, const VirtualNode* node, DirectoryContents& contents, const ListOptions& options, size_t currentDepth) const
{
    if (!node || currentDepth > options.maxDepth)
        return;

    // Handle virtual nodes
    for (const auto& [childName, childNode] : node->children)
    {
        if (!options.includeHidden && childName.starts_with("."))
        {
            continue;
        }

        ResPath childPath = currentPath / childName;

        if (childNode->isDirectory)
        {
            if (MatchesPattern(childName, options.filterPattern))
            {
                contents.directories.push_back(GetDirectoryInfo(childPath, childNode.get()));
            }
            if (options.recursive)
            {
                ListContentsRecursive(childPath, childNode.get(), contents, options, currentDepth + 1);
            }
        }
        else
        {
            if (MatchesPattern(childName, options.filterPattern))
            {
                auto fileInfo = GetFileInfo(childPath, childNode.get());
                contents.files.push_back(fileInfo);
                contents.totalSize += fileInfo.size;
            }
        }
    }

    // Handle physical directory if mounted
    if (!node->physicalPath.empty())
    {
        try
        {
            for (const auto& entry : std::filesystem::directory_iterator(node->physicalPath))
            {
                String entryName = entry.path().filename().string();
                if (!options.includeHidden && entryName.starts_with("."))
                {
                    continue;
                }

                ResPath virtualChildPath = currentPath / entryName;

                if (entry.is_directory())
                {
                    if (MatchesPattern(entryName, options.filterPattern))
                    {
                        DirectoryInfo dirInfo;
                        dirInfo.name = entryName;
                        dirInfo.virtualPath = virtualChildPath;
                        dirInfo.physicalPath = entry.path().string();
                        dirInfo.isVirtual = false;
                        contents.directories.push_back(dirInfo);
                    }
                    if (options.recursive)
                    {
                        VirtualNode* childNode = FindNode(virtualChildPath);
                        ListContentsRecursive(virtualChildPath, childNode, contents, options, currentDepth + 1);
                    }
                }
                else if (entry.is_regular_file())
                {
                    if (MatchesPattern(entryName, options.filterPattern))
                    {
                        FileInfo fileInfo;
                        fileInfo.name = entryName;
                        fileInfo.virtualPath = virtualChildPath;
                        fileInfo.physicalPath = entry.path().string();
                        fileInfo.isVirtual = false;
                        fileInfo.size = entry.file_size();
                        // TODO: fileInfo.lastModified = std::chrono::system_clock::to_time_t(entry.last_write_time());
                        fileInfo.extension = GetExtension(entryName);

                        contents.files.push_back(fileInfo);
                        contents.totalSize += fileInfo.size;
                    }
                }
            }
        }
        catch (...)
        {
            // TODO: Handle filesystem errors gracefully
        }
    }
}

String ResourceManager::GetExtension(const ResPath& path) const
{
    String ext = path.Ext();
    return ext.empty() ? ext : ext.substr(1); // Remove the dot from extension
}
