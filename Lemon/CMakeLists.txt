file(GLOB_RECURSE SOURCES "src/*.cpp")

find_package(spdlog REQUIRED)
add_library(Lemon STATIC ${SOURCES})

target_include_directories(Lemon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_precompile_headers(Lemon PRIVATE src/pch.h)