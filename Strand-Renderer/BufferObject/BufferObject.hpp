#pragma once

#include "GraphicsDevice/DeviceObject.hpp"

#include <d3d11.h>
#include <wrl.h>

using namespace Microsoft::WRL;

struct BufferDesc{
    D3D11_BUFFER_DESC Desc;
    D3D11_SUBRESOURCE_DATA InitialData;
};

class BufferObject : public DeviceObject
{
public:
    BufferObject(GraphicsDevice* device, BufferDesc& desc);
    BufferObject(const BufferObject&) = delete;
    BufferObject& operator=(const BufferObject&) = delete;
    ~BufferObject() = default;

    DeviceObjectType GetDeviceObjectType() override
    { return DeviceObjectType::BufferObject; }

    ComPtr<ID3D11Buffer>& GetBuffer() { return Buffer_; }
    BufferDesc& GetDesc() { return Desc_; }
private:
    ComPtr<ID3D11Buffer> Buffer_;
    BufferDesc Desc_;
};
