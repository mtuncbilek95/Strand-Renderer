#include "CommandList.hpp"

#include <GraphicsDevice/GraphicsDevice.hpp>
#include <Window/Window.hpp>

#include <Pipeline/Pipeline.hpp>
#include <BufferObject/BufferObject.hpp>
#include <TextureView/TextureView.hpp>
#include <Shader/Shader.hpp>
#include <Sampler/SamplerState.hpp>

CommandList::CommandList(GraphicsDevice* device)
{
    GraphicsDevice_ = device;
    GraphicsDevice_->GetDevice()->CreateDeferredContext(0, DeferredContext_.GetAddressOf());
}

void CommandList::BindViewport()
{
    D3D11_VIEWPORT viewport {};
    viewport.Width = static_cast<float>(GraphicsDevice_->GetWindow().GetWindowSize().x);
    viewport.Height = static_cast<float>(GraphicsDevice_->GetWindow().GetWindowSize().y);
    viewport.TopLeftX = 0.f;
    viewport.TopLeftY = 0.f;
    viewport.MinDepth = 0.f;
    viewport.MaxDepth = 1.f;

    DeferredContext_->RSSetViewports(1, &viewport);
}

void CommandList::BindVertexBuffer(BufferObject* vertexBuffer)
{
    uint32_t stride = vertexBuffer->GetDesc().Desc.StructureByteStride;
    uint32_t offset = 0;

    DeferredContext_->IASetVertexBuffers(0, 1, vertexBuffer->GetBuffer().GetAddressOf(), &stride, &offset);
}

void CommandList::BindIndexBuffer(BufferObject* indexBuffer)
{
    DeferredContext_->IASetIndexBuffer(indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
}

void CommandList::DrawIndexed(uint32_t indexCount, uint32_t startIndexLocation, int32_t baseVertexLocation)
{
    DeferredContext_->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}

void CommandList::ClearBuffer(XMFLOAT4 color)
{
    DeferredContext_->ClearRenderTargetView(GraphicsDevice_->GetRenderTargetView().Get(), reinterpret_cast<const float*>(&color));
    DeferredContext_->ClearDepthStencilView(GraphicsDevice_->GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void CommandList::ExecuteCommandList()
{
    DeferredContext_->FinishCommandList(false, CommandList_.GetAddressOf());

    GraphicsDevice_->GetImmediateContext()->ExecuteCommandList(CommandList_.Get(), false);
}

void CommandList::BindRTV()
{
    DeferredContext_->OMSetRenderTargets(1, GraphicsDevice_->GetRenderTargetView().GetAddressOf(), GraphicsDevice_->GetDepthStencilView().Get());
}

void CommandList::BindPipeline(Pipeline* pipeline)
{
    PipelineRef_ = pipeline;

    for(auto& shader : PipelineRef_->GetDesc().Shaders) {
        switch(shader->GetShaderType()) {
            case ShaderType::Vertex:
                DeferredContext_->VSSetShader(shader->GetVertexShader().Get(), nullptr, 0);
                break;
            case ShaderType::Pixel:
                DeferredContext_->PSSetShader(shader->GetPixelShader().Get(), nullptr, 0);
                break;
            default:
                break;
        }
    }

    DeferredContext_->IASetInputLayout(pipeline->GetInputLayout().Get());
    const float factor[4] = {0,0,0,0};
    DeferredContext_->OMSetBlendState(pipeline->GetBlendState()->Get(), factor, D3D11_APPEND_ALIGNED_ELEMENT);
    DeferredContext_->OMSetDepthStencilState(pipeline->GetDepthStencilState().Get(), 0);
    DeferredContext_->RSSetState(pipeline->GetRasterizerState().Get());
    DeferredContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
