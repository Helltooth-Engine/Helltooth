function makeProject(name) 
	project(name)
	location ("../../Solution/" .. name .. "/")
	
	cppdialect "C++14"

	filter {"configurations:Debug-GL"}
		defines {
			"HT_DEBUG",
			"HT_OPENGL",
		}

	filter {"configurations:Release-GL"}
		defines {
			"HT_RELEASE",
			"HT_OPENGL",
		}
		optimize "Full"
		symbols "Off"

	filter {"configurations:Debug-DX"}
		defines {
			"HT_DEBUG",
			"HT_DIRECTX",
		}


	filter {"configurations:Release-DX"}
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
			
		}
	filter {}

	defines {
		("HT_" .. os.host():upper()),
	}

	objdir ("../../Intermediates/" .. name .. "/")
	targetdir ("../../bin/" .. name .. "/")
end
