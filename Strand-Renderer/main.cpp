#include <vector>
#include <DirectXMath.h>

#include <Application/Application.hpp>

#include <Window/Window.hpp>
#include <GraphicsDevice/GraphicsDevice.hpp>

#include <Shader/Shader.hpp>
#include <Pipeline/Pipeline.hpp>
#include <Sampler/SamplerState.hpp>
#include <BufferObject/BufferObject.hpp>
#include <CommandList/CommandList.hpp>

using namespace DirectX;

struct Vertex
{
    XMFLOAT3 Position;
    XMFLOAT4 Color;
};

std::vector<uint16_t> indices = {0, 2, 1, 2, 3, 1};
std::vector<Vertex> triangle =
        {
                {{-0.5f, -0.5f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
                {{0.5f,  -0.5f, -1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
                {{-0.5f, 0.5f,  -1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}},
                {{0.5f,  0.5f,  1.0f},  {1.0f, 0.0f, 1.0f, 1.0f}}
        };

int main()
{
    Application* app = new Application("Strand Renderer", {1280, 720}, false);

    app->Initialize();
    app->Run();

    return 0;
}
