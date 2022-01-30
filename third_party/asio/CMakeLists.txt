cmake_minimum_required(VERSION 3.21)



###############################################################################
## LIBRARY-PROJECT
## name and version
###############################################################################
project(asio LANGUAGES CXX)



###############################################################################
## SETTINGS
## basic project settings before use
###############################################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Enabling export of all symbols to create a dynamic library
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")



###############################################################################
## FETCH
## fetch content of library
###############################################################################
include(FetchContent)
FetchContent_Declare(
    asio_src
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-21-0)
FetchContent_MakeAvailable(asio_src)



###############################################################################
## TARGET
## create target and add include path
###############################################################################
# create lib from src
if (NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME} INTERFACE)
endif()

target_include_directories(${PROJECT_NAME} INTERFACE ${asio_src_SOURCE_DIR}/asio/include)

if(UNIX)
  target_link_libraries(asio
    INTERFACE pthread
  )
elseif (WIN32 AND MINGW)
    target_link_libraries(${PROJECT_NAME} INTERFACE ws2_32)
endif()



###############################################################################
## ADDITIONAL SETTINGS
## additional options and project settings
###############################################################################
target_compile_definitions(${PROJECT_NAME} INTERFACE ASIO_NO_DEPRECATED)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

