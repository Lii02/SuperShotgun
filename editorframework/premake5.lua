project "EditorFramework"
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
		"LiLib",
		"Platform",
		"Renderer",
		"AudioEngine",
		"Thirdparty",
		"GameFramework"
	}