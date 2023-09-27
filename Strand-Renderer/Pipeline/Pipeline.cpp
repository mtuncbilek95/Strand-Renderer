#include "Pipeline.hpp"

#include <GraphicsDevice/GraphicsDevice.hpp>
#include <Shader/Shader.hpp>
#include <Sampler/SamplerState.hpp>

Pipeline::Pipeline(GraphicsDevice* device, PipelineDesc& desc)
{
    GraphicsDevice_ = device;
    Desc_ = desc;

    HRESULT hr;

    for(int i = 0; i < Desc_.Shaders.size(); i++)
        if(Desc_.Shaders[i]->GetShaderType() == ShaderType::Vertex)
            hr = GraphicsDevice_->GetDevice()->CreateInputLayout(Desc_.InputLayoutDesc.data(), Desc_.InputLayoutDesc.size(),
                                                                 Desc_.Shaders[i]->GetShaderBlob()->GetBufferPointer(), Desc_.Shaders[i]->GetShaderBlob()->GetBufferSize(),
                                                                 &InputLayout_);

    if(FAILED(hr))
        std::exception("Failed to create input layout");

    hr = GraphicsDevice_->GetDevice()->CreateDepthStencilState(&Desc_.DepthStencilDesc, &DepthState_);

    if(FAILED(hr))
        std::exception("Failed to create depth stencil state");

    hr = GraphicsDevice_->GetDevice()->CreateRasterizerState(&Desc_.RasterizerDesc, &RasterizerState_);

    if(FAILED(hr))
        std::exception("Failed to create rasterizer state");

    hr = GraphicsDevice_->GetDevice()->CreateBlendState(&Desc_.BlendStateDesc, &BlendState_);

    if(FAILED(hr))
        std::exception("Failed to create blend state");

    SamplerState_ = Desc_.SamplerState->GetSamplerState();
}
