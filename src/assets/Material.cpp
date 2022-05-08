#include <memory>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <assets/Material.h>
#include <assets/Shader.h>
#include <Debug.h>

namespace nbop::glecs
{
    Material::Material(std::vector<std::weak_ptr<Shader>> shaders)
    {
        // Creating shader program and linking it
        m_program = glCreateProgram();

        for (std::weak_ptr<Shader> shader : shaders)
            glAttachShader(m_program, shader.lock()->id);

        glLinkProgram(m_program);

        // Fill the uniforms map
        for (std::weak_ptr<Shader> shader_weak : shaders)
        {
            std::shared_ptr<Shader> shader = shader_weak.lock();
            for (Shader::Uniform uniform : shader->uniforms)
            {
                switch (uniform.type)
                {
                case Shader::Uniform::Type::Float: initUniform<float>(uniform, m_floatUniforms);    break;
                case Shader::Uniform::Type::Int:   initUniform<int>(uniform, m_intUniforms);        break;
                case Shader::Uniform::Type::Vec2:  initUniform<glm::vec2>(uniform, m_vec2Uniforms); break;
                case Shader::Uniform::Type::Vec3:  initUniform<glm::vec3>(uniform, m_vec3Uniforms); break;
                case Shader::Uniform::Type::Vec4:  initUniform<glm::vec4>(uniform, m_vec4Uniforms); break;
                case Shader::Uniform::Type::Mat2:  initUniform<glm::mat2>(uniform, m_mat2Uniforms); break;
                case Shader::Uniform::Type::Mat3:  initUniform<glm::mat3>(uniform, m_mat3Uniforms); break;
                case Shader::Uniform::Type::Mat4:  initUniform<glm::mat4>(uniform, m_mat4Uniforms); break;
                default:
                    Debug::warn("Material::Material : Unknown uniform type");
                    break;
                }
            }
        }

        initUniform<glm::mat4>({"u_model", Shader::Uniform::Type::Mat4 }, m_mat4Uniforms);
        initUniform<glm::mat4>({"u_view", Shader::Uniform::Type::Mat4 }, m_mat4Uniforms);
        initUniform<glm::mat4>({"u_projection", Shader::Uniform::Type::Mat4 }, m_mat4Uniforms);
        initUniform<float>({"u_time", Shader::Uniform::Type::Float }, m_floatUniforms);
        initUniform<float>({"u_deltaTime", Shader::Uniform::Type::Float }, m_floatUniforms);
    }


    Material::~Material()
    { }

    // Setters
    void Material::setFloat(const std::string& name, float value) { setUniform(name, value, m_floatUniforms); }
    void Material::setInt(const std::string& name, int value) { setUniform(name, value, m_intUniforms); }

    void Material::setVec2(const std::string& name, const glm::vec2& value) { setUniform(name, value, m_vec2Uniforms); }
    void Material::setVec3(const std::string& name, const glm::vec3& value) { setUniform(name, value, m_vec3Uniforms); }
    void Material::setVec4(const std::string& name, const glm::vec4& value) { setUniform(name, value, m_vec4Uniforms); }

    void Material::setMat2(const std::string& name, const glm::mat2& value) { setUniform(name, value, m_mat2Uniforms); }
    void Material::setMat3(const std::string& name, const glm::mat3& value) { setUniform(name, value, m_mat3Uniforms); }
    void Material::setMat4(const std::string& name, const glm::mat4& value) { setUniform(name, value, m_mat4Uniforms); }

    // glUseProgram and sending uniforms value to the program
    void Material::use()
    {
        glUseProgram(m_program);
        
        // Set uniforms
        for (auto& [name, uniform] : m_floatUniforms)
            glUniform1f(uniform.location, uniform.value);

        for (auto& [name, uniform] : m_intUniforms)
            glUniform1i(uniform.location, uniform.value);

        for (auto& [name, uniform] : m_vec2Uniforms)
            glUniform2fv(uniform.location, 1, glm::value_ptr(uniform.value));
        
        for (auto& [name, uniform] : m_vec3Uniforms)
            glUniform3fv(uniform.location, 1, glm::value_ptr(uniform.value));
        
        for (auto& [name, uniform] : m_vec4Uniforms)
            glUniform4fv(uniform.location, 1, glm::value_ptr(uniform.value));
        
        for (auto& [name, uniform] : m_mat2Uniforms)
            glUniformMatrix2fv(uniform.location, 1, GL_FALSE, glm::value_ptr(uniform.value));
        
        for (auto& [name, uniform] : m_mat3Uniforms)
            glUniformMatrix3fv(uniform.location, 1, GL_FALSE, glm::value_ptr(uniform.value));
        
        for (auto& [name, uniform] : m_mat4Uniforms)
            glUniformMatrix4fv(uniform.location, 1, GL_FALSE, glm::value_ptr(uniform.value));
    }

    GLuint Material::getProgram() const
    {
        return m_program;
    }
} // namespace nbop::glecs
