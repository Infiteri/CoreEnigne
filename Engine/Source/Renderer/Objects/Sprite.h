#pragma once

#include "Core/Base.h"

#include "Math/Transform.h"

#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Material.h"
#include "Renderer/Texture.h"

namespace Core
{
    class CE_API Sprite
    {
    private:
        // DONE: Getters
        VertexArray *array;
        Transform *transform;
        Material *material;

    public:
        Texture* texture;
        Sprite();
        ~Sprite();

        void Init();

        void Render();

        void Update();

        inline Transform *GetTransform() { return transform; };
        inline Material *GetMaterial() { return material; };
    };

}