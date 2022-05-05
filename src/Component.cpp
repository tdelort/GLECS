#include <Component.h>

namespace nbop::glecs
{
    Component::Component(std::weak_ptr<Entity> owner) : m_owner(owner) { }
    Component::~Component() { }

    std::weak_ptr<Entity> Component::GetOwner() const { return m_owner; }
}