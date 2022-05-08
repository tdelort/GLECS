#pragma once

#include <string>

namespace nbop::glecs
{
    class FileUtility
    {
    public:
        static std::string readToString(const std::string& path);
    };   
} // namespace nbop::glecs
