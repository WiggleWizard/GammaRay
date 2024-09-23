#pragma once

#include <string>

struct StringName
{
    friend struct std::hash<StringName>;
    
    StringName(const std::string& s);
    StringName(const char* s);
    
    friend bool operator==(const StringName& lhs, const StringName& rhs)
    {
        return lhs.name == rhs.name;
    }

    friend bool operator!=(const StringName& lhs, const StringName& rhs)
    {
        return !(lhs == rhs);
    }

private:
    std::string name;
};

// Implementation for hash maps (currently only supports std::unordered_map)
template <>
struct std::hash<StringName>
{
    std::size_t operator()(const StringName& k) const
    {
        using std::size_t;
        using std::hash;
        using std::string;

        return hash<string>()(k.name);
    }
};