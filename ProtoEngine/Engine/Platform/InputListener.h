#pragma once
#include <stdafx.h>
namespace ProtoEngine::Platform {

enum KeyStatus : uint32_t {
    Down = 0,
    Pressed = 1,
    Up = 2,
};

enum MouseSource : uint32_t {
    Left = 0,
    Right = 1,
    Middle = 2,
};

struct KeyEvent {
    KeyStatus Status;
    uint32 KeyCode;
    std::function<void()> Callback;
};

struct MouseEvent {
    KeyStatus Status;
    uint32 Button;
    float X;
    float Y;
};

class InputListener {
public:
    virtual ~InputListener() = default;

    void RegisterKeyEvent(uint32_t keyCode, KeyStatus status, std::function<void()> callback)
    {
        RegisterKeyEvent({status, keyCode, callback});
    }

private:
    void RegisterKeyEvent(const KeyEvent &event)
    {
        m_KeyEvents.push_back(event);
    }
    std::vector<KeyEvent> m_KeyEvents;
};
} // namespace ProtoEngine::Platform