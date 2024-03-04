#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H
#include "types.h"


class OrthographicCamera {
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    void SetPosition(const Vector3& position);
    void SetRotation(float rotation);

    Vector3 GetPosition() const;
    float GetRotation() const;

    const Matrix4& GetProjectionMatrix() const;
    const Matrix4& GetViewMatrix() const;
    const Matrix4& GetViewProjectionMatrix() const;
private:
    Matrix4 projection {};
    Matrix4 view {};
    Matrix4 viewProjection {};

    Vector3 position {0.0f, 0.0f, 0.0f};
    float rotation {0.0f};

    void CalculateViewMatrix();
};



#endif
