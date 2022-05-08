#pragma once

#include <optional>
#include <unordered_map>
#include <memory>

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <assets/Shader.h>

namespace nbop::glecs
{
    class Material
    {
        template<typename T>
        struct Uniform
        {
            GLint location;
            T value;
        };

    public:
        Material(std::vector<std::weak_ptr<Shader>> shaders);
        ~Material();

        void setFloat(const std::string& name, float value);
        void setInt(const std::string& name, int value);

        void setVec2(const std::string& name, const glm::vec2& value);
        void setVec3(const std::string& name, const glm::vec3& value);
        void setVec4(const std::string& name, const glm::vec4& value);

        void setMat2(const std::string& name, const glm::mat2& value);
        void setMat3(const std::string& name, const glm::mat3& value);
        void setMat4(const std::string& name, const glm::mat4& value);
        
        void use();

        GLuint getProgram() const;

    private:

        GLuint m_program;
        GLuint m_vertexShader, m_fragmentShader, m_geometryShader;

        // Not really sexy but couldn't find a better way right now
        // Might need to change the unordered_map because it will be iterated over
        // in the render loop
        std::unordered_map<std::string, Uniform<float>> m_floatUniforms;
        std::unordered_map<std::string, Uniform<int>> m_intUniforms;
        std::unordered_map<std::string, Uniform<glm::vec2>> m_vec2Uniforms;
        std::unordered_map<std::string, Uniform<glm::vec3>> m_vec3Uniforms;
        std::unordered_map<std::string, Uniform<glm::vec4>> m_vec4Uniforms;
        std::unordered_map<std::string, Uniform<glm::mat2>> m_mat2Uniforms;
        std::unordered_map<std::string, Uniform<glm::mat3>> m_mat3Uniforms;
        std::unordered_map<std::string, Uniform<glm::mat4>> m_mat4Uniforms;

        template<typename T>
        void initUniform(Shader::Uniform uniform, std::unordered_map<std::string, Uniform<T>>& uniforms);

        template<typename T>
        void setUniform(const std::string& name, const T& value, std::unordered_map<std::string, Uniform<T>>& uniforms);

        void initShader(GLenum type, Shader shader);
    };


    template<typename T>
    void Material::initUniform(Shader::Uniform uniform, std::unordered_map<std::string, Uniform<T>>& uniforms)
    {
        uniforms[uniform.name].location = glGetUniformLocation(m_program, uniform.name.c_str());
    }

    template<typename T>
    void Material::setUniform(const std::string& name, const T& value, std::unordered_map<std::string, Uniform<T>>& uniforms)
    {
        //std::unordered_map<std::string, Uniform<T>>::iterator it = uniforms.find(name);
        auto it = uniforms.find(name);
        if (it == uniforms.end())
        {
            Debug::error("Material::setUniform : Uniform " + name + " is not found");
            return;
        }
        it->second.value = value;
    }

} // namespace nbop::glecs
