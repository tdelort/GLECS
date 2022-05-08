#include <vector>
#include <memory>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>

#include <Component.h>
#include <components/Transform.h>

namespace nbop::glecs
{
    Transform::Transform(std::weak_ptr<Entity> owner) 
        : Component(owner), m_T(1.0f), m_R(1.0f), m_S(1.0f)
    { }

    Transform::~Transform() { }

    // Transform between spaces
    glm::mat4 Transform::getLocalToWorldMatrix() const
    {
        // TODO : a revoir
        glm::mat4 trans = getModelMatrix();
        if (m_parent.expired())
            return trans;

        glm::mat4 parentLocalToWorldMatrix = m_parent.lock()->getLocalToWorldMatrix();
        return trans * parentLocalToWorldMatrix;
    }

    glm::mat4 Transform::getWorldToLocalMatrix() const
    {
        return glm::inverse(getLocalToWorldMatrix());
    }

    // Getters
    glm::vec3 Transform::getPosition() const
    {
        return glm::vec3(m_T[3]);
    }

    glm::vec3 Transform::getRotation() const
    {
        glm::mat3 rot = glm::mat3(m_R);
        return glm::degrees(glm::eulerAngles(glm::quat_cast(rot)));
    }

    glm::vec3 Transform::getScale() const
    {
        glm::vec3 scale;
        for(int i = 0; i < 3; i++)
            scale[i] = glm::length(glm::vec3(m_S[i]));
        return scale;
    }

    std::weak_ptr<Transform> Transform::getParent() const
    {
        return m_parent;
    }

    glm::mat4 Transform::getModelMatrix() const
    {
        return m_S * m_R * m_T;
    }

    // Setters
    void Transform::setPosition(glm::vec3 position)
    {
        m_T = glm::translate(glm::mat4(1.0f), position);
    }

    void Transform::setRotationEuler(glm::vec3 rotation)
    {
        glm::mat4 rX = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rY = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rZ = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        m_R = rZ * rY * rX;
    }

    void Transform::setScale(glm::vec3 scale)
    {
        m_S = glm::scale(glm::mat4(1.0f), scale);
    }

    void Transform::setParent(std::weak_ptr<Transform> parent)
    {
        m_parent = parent;
    }
}