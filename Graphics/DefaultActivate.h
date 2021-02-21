#pragma once
#include "Activatable.h"
#include <vector>

class DefaultActivate : public Activatable
{
private:
	bool state = false;
	std::vector<std::reference_wrapper<ActivateSubscriber>> subscribers;

public:
	virtual void AddOnActivateSubscriber(ActivateSubscriber& subscriber) override;
	virtual void RemoveOnActivateSubscriber(ActivateSubscriber& subscriber) override;
	virtual void SetActive(bool state) override;
	virtual bool IsActive() override;
	virtual void NotifyOnActivateStateChanged(EventOnActivateInfo& activateInfo) override;
};


