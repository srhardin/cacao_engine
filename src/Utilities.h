#pragma once

#include "CommonIncludes.h"

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