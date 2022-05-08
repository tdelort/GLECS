#pragma once

#include <glm/glm.hpp>

#include <Component.h>
#include <components/Transform.h>
#include <assets/Mesh.h>
#include <assets/Material.h>

namespace nbop::glecs
{
    class MeshRenderer : public Component
    {
    public:
        static constexpr auto Type = "MeshRenderer";

        MeshRenderer(std::weak_ptr<Entity> owner);
        ~MeshRenderer() override;
        
        void onNewFrame() override;

        void setup(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh);

        private:
        std::shared_ptr<Material> m_material;

        // weak_ptr because autority is owned by the entity
        std::weak_ptr<Transform> m_transform;
        std::weak_ptr<Mesh> m_mesh;
    };
}