#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include <vector>

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
    const std::string appName = "Fluffy Butter";

    GLFWwindow* window;
    VkInstance instance;

    VkDevice device;
    VkDebugUtilsMessengerEXT debugMessenger;


    ///////////////////////////////////////////////////////////////
    // Methods

    // GLFW / Window
    void InitWindow();
    void MainLoop();
    void Cleanup();

    // Vulkan
    void InitVulkan();
    void CreateInstance();
    bool CheckValidationLayerSupport();
    std::vector<const char*> GetRequiredExtensions();

    // Debug
    void SetupDebugMessenger();
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