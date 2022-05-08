#include <string>
#include <string_view>
#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <assets/Shader.h>
#include <FileUtility.h>

#define _DEBUG_SHADER

namespace nbop::glecs
{
    Shader::Shader(const std::string& path, const std::vector<Uniform>& uniforms, GLenum type)
        : filePath(path), uniforms(uniforms)
    {
        std::string shaderSource = FileUtility::readToString(filePath);

        GLchar const* files[] = { shaderVersionString.c_str(), shaderSource.c_str() };
        GLint lengths[] =       { (GLint)shaderVersionString.size(), (GLint)shaderSource.size() };

        id = glCreateShader(type);
        glShaderSource(id, 2, files, lengths);
        glCompileShader(id);

        #ifdef _DEBUG_SHADER
            GLint status;
            glGetShaderiv(id, GL_COMPILE_STATUS, &status);
            std::cout << glenumShaderTypeToString(type) << " compile status : " << status << " (1 means success)" << std::endl;
            if(status == GL_FALSE)
            {
                GLint infoLogLength;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
                GLchar *strInfoLog = new GLchar[infoLogLength + 1];
                glGetShaderInfoLog(id, infoLogLength, NULL, strInfoLog);
                std::cout << "Compile failure in vertex shader : " << std::endl;
                std::cout << strInfoLog << std::endl;
                delete[] strInfoLog;
            }
        #endif
    }

    std::string Shader::glenumShaderTypeToString(GLenum type)
    {
        switch (type)
        {
            case GL_VERTEX_SHADER:
                return "Vertex Shader";
            case GL_FRAGMENT_SHADER:
                return "Fragment Shader";
            case GL_GEOMETRY_SHADER:
                return "Geometry Shader";
            default:
                return "Not supported Shader type";
        }
    }
} // namespace nbop::glecs
