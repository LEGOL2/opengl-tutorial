#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <filesystem>

class Application {
public:
	Application(uint32_t width, uint32_t height);
	~Application();

	GLuint CreateProgram(std::filesystem::path vertex_shader_path, std::filesystem::path fragment_shader_path);
	GLuint CreateShader(GLenum shader_type, std::filesystem::path shader_path);
	void RenderLoop();

private:
	void CreateWindow(uint32_t width, uint32_t height);
	void ProcessInput();

	GLFWwindow* window;
};
