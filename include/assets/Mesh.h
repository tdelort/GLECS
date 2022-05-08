#pragma once

#include <vector>

#include <glad/glad.h>

namespace nbop::glecs
{
    class Mesh
    {
    public:
        Mesh();
        ~Mesh();
        
        void setVertexData(const std::vector<float> vertexPositions, const std::vector<float> vertexColors, const std::vector<unsigned int> faceIndices);

        void setupForRendering(GLuint program);
        
        size_t faceBufferSize() const;

        void bind();

        private:
        std::vector<GLfloat> m_vertexPositions;
        std::vector<GLfloat> m_vertexColors;
        std::vector<GLuint> m_faceIndices;

        // GL
        GLuint m_vao;
        GLuint m_vertexPositionVbo, m_vertexColorsVbo;
        GLuint m_ebo;
    };
} // namespace nbop::glecs