//========= Copyright © 2014, Bryan Andrew King, All rights reserved. ============
#include "InputSystem.h"
#include <sstream>

InputSystem::InputSystem(const size_t &hwnd) : inputSystem(NULL), keyboard(NULL), mouse(NULL)
{
	OIS::ParamList		paramList;
	std::ostringstream	hwndStr;

	hwndStr << (unsigned int)hwnd;
	paramList.insert(std::make_pair(std::string("WINDOW"), hwndStr.str()));

	// Create a non-exclusive mouse to prevent interruptions with leadwerks
	paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

	inputSystem = OIS::InputManager::createInputSystem(paramList);

	// Create keyboard input device
	if (inputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0)
	{
		keyboard = static_cast<OIS::Keyboard*>(inputSystem->createInputObject(OIS::OISKeyboard, true));
	}
	else
	{
		printf("\InputSystem: NO KEYBOARD FOUND\n");
	}

	// Create mouse input device
	if (inputSystem->getNumberOfDevices(OIS::OISMouse) > 0)
	{
		mouse = static_cast<OIS::Mouse*>(inputSystem->createInputObject(OIS::OISMouse, true));
	}
	else
	{
		printf("\InputSystem: NO MOUSE FOUND\n");
	}
}

InputSystem::~InputSystem()
{
	if (keyboard)
	{
		inputSystem->destroyInputObject(keyboard);
		keyboard = nullptr;
	}

	if (mouse)
	{
		inputSystem->destroyInputObject(mouse);
		mouse = nullptr;
	}

	OIS::InputManager::destroyInputSystem(inputSystem);
	inputSystem = nullptr;
}

void InputSystem::SetKeyboardListener(OIS::KeyListener* listener)
{
	keyboard->setEventCallback(listener);
}

void InputSystem::SetMouseListener(OIS::MouseListener* listener)
{
	mouse->setEventCallback(listener);
}

void InputSystem::CaptureKeyboard()
{
	keyboard->capture();
}

void InputSystem::CaptureMouse()
{
	mouse->capture();
}

void InputSystem::Capture()
{
	keyboard->capture();
	mouse->capture();
}

void InputSystem::SetDisplayAreaSize(const int x, const int y)
{
	const OIS::MouseState &mouseState = mouse->getMouseState();
	mouseState.width = x;
	mouseState.height = y;
}