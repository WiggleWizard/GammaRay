#pragma once

#include "Core/Memory/Archive.h"

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

    void Serialize(Archive& ar)
    {
        ar << position.x;
        ar << position.y;
        ar << position.z;

        ar << normal.x;
        ar << normal.y;
        ar << normal.z;

        ar << uv.u;
        ar << uv.v;

        ar << color.r;
        ar << color.g;
        ar << color.b;
        ar << color.a;
    }
};

#pragma pack(pop)

template<class T>
static Dg::Vector3<T> GetForwardVector(Dg::Matrix4x4<T> m)
{
    Dg::Vector3<T> result = { m._31, m._32, m._33 };
    result = Dg::normalize(result);
    return result;
}

template<class T>
static Dg::Vector3<T> GetRightVector(Dg::Matrix4x4<T> m)
{
    Dg::Vector3<T> result = { m._11, m._12, m._13 };
    result = Dg::normalize(result);
    return result;
}

template<class T>
static Dg::Vector3<T> GetPositionFromMatrix(const Dg::Matrix4x4<T> mat)
{
    return Dg::Vector3<T>(mat._41, mat._42, mat._43);
}