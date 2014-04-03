/*********************************************************************************
*	The MIT License(MIT)
*
*	Copyright © 2014, Noesis Technologies S.L.
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
#ifndef RENDER_STATES_H
#define RENDER_STATES_H

struct RenderStates
{
	int             frameBuffer;
	int             viewport[4];
	float           clearColors[4];
	float           clearDepth;
	int             clearStencil;
	unsigned char   alphaTest;
	unsigned char   depthTest;
	unsigned char   depthWrite;
	int             depthFunc;
	unsigned char   stencilTest;
	int             stencilTestFailOp;
	int             stencilTestSPDF;
	int             stencilTestSPDP;
	int             stencilFunc;
	int             stencilRef;
	unsigned int    stencilMask;
	unsigned int    stencilWriteMask;
	unsigned char   scissorTest;
	unsigned char   cullFaceEnabled;
	int             cullFaceMode;
	unsigned char   dither;
	unsigned char   sampleAlphaToCoverage;
	unsigned char   sampleCoverage;
	unsigned char   blendEnabled;
	int             blendEquation;
	int             blendSource;
	int             blendDestination;
	unsigned char   colorWriteMask[4];
	unsigned int    arrayBuffer;
	int             vertexAttribsEnabled[6];
	int             activeTexture;
	unsigned int    elementArrayBuffer;
	unsigned int    vertexArrayBuffer;
	int             boundTexture[4];
	int             currentProgram;
	int             unpackAlignment;
};

#endif//RENDER_STATES_H