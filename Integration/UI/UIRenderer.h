//========= Copyright © 2014, Bryan Andrew King, All rights reserved. ============
#ifndef UI_RENDERER_H
#define UI_RENDERER_H

// Bad dependencies
#include <Noesis.h>
#include <NsCore\Ptr.h>
#include <NsGui\IRenderer.h>
#include <NsGui\FrameworkElement.h>

class OpenGLState;

/**
 * \class UIRenderer
 * \brief XAML Renderer
 */
class UIRenderer
{
private:
	int													uid; ///< Unique id
	Noesis::Ptr<Noesis::Gui::IRenderer>					renderer; ///< Actual UIRenderer
	Noesis::Gui::RenderCommands							renderCommands;
	Noesis::Ptr<Noesis::Gui::FrameworkElement>			xaml; ///< Loaded xaml file
	OpenGLState*										glState; ///< OpenGL state
	int													mx, my; ///< Mouse coordinates

public:
	/**
	 * \brief Creates a new UIRenderer
	 */
	UIRenderer(const int id);
	virtual ~UIRenderer();

	/**
	 * \brief Loads the specified xaml
	 * \param[in] xaml XAML to load
	 * \param[in] resource Additional xaml style / resource
	 */
	void	Load(std::string xaml, std::string resource = "");

	/**
	 * \brief Update Renderer
	 * \details Updates the noesis kernel, the renderer and the renderCommands.
	 * \param[in] time Time in ms
	 */
	void	Update(const double time);

	/**
	 * \brief Notifies the renderer that the mouse position has changed
	 */
	void	MousePosition(const int x, const int y);

	/**
	 * \brief Notifies the renderer that a mouse button has been pressed
	 */
	void	MouseButtonDown(const int button);
	/**
	 * \brief Notifies the renderer that a mouse button has been released
	 */
	void	MouseButtonUp(const int button);
	/**
	 * \brief Notifies the renderer that the mouse wheel has been rotated
	 */
	void	MouseWheel(const int rotation);
	
	/**
	 * \brief Sends the specified key to the renderer
	 */
	void	Character(const char character);
	/**
	 * \brief Notifies renderer that a key was pressed
	 */
	void	KeyDown(const int key);
	/**
	 * \brief Notifies renderer that a key was released
	 */
	void	KeyUp(const int key);
	
	/**
	 * \brief Render xaml offscreen
	 */
	void	RenderOffscreen();
	/**
	 * \brief Render xaml to screen
	 */
	void	Render();

	/**
	 * \brief Sets the renderer to the specified size
	 */
	void	SetSize(const int width, const int height);

	/**
	 * \brief Sets the antialiasing mode.
	 * \details Default value is MSAA.
	 * \param[in] mode Noesis::Gui::AntialiasingMode
	 */
	void	SetAntialiasingMode(const int mode);

	/**
	 * \brief Sets the tesselation quality.
	 * \details Default value is Medium.
	 * \param[in] quality Noesis::Gui::TessellationQuality
	 */
	void	SetTessellationQuality(const int quality);

	/**
	 * \brief Sets the tesselation mode.
	 * \details Default value is Threshold.
	 * \param[in] mode Noesis::Gui::TessellationMode
	 */
	void	SetTessellationMode(const int mode);

	/**
	 * \brief Set offscreen rendering quality
	 * \details By default, offscreen textures have the same dimensions that the target surface and
				multisampling is disabled for them.
	 * \param[in] width Relative width (0-1)
	 * \param[in] height Relative height (0-1)
	 * \param[in] multisample Noesis::Render::MultiSample
	 */
	void	SetOffscreenSize(const int width, const int height, const int multisample);

	/**
	 * \brief Returns the renderers uid.
	 * \return uid
	 */
	inline  short	GetUID(){ return uid; } 

	/**
	 * \brief Returns the loaded XAML
	 * \return XAML
	 */
	Noesis::Gui::FrameworkElement*	GetXAML() { return xaml.GetPtr(); }
};

#endif//UI_RENDERER_H