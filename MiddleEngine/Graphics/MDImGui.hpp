#pragma once
#include "VulkanMemory.hpp"
#include "../Imgui/imgui.h"
#include "VulkanBuffer.hpp"
#include "VulkanHelper.hpp"
#include "MDDevice.hpp"

MD_NAMESPACE_START

// ----------------------------------------------------------------------------
// ImGUI 
// ----------------------------------------------------------------------------
namespace MDImGui
{
	
	void Clean();

	// Initialize styles, keys, etc.
	void init(MDDevice* _device, float width, float height);

	// Initialize all Vulkan resources used by the ui
	void initResources(VkRenderPass renderPass, VkQueue copyQueue);

	// Starts a new imGui frame and sets up windows and ui elements
	void newFrame(bool updateFrameGraph);

	// Update vertex and index buffer containing the imGui elements when required
	void updateBuffers();

	// Draw current imGui frame into a command buffer
	void drawFrame(VkCommandBuffer commandBuffer);

};

MD_NAMESPACE_END