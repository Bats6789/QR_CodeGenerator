cmake_minimum_required(VERSION 3.10)

project(QRCode VERSION 1.0.1 LANGUAGES C)

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
add_library(image STATIC src/image.c src/image_export.c)
target_link_libraries(image ${PNG_LIBRARIES})

add_library(reed_solomon STATIC src/reed_solomon.c)

add_library(bch STATIC src/bch.c)
target_link_libraries(bch m)

add_library(QRcodeGen STATIC src/QRcode.c src/QR_codewords.c src/codeword_lookup.c)
target_link_libraries(QRcodeGen image bch reed_solomon)

# ===============Main executable========================
add_executable(QRCode src/main.c)
target_link_libraries(QRCode image m reed_solomon bch QRcodeGen)

# ===================Tests==============================
# Test binaries
add_executable(reed_solomon_test tests/reed_solomon_test.c tests/test_utils.c)
target_link_libraries(reed_solomon_test reed_solomon)

add_executable(codeword_tests tests/codeword_tests.c tests/test_utils.c)
target_link_libraries(codeword_tests QRcodeGen)

enable_testing()

add_test(NAME reed_solomon_test COMMAND $<TARGET_FILE:reed_solomon_test>)
add_test(NAME codeword_tests COMMAND $<TARGET_FILE:codeword_tests>)

set_target_properties(reed_solomon_test
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test
)

set_target_properties(codeword_tests
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test
)
