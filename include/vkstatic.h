#include <vulkan/vulkan.h>

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
} Vkstatic();

void vkstatic(init)(
	Vkstatic()* vks,
	VkInstance instance,
	VkSurfaceKHR surface
);
void vkstatic(deinit)(Vkstatic()* v);
VkCommandBuffer vkstatic(begin)(Vkstatic()* vks);

VkCommandBuffer vkstatic(oneshot_begin)(Vkstatic()* vks);
void vkstatic(oneshot_end)(VkCommandBuffer cbuf, Vkstatic()* vks);
