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
