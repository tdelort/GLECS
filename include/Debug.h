#pragma once

#include <iostream>

namespace nbop::glecs
{
    // A class and not just a namespace if i ever need ome memory 
    // like storing errno or something.
    class Debug
    {
    public:
        template<typename T>
        static void logAssert(T&& condition, const std::string& message)
        {
            if (!condition)
            {
                std::cerr << "Assertion failed: " << message << std::endl;
                std::abort();
            }
        }

        static void warn(const std::string &message)
        {
            // print in yellow in cout
            std::cout << "\033[1;33m" << message << "\033[0m" << std::endl;
        }

        static void error(const std::string &message)
        {
            // print in red in cerr
            std::cerr << "\033[1;31m" << message << "\033[0m" << std::endl;
        }

        static void log(const std::string &message)
        {
            std::cout << message << std::endl;
        }
    };
}