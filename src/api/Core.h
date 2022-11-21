//
// Created by Erik on 08/10/22.
//

#ifndef LII_CORE_H
#define LII_CORE_H
#include "RenderingProvider.h"

class Core
{
public:
    virtual void SetRenderingProvider(RenderingProvider& provider) = 0;
    virtual long long int SetAttributes(int index, long long int parameter) = 0;
    virtual long long int RemoveAttribute(int index, long long int parameter) = 0;
    virtual void UpdateScale() = 0;
    virtual void Redraw() = 0;
    virtual void Close() = 0;
    virtual void Start() = 0;
    virtual void SetLockCursorSize(const glm::vec2 &size) = 0;
    virtual void LockCursor(const bool& lockState) = 0;
    virtual const bool& IsCursorLocked() const = 0;
    virtual RenderingProvider* GetRenderingProvider() = 0;
};


#endif //LII_CORE_H
