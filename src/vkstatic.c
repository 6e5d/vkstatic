#include <vulkan/vulkan.h>

#include "../include/vkstatic.h"
#include "../../vkhelper/include/device.h"
#include "../../vkhelper/include/semaphore.h"
#include "../../vkhelper/include/cbuf.h"
#include "../../vkhelper/include/scsi.h"
#include "../../vkhelper/include/validation.h"
#include "../../vkhelper/include/instance.h"
#include "../../vkhelper/include/pdev.h"

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
	vkGetPhysicalDeviceMemoryProperties(vks->pdev, &vks->pdev_memprop);
	vks->scsi = vkhelper_scsi(vks->pdev, vks->surface);
	vkhelper_device(
		&vks->device,
		&vks->queue,
		&vks->cpool,
		vks->pdev,
		family_idx
	);
	vks->cbuf = vkhelper_cbuf_new(vks->cpool, vks->device);
}

void vkstatic_deinit(Vkstatic* v) {
	vkFreeCommandBuffers(v->device, v->cpool, 1, &v->cbuf);
	vkDestroyCommandPool(v->device, v->cpool, NULL);
	vkDestroyDevice(v->device, NULL);
	vkDestroySurfaceKHR(v->instance, v->surface, NULL);
	vkhelper_validation_destroy(v->instance, v->messenger);
	vkDestroyInstance(v->instance, NULL);
}
