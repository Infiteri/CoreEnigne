#include "Core/Launch.h"
#include "Core/Application.h"
#include "Core/Layer/LayerStack.h"
#include "Renderer/Renderer.h"

#include "EditorLayer.h"

namespace Core
{

    class Editor : public Application
    {
    public:
        Editor(){};
        ~Editor(){};

        void OnPreInit()
        {

            this->p_Configuration.StartMaximized = true;
            this->p_Configuration.title = "Core Editor";
        };

        void OnInit()
        {
            Renderer::SetClearColor(0.0, 0, 0, 1);

            LayerStack::PushLayer(new EditorLayer());
        }
    };

    Application *CreateApplication()
    {
        return new Editor();
    };
}