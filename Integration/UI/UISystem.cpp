//========= Copyright © 2014, Bryan Andrew King, All rights reserved. ============
#include "UISystem.h"

// Neosis
#include <NsCore\Kernel.h>
#include <NsCore\NsSystem.h>
#include <NsCore\NsConfig.h>

void NoesisErrorHandler(const NsChar* filename, NsInt line, const NsChar* desc)
{
	throw std::exception(desc);
}

UISystem::UISystem() : currentUID(1)
{
	Noesis::Core::SetErrorHandler(NoesisErrorHandler);

	NsGetKernel()->Init();

	// Select Render
	NsConfigValue("Render.RenderSystem", "Render", "GL");

	NsGetKernel()->InitSystems();
}

UISystem::~UISystem()
{
	NsGetKernel()->Shutdown();
}

bool UISystem::keyPressed(const OIS::KeyEvent &e)
{
	for (auto i = listener.begin(); i != listener.end(); i++)
	{
		(*i)->KeyDown(e.key);
		(*i)->Character(e.text);
	}
	return false;
}

bool UISystem::keyReleased(const OIS::KeyEvent &e)
{
	for (auto i = listener.begin(); i != listener.end(); i++)
	{
		(*i)->KeyUp(e.key);
	}
	return false;
}

bool UISystem::mouseMoved(const OIS::MouseEvent &arg)
{
	for (auto i = listener.begin(); i != listener.end(); i++)
	{
		(*i)->MousePosition(arg.state.X.abs, arg.state.Y.abs);
	}
	return false;
}

bool UISystem::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	for (auto i = listener.begin(); i != listener.end(); i++)
	{
		(*i)->MouseButtonDown(id);
	}
	return false;
}

bool UISystem::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	for (auto i = listener.begin(); i != listener.end(); i++)
	{
		(*i)->MouseButtonUp(id);
	}
	return false;
}

int	UISystem::GenerateUID()
{
	return currentUID++;
}

void UISystem::AddInputListener(UIRenderer* &uiRenderer)
{
	if (uiRenderer->GetUID() > 0)
	{
		listener.push_back(uiRenderer);
	}
}

void UISystem::RemoveInputListener(const int uid)
{
	for (auto i = listener.begin(); i != listener.end(); /**/)
	{
		if ((*i)->GetUID() == uid)
		{
			i = listener.erase(i);
			break;
		}
		else i++;
	}
}
