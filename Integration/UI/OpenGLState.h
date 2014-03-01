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