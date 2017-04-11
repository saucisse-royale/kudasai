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

	void VulkanGraphicsPipeline::create(VulkanGraphicsPipelineConfig const& pipelineConfig) noexcept {
		createVertexShaderModule(pipelineConfig.vertexPath);
		createFragmentShaderModule(pipelineConfig.fragmentPath);

		std::array<VkPipelineShaderStageCreateInfo, 2> shaderStageInfos{};

		shaderStageInfos[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStageInfos[0].module = _vertexShaderModule;
		shaderStageInfos[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		shaderStageInfos[0].pName = pipelineConfig.vertexPath.c_str();

		shaderStageInfos[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStageInfos[1].module = _fragmentShaderModule;
		shaderStageInfos[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		shaderStageInfos[1].pName = pipelineConfig.fragmentPath.c_str();

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
	}

} // namespace kds
