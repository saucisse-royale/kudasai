#pragma once

#include "RAII.hpp"
#include "VulkanLoader.hpp"
#include "VulkanHelper.hpp"
#include "VulkanConfig.hpp"

#include <string>

namespace kds {

	struct VulkanGraphicsPipelineConfig {
		std::string vertexPath{""};
		std::string fragmentPath{""};

		VkPrimitiveTopology primitiveTopology{VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST};

		struct {
			bool depthClampEnabled{false};
			bool rasterizerDiscardEnabled{false};
			VkPolygonMode polygonMode{VK_POLYGON_MODE_FILL};
			VkCullModeFlags cullMode{VK_CULL_MODE_BACK_BIT};
			VkFrontFace frontFace{VK_FRONT_FACE_COUNTER_CLOCKWISE};
			bool depthBiasEnabled{false};
			float depthBiasConstantFactor{};
			float depthBiasClamp{};
			float depthBiasSlopeFactor{};
			float lineWidth{};

		} rasterizerConfig;
	};

	class VulkanContext;

	class VulkanGraphicsPipeline {
	public:
		explicit VulkanGraphicsPipeline(VulkanContext* vulkanContext) noexcept;

		void create(VulkanGraphicsPipelineConfig const&) noexcept;

		void setVertexShader(std::string const& path) noexcept;
		void setFragmentShader(std::string const& path) noexcept;

		void createVertexShaderModule(std::string const& path) noexcept;
		void createFragmentShaderModule(std::string const& path) noexcept;


		// non owning pointer to the vulkan context
		VulkanContext* _vulkanContext{};
		RAII<VkShaderModule> _vertexShaderModule;
		RAII<VkShaderModule> _fragmentShaderModule;

		RAII<VkPipeline> _pipeline;

	};
} // namespace kds
