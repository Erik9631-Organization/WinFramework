//
// Created by erik9 on 12/12/2022.
//

#ifndef LII_MOVABLEMODELBEHAVIOR_H
#define LII_MOVABLEMODELBEHAVIOR_H
#include <vector>
#include "MoveSubscriber.h"
#include "Movable.h"

//curValue = GetPosition()
//curValue.x = 12313123123
//SetPosition(curValue)

class MovableModelBehavior : public Movable
{
private:
    glm::vec3 position{0};
    glm::vec3 translation{0};
    std::vector<MoveSubscriber*> moveSubscribers;
    Movable& owner;
public:
    explicit MovableModelBehavior(Movable& associatedMovable);

    [[nodiscard]] const glm::vec3 & GetPosition() const override;

    [[nodiscard]] const glm::vec3 & GetAbsolutePosition() const override;

    void SetPosition(const glm::vec3 &position, bool emit = true) override;

    void SetTranslate(const glm::vec3 &offset, bool emit = true) override;

    [[nodiscard]] const glm::vec3 & GetTranslate() const override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(const EventMoveInfo &e) override;
};


#endif //LII_MOVABLEMODELBEHAVIOR_H
