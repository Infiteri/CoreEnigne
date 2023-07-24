#pragma once

#include "Core/Base.h"
#include "scene/Scene.h"

namespace Core
{
    class CE_API SceneSerializer
    {
    public:
        SceneSerializer(Scene* scene);
        ~SceneSerializer();

        void Serialize(const std::string &path);
        void Deserialize(const std::string &path);

        Scene* scene;
    };
}
