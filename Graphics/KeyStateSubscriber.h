#pragma 
class KeyStateInfo;

class KeyStateSubscriber
{
	virtual void OnKeyDown(KeyStateInfo e) = 0;
	virtual void OnKeyUp(KeyStateInfo e) = 0;
	virtual void OnKeyPressed(KeyStateInfo e) = 0;
};

