#ifndef VULKAN_WRAPPER_STUB_H
#define VULKAN_WRAPPER_STUB_H

/* We only define what the wrapper needs */

#include <stdint.h>

typedef uint64_t VkDeviceSize;
typedef uint64_t VkFlags;
typedef uint64_t VkBool32;

typedef struct VkInstance_T* VkInstance;
typedef struct VkDevice_T*   VkDevice;
typedef struct VkPhysicalDevice_T* VkPhysicalDevice;

/* Basic properties (this structure is stable across versions) */
typedef struct VkPhysicalDeviceProperties {
    uint32_t apiVersion;
    uint32_t driverVersion;
    uint32_t vendorID;
    uint32_t deviceID;
    char     deviceName[256];
    uint8_t  pipelineCacheUUID[16];
} VkPhysicalDeviceProperties;

/* Minimal function pointer type */
typedef void (*PFN_vkVoidFunction)(void);

/* Loader entrypoint */
typedef PFN_vkVoidFunction (*PFN_vkGetInstanceProcAddr)(VkInstance instance, const char *pName);

#endif
