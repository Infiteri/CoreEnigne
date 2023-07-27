#include "SceneHierarchyPanel.h"
#include "Core/Logger.h"
#include "Utils/Utils.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace Core
{
    template <typename T, typename UIFun>
    void DrawUI(const std::string &name, Entity *ent, UIFun fun)
    {
        const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_DefaultOpen;

        if (ent->HasComponent<T>())
        {
            auto comp = ent->GetComponent<T>();
            bool remove = false;

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {4, 4});
            bool open = ImGui::TreeNodeEx((void *)typeid(T).hash_code(), flags, name.c_str());

            ImGui::SameLine(ImGui::GetWindowWidth() - 50.0f);

            if (ImGui::Button("+"))
                ImGui::OpenPopup("ComponentSettings");

            if (ImGui::BeginPopup("ComponentSettings"))
            {
                if (ImGui::MenuItem("Remove"))
                {
                    remove = true;
                }

                ImGui::EndPopup();
            }

            ImGui::PopStyleVar();

            if (open)
            {
                fun(comp);
                ImGui::TreePop();
            }

            if (remove)
            {
                ent->RemoveComponent<T>();
            }
        }
    }

    void SetupImGuiDrag3(const char *title, Core::Vector3 *vec, Core::Vector3 *out)
    {
        ImGui::PushID(title);

        ImGui::Columns(2);

        ImGui::SetColumnWidth(0, 100.0f);
        ImGui::Text(title);
        ImGui::NextColumn();
        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        float lineH = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = {lineH + 3.0f, lineH};

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        if (ImGui::Button("X", buttonSize))
        {
            out->x = 0.0f;
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##x", &out->x, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        if (ImGui::Button("Y", buttonSize))
        {
            out->y = 0.0f;
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##y", &out->y, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
        if (ImGui::Button("Z", buttonSize))
        {
            out->z = 0.0f;
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##z", &out->z, 0.1f);
        ImGui::PopItemWidth();
        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();
    }

    SceneHierarchyPanel::SceneHierarchyPanel(Scene *scene)
    {
        SetContext(scene);
    }

    SceneHierarchyPanel::~SceneHierarchyPanel()
    {
    }

    void SceneHierarchyPanel::SetContext(Scene *scene)
    {
        this->scene = scene;
        selectionContext = nullptr;
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");

        for (Entity *ent : scene->GetAllEntities())
        {
            DrawNode(ent);
        }

        if (ImGui::BeginPopupContextWindow(0, 1))
        {
            if (ImGui::MenuItem("Create Entity"))
            {
                scene->AddEntity(new Entity("Empty Entity"));
            }

            ImGui::EndPopup();
        }
        ImGui::End();

        ImGui::Begin("Proprieties");

        if (selectionContext)
        {
            DrawComponents(selectionContext);

            if (ImGui::Button("Add Component "))
                ImGui::OpenPopup("AddComponent");

            if (ImGui::BeginPopup("AddComponent"))
            {
                if (ImGui::MenuItem("Transform"))
                {
                    selectionContext->AddComponent<TransformComponent>();
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Sprite"))
                {
                    selectionContext->AddComponent<SpriteComponent>();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::MenuItem("Camera"))
                {
                    selectionContext->AddComponent<CameraComponent>();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::MenuItem("Script"))
                {
                    selectionContext->AddComponent<ScriptComponent>();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::MenuItem("Particle Emitter"))
                {
                    selectionContext->AddComponent<ParticleEmitterComponent>();
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
        }

        ImGui::End();
    }

    void SceneHierarchyPanel::DrawNode(Entity *e)
    {
        ImGuiTreeNodeFlags flags = ((selectionContext != nullptr && selectionContext->GetID()) == e->GetID() ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;

        bool open = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)e->GetID(), flags, e->GetName().c_str());
        bool removed = false;

        if (ImGui::IsItemClicked(0))
        {
            selectionContext = e;
        }

        if (open)
            ImGui::TreePop();
    }

    void SceneHierarchyPanel::DrawComponents(Entity *e)
    {
        // Draw display name
        static char nameBuffer[256];
        memset(nameBuffer, 0, sizeof(nameBuffer));
        strcat_s(nameBuffer, e->GetName().c_str());

        if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer)))
            e->SetName(nameBuffer);

        DrawUI<TransformComponent>("Transform", e, [](TransformComponent *c)
                                   {
            SetupImGuiDrag3("Position", &c->transform.position, &c->transform.position);
            SetupImGuiDrag3("Rotation", &c->transform.rotation, &c->transform.rotation);
            SetupImGuiDrag3("Scale", &c->transform.scale, &c->transform.scale); });

        DrawUI<SpriteComponent>("Sprite", e, [](SpriteComponent *c)
                                {
                                    // Sprite
                                    Color *col = c->sprite.GetMaterial()->GetColor();
                                    float color[4] = {
                                        col->GetRNormalized(),
                                        col->GetGNormalized(),
                                        col->GetBNormalized(),
                                        col->GetANormalized(),
                                    };

                                    if (ImGui::ColorEdit4("Color", color, ImGuiColorEditFlags_NoInputs))
                                    {
                                        col->r = color[0] * 255;
                                        col->g = color[1] * 255;
                                        col->b = color[2] * 255;
                                        col->a = color[3] * 255;
                                    }
                                    float spriteWidth = c->sprite.GetWidth();
                                    float spriteHeight = c->sprite.GetHeight();
                                    float spriteSizes[2] = {spriteWidth, spriteHeight};

                                    if (ImGui::DragFloat2("Size", spriteSizes, 1.0f))
                                    {
                                        c->sprite.SetSize(spriteSizes[0], spriteSizes[1]);
                                    }
                                    
                                    ImGui::Button("Texture");

                                    if(ImGui::BeginDragDropTarget()) {
                                        if(const ImGuiPayload* payload= ImGui::AcceptDragDropPayload("CONTENT_PAYLOAD")) {
                                            const char* path = (const char*)payload->Data;

                                        if(Utils::FileHasExtension(path, "png") || Utils::FileHasExtension(path, "jfif") || Utils::FileHasExtension(path, "jpeg") || Utils::FileHasExtension(path, "jpg")) {
                                            c->sprite.GetMaterial()->GetTexture()->FromPath(path );
                                        }
                                    }
                                        
                                        ImGui::EndDragDropTarget();
                                    } });

        DrawUI<CameraComponent>("Camera", e, [](CameraComponent *c)
                                {
                                    // Camera
                                    float zoomLevel = c->camera.GetZoom();

                                    if(ImGui::DragFloat("Zoom", &zoomLevel, 0.025f, 0.1f)) {
                                        c->camera.SetZoom(zoomLevel);
                                        c->camera.UpdateProjection();
                                    } 
                                    
                                    float camPos[2] = {c->camera.GetPosition()->x, c->camera.GetPosition()->y};

                                    if (ImGui::DragFloat2("Camera position", camPos))
                                    {
                                        c->camera.GetPosition()->x = camPos[0];
                                        c->camera.GetPosition()->y = camPos[1];
                                        c->camera.UpdateView();
                                    } });

        DrawUI<ScriptComponent>("Script", e, [](ScriptComponent *c) { // Draw display name
            static char classNameBuffer[256];
            memset(classNameBuffer, 0, sizeof(classNameBuffer));
            strcat_s(classNameBuffer, c->className.c_str());

            if (ImGui::InputText("Class Name", classNameBuffer, sizeof(classNameBuffer)))
                c->className = std::string(classNameBuffer);
        });

        DrawUI<ParticleEmitterComponent>("Particle Emitter", e, [](ParticleEmitterComponent *c)
                                         {
                                             ImGui::DragFloat("Amount", &c->amountPerFrame);

                                             // todo: Velocity distribution, size down-scaling
                                         });
    }
}