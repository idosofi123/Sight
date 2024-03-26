#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 direction, float fov, float nearThreshold, float farThreshold, unsigned int width, unsigned int height)
    : position(position), direction(direction), fov(fov), nearThreshold(nearThreshold), farThreshold(farThreshold), width(width), height(height) {
    
}

Camera::~Camera() {}

glm::mat4 Camera::getCameraMatrix() const {
    return glm::perspective(
        glm::radians(this->fov),
        static_cast<float>(this->width) / this->height,
        this->nearThreshold,
        this->farThreshold)
        * glm::lookAt(this->position, this->position + this->direction, UP_VECTOR);
}
