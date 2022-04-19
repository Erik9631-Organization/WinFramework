//
// Created by Erik on 13/03/22.
//
#include "BasicCamera.h"

void OpenGL::BasicCamera::Left(const float &val)
{
    position -= val * rightAxis;
}

void OpenGL::BasicCamera::Right(const float &val)
{
    position += val * rightAxis;
}

void OpenGL::BasicCamera::Up(const float &val)
{
    position += val * upAxis;
}

void OpenGL::BasicCamera::Down(const float &val)
{
    position -= val * upAxis;
}

void OpenGL::BasicCamera::Foward(const float &val)
{
    position += val * forwardAxis;
}

void OpenGL::BasicCamera::Backward(const float &val)
{
    position -= val * forwardAxis;
}


void OpenGL::BasicCamera::SetPosition(const float &x, const float &y, const float &z)
{
    position = {x, y, z};
}

void OpenGL::BasicCamera::SetPosition(const glm::vec3 &position)
{
    this->position = position;
}

const glm::vec3 &OpenGL::BasicCamera::GetPosition() const
{
    return position;
}

void OpenGL::BasicCamera::SetYaw(const float &x)
{
    this->yaw = x;
    UpdateAxes();
}

void OpenGL::BasicCamera::SetRoll(const float &x)
{

}

void OpenGL::BasicCamera::AddPitch(const float &x)
{
    pitch += x;
    UpdateAxes();
}

void OpenGL::BasicCamera::AddYaw(const float &x)
{
    yaw += x;
    UpdateAxes();
}

void OpenGL::BasicCamera::AddRoll(const float &x)
{

}

void OpenGL::BasicCamera::SetPitch(const float &x)
{
    pitch = x;
    UpdateAxes();
}

OpenGL::BasicCamera::BasicCamera()
{
    position = {0, 0, 0};
    forwardAxis = {0, 0, -1};
    upAxis = {0, 1, 0};
    rightAxis = {1, 0, 0};
}

const glm::vec3 & OpenGL::BasicCamera::GetForwardAxis() const
{
    return forwardAxis;
}

const glm::vec3 & OpenGL::BasicCamera::GetRightAxis() const
{
    return rightAxis;
}

const glm::vec3 & OpenGL::BasicCamera::GetUpAxis() const
{
    return upAxis;
}

void OpenGL::BasicCamera::UpdateAxes()
{
    float yawRads = glm::radians(yaw);
    float pitchRads = glm::radians(pitch);

    forwardAxis.x = sin(yawRads) * sin(pitchRads);
    forwardAxis.y = cos(pitchRads);
    forwardAxis.z = cos(yawRads) * sin(pitchRads);
    forwardAxis = glm::normalize(forwardAxis);
    rightAxis = glm::cross(forwardAxis, upAxis);
}
