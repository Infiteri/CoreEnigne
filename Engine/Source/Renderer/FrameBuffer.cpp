#include "FrameBuffer.h"
#include "glad/glad.h"
#include "Core/Logger.h"

// TODO: WTF even is this, refactor for multiple framebuffers support
namespace Core
{
    FrameBuffer::FrameBuffer(FrameBufferSpecification spec)
    {
        for (auto a : spec.Attachment.Attachments)
        {
            if (a.Filtering == FrameBufferTextureFiltering::Depth24Stencil8)
                depthSpecification = a;
            else
                colorSpecifications.push_back(a);
        }

        Create(spec);
    }

    static GLenum FilterToGL(FrameBufferTextureFiltering filter)
    {
        switch (filter)
        {
        case FrameBufferTextureFiltering::Rgba8:
            return GL_RGBA8;
            break;

        case FrameBufferTextureFiltering::Depth24Stencil8:
            return GL_DEPTH24_STENCIL8;
            break;

        case FrameBufferTextureFiltering::RedInteger:
            return GL_RED_INTEGER;
            break;
        }

        return 0;
    };

    void FrameBuffer::Create(FrameBufferSpecification spec)
    {
        // Set the specification
        specification = spec;

        glGenFramebuffers(1, &id);
        glBindFramebuffer(GL_FRAMEBUFFER, id);

        // Resize array to this size
        colorAttachmentsID.resize(colorSpecifications.size());

        // Loop on generate each texture
        for (int i = 0; i < colorSpecifications.size(); i++)
        {
            glGenTextures(1, &colorAttachmentsID[i]);
            glBindTexture(GL_TEXTURE_2D, colorAttachmentsID[i]);

            switch (colorSpecifications[i].Filtering)
            {
            case FrameBufferTextureFiltering::Rgba8:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, spec.Width, spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
                break;

            case FrameBufferTextureFiltering::RedInteger:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, spec.Width, spec.Height, 0, GL_RED_INTEGER, GL_INT, nullptr);
                break;

            default:
                break;
            }

            // TODO: Dynamic
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glBindTexture(GL_TEXTURE_2D, 0);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorAttachmentsID[i], 0);
        }

        // attach it to currently bound framebuffer object

        // Depth
        glGenRenderbuffers(1, &depthAttachmentID);
        glBindRenderbuffer(GL_RENDERBUFFER, depthAttachmentID);
        glRenderbufferStorage(GL_RENDERBUFFER, FilterToGL(depthSpecification.Filtering), spec.Width, spec.Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthAttachmentID);

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    void FrameBuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

    void FrameBuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::Resize(float width, float height)
    {
        specification.Width = width;
        specification.Height = height;

        Create(specification);
    }

    void FrameBuffer::Destroy()
    {
        glDeleteFramebuffers(1, &id);
    }

    void FrameBuffer::UseColorAttachment(int i)
    {
        glActiveTexture(GL_COLOR_ATTACHMENT0 + i);
    }

    uint32_t FrameBuffer::ReadPixel(uint32_t attachment, int x, int y)
    {
        glBindTexture(GL_TEXTURE_2D, colorAttachmentsID[attachment]);

        int pd;
        glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pd);

        return (uint32_t)pd;
    }
}