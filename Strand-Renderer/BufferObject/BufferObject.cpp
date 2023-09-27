#include "BufferObject.hpp"

#include "GraphicsDevice/GraphicsDevice.hpp"

BufferObject::BufferObject(GraphicsDevice* device, BufferDesc& desc)
{
    HRESULT hr = device->GetDevice()->CreateBuffer(&desc.Desc, &desc.InitialData, &Buffer_);
    if (FAILED(hr))
    {
        throw std::exception("Failed to create buffer object.");
    }

    GraphicsDevice_ = device;
    Desc_ = desc;
}
