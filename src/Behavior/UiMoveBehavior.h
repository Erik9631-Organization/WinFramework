#pragma once
#include "Events/MoveSubscriber.h"
#include "EventTypes/EventMoveInfo.h"
#include <vector>
#include "DataTypes/MultiTree.h"
#include "api/Adjustable.h"
#include "../GenericObj.h"
#include "DefaultRelativeZIndex.h"

/**
 * T has to be of pointer type
 */
template<class T>
class UiMoveBehavior : public Movable
{
private:
	std::vector<std::reference_wrapper<MoveSubscriber>> moveSubscribers;
    glm::vec4 absolutePosition{0};
    glm::vec4 relativePosition{0};
    glm::vec4 translate{0}; // Defines the viewPortSize within the viewport
    glm::vec4 childrenTranslate{0};
	MultiTree<T>& associatedAdjustableNode;

    template <typename T>
    struct IsSmartPtr : std::false_type {};

    template <typename T>
    struct IsSmartPtr<std::unique_ptr<T>> : std::true_type {};

    template <typename T>
    struct IsSmartPtr<std::shared_ptr<T>> : std::true_type {};

    template <typename T>
    static constexpr bool isSmartPtr = IsSmartPtr<T>::value;

    void NotifyOnMoveSubscribers(const glm::vec4& position, T& src);

public:
	UiMoveBehavior(MultiTree<T>& component);
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
	const glm::vec4 & GetAbsolutePosition() override;

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
void UiMoveBehavior<T>::NotifyOnMoveSubscribers(const glm::vec4 &position, T& src)
{
    if constexpr (std::is_pointer<T>::value)
        NotifyOnMoveSubscribers(EventMoveInfo(position, dynamic_cast<Movable*>(src)));
    else if constexpr (isSmartPtr<T>)
        NotifyOnMoveSubscribers(EventMoveInfo(position, dynamic_cast<Movable*>(src.get())));
    else
        NotifyOnMoveSubscribers(EventMoveInfo(position, dynamic_cast<Movable*>(&src)));
}

template<class T>
glm::vec4 UiMoveBehavior<T>::GetChildrenTranslate() const
{
	return childrenTranslate;
}

template<class T>
void UiMoveBehavior<T>::TranslateChildren(glm::vec4 translate)
{
	this->childrenTranslate = translate;
	for (int i = 0; i < associatedAdjustableNode.GetNodeCount(); i++)
        associatedAdjustableNode.Get(i)->SetTranslate(translate, true);
}


template<class T>
void UiMoveBehavior<T>::SetTranslate(glm::vec4 offset, bool emit)
{
	this->translate = offset;
}
template<class T>
void UiMoveBehavior<T>::SetTranslateX(float x, bool emit)
{
	this->translate.x = x;
}
template<class T>
void UiMoveBehavior<T>::SetTranslateY(float y, bool emit)
{
	this->translate.y = y;
}

template<class T>
glm::vec4 UiMoveBehavior<T>::GetTranslate()
{
	return translate;
}

template<class T>
float UiMoveBehavior<T>::GetTranslateX()
{
    return translate.x;
}

template<class T>
float UiMoveBehavior<T>::GetTranslateY()
{
	return translate.y;
}

template<class T>
UiMoveBehavior<T>::UiMoveBehavior(MultiTree<T>& adjustable) : associatedAdjustableNode(adjustable)
{
	absolutePosition = {0, 0, 0, 0};
	translate = {0, 0, 0, 0};
	childrenTranslate = {0, 0, 0, 0};
}

template<class T>
void UiMoveBehavior<T>::CalculateAbsolutePosition()
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
    absolutePosition.z *= static_cast<float>(DefaultRelativeZIndex::GetInstance()->GetSize());
}

template<class T>
void UiMoveBehavior<T>::AddOnMoveSubscriber(MoveSubscriber& subscriber)
{
	moveSubscribers.emplace_back(subscriber);
}

template<class T>
void UiMoveBehavior<T>::RemoveOnMoveSubscriber(MoveSubscriber& subscriber)
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
void UiMoveBehavior<T>::NotifyOnMoveSubscribers(EventMoveInfo event)
{
	for (MoveSubscriber& subscriber : moveSubscribers)
		subscriber.OnMove(event);
}

template<class T>
glm::vec4 UiMoveBehavior<T>::GetPosition()
{
	return relativePosition;
}

template<class T>
float UiMoveBehavior<T>::GetX()
{
	return relativePosition.x;
}

template<class T>
float UiMoveBehavior<T>::GetY()
{
	return relativePosition.y;
}

template<class T>
float UiMoveBehavior<T>::GetZ()
{
    return relativePosition.z;
}

template<class T>
float UiMoveBehavior<T>::GetW()
{
    return relativePosition.w;
}

template<class T>
void UiMoveBehavior<T>::SetPosition(glm::vec4 position, bool emit)
{
	relativePosition = position;
	CalculateAbsolutePosition();
    //TODO this is a hack, fix it as get is a unique_ptr
    if(emit)
	    NotifyOnMoveSubscribers(relativePosition, associatedAdjustableNode.GetValue());
}

template<class T>
void UiMoveBehavior<T>::SetPosition(float x, float y, float z, float w, bool emit)
{
    SetPosition({x, y, z, w}, emit);
}

template<class T>
void UiMoveBehavior<T>::SetX(float x, bool emit)
{
	relativePosition.x = x;
	CalculateAbsolutePosition();
    if(emit)
	    NotifyOnMoveSubscribers(relativePosition, associatedAdjustableNode.GetValue());
}

template<class T>
void UiMoveBehavior<T>::SetX(float x)
{
    SetX(x, true);
}

template<class T>
void UiMoveBehavior<T>::SetY(float y, bool emit)
{
	relativePosition.y = y;
	CalculateAbsolutePosition();
    if(emit)
	    NotifyOnMoveSubscribers(relativePosition, associatedAdjustableNode.GetValue());
}

template<class T>
void UiMoveBehavior<T>::SetY(float y)
{
    SetY(y, true);
}

template<class T>
void UiMoveBehavior<T>::SetZ(float z, bool emit)
{
    relativePosition.z = z;
    CalculateAbsolutePosition();
    if(emit)
        NotifyOnMoveSubscribers(relativePosition, associatedAdjustableNode.GetValue());
}

template<class T>
void UiMoveBehavior<T>::SetZ(float z)
{
    SetZ(z, true);
}

template<class T>
void UiMoveBehavior<T>::SetW(float w, bool emit)
{
    relativePosition.w = w;
    CalculateAbsolutePosition();
    if(emit)
        NotifyOnMoveSubscribers(relativePosition, associatedAdjustableNode.GetValue());
}

template<class T>
void UiMoveBehavior<T>::SetW(float w)
{
    SetW(w, true);
}

template<class T>
float UiMoveBehavior<T>::GetAbsoluteX()
{
	return absolutePosition.x;
}

template<class T>
float UiMoveBehavior<T>::GetAbsoluteY()
{
	return absolutePosition.y;
}

template<class T>
const glm::vec4 & UiMoveBehavior<T>::GetAbsolutePosition()
{
	return absolutePosition;
}

template<class T>
void UiMoveBehavior<T>::SetPosition(glm::vec4 position)
{
    SetPosition(position, true);
}

template<class T>
void UiMoveBehavior<T>::SetPosition(float x, float y, float z, float w)
{
    SetPosition(x, y, z, w, true);
}

template<class T>
void UiMoveBehavior<T>::SetTranslate(glm::vec4 offset)
{
    SetTranslate(offset, true);
}

template<class T>
void UiMoveBehavior<T>::SetTranslateX(float x)
{
    SetTranslateX(x, true);
}

template<class T>
void UiMoveBehavior<T>::SetTranslateY(float y)
{
    SetTranslateY(y, true);
}
