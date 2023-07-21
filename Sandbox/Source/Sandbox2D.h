#pragma once

#include "Core.h"
#include "imgui.h"


class Sandbox2D : public Core::Layer
{
public:
    Sandbox2D(){};
    ~Sandbox2D(){};

    void OnAttach();

    void OnRender();
    
    void OnImGuiRender();
};
