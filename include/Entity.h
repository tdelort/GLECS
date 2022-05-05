#pragma once

#include <unordered_map>
#include <string>
#include <string_view>
#include <memory>

#include <Component.h>

namespace nbop::glecs
{
    class Entity : public std::enable_shared_from_this<Entity>
    {
    public:
        Entity();
        ~Entity();

        // Preventing copy (and as a side effect, move)
        Entity(const Entity& other) = delete;
        Entity& operator=(const Entity& other) = delete;

        template<typename T>
        std::weak_ptr<T> addComponent();

        template<typename T>
        std::weak_ptr<T> getComponent() const;

    private:
        // Shared Pointers here and not weak pointers because Entities have
        // authority over the Components they own. Not a unique_ptr since we need
        // to be able to give weak_ptrs to the users.
        std::unordered_map<std::string, std::shared_ptr<Component>> m_components;  

        std::weak_ptr<Component> getComponent(std::string_view type_str) const;
    };

    template<typename T>
    std::weak_ptr<T> Entity::addComponent()
    {
        std::shared_ptr<T> new_component = std::make_shared<T>(weak_from_this());
        m_components.emplace(T::Type, new_component);
        return new_component;
    }

    template<typename T>
    std::weak_ptr<T> Entity::getComponent() const
    {
        std::weak_ptr<Component> component = getComponent(T::Type);
        return std::dynamic_pointer_cast<T>(component);
    }

}
