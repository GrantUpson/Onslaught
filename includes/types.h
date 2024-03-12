#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <memory>
#include "glm/glm.hpp"


using uint64 = std::uint64_t;
using uint32 = std::uint32_t;
using uint16 = std::uint16_t;
using uint8 = std::uint8_t;

using int64 = std::int64_t;
using int32 = std::int32_t;
using int16 = std::int16_t;
using int8 = std::int8_t;

using Vector2 = glm::vec2;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;

using Vector2i = glm::u16vec2;

using Matrix3 = glm::mat3;
using Matrix4 = glm::mat4;

template <typename T>
using Reference = std::shared_ptr<T>;

template <typename T>
using Owner = std::unique_ptr<T>;


#endif
