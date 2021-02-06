#pragma once
#include "MoveSubscriber.h"
#include <vector>
#include "MultiTree.h"
#include "Adjustable.h"
class Component;

class DefaultMove : public Movable
{
private:
	std::vector<std::reference_wrapper<MoveSubscriber>> moveSubscribers;
	Gdiplus::Point absolutePosition;
	Gdiplus::Point relativePosition;
	MultiTree<Adjustable&>& associatedAdjustable;

public:
	DefaultMove(MultiTree<Adjustable&>& component);
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

