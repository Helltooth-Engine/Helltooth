function setDefines(name) 
	filter {"configurations:Debug-GL"}
		objdir ("../../Intermediates/Debug-GL/" .. name .. "/")
		targetdir ("../../bin/Debug-GL/" .. name .. "/")
		defines {
			"HT_DEBUG",
			"HT_OPENGL",
		}

	filter {"configurations:Release-GL"}
		objdir ("../../Intermediates/Release-GL/" .. name .. "/")
		targetdir ("../../bin/Release-GL/" .. name .. "/")
		defines {
			"HT_RELEASE",
			"HT_OPENGL",
		}
		optimize "Full"
		symbols "Off"

	filter {"configurations:Debug-DX"}
		objdir ("../../Intermediates/Debug-DX/" .. name .. "/")
		targetdir ("../../bin/Debug-DX/" .. name .. "/")
			defines {
			"HT_DEBUG",
			"HT_DIRECTX",
		}

	filter {"configurations:Release-DX"}
		objdir ("../../Intermediates/Release-DX/" .. name .. "/")
		targetdir ("../../bin/Release-DX/" .. name .. "/")
		defines {
			"HT_RELEASE",
			"HT_DIRECTX",
		}
		optimize "Full"
		symbols "Off"

	filter { "system:linux" }
		buildoptions {
			"-msse4.1",
			"-mfma",
            "-ggdb",
		}
	
	filter { "system:windows" }
		characterset "MBCS"

	filter {}

	defines {
		("HT_" .. os.host():upper()),
	}
end

function makeProject(name) 
	project(name)
	location ("../../Solution/" .. name .. "/")
	
	cppdialect "C++14"

	setDefines(name)
end
