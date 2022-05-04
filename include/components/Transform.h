#pragma once

#include <glm/glm.hpp>

#include <Component.h>

namespace nbop::glecs
{
    class Transform : public Component
    {
    public:
        Transform(const Entity& owner);

        // Transform between spaces
        glm::mat4 GetLocalToWorldMatrix() const;
        glm::mat4 GetWorldToLocalMatrix() const;

        // Getters
        glm::vec3 GetPosition() const;
        glm::vec3 GetLocalPosition() const;

        glm::vec3 GetRotation() const;
        glm::vec3 GetLocalRotation() const;

        glm::vec3 GetScale() const;
        glm::vec3 GetLocalScale() const;

        std::optional<const Transform&> GetParent() const;

        // Setters
        void SetPosition(glm::vec3 position);
        void SetLocalPosition(glm::vec3 position);

        void SetRotationEuler(glm::vec3 rotation);
        void SetLocalRotationEuler(glm::vec3 rotation);

        void SetScale(glm::vec3 scale);
        void SetLocalScale(glm::vec3 scale);

        void SetParent(const Transform& parent);

        // TODO : add helper functions to move, rotate, scale, etc.
        // for example : Translate / RotateAround

    private:
        glm::mat4 m_T;
        glm::mat4 m_R;
        glm::mat4 m_S;

        std::optional<const Transform&> m_parent;
        std::vector<std::weak_ptr<Transform>> m_children;

        glm::mat4 localToWorldMatrix;
        //bool localToWorldMatrixDirty;
    };
}
