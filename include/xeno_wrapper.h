#ifndef XENO_WRAPPER_H
#define XENO_WRAPPER_H

#include <stdint.h>
#include <stddef.h>

/* Forward declare basic Vulkan structs */
struct VkPhysicalDeviceProperties;
struct VkPhysicalDeviceFeatures2;
struct VkPhysicalDeviceMemoryProperties2;
struct VkPhysicalDeviceMeshShaderFeaturesEXT;
struct VkPhysicalDeviceRayTracingPipelineFeaturesKHR;

void xeno_init(void);
void xeno_open_log(void);
void xeno_log(const char *fmt, ...);
void xeno_log_event(const char *json);
void xeno_log_bin(const char *relpath, const void *data, size_t size);
void xeno_flush_all(void);

/* Used by intercept.c → deep Vulkan introspection */
int generate_feature_dump_to(const char *path,
                             void *physDevice,
                             struct VkPhysicalDeviceProperties *props);

#endif
