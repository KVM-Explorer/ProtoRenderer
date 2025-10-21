
add_requires("spdlog 1.9.2")
add_requires("directxshadercompiler")
add_requires("directxtex")
add_requires("directx-headers")
add_requires("tinyobjloader v2.0.0rc13") 
add_requires("directx12-agility")


target("ProtoEngine")
    set_kind("object")
    set_pcxxheader("stdafx.h")
    add_includedirs("./",{public = true})
    add_files("./**.cpp")
    add_options("rhi_dx12")
    add_packages("spdlog","directxshadercompiler","directxtex","assimp",{public = true})
    add_packages("directx12-agility",{public = true})
    add_packages("directx-headers",{public = true})
    add_defines("RHI_DX12")
    --  Windows / DX12 / Factory
    add_syslinks("User32","D3D12","DXGI","Shell32.lib") 

    
    -- 定义编译选项
