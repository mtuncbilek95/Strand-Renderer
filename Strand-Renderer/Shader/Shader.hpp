#pragma once

#include <GraphicsDevice/DeviceObject.hpp>

#include <d3dcompiler.h>
#include <d3d11.h>
#include <wrl.h>
#include <string>

using namespace Microsoft::WRL;

enum class ShaderType
{
    Vertex,
    Pixel,
    Domain,
    Hull,
    Geometry,
    Compute
};

struct ShaderDesc{
    ShaderType Type_;
    std::string Source_;
    std::string EntryPoint_;
    std::string Target_;
};

class GraphicsDevice;

class Shader : public DeviceObject
{
public:
    Shader(GraphicsDevice* graphicsDevice, ShaderDesc& desc);
    Shader(const Shader& instance) = delete;
    Shader& operator=(const Shader& instance) = delete;
    ~Shader() = default;

    ComPtr<ID3D11VertexShader>& GetVertexShader() { return VertexShader_; }
    ComPtr<ID3D11PixelShader>& GetPixelShader() { return PixelShader_; }
    ComPtr<ID3D11DomainShader>& GetDomainShader() { return DomainShader_; }
    ComPtr<ID3D11HullShader>& GetHullShader() { return HullShader_; }
    ComPtr<ID3D11GeometryShader>& GetGeometryShader() { return GeometryShader_; }
    ComPtr<ID3D11ComputeShader>& GetComputeShader() { return ComputeShader_; }

    ComPtr<ID3DBlob>& GetShaderBlob() { return Blob_; }

    ShaderType GetShaderType() { return Desc_.Type_; }

    DeviceObjectType GetDeviceObjectType() override { return DeviceObjectType::Shader; };

private:
    ComPtr<ID3D11VertexShader> VertexShader_;
    ComPtr<ID3D11DomainShader> DomainShader_;
    ComPtr<ID3D11HullShader> HullShader_;
    ComPtr<ID3D11GeometryShader> GeometryShader_;
    ComPtr<ID3D11ComputeShader> ComputeShader_;
    ComPtr<ID3D11PixelShader> PixelShader_;

    ComPtr<ID3DBlob> Blob_;

    ShaderDesc Desc_;
};
