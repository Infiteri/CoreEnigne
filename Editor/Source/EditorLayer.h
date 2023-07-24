#pragma once

#include "Core/Layer/Layer.h"
#include "Panels/SceneHierarchyPanel.h"

namespace Core
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer(){};
        ~EditorLayer(){};

        void OnAttach();

        void OnRender();

        void OnUpdate();

        void OnImGuiRender();

        void Viewport();

        void New();
        void Open();
        void SaveAs();

        SceneHierarchyPanel *sceneHierarchyPanel;
    };
}