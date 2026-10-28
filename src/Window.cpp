#include <iostream>

#include "Window.hpp"

Node Window::parent;
GLFWwindow* Window::window = nullptr;
int Window::fbWidth = 1600;
int Window::fbHeight = 1200;

void Window::frameBufferSizeCallback(GLFWwindow*, int newWidth, int newHeight) {
    fbWidth = newWidth;
    fbHeight = newHeight;
    glViewport(0, 0, fbWidth, fbHeight);
}

int Window::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(fbWidth, fbHeight, "3dgame", NULL, NULL);
    if (window == NULL) {
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	std::cout << "Failed to initialize GLAD" << std::endl;
	return 1;
    }

    glViewport(0, 0, fbWidth, fbHeight);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    return 0;
}

void Window::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT);

	parent.updateChildren();
	parent.drawChildren();

	glfwSwapBuffers(window);
    }
}
