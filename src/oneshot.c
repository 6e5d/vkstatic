#include <assert.h>
#include <vulkan/vulkan.h>

#include "../include/vkstatic.h"

// sync, so it is slow, for initialization only
VkCommandBuffer vkstatic_oneshot_begin(Vkstatic* vks) {
	VkCommandBuffer cbuf;
	VkCommandBufferAllocateInfo info = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.commandPool = vks->cpool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = 1,
	};
	assert(0 == vkAllocateCommandBuffers(
		vks->device, &info, &cbuf));

	VkCommandBufferBeginInfo cmdBufInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
	};
	assert(0 == vkBeginCommandBuffer(cbuf, &cmdBufInfo));
	return cbuf;
}

void vkstatic_oneshot_end(VkCommandBuffer cbuf, Vkstatic* vks) {
	assert(0 == vkEndCommandBuffer(cbuf));
	VkSubmitInfo submitInfo = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.commandBufferCount = 1,
		.pCommandBuffers = &cbuf,
	};
	VkFenceCreateInfo fenceCI = {
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.flags = 0,
	};
	VkFence fence;
	assert(0 == vkCreateFence(vks->device, &fenceCI, NULL, &fence));
	assert(0 == vkQueueSubmit(vks->queue, 1, &submitInfo, fence));
	assert(0 == vkWaitForFences(vks->device, 1,
		&fence, VK_TRUE, 1000000000));

	vkDestroyFence(vks->device, fence, NULL);
	vkFreeCommandBuffers(vks->device, vks->cpool, 1, &cbuf);
}
