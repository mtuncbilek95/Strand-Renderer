#pragma once

class GameObject
{
public:
    GameObject();
    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;
    ~GameObject() = default;
};
