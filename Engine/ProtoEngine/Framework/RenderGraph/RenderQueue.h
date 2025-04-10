#pragma once

#include "stdafx.h"
#include "ProtoEngine/Resource/Material/Material.h"
#include "ProtoEngine/Component/MeshRender/Mesh.h"

namespace ProtoEngine::framework {

struct RenderItem {
    std::shared_ptr<const Component::Mesh> mesh;
    std::shared_ptr<const resource::Material> material;
};

class RenderQueue {
public:
    void Add(const RenderItem &item);
    void Clear();

    const std::vector<RenderItem> &GetOpaqueItems();
    const std::vector<RenderItem> &GetTransparentItems();
    const std::vector<RenderItem> &GetUIItems();
    const std::vector<RenderItem> &GetSkyboxItems();
    const std::vector<RenderItem> &GetDebugItems();

private:
    std::vector<RenderItem> OpaqueItems;
    std::vector<RenderItem> TransparentItems;
    std::vector<RenderItem> SkyboxItems;
    std::vector<RenderItem> UIItems;
    std::vector<RenderItem> DebugItems;
};

} // namespace ProtoEngine::framework