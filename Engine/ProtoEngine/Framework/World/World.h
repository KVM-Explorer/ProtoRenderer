#pragma once
#include <stdafx.h>
#include "ProtoEngine/Framework/World/Entity.h"
#include "ProtoEngine/RHI/DX12/DX12.h"
namespace ProtoEngine::Framework {
class World {
public:
    World() {};
    ~World() {};

    void Render(rhi::dx12::Command &command);
    void Update(rhi::dx12::Command &command);

    void AddEntity(Entity &entity) { m_Entities.push_back(entity); };
    void RemoveEntity(Entity &entity);

private:
    std::vector<Entity> m_Entities;

    // Space partitioning & Acceleration structures
};

}; // namespace ProtoEngine::Framework