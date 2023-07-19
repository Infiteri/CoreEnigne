#include "Material.h"
#include "Renderer.h"

namespace Core
{
    Material::Material()
    {
        color = new Color(255, 255, 255, 255);
    }

    Material::~Material()
    {
        delete color;
    }

    void Material::Use()
    {
        Shader *shd = Renderer::GetColorShader();

        shd->Vec4("uColor", color->GetRNormalized(), color->GetGNormalized(), color->GetBNormalized(), color->GetANormalized());
    }

    void Material::PostUse()
    {
    }
}