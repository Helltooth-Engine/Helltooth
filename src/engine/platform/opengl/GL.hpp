#ifdef HT_OPENGL
#pragma once
#include <Windows.h>
#include <gl/GL.h>

#define HT_FUNCTION_NAME(function) PFN##function##PROC
#define HT_CREATE_FUNCTION_POINTER(returntype, function, ...) typedef returntype(APIENTRY * HT_FUNCTION_NAME(function)) (__VA_ARGS__); \
		extern HT_FUNCTION_NAME(function) function

typedef unsigned int GLenum;
typedef unsigned int GLbitfield;
typedef unsigned int GLuint;
typedef long long GLsizeiptr;
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
typedef char GLchar;

#define GL_ZERO 0
#define GL_FALSE 0
#define GL_NONE 0
#define GL_NO_ERROR 0
#define GL_TRUE 1
#define GL_ONE 1

//Types
#define GL_BYTE 0x1400
#define GL_UNSIGNED_BYTE 0x1401
#define GL_SHORT 0x1402
#define GL_UNSIGNED_SHORT 0x1403
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406
#define GL_DOUBLE 0x140A

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

#define GL_VERSION 0x1F02

#define GL_SHADING_LANGUAGE_VERSION 0x8B8C

//Buffers
#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_UNIFORM_BUFFER 0x8A11
#define GL_STATIC_DRAW 0x88E4
#define GL_DYNAMIC_DRAW 0x88E8

HT_CREATE_FUNCTION_POINTER(void, glGenBuffers, GLsizei n, GLuint* buffers);
HT_CREATE_FUNCTION_POINTER(void, glBindBuffer, GLenum target, GLuint buffer);
HT_CREATE_FUNCTION_POINTER(void, glEnableVertexAttribArray, GLuint index);
HT_CREATE_FUNCTION_POINTER(void, glDisableVertexAttribArray, GLuint index);
HT_CREATE_FUNCTION_POINTER(void, glBufferData, GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
HT_CREATE_FUNCTION_POINTER(void, glVertexAttribPointer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
HT_CREATE_FUNCTION_POINTER(void, glDeleteBuffers, GLsizei n, const GLuint* buffers);
HT_CREATE_FUNCTION_POINTER(void, glNamedBufferData, GLuint buffer, GLsizei size, const void *data, GLenum usage);

HT_CREATE_FUNCTION_POINTER(void, glGenVertexArrays, GLsizei n, GLuint* arrays);
HT_CREATE_FUNCTION_POINTER(void, glBindVertexArray, GLuint array);
HT_CREATE_FUNCTION_POINTER(void, glDeleteVertexArrays, GLsizei n, const GLuint* arrays);

//Shaders
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_DELETE_STATUS 0x8B80
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_VALIDATE_STATUS 0x8B83
#define GL_INFO_LOG_LENGTH 0x8B84

HT_CREATE_FUNCTION_POINTER(GLuint, glCreateProgram);
HT_CREATE_FUNCTION_POINTER(GLuint, glCreateShader, GLenum type);
HT_CREATE_FUNCTION_POINTER(void, glShaderSource, GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
HT_CREATE_FUNCTION_POINTER(void, glCompileShader, GLuint shader);
HT_CREATE_FUNCTION_POINTER(void, glGetShaderiv, GLuint shader, GLenum pname, GLint *params);
HT_CREATE_FUNCTION_POINTER(void, glGetShaderInfoLog, GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog);

HT_CREATE_FUNCTION_POINTER(void, glAttachShader, GLuint program, GLuint shader);
HT_CREATE_FUNCTION_POINTER(void, glLinkProgram, GLuint program);
HT_CREATE_FUNCTION_POINTER(void, glValidateProgram, GLuint program);
HT_CREATE_FUNCTION_POINTER(void, glDeleteShader, GLuint shader);
HT_CREATE_FUNCTION_POINTER(void, glUseProgram, GLuint program);
HT_CREATE_FUNCTION_POINTER(void, glDeleteProgram, GLuint program);
HT_CREATE_FUNCTION_POINTER(void, glDetachShader, GLuint program, GLuint shader);
HT_CREATE_FUNCTION_POINTER(void, glGetProgramiv, GLuint program, GLenum pname, GLint *params);
HT_CREATE_FUNCTION_POINTER(void, glGetProgramInfoLog, GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog);

extern bool GLInit();

#define WGL_DRAW_TO_WINDOW_ARB						0x2001
#define WGL_SUPPORT_OPENGL_ARB						0x2010
#define WGL_DOUBLE_BUFFER_ARB						0x2011
#define WGL_PIXEL_TYPE_ARB							0x2013
#define WGL_TYPE_RGBA_ARB							0x202B
#define WGL_COLOR_BITS_ARB							0x2014
#define WGL_DEPTH_BITS_ARB							0x2022
#define WGL_STENCIL_BITS_ARB						0x2023
#define WGL_CONTEXT_MAJOR_VERSION_ARB				0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB				0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB					0x2093
#define WGL_CONTEXT_FLAGS_ARB						0x2094
#define WGL_CONTEXT_DEBUG_BIT_ARB					0x00000001
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB			0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB	0x00000002
#define WGL_CONTEXT_PROFILE_MASK_ARB				0x9126

typedef BOOL(WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);

extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

extern bool wglInit();

#endif // HT_OPENGL