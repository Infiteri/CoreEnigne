#pragma once

#include "Core/Base.h"

namespace Core
{
    class CE_API Layer
    {
    protected:
        const char *name;

    public:
        Layer(const char *name = "Layer");
        ~Layer();

        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnUpdate();
        virtual void OnRender();
        virtual void OnImGuiRender();
    };
}