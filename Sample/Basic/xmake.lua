includes("../../Engine/xmake.lua")

target("BasicRenderer")
    set_kind("binary")
    add_includedirs("./")
    add_files("main.cpp")
    add_deps("ProtoEngine")

