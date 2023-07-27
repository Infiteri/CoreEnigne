#pragma once

#include "Core/Base.h"
#include "stdint.h"
#include "vector"
#include "initializer_list"

namespace Core
{

    enum class FrameBufferTextureFiltering
    {
        Rgba8,
        RedInteger,
        Depth24Stencil8
    };

    struct FrameBufferTextureSpecification
    {
        FrameBufferTextureSpecification(){};
        FrameBufferTextureSpecification(FrameBufferTextureFiltering filter) : Filtering(filter){};

        FrameBufferTextureFiltering Filtering;
    };

    struct FrameBufferAttachmentSpecification
    {
        FrameBufferAttachmentSpecification(){};
        FrameBufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification> attachments) : Attachments(attachments){};

        std::vector<FrameBufferTextureSpecification> Attachments;
    };

    struct FrameBufferSpecification
    {
        float Width;
        float Height;

        FrameBufferAttachmentSpecification Attachment;
    };

    class CE_API FrameBuffer
    {
    public:
        FrameBuffer(FrameBufferSpecification spec);
        ~FrameBuffer(){};

        void Create(FrameBufferSpecification spec);
        void Bind();
        void Unbind();
        void Resize(float width, float height);
        void Destroy();

        uint32_t id = 0;

        FrameBufferSpecification specification;

        std::vector<FrameBufferTextureSpecification> colorSpecifications;
        FrameBufferTextureSpecification depthSpecification;

        std::vector<uint32_t> colorAttachmentsID;
        uint32_t depthAttachmentID;

        void UseColorAttachment(int i);

        uint32_t ReadPixel(uint32_t attachment, int x, int y);
    };
}