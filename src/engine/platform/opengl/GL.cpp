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
HT_CPP_FUNCTION_POINTER(glDeleteBuffers);
HT_CPP_FUNCTION_POINTER(glGenVertexArrays);
HT_CPP_FUNCTION_POINTER(glBindVertexArray);
HT_CPP_FUNCTION_POINTER(glNamedBufferData);


HT_CPP_FUNCTION_POINTER(glCreateProgram);
HT_CPP_FUNCTION_POINTER(glCreateShader);
HT_CPP_FUNCTION_POINTER(glShaderSource);
HT_CPP_FUNCTION_POINTER(glCompileShader);
HT_CPP_FUNCTION_POINTER(glGetShaderiv);
HT_CPP_FUNCTION_POINTER(glGetShaderInfoLog);
HT_CPP_FUNCTION_POINTER(glAttachShader);
HT_CPP_FUNCTION_POINTER(glLinkProgram);
HT_CPP_FUNCTION_POINTER(glValidateProgram);
HT_CPP_FUNCTION_POINTER(glDeleteShader);
HT_CPP_FUNCTION_POINTER(glUseProgram);
HT_CPP_FUNCTION_POINTER(glDeleteProgram);
HT_CPP_FUNCTION_POINTER(glDetachShader);
HT_CPP_FUNCTION_POINTER(glGetProgramiv);
HT_CPP_FUNCTION_POINTER(glGetProgramInfoLog);

bool GLInit() {

	HT_GET_GL_FUNCTION(glGenBuffers);
	HT_GET_GL_FUNCTION(glBindBuffer);
	HT_GET_GL_FUNCTION(glBufferData);
	HT_GET_GL_FUNCTION(glEnableVertexAttribArray);
	HT_GET_GL_FUNCTION(glDisableVertexAttribArray);
	HT_GET_GL_FUNCTION(glVertexAttribPointer);
	HT_GET_GL_FUNCTION(glDeleteBuffers);
	HT_GET_GL_FUNCTION(glGenVertexArrays);
	HT_GET_GL_FUNCTION(glBindVertexArray);
	HT_GET_GL_FUNCTION(glNamedBufferData);

	HT_GET_GL_FUNCTION(glCreateProgram);
	HT_GET_GL_FUNCTION(glCreateShader);
	HT_GET_GL_FUNCTION(glShaderSource);
	HT_GET_GL_FUNCTION(glCompileShader);
	HT_GET_GL_FUNCTION(glGetShaderiv);
	HT_GET_GL_FUNCTION(glGetShaderInfoLog);
	HT_GET_GL_FUNCTION(glAttachShader);
	HT_GET_GL_FUNCTION(glLinkProgram);
	HT_GET_GL_FUNCTION(glValidateProgram);
	HT_GET_GL_FUNCTION(glDeleteShader);
	HT_GET_GL_FUNCTION(glUseProgram);
	HT_GET_GL_FUNCTION(glDeleteProgram);
	HT_GET_GL_FUNCTION(glDetachShader);
	HT_GET_GL_FUNCTION(glGetProgramiv);
	HT_GET_GL_FUNCTION(glGetProgramInfoLog);

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