-- premake5.lua
workspace "CSE-16"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "CSE-16"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus", "/permissive-", "/utf-8" }

OutputDir = "build/%{cfg.buildcfg}"

group "CSE-16"
	include "CSE-16/Build-CSE-16.lua"