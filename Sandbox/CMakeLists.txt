file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Sandbox ${SOURCES})

target_link_libraries(Sandbox PUBLIC Lemon)

target_include_directories(Sandbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
