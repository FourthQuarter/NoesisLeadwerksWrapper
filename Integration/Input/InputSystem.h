//========= Copyright © 2014, Bryan Andrew King, All rights reserved. ============
#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <OIS.h>

/**
 * \class InputSystem
 * \brief Input manager
 * \details OOP input management
 */
class InputSystem
{
private:
	// Input 
	OIS::InputManager*			inputSystem; ///< Input manager
	OIS::Keyboard*				keyboard; ///< Keyboard input source
	OIS::Mouse*					mouse;

public:
	/**
	 * \brief Initializes the input system
	 * \details Creates the inputSystem and keyboad objects.
	 * \param[in] hwnd Current window handle
	 */
	InputSystem(const size_t &hwnd);
	virtual ~InputSystem();

	/**
	 * \brief Registers a listener for keyboard events
	 * \warning Only one listener supported
	 */
	void	SetKeyboardListener(OIS::KeyListener* listener);
	/**
	 * \brief Registers a listener for mouse events
	 * \warning Only one listener supported
	 */
	void	SetMouseListener(OIS::MouseListener* listener);

	/**
	 * \brief Capture keyboard input
	 * \details The listeners will only receive input from the keyboard when this method is called once per frame.
	 */
	void	CaptureKeyboard();

	/**
	* \brief Capture mouse input
	* \details The listeners will only receive input from the mouse when this method is called once per frame.
	*/
	void	CaptureMouse();

	/**
	 * \brief Capture all input
	 * \details The listeners will only receive input when this method is called once per frame.
	 */
	void	Capture();

	/**
	 * \brief Set Width / Height of the display area for mouse input
	 */
	void	SetDisplayAreaSize(const int x, const int y);
};

#endif//INPUT_SYSTEM_H