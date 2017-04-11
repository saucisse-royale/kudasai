#include "VulkanGraphicsPipeline.hpp"

#include "VulkanLoader.hpp"
#include "VulkanHelper.hpp"
#include "VulkanContext.hpp"

namespace kds {
	VulkanGraphicsPipeline::VulkanGraphicsPipeline(VulkanContext* vulkanContext) noexcept :
		_vulkanContext{vulkanContext},
		_vertexShaderModule{vkDestroyShaderModule, _vulkanContext->_device, _vertexShaderModule, nullptr},
		_fragmentShaderModule{vkDestroyShaderModule, _vulkanContext->_device, _fragmentShaderModule, nullptr},
		_pipeline{vkDestroyPipeline, _vulkanContext->_device, _pipeline, nullptr}
	{}

	void VulkanGraphicsPipeline::createVertexShaderModule(std::string const& path) noexcept {
		std::vector<char> vertexShaderCode{utils::read_file(path)};

		VkShaderModuleCreateInfo vertexModuleInfo{};
		vertexModuleInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		vertexModuleInfo.codeSize = vertexShaderCode.size();
		vertexModuleInfo.pCode = reinterpret_cast<uint32_t const*>(vertexShaderCode.data());

		auto result = vkCreateShaderModule(_vulkanContext->_device, &vertexModuleInfo, nullptr, _vertexShaderModule.reset());
		KDS_CHECK_RESULT(result, "Failed to create a vertex shader module.");
	}

	void VulkanGraphicsPipeline::createFragmentShaderModule(std::string const& path) noexcept {
		std::vector<char> fragmentShaderCode{utils::read_file(path)};

		VkShaderModuleCreateInfo fragmentModuleInfo{};
		fragmentModuleInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		fragmentModuleInfo.codeSize = fragmentShaderCode.size();
		fragmentModuleInfo.pCode = reinterpret_cast<uint32_t const*>(fragmentShaderCode.data());

		auto result = vkCreateShaderModule(_vulkanContext->_device, &fragmentModuleInfo, nullptr, _fragmentShaderModule.reset());
		KDS_CHECK_RESULT(result, "Failed to create a vertex shader module.");
	}

	RAII<VkPipelineLayout> VulkanGraphicsPipeline::createPipelineLayout() const noexcept {
		RAII<VkPipelineLayout> pipelineLayout{vkDestroyPipelineLayout, _vulkanContext->_device, pipelineLayout, nullptr};

		// TODO change when descriptor sets are supported
		VkPipelineLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		layoutInfo.setLayoutCount = 0;
		layoutInfo.pSetLayouts = nullptr;
		layoutInfo.pushConstantRangeCount = 0;
		layoutInfo.pPushConstantRanges = nullptr;

		auto result = vkCreatePipelineLayout(_vulkanContext->_device, &layoutInfo, nullptr, pipelineLayout.reset());
		KDS_CHECK_RESULT(result, "Failed to create a pipeline layout.");

		return pipelineLayout;
	}

	RAII<VkRenderPass> VulkanGraphicsPipeline::createRenderPass() const noexcept {
		std::array<VkAttachmentDescription, 1> attachmentDescriptions{};
		attachmentDescriptions[0].flags = 0;
		attachmentDescriptions[0].format = _vulkanContext->_vulkanSwapchain._surfaceFormat.format;
		attachmentDescriptions[0].samples = VK_SAMPLE_COUNT_1_BIT;
		attachmentDescriptions[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachmentDescriptions[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachmentDescriptions[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachmentDescriptions[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachmentDescriptions[0].initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		attachmentDescriptions[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		std::array<VkAttachmentReference, 1> attachmentReferences{};
		attachmentReferences[0].attachment = 0;
		attachmentReferences[0].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		std::array<VkSubpassDescription, 1> subpassDescriptions{};
		subpassDescriptions[0].flags = 0;
		subpassDescriptions[0].pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpassDescriptions[0].inputAttachmentCount = 0;
		subpassDescriptions[0].pInputAttachments = nullptr;
		subpassDescriptions[0].colorAttachmentCount = 1;
		subpassDescriptions[0].pColorAttachments = attachmentReferences.data();
		subpassDescriptions[0].pResolveAttachments = nullptr;
		subpassDescriptions[0].pDepthStencilAttachment = nullptr;
		subpassDescriptions[0].preserveAttachmentCount = 0;
		subpassDescriptions[0].pPreserveAttachments = nullptr;

		RAII<VkRenderPass> renderPass{vkDestroyRenderPass, _vulkanContext->_device, renderPass, nullptr};

		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = attachmentDescriptions.size();
		renderPassInfo.pAttachments = attachmentDescriptions.data();
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = subpassDescriptions.data();
		renderPassInfo.dependencyCount = 0;
		renderPassInfo.pDependencies = nullptr;

		auto result = vkCreateRenderPass(_vulkanContext->_device, &renderPassInfo, nullptr, renderPass.reset());
		KDS_CHECK_RESULT(result, "Failed to create a render pass.");

		return renderPass;
	}

	void VulkanGraphicsPipeline::create(VulkanGraphicsPipelineConfig const& pipelineConfig) noexcept {
		createVertexShaderModule(pipelineConfig.vertexPath);
		createFragmentShaderModule(pipelineConfig.fragmentPath);

		std::array<VkPipelineShaderStageCreateInfo, 2> shaderStageInfos{};

		shaderStageInfos[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStageInfos[0].module = _vertexShaderModule;
		shaderStageInfos[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		shaderStageInfos[0].pName = "main";

		shaderStageInfos[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStageInfos[1].module = _fragmentShaderModule;
		shaderStageInfos[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		shaderStageInfos[1].pName = "main";

		VkPipelineVertexInputStateCreateInfo vertexInputStateInfo{};
		vertexInputStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateInfo{};
		inputAssemblyStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssemblyStateInfo.topology = pipelineConfig.primitiveTopology;
		inputAssemblyStateInfo.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = _vulkanContext->_contextConfig.windowConfig.width;
		viewport.height = _vulkanContext->_contextConfig.windowConfig.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissors{};
		scissors.offset = {static_cast<int32_t>(viewport.x), static_cast<int32_t>(viewport.y)};
		scissors.extent = {static_cast<uint32_t>(viewport.width), static_cast<uint32_t>(viewport.height)};

		VkPipelineViewportStateCreateInfo viewportStateInfo{};
		viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportStateInfo.viewportCount = 1;
		viewportStateInfo.pViewports = &viewport;
		viewportStateInfo.scissorCount = 1;
		viewportStateInfo.pScissors = &scissors;

		auto const& rasterizerConfig = pipelineConfig.rasterizerConfig;

		VkPipelineRasterizationStateCreateInfo rasterizerStateInfo{};
		rasterizerStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizerStateInfo.depthClampEnable = rasterizerConfig.depthClampEnabled;
		rasterizerStateInfo.rasterizerDiscardEnable = rasterizerConfig.rasterizerDiscardEnabled;
		rasterizerStateInfo.polygonMode = rasterizerConfig.polygonMode;
		rasterizerStateInfo.cullMode = rasterizerConfig.cullMode;
		rasterizerStateInfo.frontFace = rasterizerConfig.frontFace;
		rasterizerStateInfo.depthBiasEnable = rasterizerConfig.depthBiasEnabled;
		rasterizerStateInfo.depthBiasClamp = rasterizerConfig.depthBiasClamp;
		rasterizerStateInfo.depthBiasSlopeFactor = rasterizerConfig.depthBiasSlopeFactor;
		rasterizerStateInfo.lineWidth = rasterizerConfig.lineWidth;

		// TODO change when textures will be supported
		VkPipelineMultisampleStateCreateInfo multisampleStateInfo{};
		multisampleStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampleStateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampleStateInfo.sampleShadingEnable = VK_FALSE;
		multisampleStateInfo.minSampleShading = 1.0f;
		multisampleStateInfo.pSampleMask = nullptr;
		multisampleStateInfo.alphaToCoverageEnable = VK_FALSE;
		multisampleStateInfo.alphaToOneEnable = VK_FALSE;

		// temp
		VkPipelineColorBlendAttachmentState colorBlendState{};
		colorBlendState.blendEnable = VK_FALSE;
		colorBlendState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendState.colorBlendOp = VK_BLEND_OP_ADD;
		colorBlendState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendState.alphaBlendOp = VK_BLEND_OP_ADD;
		colorBlendState.colorWriteMask =
			VK_COLOR_COMPONENT_R_BIT |
			VK_COLOR_COMPONENT_G_BIT |
			VK_COLOR_COMPONENT_B_BIT |
			VK_COLOR_COMPONENT_A_BIT;

		VkPipelineColorBlendStateCreateInfo colorBlendStateInfo{};
		colorBlendStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlendStateInfo.logicOpEnable = VK_FALSE;
		colorBlendStateInfo.logicOp = VK_LOGIC_OP_COPY;
		colorBlendStateInfo.attachmentCount = 1;
		colorBlendStateInfo.pAttachments = &colorBlendState;
		colorBlendStateInfo.blendConstants[0] = 0.0f;
		colorBlendStateInfo.blendConstants[1] = 0.0f;
		colorBlendStateInfo.blendConstants[2] = 0.0f;
		colorBlendStateInfo.blendConstants[3] = 0.0f;

		auto pipelineLayout = createPipelineLayout();
		auto renderPass = createRenderPass();

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = shaderStageInfos.size();
		pipelineInfo.pStages = shaderStageInfos.data();
		pipelineInfo.pVertexInputState = &vertexInputStateInfo;
		pipelineInfo.pInputAssemblyState = &inputAssemblyStateInfo;
		pipelineInfo.pTessellationState = nullptr;
		pipelineInfo.pViewportState = &viewportStateInfo;
		pipelineInfo.pRasterizationState = &rasterizerStateInfo;
		pipelineInfo.pMultisampleState = &multisampleStateInfo;
		pipelineInfo.pDepthStencilState = nullptr;
		pipelineInfo.pColorBlendState = &colorBlendStateInfo;
		pipelineInfo.pDynamicState = nullptr;
		pipelineInfo.layout = pipelineLayout;
		pipelineInfo.renderPass = renderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineInfo.basePipelineIndex = -1;

		auto result = vkCreateGraphicsPipelines(_vulkanContext->_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, _pipeline.reset());
		KDS_CHECK_RESULT(result, "Failed to create a graphics pipeline.");
	}

} // namespace kds
