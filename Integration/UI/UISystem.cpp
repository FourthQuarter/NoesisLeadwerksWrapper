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
#include "UISystem.h"
#include "UIRenderer.h"

// Neosis
#include <NsCore\Kernel.h>
#include <NsCore\NsSystem.h>
#include <NsCore\NsConfig.h>
#include <NsGui\InputEnums.h>

void NoesisErrorHandler(const NsChar* filename, NsInt line, const NsChar* desc)
{
	// Print error to console
	printf("\n----------------------------------------------------\n");
	printf(" NoesisErrorHandler:\n");
	printf("----------------------------------------------------\n");
	printf("%s", desc);
	printf("\n----------------------------------------------------\n");

	// Display messagebox
#ifdef _WIN32
	MessageBox(0, desc, "NoesisErrorHandler", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif

	exit(EXIT_FAILURE);
}

UISystem::UISystem() : currentUID(1)
{

	Noesis::Core::SetErrorHandler(NoesisErrorHandler);

	// Init kernel
	NsGetKernel()->Init();

	// Select render
	NsConfigValue("Render.RenderSystem", "Render", "GL");

	// Init systems
	NsGetKernel()->InitSystems();

	for (int i = 0; i < 5; i++) msbuttondown[i] = false;
}

UISystem::~UISystem()
{
	kbListener.clear();
	msListener.clear();

	NsGetKernel()->Shutdown();
}

int	UISystem::GenerateUID()
{
	return currentUID++;
}

void UISystem::AddKeyboardListener(UIRenderer* &uiRenderer)
{
	if (uiRenderer->GetUID() > 0)
	{
		kbListener.push_back(uiRenderer);
	}
}

void UISystem::AddMouseListener(UIRenderer* &uiRenderer)
{
	if (uiRenderer->GetUID() > 0)
	{
		msListener.push_back(uiRenderer);
	}
}

void UISystem::RemoveKeyboardListener(const int uid)
{
	for (auto i = kbListener.begin(); i != kbListener.end(); /**/)
	{
		if ((*i)->GetUID() == uid)
		{
			i = kbListener.erase(i);
			break;
		}
		else ++i;
	}
}

void UISystem::RemoveMouseListener(const int uid)
{
	for (auto i = msListener.begin(); i != msListener.end(); /**/)
	{
		if ((*i)->GetUID() == uid)
		{
			i = msListener.erase(i);
			break;
		}
		else ++i;
	}
}

int UISystem::ConvertKey(const int key)
{
	if (key == Leadwerks::Key::Alt) return Noesis::Gui::Key_Alt;
	if (key == Leadwerks::Key::BackSpace) return Noesis::Gui::Key_Back;
	if (key == Leadwerks::Key::CapsLock) return Noesis::Gui::Key_None; // ?
	if (key == Leadwerks::Key::ControlKey) return Noesis::Gui::Key_Control;
	if (key == Leadwerks::Key::Delete) return Noesis::Gui::Key_Delete;
	if (key == Leadwerks::Key::Down) return Noesis::Gui::Key_Down;
	if (key == Leadwerks::Key::End) return Noesis::Gui::Key_End;
	if (key == Leadwerks::Key::Enter) return Noesis::Gui::Key_Return;
	if (key == Leadwerks::Key::Escape) return Noesis::Gui::Key_Escape;
	if (key == Leadwerks::Key::Home) return Noesis::Gui::Key_Home;
	if (key == Leadwerks::Key::Insert) return Noesis::Gui::Key_Insert;
	if (key == Leadwerks::Key::Left) return Noesis::Gui::Key_Left;

	if (key == Leadwerks::Key::NumLock) return Noesis::Gui::Key_NumLock;
	if (key == Leadwerks::Key::PageDown) return Noesis::Gui::Key_None;
	if (key == Leadwerks::Key::PageUp) return Noesis::Gui::Key_None; // ?
	if (key == Leadwerks::Key::RControlKey) return Noesis::Gui::Key_Control;
	if (key == Leadwerks::Key::Right) return Noesis::Gui::Key_Right;
	if (key == Leadwerks::Key::Shift) return Noesis::Gui::Key_Shift;
	if (key == Leadwerks::Key::Space) return Noesis::Gui::Key_Space;
	if (key == Leadwerks::Key::Subtract) return Noesis::Gui::Key_Subtract;
	if (key == Leadwerks::Key::Tab) return Noesis::Gui::Key_Tab;
	if (key == Leadwerks::Key::Up) return Noesis::Gui::Key_Up;

	if (key == Leadwerks::Key::Tilde) return Noesis::Gui::Key_None; // ?
	if (key == Leadwerks::Key::Equals) return Noesis::Gui::Key_None; // ?
	if (key == Leadwerks::Key::OpenBracket) return Noesis::Gui::Key_None; // ?
	if (key == Leadwerks::Key::CloseBracket) return Noesis::Gui::Key_None; // ?
	if (key == Leadwerks::Key::Backslash) return Noesis::Gui::Key_None; // ?
	if (key == Leadwerks::Key::Semicolon) return Noesis::Gui::Key_None; // ?
	if (key == Leadwerks::Key::Quotes) return Noesis::Gui::Key_None; // ?
	if (key == Leadwerks::Key::Comma) return Noesis::Gui::Key_None; // ?
	if (key == Leadwerks::Key::Period) return Noesis::Gui::Key_Decimal;
	if (key == Leadwerks::Key::Slash) return Noesis::Gui::Key_None; // ?
	if (key == Leadwerks::Key::WindowsKey) return Noesis::Gui::Key_None; // ?

	if (key == Leadwerks::Key::F1) return Noesis::Gui::Key_F1;
	if (key == Leadwerks::Key::F2) return Noesis::Gui::Key_F2;
	if (key == Leadwerks::Key::F3) return Noesis::Gui::Key_F3;
	if (key == Leadwerks::Key::F4) return Noesis::Gui::Key_F4;
	if (key == Leadwerks::Key::F5) return Noesis::Gui::Key_F5;
	if (key == Leadwerks::Key::F6) return Noesis::Gui::Key_F6;
	if (key == Leadwerks::Key::F7) return Noesis::Gui::Key_F7;
	if (key == Leadwerks::Key::F8) return Noesis::Gui::Key_F8;
	if (key == Leadwerks::Key::F9) return Noesis::Gui::Key_F9;
	if (key == Leadwerks::Key::F10) return Noesis::Gui::Key_F10;
	if (key == Leadwerks::Key::F11) return Noesis::Gui::Key_F11;
	if (key == Leadwerks::Key::F12) return Noesis::Gui::Key_F12;

	if (key == Leadwerks::Key::A) return Noesis::Gui::Key_A;
	if (key == Leadwerks::Key::B) return Noesis::Gui::Key_B;
	if (key == Leadwerks::Key::C) return Noesis::Gui::Key_C;
	if (key == Leadwerks::Key::D) return Noesis::Gui::Key_D;
	if (key == Leadwerks::Key::E) return Noesis::Gui::Key_E;
	if (key == Leadwerks::Key::F) return Noesis::Gui::Key_F;
	if (key == Leadwerks::Key::G) return Noesis::Gui::Key_G;
	if (key == Leadwerks::Key::H) return Noesis::Gui::Key_H;
	if (key == Leadwerks::Key::I) return Noesis::Gui::Key_I;
	if (key == Leadwerks::Key::J) return Noesis::Gui::Key_J;
	if (key == Leadwerks::Key::K) return Noesis::Gui::Key_K;
	if (key == Leadwerks::Key::L) return Noesis::Gui::Key_L;
	if (key == Leadwerks::Key::M) return Noesis::Gui::Key_M;
	if (key == Leadwerks::Key::N) return Noesis::Gui::Key_N;
	if (key == Leadwerks::Key::O) return Noesis::Gui::Key_O;
	if (key == Leadwerks::Key::P) return Noesis::Gui::Key_P;
	if (key == Leadwerks::Key::Q) return Noesis::Gui::Key_Q;
	if (key == Leadwerks::Key::R) return Noesis::Gui::Key_R;
	if (key == Leadwerks::Key::S) return Noesis::Gui::Key_S;
	if (key == Leadwerks::Key::T) return Noesis::Gui::Key_T;
	if (key == Leadwerks::Key::U) return Noesis::Gui::Key_U;
	if (key == Leadwerks::Key::V) return Noesis::Gui::Key_V;
	if (key == Leadwerks::Key::W) return Noesis::Gui::Key_W;
	if (key == Leadwerks::Key::X) return Noesis::Gui::Key_X;
	if (key == Leadwerks::Key::Y) return Noesis::Gui::Key_Y;
	if (key == Leadwerks::Key::Z) return Noesis::Gui::Key_Z;

	if (key == Leadwerks::Key::D0) return Noesis::Gui::Key_0;
	if (key == Leadwerks::Key::D1) return Noesis::Gui::Key_1;
	if (key == Leadwerks::Key::D2) return Noesis::Gui::Key_2;
	if (key == Leadwerks::Key::D3) return Noesis::Gui::Key_3;
	if (key == Leadwerks::Key::D4) return Noesis::Gui::Key_4;
	if (key == Leadwerks::Key::D5) return Noesis::Gui::Key_5;
	if (key == Leadwerks::Key::D6) return Noesis::Gui::Key_6;
	if (key == Leadwerks::Key::D7) return Noesis::Gui::Key_7;
	if (key == Leadwerks::Key::D8) return Noesis::Gui::Key_8;
	if (key == Leadwerks::Key::D9) return Noesis::Gui::Key_9;

	if (key == Leadwerks::Key::NumPad0) return Noesis::Gui::Key_Pad0;
	if (key == Leadwerks::Key::NumPad1) return Noesis::Gui::Key_Pad1;
	if (key == Leadwerks::Key::NumPad2) return Noesis::Gui::Key_Pad2;
	if (key == Leadwerks::Key::NumPad3) return Noesis::Gui::Key_Pad3;
	if (key == Leadwerks::Key::NumPad4) return Noesis::Gui::Key_Pad4;
	if (key == Leadwerks::Key::NumPad5) return Noesis::Gui::Key_Pad5;
	if (key == Leadwerks::Key::NumPad6) return Noesis::Gui::Key_Pad6;
	if (key == Leadwerks::Key::NumPad7) return Noesis::Gui::Key_Pad7;
	if (key == Leadwerks::Key::NumPad8) return Noesis::Gui::Key_Pad8;
	if (key == Leadwerks::Key::NumPad9) return Noesis::Gui::Key_Pad9;
	if (key == Leadwerks::Key::NumPadPeriod) return Noesis::Gui::Key_Decimal;
	if (key == Leadwerks::Key::NumPadDivide) return Noesis::Gui::Key_Divide;
	if (key == Leadwerks::Key::NumPadMultiply) return Noesis::Gui::Key_Multiply;
	if (key == Leadwerks::Key::NumPadSubtract) return Noesis::Gui::Key_Subtract;
	if (key == Leadwerks::Key::NumPadAddition) return Noesis::Gui::Key_Add;

	return Noesis::Gui::Key_None;
}

int UISystem::ConvertMouseKey(const int key)
{
	if (key == Leadwerks::Key::LButton) return Noesis::Gui::MouseButton_Left;
	if (key == Leadwerks::Key::RButton) return Noesis::Gui::MouseButton_Right;
	if (key == Leadwerks::Key::MButton) return Noesis::Gui::MouseButton_Middle;
	if (key == Leadwerks::Key::XButton1) return Noesis::Gui::MouseButton_XButton1;
	if (key == Leadwerks::Key::XButton2) return Noesis::Gui::MouseButton_XButton2;

	return -1;
}

int UISystem::KeyToText(const int vkey)
{
	// This method is from OIS, license:

	/*
	The zlib/libpng License

	Copyright (c) 2005-2007 Phillip Castaneda (pjcast -- www.wreckedgames.com)

	This software is provided 'as-is', without any express or implied warranty. In no event will
	the authors be held liable for any damages arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose, including commercial
	applications, and to alter it and redistribute it freely, subject to the following
	restrictions:

	1. The origin of this software must not be misrepresented; you must not claim that
	you wrote the original software. If you use this software in a product,
	an acknowledgment in the product documentation would be appreciated but is
	not required.

	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.

	3. This notice may not be removed or altered from any source distribution.
	*/

	BYTE keyState[256];
	HKL  layout = GetKeyboardLayout(0);
	if (GetKeyboardState(keyState) == 0)
		return 0;

	unsigned int sc = MapVirtualKeyEx(vkey, 0, layout);
	if (sc == 0)
		return 0;

	WCHAR buff[3] = { 0 };
	int ascii = ToUnicodeEx(vkey, sc, keyState, buff, 3, 0, layout);

	if (ascii == 1 && deadKey != '\0')
	{
		// A dead key is stored and we have just converted a character key
		// Combine the two into a single character
		WCHAR wcBuff[3] = { buff[0], deadKey, '\0' };
		WCHAR out[3];

		deadKey = '\0';
		if (FoldStringW(MAP_PRECOMPOSED, (LPWSTR)wcBuff, 3, (LPWSTR)out, 3))
			return out[0];
	}
	else if (ascii == 1)
	{	// We have a single character
		deadKey = '\0';
		return buff[0];
	}
	else if (ascii == 2)
	{	// Convert a non-combining diacritical mark into a combining diacritical mark
		// Combining versions range from 0x300 to 0x36F; only 5 (for French) have been mapped below
		// http://www.fileformat.info/info/unicode/block/combining_diacritical_marks/images.htm
		switch (buff[0])	{
			case 0x5E: // Circumflex accent: â
				deadKey = 0x302; break;
			case 0x60: // Grave accent: à
				deadKey = 0x300; break;
			case 0xA8: // Diaeresis: ü
				deadKey = 0x308; break;
			case 0xB4: // Acute accent: é
				deadKey = 0x301; break;
			case 0xB8: // Cedilla: ç
				deadKey = 0x327; break;
			default:
				deadKey = buff[0]; break;
		}
	}

	return 0;
}

void UISystem::CaptureKeyboard()
{
	int i = 0;
	int size = 256;

	for (/**/; i < size; ++i)
	{
		if (Leadwerks::Window::GetCurrent()->KeyHit(i))
		{
			for (auto x = kbListener.begin(); x != kbListener.end(); ++x)
			{
				(*x)->KeyDown(ConvertKey(i));
				(*x)->Character(KeyToText(i));
			}
		}
		else
		{
			for (auto x = kbListener.begin(); x != kbListener.end(); ++x)
			{
				(*x)->KeyUp(ConvertKey(i));
			}
		}
	}
}

void UISystem::CaptureMouse()
{
	// Update mouse position
	mspos = Leadwerks::Window::GetCurrent()->GetMousePosition();

	for (auto x = msListener.begin(); x != msListener.end(); ++x)
	{
		(*x)->MousePosition(mspos.x, mspos.y);
	//	(*x)->MouseWheel(mspos.z);
	}

	// Key presses
	int i = 0;
	int size = 5;

	for (/**/; i < size; ++i)
	{
		if (Leadwerks::Window::GetCurrent()->MouseDown(i))
		{
			for (auto x = msListener.begin(); x != msListener.end(); ++x)
			{
				if (!msbuttondown[i])
				{
					(*x)->MouseButtonDown(ConvertMouseKey(i));
					msbuttondown[i] = true;
				}
			}
		}
		else
		{
			for (auto x = msListener.begin(); x != msListener.end(); ++x)
			{
				if (msbuttondown[i])
				{
					(*x)->MouseButtonUp(ConvertMouseKey(i));
					msbuttondown[i] = false;
				}
			}
		}
	}
}

void UISystem::Capture()
{
	CaptureKeyboard();
	CaptureMouse();
}