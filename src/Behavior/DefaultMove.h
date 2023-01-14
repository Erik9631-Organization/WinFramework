#pragma once
#include "Events/MoveSubscriber.h"
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
    glm::vec4 absolutePosition{0};
    glm::vec4 relativePosition{0};
    glm::vec4 translate{0}; // Defines the position within the viewport
    glm::vec4 childrenTranslate{0};
	MultiTree<T>& associatedAdjustableNode;

public:
	DefaultMove(MultiTree<T>& component);
	void CalculateAbsolutePosition();
	void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	void NotifyOnMoveSubscribers(EventMoveInfo event) override;
	glm::vec4 GetPosition() override;
	float GetX() override;
	float GetY() override;
    float GetZ() override ;
    float GetW() override;
	void SetPosition(glm::vec4 position, bool emit) override;
	void SetPosition(float x, float y, float z, float w, bool emit) override;
	void SetX(float x, bool emit) override;
    void SetX(float x) override;
	void SetY(float y, bool emit) override;
    void SetY(float y) override;
    void SetZ(float z, bool emit) override;
    void SetZ(float z) override;
    void SetW(float w, bool emit) override;
    void SetW(float w) override;
	float GetAbsoluteX() override;
	float GetAbsoluteY() override;
	glm::vec4 GetAbsolutePosition() override;

	void SetTranslate(glm::vec4 offset, bool emit) override;
	void SetTranslateX(float x, bool emit) override;
	void SetTranslateY(float Y, bool emit) override;

	glm::vec4 GetTranslate() override;
	float GetTranslateX() override;
	float GetTranslateY() override;

	glm::vec4 GetChildrenTranslate() const;
	void TranslateChildren(glm::vec4 translate);

    void SetPosition(glm::vec4 position) override;

    void SetPosition(float x, float y, float z, float w) override;

    void SetTranslate(glm::vec4 offset) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y) override;
};


template<class T>
glm::vec4 DefaultMove<T>::GetChildrenTranslate() const
{
	return childrenTranslate;
}

template<class T>
void DefaultMove<T>::TranslateChildren(glm::vec4 translate)
{
	this->childrenTranslate = translate;
	for (int i = 0; i < associatedAdjustableNode.GetNodeCount(); i++)
        associatedAdjustableNode.Get(i)->SetTranslate(translate, true);
}


template<class T>
void DefaultMove<T>::SetTranslate(glm::vec4 offset, bool emit)
{
	this->translate = offset;
}
template<class T>
void DefaultMove<T>::SetTranslateX(float x, bool emit)
{
	this->translate.x = x;
}
template<class T>
void DefaultMove<T>::SetTranslateY(float y, bool emit)
{
	this->translate.y = y;
}

template<class T>
glm::vec4 DefaultMove<T>::GetTranslate()
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
	absolutePosition = {0, 0, 0, 0};
	translate = {0, 0, 0, 0};
	childrenTranslate = {0, 0, 0, 0};
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
glm::vec4 DefaultMove<T>::GetPosition()
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
float DefaultMove<T>::GetZ()
{
    return relativePosition.z;
}

template<class T>
float DefaultMove<T>::GetW()
{
    return relativePosition.w;
}

template<class T>
void DefaultMove<T>::SetPosition(glm::vec4 position, bool emit)
{
	relativePosition = position;
	CalculateAbsolutePosition();
    if(emit)
	    NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue() ));
}

template<class T>
void DefaultMove<T>::SetPosition(float x, float y, float z, float w, bool emit)
{
    SetPosition(glm::vec4(x, y, 0, 0), emit);
}

template<class T>
void DefaultMove<T>::SetX(float x, bool emit)
{
	relativePosition.x = x;
	CalculateAbsolutePosition();
    if(emit)
	    NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue()));
}

template<class T>
void DefaultMove<T>::SetX(float x)
{
    SetX(x, true);
}

template<class T>
void DefaultMove<T>::SetY(float y, bool emit)
{
	relativePosition.y = y;
	CalculateAbsolutePosition();
    if(emit)
	    NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue()));
}

template<class T>
void DefaultMove<T>::SetY(float y)
{
    SetY(y, true);
}

template<class T>
void DefaultMove<T>::SetZ(float z, bool emit)
{
    relativePosition.z = z;
    CalculateAbsolutePosition();
    if(emit)
        NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue()));
}

template<class T>
void DefaultMove<T>::SetZ(float z)
{
    SetZ(z, true);
}

template<class T>
void DefaultMove<T>::SetW(float w, bool emit)
{
    relativePosition.w = w;
    CalculateAbsolutePosition();
    if(emit)
        NotifyOnMoveSubscribers(EventMoveInfo(relativePosition, (Movable*)&associatedAdjustableNode.GetValue()));
}

template<class T>
void DefaultMove<T>::SetW(float w)
{
    SetW(w, true);
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
glm::vec4 DefaultMove<T>::GetAbsolutePosition()
{
	return absolutePosition;
}

template<class T>
void DefaultMove<T>::SetPosition(glm::vec4 position)
{
    SetPosition(position, true);
}

template<class T>
void DefaultMove<T>::SetPosition(float x, float y, float z, float w)
{
    SetPosition(x, y, z, w, true);
}

template<class T>
void DefaultMove<T>::SetTranslate(glm::vec4 offset)
{
    SetTranslate(offset, true);
}

template<class T>
void DefaultMove<T>::SetTranslateX(float x)
{
    SetTranslateX(x, true);
}

template<class T>
void DefaultMove<T>::SetTranslateY(float y)
{
    SetTranslateY(y, true);
}
