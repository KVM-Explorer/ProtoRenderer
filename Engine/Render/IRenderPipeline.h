#pragma once
#include <stdafx.h>
class IRenderPipeline {
public:
    virtual ~IRenderPipeline() = default;

    virtual void Initialize() = 0;
    virtual void Update(std::chrono::milliseconds deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Shutdown() = 0;
};