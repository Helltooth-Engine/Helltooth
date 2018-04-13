require "projectTemplate"
function makeDemo(name) 
	project(name)
	location ("../../Solution/demo/" .. name .. "/")

	kind ("ConsoleApp")
	files {
		"../demo/" .. name .."/**.h",
		"../demo/" .. name .."/**.hpp",
		"../demo/" .. name .."/**.cpp",
		"../demo/res/*/*.*"
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
	
	debugdir ("../demo/")
	
	setDefines(name)

	sysincludedirs {
		"../engine/",
		"../Helltooth-ShadingLanguage/src/htsl/",
	}

	syslibdirs {
		"../../bin/Helltooth/",
		"../../bin/Helltooth-ShadingLanguage/",
	}

end