//
// Created by erik9 on 12/12/2022.
//

#ifndef LII_RESIZABLEMODELBEHAVIOR_H
#define LII_RESIZABLEMODELBEHAVIOR_H
#include "Resizable.h"
#include "ResizeSubscriber.h"
#include <vector>

class ResizableModelBehavior : public Resizable
{
private:
    glm::vec3 size{0};
    std::vector<ResizeSubscriber*> resizeSubscribers;

public:
    [[nodiscard]] const glm::vec3 & GetSize() const override;

    void SetSize(const glm::vec3 &size, bool emit) override;

    void NotifyOnResizeSubscribers(EventResizeInfo event) override;

    void AddOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) override;

};


#endif //LII_RESIZABLEMODELBEHAVIOR_H
