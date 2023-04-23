//
// Created by erik9 on 4/22/2023.
//

#ifndef LII_TEXTINPUTAPI_H
#define LII_TEXTINPUTAPI_H


#include <string>
#include "Movable.h"
#include "Resizable.h"
#include "ActivateSubject.h"
#include "KeyStateSubject.h"

//TODO properties like background shouldn't be tied to the interface.
class TextInputApi : public virtual Movable, public virtual Resizable, public virtual ActivateSubject, public virtual KeyStateSubject
{
public:
    virtual void SetText(std::wstring text) = 0;
    virtual const std::wstring& GetText() = 0;
    virtual const glm::ivec4& GetBackgroundColor() = 0;
    virtual void SetBackgroundColor(const glm::ivec4& color) = 0;
};


#endif //LII_TEXTINPUTAPI_H
