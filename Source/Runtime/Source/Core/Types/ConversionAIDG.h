#pragma once

#include <assimp/color4.h>
#include <assimp/vector2.h>
#include <assimp/vector3.h>

Dg::float3 ConversionAIDG(const aiVector3D& in)
{
    return { in.x, in.y, in.z };   
}

Dg::float2 ConversionAIDG(const aiVector2D& in)
{
    return { in.x, in.y };   
}

Dg::float2 ConversionAIDGSwizzle(const aiVector3D& in)
{
    return { in.x, in.y };
}

Dg::float4 ConversionAIDG(const aiColor4D& in)
{
    return { in.r, in.g, in.b, in.a };
}