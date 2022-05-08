#include <Component.h>

namespace nbop::glecs
{
    Component::Component(std::weak_ptr<Entity> owner) : m_owner(owner) { }
    Component::~Component() { }

    std::weak_ptr<Entity> Component::getOwner() const { return m_owner; }

    void Component::onEntityCreated() { }
    void Component::onNewFrame() { }
    void Component::onEntityDestroyed() { }
}