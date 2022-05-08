#include <glm/glm.hpp>

#include <Entity.h>
#include <Debug.h>
#include <Camera.h>
#include <assets/Shader.h>
#include <assets/Material.h>
#include <assets/Mesh.h>
#include <Component.h>
#include <components/MeshRenderer.h>
#include <components/Transform.h>

namespace nbop::glecs
{
    MeshRenderer::MeshRenderer(std::weak_ptr<Entity> owner) : Component(owner) 
    {
        std::shared_ptr<Entity> lockedOwner = owner.lock();
        Debug::logAssert(lockedOwner != nullptr, "MeshRenderer::MeshRenderer() : owner is nullptr");

        m_transform = lockedOwner->getComponent<Transform>();
    }

    MeshRenderer::~MeshRenderer() { }

    void MeshRenderer::onNewFrame()
    {
        std::shared_ptr<Entity> owner = getOwner().lock();
        Debug::logAssert(owner != nullptr, "MeshRenderer::OnNewFrame: owner is nullptr");

        // Get the transform component
        std::shared_ptr<Transform> transform = m_transform.lock();
        if (!transform)
        {
            Debug::error("MeshRenderer::OnNewFrame: owner has no transform component");
            return;
        }

        // Get the vertex data from a Mesh component
        std::shared_ptr<Mesh> mesh = m_mesh.lock();
        if (!mesh)
        {
            Debug::error("MeshRenderer::OnNewFrame: owner has no mesh component");
            return;
        }

        // Set some uniforms and then use the material
        m_material->setMat4("u_model", transform->getModelMatrix());
        m_material->setMat4("u_view", Camera::getViewMatrix());
        m_material->setMat4("u_projection", Camera::getProjectionMatrix());
        //m_material->setFloat("u_time", Time::time());
        //m_material->setFloat("u_deltaTime", Time::deltaTime());

        m_material->use();

        // glBindVertexArray
        mesh->bind();

        // DRAW
        glDrawElements(GL_TRIANGLES, mesh->faceBufferSize(), GL_UNSIGNED_INT, 0);
    }

    void MeshRenderer::setup(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh)
    {
        mesh->setupForRendering(material->getProgram());
        m_material = material;
        m_mesh = mesh;
    }
}
