#include "grpch.h"
#include "LayerStack.h"

#include "Layer.h"


LayerStack::LayerStack()
{
    m_itLayerInsert = begin();
}

LayerStack::~LayerStack()
{
    for(Layer* layer : m_layers)
        delete layer;
}

void LayerStack::PushLayer(Layer* layer)
{
    m_itLayerInsert = m_layers.emplace(m_itLayerInsert, layer);
    layer->OnAttach();
}

void LayerStack::PushOverlay(Layer* overlayLayer)
{
    m_layers.emplace_back(overlayLayer);
}

void LayerStack::PopLayer(Layer* layer)
{
    auto it = std::find(begin(), end(), layer);
    if(it != end())
    {
        m_layers.erase(it);
        m_itLayerInsert--;
    }
}

void LayerStack::PopOverlay(Layer* overlayLayer)
{
    auto it = std::find(begin(), end(), overlayLayer);
    if(it != end())
    {
        m_layers.erase(it);
    }
}
