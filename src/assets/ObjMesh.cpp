#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <glad/glad.h>

#include <Debug.h>
#include <assets/Mesh.h>
#include <assets/ObjMesh.h>

namespace nbop::glecs
{
    ObjMesh::ObjMesh(const std::string& filepath)
        : Mesh()
    {
        std::ifstream file;
        file.open(filepath);

        Debug::logAssert(file.is_open(), "Failed to open file: " + filepath);

        std::vector<GLfloat> vPositions;
        std::vector<GLfloat> vColors;
        std::vector<GLuint> faces;
        std::string line;

        int i = 0;
        while (std::getline(file, line))
        {
            i++;
            std::stringstream ss(line);
            if (line.length() == 0)
            {
                Debug::log("ObjMesh::ObjMesh : Empty line");
                continue;
            }

            if (line.substr(0, 2) == "v ")
            {
                std::istringstream iss(line.substr(2));
                float x, y, z;
                iss >> x >> y >> z;
                vPositions.push_back(x);
                vPositions.push_back(y);
                vPositions.push_back(z);

                // For now, we don't care about colors
                // TODO : Add colors
                vColors.push_back(1.0f);
                vColors.push_back(1.0f);
                vColors.push_back(1.0f);
            }
            else if (line.substr(0, 2) == "f ")
            {
                std::istringstream iss(line.substr(2));
                unsigned int v;
                while (iss >> v)
                {
                    //Debug::log("ObjMesh::ObjMesh : Face at line " + std::to_string(i) + " : " + std::to_string(v));
                    faces.push_back(v - 1);
                }
            }
            else
            {
                // ignore other kind of data for now
                Debug::log("ObjMesh::ObjMesh : Ignoring line " + std::to_string(i));
            }
        }
        setVertexData(vPositions, vColors, faces);
        file.close();
    }

    ObjMesh::~ObjMesh()
    { }
} // namespace nbop::glecs

