#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

private:

public:

    Camera(glm::vec3 position, glm::vec3 direction, float fov, float nearThreshold, float farThreshold, unsigned int width, unsigned int height);
    ~Camera();

    glm::vec3 position;
    glm::vec3 direction;
    float fov;
    float nearThreshold;
    float farThreshold;
    unsigned int width;
    unsigned int height;

    glm::mat4 getCameraMatrix() const;

    static constexpr glm::vec3 UP_VECTOR{ 0.0f, 1.0f, 0.0f };
};