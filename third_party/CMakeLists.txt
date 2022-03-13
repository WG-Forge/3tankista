cmake_minimum_required(VERSION 3.21)

project(third_party LANGUAGES CXX)

set(NANA_STATIC_STDLIB OFF CACHE BOOL "Build with shared stdlibc++")
add_subdirectory(nana)
add_subdirectory(asio)
add_subdirectory(json)
add_subdirectory(ecs)
add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(stb_image)
add_subdirectory(freetype)

