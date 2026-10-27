#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    static int init();
    static void mainLoop();
private:
    static void frameBufferSizeCallback(GLFWwindow*, int newWidth, int newHeight);

    static GLFWwindow* window;
    static int fbWidth;
    static int fbHeight;
};
