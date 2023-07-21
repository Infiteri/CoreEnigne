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
        VertexArray *array;

        // DONE: Getters
        Transform *transform;
        Material *material;

        float width = 100;
        float height = 100;
        bool isInitialized =false;

    public:
        Sprite();
        ~Sprite();

        void Init();

        /// @brief Sets the sprites sizes. Calling this after init will cause a re-buffer. Best called before Init.
        /// @param width The sprites new width.
        /// @param height The sprites new height.
        void SetSize(float width, float height);

        void Render();

        void Update();

        inline Transform *GetTransform() { return transform; };
        inline Material *GetMaterial() { return material; };

        inline float GetWidth() { return width; };

        inline float GetHeight() { return height; };
    };

}