#pragma once
#include "../MiddleEngine.hpp"

#define MD_DEFAULT_BUFFER_PROPERTIES VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
};


struct MDBuffer
{
    VkBuffer buffer;
    VkDeviceMemory memory;
    void Dispose(const VkDevice& device) const
    {
        vkDestroyBuffer(device, buffer, nullptr);
        vkFreeMemory(device, memory, nullptr);
    }
};

struct MDTexture
{
    MDBuffer buffer;
    VkImage image;
    VkImageView imageView;
    VkSampler sampler;
    int width, height;

    void Dispose(const VkDevice& device)
    {
        buffer.Dispose(device);
        vkDestroyImage(device, image, nullptr);
        vkDestroyImageView(device, imageView, nullptr);
        vkDestroySampler(device, sampler, nullptr);
    }
};

typedef enum MDBufferCreateFlagBits
{
    MD_NONE_BIT = 0x00000000,
    MD_MAP_BIT  = 0x00000001,
    MD_IMAGE_BIT = 0x00000002
} MDBufferCreateFlagBits;
typedef VkFlags MDBufferCreateFlags;

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
    VkImageView createImageView(VkDevice _device, VkImage image, VkFormat format);
    VkImageView createImageView(VkImage image, VkFormat format);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, MDTexture& texture);
    
    MDTexture CreateTexture(
        const char* filePath,
        VkFilter minFilter = VK_FILTER_NEAREST,
        VkFilter magFilter = VK_FILTER_NEAREST,
        VkSamplerAddressMode addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        VkSamplerAddressMode addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT);

    // BUFFER
    void copyBuffer(const MDBuffer& srcBuffer, const MDBuffer& dstBuffer, VkDeviceSize size);

    void CreateBuffer(
        const void* vertices, 
        VkDeviceSize vertexCount, 
        VkDeviceSize stride, 
        VkBufferUsageFlags usage, 
        VkMemoryPropertyFlags properties, 
        MDBufferCreateFlags flags,
        MDBuffer& result);
    
    template<typename T>
    void CreateBuffer(
        const std::vector<T>& vertices,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        MDBuffer& result)
    {
        CreateBuffer(vertices.data(), vertices.size(), sizeof(T), usage, properties, MD_MAP_BIT, result);
    }
    
    template<typename T, typename size_t size>
    void CreateBuffer(
        const std::array<T, size>& vertices,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        MDBuffer& result)
    {
        CreateBuffer(vertices.data(), vertices.size(), sizeof(T), usage, properties, MD_MAP_BIT, result);
    }

}