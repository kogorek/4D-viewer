#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

#include <glm/gtx/transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/rotate_vector.hpp>

// Default camera values
const float YAW        = -90.0f;
const float PITCH      =  0.0f;
//const float SPEED      =  3.0f;
//const float SENSITIVTY =  0.25f;
//const float ZOOM       =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    glm::mat4 projectionMatrix;
    // Eular Angles
    float Yaw;
    float Pitch;


    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float yaw = YAW, float pitch = PITCH,
           glm::vec3 up = glm::vec3(0.0f, 0.0f, -1.0f));

    glm::mat4 getViewMatrix();

    void setOrthoMode(const float left, const float right, const float bottom, const float top, const float near, const float far);

    void setPerspectiveMode(const float fov, const float aspect, const float near, const float far);

    glm::mat4 getProjectionMatrix() const;

    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3 &value);

private:
    // Calculates the front vector from the Camera's (updated) Eular Angles
    void updateCameraVectors();
};


#endif // CAMERA_H
