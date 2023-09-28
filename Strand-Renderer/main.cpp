#include <Application/Application.hpp>

int main()
{
    Application* app = new Application("Strand Renderer", {1280, 720}, false);

    app->Initialize();
    app->Run();

    return 0;
}
