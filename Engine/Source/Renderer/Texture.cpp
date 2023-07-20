#include "Texture.h"
#include "Core/Logger.h"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Core
{
    static uint32_t generations = 0;

    GLenum ChannelsToGL(int channels)
    {
        switch (channels)
        {
        case 3:
            return GL_RGB;

        case 4:
            return GL_RGBA;

        default:
            CE_ERROR("Unknown channel count: %i.", channels);
            return GL_RGB;
        }
    }

    Texture::Texture()
    {
        channels = 3;
        generation = generations;
        generations++;

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        // Use default data
        uint8_t data[4] = {255, 255, 255, 255};
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // No distortion
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // WIP: Dynamyc texture sampling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture::~Texture()
    {
        Destroy();
    }

    void Texture::FromPath(const char *path)
    {
        Destroy();

        uint8_t *data = stbi_load(path, &width, &height, &channels, 0);

        if (!data)
        {
            CE_ERROR("Unable to load image: %s", path);
            return;
        }

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        // WIP: Dynamyc texture sampling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Use default data
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // No distortion
        glTexImage2D(GL_TEXTURE_2D, 0, ChannelsToGL(channels), width, height, 0, ChannelsToGL(channels), GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    void Texture::Swap(const char *path)
    {
        Destroy();
        FromPath(path);
    }

    void Texture::Bind()
    {
        if (channels == 4)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        glBindTexture(GL_TEXTURE_2D, id);
    }

    void Texture::Unbind()
    {
        if (channels == 4)
        {
            glDisable(GL_BLEND);
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::Destroy()
    {
        Unbind();
        glDeleteTextures(1, &id);
    }

    void Texture::Use()
    {
        glActiveTexture(GL_TEXTURE0 + generation);
        Bind();
    }

    uint32_t Texture::GetID()
    {
        return id;
    }

    uint32_t Texture::GetGeneration()
    {
        return generation;
    }
}