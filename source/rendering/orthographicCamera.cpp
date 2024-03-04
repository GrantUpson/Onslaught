#include "rendering/orthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"


OrthographicCamera::OrthographicCamera(const float left, const float right, const float bottom, const float top) :
   projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)) {
    viewProjection = projection * view;
}


void OrthographicCamera::SetPosition(const Vector3& position) {
    this->position = position;
    CalculateViewMatrix();
}


void OrthographicCamera::SetRotation(const float rotation) {
    this->rotation = rotation;
}


Vector3 OrthographicCamera::GetPosition() const {
    return position;
}


float OrthographicCamera::GetRotation() const {
    return rotation;
}


const Matrix4& OrthographicCamera::GetProjectionMatrix() const {
    return projection;
}


const Matrix4& OrthographicCamera::GetViewMatrix() const {
    return view;
}


const Matrix4& OrthographicCamera::GetViewProjectionMatrix() const {
    return viewProjection;
}


void OrthographicCamera::CalculateViewMatrix() {
    Matrix4 transform = translate(Matrix4(1.0f), position) * rotate(Matrix4(1.0f), rotation, Vector3(0, 0, 1));
    view = inverse(transform);
    viewProjection = projection * view;
}
