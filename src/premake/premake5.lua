require "projectTemplate"
require "demoTemplate"

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

group "Helltooth"
makeProject("Cereal")
	kind("StaticLib")
	files {
		"../Cereal/Cereal/Cereal/**.h",
	}
	includedirs {
		"../Cereal/Cereal/Cereal/src",
	}

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
		"../engine/**.htsl",
	}
	dependson "Helltooth-ShadingLanguage"
	dependson "Cereal"

	includedirs {
		"../engine/",
		"../Helltooth-ShadingLanguage/src/htsl/",
		"../Cereal/Cereal/",
	}

group "Sandbox"
makeDemo ("10000Cubes")
