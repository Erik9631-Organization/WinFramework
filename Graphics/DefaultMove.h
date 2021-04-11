#pragma once
#include "MoveSubscriber.h"
#include <Windows.h>
#include <gdiplus.h>
#include "EventMoveInfo.h"
#include <vector>
#include "MultiTree.h"
#include "Adjustable.h"
#include "GenericObj.h"


template<class T>
class DefaultMove : public Movable
{
private:
	std::vector<std::reference_wrapper<MoveSubscriber>> moveSubscribers;
	Gdiplus::Point absolutePosition;
	Gdiplus::Point relativePosition;
	Gdiplus::Point offset; // Defines the offset within the viewport
	Gdiplus::Point internalOffset;
	MultiTree<T>& associatedAdjustableNode;

public:
	DefaultMove(MultiTree<T>& component);
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

	virtual void SetElementOffset(Gdiplus::Point offset) override;
	virtual void SetElementXOffset(int x) override;
	virtual void SetElementYOffset(int Y) override;

	virtual Gdiplus::Point GetElementOffset() override;
	virtual int GetElementXOffset() override;
	virtual int GetElementYOffset() override;

	Gdiplus::Point GetInternalOffset();
	void SetInternalOffset(Gdiplus::Point internalOffset);
};


template<class T>
Gdiplus::Point DefaultMove<T>::GetInternalOffset()
{
	return internalOffset;
}

template<class T>
void DefaultMove<T>::SetInternalOffset(Gdiplus::Point internalOffset)
{
	this->internalOffset = internalOffset;
	for (int i = 0; i < associatedAdjustableNode.GetNodeCount(); i++)
		associatedAdjustableNode.Get(i).GetValue().SetElementOffset(internalOffset);
}


template<class T>
void DefaultMove<T>::SetElementOffset(Gdiplus::Point offset)
{
	this->offset = offset;
}
template<class T>
void DefaultMove<T>::SetElementXOffset(int x)
{
	this->offset.X = x;
}
template<class T>
void DefaultMove<T>::SetElementYOffset(int y)
{
	this->offset.Y = y;
}

template<class T>
Gdiplus::Point DefaultMove<T>::GetElementOffset()
{
	return offset;
}

template<class T>
int DefaultMove<T>::GetElementXOffset()
{
	return offset.X;
}

template<class T>
int DefaultMove<T>::GetElementYOffset()
{
	return offset.Y;
}

template<class T>
DefaultMove<T>::DefaultMove(MultiTree<T>& adjustable) : associatedAdjustableNode(adjustable)
{
	absolutePosition = Gdiplus::Point(0, 0);
	offset = Gdiplus::Point(0, 0);
	internalOffset = Gdiplus::Point(0, 0);
}

template<class T>
void DefaultMove<T>::CalculateAbsolutePosition()
{
	if (associatedAdjustableNode.IsRoot() || associatedAdjustableNode.GetParent()->IsRoot()) //If the parent is root, we are in the global windowSpace and relative is same as absolute
	{
		absolutePosition = relativePosition + offset;
	}
	else
	{
		absolutePosition.X = relativePosition.X + associatedAdjustableNode.GetParent()->GetValue().GetAbsoluteX() + offset.X;
		absolutePosition.Y = relativePosition.Y + associatedAdjustableNode.GetParent()->GetValue().GetAbsoluteY() + offset.Y;
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
	NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue() ));
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
	NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue()));
}

template<class T>
void DefaultMove<T>::SetY(int y)
{
	relativePosition.Y = y;
	CalculateAbsolutePosition();

	NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue()));
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
