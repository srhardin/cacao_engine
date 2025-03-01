#pragma once

#include "CommonIncludes.h"
#include "Defines.h"

static std::vector<char> readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        std::string errorMessage = "failed to open file: " + filename;
        throw std::runtime_error(errorMessage);
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    // go to the start of the file
    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

static void VerifyResult(VkResult result, std::string type)
{
    if (result != VK_SUCCESS)
    {
        std::string message = "Error at graphics step: " + type;
        throw std::runtime_error(message);
    }
#ifdef VERBOSE_LOGS
    else
    {
        std::cout << "Completed step: " << type << std::endl;
    }
#endif
}