cmake_minimum_required(VERSION 3.10)

project(QRCode VERSION 1.0 LANGUAGES C)

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

# Find libraries
find_package(PNG MODULE)

# Build Libraries
add_library(image STATIC src/image_export.c)
target_link_libraries(image png)

# Main executable
add_executable(QRCode src/main.c)
target_link_libraries(QRCode image)
