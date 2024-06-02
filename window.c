#include "window.h"
#include <stdbool.h>
#include <stdint.h>
#include "opengl.h"

static SDL_GLContext gl_context = NULL;
static SDL_Window *window = NULL;

void destroy_window()
{
#ifndef BUILD_TARGET_WEB
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();
#endif
}

void swap_window()
{
	if(!window)
		return;
	SDL_GL_SwapWindow(window);
}

SDL_Window *create_window()
{

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}

	SDL_Renderer *renderer = NULL;
	SDL_CreateWindowAndRenderer(1280, 960, SDL_WINDOW_OPENGL, &window, &renderer);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("OpenGL Window",
										  SDL_WINDOWPOS_UNDEFINED,
										  SDL_WINDOWPOS_UNDEFINED,
										  1280,
										  960,
										  SDL_WINDOW_OPENGL);
	if(!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}

	gl_context = SDL_GL_CreateContext(window);

	#ifndef BUILD_TARGET_WEB
	if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize OpenGL context!\n");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return NULL;
	}
	#endif
	return window;
}
