
add_requires("spdlog 1.9.2")

add_requires("directxshadercompiler")
add_requires("directxtex")
-- add_requires("directx-headers v1.610.0")


target("ProtoEngine")
    set_kind("static")
    set_pcxxheader("stdafx.h")
    add_includedirs("./",{public = true})
    add_files("./**.cpp")
    add_options("rhi_dx12")
    add_packages("spdlog","directxshadercompiler","directxtex")
    add_defines("RHI_DX12")

    
    -- 定义编译选项
