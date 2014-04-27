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
#include "UIRenderTarget.h"

#define V(exp) \
	do \
	{ \
	while (glGetError() != GL_NO_ERROR); \
	exp; \
	GLenum err = glGetError(); \
	if (err != 0) \
		{ \
		switch (err) \
			{ \
		case GL_NO_ERROR: printf("\n%s [GL_NO_ERROR]\n", #exp); break; \
		case GL_INVALID_ENUM: printf("\n%s [GL_INVALID_ENUM]\n", #exp); break; \
		case GL_INVALID_VALUE: printf("\n%s [GL_INVALID_VALUE]\n", #exp); break; \
		case GL_INVALID_OPERATION: printf("\n%s [GL_INVALID_OPERATION]\n", #exp); break; \
		case GL_INVALID_FRAMEBUFFER_OPERATION: printf("\n%s [GL_INVALID_FRAMEBUFFER_OPERATION]\n", #exp); break; \
		case GL_OUT_OF_MEMORY: printf("\n%s [GL_OUT_OF_MEMORY]\n", #exp); break; \
		default: printf("\n%s [0x%08x]\n", #exp, err); break; \
			} \
		} \
	} \
	while (false)

#ifdef _DEBUG
#define VD(exp) V(exp)
#else
#define VD(exp) exp
#endif

void FramebufferError(GLenum err)
{
	switch (err)
	{
	default:
		printf("\nglCheckFramebufferStatus [0x%08x]\n", err);
	}
}

UIRenderTarget::UIRenderTarget(const int width, const int height, const int format, const int flags, const int frames, const int samples)
{
	// Create a texture
	texture = (Leadwerks::OpenGL2Texture*)Leadwerks::Texture::Create(width, height, format, flags, frames, samples);
	
	// Create a FBO
	V(glGenFramebuffers(1, &fbo));
	V(glBindFramebuffer(GL_FRAMEBUFFER, fbo));

	V(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->gltexturehandle, 0));

	// Create a stencil buffer
	V(glGenRenderbuffers(1, &depthStencil));
	V(glBindRenderbuffer(GL_RENDERBUFFER, depthStencil));
	V(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
	V(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencil));

	GLenum framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (framebufferStatus != GL_FRAMEBUFFER_COMPLETE)
	{
		FramebufferError(framebufferStatus);
	}
}

UIRenderTarget::~UIRenderTarget()
{
	texture->Release();
	texture = NULL;

	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &depthStencil);
}

void UIRenderTarget::Begin()
{
	VD(glViewport(0, 0, texture->GetWidth(), texture->GetHeight()));
	VD(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
}

void UIRenderTarget::End()
{
	VD(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	VD(glViewport(0, 0, Leadwerks::Context::GetCurrent()->GetWidth(), Leadwerks::Context::GetCurrent()->GetHeight()));

	// Rebuild mip maps
	if (texture->hasmipmaps)
	{
		texture->BuildMipmaps();
	}
}

Leadwerks::Texture* UIRenderTarget::GetTexture()
{
	return texture;
}