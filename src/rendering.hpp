#pragma once

#include <vulkan/vulkan.h>

struct VkVertex
{
    // Define vertex data structure (e.g., position, color)
    glm::vec2 pos;
    glm::vec3 color;
};

class VulkanRenderer
{
public:
    VulkanRenderer(SDL_Window *window);
    ~VulkanRenderer();

    bool createInstance();
    bool createDevice();
    // ... Function declarations for creating resources
    bool createSwapchain(SDL_Window *window);
    // ...

    bool recordCommandBuffer(VkCommandBuffer commandBuffer);
    void renderFrame();

private:
    // Member variable and function declarations
    SDL_Window *window;
    // ...

    // Function declarations for internal cleanup
    void cleanupVulkan();
};