#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError()
                  << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Window* window =
        SDL_CreateWindow("SDLVulk Test", 800, 600, SDL_WINDOW_VULKAN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Vulkan";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    uint32_t extensionCount = 0;
    if (!SDL_Vulkan_GetInstanceExtensions(&extensionCount)) {
        std::cerr << "Failed to get Vulkan instance extensions: "
                  << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    std::vector<const char*> extensions(extensionCount);
    if (!SDL_Vulkan_GetInstanceExtensions(&extensionCount)) {
        std::cerr << "Failed to get Vulkan instance extensions: "
                  << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkInstance instance;
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        std::cerr << "Failed to create Vulkan instance!" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    VkAllocationCallbacks allocator = {};

    VkSurfaceKHR surface;
    if (!SDL_Vulkan_CreateSurface(window, instance, &allocator, &surface)) {
        std::cerr << "Failed to create Vulkan surface: " << SDL_GetError()
                  << std::endl;
        vkDestroyInstance(instance, nullptr);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // TODO: Add your Vulkan rendering code here.
    // TODO: Add your Vulkan rendering code here.
    // Define vertex data for a white square.
    float vertices[] = {
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  // Bottom-left
        0.5f,  -0.5f, 1.0f, 1.0f, 1.0f,  // Bottom-right
        0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // Top-right
        -0.5f, 0.5f,  1.0f, 1.0f, 1.0f   // Top-left
    };

    // Create a vertex buffer and copy the vertex data to it.

    // Create a graphics pipeline.

    // Create a command buffer.

    // Start recording commands to the command buffer.

    // Bind the graphics pipeline.

    // Bind the vertex buffer.

    // Draw the square.

    // End recording commands to the command buffer.

    // Submit the command buffer to a queue for execution.

    // Wait for the queue to finish executing the command buffer.

    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
