//
// Created by Erik on 20/03/22.
//

#ifndef LII_RELATIVEMOVEMENT_H
#define LII_RELATIVEMOVEMENT_H
#include <glm.hpp>

class RelativeMovement
{
public:
    virtual void Left(const float& val) = 0;
    virtual void Right(const float& val) = 0;
    virtual void Up(const float& val) = 0;
    virtual void Down(const float& val) = 0;
    virtual void Foward(const float& val) = 0;
    virtual void Backward(const float& val) = 0;
    virtual void SetPosition(const float& x, const float& y, const float& z) = 0;
    virtual void SetPosition(const glm::vec3& position) = 0;
    virtual const glm::vec3& GetPosition() const = 0;
    virtual void SetPitch(const float& x) = 0;
    virtual void SetYaw(const float& x) = 0;
    virtual void SetRoll(const float& x) = 0;
    virtual void AddPitch(const float& x) = 0;
    virtual void AddYaw(const float& x) = 0;
    virtual void AddRoll(const float& x) = 0;
    virtual const glm::vec3 & GetForwardAxis() const = 0;
    virtual const glm::vec3 & GetRightAxis() const = 0;
    virtual const glm::vec3 & GetUpAxis() const = 0;
    virtual ~RelativeMovement() = default;
};



#endif //LII_RELATIVEMOVEMENT_H
