#pragma once
#include <stdio.h>

#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#ifdef BUILD_TARGET_WEB
	#include <GLES2/gl2.h>
#else
	#include <glad/glad.h>
#endif
#define CHECK_GL_ERROR() checkGLError(__FILE__, __LINE__)

static void checkGLError(const char *file, int line)
{
	GLenum err;
	while((err = glGetError()) != GL_NO_ERROR)
	{
		printf("OpenGL error in file %s at line %d: 0x%02X\n", file, line, err);
	}
}
