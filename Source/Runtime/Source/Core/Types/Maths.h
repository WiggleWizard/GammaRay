#pragma once

#include <BasicMath.hpp>

#pragma pack(push,1)

struct Vertex
{
    Dg::float3 position;
    Dg::float3 normal;
    Dg::float2 uv;
    Dg::float4 color;

    Vertex() : position(0,0,0), normal(0,0,0), uv(0,0), color(1,1,1,1) {} // Default constructor

    Vertex(const Dg::float3& pos, const Dg::float3& norm, const Dg::float2& texcoord, const Dg::float4& col)
        : position(pos)
        , normal(norm)
        , uv(texcoord)
        , color(col)
    {}
};

#pragma pack(pop)
