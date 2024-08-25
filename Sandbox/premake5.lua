project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    files {
        "**.cpp",
        "**.h"
    }
    includedirs {
        "src",
        "../Lemon/src"
    }
    links {
        "Lemon"
    }
    filter { "configurations:Debug" }
    defines { "DEBUG" }
    symbols "On"

    filter { "configurations:Release" }
    defines { "NDEBUG" }
    optimize "On"