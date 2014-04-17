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
#ifndef UI_RENDERTARGET_H
#define UI_RENDERTARGET_H

#include <Leadwerks.h>

/**
 * \class UIRenderTarget
 * \brief Render target
 * \details Creates a new FBO with stencil enabled in the current OpenGL context.
 */
class UIRenderTarget
{
private:
	GLuint						fbo; ///< Framebuffer
	GLuint						depthStencil; ///< Renderbuffer
	Leadwerks::OpenGL2Texture*	texture; ///< Texture

public:
	/**
	 * \brief Craetes a new render target
	 * \details Parameter information: http://www.leadwerks.com/werkspace/page/documentation/_/command-reference/texture/texturecreate-r340
	 * \param[in] width Texture width
	 * \param[in] height Texture height
	 * \param[in] format Texture format
	 * \param[in] flags Texture flags
	 * \param[in] frames Texture frames
	 * \param[in] samples Texture samples
	 */
	UIRenderTarget(const int width, const int height, const int format = Leadwerks::Texture::RGBA, const int flags = 0, const int frames = 1, const int samples = 0);
	~UIRenderTarget();

	/**
	 * \brief Start rendering into the render target
	 */
	void				Begin();

	/**
	 * \brief Stop rendering into the render target
	 */
	void				End();

	/**
	 * \brief Get render target texture
	 * \return Texture
	 */
	Leadwerks::Texture*	GetTexture();
};

#endif//UI_RENDERTARGET_H
