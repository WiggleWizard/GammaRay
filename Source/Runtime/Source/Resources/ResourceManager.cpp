#include "ResourceManager.h"

#include <filesystem>

ResourceManager::ResourceManager()
    : rootNode(std::make_unique<VirtualNode>())
{
    rootNode->isDirectory = true;
}

bool ResourceManager::CreateVirtualDirectory(const String& path)
{
    if (!IsValidPath(path))
        return false;

    VirtualNode* node = CreateNodePath(path);
    if (!node)
        return false;

    node->isDirectory = true;
    return true;
}

void ResourceManager::AddVirtualResource(const String& virtualPath, Resource* res)
{
    AddVirtualResource(virtualPath, Res{ res });
}

void ResourceManager::AddVirtualResource(const String& destPath, Res<Resource> res)
{
    VirtualNode* node = CreateNodePath(destPath);
    if (node)
    {
        node->isDirectory = false;
        node->resource = res;
    }
}

Res<Resource> ResourceManager::GetResource(const String& virtualPath)
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

ResourceManager::VirtualNode* ResourceManager::FindNode(const String& path) const
{
    if (path.empty() || path == "/")
    {
        return rootNode.get();
    }

    const std::vector<String> components = SplitPath(path);
    VirtualNode* current = rootNode.get();

    for (const auto& component : components)
    {
        if (component.empty() || component == ".")
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
    std::vector<String> components;
    const std::filesystem::path fsPath(path);

    for (const auto& component : fsPath)
    {
        String comp = component.string();
        if (!comp.empty() && comp != "/" && comp != "\\")
        {
            components.push_back(comp);
        }
    }

    return components;
}

bool ResourceManager::IsValidPath(const String& path) const
{
    if (path.empty())
    {
        return false;
    }

    try
    {
        const std::filesystem::path fsPath(path);
        return !fsPath.empty();
    }
    catch (...)
    {
        return false;
    }
}

ResourceManager::VirtualNode* ResourceManager::CreateNodePath(const String& path)
{
    const std::vector<String> components = SplitPath(path);
    VirtualNode* current = rootNode.get();

    for (const auto& component : components)
    {
        if (component.empty() || component == ".")
        {
            continue;
        }

        auto& child = current->children[component];
        if (!child)
        {
            child = std::make_unique<VirtualNode>();
        }
        current = child.get();
    }

    return current;
}
