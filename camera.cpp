#include "camera.h"

Camera::Camera(glm::vec3 position, float yaw, float pitch, glm::vec3 up) : Front(glm::vec3(0.0f, 1.0f, 0.0f))
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
    updateCameraVectors();
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::setOrthoMode(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
    projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
}

void Camera::setPerspectiveMode(const float fov, const float aspect, const float near, const float far)
{
    projectionMatrix = glm::perspective(fov, aspect, near, far);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return projectionMatrix;
}

glm::vec3 Camera::getPosition() const
{
    return Position;
}

void Camera::setPosition(const glm::vec3 &value)
{
    Position = value;
}

void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.y = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    front.z = sin(glm::radians(this->Pitch));
    front.x = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->Up    = glm::normalize(glm::cross(this->Right, this->Front));
}

//Camera::Camera() :
//    position(0.0f),
//    rotation(0.0f)
//{

//}

//glm::vec3 Camera::getPosition()
//{
//    return this->position;
//}

//glm::vec3 Camera::getRotation()
//{
//    return this->rotation;
//}
//glm::vec3* Camera::setPosition()
//{
//    this->VPchanged = true;
//    return &this->position;
//}

//glm::vec3* Camera::setRotation()
//{
//    this->VPchanged = true;
//    return &this->rotation;
//}

//void Camera::setPosition(glm::vec3 position)
//{
//    this->VPchanged = true;
//    this->position = position;
//}

//void Camera::setRotation(glm::vec3 rotation)
//{
//    this->VPchanged = true;
//    this->rotation = rotation;
//}

//void Camera::addLocalCoordinats(const glm::vec3 coord)
//{
//    glm::vec3 test;
//    test = glm::rotate(coord, glm::radians(getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
//    //    test = glm::rotate(test, glm::radians(getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
//    test = glm::rotate(test, glm::radians(getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
//    position += test;
//    this->VPchanged = true;
//}

//void Camera::lookAt(glm::vec3 position, glm::vec3 lookingAt, glm::vec3 up)
//{
//    this->VPchanged = true;
//    this->position = position;
//    this->up = up;
//    this->lookingAt = lookingAt;
//    this->View = glm::lookAt(this->position, this->lookingAt, this->up);
//}

//void Camera::projetionOrtho(float f_left, float f_right, float f_bottom, float f_top, float f_zNear, float f_zFar)
//{
//    this->VPchanged = true;
//    this->Projection = glm::ortho(f_left, f_right, f_bottom, f_top, f_zNear, f_zFar);
//}

//void Camera::projectionPerspective(float f_fieldOfView, float f_aspectRatio, float f_zNear, float f_zFar)
//{
//    this->VPchanged = true;
//    this->Projection =glm::perspective(f_fieldOfView, f_aspectRatio, f_zNear, f_zFar);
//}

//glm::mat4 Camera::getVP()
//{
//    return this->VP;
//}

//glm::mat4 Camera::getProjection()
//{
//    return Projection;
//}

//glm::mat4 Camera::getView()
//{
//    return View;
//}

//void Camera::update()
//{
//    if(this->VPchanged)
//    {
//        //        this->lookingAt = glm::vec3(position.x-sin(rotation.z*(M_PI/180.0f)),
//        //                                    (position.y+cos(rotation.z*(M_PI/180.0f))),
//        //                                    position.z+(rotation.y*M_PI/180.0f));
//        this->lookingAt = glm::vec3(position.x-sin(rotation.z*M_PI/180.0f),
//                                    (position.y+cos(rotation.z*M_PI/180.0f)),
//                                    position.z+tan(rotation.y*M_PI/180.0f));
////        std::cout << "Rot Y: " << rotation.y << std::endl;
////        std::cout << "Rot Z: " << rotation.z << std::endl;
////        std::cout << "Pos X: " << position.x << std::endl;
////        std::cout << "Pos Y: " << position.y << std::endl;
////        std::cout << "Pos Z: " << position.z << std::endl;
////        std::cout << "=== " << std::endl;

//        this->View = glm::lookAt(this->position, this->lookingAt, this->up);
//        this->VP = this->Projection * this->View;
//        VPchanged = false;
//    }
//}
