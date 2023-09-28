#pragma once

#include <string>

#include <DirectXMath.h>

using namespace DirectX;

class Window;
class GraphicsDevice;
class Pipeline;
class GameTimer;

class Application
{
public:
    Application(std::string appName, XMINT2 windowSize, bool fullScreen);
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    ~Application() = default;

    void Initialize();

    void Run();
private:
    Window* window;

    Pipeline* basicPipeline;
    GameTimer* timer;
};
