project "ECS"
    location "ECS"
    kind "staticlib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    objdir ("bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

    files
    {
        "include/**.h",

        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "include",
        "src"
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
