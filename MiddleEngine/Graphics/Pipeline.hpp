#pragma once
#include "VulkanBackend.hpp"
#include "../Common.hpp"

namespace Rendering
{
    namespace Pipeline
    {
        VkShaderModule CreateShaderModule(const std::string& path, const VkDevice& device);
    
        void CreateGraphicsPipeline(
            const VkExtent2D& swapchainExtent,
            const char* vertexPath, const char* fragmentPath,
            const VkVertexInputBindingDescription* vertexBindingDescriptions,     // Vertex::getBindingDescription
            const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions,// Vertex::getattributeDescriptions
            const VkDescriptorSetLayout& descriptorSetLayout,
            const VkRenderPass& renderPass,
            VkPipelineLayout& pipelineLayout,
            VkPipeline& graphicsPipeline
        );
    }
}

