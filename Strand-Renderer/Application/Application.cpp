#include "Application.hpp"

#include <GameTimer/GameTimer.hpp>

#include <Window/Window.hpp>
#include <GraphicsDevice/GraphicsDevice.hpp>

#include <Shader/Shader.hpp>
#include <Pipeline/Pipeline.hpp>
#include <Sampler/SamplerState.hpp>
#include <BufferObject/BufferObject.hpp>
#include <CommandList/CommandList.hpp>

#include <World/GraphicsManager/GraphicsManager.hpp>

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


Application::Application(std::string appName, XMINT2 windowSize, bool fullScreen)
{
    GraphicsManager& graphicsManager = GraphicsManager::GetInstance();
    window = new Window(appName, windowSize);
    window->InitializeWindow(fullScreen);

    timer = new GameTimer();

    graphicsManager.GetGraphicsDevice().SetOwnerWindow(window);
    graphicsManager.GetGraphicsDevice().CreateDevice();
    graphicsManager.GetGraphicsDevice().CreateSwapchain();
    graphicsManager.GetGraphicsDevice().CreateRenderTargetView();
    graphicsManager.GetGraphicsDevice().CreateDepthStencilView();
}

void Application::Run()
{
    GraphicsManager& graphicsManager = GraphicsManager::GetInstance();
    CommandList* commandList = graphicsManager.GetGraphicsDevice().CreateCommandList();

    ShaderDesc vertexDesc = {
            .Type_ = ShaderType::Vertex,
            .Source_ = "VertexShader",
            .EntryPoint_ = "vs_main",
            .Target_ = "vs_5_0"
    };

    Shader* vertexShader = graphicsManager.GetGraphicsDevice().CreateShader(vertexDesc);

    ShaderDesc pixelDesc = {
            .Type_ = ShaderType::Pixel,
            .Source_ = "PixelShader",
            .EntryPoint_ = "ps_main",
            .Target_ = "ps_5_0"
    };

    Shader* pixelShader = graphicsManager.GetGraphicsDevice().CreateShader(pixelDesc);

    D3D11_SAMPLER_DESC samplerDesc = {
            .Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
            .AddressU = D3D11_TEXTURE_ADDRESS_WRAP,
            .AddressV = D3D11_TEXTURE_ADDRESS_WRAP,
            .AddressW = D3D11_TEXTURE_ADDRESS_WRAP,
            .MipLODBias = 1.0f,
            .MaxAnisotropy = 16,
            .ComparisonFunc = D3D11_COMPARISON_ALWAYS,
            .BorderColor = {0.0f, 0.0f, 0.0f, 0.0f},
            .MinLOD = 0.0f,
            .MaxLOD = D3D11_FLOAT32_MAX
    };
    SamplerState* samplerState = graphicsManager.GetGraphicsDevice().CreateSamplerState(samplerDesc);

    PipelineDesc basicPipelineDesc = {
            .Shaders = {vertexShader, pixelShader},
            .InputLayoutDesc = {
                    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                    {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
            },
            .DepthStencilDesc = {
                    .DepthEnable = true,
                    .DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,
                    .DepthFunc = D3D11_COMPARISON_LESS,
                    .StencilEnable = false,
                    .StencilReadMask = 0xFF,
                    .StencilWriteMask = 0xFF,
            },
            .RasterizerDesc = {
                    .FillMode = D3D11_FILL_SOLID,
                    .CullMode = D3D11_CULL_BACK,
                    .FrontCounterClockwise = false,
                    .DepthBias = 0,
                    .DepthBiasClamp = 0.0f,
                    .SlopeScaledDepthBias = 0.0f,
                    .DepthClipEnable = false,
                    .ScissorEnable = false,
                    .MultisampleEnable = true,
                    .AntialiasedLineEnable = true

            },
            .BlendDesc = {
                    .BlendEnable = true,
                    .SrcBlend = D3D11_BLEND_ONE,
                    .DestBlend = D3D11_BLEND_ONE,
                    .BlendOp = D3D11_BLEND_OP_ADD,
                    .SrcBlendAlpha = D3D11_BLEND_ONE,
                    .DestBlendAlpha = D3D11_BLEND_ONE,
                    .BlendOpAlpha = D3D11_BLEND_OP_ADD,
                    .RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL
            },
            .BlendStateDesc = {
                    .AlphaToCoverageEnable = false,
                    .IndependentBlendEnable = true,
                    .RenderTarget = {basicPipelineDesc.BlendDesc }
            },
            .SamplerState = samplerState
    };

    basicPipeline = graphicsManager.GetGraphicsDevice().CreatePipeline(basicPipelineDesc);

    BufferDesc vertexBufferDesc = {
            .Desc = {
                    .ByteWidth = static_cast<uint32_t>(sizeof(Vertex) * triangle.size()),
                    .Usage = D3D11_USAGE_DEFAULT,
                    .BindFlags = D3D11_BIND_VERTEX_BUFFER,
                    .CPUAccessFlags = 0,
                    .MiscFlags = 0,
                    .StructureByteStride = sizeof(Vertex)
            },
            .InitialData = {
                    .pSysMem = triangle.data(),
            }
    };

    BufferObject* vertexBuffer = graphicsManager.GetGraphicsDevice().CreateBufferObject(vertexBufferDesc);

    BufferDesc indexBufferDesc = {
            .Desc = {
                    .ByteWidth = static_cast<uint32_t>(sizeof(uint16_t) * indices.size()),
                    .Usage = D3D11_USAGE_DEFAULT,
                    .BindFlags = D3D11_BIND_INDEX_BUFFER,
                    .CPUAccessFlags = 0,
                    .MiscFlags = 0,
                    .StructureByteStride = sizeof(uint16_t)
            },
            .InitialData = {
                    .pSysMem = indices.data(),
            }
    };

    BufferObject* indexBuffer = graphicsManager.GetGraphicsDevice().CreateBufferObject(indexBufferDesc);

    while (!window->ShouldClose())
    {
        timer->Tick();

        window->ProcessMessage();

        commandList->BindRTV();

        commandList->BindPipeline(basicPipeline);
        commandList->BindVertexBuffer(vertexBuffer);
        commandList->BindIndexBuffer(indexBuffer);

        commandList->BindViewport();
        commandList->ClearBuffer({0.0f, 0.0f, 0.0f, 1.0f});
        commandList->DrawIndexed(indices.size(), 0, 0);

        commandList->ExecuteCommandList();

        graphicsManager.GetGraphicsDevice().Present();
    }
}

void Application::Initialize()
{
    /*ShaderDesc vertexDesc = {
            .Type_ = ShaderType::Vertex,
            .Source_ = "VertexShader",
            .EntryPoint_ = "vs_main",
            .Target_ = "vs_5_0"
    };

    Shader* vertexShader = graphicsManager.GetGraphicsDevice().CreateShader(vertexDesc);

    ShaderDesc pixelDesc = {
            .Type_ = ShaderType::Pixel,
            .Source_ = "PixelShader",
            .EntryPoint_ = "ps_main",
            .Target_ = "ps_5_0"
    };

    Shader* pixelShader = graphicsManager.GetGraphicsDevice().CreateShader(pixelDesc);

    D3D11_SAMPLER_DESC samplerDesc = {
            .Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
            .AddressU = D3D11_TEXTURE_ADDRESS_WRAP,
            .AddressV = D3D11_TEXTURE_ADDRESS_WRAP,
            .AddressW = D3D11_TEXTURE_ADDRESS_WRAP,
            .MipLODBias = 1.0f,
            .MaxAnisotropy = 16,
            .ComparisonFunc = D3D11_COMPARISON_ALWAYS,
            .BorderColor = {0.0f, 0.0f, 0.0f, 0.0f},
            .MinLOD = 0.0f,
            .MaxLOD = D3D11_FLOAT32_MAX
    };
    SamplerState* samplerState = graphicsManager.GetGraphicsDevice().CreateSamplerState(samplerDesc);

    PipelineDesc basicPipelineDesc = {
            .Shaders = {vertexShader, pixelShader},
            .InputLayoutDesc = {
                    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                    {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
            },
            .DepthStencilDesc = {
                    .DepthEnable = true,
                    .DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,
                    .DepthFunc = D3D11_COMPARISON_LESS,
                    .StencilEnable = false,
                    .StencilReadMask = 0xFF,
                    .StencilWriteMask = 0xFF,
            },
            .RasterizerDesc = {
                    .FillMode = D3D11_FILL_SOLID,
                    .CullMode = D3D11_CULL_BACK,
                    .FrontCounterClockwise = false,
                    .DepthBias = 0,
                    .DepthBiasClamp = 0.0f,
                    .SlopeScaledDepthBias = 0.0f,
                    .DepthClipEnable = false,
                    .ScissorEnable = false,
                    .MultisampleEnable = true,
                    .AntialiasedLineEnable = true

            },
            .BlendDesc = {
                    .BlendEnable = true,
                    .SrcBlend = D3D11_BLEND_ONE,
                    .DestBlend = D3D11_BLEND_ONE,
                    .BlendOp = D3D11_BLEND_OP_ADD,
                    .SrcBlendAlpha = D3D11_BLEND_ONE,
                    .DestBlendAlpha = D3D11_BLEND_ONE,
                    .BlendOpAlpha = D3D11_BLEND_OP_ADD,
                    .RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL
            },
            .BlendStateDesc = {
                    .AlphaToCoverageEnable = false,
                    .IndependentBlendEnable = true,
                    .RenderTarget = {basicPipelineDesc.BlendDesc }
            },
            .SamplerState = samplerState
    };

    basicPipeline = graphicsManager.GetGraphicsDevice().CreatePipeline(basicPipelineDesc);*/
}
