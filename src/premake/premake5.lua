require "projectTemplate"

workspace ("Helltooth")
	filter { "system:windows"}
		configurations {
			"Debug-GL",
			"Release-GL",
			"Debug-DX",
			"Release-DX",
		}
	filter { "system:linux"}
		configurations {
			"Debug-GL",
			"Release-GL",
		}

	filter {}

	platforms {
		"x86",
		"x64",
	}

	location "../../Solution/"
	startproject "Sandbox"

makeProject("Helltooth-ShadingLanguage")
	kind ("StaticLib")
	files {
		"../Helltooth-ShadingLanguage/src/htsl/**.hpp",
		"../Helltooth-ShadingLanguage/src/htsl/**.cpp",
	}
	includedirs {
		"../Helltooth-ShadingLanguage/src/htsl/"
	}

makeProject ("Helltooth")
	kind ("StaticLib")
	files {
		"../engine/**.hpp",
		"../engine/**.cpp",
	}
	dependson "Helltooth-ShadingLanguage"
	includedirs {
		"../engine/",
		"../Helltooth-ShadingLanguage/src/htsl/",
	}

makeProject ("Sandbox")
	kind ("ConsoleApp")
	files {
		"../demo/**.h",
		"../demo/**.hpp",
		"../demo/**.cpp",
		"../../Solution/Sandbox/res/*/*.*"
	}
	dependson {
		"Helltooth",
		"Helltooth-ShadingLanguage",
	}
	
	links {
		"Helltooth",
		"Helltooth-ShadingLanguage",
	}

	filter {"configurations:Debug-GL", "system:windows" }
		links {
			"opengl32"
		}
	filter {"configurations:Release-GL", "system:windows" }
		links {
			"opengl32"
		}
	filter {"configurations:Debug-DX", "system:windows" }
		links {
			"D3D11",
			"d3dcompiler"
		}
	filter {"configurations:Release-DX", "system:windows" }
		links {
			"D3D11",
			"d3dcompiler"
		}

	filter { "system:linux", "configurations:Debug-GL"}
		links {
			"GL",
			"X11",
			"GLU",
		}
	filter { "system:linux", "configurations:Release-GL"}
		links {
			"GL",
			"X11",
			"GLU",
		}
	filter {}
	
	sysincludedirs {
		"../engine/",
		"../Helltooth-ShadingLanguage/src/htsl/",
	}

	syslibdirs {
		"../../bin/Helltooth/",
		"../../bin/Helltooth-ShadingLanguage/",
	}
