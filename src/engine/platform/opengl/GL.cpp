#include "GL.hpp"
#define HT_CPP_FUNCTION_POINTER(function) HT_FUNCTION_NAME(function) function
#define HT_GET_GL_FUNCTION(function) function = ( HT_FUNCTION_NAME(function) )wglGetProcAddress(#function); \
	if((PROC)function == (PROC)0 || (PROC)function == (PROC)-1) return false;


HT_CPP_FUNCTION_POINTER(glClear);
HT_CPP_FUNCTION_POINTER(glClearColor);
HT_CPP_FUNCTION_POINTER(glBegin);
HT_CPP_FUNCTION_POINTER(glEnd);

bool GLInit() {
	HT_GET_GL_FUNCTION(glClear)
	HT_GET_GL_FUNCTION(glClearColor)

	HT_GET_GL_FUNCTION(glBegin)
	HT_GET_GL_FUNCTION(glEnd)

	return true;
}