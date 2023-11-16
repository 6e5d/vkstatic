#include <vulkan/vulkan.h>

#include "vkstatic.h"

VkCommandBuffer vkstatic_oneshot_begin(Vkstatic* vks);
void vkstatic_oneshot_end(VkCommandBuffer cbuf, Vkstatic* vks);
