find_package(Vulkan REQUIRED)

add_subdirectory(sdl)
add_subdirectory(glm)

add_library(external INTERFACE)

target_link_libraries(external
    INTERFACE SDL3::SDL3
    INTERFACE Vulkan::Vulkan
    INTERFACE glm::glm
)