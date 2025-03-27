
add_requires("spdlog 1.9.2")

target("ProtoEngine")
    set_kind("static")
    set_pcxxheader("stdafx.h")
    add_includedirs("./",{public = true})
    add_files("./**.cpp")
    add_packages("spdlog")
