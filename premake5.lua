project "ECS"
    location "ECS"
    kind "staticlib"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    objdir ("bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

    files
    {
        "%{prj.name}/include/**.h",

        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/include",
        "%{prj.name}/src"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "ECS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "ECS_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "ECS_DIST"
        optimize "On"
