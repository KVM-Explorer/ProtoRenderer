#pragma once
#include <stdafx.h>
#include "Engine/RHI/DX12/Resource/MeshContainer.h"
#include "Engine/Component/IComponent.h"
#include "Engine/RHI/DX12/Runtime/Command.h"
namespace ProtoEngine::Framework {
class Entity {
public:
    Entity(std::string name);

    std::string_view GetName() const { return m_Name; }

    void AddComponent(std::shared_ptr<Component::IComponent> component);
    void MeshRender(rhi::dx12::Command &command);

    void Upload();

private:
    static inline uint64 EntityID = 0;
    std::vector<std::shared_ptr<Component::IComponent>> m_Components;
    std::unordered_map<Component::ComponentType, int32> m_ComponentIndex;
    uint64 m_ID;
    std::string m_Name;
};
} // namespace ProtoEngine::Framework