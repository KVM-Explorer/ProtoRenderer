#pragma once
#include "ProtoEngine/App.h"
namespace ProtoEngine {

class Engine {
public:
    Engine();
    ~Engine();

    void ParseParams() {}
    void Init();

    std::shared_ptr<App> GetApp() const { return m_App; }

private:
    std::shared_ptr<App> m_App;
};
} // namespace ProtoEngine