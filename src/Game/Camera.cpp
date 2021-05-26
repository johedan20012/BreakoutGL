#include "Camera.h"

Camera::Camera(glm::vec3 position,float yaw,float pitch,float fov)
    :position(position),up(glm::vec3(0.0f,1.0f,0.0f)),yaw(yaw),pitch(pitch),fov(fov){
        calculateFront();        
}

glm::vec3 Camera::getPosition(){
    return position;
}

void Camera::setPosition(glm::vec3 position){
    this->position = position;
}

glm::vec3 Camera::getUp(){
    return up;
}

glm::vec3 Camera::getFront(){
    return front;
}

float Camera::getYaw(){
    return yaw;
}

void Camera::setYaw(float yaw){
    this->yaw = fmod(yaw,360.0f);
    calculateFront();
}

float Camera::getPitch(){
    return pitch;
}

void Camera::setPitch(float pitch){
    this->pitch = pitch;
    if(this->pitch > 89.0f) this->pitch = 89.0f;
    if(this->pitch < -89.0f) this->pitch = -89.0f;
    calculateFront();
}

float Camera::getFov(){
    return fov;
}

glm::mat4 Camera::getViewMatriz(){
    return glm::lookAt(position, position + front, up);
}

void Camera::calculateFront(){
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
}