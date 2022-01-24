#pragma once
#include "Events/MoveSubscriber.h"
#include <Windows.h>
#include <gdiplus.h>
#include "EventTypes/EventMoveInfo.h"
#include <vector>
#include "DataTypes/MultiTree.h"
#include "Components/Adjustable.h"
#include "../GenericObj.h"


template<class T>
class DefaultMove : public Movable
{
private:
	std::vector<std::reference_wrapper<MoveSubscriber>> moveSubscribers;
	Gdiplus::Point absolutePosition;
	Gdiplus::Point relativePosition;
	Gdiplus::Point translate; // Defines the position within the viewport
	Gdiplus::Point childrenTranslate;
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

	virtual void SetTranslate(Gdiplus::Point offset) override;
	virtual void SetTranslateX(int x) override;
	virtual void SetTranslateY(int Y) override;

	virtual Gdiplus::Point GetTranslate() override;
	virtual int GetTranslateX() override;
	virtual int GetTranslateY() override;

	Gdiplus::Point GetChildrenTranslate();
	void TranslateChildren(Gdiplus::Point translate);
};


template<class T>
Gdiplus::Point DefaultMove<T>::GetChildrenTranslate()
{
	return childrenTranslate;
}

template<class T>
void DefaultMove<T>::TranslateChildren(Gdiplus::Point translate)
{
	this->childrenTranslate = translate;
	for (int i = 0; i < associatedAdjustableNode.GetNodeCount(); i++)
        associatedAdjustableNode.Get(i).GetValue().SetTranslate(translate);
}


template<class T>
void DefaultMove<T>::SetTranslate(Gdiplus::Point offset)
{
	this->translate = offset;
}
template<class T>
void DefaultMove<T>::SetTranslateX(int x)
{
	this->translate.X = x;
}
template<class T>
void DefaultMove<T>::SetTranslateY(int y)
{
	this->translate.Y = y;
}

template<class T>
Gdiplus::Point DefaultMove<T>::GetTranslate()
{
	return translate;
}

template<class T>
int DefaultMove<T>::GetTranslateX()
{
	return translate.X;
}

template<class T>
int DefaultMove<T>::GetTranslateY()
{
	return translate.Y;
}

template<class T>
DefaultMove<T>::DefaultMove(MultiTree<T>& adjustable) : associatedAdjustableNode(adjustable)
{
	absolutePosition = Gdiplus::Point(0, 0);
    translate = Gdiplus::Point(0, 0);
    childrenTranslate = Gdiplus::Point(0, 0);
}

template<class T>
void DefaultMove<T>::CalculateAbsolutePosition()
{
	if (associatedAdjustableNode.IsRoot() || associatedAdjustableNode.GetParent()->IsRoot()) //If the parent is root, we are in the global windowSpace and relative is same as absolute
	{
		absolutePosition = relativePosition + translate;
	}
	else
	{
		absolutePosition.X = relativePosition.X + associatedAdjustableNode.GetParent()->GetValue().GetAbsoluteX() + translate.X;
		absolutePosition.Y = relativePosition.Y + associatedAdjustableNode.GetParent()->GetValue().GetAbsoluteY() + translate.Y;
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
