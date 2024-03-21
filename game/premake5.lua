project "Game"
	kind "ConsoleApp"
	
	files {
		"**.cpp",
		"**.h"
	}
	includedirs {
		"%{wks.location}"
	}
	links {
		"LiLib",
		"Platform",
		"GLRenderer",
		"GameFramework",
		"Thirdparty"	
	}