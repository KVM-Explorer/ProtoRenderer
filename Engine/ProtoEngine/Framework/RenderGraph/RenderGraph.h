#pragma once

#include <stdafx.h>

namespace ProtoEngine::framework {

class RenderGraph {
public:
    RenderGraph() {};
    virtual ~RenderGraph() {};

    void Setup();
    void Compile();
    void Execute();

private:
    void SetupFrameSyncPoints();

    
};

}; // namespace ProtoEngine::framework