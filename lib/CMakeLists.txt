# GLFW
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(glfw)

# GLAD
set(GLAD_API "gl=3.3")
add_subdirectory(glad)

# GLM
add_subdirectory(glm)

# STB required.... extra work
add_subdirectory(stb)