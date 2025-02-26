#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <optional>
#include <cstdint>
#include <limits>
#include <algorithm>

// Data structures
#include <vector>
#include <map>
#include <set>

// The current control mechanism for the initialization logs. This may change
// in future versions, probably to a cmd line launcher arg
#define VERBOSE_LOGS

class BaseApplication
{
public:
    void Run();

private:
    ///////////////////////////////////////////////////////////////
    // Variables

    // Consts
    const std::vector<const char*> validationLayers = 
    {
        "VK_LAYER_KHRONOS_validation"
    };

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif
    const std::string appName = "Cacao Engine";

    GLFWwindow* window;
    VkInstance instance;

    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;
    
    // SwapChain
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainFormat;
    VkExtent2D swapChainExtent;

    VkPhysicalDevice physicalDevice;
    VkDebugUtilsMessengerEXT debugMessenger;

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool IsComplete()
        {
            return graphicsFamily.has_value();
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };


    ///////////////////////////////////////////////////////////////
    // Methods

    // GLFW / Window
    void InitWindow();
    void MainLoop();
    void Cleanup();

    // Surface | WSI
    void CreateSurface();

    // Vulkan
    void InitVulkan();
    void CreateInstance();
    std::vector<const char*> GetRequiredExtensions();
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    // SwapChain | SwapSurface
    void CreateSwapChain();
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    // Physical Device
    void PickPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    bool RateDeviceSuitability(VkPhysicalDevice device);
        // Queue
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

    // Logical Device
    void CreateLogicalDevice();

    // Debug
    void SetupDebugMessenger();
    bool CheckValidationLayerSupport();
    VkResult CreateDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
                                        const VkAllocationCallbacks* pAllocator, 
                                        VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(const VkAllocationCallbacks* pAllocator);

    static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);
};