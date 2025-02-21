cmake_minimum_required(VERSION 3.10)

project(QRCode VERSION 1.0 LANGUAGES C)

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

# Find libraries
find_package(PNG MODULE)
if(PNG_FOUND)
	include_directories(${PNG_INCLUDE_DIRS})
else()
	message(FATAL_ERROR "libpng not found")
endif()

# =================Libraries============================
add_library(image STATIC src/image_export.c)
target_link_libraries(image ${PNG_LIBRARIES})

# ===============Main executable========================
add_executable(QRCode src/main.c)
target_link_libraries(QRCode image m)

# ===================Tests==============================
# Reed solomon
add_executable(reed_solomon_test tests/reed_solomon_test.c)

enable_testing()

add_test(NAME reed_solomon_test COMMAND $<TARGET_FILE:reed_solomon_test>)

set_target_properties(reed_solomon_test
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test
)
