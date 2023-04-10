//
// Created by erik9 on 12/12/2022.
//

#ifndef LII_MOVABLEMODELBEHAVIOR_H
#define LII_MOVABLEMODELBEHAVIOR_H
#include <vector>
#include "MoveSubscriber.h"
#include "Movable.h"

class MovableModelBehavior : public Movable
{
private:
    glm::vec4 position = {0, 0, 0, 0};
    glm::vec4 translation;
    std::vector<MoveSubscriber*> moveSubscribers;
    Movable& owner;
public:
    MovableModelBehavior(Movable& associatedMovable);

    glm::vec4 GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetZ() override;

    float GetW() override;

    float GetAbsoluteX() override;

    float GetAbsoluteY() override;

    const glm::vec4 & GetAbsolutePosition() override;

    void SetPosition(glm::vec4 position, bool emit) override;

    void SetPosition(glm::vec4 position) override;

    void SetPosition(float x, float y, float z, float w, bool emit) override;

    void SetPosition(float x, float y, float z, float w) override;

    void SetX(float x, bool emit) override;

    void SetX(float x) override;

    void SetY(float y, bool emit) override;

    void SetY(float y) override;

    void SetZ(float z, bool emit) override;

    void SetZ(float z) override;

    void SetW(float w, bool emit) override;

    void SetW(float w) override;

    void SetTranslate(glm::vec4 offset, bool emit) override;

    void SetTranslate(glm::vec4 offset) override;

    void SetTranslateX(float x, bool emit) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y, bool emit) override;

    void SetTranslateY(float y) override;

    glm::vec4 GetTranslate() override;

    float GetTranslateX() override;

    float GetTranslateY() override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(EventMoveInfo e) override;
};


#endif //LII_MOVABLEMODELBEHAVIOR_H
