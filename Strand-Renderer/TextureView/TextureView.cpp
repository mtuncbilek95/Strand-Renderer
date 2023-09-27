#include "TextureView.hpp"

#include <exception>
#include <GraphicsDevice/GraphicsDevice.hpp>

TextureView::TextureView(GraphicsDevice* device, TextureViewObjectDesc& desc)
{
    HRESULT hr = device->GetDevice()->CreateTexture2D(&desc.TextureDesc, desc.SubresourceData, &TextureBuffer_);
    if (FAILED(hr))
    {
        throw std::exception("Failed to create texture 2d.");
    }

    hr = device->GetDevice()->CreateShaderResourceView(TextureBuffer_.Get(), &desc.ResourceDesc, &ShaderResourceView_);
    if (FAILED(hr))
    {
        throw std::exception("Failed to create shader resource view.");
    }

    GraphicsDevice_ = device;
    Desc_ = desc;
}
