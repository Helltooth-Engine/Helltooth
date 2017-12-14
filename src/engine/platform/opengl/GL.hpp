#ifdef HT_OPENGL
#pragma once
#include <Windows.h>

typedef unsigned int GLenum;
typedef unsigned int GLbitfield;
typedef unsigned int GLuint;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLboolean;
typedef signed char GLbyte;
typedef short GLshort;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned long GLulong;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;

#define GL_ZERO 0
#define GL_FALSE 0
#define GL_NONE 0
#define GL_NO_ERROR 0
#define GL_TRUE 1
#define GL_ONE 1

//Draw modes
#define GL_LINES 0x0001
#define GL_LINE_LOOP 0x0002
#define GL_LINE_STRIP 0x0003
#define GL_TRIANGLES 0x0004
#define GL_TRIANGLE_STRIP 0x0005
#define GL_TRIANGLE_FAN 0x0006
#define GL_QUADS 0x0007
#define GL_QUAD_STRIP 0x0008

//Buffer bits
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define HT_FUNCTION_NAME(function) PFN##function##PROC
#define HT_CREATE_FUNCTION_POINTER(returntype, function, ...) typedef returntype(APIENTRY * HT_FUNCTION_NAME(function)) (__VA_ARGS__); \
		extern HT_FUNCTION_NAME(function) function


HT_CREATE_FUNCTION_POINTER(void, glClearColor, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
HT_CREATE_FUNCTION_POINTER(void, glClear, GLbitfield mask);
HT_CREATE_FUNCTION_POINTER(void, glBegin, GLenum mode);
HT_CREATE_FUNCTION_POINTER(void, glEnd, void);

extern bool GLInit();

#endif // HT_OPENGL