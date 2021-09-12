cmake_minimum_required(VERSION 3.12)

project(chicken3421 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(chicken3421)
target_include_directories(chicken3421 PUBLIC include)
target_sources(
        chicken3421
        PRIVATE
        src/file_utils.cpp
)
target_link_libraries(chicken3421 PUBLIC glad glfw glm stb)