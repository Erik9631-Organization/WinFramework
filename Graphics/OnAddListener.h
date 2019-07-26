#pragma once
class Component;

class OnAddListener
{
public:
	virtual void OnAdd(Component & component) = 0;
	OnAddListener();
	~OnAddListener() {};
};

