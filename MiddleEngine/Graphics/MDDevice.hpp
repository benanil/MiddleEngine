#pragma once
#include "VulkanHelper.hpp"
#include "VulkanBuffer.hpp"

MD_NAMESPACE_START


struct MDDevice
{
	VkPhysicalDevice physicalDevice;
	VkDevice logicalDevice;
	VkResult createBuffer(VkBufferUsageFlags usageFlags, 
		VkMemoryPropertyFlags memoryPropertyFlags, 
		VkDeviceSize size, 
		VkBuffer* buffer, 
		VkDeviceMemory* memory, 
		void* data = VK_NULL_HANDLE);
	
	VkResult createBuffer(
		VkBufferUsageFlags usageFlags,
		VkMemoryPropertyFlags memoryPropertyFlags,
		vks::Buffer* buffer,
		VkDeviceSize size,
		void* data = VK_NULL_HANDLE);
};

MD_NAMESPACE_END