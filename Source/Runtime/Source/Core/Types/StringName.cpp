#include "StringName.h"

StringName::StringName(const std::string& s)
{
    name = s;
}

StringName::StringName(const char* s)
{
    name = s;
}
