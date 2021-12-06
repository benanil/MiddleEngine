#include "Pipeline.hpp"
#include <fstream>
#include "../MiddleEngine.hpp"
#include "VulkanMemory.hpp"
#include "VulkanHelper.hpp"

namespace Rendering
{

    static std::vector<char> readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary | std::ios::failbit);

        if (!file.is_open() || file.fail()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    VkShaderModule Pipeline::CreateShaderModule(const std::string& path, const VkDevice& device)
    {
        auto code = readFile(path);

        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
    
        VkShaderModule shaderModule;
        if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module!");
        }
    
        return shaderModule;
    }

    void Pipeline::CreateGraphicsPipeline(
        const VkExtent2D& swapchainExtent,
        const char* vertexPath, const char* fragmentPath,
        const VkVertexInputBindingDescription* vertexBindingDescriptions,     // Vertex::getBindingDescription
        const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions,// Vertex::getattributeDescriptions
        const VkDescriptorSetLayout& descriptorSetLayout,
        const VkRenderPass& renderPass,
        VkPipelineLayout& pipelineLayout,
        VkPipeline& graphicsPipeline
        ) {

        const VkDevice& device = VulkanBackend::GetDevice();

        VkShaderModule vertShaderModule = CreateShaderModule(MD_ASSETS_PATH(vertexPath)  , device);
        VkShaderModule fragShaderModule = CreateShaderModule(MD_ASSETS_PATH(fragmentPath), device);

        VkPipelineShaderStageCreateInfo vertShaderStageInfo{
            VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            nullptr, 0, VK_SHADER_STAGE_VERTEX_BIT, vertShaderModule, "main"
        };

        VkPipelineShaderStageCreateInfo fragShaderStageInfo{
            VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            nullptr, 0, VK_SHADER_STAGE_FRAGMENT_BIT, fragShaderModule, "main"
        };

        VkPipelineShaderStageCreateInfo shaderStages[]{ vertShaderStageInfo, fragShaderStageInfo };

        VkPipelineVertexInputStateCreateInfo vertexInputInfo{};

        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
        vertexInputInfo.pVertexBindingDescriptions = vertexBindingDescriptions;
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

        VkPipelineInputAssemblyStateCreateInfo inputAssembly{
            VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO, nullptr, 0,
            VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
            VK_FALSE // primitive RestartEnable
        };

        VkViewport viewport{
            0, 0, // x-y
            (float)swapchainExtent.width, (float)swapchainExtent.height ,
            0.0f, 1.0f // min-max depth
        };

        VkRect2D scissor{ { 0, 0 } , swapchainExtent };

        VkPipelineViewportStateCreateInfo viewportState{
            VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, nullptr, 0,
            1, &viewport,
            1, &scissor
        };

        VkPipelineRasterizationStateCreateInfo rasterizer{
            VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO, nullptr, 0,
            VK_FALSE, // depthClamp Enable 
            VK_FALSE, // rasterizer Discard Enable
            VK_POLYGON_MODE_FILL, // polygonMode
            VK_CULL_MODE_BACK_BIT, // cullMode
            // VK_CULL_MODE_FRONT_AND_BACK,
            // VK_CULL_MODE_FRONT_BIT,
            VK_FRONT_FACE_COUNTER_CLOCKWISE,
            VK_FALSE, // depthBiasEnable
            0, 0, 0, 1
        };
        
        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_TRUE;
        multisampling.rasterizationSamples = getMaxUsableSampleCount();
        multisampling.minSampleShading = .2f;

        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

        VkPipelineDepthStencilStateCreateInfo depthStencil{};
        depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencil.depthTestEnable = VK_TRUE;
        depthStencil.depthWriteEnable = VK_TRUE;
        depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
        depthStencil.depthBoundsTestEnable = VK_FALSE;
        depthStencil.stencilTestEnable = VK_FALSE;

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 1;
        pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
        pipelineLayoutInfo.pushConstantRangeCount = 0;

        if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("PipelineLayout creation failed");
        }

        VkGraphicsPipelineCreateInfo pipelineInfo{
            VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO, nullptr, 0,
            2, shaderStages, // shader stages
            &vertexInputInfo,
            &inputAssembly,
            nullptr, // tesselation state
            &viewportState,
            &rasterizer,
            &multisampling,
            &depthStencil, // depth stencil state
            &colorBlending,
            nullptr, // dynamic state
            pipelineLayout,
            renderPass,
            0, // subpass
            VK_NULL_HANDLE // basePipelineHandle
        };

        if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
            throw std::runtime_error("GraphicsPipelines creation failed");
        }

        vkDestroyShaderModule(device, fragShaderModule, nullptr);
        vkDestroyShaderModule(device, vertShaderModule, nullptr);
    }
}