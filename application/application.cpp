#include "application.hpp"

#include <iostream>
#include <fstream>
#include <vector>

struct StringHelper {
	const char* p;
	StringHelper(const std::string& s) : p(s.c_str()) {}
	operator const char** () { return &p; }
};

Application::Application(uint32_t width, uint32_t height) {
	CreateWindow(width, height);

}

Application::~Application() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLuint Application::CreateProgram(std::filesystem::path vertex_shader_path, std::filesystem::path fragment_shader_path) {
	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_path);
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_path);
	auto shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	GLint result;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &result);
	if (!result) {
		GLint log_size;
		glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &log_size);
		std::vector<char> log(log_size);
		glGetProgramInfoLog(shader_program, log_size, nullptr, log.data());
		std::cout << "Program linking failed: " << log.data() << std::endl;
		std::abort();
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return shader_program;
}

GLuint Application::CreateShader(GLenum shader_type, std::filesystem::path shader_path) {
	auto shader = glCreateShader(shader_type);
	std::ifstream source_file(shader_path);
	if (!source_file.is_open()) {
		std::abort();
	}
	std::stringstream source;
	source << source_file.rdbuf();
	glShaderSource(shader, 1, StringHelper(source.str()), nullptr);
	glCompileShader(shader);
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLint log_size;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
		std::vector<char> log(log_size);
		glGetShaderInfoLog(shader, log_size, nullptr, log.data());
		std::cout << "Shader compilation failed: " << log.data() << std::endl;
		std::abort();
	}

	return shader;
}

void Application::RenderLoop() {
	while (!glfwWindowShouldClose(window)) {
		ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


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
