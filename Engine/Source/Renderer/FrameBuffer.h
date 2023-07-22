#pragma once

#include "Core/Base.h"
#include "stdint.h"

namespace Core
{

    class CE_API FrameBuffer
    {
    public:
        FrameBuffer();
        ~FrameBuffer(){};

        void Create(float width, float height);
        void Bind();
        void Unbind();
        void Resize(float width, float height);
        void Destroy();

        uint32_t id = 0;
        uint32_t colorAttachment;
        uint32_t depthAttachment;
    };

}