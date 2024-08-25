workspace "Lemon"
    cppdialect "C++17"
    architecture "x86_64"
    buildoptions { "/MP" }
    configurations { "Debug", "Release" }

group "Core"
    include "Lemon"
group ""

group "Misc"
    include "Sandbox"
group ""
