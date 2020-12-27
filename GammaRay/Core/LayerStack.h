#pragma once

#include "Layer.h"

#include <vector>


class LayerStack
{
public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlayLayer);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* overlayLayer);

    std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
    std::vector<Layer*>::iterator end() { return m_layers.end(); }

private:
    std::vector<Layer*> m_layers;
    std::vector<Layer*>::iterator m_itLayerInsert;
};

