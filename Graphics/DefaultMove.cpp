#include "DefaultMove.h"
#include "EventMoveInfo.h";
#include "CoreWindowFrame.h";
#include "Component.h"
#include "DefaultMultiTree.h"
#include "EventUpdateInfo.h"

/*
* REFACTORING NOTE:
* Use associatedComponent.GetParent() == nullptr, instead of associatedComponent.GetParent() != nullptr && !associatedComponent.IsRoot()
* Easier to read
*/

DefaultMove::DefaultMove(MultiTree<Adjustable&>& component) : associatedAdjustable(component)
{
    absolutePosition = Gdiplus::Point(0, 0);
}

void DefaultMove::CalculateAbsolutePosition()
{
    if (associatedAdjustable.IsRoot() || associatedAdjustable.GetParent()->IsRoot()) //If the parent is root, we are in the global windowSpace and relative is same as absolute
    {
        absolutePosition = relativePosition;
    }
    else
    {
        absolutePosition.X = relativePosition.X + associatedAdjustable.GetParent()->GetValue().GetAbsoluteX();
        absolutePosition.Y = relativePosition.Y + associatedAdjustable.GetParent()->GetValue().GetAbsoluteY();
    }
}

void DefaultMove::AddOnMoveSubscriber(MoveSubscriber& subscriber)
{
    moveSubscribers.push_back(subscriber);
}

void DefaultMove::RemoveOnMoveSubscriber(MoveSubscriber& subscriber)
{
    for (std::vector<std::reference_wrapper<MoveSubscriber>>::iterator i = moveSubscribers.begin(); i != moveSubscribers.end(); i++)
    {
        if (&i->get() == &subscriber)
        {
            moveSubscribers.erase(i);
            return;
        }
    }
}

void DefaultMove::NotifyOnMoveSubscribers(EventMoveInfo event)
{
    for (MoveSubscriber& subscriber : moveSubscribers)
        subscriber.OnMove(event);
}

Gdiplus::Point DefaultMove::GetPosition()
{
    return relativePosition;
}

int DefaultMove::GetX()
{
    return relativePosition.X;
}

int DefaultMove::GetY()
{
    return relativePosition.Y;
}

void DefaultMove::SetPosition(Gdiplus::Point position)
{
    relativePosition = position;
    CalculateAbsolutePosition();
    NotifyOnMoveSubscribers(EventMoveInfo(relativePosition));
}

void DefaultMove::SetPosition(int x, int y)
{
    Gdiplus::Point newPoint = Gdiplus::Point(x, y);
    SetPosition(newPoint);
}

void DefaultMove::SetX(int x)
{
    relativePosition.X = x;
    CalculateAbsolutePosition();

    NotifyOnMoveSubscribers(EventMoveInfo(relativePosition));
}

void DefaultMove::SetY(int y)
{
    relativePosition.Y = y;
    CalculateAbsolutePosition();

    NotifyOnMoveSubscribers(EventMoveInfo(relativePosition));
}

int DefaultMove::GetAbsoluteX()
{
    return absolutePosition.X;
}

int DefaultMove::GetAbsoluteY()
{
    return absolutePosition.Y;
}

Gdiplus::Point DefaultMove::GetAbsolutePosition()
{
    return absolutePosition;
}
