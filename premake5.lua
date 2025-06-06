workspace "2DPhysicEngine"
	architecture "x64"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "2DPhysicEngine"
	location "2DPhysicEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { 
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/SFML/include"
	}
	libdirs { "%{prj.name}/vendor/SFML/lib" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines { "EN_PLATFORM_WINDOWS", "EN_BUILD_DLL" }

	postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") }

	filter "configurations:Debug"
		symbols "On"
		links 
		{ 
			"sfml-graphics-d",
			"sfml-window-d",
			"sfml-audio-d",
			"sfml-network-d",
			"sfml-system-d"
		}

	filter "configurations:Release"
		optimize "On"
		links 
		{ 
			"sfml-graphics",
			"sfml-window",
			"sfml-audio",
			"sfml-network",
			"sfml-system"
		}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { 
		"2DPhysicEngine/src",
		"2DPhysicEngine/vendor/spdlog/include",
		"2DPhysicEngine/vendor/SFML/include"
	}
	libdirs { "2DPhysicEngine/vendor/SFML/lib" }
	links { "2DPhysicEngine"}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines { "EN_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		symbols "On"
		links 
		{ 
			"sfml-graphics-d",
			"sfml-window-d",
			"sfml-audio-d",
			"sfml-network-d",
			"sfml-system-d"
		}

	filter "configurations:Release"
		optimize "On"
		links 
		{ 
			"sfml-graphics",
			"sfml-window",
			"sfml-audio",
			"sfml-network",
			"sfml-system"
		}