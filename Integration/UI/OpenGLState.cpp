/*********************************************************************************
*	The MIT License(MIT)
*
*	Version 1.0
*	Copyright � 2014, Noesis Technologies S.L. and Bryan Andrew King
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
#include "OpenGLState.h"

#include <Noesis.h>
#include <Leadwerks.h>

OpenGLState::OpenGLState()
{
#define GL_IMPORT(_proto, _func) \
	{ \
		_func = (_proto)wglGetProcAddress(#_func); \
		if (_func == NULL) \
		{ \
		printf("wglGetProcAddress %s", #_func); \
		} \
	}

	GL_IMPORT(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer);
	GL_IMPORT(PFNGLBINDBUFFERPROC, glBindBuffer);
	GL_IMPORT(PFNGLACTIVETEXTUREPROC, glActiveTexture);
	GL_IMPORT(PFNGLUSEPROGRAMPROC, glUseProgram);
	GL_IMPORT(PFNGLGETVERTEXATTRIBIVPROC, glGetVertexAttribiv);
	GL_IMPORT(PFNGLENABLEVERTEXATTRIBARRAYARBPROC, glEnableVertexAttribArray);
	GL_IMPORT(PFNGLDISABLEVERTEXATTRIBARRAYARBPROC, glDisableVertexAttribArray);
	GL_IMPORT(PFNGLBLENDEQUATIONPROC, glBlendEquation);
	GL_IMPORT(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
}

void OpenGLState::Store()
{
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &renderStates.unpackAlignment);
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &renderStates.frameBuffer);
	glGetIntegerv(GL_VIEWPORT, renderStates.viewport);

	glGetFloatv(GL_COLOR_CLEAR_VALUE, renderStates.clearColors);
	glGetFloatv(GL_DEPTH_CLEAR_VALUE, &renderStates.clearDepth);
	glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &renderStates.clearStencil);

	glGetBooleanv(GL_COLOR_WRITEMASK, renderStates.colorWriteMask);

	renderStates.dither = glIsEnabled(GL_DITHER);
	renderStates.sampleAlphaToCoverage = glIsEnabled(GL_SAMPLE_ALPHA_TO_COVERAGE);
	renderStates.sampleCoverage = glIsEnabled(GL_SAMPLE_COVERAGE);

#ifndef LEADWERKS_3_1
	renderStates.alphaTest = glIsEnabled(GL_ALPHA_TEST);
#endif

	renderStates.depthTest = glIsEnabled(GL_DEPTH_TEST);
	glGetBooleanv(GL_DEPTH_WRITEMASK, &renderStates.depthWrite);
	glGetIntegerv(GL_DEPTH_FUNC, &renderStates.depthFunc);

	renderStates.stencilTest = glIsEnabled(GL_STENCIL_TEST);
	glGetIntegerv(GL_STENCIL_FAIL, &renderStates.stencilTestFailOp);
	glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, &renderStates.stencilTestSPDF);
	glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &renderStates.stencilTestSPDP);
	glGetIntegerv(GL_STENCIL_FUNC, &renderStates.stencilFunc);
	glGetIntegerv(GL_STENCIL_REF, &renderStates.stencilRef);
	glGetIntegerv(GL_STENCIL_VALUE_MASK, (int*)&renderStates.stencilMask);
	glGetIntegerv(GL_STENCIL_WRITEMASK, (int*)&renderStates.stencilWriteMask);

	renderStates.scissorTest = glIsEnabled(GL_SCISSOR_TEST);
	renderStates.cullFaceEnabled = glIsEnabled(GL_CULL_FACE);
	glGetIntegerv(GL_CULL_FACE_MODE, &renderStates.cullFaceMode);

	renderStates.blendEnabled = glIsEnabled(GL_BLEND);
	glGetIntegerv(GL_BLEND_EQUATION_RGB, &renderStates.blendEquation);
	glGetIntegerv(GL_BLEND_SRC_RGB, &renderStates.blendSource);
	glGetIntegerv(GL_BLEND_DST_RGB, &renderStates.blendDestination);

	glGetIntegerv(GL_ACTIVE_TEXTURE, &renderStates.activeTexture);

	for (NsSize i = 0; i < 4; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &(renderStates.boundTexture[i]));
	}

	glGetIntegerv(GL_CURRENT_PROGRAM, &renderStates.currentProgram);

	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, (int*)&renderStates.arrayBuffer);
	for (NsSize i = 0; i < 6; i++)
	{
		glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_ENABLED,
							&(renderStates.vertexAttribsEnabled[i]));
	}

	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, (int*)&renderStates.elementArrayBuffer);
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (int*)&renderStates.vertexArrayBuffer);
}

void OpenGLState::Restore()
{
	//printf("--START--\n");
	//printf("GLERR: %d\n", glGetError());
	glPixelStorei(GL_UNPACK_ALIGNMENT, renderStates.unpackAlignment);
	
	glBindFramebuffer(GL_FRAMEBUFFER, renderStates.frameBuffer);
	glViewport(renderStates.viewport[0], renderStates.viewport[1], renderStates.viewport[2],
			   renderStates.viewport[3]);

	glClearColor(renderStates.clearColors[0], renderStates.clearColors[1],
				 renderStates.clearColors[2], renderStates.clearColors[3]);
	glClearDepth(renderStates.clearDepth);

	glClearStencil(renderStates.clearStencil);
	glColorMask(renderStates.colorWriteMask[0], renderStates.colorWriteMask[1],
				renderStates.colorWriteMask[2], renderStates.colorWriteMask[3]);

	renderStates.dither ? glEnable(GL_DITHER) : glDisable(GL_DITHER);
	renderStates.sampleAlphaToCoverage ? glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE) :
		glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

	renderStates.sampleCoverage ? glEnable(GL_SAMPLE_COVERAGE) : glDisable(GL_SAMPLE_COVERAGE);

#ifndef LEADWERKS_3_1
	renderStates.alphaTest ? glEnable(GL_ALPHA_TEST) : glDisable(GL_ALPHA_TEST);
#endif

	renderStates.depthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

	glDepthMask(renderStates.depthWrite);
	glDepthFunc(renderStates.depthFunc);
	renderStates.stencilTest ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
	glStencilOp(renderStates.stencilTestFailOp, renderStates.stencilTestSPDF,
				renderStates.stencilTestSPDP);
	glStencilFunc(renderStates.stencilFunc, renderStates.stencilRef, renderStates.stencilMask);
	glStencilMask(renderStates.stencilWriteMask);
	renderStates.scissorTest ? glEnable(GL_SCISSOR_TEST) : glDisable(GL_SCISSOR_TEST);
	renderStates.cullFaceEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	glCullFace(renderStates.cullFaceMode);
	renderStates.blendEnabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
	glBlendEquation(renderStates.blendEquation);
	glBlendFunc(renderStates.blendSource, renderStates.blendDestination);
	for (NsSize i = 0; i < 4; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, renderStates.boundTexture[i]);
	}

	glActiveTexture(renderStates.activeTexture);

	glUseProgram(renderStates.currentProgram);

	glBindVertexArray(renderStates.vertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, renderStates.arrayBuffer);
	for (NsSize i = 0; i < 6; i++)
	{
		renderStates.vertexAttribsEnabled[i] ?
			glEnableVertexAttribArray(i) : glDisableVertexAttribArray(i);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderStates.elementArrayBuffer);
	//printf("GLERR: %d\n", glGetError());
	//printf("--END--\n");
}