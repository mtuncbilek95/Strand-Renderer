#pragma once

#include "GraphicsDevice/DeviceObject.hpp"

#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <Shader/Shader.hpp>

using namespace Microsoft::WRL;

class SamplerState;

struct PipelineDesc
{
    std::vector<Shader*> Shaders;
    std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayoutDesc;
    D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
    D3D11_RASTERIZER_DESC RasterizerDesc;
    D3D11_RENDER_TARGET_BLEND_DESC BlendDesc;
    D3D11_BLEND_DESC BlendStateDesc;

    SamplerState* SamplerState;
};

class Pipeline : public DeviceObject
{
public:
    Pipeline(GraphicsDevice* device, PipelineDesc& desc);
    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;
    ~Pipeline() = default;

    ComPtr<ID3D11InputLayout>& GetInputLayout() { return InputLayout_; }
    ComPtr<ID3D11DepthStencilState>& GetDepthStencilState() { return DepthState_; }
    ComPtr<ID3D11RasterizerState>& GetRasterizerState() { return RasterizerState_; }
    ComPtr<ID3D11BlendState>* GetBlendState() { return &BlendState_; }
    ComPtr<ID3D11SamplerState>& GetSamplerState() { return SamplerState_; }

    std::vector<Shader*> GetShader(ShaderType type);
    const PipelineDesc& GetDesc() const { return Desc_; }

    DeviceObjectType GetDeviceObjectType() override
    { return DeviceObjectType::Pipeline; }

private:
    PipelineDesc Desc_;

    ComPtr<ID3D11InputLayout> InputLayout_;
    ComPtr<ID3D11DepthStencilState> DepthState_;
    ComPtr<ID3D11RasterizerState> RasterizerState_;
    ComPtr<ID3D11BlendState> BlendState_;
    ComPtr<ID3D11SamplerState> SamplerState_;

};
