# Noesis Leadwerks integration #

This repository provides an integration of NoesisGUI into the Leadwerks game engine.

## Getting started ##

###Overview###
    +Root
     +Documentation: Doxygen docs
	 +Examples: Implementation examples
     +Integration: Required header / source files


###Pre-Requirements###


I. **Noesis**


1. Download Noesis
2. Add the *include* folder to your project's additional include directories
3. Link your project to bin/Noesis.lib
4. Copy Noesis.dll, tbb.dll and tbbmalloc.dll from */bin* to your project's executable
5. Run the Resource.BuildTool.exe to build all required resources: *Resource.BuildTool.exe rebuild --platform GL*
6. Copy *bin/Data* to your executable's directory

II. **Wrapper**

Add the content of *integration* to your project.

### Quick start guide ###

Once you have all necessary files added to your project start by adding the includes for the input and ui system to your app.h:

	#include <UI\UISystem.h>
	#include <UI\UIRenderer.h>

    
Define objects for the ui system and renderer:

	UISystem*		uiSystem;
	UIRenderer*		uiRenderer;

Initialize both objects inside the *App::Start* method:

	// Create the ui system
	uiSystem	= new UISystem();

	// Create a renderer with an unique ID
	uiRenderer	= new UIRenderer(uiSystem->GenerateUID());
	uiRenderer->Load("Gui/Samples/Tux.xaml" ); // Load XAML
	uiRenderer->SetSize(context->GetWidth(), context->GetHeight());


Don't forget to delete the objects in the destructor. Inside the *App::Loop* method we now need to update and render the ui:

	// Update XAML renderer
	uiRenderer->Update(Time::Millisecs() / 1000.0f);

	// Render XAML offscreen
	uiRenderer->RenderOffscreen();

	// ..
	world->Update();
	world->Render();

	// Render XAML
	uiRenderer->Render();

	context->Sync(false);


That's all! You should now see a tux:

![TUX](http://i.imgur.com/rdF5RCz.jpg)

For more examples check the *Examples* folder.