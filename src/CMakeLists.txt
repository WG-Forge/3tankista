cmake_minimum_required(VERSION 3.21)

project(server LANGUAGES CXX)

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h
                               ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(SOURCES ${HEADER_FILES} ${SOURCE_FILES})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE asio
                                              nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/server
                                                   ${CMAKE_CURRENT_SOURCE_DIR}/server/models
                                                   ${CMAKE_CURRENT_SOURCE_DIR}/server/protocols
                                                   ${CMAKE_CURRENT_SOURCE_DIR}/utility)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
