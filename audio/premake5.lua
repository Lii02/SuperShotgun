project "AudioEngine"
	kind "StaticLib"
	language "C++"

	files {
		"**.cpp",
		"**.h",
	}
	includedirs {
		"%{wks.location}"
	}
	links {
		"LiLib"
	}