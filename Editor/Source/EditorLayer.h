#pragma once

#include "Core/Layer/Layer.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"

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

        void RenderPlayStop();

        SceneHierarchyPanel *sceneHierarchyPanel;
        ContentBrowserPanel *contentBrowserPanel;

        void OpenScene(const std::string &path);

        // Internal state
        enum class SceneState
        {
            Edit = 0,
            Play = 1
        };

        SceneState sceneState = SceneState::Edit;

        void OnScenePlay();
        void OnSceneStop();

        void OnEditorUpdate();
        void OnRuntimeUpdate();
    };
}