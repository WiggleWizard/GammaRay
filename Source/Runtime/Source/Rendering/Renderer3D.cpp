#include "Renderer3D.h"

void Renderer3D::Render()
{
}

void Renderer3D::RegisterViewport(ObjectPtr<Viewport> viewport)
{
    viewports.push_back(viewport);
}
