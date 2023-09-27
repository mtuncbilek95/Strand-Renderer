#include "Shader.hpp"

#include <GraphicsDevice/GraphicsDevice.hpp>
#include <FileReader/FileReader.hpp>

Shader::Shader(GraphicsDevice* graphicsDevice, ShaderDesc& desc)
{
    GraphicsDevice_ = graphicsDevice;
    Desc_ = desc;

    ComPtr<ID3DBlob> errorBlob;

    std::string shaderData = FileReader::GetShaderData(desc.Source_);

    D3DCompile(shaderData.c_str(), shaderData.length(), nullptr, nullptr, nullptr,
               desc.EntryPoint_.c_str(), desc.Target_.c_str(), D3DCOMPILE_ENABLE_STRICTNESS, 0, Blob_.GetAddressOf(), &errorBlob);

    if(errorBlob.Get() != nullptr && errorBlob.Get()->GetBufferPointer() != nullptr) {
        std::exception((char*) errorBlob->GetBufferPointer());
    }

    HRESULT hr;

    switch(desc.Type_) {
        case ShaderType::Vertex:
            hr = GraphicsDevice_->GetDevice()->CreateVertexShader(Blob_->GetBufferPointer(), Blob_->GetBufferSize(), nullptr, VertexShader_.GetAddressOf());
            break;
        case ShaderType::Pixel:
            hr = GraphicsDevice_->GetDevice()->CreatePixelShader(Blob_->GetBufferPointer(), Blob_->GetBufferSize(), nullptr, PixelShader_.GetAddressOf());
            break;
        case ShaderType::Domain:
            hr = GraphicsDevice_->GetDevice()->CreateDomainShader(Blob_->GetBufferPointer(), Blob_->GetBufferSize(), nullptr, DomainShader_.GetAddressOf());
            break;
        case ShaderType::Hull:
            hr = GraphicsDevice_->GetDevice()->CreateHullShader(Blob_->GetBufferPointer(), Blob_->GetBufferSize(), nullptr, HullShader_.GetAddressOf());
            break;
        case ShaderType::Geometry:
            hr = GraphicsDevice_->GetDevice()->CreateGeometryShader(Blob_->GetBufferPointer(), Blob_->GetBufferSize(), nullptr, GeometryShader_.GetAddressOf());
            break;
        case ShaderType::Compute:
            hr = GraphicsDevice_->GetDevice()->CreateComputeShader(Blob_->GetBufferPointer(), Blob_->GetBufferSize(), nullptr, ComputeShader_.GetAddressOf());
            break;
    }

    if(FAILED(hr)) {
        std::exception("Failed to create shader");
    }
}
