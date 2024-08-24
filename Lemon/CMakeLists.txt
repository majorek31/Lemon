file(GLOB_RECURSE SOURCES "src/*.cpp")

set(spdlog_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)

find_package(spdlog REQUIRED)
find_package(OpenGL REQUIRED)

add_library(Lemon STATIC ${SOURCES})
set_property(TARGET Lemon PROPERTY CXX_STANDARD 17)
target_link_libraries(Lemon PRIVATE spdlog::spdlog_header_only glfw OpenGL::GL)
target_include_directories(Lemon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_precompile_headers(Lemon PRIVATE src/pch.h)