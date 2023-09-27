#pragma once

#include <vector>
#include <d3d11.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <wrl.h>

using namespace Microsoft::WRL;

class Window;
class DeviceObject;

class TextureView;
struct TextureViewObjectDesc;

class BufferObject;
struct BufferDesc;

class Pipeline;
struct PipelineDesc;

class SamplerState;

class Shader;
struct ShaderDesc;

class CommandList;

class GraphicsDevice
{
public:
    GraphicsDevice(Window* window);
    GraphicsDevice(const GraphicsDevice&) = delete;
    GraphicsDevice& operator=(const GraphicsDevice&) = delete;
    ~GraphicsDevice();

    void CreateDevice();
    void CreateSwapchain();
    void CreateRenderTargetView();
    void CreateDepthStencilView();

    TextureView* CreateTextureView(TextureViewObjectDesc& desc);
    BufferObject* CreateBufferObject(BufferDesc& desc);
    Pipeline* CreatePipeline(PipelineDesc& desc);
    SamplerState* CreateSamplerState(D3D11_SAMPLER_DESC& desc);
    Shader* CreateShader(ShaderDesc& desc);
    CommandList* CreateCommandList();

    ComPtr<ID3D11DeviceContext>& GetImmediateContext() { return ImmediateContext_; }
    ComPtr<ID3D11Device>& GetDevice() { return Device_; }

    Window& GetWindow() { return *Window_; }

    ComPtr<IDXGISwapChain>& GetSwapchain() { return Swapchain_; }
    ComPtr<ID3D11RenderTargetView>& GetRenderTargetView() { return RenderTargetView_; }
    ComPtr<ID3D11DepthStencilView>& GetDepthStencilView() { return DepthStencilBuffer_; }

    void Present();
private:
    Window* Window_;
    ComPtr<ID3D11Device> Device_;
    ComPtr<ID3D11DeviceContext> ImmediateContext_;
    ComPtr<IDXGISwapChain> Swapchain_;
    ComPtr<ID3D11RenderTargetView> RenderTargetView_;
    ComPtr<ID3D11DepthStencilView> DepthStencilBuffer_;

    std::vector<DeviceObject*> DeviceObjects_;
};
