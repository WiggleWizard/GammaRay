#pragma once

class Resource
{
public:
    virtual ~Resource() = default;
    
    virtual void Retain() {}
    virtual void Release() {}

public:
    UUID id = UUID::CreateInvalid();

    // The path to the original file that was imported
    String source = "";
};
