#define _GNU_SOURCE
#include "vulkan/vulkan.h"

/*
 * Eden sometimes calls vk_icdGetInstanceProcAddr instead of vkGetInstanceProcAddr.
 * This forwarder ensures the wrapper always loads.
 */

extern PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance instance, const char *pName);

PFN_vkVoidFunction vk_icdGetInstanceProcAddr(VkInstance instance, const char *pName)
{
    return vkGetInstanceProcAddr(instance, pName);
}
