#include "Window.hpp"

#include <stb_image.h>
#include <FileReader/FileReader.hpp>

Window::Window(const std::string& windowName, XMINT2 windowSize) : WindowSize_(windowSize), WindowName_(windowName)
{
}

Window::~Window()
{
    if(WindowInstance_)
        glfwTerminate();
}

void Window::InitializeWindow(bool fullScreen)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    if(fullScreen)
        WindowInstance_ = glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width, glfwGetVideoMode(glfwGetPrimaryMonitor())->height, WindowName_.c_str(), glfwGetPrimaryMonitor(), nullptr);
    else
        WindowInstance_ = glfwCreateWindow(WindowSize_.x, WindowSize_.y, WindowName_.c_str(), nullptr, nullptr);

    //glfwSetInputMode(WindowInstance_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    int width, height, channels;
    std::string path = FileReader::GetFullPath("External/Resources/RendererIcon.png");
    unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 4);

    GLFWimage image[1];
    image[0].width = width;
    image[0].height = height;
    image[0].pixels = pixels;

    glfwSetWindowIcon(WindowInstance_, 1, image);
}

void Window::ProcessMessage()
{
    glfwPollEvents();
}


