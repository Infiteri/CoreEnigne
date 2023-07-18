#pragma once

#include "Core/Base.h"
#include "Layer.h"

namespace Core
{
    class CE_API LayerStack
    {
    public:
        LayerStack(){};
        ~LayerStack(){};

        static void Init();
        static void Destroy();
        static void Update();
        static void Render();
        static void RenderImGui();
        static void PushLayer(Layer *layer);
        static void PopLayer(Layer *layer);
    };

}