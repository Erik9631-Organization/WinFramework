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
	Vector2 absolutePosition;
	Vector2 relativePosition;
	Vector2 translate; // Defines the position within the viewport
	Vector2 childrenTranslate;
	MultiTree<T>& associatedAdjustableNode;

public:
	DefaultMove(MultiTree<T>& component);
	void CalculateAbsolutePosition();
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void NotifyOnMoveSubscribers(EventMoveInfo event) override;
	virtual Vector2 GetPosition() override;
	virtual float GetX() override;
	virtual float GetY() override;
	virtual void SetPosition(Vector2 position) override;
	virtual void SetPosition(float x, float y) override;
	virtual void SetX(float x) override;
	virtual void SetY(float y) override;
	virtual float GetAbsoluteX() override;
	virtual float GetAbsoluteY() override;
	virtual Vector2 GetAbsolutePosition() override;

	virtual void SetTranslate(Vector2 offset) override;
	virtual void SetTranslateX(float x) override;
	virtual void SetTranslateY(float Y) override;

	virtual Vector2 GetTranslate() override;
	virtual float GetTranslateX() override;
	virtual float GetTranslateY() override;

	Vector2 GetChildrenTranslate() const;
	void TranslateChildren(Vector2 translate);
};


template<class T>
Vector2 DefaultMove<T>::GetChildrenTranslate() const
{
	return childrenTranslate;
}

template<class T>
void DefaultMove<T>::TranslateChildren(Vector2 translate)
{
	this->childrenTranslate = translate;
	for (int i = 0; i < associatedAdjustableNode.GetNodeCount(); i++)
        associatedAdjustableNode.Get(i).GetValue().SetTranslate(translate);
}


template<class T>
void DefaultMove<T>::SetTranslate(Vector2 offset)
{
	this->translate = offset;
}
template<class T>
void DefaultMove<T>::SetTranslateX(float x)
{
	this->translate.SetX(x);
}
template<class T>
void DefaultMove<T>::SetTranslateY(float y)
{
	this->translate.SetY(y);
}

template<class T>
Vector2 DefaultMove<T>::GetTranslate()
{
	return translate;
}

template<class T>
float DefaultMove<T>::GetTranslateX()
{
	return translate.GetX();
}

template<class T>
float DefaultMove<T>::GetTranslateY()
{
	return translate.GetY();
}

template<class T>
DefaultMove<T>::DefaultMove(MultiTree<T>& adjustable) : associatedAdjustableNode(adjustable)
{
	absolutePosition = {0, 0};
	translate = {0, 0};
	childrenTranslate = {0, 0};
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
	    absolutePosition.SetX(relativePosition.GetX() + associatedAdjustableNode.GetParent()->GetValue().GetAbsoluteX() + translate.GetX());
	    absolutePosition.SetY(relativePosition.GetY() + associatedAdjustableNode.GetParent()->GetValue().GetAbsoluteY() + translate.GetY());
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
Vector2 DefaultMove<T>::GetPosition()
{
	return relativePosition;
}

template<class T>
float DefaultMove<T>::GetX()
{
	return relativePosition.GetX();
}

template<class T>
float DefaultMove<T>::GetY()
{
	return relativePosition.GetY();
}

template<class T>
void DefaultMove<T>::SetPosition(Vector2 position)
{
	relativePosition = position;
	CalculateAbsolutePosition();
	NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue() ));
}

template<class T>
void DefaultMove<T>::SetPosition(float x, float y)
{
	Vector2 newPoint = {x, y};
	SetPosition(newPoint);
}

template<class T>
void DefaultMove<T>::SetX(float x)
{
	relativePosition.SetX(x);
	CalculateAbsolutePosition();
	NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue()));
}

template<class T>
void DefaultMove<T>::SetY(float y)
{
	relativePosition.SetY(y);
	CalculateAbsolutePosition();

	NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue()));
}

template<class T>
float DefaultMove<T>::GetAbsoluteX()
{
	return absolutePosition.GetX();
}

template<class T>
float DefaultMove<T>::GetAbsoluteY()
{
	return absolutePosition.GetY();
}

template<class T>
Vector2 DefaultMove<T>::GetAbsolutePosition()
{
	return absolutePosition;
}
