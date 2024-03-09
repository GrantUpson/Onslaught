#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "types.h"
#include <string>


class Texture2D {
public:
    explicit Texture2D(const std::string& filepath);
    ~Texture2D();

    uint32 GetId() const;
    int32 GetWidth() const;
    int32 GetHeight() const;
private:
    uint32 id {};
    int32 width {};
    int32 height {};
};



#endif
