cmake_minimum_required(VERSION 3.12)

project(chicken3421)

set(CMAKE_CXX_STANDARD 17)

option(CHICKEN3421_INSTALL "Generate install target" ON)
set(GLFW_COMMIT_TAG master CACHE STRING "Which GLFW commit to use (for macOS compatibility")

message(STATUS "Using GLFW commit: ${GLFW_COMMIT_TAG}")

add_subdirectory(lib)

set(COMMON_LIBS glad glfw glm stb tinyobjloader)

add_library(chicken3421)
target_include_directories(
        chicken3421
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
target_sources(
        chicken3421
        PRIVATE
        include/chicken3421/chicken3421.hpp
        include/chicken3421/camera.hpp
        include/chicken3421/error_utils.hpp
        include/chicken3421/file_utils.hpp
        include/chicken3421/gl_utils.hpp
        include/chicken3421/window_utils.hpp

        src/camera.cpp
        src/error_utils.cpp
        src/file_utils.cpp
        src/gl_utils.cpp
        src/model.cpp
        src/window_utils.cpp
)
target_link_libraries(chicken3421 PUBLIC ${COMMON_LIBS})

if (CHICKEN3421_INSTALL)
    install(
            TARGETS chicken3421
            DESTINATION lib
            EXPORT chicken3421Targets
    )

    install(
            DIRECTORY include/chicken3421
            TYPE INCLUDE
    )

    install(
            EXPORT chicken3421Targets
            FILE chicken3421Targets.cmake
            DESTINATION lib/cmake/chicken3421
    )

    include(CMakePackageConfigHelpers)

    # generate the config file that includes the exports
    configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/chicken3421Config.cmake.in
            "${CMAKE_CURRENT_BINARY_DIR}/chicken3421Config.cmake"
            INSTALL_DESTINATION "lib/cmake/chicken3421"
            NO_SET_AND_CHECK_MACRO
            NO_CHECK_REQUIRED_COMPONENTS_MACRO
            )

    # generate the version file for the config file
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/chicken3421ConfigVersion.cmake"
            VERSION 0.01
            COMPATIBILITY AnyNewerVersion
    )

    # install the configuration file
    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/chicken3421Config.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/chicken3421ConfigVersion.cmake
            DESTINATION lib/cmake/chicken3421
            )
endif ()