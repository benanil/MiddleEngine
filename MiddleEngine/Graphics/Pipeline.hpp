#pragma once
#include "VulkanBackend.hpp"
#include "../Common.hpp"

namespace MiddleEngine
{
    namespace Pipeline
    {
        VkShaderModule CreateShaderModule(const std::string& path, const VkDevice& device);
    
        /// <summary> creates vertex-fragment pipeline </summary>
        /// <param name="vertexBindingDescriptions"> Vertex::getBindingDescription </param>
        /// <param name="attributeDescriptions"> Vertex::getattributeDescriptions </param>
        void CreateGraphicsPipeline(
            const VkExtent2D& swapchainExtent,
            const char* vertexPath, const char* fragmentPath,
            const VkVertexInputBindingDescription* vertexBindingDescriptions,     
            const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions,
            const VkDescriptorSetLayout& descriptorSetLayout,
            const VkRenderPass& renderPass,
            VkPipelineLayout& pipelineLayout,
            VkPipeline& graphicsPipeline
        );
    }
}

