project "GLRenderer"
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
		"Platform"
	}