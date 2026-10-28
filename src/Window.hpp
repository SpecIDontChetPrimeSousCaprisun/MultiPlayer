#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Node.hpp"

class Window {
public:
    static int init();
    static void mainLoop();

    static Node parent;
private:
    static void frameBufferSizeCallback(GLFWwindow*, int newWidth, int newHeight);

    static GLFWwindow* window;
    static int fbWidth;
    static int fbHeight;
};
