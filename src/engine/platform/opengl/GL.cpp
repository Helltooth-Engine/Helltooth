#ifdef HT_OPENGL
#include "GL.hpp"
#define HT_CPP_FUNCTION_POINTER(function) HT_FUNCTION_NAME(function) function
#define HT_GET_GL_FUNCTION(function) function = ( HT_FUNCTION_NAME(function) )wglGetProcAddress(#function); \
	if((PROC)function == (PROC)0 || (PROC)function == (PROC)-1) return false;


HT_CPP_FUNCTION_POINTER(glGenBuffers);
HT_CPP_FUNCTION_POINTER(glBindBuffer);
HT_CPP_FUNCTION_POINTER(glBufferData);
HT_CPP_FUNCTION_POINTER(glEnableVertexAttribArray);
HT_CPP_FUNCTION_POINTER(glDisableVertexAttribArray);
HT_CPP_FUNCTION_POINTER(glVertexAttribPointer);

bool GLInit() {

	HT_GET_GL_FUNCTION(glGenBuffers);
	HT_GET_GL_FUNCTION(glBindBuffer);
	HT_GET_GL_FUNCTION(glBufferData);
	HT_GET_GL_FUNCTION(glEnableVertexAttribArray);
	HT_GET_GL_FUNCTION(glDisableVertexAttribArray);
	HT_GET_GL_FUNCTION(glVertexAttribPointer);

	return true;
}


PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

bool wglInit() {

	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	
	return true;
}
#endif