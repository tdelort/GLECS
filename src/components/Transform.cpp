#include <Component.h>
#include <components/Transform.h>

namespace nbop::glecs
{
    Transform::Transform(const Entity& owner) 
        : Component(owner), m_T(1.0f), m_R(1.0f), m_S(1.0f)
    {
        m_parent = std::nullopt;
    }

    glm::mat4 Transform::GetLocalToWorldMatrix() const
    {
        glm::mat4 trans = m_T * m_R * m_S;
        return m_parent ? trans * m_parent.GetLocalToWorldMatrix() : trans;
    }

    // TODO : continue here

    glm::vec3 Transform::GetPosition() const
    {

    }

    glm::vec3 Transform::GetLocalPosition() const
    {
        // Extracts the 4th column of the transform matrix
        return glm::vec3(m_T[3]);
    }

}