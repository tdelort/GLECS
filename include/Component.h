#pragma once

#include <memory>

class Entity;

namespace nbop::glecs
{
    class Component
    {
        //static constexpr auto Type = "ComponentTypeName";
    public:
        Component(std::weak_ptr<Entity> owner);

        // destructor set as pure virtual to prevent instances of 
        // Component from being created, making Component an abstract class
        // we can still give this constructor a body in the .cpp
        virtual ~Component() = 0;

        // Preventing copy (and as a side effect, move)
        Component(const Component& other) = delete;
        Component& operator=(const Component& other) = delete;
        
        std::weak_ptr<Entity> GetOwner() const;

        virtual void OnEntityCreated();
        virtual void OnNewFrame();
        virtual void OnEntityDestroyed();

    private:
        std::weak_ptr<Entity> m_owner;
    };
}

