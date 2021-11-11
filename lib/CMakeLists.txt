include(FetchContent)

FetchContent_Declare(
        tinyobj
        GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader
        GIT_TAG master
)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG master
        GIT_PROGRESS ON
)
option(BUILD_TESTING "" OFF)


FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad
        GIT_TAG master
        GIT_PROGRESS ON
)
set(GLAD_API "gl=3.3" CACHE STRING "" FORCE)
option(GLAD_INSTALL "" ON)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG ${GLFW_COMMIT_TAG}
        GIT_PROGRESS ON
)
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)


FetchContent_Declare(
        stb-cmake
        GIT_REPOSITORY https://gitlab.cse.unsw.edu.au/COMP3421/stb-cmake-package
        GIT_TAG master
        GIT_PROGRESS ON
)

# GLM is a piece of s***
if (NOT glm_POPULATED)
    FetchContent_Populate(glm)

    file(STRINGS ${glm_SOURCE_DIR}/CMakeLists.txt BUILD_SYS_LINES)
    list(FILTER BUILD_SYS_LINES EXCLUDE REGEX "CMAKE_SOURCE_DIR.*STREQUAL.*CMAKE_CURRENT_SOURCE_DIR")
    list(JOIN BUILD_SYS_LINES "\n" NEW_BUILD_SYS)
    file(WRITE ${glm_SOURCE_DIR}/CMakeLists.txt ${NEW_BUILD_SYS})

    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()

FetchContent_MakeAvailable(tinyobj glad glfw stb-cmake)
