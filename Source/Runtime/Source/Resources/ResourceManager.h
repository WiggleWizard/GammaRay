#pragma once

#include "Res.h"
#include "Resource.h"
#include "ResPath.h"

class Importer;
class FileIO;
class Resource;

struct FileInfo
{
    String name;
    ResPath virtualPath;
    String physicalPath;
    size_t size = 0;
    time_t lastModified = 0;
    bool isVirtual = true;

    // Optional: Resource type/extension
    String extension;
};

struct DirectoryInfo
{
    String name;
    ResPath virtualPath;
    String physicalPath;
    bool isVirtual = true;
    size_t numChildren = 0; // Number of immediate children
};

// Directory listing options
struct ListOptions
{
    bool recursive = false;
    bool includeHidden = false;
    String filterPattern; // e.g., "*.png" for PNG files
    size_t maxDepth = std::numeric_limits<size_t>::max();
};

class ResourceManager : public Object
{
public:
    ResourceManager();

    // VFS
    bool CreateVirtualDirectory(const ResPath& path);
    bool DeleteVirtualDirectory(const ResPath& path, bool recursive = false);
    bool MountPhysicalDirectory(const ResPath& virtualPath, const String& physicalPath);
    bool UnmountDirectory(const ResPath& virtualPath);

    // Resource management
    // Takes ownership of the Resource pointer
    void AddVirtualResource(const ResPath& virtualPath, Resource* res);
    void AddVirtualResource(const ResPath& virtualPath, Res<Resource> res);
    bool DeleteResource(const ResPath& virtualPath);
    Res<Resource> GetResource(const ResPath& virtualPath);
    bool ResourceExists(const ResPath& virtualPath) const;
    bool IsDirectory(const ResPath& virtualPath) const;

    // Directory listing methods
    std::vector<DirectoryInfo> ListDirectories(const ResPath& path, const ListOptions& options = {}) const;
    std::vector<FileInfo> ListFiles(const ResPath& path, const ListOptions& options = {}) const;
    
    // Combined listing method
    struct DirectoryContents {
        std::vector<DirectoryInfo> directories;
        std::vector<FileInfo> files;
        size_t totalSize = 0;
    };
    DirectoryContents ListContents(const ResPath& path, const ListOptions& options = {}) const;

    // Path operations
    String ResolvePath(const String& virtualPath) const; // Converts virtual path to physical if applicable
    String NormalizePath(const String& path) const; // Normalizes path separators and removes redundant elements

protected:
    // List of importers available for file extensions
    std::unordered_map<String, ObjectPtr<Importer>> registeredImports;
    std::unordered_map<String, ObjectPtr<FileIO>> registeredFileIO;

protected:
    struct VirtualNode
    {
        bool isDirectory = false;
        String physicalPath; // Empty if purely virtual
        Res<Resource> resource;
        std::unordered_map<String, std::unique_ptr<VirtualNode>> children;
    };

    std::unique_ptr<VirtualNode> rootNode;

    // Helper functions
    VirtualNode* FindNode(const ResPath& path) const;
    std::vector<String> SplitPath(const String& path) const;
    bool IsValidPath(const ResPath& path) const;
    VirtualNode* CreateNodePath(const ResPath& path);
    bool DeleteNodeRecursive(VirtualNode* node);

    bool MatchesPattern(const String& filename, const String& pattern) const;
    FileInfo GetFileInfo(const ResPath& virtualPath, const VirtualNode* node) const;
    DirectoryInfo GetDirectoryInfo(const ResPath& virtualPath, const VirtualNode* node) const;
    void ListContentsRecursive(const ResPath& currentPath, const VirtualNode* node, DirectoryContents& contents, const ListOptions& options, size_t currentDepth) const;
    String GetExtension(const ResPath& path) const;

    // Mount point tracking
    struct MountPoint
    {
        String virtualPath;
        String physicalPath;
    };

    std::vector<MountPoint> mountPoints;
};
