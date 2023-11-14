#include <vulkan/vulkan.h>

#include "../../vkhelper/include/cbuf.h"
#include "../../vkhelper/include/device.h"
#include "../../vkhelper/include/instance.h"
#include "../../vkhelper/include/pdev.h"
#include "../../vkhelper/include/scsi.h"
#include "../../vkhelper/include/semaphore.h"
#include "../../vkhelper/include/validation.h"
#include "../include/vkstatic.h"

void vkstatic_init(
	Vkstatic* vks,
	VkInstance instance,
	VkSurfaceKHR surface
) {
	vks->messenger = vkhelper_validation_new(instance);
	vks->instance = instance;
	vks->surface = surface;
	uint32_t family_idx;
	vks->pdev = vkhelper_pdev_selector(instance, surface, &family_idx);
	vkhelper_depth_format(vks->pdev, &vks->depth_format);
	vkGetPhysicalDeviceMemoryProperties(vks->pdev, &vks->memprop);
	vkhelper_scsi(
		&vks->surface_format, &vks->surface_caps,
		vks->pdev, vks->surface);
	vkhelper_device(
		&vks->device,
		&vks->queue,
		&vks->cpool,
		vks->pdev,
		family_idx
	);
	vks->cbuf = vkhelper_cbuf_new(vks->cpool, vks->device);
}

void vkstatic_deinit(Vkstatic* vks) {
	vkFreeCommandBuffers(vks->device, vks->cpool, 1, &vks->cbuf);
	vkDestroyCommandPool(vks->device, vks->cpool, NULL);
	vkDestroyDevice(vks->device, NULL);
	vkDestroySurfaceKHR(vks->instance, vks->surface, NULL);
	vkhelper_validation_destroy(vks->instance, vks->messenger);
	vkDestroyInstance(vks->instance, NULL);
}
