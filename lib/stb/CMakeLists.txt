cmake_minimum_required(VERSION 3.12)

project("stb-cmake")

set(CMAKE_CXX_STANDARD 17)

configure_file(${PROJECT_SOURCE_DIR}/lib/stb/stb_image.h ${PROJECT_SOURCE_DIR}/include/stb/stb_image.h COPYONLY)

add_library(stb)
target_sources(stb PRIVATE ${PROJECT_SOURCE_DIR}/src/stb_image.cpp)
target_include_directories(stb PUBLIC ${PROJECT_SOURCE_DIR}/include)