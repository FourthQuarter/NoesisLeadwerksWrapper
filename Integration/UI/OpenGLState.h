/*********************************************************************************
*	The MIT License(MIT)
*
*	Copyright © 2014, Noesis Technologies S.L. and Bryan Andrew King
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
#ifndef OPENGL_STATE_H
#define OPENGL_STATE_H

#include "RenderStates.h"

#include <Leadwerks.h>
#include <GL\GL.h>
#include <GL\glew.h>

/**
 * \class OpenGLState
 * \brief Stores and restores the current GPU state.
 * \details Implements the ability to store and restore a gpu state.
 */
class OpenGLState
{
private:
	RenderStates							renderStates;

	PFNGLBINDFRAMEBUFFERPROC				glBindFramebuffer;
	PFNGLBINDBUFFERPROC						glBindBuffer;
	PFNGLACTIVETEXTUREPROC					glActiveTexture;
	PFNGLUSEPROGRAMPROC						glUseProgram;
	PFNGLGETVERTEXATTRIBIVPROC				glGetVertexAttribiv;
	PFNGLENABLEVERTEXATTRIBARRAYARBPROC		glEnableVertexAttribArray;
	PFNGLDISABLEVERTEXATTRIBARRAYARBPROC	glDisableVertexAttribArray;
	PFNGLBLENDEQUATIONPROC					glBlendEquation;
	PFNGLBINDVERTEXARRAYPROC				glBindVertexArray;

public:
	OpenGLState();

	/**
	 * \brief Stores the current gpu state.
	 */
	void Store();
	/**
	 * \brief Restores the stored gpu state.
	 */
	void Restore();
};

#endif//OPENGL_STATE_H