# GLFW
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(glfw)

# GLAD
add_subdirectory(glad)

# GLM
add_subdirectory(glm)

# STB requires.... extra work
add_subdirectory(stb)