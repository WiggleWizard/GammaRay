#include "PSOGrid.h"

std::vector<Dg::LayoutElement> PSOGrid::GetLayoutElements()
{
    return Super::GetLayoutElements();
    
    // return {
    //     // Position
    //     Dg::LayoutElement{0, 0, 3, Dg::VT_FLOAT32, false},
    //     // UV Coord
    //     Dg::LayoutElement{1, 0, 4, Dg::VT_FLOAT32, false}
    // };
}

void PSOGrid::ModifyPSOCreationInfo(Dg::GraphicsPipelineStateCreateInfo& creationInfo)
{
    PSO3D::ModifyPSOCreationInfo(creationInfo);

    creationInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendEnable = true;
    creationInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlend = Dg::BLEND_FACTOR_SRC_ALPHA;
    creationInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlend = Dg::BLEND_FACTOR_INV_SRC_ALPHA;
    creationInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendOp = Dg::BLEND_OPERATION_ADD;
    creationInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlendAlpha = Dg::BLEND_FACTOR_ONE;
    creationInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlendAlpha = Dg::BLEND_FACTOR_INV_SRC_ALPHA;
    creationInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendOpAlpha = Dg::BLEND_OPERATION_ADD;
}

// Vertex Shader
String PSOGrid::GetShaderSourceVertex()
{
    return R"(
        // Attributes
        layout(location = 0) in vec3 ATTRIB0_Position;

        // Constant buffer
        layout(std140, binding = 0) uniform ConstantsVS
        {
            mat4 g_WorldViewProj;
            mat4 g_World;
            vec3 g_CameraPosition;
        };

        // Outputs to fragment shader
        layout(location = 0) out vec3 out_CameraPos;
        layout(location = 1) out vec2 out_Coords;

        // Constants
        const float GRID_SIZE = 100.0;

        void main()
        {
            // Create grid quad centered at camera
            vec4 worldPos = vec4(ATTRIB0_Position, 1.0);
            worldPos.xyz *= GRID_SIZE;
            worldPos.xz += g_CameraPosition.xz; // Make the quad follow the camera
            
            gl_Position = g_WorldViewProj * worldPos;
            out_CameraPos = g_CameraPosition;
            out_Coords = worldPos.xz;
        }
    )";
}

// Pixel Shader
String PSOGrid::GetShaderSourcePixel()
{
    return R"(
        // Inputs from vertex shader
        layout(location = 0) in vec3 in_CameraPos;
        layout(location = 1) in vec2 in_Coords;

        // Output
        layout(location = 0) out vec4 out_Color;

        // Grid constants
        const float GRID_SIZE = 100.0;
        const float CELL_SIZE = 1.0;
        const float HALF_CELL_SIZE = CELL_SIZE * 0.5;
        const float CELL_LINE_THICKNESS = 0.01;
        const float SUBCELL_SIZE = 0.1;
        const float HALF_SUBCELL_SIZE = SUBCELL_SIZE * 0.5;
        const float SUBCELL_LINE_THICKNESS = 0.001;
        const vec4 CELL_COLOR = vec4(0.75, 0.75, 0.75, 0.5);
        const vec4 SUBCELL_COLOR = vec4(0.5, 0.5, 0.5, 0.5);
        const float HEIGHT_TO_FADE_DISTANCE_RATIO = 25.0;
        const float MIN_FADE_DISTANCE = GRID_SIZE * 0.05;
        const float MAX_FADE_DISTANCE = GRID_SIZE * 0.5;

        void main()
        {
            // Calculate cell coordinates
            vec2 cellCoords = mod(in_Coords + HALF_CELL_SIZE, CELL_SIZE);
            vec2 subcellCoords = mod(in_Coords + HALF_SUBCELL_SIZE, SUBCELL_SIZE);
            
            // Calculate distances to cell edges
            vec2 distanceToCell = abs(cellCoords - HALF_CELL_SIZE);
            vec2 distanceToSubcell = abs(subcellCoords - HALF_SUBCELL_SIZE);
            
            // Calculate line thickness adjustment based on distance
            vec2 derivatives = fwidth(in_Coords);
            float adjustedCellLineThickness = 0.5 * (CELL_LINE_THICKNESS + length(derivatives));
            float adjustedSubcellLineThickness = 0.5 * (SUBCELL_LINE_THICKNESS + length(derivatives));
            
            // Determine grid color
            vec4 color = vec4(0.0);
            if (any(lessThan(distanceToSubcell, vec2(adjustedSubcellLineThickness))))
            {
                color = SUBCELL_COLOR;
            }
            if (any(lessThan(distanceToCell, vec2(adjustedCellLineThickness))))
            {
                color = CELL_COLOR;
            }
            
            // Calculate opacity falloff
            float distanceToCamera = length(in_Coords - in_CameraPos.xz);
            float fadeDistance = abs(in_CameraPos.y) * HEIGHT_TO_FADE_DISTANCE_RATIO;
            fadeDistance = clamp(fadeDistance, MIN_FADE_DISTANCE, MAX_FADE_DISTANCE);
            float opacityFalloff = smoothstep(1.0, 0.0, distanceToCamera / fadeDistance);
            
            out_Color = color * opacityFalloff;
        }
    )";
}
