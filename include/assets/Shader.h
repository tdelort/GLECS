#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <glad/glad.h>

namespace nbop::glecs
{
    struct Shader
    {
        struct Uniform
        {
            enum class Type : uint8_t
            {
                Float, Int,
                Vec2, Vec3, Vec4,
                Mat2, Mat3, Mat4
            };

            std::string name;
            Type type;
        };

        Shader(const std::string& path, const std::vector<Uniform>& uniforms, GLenum type);

        std::string filePath;
        std::vector<Uniform> uniforms;
        GLuint id;

        static std::string glenumShaderTypeToString(GLenum type);
        std::string shaderVersionString = "#version 150\n";
    };
} // namespace nbop::glecs
