#include "utility/resourceLoader.h"



std::unordered_map<std::string, Reference<Shader>> ResourceLoader::shaders;
std::unordered_map<std::string, Reference<Texture2D>> ResourceLoader::textures;


Reference<Shader> ResourceLoader::GetShader(const std::string& name) {
    return shaders[name];
}


void ResourceLoader::LoadShader(const std::string& name, const std::string& vertexFilepath, const std::string& fragmentFilepath) {
    shaders[name] = std::make_shared<Shader>(vertexFilepath, fragmentFilepath);
}


void ResourceLoader::LoadTexture(const std::string& name, const std::string& filepath) {
    textures[name] = std::make_shared<Texture2D>(filepath);
}


Reference<Texture2D> ResourceLoader::GetTexture(const std::string& name) {
    return textures[name];
}

