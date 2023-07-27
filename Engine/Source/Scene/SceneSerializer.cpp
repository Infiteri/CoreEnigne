#include "SceneSerializer.h"
#include "yaml-cpp/yaml.h"
#include "Core/Logger.h"
#include "Renderer/Color.h"
#include "Scene/Components.h"
#include <fstream>

namespace Core
{
    YAML::Emitter &operator<<(YAML::Emitter &out, Vector3 *v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v->x << v->y << v->z << YAML::EndSeq;
        return out;
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, Color *color)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << color->GetR() << color->GetG() << color->GetB() << color->GetA() << YAML::EndSeq;
        return out;
    }

    SceneSerializer::SceneSerializer(Scene *scene)
    {
        this->scene = scene;
    }

    SceneSerializer::~SceneSerializer()
    {
    }

    void SceneSerializer::Serialize(const std::string &path)
    {
        YAML::Emitter out;

        out << YAML::BeginMap;
        out << YAML::Key << "Scene" << YAML::Value << "Unnamed";
        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

        for (Entity *entity : scene->GetAllEntities())
        {
            out << YAML::BeginMap;
            out << YAML::Key << "Entity";
            out << YAML::Value << entity->GetID();

            out << YAML::Key << "Name" << YAML::Value << entity->GetName().c_str();

            if (entity->HasComponent<TransformComponent>())
            {
                TransformComponent *tc = entity->GetComponent<TransformComponent>();

                out << YAML::Key << "TransformComponent";
                out << YAML::BeginMap;
                out << YAML::Key << "Position" << YAML::Value << &tc->transform.position;
                out << YAML::Key << "Rotation" << YAML::Value << &tc->transform.rotation;
                out << YAML::Key << "Scale" << YAML::Value << &tc->transform.scale;
                out << YAML::EndMap;
            }

            if (entity->HasComponent<SpriteComponent>())
            {
                SpriteComponent *c = entity->GetComponent<SpriteComponent>();

                out << YAML::Key << "SpriteComponent";

                out << YAML::BeginMap;
                out << YAML::Key << "Color" << YAML::Value << c->sprite.GetMaterial()->GetColor();
                out << YAML::Key << "Width" << YAML::Value << c->sprite.GetWidth();
                out << YAML::Key << "Height" << YAML::Value << c->sprite.GetHeight();

                out << YAML::Key << "TexturePath" << YAML::Value << c->sprite.GetMaterial()->GetTexture()->GetPath().c_str();
                out << YAML::EndMap;
            }

            if (entity->HasComponent<CameraComponent>())
            {
                CameraComponent *c = entity->GetComponent<CameraComponent>();

                out << YAML::Key << "CameraComponent";

                out << YAML::BeginMap;
                out << YAML::Key << "Position" << YAML::Value << c->camera.GetPosition();
                out << YAML::Key << "Zoom" << YAML::Value << c->camera.GetZoom();
                out << YAML::EndMap;
            }

            if (entity->HasComponent<ScriptComponent>())
            {
                ScriptComponent *c = entity->GetComponent<ScriptComponent>();

                out << YAML::Key << "ScriptComponent";

                out << YAML::BeginMap;
                out << YAML::Key << "ClassName" << YAML::Value << c->className.c_str();
                out << YAML::EndMap;
            }

            out << YAML::EndMap;
        }

        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream fout(path);
        fout << out.c_str();
    }

    void SceneSerializer::Deserialize(const std::string &path)
    {
        std::ifstream stream(path);
        std::stringstream strStream;
        strStream << stream.rdbuf();

        YAML::Node data = YAML::Load(strStream);

        if (!data["Scene"])
            return;

        std::string sceneName = data["Scene"].as<std::string>();

        auto entities = data["Entities"];

        if (entities)
        {
            for (auto e : entities)
            {
                Entity *ent = new Entity();

                std::string name = e["Name"].as<std::string>();
                ent->SetName(name);

                if (e["TransformComponent"])
                {
                    TransformComponent *c = ent->AddComponent<TransformComponent>();

                    c->transform.position.x = e["TransformComponent"]["Position"][0].as<float>();
                    c->transform.position.y = e["TransformComponent"]["Position"][1].as<float>();
                    c->transform.position.z = e["TransformComponent"]["Position"][2].as<float>();

                    c->transform.rotation.x = e["TransformComponent"]["Rotation"][0].as<float>();
                    c->transform.rotation.y = e["TransformComponent"]["Rotation"][1].as<float>();
                    c->transform.rotation.z = e["TransformComponent"]["Rotation"][2].as<float>();

                    c->transform.scale.x = e["TransformComponent"]["Scale"][0].as<float>();
                    c->transform.scale.y = e["TransformComponent"]["Scale"][1].as<float>();
                    c->transform.scale.z = e["TransformComponent"]["Scale"][2].as<float>();
                }

                if (e["SpriteComponent"])
                {
                    auto color = e["SpriteComponent"]["Color"];
                    auto texPath = e["SpriteComponent"]["TexturePath"];
                    SpriteComponent *c = ent->AddComponent<SpriteComponent>();
                    c->sprite.GetMaterial()->GetColor()->Set(color[0].as<float>(), color[1].as<float>(), color[2].as<float>(), color[3].as<float>());
                    c->sprite.SetSize(e["SpriteComponent"]["Width"].as<float>(), e["SpriteComponent"]["Height"].as<float>());

                    if (texPath)
                    {
                        if (texPath.as<std::string>().compare("") == 0)
                        {
                        }
                        else
                        {
                            c->sprite.GetMaterial()->GetTexture()->FromPath(texPath.as<std::string>().c_str());
                        }
                    }
                    else
                    {
                        CE_ERROR("Scene Deserialization ERROR: Field of TexturePath inside a SpriteComponent map is not present. (%s)", name.c_str());
                    }
                }

                if (e["CameraComponent"])
                {
                    CameraComponent *c = ent->AddComponent<CameraComponent>();
                    c->camera.SetZoom(e["CameraComponent"]["Zoom"].as<float>());
                    auto pos = c->camera.GetPosition();
                    pos->x = e["CameraComponent"]["Position"][0].as<float>();
                    pos->y = e["CameraComponent"]["Position"][1].as<float>();
                    pos->z = e["CameraComponent"]["Position"][2].as<float>();
                }

                if (e["ScriptComponent"])
                {
                    ScriptComponent *c = ent->AddComponent<ScriptComponent>();
                    c->className = e["ScriptComponent"]["ClassName"].as<std::string>();
                }

                scene->AddEntity(ent);
            }
        }
    }
}