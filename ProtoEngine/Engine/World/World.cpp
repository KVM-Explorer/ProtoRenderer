#include "Engine/World/World.h"

namespace ProtoEngine::Framework {

void World::Render(rhi::dx12::Command &command)
{
    for (auto &entity : m_Entities) {
        entity.MeshRender(command);
    }
}

} // namespace ProtoEngine::Framework