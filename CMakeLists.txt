cmake_minimum_required(VERSION 3.12)

project(chicken3421 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

list(APPEND COMMON_LIBS glad glfw glm stb)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_LIST_DIR})
    message(STATUS "Checking submodules...")
    execute_process(COMMAND git submodule update --init --recursive)
    add_subdirectory(lib)
    message(STATUS "Submodules updated successfully")
else()
    message(STATUS "chicken3421 assuming that ${COMMON_LIBS} have globally available targets.")
    message(STATUS "If this is not so, please run `git submodule update --init --recursive` in the root of the project")
endif()

add_library(chicken3421)
target_include_directories(chicken3421 PUBLIC include)
target_sources(
        chicken3421
        PRIVATE
        include/chicken3421/chicken3421.hpp
        include/chicken3421/error.hpp
        include/chicken3421/file_utils.hpp
        include/chicken3421/gl_utils.hpp
        include/chicken3421/window_utils.hpp

        src/error.cpp
        src/file_utils.cpp
        src/gl_utils.cpp
        src/window_utils.cpp
)
target_link_libraries(chicken3421 PUBLIC ${COMMON_LIBS})