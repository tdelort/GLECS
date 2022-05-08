#pragma once

#include <assets/Mesh.h>

namespace nbop::glecs
{
    class ObjMesh : public Mesh
    {
    public:
        ObjMesh(const std::string& filepath);
        ~ObjMesh();
    };
} // namespace nbop::glecs
