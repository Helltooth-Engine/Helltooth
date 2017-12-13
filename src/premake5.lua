function setProjectOutputDirectories() 
	objdir "$(SolutionDir)\\Intermediates\\"
	targetdir "$(SolutionDir)\\bin\\$(Platform)\\$(Configuration)"
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
        "src/**.h",
        "src/**.cpp",
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
    setProjectOutputDirectories() 