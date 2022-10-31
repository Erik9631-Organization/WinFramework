#include "InputManager.h"
#include "Components/WindowsCore.h"
std::unique_ptr<InputManager> InputManager::globalInput = std::make_unique<InputManager>();


InputManager::InputManager(BYTE* keyboardState)
{
    memcpy(this->keyboardState, keyboardState, 256);
}

InputManager::InputManager()
{
    memset(keyboardState, 0, 256);
}

void InputManager::SetKeyboardState(BYTE* keyboardState)
{
    memcpy(this->keyboardState, keyboardState, 256);
}

const bool& InputManager::IsKeyDown(unsigned int key) const
{
    if (keyboardState[key] & 128)
        return true;
    return false;
}

const bool& InputManager::IsKeyDown(VirtualKeys key) const
{
    return IsKeyDown((unsigned int)key);
}

const bool& InputManager::IsKeyUp(VirtualKeys key) const
{
    return IsKeyUp((unsigned int)key);
}

const InputManager &InputManager::GetGlobalInput()
{
    return *globalInput;
}

const bool& InputManager::IsKeyUp(unsigned int key) const
{
    if (! (keyboardState[key] & 128))
        return true;
    return false;
}

const Vector2 & InputManager::GetMouseDelta() const
{
    return mouseDelta;
}

const Vector2 & InputManager::GetMouseScreenPosition() const
{
    return mouseScreenPosition;
}

const Vector2 & InputManager::GetMousePosition() const
{
    return mousePosition;
}

void InputManager::SetMousePosition(const Vector2 &mousePosition)
{
    this->mousePosition = mousePosition;
}

void InputManager::SetMouseScreenPosition(const Vector2 &mousePosition)
{
    this->mouseScreenPosition = mousePosition;
}

void InputManager::SetMouseDeltaPosition(const Vector2 &mousePosition)
{
    this->mouseDelta = mousePosition;
    mouseDelta.Normalize();
}
