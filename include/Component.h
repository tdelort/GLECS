#pragma once

#include <memory>

namespace nbop::glecs
{
    class Entity;

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
        
        std::weak_ptr<Entity> getOwner() const;

        //virtual void setup(std::string jsonString) = 0; // from json

        virtual void onEntityCreated();
        virtual void onNewFrame();
        virtual void onEntityDestroyed();

    private:
        std::weak_ptr<Entity> m_owner;
    };
}

