#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application {
public:
	Application(uint32_t width, uint32_t height);
	~Application();

	void RenderLoop();

private:
	void CreateWindow(uint32_t width, uint32_t height);
	void ProcessInput();

	GLFWwindow* window;
};
