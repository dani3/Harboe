workspace "Harboe"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Harboe"
    location "Harboe"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hbpch.h"
    pchsource "Harboe/src/hbpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HB_PLATFORM_WINDOWS",
            "HB_BUILD_DLL"
        }

        postbuildcommands
        {
            {"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"}
        }

    filter "configurations:Debug"
        defines "HB_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HB_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "HB_Dist"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"    
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Harboe/vendor/spdlog/include",
        "Harboe/src"
    }

    links
    {
        "Harboe"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HB_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "HB_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HB_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "HB_Dist"
        optimize "On"
