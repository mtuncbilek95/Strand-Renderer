#include "SamplerState.hpp"

#include <exception>
#include <GraphicsDevice/GraphicsDevice.hpp>

SamplerState::SamplerState(GraphicsDevice* device, D3D11_SAMPLER_DESC& desc)
{
    HRESULT hr = device->GetDevice()->CreateSamplerState(&desc, &SamplerState_);
    if(FAILED(hr)) {
        throw std::exception("Failed to create sampler state.");
    }

    GraphicsDevice_ = device;
    Desc_ = desc;
}
