#pragma once
#include "Events/MoveSubscriber.h"
#include <Windows.h>
#include <gdiplus.h>
#include "EventTypes/EventMoveInfo.h"
#include <vector>
#include "DataTypes/MultiTree.h"
#include "api/Adjustable.h"
#include "../GenericObj.h"

/**
 * T has to be of pointer type
 */
template<class T>
class DefaultMove : public Movable
{
private:
	std::vector<std::reference_wrapper<MoveSubscriber>> moveSubscribers;
    glm::vec2 absolutePosition;
    glm::vec2 relativePosition;
    glm::vec2 translate; // Defines the position within the viewport
    glm::vec2 childrenTranslate;
	MultiTree<T>& associatedAdjustableNode;

public:
	DefaultMove(MultiTree<T>& component);
	void CalculateAbsolutePosition();
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void NotifyOnMoveSubscribers(EventMoveInfo event) override;
	virtual glm::vec2 GetPosition() override;
	virtual float GetX() override;
	virtual float GetY() override;
	virtual void SetPosition(const glm::vec2 &position) override;
	virtual void SetPosition(float x, float y) override;
	virtual void SetX(float x) override;
	virtual void SetY(float y) override;
	virtual float GetAbsoluteX() override;
	virtual float GetAbsoluteY() override;
	virtual glm::vec2 GetAbsolutePosition() override;

	virtual void SetTranslate(const glm::vec2 &offset) override;
	virtual void SetTranslateX(float x) override;
	virtual void SetTranslateY(float Y) override;

	virtual glm::vec2 GetTranslate() override;
	virtual float GetTranslateX() override;
	virtual float GetTranslateY() override;

	glm::vec2 GetChildrenTranslate() const;
	void TranslateChildren(const glm::vec2 &translate);
};


template<class T>
glm::vec2 DefaultMove<T>::GetChildrenTranslate() const
{
	return childrenTranslate;
}

template<class T>
void DefaultMove<T>::TranslateChildren(const glm::vec2 &translate)
{
	this->childrenTranslate = translate;
	for (int i = 0; i < associatedAdjustableNode.GetNodeCount(); i++)
        associatedAdjustableNode.Get(i)->SetTranslate(translate);
}


template<class T>
void DefaultMove<T>::SetTranslate(const glm::vec2 &offset)
{
	this->translate = offset;
}
template<class T>
void DefaultMove<T>::SetTranslateX(float x)
{
	this->translate.x = x;
}
template<class T>
void DefaultMove<T>::SetTranslateY(float y)
{
	this->translate.y = y;
}

template<class T>
glm::vec2 DefaultMove<T>::GetTranslate()
{
	return translate;
}

template<class T>
float DefaultMove<T>::GetTranslateX()
{
    return translate.x;
}

template<class T>
float DefaultMove<T>::GetTranslateY()
{
	return translate.y;
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
	if (associatedAdjustableNode.IsRoot() || associatedAdjustableNode.GetParentNode()->IsRoot()) //If the parent is root, we are in the global windowSpace and relative is same as absolute
	{
		absolutePosition = relativePosition + translate;
	}
	else
	{
	    absolutePosition.x = relativePosition.x + associatedAdjustableNode.GetParent()->GetAbsoluteX() + translate.x;
	    absolutePosition.y = relativePosition.y + associatedAdjustableNode.GetParent()->GetAbsoluteY() + translate.y;
	}
}

template<class T>
void DefaultMove<T>::AddOnMoveSubscriber(MoveSubscriber& subscriber)
{
	moveSubscribers.emplace_back(subscriber);
}

template<class T>
void DefaultMove<T>::RemoveOnMoveSubscriber(MoveSubscriber& subscriber)
{
	for (auto i = moveSubscribers.begin(); i != moveSubscribers.end(); i++)
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
glm::vec2 DefaultMove<T>::GetPosition()
{
	return relativePosition;
}

template<class T>
float DefaultMove<T>::GetX()
{
	return relativePosition.x;
}

template<class T>
float DefaultMove<T>::GetY()
{
	return relativePosition.y;
}

template<class T>
void DefaultMove<T>::SetPosition(const glm::vec2 &position)
{
	relativePosition = position;
	CalculateAbsolutePosition();
	NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue() ));
}

template<class T>
void DefaultMove<T>::SetPosition(float x, float y)
{
    glm::vec2 newPoint = {x, y};
	SetPosition(newPoint);
}

template<class T>
void DefaultMove<T>::SetX(float x)
{
	relativePosition.x = x;
	CalculateAbsolutePosition();
	NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue()));
}

template<class T>
void DefaultMove<T>::SetY(float y)
{
	relativePosition.y = y;
	CalculateAbsolutePosition();

	NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue()));
}

template<class T>
float DefaultMove<T>::GetAbsoluteX()
{
	return absolutePosition.x;
}

template<class T>
float DefaultMove<T>::GetAbsoluteY()
{
	return absolutePosition.y;
}

template<class T>
glm::vec2 DefaultMove<T>::GetAbsolutePosition()
{
	return absolutePosition;
}
