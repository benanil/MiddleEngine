#pragma once
#include "VulkanInitializers.hpp"
#include "VulkanBackend.hpp"
#include "../Common.hpp"

MD_NAMESPACE_START

typedef enum MDBufferCreateFlagBits
{
    MD_BUFFER_NONE_BIT = 0x00000000,
    MD_MAP_BIT  = 0x00000001,
    MD_IMAGE_BIT = 0x00000002
} MDBufferCreateFlagBits;
typedef VkFlags MDBufferCreateFlags;

struct MDBuffer
{
    VkBuffer buffer;
    VkDeviceMemory memory;
    void* mapped = nullptr;
    
    void Flush(size_t size) const
    {
        VkMappedMemoryRange memoryRange = vks::initializers::mappedMemoryRange();
        memoryRange.memory = memory;
        memoryRange.size = size;
        vkFlushMappedMemoryRanges(VulkanBackend::GetDevice(), 1, &memoryRange);
    }

    void Dispose(const VkDevice& device) const
    {
        vkDestroyBuffer(device, buffer, nullptr);
        vkFreeMemory(device, memory, nullptr);
    }
};

struct MDImage
{
    VkImage image;
    VkImageView imageView;
    VkDeviceMemory memory;
    uint32_t width, height;
    
    void Dispose(const VkDevice& device)
    {
        vkDestroyImage(device, image, nullptr);
        vkDestroyImageView(device, imageView, nullptr);
        vkFreeMemory(device, memory, nullptr);
    }
};

struct MDTexture
{
    MDBuffer buffer;
    VkImage image;
    VkImageView imageView;
    VkSampler sampler;
    int32_t width, height;

    void Dispose(const VkDevice& device)
    {
        buffer.Dispose(device);
        vkDestroyImage(device, image, nullptr);
        vkDestroyImageView(device, imageView, nullptr);
        vkDestroySampler(device, sampler, nullptr);
    }
};

namespace VulkanMemory
{

    void Init(
        const VkPhysicalDevice& _physicalDevice, 
        const VkDevice& _device,
        const VkInstance& _instance, 
        const VkCommandPool& commandPool,
        const VkQueue& _graphicsQueue);

    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(const VkCommandBuffer& commandBuffer);

    // TEXTURE
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels = 1 );
    void copyBufferToImage(VkBuffer buffer, MDTexture& texture);

    VkImageView createImageView(VkImage image, VkFormat format, 
        VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT,
        uint32_t mipLevels = 1);

    VkImageView createImageView(VkDevice _device, VkImage image, VkFormat format,
        VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT, 
        uint32_t mipLevels = 1);

    void createImage(
        MDImage& mdImage,
        VkFormat format,
        VkImageTiling tiling,
        VkImageUsageFlags usage,
        VkMemoryPropertyFlags properties,
        uint32_t mipLevels = 1,
        VkSampleCountFlagBits numSample = VK_SAMPLE_COUNT_1_BIT);

    MDTexture CreateTexture(
        const char** filePath,
        bool createMipmap = true,
        VkFilter minFilter = VK_FILTER_LINEAR,
        VkFilter magFilter = VK_FILTER_LINEAR,
        VkSamplerAddressMode addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        VkSamplerAddressMode addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT);

    // BUFFER
    void copyBuffer(const MDBuffer& srcBuffer, const MDBuffer& dstBuffer, VkDeviceSize size);

    void CreateBuffer(
        const void* vertices, 
        VkDeviceSize bufferSize,
        VkBufferUsageFlags usage, 
        VkMemoryPropertyFlags properties, 
        MDBufferCreateFlags flags,
        MDBuffer& result);

    /// <summary> creates and maps the buffer </summary>
    template<typename T>
    void CreateBuffer(T& vertices, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, MDBuffer& result)
    {
        CreateBuffer(vertices.data(), vertices.size() * sizeof(T), usage, properties, MD_MAP_BIT, result);
    }

    template<typename T>
    void CreateBuffer(
        const std::vector<T>& vertices,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        MDBuffer& result)
    {
        CreateBuffer(vertices.data(), vertices.size() * sizeof(T), usage, properties, MD_MAP_BIT, result);
    }

    template<typename T, typename size_t size>
    void CreateBuffer(
        const std::array<T, size>& vertices,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        MDBuffer& result)
    {
        CreateBuffer(vertices.data(), vertices.size() * sizeof(T), usage, properties, MD_MAP_BIT, result);
    }

}

MD_NAMESPACE_END

