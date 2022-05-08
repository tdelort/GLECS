#include <fstream>
#include <string>
#include <sstream>

#include <FileUtility.h>

namespace nbop::glecs
{
    std::string FileUtility::readToString(const std::string& path)
    {
        std::ifstream file(path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
} // namespace nbop::glecs
