#pragma once
#include "ActivateSubject.h"

class Activatable : ActivateSubject
{
public:
	virtual void SetActive(bool state) = 0;
	virtual bool IsActive() = 0;
};

