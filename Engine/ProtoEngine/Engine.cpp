#include "ProtoEngine/Engine.h"
#include "ProtoEngine/Core/Core.h"
namespace ProtoEngine {
extern std::shared_ptr<ProtoEngine::App> CreateApp();

Engine::Engine() {}

Engine::~Engine() {}
} // namespace ProtoEngine

void ProtoEngine::Engine::Init()
{
    // Init Log
    auto logger = Core::Log::GetCore();

    // Load Instance
    m_App = CreateApp();
}