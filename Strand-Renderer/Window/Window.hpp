#pragma once

#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "glfw3native.h"

#include <string>

#include <DirectXMath.h>

using namespace DirectX;

class Window
{
public:
    Window(const std::string& windowName, XMINT2 windowSize);

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    ~Window();

    void InitializeWindow(bool fullScreen);
    void ProcessMessage();

    bool ShouldClose() const { return glfwWindowShouldClose(WindowInstance_);}
    void SetShouldClose(bool shouldClose) { glfwSetWindowShouldClose(WindowInstance_, shouldClose); }

    XMINT2 GetWindowSize() { return WindowSize_; }
    HWND GetWindowHandle() { return glfwGetWin32Window(WindowInstance_); }
    GLFWwindow* GetWindow() { return WindowInstance_; }

private:
    GLFWwindow* WindowInstance_;
    XMINT2 WindowSize_;
    const std::string WindowName_;
};
