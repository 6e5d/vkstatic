#ifndef _VKSTATIC_VKSTATICH
#define _VKSTATIC_VKSTATICH

#include <vulkan/vulkan.h>

#include "../../vkhelper/include/scsi.h"

typedef struct {
	VkInstance instance;
	VkCommandBuffer cbuf;
	VkDebugUtilsMessengerEXT messenger;
	VkSurfaceKHR surface;
	VkPhysicalDevice pdev;
	VkFormat depth_format;
	VkPhysicalDeviceMemoryProperties memprop;
	VkSurfaceFormatKHR surface_format;
	VkSurfaceCapabilitiesKHR surface_caps;
	VkDevice device;
	VkQueue queue;
	VkCommandPool cpool;
} Vkstatic;

void vkstatic_init(
	Vkstatic* vks,
	VkInstance instance,
	VkSurfaceKHR surface
);
void vkstatic_deinit(Vkstatic* v);

#endif
