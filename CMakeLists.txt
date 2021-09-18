cmake_minimum_required(VERSION 3.12)

project(chicken3421 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(CHICKEN3421_INSTALL "Generate install target" ON)

set(FETCH_DEPS ON CACHE BOOL "Should the build system fetch, build, and install this project's dependencies")
if (FETCH_DEPS)
    set(BUILD_DIR ${PROJECT_SOURCE_DIR}/lib/tmp)

    # Configure the "lib" directory as a separate project (whose sole purpose is to fetch dependencies)
    execute_process(
            COMMAND ${CMAKE_COMMAND}
            -S ${PROJECT_SOURCE_DIR}/lib
            -B ${BUILD_DIR}
            -G ${CMAKE_GENERATOR}
            -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    )

    # Build it (actually downloads)
    execute_process(COMMAND ${CMAKE_COMMAND} --build ${BUILD_DIR})

    # Install the binaries (the actual things needed)
    execute_process(COMMAND ${CMAKE_COMMAND} --install ${BUILD_DIR})

    # Clean up after ourselves
    file(REMOVE_RECURSE ${BUILD_DIR})

    # Don't need to refetch the dependencies
    set(FETCH_DEPS OFF CACHE BOOL "" FORCE)
endif()

find_package(glad REQUIRED HINTS ${PROJECT_SOURCE_DIR}/lib/glad)
find_package(glfw3 REQUIRED HINTS ${PROJECT_SOURCE_DIR}/lib/glfw)
find_package(glm REQUIRED HINTS ${PROJECT_SOURCE_DIR}/lib/glm)
find_package(stb REQUIRED HINTS ${PROJECT_SOURCE_DIR}/lib/stb)

set(COMMON_LIBS glad::glad glfw glm::glm stb)

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

    # generate the config file that is includes the exports
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
endif()