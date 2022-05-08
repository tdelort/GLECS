#include <string_view>
#include <memory>
#include <algorithm>
#include <iterator>

#include <Entity.h>
#include <Component.h>

namespace nbop::glecs
{
    Entity::Entity(const std::string& name) : m_name(name) { }
    Entity::~Entity() { }

    std::weak_ptr<Component> Entity::getComponentIf(std::function<bool(std::shared_ptr<Component>)> predicate) const
    {
        return *(std::find_if(m_components.begin(), m_components.end(), predicate));
    }

    std::vector<std::weak_ptr<Component>> Entity::getAllComponentsIf(std::function<bool(std::shared_ptr<Component>)> predicate) const
    {
        std::vector<std::weak_ptr<Component>> result;
        std::copy_if(m_components.begin(), m_components.end(), std::back_inserter(result), predicate);
        return result;
    }
}