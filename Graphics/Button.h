#pragma once
#include "Component.h"
#include "Border.h"
class Animation;
class Button : public Component
{
	/*TODO
	 - Border should be notified of any changes to size or position
	 - Animation should be an abstract type accepting graphics and should do a transition;
	*/
private:
	//void SetBackgroundColor(COLORREF color);
	//void SetFont(Font font);
	Pen* pen;
	Border* border;
	//Animation animation;
public:
	void Paint(Graphics& g) override;
	Button(int x, int y, int width, int height);
	void SetBorderStyle(Border* border);
	void SetBorderColor(COLORREF color);
	void SetBorderThickness(float thickness);
	~Button();
};

