#include "rendering.hpp"
#include <iostream>
#include <vulkan/vulkan.h>
#include <vector>

VulkanRenderer::VulkanRenderer(SDL_Window *window) : window(window) {}

VulkanRenderer::~VulkanRenderer()
{
    cleanupVulkan();
}

VkInstance VulkanRenderer::createInstance()
{
    // Application information
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VulkanRenderer";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3; // Or a compatible version

    // Create instance
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Enable validation layers (optional, for debugging)
#ifdef NDEBUG
    const uint32_t validationLayerCount = 0;
#else
    const char *validationLayers[] = {"VK_LAYER_KHRONOS_validation"};
    const uint32_t validationLayerCount = 1;
    // Corrected member name
    createInfo.ppEnabledLayerNames = validationLayers; // Use ppEnabledLayerNames
#endif

    // Required extensions for Vulkan and SDL (SDL_vulkan.h usually defines these)
    const char *requiredExtensions[] = {VK_KHR_SURFACE_EXTENSION_NAME};
    createInfo.enabledExtensionCount = sizeof(requiredExtensions) / sizeof(requiredExtensions[0]);
    createInfo.ppEnabledExtensionNames = requiredExtensions;

    VkInstance instance;
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if (result != VK_SUCCESS)
    {
        std::cerr << "Failed to create Vulkan instance: " << result << std::endl;
        return VK_NULL_HANDLE; // Or throw an exception (depending on your error handling strategy)
    }

    return instance;
}

// VkPhysicalDevice VulkanRenderer::selectPhysicalDevice(const VkInstance vulkanInstance)
// {
//     // 1. Enumerate available physical devices
//     uint32_t deviceCount = 0;
//     vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, nullptr);
//     if (deviceCount == 0)
//     {
//         // Handle case where no physical devices are found
//         return VK_NULL_HANDLE;
//     }

//     // 2. Allocate space for device handles
//     std::vector<VkPhysicalDevice> devices(deviceCount);
//     vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, devices.data());

//     // 3. Select a suitable physical device
//     for (const auto &device : devices)
//     {
//         // Check if the device supports VK_QUEUE_GRAPHICS_BIT for graphics operations
//         VkPhysicalDeviceProperties deviceProperties = {};
//         vkGetPhysicalDeviceProperties(device, &deviceProperties);
//         if (!(deviceProperties.deviceType & VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU))
//         {
//             continue; // Skip devices without graphics support
//         }

//         // Check for queue families that support graphics and optionally presentation
//         uint32_t queueFamilyCount = 0;
//         vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
//         std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
//         vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

//         bool foundGraphicsFamily = false;
//         uint32_t graphicsFamilyIndex = -1;
//         bool foundPresentFamily(VK_EXT_SWAPCHAIN_SUPPORT_KHR); // Optional for presentation

//         for (uint32_t i = 0; i < queueFamilyCount; i++)
//         {
//             if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
//             {
//                 foundGraphicsFamily = true;
//                 graphicsFamilyIndex = i;
//             }

//             // Check for presentation support if extension is available
//             VkBool32 presentSupport = VK_FALSE;
//             vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport); // Replace 'surface' with your actual surface handle if using swapchain
//             if (presentSupport && !foundPresentFamily)
//             {
//                 foundPresentFamily = true;
//             }
//         }

//         // Select this device if it has graphics support and optionally presentation support
//         if (foundGraphicsFamily && (foundPresentFamily || !VK_EXT_SWAPCHAIN_SUPPORT_KHR))
//         {
//             return device;
//         }
//     }

//     // No suitable device found
//     return VK_NULL_HANDLE;
// }

// VkDevice VulkanRenderer::createDevice(const VkInstance vulkanInstance)
// {
//     // 1. Select a physical device (consider using a separate function)
//     VkPhysicalDevice physicalDevice = selectPhysicalDevice(vulkanInstance);
//     if (physicalDevice == VK_NULL_HANDLE)
//     {
//         // Handle case where no suitable physical device is found
//         return VK_NULL_HANDLE;
//     }

//     // 2. Gather device queue family information
//     uint32_t queueFamilyCount = 0;
//     vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
//     std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
//     vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

//     // 3. Determine queue family indices for graphics and presentation (placeholder logic)
//     uint32_t graphicsFamilyIndex = -1;
//     uint32_t presentFamilyIndex = -1;
//     // Implement logic to find suitable queue families based on their capabilities
//     // (consider using a separate function)

//     // 4. Specify device creation info
//     VkDeviceCreateInfo deviceCreateInfo = {};
//     deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

//     // Required extensions (consider adding extensions your application needs)
//     const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
//     deviceCreateInfo.enabledExtensionCount = deviceExtensions.size();
//     deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

//     // Queue family information
//     std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
//     float queuePriority = 1.0f; // Adjust queue priority as needed

//     // Add queue creation info for graphics queue (replace placeholder logic)
//     if (graphicsFamilyIndex != -1)
//     {
//         VkDeviceQueueCreateInfo queueCreateInfo = {};
//         queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//         queueCreateInfo.queueFamilyIndex = graphicsFamilyIndex;
//         queueCreateInfo.queueCount = 1; // Request 1 queue from the graphics family
//         queueCreateInfo.pQueuePriorities = &queuePriority;
//         queueCreateInfos.push_back(queueCreateInfo);
//     }

//     // Optionally add queue creation info for presentation queue (replace placeholder logic)
//     if (presentFamilyIndex != -1 && presentFamilyIndex != graphicsFamilyIndex)
//     {
//         VkDeviceQueueCreateInfo queueCreateInfo = {};
//         queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//         queueCreateInfo.queueFamilyIndex = presentFamilyIndex;
//         queueCreateInfo.queueCount = 1; // Request 1 queue from the presentation family
//         queueCreateInfo.pQueuePriorities = &queuePriority;
//         queueCreateInfos.push_back(queueCreateInfo);
//     }

//     deviceCreateInfo.queueCreateInfoCount = queueCreateInfos.size();
//     deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();

//     // 5. Create the logical device
//     VkDevice device;
//     VkResult result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);
//     if (result != VK_SUCCESS)
//     {
//         // Handle device creation failure
//         return VK_NULL_HANDLE;
//     }

//     // Successfully created the device
//     return device;
// }

void VulkanRenderer::printInstanceInfoInConsole(const VkInstance vulkanInstance)
{
    // Enumerate physical devices
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, nullptr); // Get count first

    if (deviceCount == 0)
    {
        std::cerr << "No physical devices found!" << std::endl;
        return;
    }

    // Allocate array for device handles (using std::vector for flexibility)
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, devices.data()); // Get device handles

    // Print device information
    std::cout << "Found " << deviceCount << " physical devices:" << std::endl;
    for (size_t i = 0; i < devices.size(); i++)
    {
        VkPhysicalDevice device = devices[i];

        // Get device properties
        VkPhysicalDeviceProperties deviceProperties = {};
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        // Print device name
        std::cout << "\tDevice " << i + 1 << ": " << deviceProperties.deviceName << std::endl;

        // Get device memory information
        VkPhysicalDeviceMemoryProperties memoryProperties = {};
        vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);

        // Print some memory details (adjust as needed)
        std::cout << "\t  Memory Heaps (" << memoryProperties.memoryHeapCount << "):" << std::endl;
        for (uint32_t j = 0; j < memoryProperties.memoryHeapCount; j++)
        {
            VkMemoryHeap memoryHeap = memoryProperties.memoryHeaps[j];
            std::cout << "\t\t  Heap " << j + 1 << ": Size " << memoryHeap.size << " Bytes" << std::endl;
        }

        // Print some memory details (adjust as needed)
        std::cout << "\t  Memory Types (" << memoryProperties.memoryTypeCount << "):" << std::endl;
        for (uint32_t j = 0; j < memoryProperties.memoryTypeCount; j++)
        {
            if (memoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
            {
                std::cout << "\t\t  Type " << j + 1 << ": Device Local" << std::endl;
            }
            if (memoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
            {
                std::cout << "\t\t  Type " << j + 1 << ": Host Visible" << std::endl;
            }
        }

        // Get device queue family information
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr); // Get count first
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        // Print some queue family details
        std::cout << "\t  Queue Families (" << queueFamilyCount << "):" << std::endl;
        for (uint32_t j = 0; j < queueFamilyCount; j++)
        {
            VkQueueFamilyProperties queueFamily = queueFamilies[j];
            std::cout << "\t\t  - Queue Family " << j << ":" << std::endl;
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                std::cout << "\t\t\t    Supports graphics operations" << std::endl;
            }
            if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
            {
                std::cout << "\t\t\t    Supports compute operations" << std::endl;
            }
            if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                std::cout << "\t\t\t    Supports transfer operations" << std::endl;
            }
            std::cout << "\t\t\t    Queue Count: " << queueFamily.queueCount << std::endl;
        }
    }
}

void VulkanRenderer::cleanupVulkan()
{
    // Implement Vulkan resource cleanup logic here (placeholder for now)
    if (device)
    {
        vkDestroyDevice(device, nullptr);
    }
    if (instance)
    {
        vkDestroyInstance(instance, nullptr);
    }
}