//
// Created by Erik on 13/03/22.
//

#ifndef LII_BASICCAMERA_H
#define LII_BASICCAMERA_H
#include "Camera.h"

namespace OpenGL
{
    class BasicCamera : public Camera
    {
    public:
        BasicCamera();
        void Left(const float &val) override;
        void Right(const float &val) override;
        void Up(const float &val) override;
        void Down(const float &val) override;
        void SetPosition(const float &x, const float &y, const float &z) override;
        void SetPosition(const glm::vec3 &position) override;
        const glm::vec3 &GetPosition() const override;
        void SetYaw(const float &x) override;
        void SetRoll(const float &x) override;
        void AddPitch(const float &x) override;
        void AddYaw(const float &x) override;
        void AddRoll(const float &x) override;
        void Foward(const float &val) override;
        void Backward(const float &val) override;
        void SetPitch(const float& x) override;
        const glm::vec3 & GetForwardAxis() const override;
        const glm::vec3 & GetRightAxis() const override;
        const glm::vec3 & GetUpAxis() const override;
    private:
        void UpdateAxes();

        float yaw = 0;
        float pitch = -90;
        float roll = 0;

        glm::vec3 position;
        //Used to define basis of the camera coordinate system
        glm::vec3 forwardAxis;
        glm::vec3 rightAxis;
        glm::vec3 upAxis;

    };
}


#endif //LII_BASICCAMERA_H
