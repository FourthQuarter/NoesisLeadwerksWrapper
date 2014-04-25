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
#ifndef UI_RENDERER_H
#define UI_RENDERER_H

#include <Leadwerks.h>

class OpenGLState;

namespace Noesis
{
	namespace Gui
	{
		class IRenderer;
		class RenderCommands;
		class FrameworkElement;
	}
}

/**
 * \class UIRenderer
 * \brief XAML Renderer
 */
class UIRenderer
{
private:
	int													uid; ///< Unique id
	OpenGLState*										glState; ///< OpenGL state
	Leadwerks::Vec3										mspos; ///< Last known mouse position
	Noesis::Gui::IRenderer*								renderer; ///< Actual renderer
	Noesis::Gui::FrameworkElement*						xaml; ///< Loaded xaml

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
	 * \param[in] time Time in s
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
	inline  int	GetUID(){ return uid; } 

	/**
	 * \brief Returns the loaded XAML
	 * \return XAML
	 */
	Noesis::Gui::FrameworkElement*	GetXAML();
	
	/**
	 * \brief  Sets renderer flags
	 * \details Noesis::Gui::RendererFlags
	 * \param[in] flag Wireframe, ColorBatch, Overdraw or FlipY. Flags can be combined.
	 */
	void	SetFlags(const int flags);

	// Render flags
	static const int	Wireframe;
	static const int	ColorBatch;
	static const int	Overdraw;
	static const int	FlipY;
};

#endif//UI_RENDERER_H