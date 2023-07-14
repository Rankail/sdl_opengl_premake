
VendorPath = "%{wks.location}/vendor"
IncludeDirs = {}
IncludeDirs.glad = (VendorPath.."/glad/include")
IncludeDirs.sdl = (VendorPath.."/sdl2/include")

LibraryDirs = {}
LibraryDirs.sdl = (VendorPath.."/sdl2/lib")

workspace "sdl_gl_test"
    startproject "mainapp"
    architecture "x86_64"
    configurations {"Debug", "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "mainapp"