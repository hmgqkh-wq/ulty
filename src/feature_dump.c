#define _GNU_SOURCE
#include "xeno_wrapper.h"
#include "vulkan/vulkan.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Deep Vulkan device info extraction (B-EASY) */

int generate_feature_dump_to(const char *path,
                             void *physGeneric,
                             struct VkPhysicalDeviceProperties *props)
{
    (void) physGeneric; /* We don't need raw VkPhysicalDevice for now */

    const char *out = (path && path[0])
                        ? path
                        : "/storage/emulated/0/eden_wrapper_logs/device/device_properties.json";

    FILE *f = fopen(out, "w");
    if (!f) return -1;

    time_t t = time(NULL);

    fprintf(f, "{\n");
    fprintf(f, "  \"timestamp\": %ld,\n", (long)t);
    fprintf(f, "  \"apiVersion\": %u,\n", props->apiVersion);
    fprintf(f, "  \"driverVersion\": %u,\n", props->driverVersion);
    fprintf(f, "  \"vendorID\": %u,\n", props->vendorID);
    fprintf(f, "  \"deviceID\": %u,\n", props->deviceID);
    fprintf(f, "  \"deviceName\": \"%s\",\n", props->deviceName);

    /* Dump pipeline UUID */
    fprintf(f, "  \"pipelineCacheUUID\": [");
    for (int i = 0; i < 16; i++) {
        fprintf(f, "%u%s", props->pipelineCacheUUID[i], (i == 15 ? "" : ", "));
    }
    fprintf(f, "]\n");

    fprintf(f, "}\n");
    fclose(f);

    xeno_log("feature_dump: wrote %s", out);
    return 0;
}
