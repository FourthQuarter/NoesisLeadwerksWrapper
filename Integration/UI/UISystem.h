/*********************************************************************************
*	The MIT License(MIT)
*
*	Copyright © 2014, Bryan Andrew King
*	All rights reserved.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*	of this software and associated documentation files(the "Software"), to deal
*	in the Software without restriction, including without limitation the rights
*	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
*	copies of the Software, and to permit persons to whom the Software is
*	furnished to do so, subject to the following conditions :
*
*	The above copyright notice and this permission notice shall be included in all
*	copies or substantial portions of the Software.
*
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*	SOFTWARE.
**********************************************************************************/
#ifndef UI_SYSTEM_H
#define UI_SYSTEM_H

#include <Leadwerks.h>

class UIRenderer;

/**
 * \class UISystem
 * \brief Manages all UI related renderers
 * \details Initializes all required noesis components and manages input for the UIRenderers.
 */
class UISystem
{
private:
	std::vector<UIRenderer*>	msListener;	///< Mouse listeners
	std::vector<UIRenderer*>	kbListener; ///< Keyboard listeners
	int							currentUID; ///< Current unique id
	
	// Keyboard input
	char						deadKey; ///< Last found deadkey
	
	/**
	 * \brief Convert Leadwerks V-Key to Noesis compatible key-code
	 * \return Noesis compatible key-code
	 */
	int							ConvertKey(const int key);

	/**
	* \brief Convert Leadwerks mouse-key to Noesis compatible key-code
	* \return Noesis compatible key-code
	*/
	int							ConvertMouseKey(const int key);

	/**
	 * \brief Converts a vkey to an ascii code
	 * \return Ascii code
	 */
	int							KeyToText(const int vkey);

	// Mouse input
	bool						msbuttondown[5]; ///< Keydown state for all mouse buttons
	Leadwerks::Vec3				mspos; ///< Mouse position
	
	double						lastMsWheelPos; 
	double						curMsWheelPos;
	double						msWheelPos;

	static bool					stencilEnabled;
public:
	/**
	 * \brief Initializes noesis.
	 */
	UISystem();
	~UISystem();

	/**
	 * \brief Generates a new unique id
	 * \return id
	 */
	int						GenerateUID();

	/**
	 * \brief Registers a listener for keyboard input events
	 * \warning The specified renderer must have an unique id assigned
	 * \param[in] uiRenderer Listener
	 */
	void					AddKeyboardListener(UIRenderer* &uiRenderer);

	/**
	 * \brief Registers a listener for mouse input events
	 * \warning The specified renderer must have an unique id assigned
	 * \param[in] uiRenderer Listener
	 */
	void					AddMouseListener(UIRenderer* &uiRenderer);

	/**
	 * \brief Removes a listener for keyboard input events
	 * \param[in] uid	The uid of the renderer that will be removed
	 */
	void					RemoveKeyboardListener(const int uid);

	/**
	 * \brief Removes a listener for mouse input events
	 * \param[in] uid	The uid of the renderer that will be removed
	 */
	void					RemoveMouseListener(const int uid);

	/**
	 * \brief Capture keyboard input
	 */
	void					CaptureKeyboard();

	/**
	 * \brief Capture mouse input
	 */
	void					CaptureMouse();

	/**
	 * \brief Capture Keyboard and mouse input
	 */
	void					Capture();

	/**
	 * \brief Enables Leadwerks stencil support
	 * \warning Must be called before context creation!
	 */
	static void				EnableStencil();
};

#endif//UI_SYSTEM_H