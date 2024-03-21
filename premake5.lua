workspace "SuperShotgun"
	cppdialect "C++17"
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	targetdir ("%{wks.location}/build")
	objdir ("%{wks.location}/" .. outputdir)
	flags {
		"MultiProcessorCompile"	
	}
	defines {
		"UNICODE",
		"_CRT_SECURE_NO_WARNINGS",
		"LILIB_ENABLE_ASSERTS",
	}
	configurations { "Debug", "Release" }
	platforms { "Win32", "Win64" }
	includedirs { "thirdparty", "FreeType" }
	libdirs { "thirdparty" }
	filter "platforms:Win32"
		architecture "x86"
	filter "platforms:Win64"
		architecture "x86_64"	
	filter "configurations:Debug"
		defines {"DEBUG"}
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines {"NDEBUG"}
		runtime "Release"
		optimize "on"
	filter "system:windows"
		defines {"ENGINE_WINDOWS"}
		links {"gdi32", "opengl32", "OpenAL32", "freetype" }
	filter "system:linux"
		defines {"ENGINE_LINUX"}
	filter "system:macosx"
		defines {"ENGINE_MACOSX"}
	filter "system:android"
		defines {"ENGINE_ANDROID"}

include "game"
include "lilib"
include "platform"
include "glrenderer"
include "gameframework"
include "audio"
include "thirdparty"
include "editorframework"