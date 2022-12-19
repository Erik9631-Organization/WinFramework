//
// Created by erik9 on 12/12/2022.
//

#ifndef LII_MOVABLEMODELBEHAVIOR_H
#define LII_MOVABLEMODELBEHAVIOR_H
#include "Movable.h"
#include <vector>
#include "MoveSubscriber.h"

class MovableModelBehavior : public Movable
{
private:
    glm::vec2 position;
    glm::vec2 translation;
    std::vector<MoveSubscriber*> moveSubscribers;
public:
    glm::vec2 GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetAbsoluteX() override;

    float GetAbsoluteY() override;

    glm::vec2 GetAbsolutePosition() override;

    void SetPosition(glm::vec2 position, bool emit) override;

    void SetPosition(glm::vec2 position) override;

    void SetPosition(float x, float y, bool emit) override;

    void SetPosition(float x, float y) override;

    void SetX(float x, bool emit) override;

    void SetX(float x) override;

    void SetY(float y, bool emit) override;

    void SetY(float y) override;

    void SetTranslate(glm::vec2 offset, bool emit) override;

    void SetTranslate(glm::vec2 offset) override;

    void SetTranslateX(float x, bool emit) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y, bool emit) override;

    void SetTranslateY(float y) override;

    glm::vec2 GetTranslate() override;

    float GetTranslateX() override;

    float GetTranslateY() override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(EventMoveInfo e) override;

};


#endif //LII_MOVABLEMODELBEHAVIOR_H
