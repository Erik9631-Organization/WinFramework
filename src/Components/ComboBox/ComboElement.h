#pragma once
#include "Events/MouseStateSubject.h"
#include "Events/MouseStateSubscriber.h"
#include <string>
#include <vector>
#include <condition_variable>
#include <thread>
#include <any>

class Button;
class ComboSelection;

class ComboElement : public MouseStateSubscriber, public MouseStateSubject
{
private:
	std::wstring text;
	std::any value;
	Button* elementGui;
	ComboSelection& comboSelection;
	std::vector<std::reference_wrapper<MouseStateSubscriber>> comboBoxStateSubscribers;
	bool isSelected = false;
	std::mutex* deleteSyncMutex;
	std::condition_variable* deleteSync;
	bool eventSentSignalContinue = true;
	std::thread::id eventThreadId;

public:
	ComboElement(ComboSelection& comboSelection, std::wstring displayText, std::any value);
	std::wstring GetText();
	std::any GetValue();
	void SetText(std::wstring text);

	void DisplayElementGui();
	void RemoveElementGui();

	bool IsSelected();
	void SetSelected(bool selected);
	

	// Inherited via MouseStateSubject
	virtual void NotifyOnMouseDown(EventMouseStateInfo e) override;

	virtual void NotifyOnMouseUp(EventMouseStateInfo e) override;

	virtual void NotifyOnMousePressed(EventMouseStateInfo e) override;

	virtual void NotifyOnMouseHover(EventMouseStateInfo e) override;

	virtual void NotifyOnMouseEnter(EventMouseStateInfo e) override;

	virtual void NotifyOnMouseLeave(EventMouseStateInfo e) override;

	virtual void AddMouseStateSubscriber(MouseStateSubscriber& subscriber) override;

	virtual void RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber) override;

	virtual bool HasMouseEntered() override;


	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override;

	virtual void OnMouseUp(EventMouseStateInfo e) override;

	virtual void OnMousePressed(EventMouseStateInfo e) override;

	virtual void OnMouseMove(EventMouseStateInfo e) override;

	virtual void OnMouseEntered(EventMouseStateInfo e) override;

	virtual void OnMouseLeft(EventMouseStateInfo e) override;

    void NotifyOnMouseCapture(EventMouseStateInfo e) override;

    bool IsMouseCaptured() override;

    void OnMouseCaptured(EventMouseStateInfo e) override;

};

