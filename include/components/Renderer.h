#pragma once

#include <glm/glm.hpp>

#include <Component.h>

namespace nbop::glecs
{
    class Renderer : public Component
    {
    public:
        static constexpr auto Type = "Renderer";

        Renderer(std::weak_ptr<Entity> owner);
        ~Renderer() override;
        
        private:
    };
}