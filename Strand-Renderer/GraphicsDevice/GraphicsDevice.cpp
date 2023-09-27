#include "GraphicsDevice.hpp"

#include <Window/Window.hpp>
#include <TextureView/TextureView.hpp>
#include <BufferObject/BufferObject.hpp>
#include <Sampler/SamplerState.hpp>
#include <Pipeline/Pipeline.hpp>
#include <Shader/Shader.hpp>
#include <CommandList/CommandList.hpp>

GraphicsDevice::GraphicsDevice(Window* window)
{
    Window_ = window;
}

GraphicsDevice::~GraphicsDevice()
{
    ImmediateContext_->Release();
    Device_->Release();
    Swapchain_->Release();
}

void GraphicsDevice::CreateSwapchain()
{
    DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};

    SwapChainDesc.BufferDesc.Width = 0;
    SwapChainDesc.BufferDesc.Height = 0;

    SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    SwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    SwapChainDesc.BufferDesc.RefreshRate.Denominator = 0;

    SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

    SwapChainDesc.SampleDesc.Count = 1;
    SwapChainDesc.SampleDesc.Quality = 0;

    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDesc.BufferCount = 3;

    SwapChainDesc.OutputWindow = Window_->GetWindowHandle();
    SwapChainDesc.Windowed = true;
    SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    SwapChainDesc.Flags = 0;

    ComPtr<IDXGIDevice> dxgiDevice;
    ComPtr<IDXGIAdapter> dxgiAdapter;
    ComPtr<IDXGIFactory> dxgiFactory;

    Device_.As(&dxgiDevice);
    dxgiDevice->GetParent(IID_PPV_ARGS(&dxgiAdapter));
    dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
    HRESULT hr = dxgiFactory->CreateSwapChain(Device_.Get(), &SwapChainDesc, &Swapchain_);

    if(FAILED(hr)) {
        std::exception("Failed to create swapchain.");
    }
}

void GraphicsDevice::CreateDevice()
{
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION,
                                   &Device_, nullptr, &ImmediateContext_);

    if(FAILED(hr)) {
        std::exception("Failed to create device.");
    }
}

void GraphicsDevice::CreateRenderTargetView()
{
    ComPtr<ID3D11Texture2D> backBuffer;

    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc{};
    renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    Swapchain_->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    HRESULT hr = Device_->CreateRenderTargetView(backBuffer.Get(), &renderTargetViewDesc, &RenderTargetView_);

    if(FAILED(hr)) {
        std::exception("Failed to create render target view.");
    }
}

void GraphicsDevice::CreateDepthStencilView()
{
    D3D11_TEXTURE2D_DESC depthStencilDesc = {};
    depthStencilDesc.Width = Window_->GetWindowSize().x;
    depthStencilDesc.Height = Window_->GetWindowSize().y;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    ComPtr<ID3D11Texture2D> depthStencilBuffer;
    HRESULT hr = Device_->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilBuffer);

    if(FAILED(hr)) {
        std::exception("Failed to create depth stencil buffer.");
    }

    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    hr = Device_->CreateDepthStencilView(depthStencilBuffer.Get(), &depthStencilViewDesc, &DepthStencilBuffer_);

    if(FAILED(hr)) {
        std::exception("Failed to create depth stencil view.");
    }
}

TextureView* GraphicsDevice::CreateTextureView(TextureViewObjectDesc& desc)
{
    DeviceObject* textureView = new TextureView(this, desc);
    DeviceObjects_.push_back(textureView);

    return static_cast<TextureView*>(textureView);
}

BufferObject* GraphicsDevice::CreateBufferObject(BufferDesc& desc)
{
    DeviceObject* bufferObject = new BufferObject(this, desc);
    DeviceObjects_.push_back(bufferObject);

    return static_cast<BufferObject*>(bufferObject);
}

Pipeline* GraphicsDevice::CreatePipeline(PipelineDesc& desc)
{
    DeviceObject* pipeline = new Pipeline(this, desc);
    DeviceObjects_.push_back(pipeline);

    return static_cast<Pipeline*>(pipeline);
}

SamplerState* GraphicsDevice::CreateSamplerState(D3D11_SAMPLER_DESC& desc)
{
    DeviceObject* samplerState = new SamplerState(this, desc);
    DeviceObjects_.push_back(samplerState);

    return static_cast<SamplerState*>(samplerState);
}

Shader* GraphicsDevice::CreateShader(ShaderDesc& desc)
{
    DeviceObject* shader = new Shader(this, desc);
    DeviceObjects_.push_back(shader);

    return static_cast<Shader*>(shader);
}

CommandList* GraphicsDevice::CreateCommandList()
{
    DeviceObject* commandList = new CommandList(this);
    DeviceObjects_.push_back(commandList);

    return static_cast<CommandList*>(commandList);
}

void GraphicsDevice::Present()
{
    Swapchain_->Present(1, 0);
}


