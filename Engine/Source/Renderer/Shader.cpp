#include "Shader.h"
#include "Core/Logger.h"
#include "Platform/FileSystem.h"
#include "glad/glad.h"

namespace Core
{
    static uint32_t GenerateIndividualShader(GLenum type, const char *src)
    {
        GLuint shader = glCreateShader(type);
        const GLchar *newSource = (const GLchar *)src;
        glShaderSource(shader, 1, &newSource, 0);
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            CE_ERROR("Shader compilation failed.");
            CE_ERROR("%s", infoLog.data());

            // We don't need the shader anymore.
            glDeleteShader(shader);

            // Use the infoLog as you see fit.

            // In this simple program, we'll just leave
            return (GLuint)0;
        }

        return shader;
    };

    Shader::Shader(const std::string &vertexSource, const std::string &fragSource)
    {
        std::string vertexFinalSource = FileSystem::Read(vertexSource.c_str());
        std::string fragFinalSource = FileSystem::Read(fragSource.c_str());

        uint32_t vertexShader = GenerateIndividualShader(GL_VERTEX_SHADER, vertexFinalSource.c_str());
        uint32_t fragmentShader = GenerateIndividualShader(GL_FRAGMENT_SHADER, fragFinalSource.c_str());

        id = glCreateProgram();
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);

        uint32_t isLinked = 0;
        glGetProgramiv(id, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);
            glDeleteProgram(id);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            CE_ERROR("Program error dead.");
            CE_ERROR("%s", infoLog.data());
        }
    }

    Shader::~Shader()
    {
        Destroy();
    }

    void Shader::Destroy()
    {
        Detach();
        glDeleteProgram(id);
    }

    void Shader::Use()
    {
        glUseProgram(this->id);
    }

    void Shader::Detach()
    {
        glUseProgram(0);
    }

    uint32_t Shader::GetUniformLocation(const char *name)
    {
        Use();
        return glGetUniformLocation(id, name);
    }

    void Shader::Mat4(const char *name, float *data)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, data);
    }

    void Shader::Vec4(const char *name, float x, float y, float z, float w)
    {
        glUniform4f(GetUniformLocation(name), x, y, z, w);
    }

    void Shader::Int(const char *name, int x)
    {
        glUniform1i(GetUniformLocation(name), x);
    }

    uint32_t Shader::GetID()
    {
        return id;
    }

}