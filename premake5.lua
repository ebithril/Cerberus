workspace "Cerberus"
	configurations { "Debug", "Release" }
	filter "language:C++"
		buildoptions { "-std=c++17", "-pedantic" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

targetdir "bin/%{cfg.buildcfg}"

project "Cerberus"
	kind "ConsoleApp"
	language "C++"

	files { "*.h", "*.c", "*.cpp" }
	includedirs { "Utils", "Engine" }
	libdirs { "$(VK_SDK_PATH)/Lib" }
	links { "Engine", "Utils", "SDL2", "SDL2main" }

project "Engine"
	kind "StaticLib"
	language "C++"
	
	files { "Engine/**.h", "Engine/**.c", "Engine/**.cpp" }
	includedirs { "Utils", "$(VK_SDK_PATH)/Include" }

project "Utils"
	kind "StaticLib"
	language "C++"
	
	files { "Utils/**.h", "Utils/**.c", "Utils/**.cpp" }
	includedirs { "thirdparty" }

