workspace "Cerberus"
	configurations { "Debug", "Release" }
	filter "language:C++"
		buildoptions "-std=c++11"

project "Cerberus"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files { "*.h", "*.c", "*.cpp" }
	includedirs { "Utils", "Engine" }
	links { "Engine", "Utils" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

project "Engine"
	kind "StaticLib"
	language "C++"
	
	files { "Engine/**.h", "Engine/**.c", "Engine/**.cpp" }
	includedirs { "Utils", "C:/VulkanSDK/1.0.46.0/Include" }
	libdirs { os.findlib("Vulkan") }
	links { "Utils" }
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

project "Utils"
	kind "StaticLib"
	language "C++"
	
	files { "Utils/**.h", "Utils/**.c", "Utils/**.cpp" }
	includedirs { "thirdparty" }
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

