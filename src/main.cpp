#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError()
                  << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Window *window =
        SDL_CreateWindow("SDLVulk Test", 800, 600,
                         // SDL_WindowFlags::SDL_WINDOW_RESIZABLE |
                         SDL_WindowFlags::SDL_WINDOW_VULKAN);
    if (!window)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, NULL, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError()
                  << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // VkApplicationInfo appInfo{};
    // appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    // appInfo.pApplicationName = "Hello Vulkan";
    // appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    // appInfo.pEngineName = "No Engine";
    // appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    // appInfo.apiVersion = VK_API_VERSION_1_0;

    // uint32_t extensionCount = 0;
    // std::vector<const char *> extensions(extensionCount);
    // if (!SDL_Vulkan_GetInstanceExtensions(&extensionCount))
    // {
    //     std::cerr << "Failed to get Vulkan instance extensions: "
    //               << SDL_GetError() << std::endl;
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return EXIT_FAILURE;
    // }

    // VkInstanceCreateInfo createInfo{};
    // createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    // createInfo.pApplicationInfo = &appInfo;
    // createInfo.enabledExtensionCount = extensionCount;
    // createInfo.ppEnabledExtensionNames = extensions.data();

    // VkInstance instance;
    // if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    // {
    //     std::cerr << "Failed to create Vulkan instance!" << std::endl;
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return EXIT_FAILURE;
    // }

    // VkAllocationCallbacks allocator = {};

    // VkSurfaceKHR surface;
    // if (!SDL_Vulkan_CreateSurface(window, instance, &allocator, &surface))
    // {
    //     std::cerr << "Failed to create Vulkan surface: " << SDL_GetError()
    //               << std::endl;
    //     vkDestroyInstance(instance, nullptr);
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return EXIT_FAILURE;
    // }

    // float vertices[] = {
    //     -0.5f, -0.5f, 1.0f,
    //     0.5f, -0.5f, 1.0f,
    //     0.5f, 0.5f, 1.0f,
    //     -0.5f, 0.5f, 1.0f};

    // vkDestroySurfaceKHR(instance, surface, nullptr);
    // vkDestroyInstance(instance, nullptr);

    SDL_Event event;
    bool m_running = true;
    while (m_running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                m_running = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                auto keysympressed = event.key.keysym.sym;
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    m_running = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}