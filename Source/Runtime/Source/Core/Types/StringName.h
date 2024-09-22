#pragma once

#include <string>

struct StringName
{
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
    std::string name = "";
};