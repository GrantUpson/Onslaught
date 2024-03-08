#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <utility>
#include "window.h"


static void ErrorCallback(int error, const char* description) {
    //TODO Error callback
}


Window::Window(std::string title, bool windowedModeEnabled, bool vSyncEnabled, uint32 width, uint32 height) {
    this->title = std::move(title);
    this->windowedModeEnabled = windowedModeEnabled;
    this->vSyncEnabled = vSyncEnabled;
    this->width = width;
    this->height = height;

    glfwSetErrorCallback(ErrorCallback);

    if(!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);//
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//

    if(!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, width, height);

    if(windowedModeEnabled) {
        glfwSetWindowMonitor(window, nullptr, 0, 0, width, height, mode->refreshRate);//
        glfwSetWindowPos(window, (mode->width - width) / 2, (mode->height - height) / 2);
    }
}


void Window::Close() const {
    glfwDestroyWindow(window);
    glfwTerminate();
}


bool Window::WindowedModeEnabled() const {
    return windowedModeEnabled;
}


bool Window::VSyncEnabled() const {
    return vSyncEnabled;
}


uint32 Window::GetWidth() const {
    return width;
}


uint32 Window::GetHeight() const {
    return height;
}


GLFWwindow* Window::GetWindow() const {
    return window;
}









