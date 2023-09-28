#pragma once

#include <Containers/Singleton.hpp>
#include <Containers/UniqueHeap.hpp>

#include <GraphicsDevice/GraphicsDevice.hpp>
#include <Window/Window.hpp>
#include <iostream>

class GraphicsManager : public Singleton<GraphicsManager>
{
public:
    GraphicsManager()
    {
        if(Device_ == nullptr)
            Device_ = MakeUniqueHeap<GraphicsDevice>();
    }

    GraphicsDevice& GetGraphicsDevice() { return *Device_; }

    GraphicsManager(const GraphicsManager&) = delete;
    GraphicsManager& operator=(const GraphicsManager&) = delete;
    ~GraphicsManager() = default;

private:
    UniqueHeap<GraphicsDevice> Device_;
};