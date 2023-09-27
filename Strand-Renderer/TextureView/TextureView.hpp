#pragma once

#include <d3d11.h>
#include <wrl.h>

using namespace Microsoft::WRL;

#include <GraphicsDevice/DeviceObject.hpp>

struct TextureViewObjectDesc
{
    D3D11_TEXTURE2D_DESC TextureDesc;
    D3D11_SHADER_RESOURCE_VIEW_DESC ResourceDesc;
    D3D11_SUBRESOURCE_DATA* SubresourceData;
};

class GraphicsDevice;

class TextureView : public DeviceObject
{
public:
    TextureView(GraphicsDevice* device, TextureViewObjectDesc& desc);
    TextureView(const TextureView&) = delete;
    TextureView& operator=(const TextureView&) = delete;
    ~TextureView() {};

    DeviceObjectType GetDeviceObjectType() override
    { return DeviceObjectType::TextureView; }

    ComPtr<ID3D11ShaderResourceView>& GetShaderResourceView() { return ShaderResourceView_; }
    ComPtr<ID3D11Texture2D>& GetTextureBuffer() { return TextureBuffer_; }
    TextureViewObjectDesc& GetDesc() { return Desc_; }

private:
    ComPtr<ID3D11ShaderResourceView> ShaderResourceView_;
    ComPtr<ID3D11Texture2D> TextureBuffer_;
    TextureViewObjectDesc Desc_;
};
