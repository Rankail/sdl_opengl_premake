project "mainapp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/"..outputdir.."/%{prj.name}")
    objdir ("%{wks.location}/bin-int/"..outputdir.."/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp",
        (VendorPath.."/glad/src/glad.c")
    }

    includedirs {
        "src",
        IncludeDirs.glad,
        IncludeDirs.sdl
    }

    libdirs {
        LibraryDirs.sdl
    }

    links {
        "SDL2",
        "SDL2main"
    }

    filter "action:clion"
        postbuildcommands {
            '{COPYDIR} "../../../%{prj.name}/rsc" "%{cfg.targetdir}"'
        }

    filter "action:not clion"
        postbuildcommands {
            '{COPYDIR} "rsc" "%{cfg.targetdir}/rsc"'
        }

    filter "system:windows"
        prebuildcommands {
            '{COPYFILE} "%{LibraryDirs.sdl}/SDL2.dll" "%{prj.location}/src"',
            '{COPYFILE} "%{LibraryDirs.sdl}/SDL2.dll" "%{cfg.targetdir}"',
        }

    filter "configurations:Debug"
        defines { "RTS_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RTS_NDEBUG" }
        symbols "Off"
        optimize "Full"
