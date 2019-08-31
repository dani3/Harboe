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
IncludeDir["Glad"] = "Harboe/vendor/GLAD/include"
IncludeDir["ImGui"] = "Harboe/vendor/imgui"
IncludeDir["glm"] = "Harboe/vendor/glm"

include "Harboe/vendor/GLFW"
include "Harboe/vendor/Glad"
include "Harboe/vendor/imgui"

project "Harboe"
    location "Harboe"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hbpch.h"
    pchsource "Harboe/src/hbpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
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
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "HB_PLATFORM_WINDOWS",
            "HB_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            {"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"}
        }

    filter "configurations:Debug"
        defines { "HB_DEBUG", "HB_ENABLE_ASSERTS" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "HB_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "HB_Dist"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "HB_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "HB_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "HB_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "HB_Dist"
        runtime "Release"
        optimize "On"
