
#include <vulkan/vulkan.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <iostream>
#include <vector>

#include "rendering.hpp"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_InitFlags::SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError()
                  << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Window *window =
        SDL_CreateWindow("SDLVulk Test", 800, 600, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    VulkanRenderer vulkanRenderer(window);
    VkInstance vulkanInstance = vulkanRenderer.createInstance();
    vulkanRenderer.printInstanceInfoInConsole(vulkanInstance);

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
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}