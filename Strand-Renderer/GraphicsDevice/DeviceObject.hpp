#pragma once

enum class DeviceObjectType
{
    None,
    TextureView,
    BufferObject,
    Pipeline,
    SamplerState,
    Shader,
    CommandList
};

class GraphicsDevice;

class DeviceObject
{
public:
    DeviceObject() = default;
    DeviceObject(const DeviceObject&) = delete;
    DeviceObject& operator=(const DeviceObject&) = delete;
    ~DeviceObject() = default;

    virtual DeviceObjectType GetDeviceObjectType()
    { return DeviceObjectType::None; }
protected:
    GraphicsDevice* GraphicsDevice_;
};
