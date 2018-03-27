#ifdef HT_OPENGL
#pragma once

#if defined(HT_WINDOWS)
#include <Windows.h>
#include <gl/GL.h>
#elif defined(HT_LINUX)
#include <GL/glx.h>
#endif

#define HT_FUNCTION_NAME(function) PFN##function##PROC
#ifdef HT_WINDOWS
#define HT_APIENTRY __stdcall
typedef void (*HT_PROC)();
#else
#define HT_APIENTRY
typedef void (*HT_PROC)();
#endif

#define HT_CREATE_FUNCTION_POINTER(returntype, function, ...) typedef returntype(HT_APIENTRY * HT_FUNCTION_NAME(function)) (__VA_ARGS__); \
		extern HT_FUNCTION_NAME(function) function

#if !defined(HT_LINUX)
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
#endif // These typedefs are already defined for linux


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
#define GL_STREAM_DRAW 0x88E0
#define GL_WRITE_ONLY 0x88B9

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
HT_CREATE_FUNCTION_POINTER(void*, glMapNamedBuffer, GLuint buffer, GLenum access);
HT_CREATE_FUNCTION_POINTER(GLboolean, glUnmapNamedBuffer, GLuint buffer);
HT_CREATE_FUNCTION_POINTER(void, glNamedBufferSubData, GLuint buffer, GLsizeiptr offset, GLsizei size, const void* data);
HT_CREATE_FUNCTION_POINTER(void, glBindBufferBase, GLenum target, GLuint index, GLuint buffer);
HT_CREATE_FUNCTION_POINTER(void, glBufferSubData, GLenum target, GLsizeiptr offset, GLsizeiptr size, const GLvoid* data);
HT_CREATE_FUNCTION_POINTER(void*, glMapBuffer, GLenum target, GLenum access);
HT_CREATE_FUNCTION_POINTER(GLboolean, glUnmapBuffer, GLenum target);

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
HT_CREATE_FUNCTION_POINTER(GLuint, glGetUniformBlockIndex, GLuint program, const GLchar* uniformBlockName);
HT_CREATE_FUNCTION_POINTER(void, glUniformBlockBinding, GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
HT_CREATE_FUNCTION_POINTER(void, glUniform1iv, GLint location, GLsizei count, const GLint* value);
HT_CREATE_FUNCTION_POINTER(GLint, glGetUniformLocation, GLuint program, const GLchar* name);

//Texture
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8
#define GL_TEXTURE9 0x84C9
#define GL_TEXTURE10 0x84CA
#define GL_TEXTURE11 0x84CB
#define GL_TEXTURE12 0x84CC
#define GL_TEXTURE13 0x84CD
#define GL_TEXTURE14 0x84CE
#define GL_TEXTURE15 0x84CF
#define GL_TEXTURE16 0x84D0
#define GL_TEXTURE17 0x84D1
#define GL_TEXTURE18 0x84D2
#define GL_TEXTURE19 0x84D3
#define GL_TEXTURE20 0x84D4
#define GL_TEXTURE21 0x84D5
#define GL_TEXTURE22 0x84D6
#define GL_TEXTURE23 0x84D7
#define GL_TEXTURE24 0x84D8
#define GL_TEXTURE25 0x84D9
#define GL_TEXTURE26 0x84DA
#define GL_TEXTURE27 0x84DB
#define GL_TEXTURE28 0x84DC
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF
#define GL_BGRA 0x80E1

#if !defined(HT_LINUX)
HT_CREATE_FUNCTION_POINTER(void, glActiveTexture, GLenum texture);
#endif

extern bool GLInit();

#if defined(HT_WINDOWS)

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
typedef BOOL(WINAPI *PFNWGLSWAPINTERVALEXTPROC) (int interval);

extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
extern PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
extern bool wglInit();

#endif // HT_WINDOWS

#endif // HT_OPENGL
