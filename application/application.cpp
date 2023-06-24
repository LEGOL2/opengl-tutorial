#include "application.hpp"

#include <iostream>

Application::Application(uint32_t width, uint32_t height) {
	CreateWindow(width, height);

}

Application::~Application() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::RenderLoop() {
	while (!glfwWindowShouldClose(window)) {
		ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


void Application::CreateWindow(uint32_t width, uint32_t height) {
	if (!glfwInit()) {
		[[unlikely]]
		std::cout << "Failed to initialize GLFW" << std::endl;
		std::abort();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, "OpenGL tutorial", nullptr, nullptr);
	if (!window ) { [[unlikely]] std::abort(); }
	glfwMakeContextCurrent(window);

	if (GLEW_OK != glewInit()) { [[unlikely]] std::abort(); }

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });
}

void Application::ProcessInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
