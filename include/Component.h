#pragma once

class Entity;

namespace nbop::glecs
{
    class Component
    {
        //static constexpr auto Type = "ComponentTypeName";
    public:
        Component(const Entity& owner);
        
        const Entity& GetOwner() const;

        // destructor set as pure virtual to prevent instances of 
        // Component from being created, making Component an abstract class
        // we can still give this constructor a body in the .cpp
        virtual ~Component() = 0;
    private:
        const Entity& m_owner;
    };
}

