#include "VulkanLoader.hpp"

// Exported functions
KDS_DECL(vkGetInstanceProcAddr);

// Global level functions
KDS_DECL(vkCreateInstance);
KDS_DECL(vkEnumerateInstanceExtensionProperties);
KDS_DECL(vkEnumerateInstanceLayerProperties);

// Instance level functions
KDS_DECL(vkEnumeratePhysicalDevices);
KDS_DECL(vkEnumerateDeviceExtensionProperties);
KDS_DECL(vkGetPhysicalDeviceProperties);
KDS_DECL(vkGetPhysicalDeviceFeatures);
KDS_DECL(vkGetPhysicalDeviceQueueFamilyProperties);
KDS_DECL(vkCreateDevice);
KDS_DECL(vkGetDeviceProcAddr);
KDS_DECL(vkDestroyInstance);
KDS_DECL(vkCreateDebugReportCallbackEXT);
KDS_DECL(vkDestroyDebugReportCallbackEXT);
#ifdef KDS_OS_LINUX
KDS_DECL(vkCreateXcbSurfaceKHR);
#elif defined(KDS_OS_WINDOWS)
KDS_DECL(vkCreateWin32SurfaceKHR);
#endif

// Device level functions
KDS_DECL(vkDestroyDevice);
KDS_DECL(vkGetDeviceQueue);
KDS_DECL(vkQueueSubmit);
KDS_DECL(vkQueueWaitIdle);
KDS_DECL(vkDeviceWaitIdle);
KDS_DECL(vkAllocateMemory);
KDS_DECL(vkFreeMemory);
KDS_DECL(vkMapMemory);
KDS_DECL(vkUnmapMemory);
KDS_DECL(vkFlushMappedMemoryRanges);
KDS_DECL(vkInvalidateMappedMemoryRanges);
KDS_DECL(vkGetDeviceMemoryCommitment);
KDS_DECL(vkBindBufferMemory);
KDS_DECL(vkBindImageMemory);
KDS_DECL(vkGetBufferMemoryRequirements);
KDS_DECL(vkGetImageMemoryRequirements);
KDS_DECL(vkGetImageSparseMemoryRequirements);
KDS_DECL(vkGetPhysicalDeviceSparseImageFormatProperties);
KDS_DECL(vkQueueBindSparse);
KDS_DECL(vkCreateFence);
KDS_DECL(vkDestroyFence);
KDS_DECL(vkResetFences);
KDS_DECL(vkGetFenceStatus);
KDS_DECL(vkWaitForFences);
KDS_DECL(vkCreateSemaphore);
KDS_DECL(vkDestroySemaphore);
KDS_DECL(vkCreateEvent);
KDS_DECL(vkDestroyEvent);
KDS_DECL(vkGetEventStatus);
KDS_DECL(vkSetEvent);
KDS_DECL(vkResetEvent);
KDS_DECL(vkCreateQueryPool);
KDS_DECL(vkDestroyQueryPool);
KDS_DECL(vkGetQueryPoolResults);
KDS_DECL(vkCreateBuffer);
KDS_DECL(vkDestroyBuffer);
KDS_DECL(vkDestroyBufferView);
KDS_DECL(vkCreateImage);
KDS_DECL(vkDestroyImage);
KDS_DECL(vkGetImageSubresourceLayout);
KDS_DECL(vkCreateImageView);
KDS_DECL(vkDestroyImageView);
KDS_DECL(vkCreateShaderModule);
KDS_DECL(vkDestroyShaderModule);
KDS_DECL(vkCreatePipelineCache);
KDS_DECL(vkDestroyPipelineCache);
KDS_DECL(vkDestroyPipelineLayout);
KDS_DECL(vkGetPipelineCacheData);
KDS_DECL(vkMergePipelineCaches);
KDS_DECL(vkCreateGraphicsPipelines);
KDS_DECL(vkCreateComputePipelines);
KDS_DECL(vkDestroyPipeline);
KDS_DECL(vkCreatePipelineLayout);
KDS_DECL(vkCreateSampler);
KDS_DECL(vkDestroySampler);
KDS_DECL(vkCreateDescriptorSetLayout);
KDS_DECL(vkCreateDescriptorPool);
KDS_DECL(vkDestroyDescriptorPool);
KDS_DECL(vkResetDescriptorPool);
KDS_DECL(vkAllocateDescriptorSets);
KDS_DECL(vkFreeDescriptorSets);
KDS_DECL(vkUpdateDescriptorSets);
KDS_DECL(vkCreateFramebuffer);
KDS_DECL(vkDestroyFramebuffer);
KDS_DECL(vkCreateRenderPass);
KDS_DECL(vkDestroyRenderPass);
KDS_DECL(vkGetRenderAreaGranularity);
KDS_DECL(vkCreateCommandPool);
KDS_DECL(vkDestroyCommandPool);
KDS_DECL(vkResetCommandPool);
KDS_DECL(vkAllocateCommandBuffers);
KDS_DECL(vkFreeCommandBuffers);
KDS_DECL(vkBeginCommandBuffer);
KDS_DECL(vkEndCommandBuffer);
KDS_DECL(vkResetCommandBuffer);
KDS_DECL(vkCmdBindPipeline);
KDS_DECL(vkCmdSetViewport);
KDS_DECL(vkCmdSetScissor);
KDS_DECL(vkCmdSetLineWidth);
KDS_DECL(vkCmdSetDepthBias);
KDS_DECL(vkCmdSetBlendConstants);
KDS_DECL(vkCmdSetDepthBounds);
KDS_DECL(vkCmdSetStencilCompareMask);
KDS_DECL(vkCmdSetStencilWriteMask);
KDS_DECL(vkCmdSetStencilReference);
KDS_DECL(vkCmdBindDescriptorSets);
KDS_DECL(vkCmdBindIndexBuffer);
KDS_DECL(vkCmdBindVertexBuffers);
KDS_DECL(vkCmdDraw);
KDS_DECL(vkCmdDrawIndexed);
KDS_DECL(vkCmdDrawIndirect);
KDS_DECL(vkCmdDrawIndexedIndirect);
KDS_DECL(vkCmdDispatch);
KDS_DECL(vkCmdDispatchIndirect);
KDS_DECL(vkCmdCopyBuffer);
KDS_DECL(vkCmdBlitImage);
KDS_DECL(vkCmdCopyBufferToImage);
KDS_DECL(vkCmdCopyImageToBuffer);
KDS_DECL(vkCmdUpdateBuffer);
KDS_DECL(vkCmdFillBuffer);
KDS_DECL(vkCmdClearColorImage);
KDS_DECL(vkCmdClearDepthStencilImage);
KDS_DECL(vkCmdClearAttachments);
KDS_DECL(vkCmdResolveImage);
KDS_DECL(vkCmdSetEvent);
KDS_DECL(vkCmdResetEvent);
KDS_DECL(vkCmdWaitEvents);
KDS_DECL(vkCmdPipelineBarrier);
KDS_DECL(vkCmdBeginQuery);
KDS_DECL(vkCmdEndQuery);
KDS_DECL(vkCmdResetQueryPool);
KDS_DECL(vkCmdWriteTimestamp);
KDS_DECL(vkCmdCopyQueryPoolResults);
KDS_DECL(vkCmdPushConstants);
KDS_DECL(vkCmdBeginRenderPass);
KDS_DECL(vkCmdNextSubpass);
KDS_DECL(vkCmdEndRenderPass);
KDS_DECL(vkCmdExecuteCommands);

// KHR extension functions
KDS_DECL(vkGetPhysicalDeviceSurfaceSupportKHR);
KDS_DECL(vkGetPhysicalDeviceSurfacePresentModesKHR);
KDS_DECL(vkGetPhysicalDeviceSurfaceFormatsKHR);
KDS_DECL(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
KDS_DECL(vkQueuePresentKHR);
KDS_DECL(vkAcquireNextImageKHR);
KDS_DECL(vkGetSwapchainImagesKHR);
KDS_DECL(vkCreateSwapchainKHR);
KDS_DECL(vkDestroySwapchainKHR);
KDS_DECL(vkDestroySurfaceKHR);

//test
//KDS_DECL(vkCreateXcbSurfaceKHR);

bool kds::loader::init(VULKAN_LIBRARY_TYPE lib) {
	#ifdef KDS_OS_LINUX
		lib = dlopen("libvulkan.so", RTLD_NOW);
		vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(dlsym(lib, "vkGetInstanceProcAddr"));
	#elif defined(KDS_OS_WINDOWS)
		lib = LoadLibrary("vulkan-1.dll");
		vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(GetProcAddress(lib, "vkGetInstanceProcAddr"));
	#endif

	if (vkGetInstanceProcAddr == nullptr) {
		std::cerr << "KDS FATAL: failed to load exported vulkan functions\n";
		return false;
	}

	KDS_LOAD_GLOBAL_LEVEL(vkCreateInstance);
	KDS_LOAD_GLOBAL_LEVEL(vkEnumerateInstanceExtensionProperties);
	KDS_LOAD_GLOBAL_LEVEL(vkEnumerateInstanceLayerProperties);

	return true;
}

bool kds::loader::loadInstanceLevelFunctions(VULKAN_LIBRARY_TYPE lib, VkInstance instance) {
	if (instance == nullptr) {
		std::cerr << "KDS FATAL: tried to load instance level functions to a non valid instance\n";
		return false;
	}

	KDS_LOAD_INSTANCE_LEVEL(vkEnumeratePhysicalDevices);
	KDS_LOAD_INSTANCE_LEVEL(vkEnumerateDeviceExtensionProperties);
	KDS_LOAD_INSTANCE_LEVEL(vkGetPhysicalDeviceProperties);
	KDS_LOAD_INSTANCE_LEVEL(vkGetPhysicalDeviceFeatures);
	KDS_LOAD_INSTANCE_LEVEL(vkGetPhysicalDeviceQueueFamilyProperties);
	KDS_LOAD_INSTANCE_LEVEL(vkCreateDevice);
	KDS_LOAD_INSTANCE_LEVEL(vkGetDeviceProcAddr);
	KDS_LOAD_INSTANCE_LEVEL(vkDestroyInstance);
#ifdef KDS_OS_LINUX
	KDS_LOAD_INSTANCE_LEVEL(vkCreateXcbSurfaceKHR);
#elif defined(KDS_OS_WINDOWS)
	KDS_LOAD_INSTANCE_LEVEL(vkCreateWin32SurfaceKHR);
#endif
	KDS_LOAD_INSTANCE_LEVEL(vkDestroySurfaceKHR);
	KDS_LOAD_INSTANCE_LEVEL(vkGetPhysicalDeviceSurfaceSupportKHR);
	KDS_LOAD_INSTANCE_LEVEL(vkGetPhysicalDeviceSurfacePresentModesKHR);
	KDS_LOAD_INSTANCE_LEVEL(vkGetPhysicalDeviceSurfaceFormatsKHR);
	KDS_LOAD_INSTANCE_LEVEL(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);

	return true;
}

bool kds::loader::loadInstanceLevelDebugFunctions(VULKAN_LIBRARY_TYPE lib, VkInstance instance) {
	if (instance == nullptr) {
		std::cerr << "KDS FATAL: tried to load instance level functions to a non valid instance\n";
		return false;
	}

	KDS_LOAD_INSTANCE_LEVEL(vkCreateDebugReportCallbackEXT);
	KDS_LOAD_INSTANCE_LEVEL(vkDestroyDebugReportCallbackEXT);

	return true;
}

bool kds::loader::loadDeviceLevelFunctions(VULKAN_LIBRARY_TYPE lib, VkDevice device) {
	if (device == nullptr) {
		std::cerr << "KDS FATAL: tried to load device level functions to a non valid device\n";
		return false;
	}

	KDS_LOAD_DEVICE_LEVEL(vkDestroyDevice);
	KDS_LOAD_DEVICE_LEVEL(vkGetDeviceQueue);
	KDS_LOAD_DEVICE_LEVEL(vkQueueSubmit);
	KDS_LOAD_DEVICE_LEVEL(vkQueueWaitIdle);
	KDS_LOAD_DEVICE_LEVEL(vkDeviceWaitIdle);
	KDS_LOAD_DEVICE_LEVEL(vkAllocateMemory);
	KDS_LOAD_DEVICE_LEVEL(vkFreeMemory);
	KDS_LOAD_DEVICE_LEVEL(vkMapMemory);
	KDS_LOAD_DEVICE_LEVEL(vkUnmapMemory);
	KDS_LOAD_DEVICE_LEVEL(vkFlushMappedMemoryRanges);
	KDS_LOAD_DEVICE_LEVEL(vkInvalidateMappedMemoryRanges);
	KDS_LOAD_DEVICE_LEVEL(vkGetDeviceMemoryCommitment);
	KDS_LOAD_DEVICE_LEVEL(vkBindBufferMemory);
	KDS_LOAD_DEVICE_LEVEL(vkBindImageMemory);
	KDS_LOAD_DEVICE_LEVEL(vkGetBufferMemoryRequirements);
	KDS_LOAD_DEVICE_LEVEL(vkGetImageMemoryRequirements);
	KDS_LOAD_DEVICE_LEVEL(vkGetImageSparseMemoryRequirements);
	KDS_LOAD_DEVICE_LEVEL(vkGetPhysicalDeviceSparseImageFormatProperties);
	KDS_LOAD_DEVICE_LEVEL(vkQueueBindSparse);
	KDS_LOAD_DEVICE_LEVEL(vkCreateFence);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyFence);
	KDS_LOAD_DEVICE_LEVEL(vkResetFences);
	KDS_LOAD_DEVICE_LEVEL(vkGetFenceStatus);
	KDS_LOAD_DEVICE_LEVEL(vkWaitForFences);
	KDS_LOAD_DEVICE_LEVEL(vkCreateSemaphore);
	KDS_LOAD_DEVICE_LEVEL(vkDestroySemaphore);
	KDS_LOAD_DEVICE_LEVEL(vkCreateEvent);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyEvent);
	KDS_LOAD_DEVICE_LEVEL(vkGetEventStatus);
	KDS_LOAD_DEVICE_LEVEL(vkSetEvent);
	KDS_LOAD_DEVICE_LEVEL(vkResetEvent);
	KDS_LOAD_DEVICE_LEVEL(vkCreateQueryPool);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyQueryPool);
	KDS_LOAD_DEVICE_LEVEL(vkGetQueryPoolResults);
	KDS_LOAD_DEVICE_LEVEL(vkCreateBuffer);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyBuffer);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyBufferView);
	KDS_LOAD_DEVICE_LEVEL(vkCreateImage);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyImage);
	KDS_LOAD_DEVICE_LEVEL(vkGetImageSubresourceLayout);
	KDS_LOAD_DEVICE_LEVEL(vkCreateImageView);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyImageView);
	KDS_LOAD_DEVICE_LEVEL(vkCreateShaderModule);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyShaderModule);
	KDS_LOAD_DEVICE_LEVEL(vkCreatePipelineCache);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyPipelineCache);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyPipelineLayout);
	KDS_LOAD_DEVICE_LEVEL(vkGetPipelineCacheData);
	KDS_LOAD_DEVICE_LEVEL(vkMergePipelineCaches);
	KDS_LOAD_DEVICE_LEVEL(vkCreateGraphicsPipelines);
	KDS_LOAD_DEVICE_LEVEL(vkCreateComputePipelines);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyPipeline);
	KDS_LOAD_DEVICE_LEVEL(vkCreatePipelineLayout);
	KDS_LOAD_DEVICE_LEVEL(vkCreateSampler);
	KDS_LOAD_DEVICE_LEVEL(vkDestroySampler);
	KDS_LOAD_DEVICE_LEVEL(vkCreateDescriptorSetLayout);
	KDS_LOAD_DEVICE_LEVEL(vkCreateDescriptorPool);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyDescriptorPool);
	KDS_LOAD_DEVICE_LEVEL(vkResetDescriptorPool);
	KDS_LOAD_DEVICE_LEVEL(vkAllocateDescriptorSets);
	KDS_LOAD_DEVICE_LEVEL(vkFreeDescriptorSets);
	KDS_LOAD_DEVICE_LEVEL(vkUpdateDescriptorSets);
	KDS_LOAD_DEVICE_LEVEL(vkCreateFramebuffer);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyFramebuffer);
	KDS_LOAD_DEVICE_LEVEL(vkCreateRenderPass);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyRenderPass);
	KDS_LOAD_DEVICE_LEVEL(vkGetRenderAreaGranularity);
	KDS_LOAD_DEVICE_LEVEL(vkCreateCommandPool);
	KDS_LOAD_DEVICE_LEVEL(vkDestroyCommandPool);
	KDS_LOAD_DEVICE_LEVEL(vkResetCommandPool);
	KDS_LOAD_DEVICE_LEVEL(vkAllocateCommandBuffers);
	KDS_LOAD_DEVICE_LEVEL(vkFreeCommandBuffers);
	KDS_LOAD_DEVICE_LEVEL(vkBeginCommandBuffer);
	KDS_LOAD_DEVICE_LEVEL(vkEndCommandBuffer);
	KDS_LOAD_DEVICE_LEVEL(vkResetCommandBuffer);
	KDS_LOAD_DEVICE_LEVEL(vkCmdBindPipeline);
	KDS_LOAD_DEVICE_LEVEL(vkCmdSetViewport);
	KDS_LOAD_DEVICE_LEVEL(vkCmdSetScissor);
	KDS_LOAD_DEVICE_LEVEL(vkCmdSetLineWidth);
	KDS_LOAD_DEVICE_LEVEL(vkCmdSetDepthBias);
	KDS_LOAD_DEVICE_LEVEL(vkCmdSetBlendConstants);
	KDS_LOAD_DEVICE_LEVEL(vkCmdSetDepthBounds);
	KDS_LOAD_DEVICE_LEVEL(vkCmdSetStencilCompareMask);
	KDS_LOAD_DEVICE_LEVEL(vkCmdSetStencilWriteMask);
	KDS_LOAD_DEVICE_LEVEL(vkCmdSetStencilReference);
	KDS_LOAD_DEVICE_LEVEL(vkCmdBindDescriptorSets);
	KDS_LOAD_DEVICE_LEVEL(vkCmdBindIndexBuffer);
	KDS_LOAD_DEVICE_LEVEL(vkCmdBindVertexBuffers);
	KDS_LOAD_DEVICE_LEVEL(vkCmdDraw);
	KDS_LOAD_DEVICE_LEVEL(vkCmdDrawIndexed);
	KDS_LOAD_DEVICE_LEVEL(vkCmdDrawIndirect);
	KDS_LOAD_DEVICE_LEVEL(vkCmdDrawIndexedIndirect);
	KDS_LOAD_DEVICE_LEVEL(vkCmdDispatch);
	KDS_LOAD_DEVICE_LEVEL(vkCmdDispatchIndirect);
	KDS_LOAD_DEVICE_LEVEL(vkCmdCopyBuffer);
	KDS_LOAD_DEVICE_LEVEL(vkCmdBlitImage);
	KDS_LOAD_DEVICE_LEVEL(vkCmdCopyBufferToImage);
	KDS_LOAD_DEVICE_LEVEL(vkCmdCopyImageToBuffer);
	KDS_LOAD_DEVICE_LEVEL(vkCmdUpdateBuffer);
	KDS_LOAD_DEVICE_LEVEL(vkCmdFillBuffer);
	KDS_LOAD_DEVICE_LEVEL(vkCmdClearColorImage);
	KDS_LOAD_DEVICE_LEVEL(vkCmdClearDepthStencilImage);
	KDS_LOAD_DEVICE_LEVEL(vkCmdClearAttachments);
	KDS_LOAD_DEVICE_LEVEL(vkCmdResolveImage);
	KDS_LOAD_DEVICE_LEVEL(vkCmdSetEvent);
	KDS_LOAD_DEVICE_LEVEL(vkCmdResetEvent);
	KDS_LOAD_DEVICE_LEVEL(vkCmdWaitEvents);
	KDS_LOAD_DEVICE_LEVEL(vkCmdPipelineBarrier);
	KDS_LOAD_DEVICE_LEVEL(vkCmdBeginQuery);
	KDS_LOAD_DEVICE_LEVEL(vkCmdEndQuery);
	KDS_LOAD_DEVICE_LEVEL(vkCmdResetQueryPool);
	KDS_LOAD_DEVICE_LEVEL(vkCmdWriteTimestamp);
	KDS_LOAD_DEVICE_LEVEL(vkCmdCopyQueryPoolResults);
	KDS_LOAD_DEVICE_LEVEL(vkCmdPushConstants);
	KDS_LOAD_DEVICE_LEVEL(vkCmdBeginRenderPass);
	KDS_LOAD_DEVICE_LEVEL(vkCmdNextSubpass);
	KDS_LOAD_DEVICE_LEVEL(vkCmdEndRenderPass);
	KDS_LOAD_DEVICE_LEVEL(vkCmdExecuteCommands);

	// KHR extensions
	KDS_LOAD_DEVICE_LEVEL(vkQueuePresentKHR);
	KDS_LOAD_DEVICE_LEVEL(vkAcquireNextImageKHR);
	KDS_LOAD_DEVICE_LEVEL(vkGetSwapchainImagesKHR);
	KDS_LOAD_DEVICE_LEVEL(vkCreateSwapchainKHR);
	KDS_LOAD_DEVICE_LEVEL(vkDestroySwapchainKHR);


	return true;
}

void kds::loader::terminate(VULKAN_LIBRARY_TYPE lib) {
	#ifdef KDS_OS_LINUX
		dlclose(lib);
	#elif defined(KDS_OS_WINDOWS)
		FreeLibrary(lib);
	#endif
}
