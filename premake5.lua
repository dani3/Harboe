workspace "Harboe"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Harboe/vendor/GLFW/include"
IncludeDir["Glad"] = "Harboe/vendor/Glad/include"
IncludeDir["ImGui"] = "Harboe/vendor/imgui"
IncludeDir["glm"] = "Harboe/vendor/glm"
IncludeDir["stb_image"] = "Harboe/vendor/stb_image"

include "Harboe/vendor/GLFW"
include "Harboe/vendor/Glad"
include "Harboe/vendor/imgui"

project "Harboe"
    location "Harboe"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hbpch.h"
    pchsource "Harboe/src/hbpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "HB_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "HB_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "HB_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "HB_Dist"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Harboe/src",
        "Harboe/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Harboe"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "HB_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "HB_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "HB_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "HB_Dist"
        runtime "Release"
        optimize "on"
