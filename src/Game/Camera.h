#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
    private:
        glm::vec3 position;
        glm::vec3 up;
        glm::vec3 front;

        float yaw;
        float pitch;
        float fov; //Tambien conocido como "zoom"

    public:
        Camera() = default;
        Camera(glm::vec3 position,float yaw,float pitch, float fov);

        glm::vec3 getPosition();
        void setPosition(glm::vec3 position);

        glm::vec3 getUp();
        glm::vec3 getFront();

        float getYaw();
        void setYaw(float yaw);
        
        float getPitch();
        void setPitch(float pitch);

        float getFov();

        glm::mat4 getViewMatriz();
    private:
        void calculateFront();
};

#endif
