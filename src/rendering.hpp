#pragma once

#include <vulkan/vulkan.h>
#include <SDL3/SDL.h>
// #include <glm/glm.hpp>

class VulkanRenderer
{
public:
    VulkanRenderer(SDL_Window *window);
    ~VulkanRenderer();

    bool createInstance();
    bool createDevice();

private:
    SDL_Window *window;
    VkInstance instance;
    VkDevice device;

    void cleanupVulkan();
};