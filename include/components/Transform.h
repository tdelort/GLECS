#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include <Component.h>

namespace nbop::glecs
{
    class Transform : public Component
    {
    public:
        static constexpr auto Type = "Transform";

        Transform(std::weak_ptr<Entity> owner);
        ~Transform() override;

        // Transform between spaces
        glm::mat4 GetLocalToWorldMatrix() const;
        glm::mat4 GetWorldToLocalMatrix() const;

        // Getters
        glm::vec3 GetPosition() const;

        glm::vec3 GetRotation() const;

        glm::vec3 GetScale() const;

        std::weak_ptr<Transform> GetParent() const;

        // Setters
        void SetPosition(glm::vec3 position);

        void SetRotationEuler(glm::vec3 rotation);

        void SetScale(glm::vec3 scale);

        void SetParent(std::weak_ptr<Transform> parent);

        // TODO : add helper functions to move, rotate, scale, etc.
        // for example : Translate / RotateAround

    private:
        glm::mat4 m_T;
        glm::mat4 m_R;
        glm::mat4 m_S;

        std::weak_ptr<Transform> m_parent;
        std::vector<std::weak_ptr<Transform>> m_children;

        glm::mat4 localToWorldMatrix;
        //bool localToWorldMatrixDirty;
    };
}
