cmake_minimum_required(VERSION 3.12)

project("stb-cmake")

set(CMAKE_CXX_STANDARD 17)

option(STB_CMAKE_INSTALL "Generate install target" ON)

include (FetchContent)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb
    GIT_TAG master
)
FetchContent_MakeAvailable(stb)

configure_file(${stb_SOURCE_DIR}/stb_image.h ${PROJECT_SOURCE_DIR}/include/stb/stb_image.h COPYONLY)

add_library(stb)
target_sources(stb PRIVATE src/stb_image.cpp)
target_include_directories(
    stb
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if (STB_CMAKE_INSTALL)
    install(
        TARGETS stb
        DESTINATION lib
        EXPORT stbTargets
    )

    install(
        DIRECTORY include/stb
        TYPE INCLUDE
        FILES_MATCHING PATTERN *.h
    )

    install(
        EXPORT stbTargets
        FILE stbTargets.cmake
        DESTINATION lib/cmake/stb
    )

    include(CMakePackageConfigHelpers)

    # generate the config file that is includes the exports
    configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/stbConfig.cmake.in
            "${CMAKE_CURRENT_BINARY_DIR}/stbConfig.cmake"
            INSTALL_DESTINATION "lib/cmake/stb"
            NO_SET_AND_CHECK_MACRO
            NO_CHECK_REQUIRED_COMPONENTS_MACRO
            )

    # generate the version file for the config file
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/stbConfigVersion.cmake"
            VERSION 0.01
            COMPATIBILITY AnyNewerVersion
    )

    # install the configuration file
    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/stbConfig.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/stbConfigVersion.cmake
            DESTINATION lib/cmake/stb
            )
endif()