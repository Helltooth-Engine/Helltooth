function setProjectOutputDirectories() 
	objdir "$(SolutionDir)\\Intermediates\\"
	targetdir "$(SolutionDir)\\bin\\$(Platform)\\$(Configuration)\\$(ProjectName)\\"
end

workspace ("Helltooth")
    configurations {
        "Debug",
        "Release",
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
        "engine/**.h",
        "engine/**.cpp",
    }
    location "../Solution/Helltooth/"

    setProjectOutputDirectories() 

project ("Sandbox")
    kind ("ConsoleApp")
    files {
        "demo/**.h",
        "demo/**.cpp",
    }
    location "../Solution/Sandbox/"
    dependson "Helltooth"
    links {
    	"Opengl32",
		"Helltooth.lib",
	}
	sysincludedirs {
		"$(SolutionDir)../src/engine/"
	}

	syslibdirs {
		"$(SolutionDir)bin\\$(Platform)\\$(Configuration)\\Helltooth\\"
	}

    setProjectOutputDirectories() 