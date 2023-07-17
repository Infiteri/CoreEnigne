#include "Core.h"
#include "Core/Launch.h"

class Sandbox : public Core::Application
{
public:
    Sandbox(){};
    ~Sandbox(){};

    void OnPreInit(){};
};

Core::Application *Core::CreateApplication()
{
    return new Sandbox();
};