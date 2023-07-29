project "mainapp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
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

    postbuildcommands {
        '{COPYDIR} %[rsc] %[%{cfg.targetdir}/rsc]'
    }

    filter "system:windows"
        prebuildcommands {
            '{COPYFILE} %[%{LibraryDirs.sdl}/SDL2.dll] %[%{prj.location}/src]',
            '{COPYFILE} %[%{LibraryDirs.sdl}/SDL2.dll] %[%{cfg.targetdir}]',
        }

    filter "configurations:Debug2"
        defines { "RTS_DEBUG" }
        symbols "On"

    filter "configurations:Release2"
        defines { "RTS_NDEBUG" }
        symbols "Off"
        optimize "Full"
