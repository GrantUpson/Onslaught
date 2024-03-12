#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "types.h"
#include <string>


class Texture2D {
public:
    explicit Texture2D(const uint32 id, const int32 width, const int32 height) : id(id), width(width), height(height) {}
    ~Texture2D();

    [[nodiscard]] uint32 GetId() const;
    [[nodiscard]] int32 GetWidth() const;
    [[nodiscard]] int32 GetHeight() const;
private:
    const uint32 id {};
    const int32 width {};
    const int32 height {};
};



#endif
