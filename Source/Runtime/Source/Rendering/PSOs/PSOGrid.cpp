#include "PSOGrid.h"

std::vector<Dg::LayoutElement> PSOGrid::GetLayoutElements()
{
    return {
        // Position
        Dg::LayoutElement{0, 0, 3, Dg::VT_FLOAT32, false},
        // Colors
        Dg::LayoutElement{1, 0, 4, Dg::VT_FLOAT32, false}
    };
}

void PSOGrid::SetupConstantsBuffer(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice)
{
    Dg::BufferDesc constantsBufferDesc;
    constantsBufferDesc.Name = "VS constants buffer";
    constantsBufferDesc.Size = sizeof(PSOConstantsGrid);
    constantsBufferDesc.Usage = Dg::USAGE_DYNAMIC;
    constantsBufferDesc.BindFlags = Dg::BIND_UNIFORM_BUFFER;
    constantsBufferDesc.CPUAccessFlags = Dg::CPU_ACCESS_WRITE;

    renderDevice->CreateBuffer(constantsBufferDesc, nullptr, &constantsBuffer);

    pso->CreateShaderResourceBinding(&shaderBinding, true);
    auto shaderVarConstants = shaderBinding->GetVariableByName(Dg::SHADER_TYPE_VERTEX, "VSConstants");
    if (shaderVarConstants)
    {
        shaderVarConstants->Set(constantsBuffer);
    }
}

String PSOGrid::GetShaderSourceVertex()
{
    return R"(
        layout(location = 0) in vec3 inPosition;
        layout(location = 1) in vec2 inTexCoord;

        layout(location = 0) out vec2 outUV;

        layout(set = 0, binding = 0) uniform Constants {
            mat4 g_WorldViewProj;
            vec3 g_CameraPosition;
            float g_GridScale;
            vec2 g_LineWidth;
            vec4 g_LineColor;
            vec4 g_BaseColor;
            int g_UVMode; // 0: MeshUV, 1: WorldX, 2: WorldY, 3: WorldZ
        };

        void main() {
            gl_Position = g_WorldViewProj * vec4(inPosition, 1.0);
            
            if (g_UVMode == 0) { // MeshUV
                outUV = inTexCoord * g_GridScale;
            } else {
                // World space UV calculation
                vec3 worldPos = (g_WorldViewProj * vec4(inPosition, 1.0)).xyz;
                vec3 cameraCenteringOffset = floor(g_CameraPosition * g_GridScale);
                vec3 cameraSnappedWorldPos = worldPos * g_GridScale - cameraCenteringOffset;
                
                if (g_UVMode == 1) { // WorldX
                    outUV = cameraSnappedWorldPos.xy;
                } else if (g_UVMode == 2) { // WorldY
                    outUV = cameraSnappedWorldPos.xz;
                } else { // WorldZ
                    outUV = cameraSnappedWorldPos.yz;
                }
            }
        }
    )";
}

String PSOGrid::GetShaderSourcePixel()
{
    return R"(
        layout(location = 0) in vec2 inUV;

        layout(location = 0) out vec4 outColor;

        layout(set = 0, binding = 0) uniform Constants {
            mat4 g_WorldViewProj;
            vec3 g_CameraPosition;
            float g_GridScale;
            vec2 g_LineWidth;
            vec4 g_LineColor;
            vec4 g_BaseColor;
            int g_UVMode;
        };

        float PristineGrid(vec2 uv, vec2 lineWidth) {
            lineWidth = clamp(lineWidth, 0.0, 1.0);
            vec2 uvDdx = dFdx(uv);
            vec2 uvDdy = dFdy(uv);
            vec2 uvDeriv = vec2(length(vec2(uvDdx.x, uvDdy.x)), length(vec2(uvDdx.y, uvDdy.y)));
            
            bvec2 invertLine = greaterThan(lineWidth, vec2(0.5));
            vec2 targetWidth = invertLine ? 1.0 - lineWidth : lineWidth;
            vec2 drawWidth = clamp(targetWidth, uvDeriv, 0.5);
            vec2 lineAA = max(uvDeriv, 0.000001) * 1.5;
            
            vec2 gridUV = abs(fract(uv) * 2.0 - 1.0);
            gridUV = invertLine ? gridUV : 1.0 - gridUV;
            
            vec2 grid2 = smoothstep(drawWidth + lineAA, drawWidth - lineAA, gridUV);
            grid2 *= clamp(targetWidth / drawWidth, 0.0, 1.0);
            grid2 = mix(grid2, targetWidth, clamp(uvDeriv * 2.0 - 1.0, 0.0, 1.0));
            grid2 = invertLine ? 1.0 - grid2 : grid2;
            
            return mix(grid2.x, 1.0, grid2.y);
        }

        void main() {
            float grid = PristineGrid(inUV, g_LineWidth);
            
            // Linear color space mixing
            vec4 finalColor = mix(g_BaseColor, g_LineColor, grid * g_LineColor.a);
            outColor = finalColor;
        }
    )";
}
