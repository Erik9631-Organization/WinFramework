#pragma once
#include "MoveSubscriber.h"
#include "EventMoveInfo.h"
#include <vector>
#include <iostream>
#include "MultiTree.h"
#include "Adjustable.h"
#include "GenericObj.h"
#include "DefaultRelativeZIndex.h"

//TODO event move info sends relative position, not absolute position

/**
 * T has to be of pointer type
 */
template<class T>
class UiMoveBehavior : public Movable
{
private:
	std::vector<std::reference_wrapper<MoveSubscriber>> moveSubscribers;
    glm::vec3 absolutePosition{0, 0, 0};
    glm::vec3 relativePosition{0, 0, 0};
    glm::vec3 translate{0, 0, 0}; // Defines the viewPortSize within the viewport
    glm::vec3 childrenTranslate{0, 0, 0};
	MultiTree<T>& associatedAdjustableNode;

    template <typename T>
    struct IsSmartPtr : std::false_type {};

    template <typename T>
    struct IsSmartPtr<std::unique_ptr<T>> : std::true_type {};

    template <typename T>
    struct IsSmartPtr<std::shared_ptr<T>> : std::true_type {};

    template <typename T>
    static constexpr bool isSmartPtr = IsSmartPtr<T>::value;

public:
    UiMoveBehavior(MultiTree<T>& component);
	void CalculateAbsolutePosition();
	void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	void NotifyOnMoveSubscribers(const EventMoveInfo &event) override;
	[[nodiscard]] const glm::vec3 & GetPosition() const override;
	void SetPosition(const glm::vec3 &position, bool emit = true) override;
	[[nodiscard]] const glm::vec3 & GetAbsolutePosition() const override;

	void SetTranslate(const glm::vec3 &offset, bool emit = true) override;

	[[nodiscard]] const glm::vec3 & GetTranslate() const override;

	[[nodiscard]] const glm::vec3 & GetChildrenTranslate() const;
	void TranslateChildren(glm::vec4 translate);
};

template<class T>
void UiMoveBehavior<T>::NotifyOnMoveSubscribers(const EventMoveInfo &event)
{
    for (MoveSubscriber& subscriber : moveSubscribers)
        subscriber.OnMove(event);

    auto nonSourceEvent = EventMoveInfo{GetPosition(), GetAbsolutePosition(), this, false};
    for (int i = 0; i < associatedAdjustableNode.GetNodeCount(); i++)
        associatedAdjustableNode.Get(i)->NotifyOnMoveSubscribers(nonSourceEvent);

}

template<class T>
const glm::vec3 & UiMoveBehavior<T>::GetChildrenTranslate() const
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
void UiMoveBehavior<T>::SetTranslate(const glm::vec3 &offset, bool emit)
{
    translate = offset;
    CalculateAbsolutePosition();
    if(emit)
        NotifyOnMoveSubscribers({GetPosition(), GetAbsolutePosition(), this});
}

template<class T>
const glm::vec3 & UiMoveBehavior<T>::GetTranslate() const
{
	return translate;
}


template<class T>
UiMoveBehavior<T>::UiMoveBehavior(MultiTree<T>& adjustable) : associatedAdjustableNode(adjustable)
{

}

template<class T>
void UiMoveBehavior<T>::CalculateAbsolutePosition()
{
	if (associatedAdjustableNode.IsRoot()) //If the parent is root, we are in the global windowSpace and relative is same as absolute
	{
		absolutePosition = relativePosition + translate;
	}
	else
	{
        auto zGap = static_cast<float>(DefaultRelativeZIndex::GetInstance()->GetIndex("zGap"));
        glm::vec3 parentPos = associatedAdjustableNode.GetParent()->GetAbsolutePosition();
	    absolutePosition.x = relativePosition.x + parentPos.x + translate.x;
	    absolutePosition.y = relativePosition.y + parentPos.y + translate.y;
        absolutePosition.z = relativePosition.z + parentPos.z - zGap + translate.z;

    }
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
const glm::vec3 & UiMoveBehavior<T>::GetPosition() const
{
	return relativePosition;
}

template<class T>
void UiMoveBehavior<T>::SetPosition(const glm::vec3 &position, bool emit)
{
	relativePosition = position;
	CalculateAbsolutePosition();
    if(emit)
    {
        auto event = EventMoveInfo{relativePosition, absolutePosition, this};
        NotifyOnMoveSubscribers(event);
    }

}

template<class T>
const glm::vec3 & UiMoveBehavior<T>::GetAbsolutePosition() const
{
	return absolutePosition;
}

