project "ECS"
    kind "staticlib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    objdir ("bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

    files
    {
        "ECS/include/ECS/**.h",
        "ECS/src/ECS/**.h",
        "ECS/src/ECS/**.cpp"
    }

    includedirs
    {
        "ECS/include",
        "ECS/src"
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
