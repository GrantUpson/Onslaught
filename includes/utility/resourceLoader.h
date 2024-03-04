#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <unordered_map>
#include "rendering/shader.h"
#include "rendering/texture2D.h"
#include <string>


class ResourceLoader {
public:
    static Reference<Shader> GetShader(const std::string& name);
    static void LoadShader(const std::string& name, const std::string& vertexFilepath, const std::string& fragmentFilepath);

    static void LoadTexture(const std::string& name, const std::string& filepath);
    static Reference<Texture2D> GetTexture(const std::string& name);

private:
    ResourceLoader() = default;

    static std::unordered_map<std::string, Reference<Shader>> shaders;
    static std::unordered_map<std::string, Reference<Texture2D>> textures;
};


#endif