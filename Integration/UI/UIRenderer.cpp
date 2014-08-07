/*********************************************************************************
 *	The MIT License(MIT)
 *
 *	Version 1.0
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
#include "UIRenderer.h"
#include "OpenGLState.h"

// Noesis
#include <Noesis.h>
#include <NsCore\Ptr.h>
#include <NsGui\IRenderer.h>
#include <NsGui\FrameworkElement.h>
#include <NsGui\IUIResource.h>
#include <NsGui\ResourceDictionary.h>
#include <NsGui\Collection.h>
#include <NsGui\Keyboard.h>

using namespace Noesis;
using namespace Noesis::Gui;
using namespace Noesis::Core;

const int UIRenderer::Wireframe		= 1;
const int UIRenderer::ColorBatch	= 2;
const int UIRenderer::Overdraw		= 4;
const int UIRenderer::FlipY			= 8;

RenderCommands renderCommands;

UIRenderer::UIRenderer(const int uid) : uid(-1), renderer(NULL), xaml(NULL), glState(NULL)
{
	this->uid	= uid;
	glState		= new OpenGLState();
}

UIRenderer::~UIRenderer()
{
	renderCommands.commands.Reset();
	renderCommands.offscreenCommands.Reset();

	renderer->Release();
	xaml->Release();

	delete glState;
	glState = NULL;
}

void UIRenderer::Load(std::string xaml, std::string resource)
{
	Ptr<FrameworkElement> ptrxaml = LoadXaml<FrameworkElement>(xaml.c_str());
	this->xaml = ptrxaml.GetPtr();
	ptrxaml->AddReference();

	if (this->xaml)
	{
		if (resource.size() > 0)
		{
			Ptr<ResourceDictionary> resources = LoadXaml<ResourceDictionary>(resource.c_str());

			if (resources)
			{
				this->xaml->GetResources()->GetMergedDictionaries()->Add(resources.GetPtr());
				resources->AddReference();
			}
			else
			{
				NS_ERROR("Loading %s", resource.c_str());
			}
		}

		Ptr<IRenderer> ptrrenderer = Gui::CreateRenderer(this->xaml);
		renderer = ptrrenderer.GetPtr();
		ptrrenderer->AddReference();
	}
}

void UIRenderer::Update(const double time)
{
	NsGetKernel()->Tick();
	renderer->Update(time);
	renderCommands = renderer->WaitForUpdate();
}

void UIRenderer::MousePosition(const int x, const int y)
{
	mspos.x = x;
	mspos.y = y;
	renderer->MouseMove(mspos.x, mspos.y);
}

void UIRenderer::MouseButtonDown(const int button)
{
	renderer->MouseButtonDown(mspos.x, mspos.y, static_cast<MouseButton>(button));
}

void UIRenderer::MouseButtonUp(const int button)
{
	renderer->MouseButtonUp(mspos.x, mspos.y, static_cast<MouseButton>(button));
}

void UIRenderer::MouseWheel(const int rotation)
{
	renderer->MouseWheel(mspos.x, mspos.y, rotation);
}

void UIRenderer::Character(const char character)
{
	renderer->Char(character);
}

void UIRenderer::KeyDown(const int key)
{
	Noesis::Gui::Keyboard* kb = renderer->GetContent()->GetKeyboard();
	NS_ASSERT(kb);

	NsUInt32 keyModifiers = kb->GetModifiers();
	NsBool isCtrlPressed = (keyModifiers & ModifierKeys_Control) != 0;
	NsBool isShiftPressed = (keyModifiers & ModifierKeys_Shift) != 0;

	// Notify of key event to the UIRenderer
	renderer->KeyDown(static_cast<Noesis::Gui::Key>(key));

	// Virtual events
	if (key == Gui::Key_Tab)
	{
		renderer->VirtualEvent(isCtrlPressed ?
							   (isShiftPressed ? VirtualEvent_ControlTabPrev : VirtualEvent_ControlTabNext) :
							   (isShiftPressed ? VirtualEvent_DirectionalTabPrev : VirtualEvent_DirectionalTabNext));
	}
	else if (key == Gui::Key_Left)
	{
		renderer->VirtualEvent(VirtualEvent_DirectionalLeft);
	}
	else if (key == Gui::Key_Right)
	{
		renderer->VirtualEvent(VirtualEvent_DirectionalRight);
	}
	else if (key == Gui::Key_Up)
	{
		renderer->VirtualEvent(VirtualEvent_DirectionalUp);
	}
	else if (key == Gui::Key_Down)
	{
		renderer->VirtualEvent(VirtualEvent_DirectionalDown);
	}
}

void UIRenderer::KeyUp(const int key)
{
	renderer->KeyUp(static_cast<Noesis::Gui::Key>(key));
}

void UIRenderer::RenderOffscreen()
{
	glState->Store();
	renderer->Render(renderCommands.offscreenCommands.GetPtr());
	glState->Restore();
}

void UIRenderer::Render()
{
	glState->Store();
	renderer->Render(renderCommands.commands.GetPtr());
	glState->Restore();
}

void UIRenderer::SetAntialiasingMode(const int mode)
{
	renderer->SetAntialiasingMode(static_cast<AntialiasingMode>(mode));
}

void UIRenderer::SetTessellationQuality(const int quality)
{
	renderer->SetTessellationQuality(static_cast<TessellationQuality>(quality));
}

void UIRenderer::SetTessellationMode(const int mode)
{
	renderer->SetTessellationMode(static_cast<TessellationMode>(mode));
}

void UIRenderer::SetOffscreenSize(const int width, const int height, const int multisample)
{
	renderer->SetOffscreenSize(width, height, static_cast<Noesis::Render::MultiSample>(multisample));
}

void UIRenderer::SetSize(const int width, const int height)
{
	renderer->SetSize(width, height);
}

Noesis::Gui::FrameworkElement*	UIRenderer::GetXAML()
{
	return this->xaml;
}

void UIRenderer::SetFlags(const int flags)
{
	renderer->SetFlags(flags);
}