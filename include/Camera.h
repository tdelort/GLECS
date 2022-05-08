#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

namespace nbop::glecs
{
    // Camera singleton
    class Camera
    {
    private:
        glm::mat4 proj;
        glm::mat4 view;
        glm::vec3 clearColor;

        Camera() = default;
    public:
        Camera(const Camera&) = delete;
        Camera& operator=(const Camera&) = delete;
        Camera(const Camera&&) = delete;
        Camera& operator=(const Camera&&) = delete;

        static Camera& instance()
        {
            static Camera instance;
            return instance;
        }

        static void setProjectionMatrix(const glm::mat4& proj)
        {
            instance().proj = proj;
        }

        static void setViewMatrix(const glm::mat4& view)
        {
            instance().view = view;
        }

        static void setClearColor(const glm::vec3& clearColor)
        {
            instance().clearColor = clearColor;
        }

        static const glm::mat4& getProjectionMatrix()
        {
            return instance().proj;
        }

        static const glm::mat4& getViewMatrix()
        {
            return instance().view;
        }

        static const glm::vec3& getClearColor()
        {
            return instance().clearColor;
        }
    };
} // namespace nbop::glecs
