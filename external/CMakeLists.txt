add_subdirectory(vulkan-headers)
add_subdirectory(sdl)

add_library(external INTERFACE)

target_link_libraries(external INTERFACE Vulkan::Headers SDL3::SDL3)