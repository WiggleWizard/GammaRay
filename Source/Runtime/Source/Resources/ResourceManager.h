#pragma once

#include "Res.h"
#include "Resource.h"

class Importer;
class FileIO;
class Resource;

class ResourceManager : public Object
{
public:
    ResourceManager();
    
    // VFS
    bool CreateVirtualDirectory(const String& path);
    bool DeleteVirtualDirectory(const String& path, bool recursive = false);
    bool MountPhysicalDirectory(const String& virtualPath, const String& physicalPath);
    bool UnmountDirectory(const String& virtualPath);

    // Resource management
    // Takes ownership of the Resource pointer
    void AddVirtualResource(const String& virtualPath, Resource* res);
    void AddVirtualResource(const String& virtualPath, Res<Resource> res);
    bool DeleteResource(const String& virtualPath);
    Res<Resource> GetResource(const String& virtualPath);
    bool ResourceExists(const String& virtualPath) const;
    bool IsDirectory(const String& virtualPath) const;

    // Path operations
    String ResolvePath(const String& virtualPath) const;  // Converts virtual path to physical if applicable
    String NormalizePath(const String& path) const;       // Normalizes path separators and removes redundant elements

protected:
    // List of importers available for file extensions
    std::unordered_map<String, ObjectPtr<Importer>> registeredImports;
    std::unordered_map<String, ObjectPtr<FileIO>> registeredFileIO;

protected:
    struct VirtualNode
    {
        bool isDirectory = false;
        String physicalPath;        // Empty if purely virtual
        Res<Resource> resource;
        std::unordered_map<String, std::unique_ptr<VirtualNode>> children;
    };
    
    std::unique_ptr<VirtualNode> rootNode;

    // Helper functions
    VirtualNode* FindNode(const String& path) const;
    std::vector<String> SplitPath(const String& path) const;
    bool IsValidPath(const String& path) const;
    VirtualNode* CreateNodePath(const String& path);
    bool DeleteNodeRecursive(VirtualNode* node);

    // Mount point tracking
    struct MountPoint
    {
        String virtualPath;
        String physicalPath;
    };
    std::vector<MountPoint> mountPoints;
};
