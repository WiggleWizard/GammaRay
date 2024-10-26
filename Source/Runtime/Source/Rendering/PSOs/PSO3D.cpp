#include "PSO3D.h"

std::vector<Dg::LayoutElement> PSO3D::GetLayoutElements()
{
    return {
        // Attribute 0 - vertex position
        Dg::LayoutElement{0, 0, 3, Dg::VT_FLOAT32, false},
        // Attribute 1 - vertex normal
        Dg::LayoutElement{1, 0, 3, Dg::VT_FLOAT32, false},
        // Attribute 2 - texture coordinates
        Dg::LayoutElement{2, 0, 2, Dg::VT_FLOAT32, false},
        // Attribute 3 - vertex colors
        Dg::LayoutElement{3, 0, 4, Dg::VT_FLOAT32, false}
    };
}

Dg::RefCntAutoPtr<Dg::IBuffer> PSO3D::GetConstantBufferVS()
{
    return constantsBufferVS;
}

String PSO3D::GetShaderSourceVertex()
{
    return R"(
        // Attributes
        layout(location = 0) in vec3 ATTRIB0_Position;
        layout(location = 1) in vec3 ATTRIB1_Normal;
        layout(location = 2) in vec2 ATTRIB2_UV;
        layout(location = 3) in vec4 ATTRIB3_Color;

        // Constant buffer
        layout(std140, binding = 0) uniform ConstantsVS
        {
            mat4 g_WorldViewProj;
            mat4 g_World;
        };

        // Outputs to fragment shader
        layout(location = 0) out vec3 out_WorldPos;
        layout(location = 1) out vec3 out_Normal;
        layout(location = 2) out vec2 out_UV;
        layout(location = 3) out vec4 out_Color;

        void main()
        {
            // Transform world position
            vec4 worldPos = g_World * vec4(ATTRIB0_Position, 1.0);
            out_WorldPos = worldPos.xyz;
            
            // Transform to clip space
            gl_Position = g_WorldViewProj * vec4(ATTRIB0_Position, 1.0);
            
            // Transform normal to world space
            out_Normal = mat3(g_World) * ATTRIB1_Normal;
            
            // Pass through texture coordinates
            out_UV = ATTRIB2_UV;

            out_Color = ATTRIB3_Color;
        }
    )";
}

String PSO3D::GetShaderSourcePixel()
{
    return R"(
        // Inputs from vertex shader
        layout(location = 0) in vec3 in_WorldPos;
        layout(location = 1) in vec3 in_Normal;
        layout(location = 2) in vec2 in_UV;
        layout(location = 3) in vec4 in_Color;

        // Output
        layout(location = 0) out vec4 out_Color;

        void main()
        {
            out_Color = in_Color;
        }
    )";
}
