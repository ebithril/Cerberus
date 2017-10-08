workspace "Cerberus"
	configurations { "Debug", "Release" }
	filter "language:C++"
		buildoptions "-std=c++11"

targetdir "bin/%{cfg.buildcfg}"

project "Cerberus"
	kind "ConsoleApp"
	language "C++"

	files { "*.h", "*.c", "*.cpp" }
	includedirs { "Utils", "Engine" }
	libdirs { "$(VK_SDK_PATH)/Lib" }
	links { "Engine", "Utils", "SDL2", "SDL2main" }

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
	includedirs { "Utils", "$(VK_SDK_PATH)/Include" }
	
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

