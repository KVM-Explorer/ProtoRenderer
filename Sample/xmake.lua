


for _, dir in ipairs(os.dirs("./*")) do
    -- print(dir)

    target(dir)
        set_kind("binary")
        add_includedirs(dir)
        add_files(dir .. "/*.cpp")
        add_deps("ProtoEngine")
        if is_mode("debug") then 
            set_symbols("debug")
            set_optimize("none")
        end 

end


