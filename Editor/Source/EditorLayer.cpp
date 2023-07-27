#include "EditorLayer.h"

#include "imgui.h"
#include "ImGuizmo.h"

#include "Utils/Utils.h"

#include "Core/Input.h"
#include "Core/Logger.h"
#include "Core/ImGuiAbstraction.h"

#include "Platform/Platform.h"

#include "Math/Math.h"

#include "Renderer/Renderer.h"
#include "Renderer/Particle/ParticleSystem.h"
#include "Renderer/OrthoMovement.h"
#include "Renderer/Objects/Sprite.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"
#include "Scene/SceneSerializer.h"

namespace Core
{
    bool isInViewportMouse;
    bool cameraA = false;
    static ImGuizmo::OPERATION operation = ImGuizmo::OPERATION::TRANSLATE;

    std::string currentScenePath = "";

    Scene *activeScene;
    Scene *editorScene;

    ImVec2 lastViewport;
    ImVec2 viewportBounds[2];

    OrthoMovement *movement;
    OrthographicCamera *editorCamera;

    Texture *playButton;
    Texture *stopButton;

    void EditorLayer::OnAttach()
    {
        editorCamera = new OrthographicCamera(Engine::Get()->GetWindow()->GetWidth(), Engine::Get()->GetWindow()->GetHeight(), -1.0, 1.0);
        movement = new OrthoMovement(editorCamera, 10.0f);
        Renderer::SetCurrentCamera(editorCamera);

        // Load textures
        playButton = new Texture();
        playButton->FromPath("EngineResources/Images/PlayButton.png");

        stopButton = new Texture();
        stopButton->FromPath("EngineResources/Images/StopButton.png");

        editorScene = new Scene();

        activeScene = editorScene;
        activeScene->Init();
        activeScene->Start();

        sceneHierarchyPanel = new SceneHierarchyPanel(activeScene);
        contentBrowserPanel = new ContentBrowserPanel();
    }

    void EditorLayer::OnRender()
    {
        activeScene->Render();
    }

    void EditorLayer::OnUpdate()
    {
        switch (sceneState)
        {
        case SceneState::Edit:
            OnEditorUpdate();
            break;
        case SceneState::Play:
            OnRuntimeUpdate();
            break;
        }

        // if (mouseX > 0 && mouseY > 0 && mouseX <= (int)viewportSize.x && mouseY <= (int)viewportSize.y)
        // {
        //     uint32_t data = Renderer::GetFrameBuffer()->ReadPixel(1, mouseX, mouseY);
        //     CE_INFO("Data: %i", data);
        // }
    }

    void EditorLayer::OnImGuiRender()
    {
        ImGuiAbstraction::SetupDockSpace();

        sceneHierarchyPanel->OnImGuiRender();
        contentBrowserPanel->OnImGuiRender();

        Viewport();

        RenderPlayStop();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::MenuItem("File"))
            {
                ImGui::OpenPopup("FilePopup");
            }

            if (ImGui::BeginPopup("FilePopup"))
            {
                if (ImGui::MenuItem("New", "Ctrl+N"))
                    New();

                if (ImGui::MenuItem("Open...", "Ctrl+O"))
                    Open();

                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                    SaveAs();

                ImGui::EndPopup();
            }

            ImGui::EndMainMenuBar();
        }

        ImGui::End();
    }

    void EditorLayer::Viewport()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::Begin("Viewport");

        auto viewportOffset = ImGui::GetCursorPos();

        ImGui::PopStyleVar();

        ImVec2 viewport = ImGui::GetContentRegionAvail();
        ImVec2 mouse = ImGui::GetMousePos();

        if (lastViewport.x != viewport.x || lastViewport.y != viewport.y)
        {
            lastViewport = viewport;
            Renderer::Viewport(viewport.x, viewport.y);
        }

        Renderer::GetFrameBuffer()->UseColorAttachment(0);
        ImGui::Image((void *)(uint64_t)(uint32_t)Renderer::GetFrameBuffer()->colorAttachmentsID[0], {viewport.x, viewport.y}, {0, 1}, {1, 0});

        auto windowSize = ImGui::GetWindowSize();
        auto minBounds = ImGui::GetWindowPos();

        ImVec2 maxBounds = {minBounds.x + windowSize.x, minBounds.y + windowSize.y};
        viewportBounds[0] = {minBounds.x, minBounds.y};
        viewportBounds[1] = {maxBounds.x, maxBounds.y};

        if (ImGui::BeginDragDropTarget())
        {
            const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("CONTENT_PAYLOAD");

            if (payload)
            {
                const char *value = (const char *)payload->Data;

                if (Utils::GetFileExtension(value) != "")
                {
                    // 0 when comparing means the same
                    if (Utils::FileHasExtension(value, "ce_scene"))
                    {
                        OpenScene(value);
                    }
                }
            }

            ImGui::EndDragDropTarget();
        }

        // ImGuizmo
        Entity *entityContext = sceneHierarchyPanel->selectionContext;
        OrthographicCamera *camera = Renderer::GetCurrentCamera();

        if (entityContext != nullptr && camera != nullptr && entityContext->HasComponent<TransformComponent>())
        {
            auto tc = entityContext->GetComponent<TransformComponent>();
            auto data = tc->transform.GetTransformMatrix()->data;

            ImGuizmo::SetOrthographic(true);
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

            ImGuizmo::Manipulate(camera->GetInvertedView()->data, camera->GetProjection()->data, operation, ImGuizmo::LOCAL, data);

            if (ImGuizmo::IsUsing())
            {

                switch (operation)
                {
                case ImGuizmo::OPERATION::TRANSLATE:
                    Math::DecomposePosition(data, &tc->transform.position);
                    break;

                case ImGuizmo::OPERATION::ROTATE:
                    Math::DecomposeRotation(data, &tc->transform.rotation);
                    break;

                case ImGuizmo::OPERATION::SCALE:
                    Math::DecomposeScale(data, &tc->transform.scale, tc->transform.rotation.z);
                    break;

                default:
                    // TODO: Warn maybe?
                    break;
                }
            }
        }

        ImGui::End();

        movement->Update();
    }

    void EditorLayer::New()
    {
        activeScene = new Scene();
    }

    void EditorLayer::Open()
    {
        std::string path = Platform::OpenFile("Core Scene (*.ce_scene)\0*.ce_scene\0");

        OpenScene(path);
    }

    void EditorLayer::SaveAs()
    {
        std::string path = Platform::SaveFile("Core Scene (*.ce_scene)\0*.ce_scene\0");

        if (!path.empty())
        {

            SceneSerializer ser(activeScene);
            ser.Serialize(path);

            sceneHierarchyPanel->SetContext(activeScene);
        }
    }

    void EditorLayer::RenderPlayStop()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::Begin("##playStop_bar", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoDecoration);

        float size = 10.0f;

        ImGui::SameLine((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
        if (ImGui::ImageButton((void *)(uintptr_t)(sceneState == SceneState::Edit ? playButton->GetID() : stopButton->GetID()), {size, size}))
        {
            if (sceneState == SceneState::Edit)
                OnScenePlay();
            else if (sceneState == SceneState::Play)
                OnSceneStop();
        }

        ImGui::End();
        ImGui::PopStyleVar();
    }

    void EditorLayer::OpenScene(const std::string &path)
    {
        if (!path.empty())
        {
            if (currentScenePath.compare(path) == 0)
                return;

            activeScene->Stop();
            activeScene->Destroy();

            editorScene = new Scene();

            activeScene = editorScene;
            activeScene->Init();
            activeScene->Start();

            SceneSerializer ser(activeScene);
            ser.Deserialize(path);
            sceneHierarchyPanel->SetContext(activeScene);

            currentScenePath = path;
        }
    }

    void EditorLayer::OnScenePlay()
    {
        sceneState = SceneState::Play;

        activeScene = Scene::Copy(editorScene);
        activeScene->Init();
        activeScene->Start();
        activeScene->OnRuntimeStart();

        sceneHierarchyPanel->SetContext(activeScene);
    }

    void EditorLayer::OnSceneStop()
    {
        sceneState = SceneState::Edit;

        activeScene = editorScene;
        activeScene->OnRuntimeStop();

        Renderer::SetCurrentCamera(editorCamera);

        sceneHierarchyPanel->SetContext(activeScene);
    }

    void EditorLayer::OnEditorUpdate()
    {

        if (Input::GetKey(InputKey::Delete))
        {
            Entity *selection = sceneHierarchyPanel->selectionContext;

            if (selection != nullptr)
            {
                activeScene->RemoveEntityByName(selection->GetName());
                sceneHierarchyPanel->selectionContext = nullptr;
            }
        }

        // KEY_BINDS
        bool ctrl = Input::GetKey(InputKey::LeftControl);
        bool shift = Input::GetKey(InputKey::LeftShift);

        if (Input::GetKey(InputKey::N))
        {
            if (ctrl)
                New();
        }

        if (Input::GetKey(InputKey::O))
        {
            if (ctrl)
                Open();
        }

        if (Input::GetKey(InputKey::S))
        {
            if (ctrl && shift)
                SaveAs();
        }

        if (Input::GetKey(InputKey::T))
        {
            operation = ImGuizmo::OPERATION::TRANSLATE;
        }

        if (Input::GetKey(InputKey::R))
        {
            operation = ImGuizmo::OPERATION::ROTATE;
        }

        if (Input::GetKey(InputKey::E))
        {
            operation = ImGuizmo::OPERATION::SCALE;
        }

        auto mp = ImGui::GetMousePos();
        mp.x -= viewportBounds[0].x;
        mp.y -= viewportBounds[0].y;

        ImVec2 viewportSize = {viewportBounds[1].x - viewportBounds[0].x, viewportBounds[1].y - viewportBounds[0].y};

        mp.y = viewportSize.y = mp.y;

        int mouseX = (int)mp.x;
        int mouseY = (int)mp.y;
    }

    void EditorLayer::OnRuntimeUpdate()
    {
        activeScene->Update();
    }
}