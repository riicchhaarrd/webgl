#include "sdl.h"

Uint32 SDL_GetTicks()
{
	return 0;
}
SDL_Window *SDL_CreateWindow(const char *title, int x, int y, int w, int h, Uint32 flags)
{
	return NULL;
}
int SDL_CreateWindowAndRenderer(int width,
								int height,
								Uint32 window_flags,
								SDL_Window **window,
								SDL_Renderer **renderer)
{
	return 0;
}

int SDL_GL_SetAttribute(SDL_GLattr attr, int value)
{
	return 0;
}

void SDL_Quit(void)
{
}

const char *SDL_GetError(void)
{
	return NULL;
}

void SDL_GL_SwapWindow(SDL_Window *wnd)
{
}
int SDL_Init(Uint32 flags)
{
	return 0;
}
void SDL_LogError(int category, const char *fmt, ...)
{
}

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
	return NULL;
}
