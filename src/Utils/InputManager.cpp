#include "InputManager.h"
#include "Components/CoreWindow.h"

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

bool InputManager::IsKeyDown(unsigned int key)
{
    if (keyboardState[key] & 128)
        return true;
    return false;
}

bool InputManager::IsKeyDown(VirtualKeys key)
{
    return IsKeyDown((unsigned int)key);
}

bool InputManager::IsKeyUp(VirtualKeys key)
{
    return IsKeyUp((unsigned int)key);
}

bool InputManager::IsKeyUp(unsigned int key)
{
    if (! (keyboardState[key] & 128))
        return true;
    return false;
}
