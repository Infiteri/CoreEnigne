#pragma once

#include "Scene/Scene.h"

namespace Core
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel(Scene *scene);
        ~SceneHierarchyPanel();

        void SetContext(Scene *scene);

        void OnImGuiRender();

        void DrawNode(Entity *e);
        void DrawComponents(Entity *e);

        Scene *scene;

        Entity *selectionContext = nullptr;
    };
}