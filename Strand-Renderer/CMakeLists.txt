cmake_minimum_required(VERSION 3.25)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(ENGINE_DEBUG)
endif()

add_executable(${PROJECT_NAME} "main.cpp"
        Containers/Singleton.hpp
        Containers/UniqueHeap.hpp
        GraphicsDevice/GraphicsDevice.cpp
        GraphicsDevice/GraphicsDevice.hpp
        Window/Window.hpp
        Window/Window.cpp
        GraphicsDevice/DeviceObject.hpp
        BufferObject/BufferObject.cpp
        BufferObject/BufferObject.hpp
        TextureView/TextureView.cpp
        TextureView/TextureView.hpp
        Sampler/SamplerState.cpp
        Sampler/SamplerState.hpp
        Pipeline/Pipeline.cpp
        Pipeline/Pipeline.hpp
        Shader/Shader.cpp
        Shader/Shader.hpp
        FileReader/FileReader.cpp
        CommandList/CommandList.cpp
        CommandList/CommandList.hpp
        Application/Application.cpp
        Application/Application.hpp
        GameTimer/GameTimer.hpp
        GameTimer/GameTimer.cpp
        World/GameObject/GameObject.cpp
        World/GameObject/GameObject.hpp
        World/GraphicsManager/GraphicsManager.cpp
        World/GraphicsManager/GraphicsManager.hpp

)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Strand-Renderer")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/External/GLFW/Include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/External/STBI")

target_link_libraries(${PROJECT_NAME} "d3d11.lib")
target_link_libraries(${PROJECT_NAME} "dxgi.lib")
target_link_libraries(${PROJECT_NAME} "d3dcompiler.lib")
target_link_libraries(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/External/GLFW/Lib/glfw3.lib")
target_link_libraries(${PROJECT_NAME} STBI)

add_compile_definitions("RENDER_ROOT=${CMAKE_SOURCE_DIR}")