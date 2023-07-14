#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include "Shader.h"

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize SDL! Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	SDL_Window* window = SDL_CreateWindow("sdl opengl test 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		std::cout << "Failed to create window! Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		std::cout << "Failed to create OpenGL context! Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	
	gladLoadGLLoader(SDL_GL_GetProcAddress);

    std::cout << "OpenGL loaded"
        << "\nVendor:   " << glGetString(GL_VENDOR)
        << "\nRenderer: " << glGetString(GL_RENDERER)
        << "\nVersion:  " << glGetString(GL_VERSION)
        << std::endl;
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	glViewport(0, 0, w, h);
	
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f
	};

	unsigned vbo;
	glGenBuffers(1, &vbo);

    unsigned vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	
	Shader shader = Shader();
	shader.addSourceAndCompile("./rsc/basic.vert", GL_VERTEX_SHADER);
	shader.addSourceAndCompile("./rsc/basic.frag", GL_FRAGMENT_SHADER);
	if (!shader.link()) {
        return -2;
    }
	
	bool quit = false;
	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				quit = true;
			}
		}
		
		glClearColor(0.f, 0.1f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
		shader.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
		
		SDL_GL_SwapWindow(window);
	}
	
	SDL_GL_DeleteContext(context);
	
	SDL_DestroyWindow(window);
	SDL_Quit();

    return 0;
}