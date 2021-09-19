include(FetchContent)

FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp
        GIT_TAG origin/master
        GIT_PROGRESS ON
)
#option(BUILD_SHARED_LIBS "" OFF)
#option(ASSIMP_BUILD_ASSIMP_TOOLS "" OFF)
#option(ASSIMP_BUILD_TESTS "" OFF)
option(ASSIMP_BUILD_ZLIB "" ON)

#FetchContent_Declare(
#        glm
#        GIT_REPOSITORY https://github.com/g-truc/glm
#        GIT_TAG master
#        GIT_PROGRESS ON
#)
#option(BUILD_TESTING "" OFF)


FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad
        GIT_TAG master
        GIT_PROGRESS ON
)
set(GLAD_API gl=3.3)
option(GLAD_INSTALL "" ON)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG master
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

FetchContent_MakeAvailable(assimp glad glfw  stb-cmake)