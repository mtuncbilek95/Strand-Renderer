#pragma once

#include <d3dcompiler.h>
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>

#include <GraphicsDevice/DeviceObject.hpp>

#include <vector>

using namespace DirectX;
using namespace Microsoft::WRL;

class GraphicsDevice;
class Pipeline;
class SamplerState;
class BufferObject;
class TextureViewObject;
class ShaderResourceView;

class CommandList : public DeviceObject
{
public:
    CommandList(GraphicsDevice* device);
    CommandList(const CommandList&) = delete;
    CommandList& operator=(const CommandList&) = delete;
    ~CommandList() = default;

    void BindRTV();
    void BindPipeline(Pipeline* pipeline);
    void ExecuteCommandList();
    void BindViewport();
    void BindVertexBuffer(BufferObject* vertexBuffer);
    void BindIndexBuffer(BufferObject* indexBuffer);

    void DrawIndexed(uint32_t indexCount, uint32_t startIndexLocation, int32_t baseVertexLocation);
    void ClearBuffer(XMFLOAT4 color);

    DeviceObjectType GetDeviceObjectType() override { return DeviceObjectType::CommandList; }
private:
    ComPtr<ID3D11DeviceContext> DeferredContext_;
    ComPtr<ID3D11CommandList> CommandList_;

    Pipeline* PipelineRef_;
};
