![Strand Renderer.png](External%2FResources%2FStrand%20Renderer.png)

# Strand Renderer

This is a simple renderer for PBR shading. It is based on my custom game engine called Strand 
Engine. It is written in C++ and DirectX 11. It is a work in progress and is not yet complete. Strand Engine
is also currently supports DirectX 11, but I am planning to add support for DirectX 12 and Vulkan in the 
future and remove DirectX 11 support. This rendering engine is a mini version of Strand Engine. It supports
only 1 Framebuffer and 1 Render Pass. It also does not support instancing.

## Features To Be Supported

- PBR Shading
- Model Loading
- Customization on the material properties
- Customization on the light properties
- Path Tracing in Compute Shader
- Intel Sponza Scene
- Basic Imgui Interface to control the properties