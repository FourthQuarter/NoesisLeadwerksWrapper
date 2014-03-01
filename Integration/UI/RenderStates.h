//========= Copyright © 2014, Bryan Andrew King, All rights reserved. ============
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