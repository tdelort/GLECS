#include <string_view>
#include <memory>

#include <Entity.h>
#include <Component.h>

namespace nbop::glecs
{
    Entity::Entity() { }
    Entity::~Entity() { }

    std::weak_ptr<Component> Entity::getComponent(std::string_view type_str) const
    {
        // unordered_map::find : avg O(1), worst O(n)
        auto it = m_components.find(std::string{type_str}); 
        if (it == m_components.end())
        {
            return {}; // returns empty weak_ptr
        }

        return it->second;
    }

}