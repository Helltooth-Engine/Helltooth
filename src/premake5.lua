function setProjectOutputDirectories() 
	objdir "$(SolutionDir)\\Intermediates\\"
	targetdir "$(SolutionDir)\\bin\\$(Platform)\\$(Configuration)\\$(ProjectName)\\"
end

function setConfigurationFilters() 
	filter {"configurations:Debug-GL"}
		defines {
			"HT_OPENGL",
			"HT_DEBUG"
		}
	filter {"configurations:Release-GL"}
		defines {
			"HT_OPENGL",
			"HT_RELEASE"
		}
		optimize "Full"
    	symbols "Off"
	filter {"configurations:Debug-DX"}
		defines {
			"HT_DIRECTX",
			"HT_DEBUG"
		}
	filter {"configurations:Release-DX"}
		defines {
			"HT_DIRECTX",
			"HT_RELEASE"
		}
		optimize "Full"
    	symbols "Off"
	filter {"platforms:x86"}
		defines {
			"HT_WINDOWS"
		}
	filter {"platforms:x64"}
		defines {
			"HT_WINDOWS"
		}
	filter {}
end


workspace ("Helltooth")
    configurations {
        "Debug-GL",
        "Release-GL",
        "Debug-DX",
        "Release-DX",
    }

    platforms {
        "x86",
        "x64",
    }

    location "../Solution/"
    startproject "Sandbox"

project ("Helltooth")
    kind ("StaticLib")
    files {
        "engine/**.hpp",
        "engine/**.cpp",
    }
    location "../Solution/Helltooth/"
    includedirs {
		"$(SolutionDir)../src/engine/"
	}

    setProjectOutputDirectories() 
    setConfigurationFilters()

project ("Sandbox")
    kind ("ConsoleApp")
    files {
        "demo/**.h",
        "demo/**.hpp",
        "demo/**.cpp",
        "../Solution/Sandbox/res/*/*.*"
    }
    location "../Solution/Sandbox/"
    dependson "Helltooth"
    links {
		"Helltooth.lib",
	}
	filter {"configurations:Debug-GL"}
		links {
			"opengl32"
		}
	filter {"configurations:Release-GL"}
		links {
			"opengl32"
		}
	filter {"configurations:Debug-DX"}
		links {
			"D3D11",
			"d3dcompiler"
		}
	filter {"configurations:Release-DX"}
		links {
			"D3D11",
			"d3dcompiler"
		}
	filter {}
	
	sysincludedirs {
		"$(SolutionDir)../src/engine/"
	}

	syslibdirs {
		"$(SolutionDir)bin\\$(Platform)\\$(Configuration)\\Helltooth\\"
	}

    setProjectOutputDirectories() 
    setConfigurationFilters()