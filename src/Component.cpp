#include <Component.h>

namespace nbop::glecs
{
    Component::Component(const Entity& owner) : m_owner(owner) { }

    const Entity& Component::GetOwner() const { return m_owner; }

    Component::~Component() { }
}