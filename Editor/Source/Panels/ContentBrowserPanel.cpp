#include "ContentBrowserPanel.h"

#include "Platform/Platform.h"
#include "Renderer/Texture.h"
#include "Utils/Utils.h"

namespace Core
{
    static bool firstRender = true;
    static bool pressedFolder = false;

    static std::string assetsPath = "Assets";
    static std::string currentDir = assetsPath;

    Texture *iconTexture;
    Texture *folderTexture;

    void ContentBrowserPanel::OnImGuiRender()
    {
        if (firstRender)
        {
            // Add first iteration loop
            iconTexture = new Texture();
            iconTexture->FromPath("EngineResources/Images/icon.png");

            folderTexture = new Texture();
            folderTexture->FromPath("EngineResources/Images/folder.png");

            firstRender = false;
            return;
        }

        ImGui::Begin("Content Browser");

        static float padding = 16.0f;
        static float thumbnailSize = 64.0f;
        float cellSize = thumbnailSize + padding;

        float panelWidth = ImGui::GetContentRegionAvail().x;
        int columnCount = (int)(panelWidth / cellSize);
        if (columnCount < 1)
            columnCount = 1;

        ImVec2 size{thumbnailSize, thumbnailSize}; // Might change based on preferences

        ImGui::Columns(columnCount, 0, false);

        if (currentDir != "Assets")
        {
            if (ImGui::Button("<-"))
            {
                currentDir = "Assets"; // Go Back
            }
        }

        int it = 0;

        for (auto entry : Platform::GetDirectoryEntries(currentDir))
        {
            it++; // Index

            ImGui::PushID(it++);

            Texture *texture = entry.directory ? folderTexture : iconTexture;
            ImGui::ImageButton((void *)(uint64_t)(uint32_t)texture->GetID(), size);

            if (ImGui::BeginDragDropSource())
            {
                ImGui::SetDragDropPayload("CONTENT_PAYLOAD", entry.path.c_str(), strlen(entry.path.c_str()) + 1);

                ImGui::EndDragDropSource();
            }

            if (ImGui::IsItemHovered(0) && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                if (entry.directory)
                {
                    if (!pressedFolder)
                    {
                        pressedFolder = true;
                        currentDir += "/" + entry.path;
                    }
                    else
                    {
                        pressedFolder = false;
                    }
                }
            }

            if (!entry.directory)
            {
                ImGui::TextWrapped(Utils::GetFileNameNoExtension(entry.path).c_str());
            }
            else
            {
                ImGui::TextWrapped(entry.path.c_str());
            }

            ImGui::NextColumn();

            ImGui::PopID();
        }

        ImGui::Columns(1);

        ImGui::End();
    }
}