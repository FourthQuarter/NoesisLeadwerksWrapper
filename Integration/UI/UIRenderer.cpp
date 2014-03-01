//========= Copyright © 2014, Bryan Andrew King, All rights reserved. ============
#include "UIRenderer.h"
#include "OpenGLState.h"

// Noesis
#include <NsGui\IUIResource.h>
#include <NsGui\ResourceDictionary.h>
#include <NsGui\Collection.h>
#include <NsGui\Keyboard.h>
#include "..\Input\OISKeyMappings.h"

using namespace Noesis;
using namespace Noesis::Gui;
using namespace Noesis::Core;

UIRenderer::UIRenderer(const int uid) : uid(-1), renderer(NULL), xaml(NULL), glState(NULL)
{
	this->uid	= uid;
	glState		= new OpenGLState();
}

UIRenderer::~UIRenderer()
{
	renderCommands.commands.Reset();
	renderCommands.offscreenCommands.Reset();
	renderer.Reset();
	xaml.Reset();
	delete glState;
	glState = NULL;
}

void UIRenderer::Load(std::string xaml, std::string resource)
{
	this->xaml = LoadXaml<FrameworkElement>(xaml.c_str());

	if (this->xaml)
	{
		if (resource.size() > 0)
		{
			Ptr<ResourceDictionary> resources = LoadXaml<ResourceDictionary>(resource.c_str());

			if (resources)
			{
				this->xaml->GetResources()->GetMergedDictionaries()->Add(resources.GetPtr());
			}
			else
			{
				NS_ERROR("Loading %s", resource.c_str());
			}
		}

		renderer = Gui::CreateRenderer(this->xaml.GetPtr());
		renderCommands	=  RenderCommands();
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
	renderer->MouseMove(x, y);
	mx = x;
	my = y;
}

void UIRenderer::MouseButtonDown(const int button)
{
	renderer->MouseButtonDown(mx, my, static_cast<MouseButton>(button));
}

void UIRenderer::MouseButtonUp(const int button)
{
	renderer->MouseButtonUp(mx, my, static_cast<MouseButton>(button));
}

void UIRenderer::MouseWheel(const int rotation)
{
	renderer->MouseWheel(mx, my, rotation);
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

	Key nsKey = s_OISKeyMappings[key];

	// Notify of key event to the UIRenderer
	renderer->KeyDown(nsKey);

	// Virtual events
	if (nsKey == Gui::Key_Tab)
	{
		renderer->VirtualEvent(isCtrlPressed ?
							   (isShiftPressed ? VirtualEvent_ControlTabPrev : VirtualEvent_ControlTabNext) :
							   (isShiftPressed ? VirtualEvent_DirectionalTabPrev : VirtualEvent_DirectionalTabNext));
	}
	else if (nsKey == Gui::Key_Left)
	{
		renderer->VirtualEvent(VirtualEvent_DirectionalLeft);
	}
	else if (nsKey == Gui::Key_Right)
	{
		renderer->VirtualEvent(VirtualEvent_DirectionalRight);
	}
	else if (nsKey == Gui::Key_Up)
	{
		renderer->VirtualEvent(VirtualEvent_DirectionalUp);
	}
	else if (nsKey == Gui::Key_Down)
	{
		renderer->VirtualEvent(VirtualEvent_DirectionalDown);
	}
}

void UIRenderer::KeyUp(const int key)
{
	renderer->KeyUp(s_OISKeyMappings[key]);
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