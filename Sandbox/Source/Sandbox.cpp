#include "Core.h"
#include "Core/Launch.h"
#include "Sandbox2D.h"

class Sandbox : public Core::Application
{
public:
    Sandbox(){};
    ~Sandbox(){};

    void OnPreInit()
    {
        this->p_Configuration.StartMaximized = true;
        this->p_Configuration.title = "Game";
    };

    void OnInit()
    {
        Core::LayerStack::PushLayer(new Sandbox2D());
    }
};

Core::Application *Core::CreateApplication()
{
    return new Sandbox();
};