#pragma once
#include <stdafx.h>
namespace ProtoEngine::rhi::dx12 {

struct ViewPort {
    float TopLeftX;
    float TopLeftY;
    float Width;
    float Height;

    ViewPort(float topLeftX, float topLeftY, float width, float height) :
        TopLeftX(topLeftX), TopLeftY(topLeftY), Width(width), Height(height) {}
    ViewPort(float width, float height) :
        TopLeftX(0), TopLeftY(0), Width(width), Height(height) {}

    void ClearRT(std::vector<uint32> targets);
};

enum class CommandType {
    Graphics,
    Compute,
    Copy,
};

class Command {
public:
    virtual ~Command() = default;

    void SetViewPort(const ViewPort &viewPort) { m_ViewPort = viewPort; }
    const ViewPort &GetViewPort() const { return m_ViewPort; }

    CommandType Type() const { return m_Type; }
    ID3D12CommandList* Get() const { return m_CommandList.Get(); }

private:
    ViewPort m_ViewPort;
    CommandType m_Type;

    ComPtr<ID3D12CommandList> m_CommandList;
};

class CommandPool {
public:
    virtual ~CommandPool() = default;
};

} // namespace ProtoEngine::rhi::dx12