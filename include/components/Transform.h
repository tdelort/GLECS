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
        Transform(const Transform& other) = delete;
        Transform& operator=(const Transform& other) = delete;

        // Transform between spaces
        glm::mat4 getLocalToWorldMatrix() const;
        glm::mat4 getWorldToLocalMatrix() const;

        // Getters
        glm::vec3 getPosition() const;

        glm::vec3 getRotation() const;

        glm::vec3 getScale() const;

        std::weak_ptr<Transform> getParent() const;

        glm::mat4 getModelMatrix() const;

        // Setters
        void setPosition(glm::vec3 position);

        void setRotationEuler(glm::vec3 rotation);

        void setScale(glm::vec3 scale);

        void setParent(std::weak_ptr<Transform> parent);

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
