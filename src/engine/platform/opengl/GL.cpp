#ifdef HT_OPENGL
#include "GL.hpp"
#define HT_CPP_FUNCTION_POINTER(function) HT_FUNCTION_NAME(function) function
#define HT_GET_GL_FUNCTION(function) function = ( HT_FUNCTION_NAME(function) )wglGetProcAddress(#function); \
	if((PROC)function == (PROC)0 || (PROC)function == (PROC)-1) return false;



bool GLInit() {


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