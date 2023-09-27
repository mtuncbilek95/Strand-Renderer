#pragma once

#include "GraphicsDevice/DeviceObject.hpp"

#include <d3d11.h>
#include <wrl.h>

using namespace Microsoft::WRL;

class SamplerState : public DeviceObject
{
public:
    SamplerState(GraphicsDevice* device, D3D11_SAMPLER_DESC& desc);
    SamplerState(const SamplerState&) = delete;
    SamplerState& operator=(const SamplerState&) = delete;
    ~SamplerState() = default;

    DeviceObjectType GetDeviceObjectType() override
    { return DeviceObjectType::SamplerState; }

    ComPtr<ID3D11SamplerState>& GetSamplerState() { return SamplerState_; }
    D3D11_SAMPLER_DESC& GetDesc() { return Desc_; }

private:
    ComPtr<ID3D11SamplerState> SamplerState_;
    D3D11_SAMPLER_DESC Desc_;
};
