#ifndef SHADER_H
#define SHADER_H

#include "types.h"


class Shader {
public:
    Shader(const std::string& vertexCode, const std::string& fragmentCode);
    ~Shader();

    void Bind() const;
    [[nodiscard]] uint32 GetId() const;

private:
    uint32 id {};
};



#endif
