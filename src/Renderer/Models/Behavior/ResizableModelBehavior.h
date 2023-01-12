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
    glm::vec4 size;
    std::vector<ResizeSubscriber*> resizeSubscribers;

public:
    glm::vec4 GetSize() override;

    float GetWidth() override;

    float GetHeight() override;

    void SetSize(glm::vec4 size, bool emit) override;

    void SetSize(glm::vec4 size) override;

    void SetSize(float width, float height, bool emit) override;

    void SetSize(float width, float height) override;

    void SetWidth(float width, bool emit) override;

    void SetWidth(float width) override;

    void SetHeight(float height, bool emit) override;

    void SetHeight(float height) override;

    void NotifyOnResizeSubscribers(EventResizeInfo event) override;

    void AddOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) override;

};


#endif //LII_RESIZABLEMODELBEHAVIOR_H
