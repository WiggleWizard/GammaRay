#pragma

#include "Core/Event/Event.h"

#include <string>


class Layer
{
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnProcess() {}
    virtual void OnEvent(Event& event) {}

    inline const std::string& GetName() const { return m_layerName; }

protected:
    std::string m_layerName;
};
