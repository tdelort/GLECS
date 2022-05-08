#pragma once

#include <vector>
#include <memory>
#include <type_traits>
#include <functional>

#include <Component.h>

namespace nbop::glecs
{
    class Entity : public std::enable_shared_from_this<Entity>
    {
    public:
        Entity(const std::string& name);
        ~Entity();

        // Preventing copy (and as a side effect, move)
        Entity(const Entity& other) = delete;
        Entity& operator=(const Entity& other) = delete;

        std::weak_ptr<Component> getComponentIf(std::function<bool(std::shared_ptr<Component>)> predicate) const;
        std::vector<std::weak_ptr<Component>> getAllComponentsIf(std::function<bool(std::shared_ptr<Component>)> predicate) const;

        template<typename T>
        std::weak_ptr<T> addComponent();

        template<typename T>
        std::weak_ptr<T> getComponent() const;

        template<typename T>
        std::vector<std::weak_ptr<T>> getAllComponents() const;

    private:
        // Shared Pointers here and not weak pointers because Entities have
        // authority over the Components they own. Not a unique_ptr since we need
        // to be able to give weak_ptrs to the users.
        std::vector<std::shared_ptr<Component>> m_components;

        const std::string m_name;
    };

    template<typename T>
    std::weak_ptr<T> Entity::addComponent()
    {
        std::shared_ptr<T> new_component = std::make_shared<T>(weak_from_this());
        m_components.push_back(new_component);
        return new_component;
    }

    template<typename T>
    std::weak_ptr<T> Entity::getComponent() const
    {
        for (auto it = m_components.begin(); it != m_components.end(); ++it)
        {
            std::shared_ptr<T> component = std::dynamic_pointer_cast<T>(*it);
            if (component)
                return component;
        }

        return std::weak_ptr<T>();
        // Je garde ca de coté
        //if(std::is_base_of_v<T, decltype(*m_components[i])>)
        //{
        //    ptr = std::static_pointer_cast<T>(m_components[i]);
        //}
    }

    template<typename T>
    std::vector<std::weak_ptr<T>> Entity::getAllComponents() const
    {
        std::vector<std::weak_ptr<T>> result;
        std::copy_if(m_components.begin(), m_components.end(), std::back_inserter(result), 
            [](std::shared_ptr<Component> component)
            {
                return std::dynamic_pointer_cast<T>(component);
            }
        );

        return result;
    }
}
