#include <vector>

#include <glad/glad.h>

#include <Span.h>
#include <assets/Mesh.h>

namespace nbop::glecs
{
    Mesh::Mesh() { }
    
    Mesh::~Mesh() { }

    void Mesh::setVertexData(const std::vector<float> vertexPositions, const std::vector<float> vertexColors, const std::vector<unsigned int> faceIndices)
    {
        // copying the data
        m_vertexPositions = vertexPositions;
        m_vertexColors = vertexColors;
        m_faceIndices = faceIndices;
    }


    void Mesh::setupForRendering(GLuint program)
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        // Vertex Position (VBO)
        glGenBuffers(1, &m_vertexPositionVbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionVbo);
        glBufferData(GL_ARRAY_BUFFER, m_vertexPositions.size() * sizeof(GLfloat), m_vertexPositions.data(), GL_STATIC_DRAW);

        GLint positionLocation = glGetAttribLocation(program, "v_position");
        glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(positionLocation);

        // Vertex Color (VBO)
        glGenBuffers(1, &m_vertexColorsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexColorsVbo);
        glBufferData(GL_ARRAY_BUFFER, m_vertexColors.size() * sizeof(GLfloat), m_vertexColors.data(), GL_STATIC_DRAW);

        GLint colorLocation = glGetAttribLocation(program, "v_color");
        glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(colorLocation);

        // Faces (EBO)
        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_faceIndices.size() * sizeof(GLuint), m_faceIndices.data(), GL_STATIC_DRAW);
    }

    size_t Mesh::faceBufferSize() const
    {
        return m_faceIndices.size();
    }
    
    void Mesh::bind()
    {
        glBindVertexArray(m_vao);
    }
}