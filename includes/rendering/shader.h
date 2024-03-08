#ifndef SHADER_H
#define SHADER_H

#include "types.h"


class Shader {
public:
    Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
    ~Shader();

    void Bind() const;
    uint32 GetId() const;

    void SetUniformMatrix4(const std::string& name, const Matrix4& matrix) const;

private:
    uint32 id {};
};



#endif
