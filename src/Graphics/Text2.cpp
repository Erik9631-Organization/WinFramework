//
// Created by erik9 on 4/4/2023.
//

#include <iostream>
#include "Text2.h"
#include "Presenter.h"
#include "EventMoveInfo.h"
#include "RelativeZIndex.h"
#include "UiElement.h"

void Text2::OnMounted(Presenter &presenter, UiElement &element)
{
    this->presenter = &presenter;
    this->parentElement = &element;
    textProxy = std::move(presenter.GetRenderer()->RequestTextProxy());
}

void Text2::OnMove(EventMoveInfo e)
{
    if(textProxy == nullptr)
        return;
    textProxy->SetPosition(e.GetSrc()->GetAbsolutePosition());
    presenter->ScheduleRedraw();
}

void Text2::OnResize(EventResizeInfo e)
{

}

float Text2::GetRelativeZIndex()
{
    return RelativeZIndex::GetInstance()->GetIndex("TextIndex");
}

void Text2::SetRelativeZIndex(float relativeZIndex)
{
    RelativeZIndex::GetInstance()->SetIndex("TextIndex", relativeZIndex);
}


void Text2::SetFontSize(float fontSize)
{
    if(textProxy == nullptr)
    {
        std::cout << "Exception textProxy is null" << std::endl;
        return;
    }
    textProxy->SetFontSize(fontSize);
}

void Text2::SetFontAlignment(FontAlignment alignment)
{
    if(textProxy == nullptr)
    {
        std::cout << "Exception textProxy is null" << std::endl;
        return;
    }
    textProxy->SetFontAlignment(alignment);
}

void Text2::SetFontLineAlignment(FontAlignment alignment)
{
    if(textProxy == nullptr)
    {
        std::cout << "Exception textProxy is null" << std::endl;
        return;
    }
    textProxy->SetFontLineAlignment(alignment);
}

void Text2::SetColor(const glm::ivec4 &color)
{
    if(textProxy == nullptr)
    {
        std::cout << "Exception textProxy is null" << std::endl;
        return;
    }
    textProxy->SetColor(color);
}

//TODO Throw exception if textProxy is null
void Text2::SetFontFamily(const std::wstring &fontFamily)
{
    if(textProxy == nullptr)
    {
        std::cout << "Exception textProxy is null" << std::endl;
        return;
    }
    textProxy->SetFontFamily(fontFamily);
}

//TODO Throw exception if textProxy is null
const glm::ivec4 &Text2::GetColor()
{
    if(textProxy == nullptr)
    {
        std::cout << "Exception textProxy is null" << std::endl;
        return glm::ivec4(0,0,0,0);
    }
    return textProxy->GetColor();
}

// TODO Throw exception if textProxy is null
const std::wstring &Text2::GetText()
{
    if(textProxy == nullptr)
    {
        std::cout << "Exception textProxy is null" << std::endl;
        return L"";
    }
    return textProxy->GetText();
}

// TODO Throw exception if textProxy is null
const std::wstring &Text2::GetFontFamily()
{
    if(textProxy == nullptr)
    {
        std::cout << "Exception textProxy is null" << std::endl;
        return L"";
    }

    return textProxy->GetFontFamily();
}

// TODO Throw exception if textProxy is null
FontAlignment Text2::GetFontLineAlignment()
{
    if(textProxy == nullptr)
    {
        std::cout << "Exception textProxy is null" << std::endl;
        return FontAlignmentCenter;
    }
    return textProxy->GetFontLineAlignment();
}

// TODO Throw exception if textProxy is null
FontAlignment Text2::GetFontAlignment()
{
    if(textProxy == nullptr)
    {
        std::cout << "Exception textProxy is null" << std::endl;
        return FontAlignmentCenter;
    }
    return textProxy->GetFontAlignment();
}

void Text2::SetText(const std::wstring &text)
{
    if(textProxy == nullptr)
        return;
    textProxy->SetText(text);
}

Text2::Text2(UiElement *associatedElement)
{
    parentElement = associatedElement;
    associatedElement->AddOnMountedSubscriber(*this);
    associatedElement->AddOnMoveSubscriber(*this);
}

Text2::~Text2()
{
    this->parentElement->RemoveOnMountedSubscriber(*this);
    this->parentElement->RemoveOnMoveSubscriber(*this);
}
