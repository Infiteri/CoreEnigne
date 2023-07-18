#include "Layer.h"

namespace Core
{
    Layer::Layer(const char *name)
    {
        this->name = name;
    }

    Layer::~Layer()
    {
    }

    void Layer::OnAttach()
    {
    }

    void Layer::OnDetach()
    {
    }

    void Layer::OnUpdate()
    {
    }

    void Layer::OnRender()
    {
    }

    void Layer::OnImGuiRender()
    {
    }
}
