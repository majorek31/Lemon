function build_glfw()
    os.execute("cmake -S vendor/glfw -B vendor/glfw -D BUILD_SHARED_LIBS=OFF -D GLFW_BUILD_EXAMPLES=OFF -D CMAKE_BUILD_TYPE=Release && cmake --build vendor/glfw")
end
function build_spdlog()
    os.execute("cd vendor/spdlog && cmake . -DCMAKE_BUILD_TYPE=Release && cmake --build .")
end
build_glfw()
build_spdlog()
project "Lemon"
    kind "StaticLib"
    language "C++"
    files {
        "src/**.cpp",
        "src/**.h"
    }
    includedirs {
        "src",
        "vendor/spdlog/include",
        "vendor/glfw/include"
    }
    libdirs {
        "vendor/spdlog",
        "vendor/glfw/src/Debug"
    }
    links {
        "glfw3",
    }
    pchheader "pch.h"
    pchsource "src/pch.cpp"

    filter { "configurations:Debug" }
    defines { "DEBUG" }
    symbols "On"

    filter { "configurations:Release" }
    defines { "NDEBUG" }
    optimize "On"

    filter "files:vendor/spdlog/**.cpp"
        flags { "NoPCH" }
        defines { "SPDLOG_COMPILED_LIB" }