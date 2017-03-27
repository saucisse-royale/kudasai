#ifndef VULKAN_LOADER_HPP
#define VULKAN_LOADER_HPP

/// Vulkan loader
///
/// Header used to dynamicly link with the vulkan library
/// It consists in several functions to retrieve the vulkan function pointers from the vulkan runtime loader
/// (Not requiered if the app is statically linked with vulkan)

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>
#include <iostream>

#if defined(__linux__) || defined(__UNIX__)
	#define KDS_OS_LINUX
	#include <dlfcn.h>
#elif defined(__MINGW32__) || defined(_WIN32)
	#define KDS_OS_WINDOWS
 	#include <Windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

namespace kds {
	namespace loader {
		/// init the VulkanWL library
		/// Loads the vulkan loader and retrives the global level function pointers from it
		///
		/// \return false if anything couldn't be loaded, of true if everything went fine
		bool init();

		/// Terminates the VulkanWL library
		/// Closes the vulkan loader, no vulkan functions can be called after calling this
		void terminate();

		/// Loads the instance-level function pointers
		///
		/// \param instance A VALID vulkan instance (after creating it with vkCreateInstance)
		///
		/// \return false if anything couldn't be loaded, of true if everything went fine
		bool loadInstanceLevelFunctions(VkInstance instance);

		/// Loads the device-level function pointers
		///
		/// \param device A VALID vulkan device (after creating it with vkCreateDevice)
		///
		/// \return false if anything couldn't be loaded, of true if everything went fine
		bool loadDeviceLevelFunctions(VkDevice device);
	} // namespace loader
} // namespace kds

// Macros to shorten the code

#define KDS_CHECK_LOADING(fun) if(!fun) {\
	std::cerr << "KDS FATAL: failed loading " << #fun << '\n';\
	return 0;\
}

#define KDS_DECL_EXTERN(fun) extern PFN_##fun fun;
#define KDS_DECL(fun) PFN_##fun fun;
#define KDS_LOAD_GLOBAL_LEVEL(fun) fun = reinterpret_cast<PFN_##fun>(vkGetInstanceProcAddr(nullptr, #fun)); KDS_CHECK_LOADING(fun);
#define KDS_LOAD_INSTANCE_LEVEL(fun) fun = reinterpret_cast<PFN_##fun>(vkGetInstanceProcAddr(instance, #fun)); KDS_CHECK_LOADING(fun);
#define KDS_LOAD_DEVICE_LEVEL(fun) fun = reinterpret_cast<PFN_##fun>(vkGetDeviceProcAddr(device, #fun)); KDS_CHECK_LOADING(fun);

// vulkan library loaded from .so lib
#ifdef KDS_OS_LINUX
	extern void *KDS_VULKAN_LIBRARY;
#elif defined(KDS_OS_WINDOWS)
	extern HMODULE KDS_VULKAN_LIBRARY;
#endif

// declare exported function
KDS_DECL_EXTERN(vkGetInstanceProcAddr);

// declare global level functions
KDS_DECL_EXTERN(vkCreateInstance);
KDS_DECL_EXTERN(vkEnumerateInstanceExtensionProperties);
KDS_DECL_EXTERN(vkEnumerateInstanceLayerProperties);

// declare instance level functions
KDS_DECL_EXTERN(vkEnumeratePhysicalDevices);
KDS_DECL_EXTERN(vkGetPhysicalDeviceProperties);
KDS_DECL_EXTERN(vkGetPhysicalDeviceFeatures);
KDS_DECL_EXTERN(vkGetPhysicalDeviceQueueFamilyProperties);
KDS_DECL_EXTERN(vkCreateDevice);
KDS_DECL_EXTERN(vkGetDeviceProcAddr);
KDS_DECL_EXTERN(vkDestroyInstance);

// declare device level functions
KDS_DECL_EXTERN(vkDestroyDevice);
KDS_DECL_EXTERN(vkGetDeviceQueue);
KDS_DECL_EXTERN(vkQueueSubmit);
KDS_DECL_EXTERN(vkQueueWaitIdle);
KDS_DECL_EXTERN(vkDeviceWaitIdle);
KDS_DECL_EXTERN(vkAllocateMemory);
KDS_DECL_EXTERN(vkFreeMemory);
KDS_DECL_EXTERN(vkMapMemory);
KDS_DECL_EXTERN(vkUnmapMemory);
KDS_DECL_EXTERN(vkFlushMappedMemoryRanges);
KDS_DECL_EXTERN(vkInvalidateMappedMemoryRanges);
KDS_DECL_EXTERN(vkGetDeviceMemoryCommitment);
KDS_DECL_EXTERN(vkBindBufferMemory);
KDS_DECL_EXTERN(vkBindImageMemory);
KDS_DECL_EXTERN(vkGetBufferMemoryRequirements);
KDS_DECL_EXTERN(vkGetImageMemoryRequirements);
KDS_DECL_EXTERN(vkGetImageSparseMemoryRequirements);
KDS_DECL_EXTERN(vkGetPhysicalDeviceSparseImageFormatProperties);
KDS_DECL_EXTERN(vkQueueBindSparse);
KDS_DECL_EXTERN(vkCreateFence);
KDS_DECL_EXTERN(vkDestroyFence);
KDS_DECL_EXTERN(vkResetFences);
KDS_DECL_EXTERN(vkGetFenceStatus);
KDS_DECL_EXTERN(vkWaitForFences);
KDS_DECL_EXTERN(vkCreateSemaphore);
KDS_DECL_EXTERN(vkDestroySemaphore);
KDS_DECL_EXTERN(vkCreateEvent);
KDS_DECL_EXTERN(vkDestroyEvent);
KDS_DECL_EXTERN(vkGetEventStatus);
KDS_DECL_EXTERN(vkSetEvent);
KDS_DECL_EXTERN(vkResetEvent);
KDS_DECL_EXTERN(vkCreateQueryPool);
KDS_DECL_EXTERN(vkDestroyQueryPool);
KDS_DECL_EXTERN(vkGetQueryPoolResults);
KDS_DECL_EXTERN(vkCreateBuffer);
KDS_DECL_EXTERN(vkDestroyBuffer);
KDS_DECL_EXTERN(vkDestroyBufferView);
KDS_DECL_EXTERN(vkCreateImage);
KDS_DECL_EXTERN(vkDestroyImage);
KDS_DECL_EXTERN(vkGetImageSubresourceLayout);
KDS_DECL_EXTERN(vkCreateImageView);
KDS_DECL_EXTERN(vkDestroyImageView);
KDS_DECL_EXTERN(vkCreateShaderModule);
KDS_DECL_EXTERN(vkDestroyShaderModule);
KDS_DECL_EXTERN(vkCreatePipelineCache);
KDS_DECL_EXTERN(vkDestroyPipelineCache);
KDS_DECL_EXTERN(vkGetPipelineCacheData);
KDS_DECL_EXTERN(vkMergePipelineCaches);
KDS_DECL_EXTERN(vkCreateGraphicsPipelines);
KDS_DECL_EXTERN(vkCreateComputePipelines);
KDS_DECL_EXTERN(vkDestroyPipeline);
KDS_DECL_EXTERN(vkCreatePipelineLayout);
KDS_DECL_EXTERN(vkCreateSampler);
KDS_DECL_EXTERN(vkDestroySampler);
KDS_DECL_EXTERN(vkCreateDescriptorSetLayout);
KDS_DECL_EXTERN(vkCreateDescriptorPool);
KDS_DECL_EXTERN(vkDestroyDescriptorPool);
KDS_DECL_EXTERN(vkResetDescriptorPool);
KDS_DECL_EXTERN(vkAllocateDescriptorSets);
KDS_DECL_EXTERN(vkFreeDescriptorSets);
KDS_DECL_EXTERN(vkUpdateDescriptorSets);
KDS_DECL_EXTERN(vkCreateFramebuffer);
KDS_DECL_EXTERN(vkDestroyFramebuffer);
KDS_DECL_EXTERN(vkCreateRenderPass);
KDS_DECL_EXTERN(vkDestroyRenderPass);
KDS_DECL_EXTERN(vkGetRenderAreaGranularity);
KDS_DECL_EXTERN(vkCreateCommandPool);
KDS_DECL_EXTERN(vkDestroyCommandPool);
KDS_DECL_EXTERN(vkResetCommandPool);
KDS_DECL_EXTERN(vkAllocateCommandBuffers);
KDS_DECL_EXTERN(vkFreeCommandBuffers);
KDS_DECL_EXTERN(vkBeginCommandBuffer);
KDS_DECL_EXTERN(vkEndCommandBuffer);
KDS_DECL_EXTERN(vkResetCommandBuffer);
KDS_DECL_EXTERN(vkCmdBindPipeline);
KDS_DECL_EXTERN(vkCmdSetViewport);
KDS_DECL_EXTERN(vkCmdSetScissor);
KDS_DECL_EXTERN(vkCmdSetLineWidth);
KDS_DECL_EXTERN(vkCmdSetDepthBias);
KDS_DECL_EXTERN(vkCmdSetBlendConstants);
KDS_DECL_EXTERN(vkCmdSetDepthBounds);
KDS_DECL_EXTERN(vkCmdSetStencilCompareMask);
KDS_DECL_EXTERN(vkCmdSetStencilWriteMask);
KDS_DECL_EXTERN(vkCmdSetStencilReference);
KDS_DECL_EXTERN(vkCmdBindDescriptorSets);
KDS_DECL_EXTERN(vkCmdBindIndexBuffer);
KDS_DECL_EXTERN(vkCmdBindVertexBuffers);
KDS_DECL_EXTERN(vkCmdDraw);
KDS_DECL_EXTERN(vkCmdDrawIndexed);
KDS_DECL_EXTERN(vkCmdDrawIndirect);
KDS_DECL_EXTERN(vkCmdDrawIndexedIndirect);
KDS_DECL_EXTERN(vkCmdDispatch);
KDS_DECL_EXTERN(vkCmdDispatchIndirect);
KDS_DECL_EXTERN(vkCmdCopyBuffer);
KDS_DECL_EXTERN(vkCmdBlitImage);
KDS_DECL_EXTERN(vkCmdCopyBufferToImage);
KDS_DECL_EXTERN(vkCmdCopyImageToBuffer);
KDS_DECL_EXTERN(vkCmdUpdateBuffer);
KDS_DECL_EXTERN(vkCmdFillBuffer);
KDS_DECL_EXTERN(vkCmdClearColorImage);
KDS_DECL_EXTERN(vkCmdClearDepthStencilImage);
KDS_DECL_EXTERN(vkCmdClearAttachments);
KDS_DECL_EXTERN(vkCmdResolveImage);
KDS_DECL_EXTERN(vkCmdSetEvent);
KDS_DECL_EXTERN(vkCmdResetEvent);
KDS_DECL_EXTERN(vkCmdWaitEvents);
KDS_DECL_EXTERN(vkCmdPipelineBarrier);
KDS_DECL_EXTERN(vkCmdBeginQuery);
KDS_DECL_EXTERN(vkCmdEndQuery);
KDS_DECL_EXTERN(vkCmdResetQueryPool);
KDS_DECL_EXTERN(vkCmdWriteTimestamp);
KDS_DECL_EXTERN(vkCmdCopyQueryPoolResults);
KDS_DECL_EXTERN(vkCmdPushConstants);
KDS_DECL_EXTERN(vkCmdBeginRenderPass);
KDS_DECL_EXTERN(vkCmdNextSubpass);
KDS_DECL_EXTERN(vkCmdEndRenderPass);
KDS_DECL_EXTERN(vkCmdExecuteCommands);

#ifdef __cplusplus
}
#endif

#endif // VulkanLoader.hpp
