#include "EditorLayer.h"
#include "imgui.h"
#include "Core/Logger.h"
#include "Renderer/Renderer.h"
#include "Renderer/OrthoMovement.h"
#include "Renderer/Objects/Sprite.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"
#include "Core/Input.h"

namespace Core
{
    ImVec2 lastViewport;
    bool isInViewportMouse;
    OrthoMovement *movement;
    Scene *activeScene;
    bool cameraA = false;

    void EditorLayer::OnAttach()
    {
        movement = new OrthoMovement(Renderer::GetCurrentCamera(), 10.0f);

        activeScene = new Scene();
        activeScene->Init();
        activeScene->Start();

        // Add entities
        Entity *entity = new Entity();
        entity->AddComponent<TransformComponent>();
        entity->AddComponent<SpriteComponent>();
        activeScene->AddEntity(entity);

        Entity *cameraEntity = new Entity("Camera Entity");
        cameraEntity->AddComponent<CameraComponent>();
        activeScene->AddEntity(cameraEntity);

        sceneHierarchyPanel = new SceneHierarchyPanel(activeScene);
    }

    void EditorLayer::OnRender()
    {
        activeScene->Render();
    }

    void EditorLayer::OnUpdate()
    {
        activeScene->Update();

        if (Input::GetKey(InputKey::Delete))
        {
            Entity *selection = sceneHierarchyPanel->selectionContext;

            if (selection != nullptr)
            {
                activeScene->RemoveEntityByName(selection->GetName());
                sceneHierarchyPanel->selectionContext = nullptr;
            }
        }
    }

    void EditorLayer::OnImGuiRender()
    {
        static bool dockingEnabled = true;
        if (dockingEnabled)
        {
            static bool dockspaceOpen = true;
            static bool opt_fullscreen_persistant = true;
            bool opt_fullscreen = opt_fullscreen_persistant;
            static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            if (opt_fullscreen)
            {
                ImGuiViewport *viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->Pos);
                ImGui::SetNextWindowSize(viewport->Size);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }

            if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                window_flags |= ImGuiWindowFlags_NoBackground;

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
            ImGui::PopStyleVar();

            if (opt_fullscreen)
                ImGui::PopStyleVar(2);

            // DockSpace
            ImGuiIO &io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }

            sceneHierarchyPanel->OnImGuiRender();
            Viewport();

            ImGui::End();
        }
    }

    void EditorLayer::Viewport()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::Begin("Viewport");
        ImGui::PopStyleVar();

        ImVec2 viewport = ImGui::GetContentRegionAvail();
        ImVec2 mouse = ImGui::GetMousePos();

        if (lastViewport.x != viewport.x || lastViewport.y != viewport.y)
        {
            lastViewport = viewport;
            Renderer::Viewport(viewport.x, viewport.y);
        }

        ImGui::Image((ImTextureID)(unsigned int)Renderer::GetFrameBuffer()->colorAttachment, {viewport.x, viewport.y}, {0, 1}, {1, 0});
        ImGui::End();

        movement->Update();

        // TODO: Props panel
        ImGui::Begin("Debug");
        Entity *cameraEntity = activeScene->GetEntityByName("Camera Entity");

        if (ImGui::Checkbox("Camera A", &cameraA))
        {
            if (cameraA)
            {

                if (cameraEntity != nullptr)
                {
                    CameraComponent *cam = cameraEntity->GetComponent<CameraComponent>();

                    if (cam != nullptr)
                    {
                        Renderer::SetCurrentCamera(&cam->camera);
                        Renderer::Viewport(lastViewport.x, lastViewport.y);
                    }
                }
            }
            else
            {
                Renderer::SetCurrentCameraDefault();
            }
        }
        ImGui::End();
    }
}