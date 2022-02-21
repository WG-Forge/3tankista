cmake_minimum_required(VERSION 3.21)

project(third_party LANGUAGES CXX)

add_subdirectory(asio)
add_subdirectory(json)
add_subdirectory(ecs)
add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(stb_image)
add_subdirectory(freetype)

