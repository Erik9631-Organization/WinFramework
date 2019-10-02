#pragma once
class ComponentListener
{
public:
	virtual void OnResize() = 0;
	virtual void OnMove() = 0;
	virtual void OnHover() = 0;
	virtual void OnFocus() = 0;
	ComponentListener();
	~ComponentListener();
};

