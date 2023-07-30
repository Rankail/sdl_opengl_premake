#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include "Shader.h"
#include "math/math.h"

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
	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	glViewport(0, 0, w, h);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};

	unsigned indices[36] = {0};
	for (int i = 0; i < 36; i++) {
		indices[i] = (unsigned)i;
	}


	unsigned vbo;
	glGenBuffers(1, &vbo);

	unsigned ebo;
	glGenBuffers(1, &ebo);

    unsigned vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	
	Shader shader = Shader();
	shader.addSourceAndCompile("./rsc/basic.vert", GL_VERTEX_SHADER);
	shader.addSourceAndCompile("./rsc/basic.frag", GL_FRAGMENT_SHADER);
	if (!shader.link()) {
        return -2;
    }

	auto model = Matrix<4, 4, float>::unit();

	auto view = Matrix<4, 4, float>::unit();
	view.set(3, 2, -3);

	auto projection = Matrix<4, 4, float>::perspective(std::numbers::pi / 4., 800.f / 600.f, 0.1f, 100.f);
	
	bool quit = false;
	SDL_Event event;

	SDL_SetRelativeMouseMode(SDL_TRUE);

	auto objColor = Matrix<3, 1, float>(1.f, 0.5f, 0.31f);
	auto lightPos = Matrix<3, 1, float>(1.2f, 1.0f, 2.0f);

	uint32_t prevTime = SDL_GetTicks();
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_MOUSEMOTION) {
				view.rotateXZ(-event.motion.xrel / 100.);
				view.rotateYZ(-event.motion.yrel / 100.);
			}
		}

		uint32_t curTime = SDL_GetTicks();
		float dt = (curTime - prevTime) / 1000.f;
		prevTime = curTime;

		constexpr float moveSpeed = 1.f;
		const Uint8* keys = SDL_GetKeyboardState(nullptr);
		if (keys[SDL_SCANCODE_ESCAPE]) {
			quit = true;
		}
		if (keys[SDL_SCANCODE_S]) {
			view.translate(0.f, 0.f, -moveSpeed * dt);
		}
		if (keys[SDL_SCANCODE_W]) {
			view.translate(0.f, 0.f, moveSpeed * dt);
		}
		if (keys[SDL_SCANCODE_A]) {
			view.translate(moveSpeed * dt, 0.f, 0.f);
		}
		if (keys[SDL_SCANCODE_D]) {
			view.translate(-moveSpeed * dt, 0.f, 0.f);
		}

		constexpr float speed = 1.f;
		model.rotate(speed * dt, speed * dt, speed * dt);
		
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		shader.use();

		shader.setMatrix("model", model);
		shader.setMatrix("view", view);
		shader.setMatrix("projection", projection);
		shader.setVector("objectColor", objColor);
		shader.setVector("lightPos", lightPos);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		
		SDL_GL_SwapWindow(window);
	}
	
	SDL_GL_DeleteContext(context);
	
	SDL_DestroyWindow(window);
	SDL_Quit();

    return 0;
}