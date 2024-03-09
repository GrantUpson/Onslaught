#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "GLFW/glfw3.h"
#include "types.h"


class Window {
public:
    explicit Window(std::string title = "Onslaught", bool windowedModeEnabled = true, bool vSyncEnabled = true, uint32 width = 640, uint32 height = 360);
    ~Window() = default;

    bool WindowedModeEnabled() const;
    bool VSyncEnabled() const;
    uint32 GetWidth() const;
    uint32 GetHeight() const;
    GLFWwindow* GetWindow() const;

    void Close() const;

private:
    std::string title;
    bool windowedModeEnabled;
    bool vSyncEnabled;
    uint32 width;
    uint32 height;
    GLFWwindow* window;
};


#endif
