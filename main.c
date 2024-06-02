#include "opengl.h"
#include <sys/types.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#ifdef BUILD_TARGET_WEB
	#include <start.h>
#endif
#include "window.h"

unsigned int ticks()
{
	return SDL_GetTicks();
}

#ifdef BUILD_TARGET_WEB
// Functions defined in loader.js
void WAJS_SetupCanvas(int width, int height);
unsigned int WAJS_GetTime();
#else
SDL_Window *wnd;
void WAJS_SetupCanvas(int width, int height)
{
	wnd = create_window();
}
unsigned int WAJS_GetTime()
{
	return SDL_GetTicks();
}

#endif

static const char* vertex_shader_text =
	"precision lowp float;"
	"uniform mat4 uMVP;"
	"attribute vec4 aPos;"
	"attribute vec3 aCol;"
	"varying vec3 vCol;"
	"void main()"
	"{"
		"vCol = aCol;"
		"gl_Position = uMVP * aPos;"
	"}";

static const char* fragment_shader_text =
	"precision lowp float;"
	"varying vec3 vCol;"
	"void main()"
	"{"
		"gl_FragColor = vec4(vCol, 1.0);"
	"}";

typedef struct Vertex { float x, y, r, g, b; } Vertex;
static GLuint program, vertex_buffer;
static GLint uMVP_location, aPos_location, aCol_location;

// This function is called at startup
int main(int argc, char *argv[])
{
	printf("yooo yo yo\n");
	WAJS_SetupCanvas(640, 480);
	glViewport(0, 0, 640, 480);

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	uMVP_location = glGetUniformLocation(program, "uMVP");
	aPos_location = glGetAttribLocation(program, "aPos");
	aCol_location = glGetAttribLocation(program, "aCol");

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

	glEnableVertexAttribArray(aPos_location);
	glVertexAttribPointer(aPos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(aCol_location);
	glVertexAttribPointer(aCol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 2));

#ifndef BUILD_TARGET_WEB

	unsigned int last_frame_time = ticks();
	bool quit = false;
	while(!quit)
	{
		unsigned int now = ticks();
		unsigned int delta_time = now - last_frame_time;
		if(delta_time > 0)
		{
			float dt = (float)delta_time / 1000.f;
			/* main_loop_update(dt); */
			void WAFNDraw();
			WAFNDraw();
		}
		last_frame_time = now;
	}
#else
	/* emscripten_set_main_loop(main_loop_update, 0, 1); */
#endif
	return 0;
}

// This function is called by loader.js every frame
void WAFNDraw()
{
	float f = ((WAJS_GetTime() % 1000) / 1000.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	Vertex vertices[3] =
	{
		{ -0.6f, -0.4f, 1.f, 0.f, 0.f },
		{  0.6f, -0.4f, 0.f, 0.f, 1.f },
		{   0.f,  0.6f, 1.f, 1.f, 1.f },
	};
	vertices[0].r = 0.5f + sinf(f * 3.14159f * 2.0f) * 0.5f;
	vertices[1].b = 0.5f + cosf(f * 3.14159f * 2.0f) * 0.5f;
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLfloat mvp[4*4] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1 };
	glUseProgram(program);
	glUniformMatrix4fv(uMVP_location, 1, GL_FALSE, mvp);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	swap_window();
}
