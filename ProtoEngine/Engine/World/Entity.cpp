#include "Engine/World/Entity.h"
#include "Engine/Component/MeshRender/Mesh.h"
namespace ProtoEngine::Framework {

Entity::Entity(std::string name) :
    m_Name(name),
    m_ID(EntityID++)
{
    for (int i = 0; i < static_cast<uint32>(Component::ComponentType::Num); i++) {
        auto item = static_cast<Component::ComponentType>(i);
        m_ComponentIndex[item] = -1;
    }
}

void Entity::AddComponent(std::shared_ptr<Component::IComponent> component)
{
    auto type = component->GetType();
    m_ComponentIndex[type] = m_Components.size();
    m_Components.push_back(component);
}

void Entity::MeshRender(rhi::dx12::Command &command)
{
    if (m_ComponentIndex[Component::ComponentType::Transform] != -1) {
        // Create Model Matrix
        PE_THROW("Not Implemented");
    }

    if (m_ComponentIndex[Component::ComponentType::Camera] != -1) {
        // Create View Matrix
        PE_THROW("Not Implemented");
    }

    if (m_ComponentIndex[Component::ComponentType::Light] != -1) {
        // Create Light Matrix
        PE_THROW("Not Implemented");
    }

    if (m_ComponentIndex[Component::ComponentType::Mesh] != -1) {
        auto component = m_Components[m_ComponentIndex[Component::ComponentType::Mesh]];
        auto meshRender = static_cast<Component::Mesh *>(component.get());
        meshRender->Render(command);
    }
}

} // namespace ProtoEngine::Framework