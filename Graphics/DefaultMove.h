#pragma once
#include "MoveSubscriber.h"
#include <Windows.h>
#include <gdiplus.h>
#include "EventMoveInfo.h"
#include <vector>
#include "MultiTree.h"
#include "Adjustable.h"


template<class T>
class DefaultMove : public Movable
{
private:
	std::vector<std::reference_wrapper<MoveSubscriber>> moveSubscribers;
	Gdiplus::Point absolutePosition;
	Gdiplus::Point relativePosition;
	T associatedAdjustable;

public:
	DefaultMove(T component);
	void CalculateAbsolutePosition();
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void NotifyOnMoveSubscribers(EventMoveInfo event) override;
	virtual Gdiplus::Point GetPosition() override;
	virtual int GetX() override;
	virtual int GetY() override;
	virtual void SetPosition(Gdiplus::Point position) override;
	virtual void SetPosition(int x, int y) override;
	virtual void SetX(int x) override;
	virtual void SetY(int y) override;
	virtual int GetAbsoluteX() override;
	virtual int GetAbsoluteY() override;
	virtual Gdiplus::Point GetAbsolutePosition() override;
};

template<class T>
DefaultMove<T>::DefaultMove(T adjustable) : associatedAdjustable(adjustable)
{
	absolutePosition = Gdiplus::Point(0, 0);
}

template<class T>
void DefaultMove<T>::CalculateAbsolutePosition()
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

template<class T>
void DefaultMove<T>::AddOnMoveSubscriber(MoveSubscriber& subscriber)
{
	moveSubscribers.push_back(subscriber);
}

template<class T>
void DefaultMove<T>::RemoveOnMoveSubscriber(MoveSubscriber& subscriber)
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

template<class T>
void DefaultMove<T>::NotifyOnMoveSubscribers(EventMoveInfo event)
{
	for (MoveSubscriber& subscriber : moveSubscribers)
		subscriber.OnMove(event);
}

template<class T>
Gdiplus::Point DefaultMove<T>::GetPosition()
{
	return relativePosition;
}

template<class T>
int DefaultMove<T>::GetX()
{
	return relativePosition.X;
}

template<class T>
int DefaultMove<T>::GetY()
{
	return relativePosition.Y;
}

template<class T>
void DefaultMove<T>::SetPosition(Gdiplus::Point position)
{
	relativePosition = position;
	CalculateAbsolutePosition();
	NotifyOnMoveSubscribers(EventMoveInfo(relativePosition));
}

template<class T>
void DefaultMove<T>::SetPosition(int x, int y)
{
	Gdiplus::Point newPoint = Gdiplus::Point(x, y);
	SetPosition(newPoint);
}

template<class T>
void DefaultMove<T>::SetX(int x)
{
	relativePosition.X = x;
	CalculateAbsolutePosition();

	NotifyOnMoveSubscribers(EventMoveInfo(relativePosition));
}

template<class T>
void DefaultMove<T>::SetY(int y)
{
	relativePosition.Y = y;
	CalculateAbsolutePosition();

	NotifyOnMoveSubscribers(EventMoveInfo(relativePosition));
}

template<class T>
int DefaultMove<T>::GetAbsoluteX()
{
	return absolutePosition.X;
}

template<class T>
int DefaultMove<T>::GetAbsoluteY()
{
	return absolutePosition.Y;
}

template<class T>
Gdiplus::Point DefaultMove<T>::GetAbsolutePosition()
{
	return absolutePosition;
}
