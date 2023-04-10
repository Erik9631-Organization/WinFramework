#pragma once
#include "api/Adjustable.h"
#include "Behavior/UiMoveBehavior.h"
#include "Behavior/DefaultResize.h"
#include "DataTypes/DefaultMultiTree.h"

class UiElement;

class Viewport : public Adjustable
{
private:
	Adjustable& associatedAdjustable;
	DefaultMultiTree<Adjustable*> viewportNode; //For the default behavior

	UiMoveBehavior<Adjustable*> moveBehavior;
	DefaultResize resizeBehavior;

    glm::vec4 absoluteSize{0};
    glm::vec4 absolutePosition{0};
    glm::vec4 internalOffset{0};

	float xMultiplier = 1;
	float yMultiplier = 1;
	float widthMultiplier = 1;
	float heightMultiplier = 1;

private:
	void CalculateAbsolutePosition(glm::vec4 relative);
	void CalculateAbsoluteSize(glm::vec4 size);

public:
	Viewport(Adjustable& adjustable);

	void SetXMultiplier(float x);
	void SetYMultiplier(float y);
	void SetWidthMultiplier(float width);
	void SetHeightMultiplier(float height);
	virtual float GetViewportXMultiplier();
	virtual float GetViewportYMultiplier();
	virtual float GetViewportWidthMultiplier();
	virtual float GetViewportHeightMultiplier();

	virtual int GetViewportAbsoluteWidth();
	virtual int GetViewportAbsoluteHeight();
	virtual glm::vec4 GetViewportAbsoluteSize();

	// Inherited via Movable
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void NotifyOnMoveSubscribers(EventMoveInfo event) override;
	virtual glm::vec4 GetPosition() override;
	virtual float GetX() override;
	virtual float GetY() override;
	virtual float GetAbsoluteX() override;
	virtual float GetAbsoluteY() override;
	virtual const glm::vec4 & GetAbsolutePosition() override;
	virtual void SetPosition(glm::vec4 position, bool emit) override;
	virtual void SetPosition(float x, float y, float z, float w, bool emit) override;
	virtual void SetX(float x, bool emit) override;
	virtual void SetY(float y, bool emit) override;

	// Inherited via Resizable
	virtual void NotifyOnResizeSubscribers(EventResizeInfo event) override;
	virtual void AddOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual const glm::vec4 & GetSize() override;
	virtual float GetWidth() override;
	virtual float GetHeight() override;
	virtual void SetSize(glm::vec4 size, bool emit) override;
	virtual void SetSize(float width, float height, bool emit) override;
	virtual void SetWidth(float width, bool emit) override;
	virtual void SetHeight(float height, bool emit) override;

	// Inherited via Adjustable
	virtual void OnUpdate(EventUpdateInfo e) override;


	// Inherited via Adjustable
	virtual void SetTranslate(glm::vec4 offset, bool emit) override;

	virtual void SetTranslateX(float x, bool emit) override;

	virtual void SetTranslateY(float y, bool emit) override;

	virtual glm::vec4 GetTranslate() override;

	virtual float GetTranslateX() override;

	virtual float GetTranslateY() override;

    void SetPosition(glm::vec4 position) override;

    void SetPosition(float x, float y, float z, float w) override;

    void SetX(float x) override;

    void SetY(float y) override;

    void SetTranslate(glm::vec4 offset) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y) override;

    void SetSize(glm::vec4 size) override;

    void SetSize(float width, float height) override;

    void SetWidth(float width) override;

    void SetHeight(float height) override;

    float GetZ() override;

    float GetW() override;

    void SetZ(float z, bool emit) override;

    void SetZ(float z) override;

    void SetW(float w, bool emit) override;

    void SetW(float w) override;

};

