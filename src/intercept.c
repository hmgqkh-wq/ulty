#define _GNU_SOURCE
#include "xeno_wrapper.h"
#include "vulkan/vulkan.h"

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

/* ========================================================================== */
/*  Forward-declared real Vulkan entrypoint                                   */
/* ========================================================================== */

static PFN_vkGetInstanceProcAddr real_vkGetInstanceProcAddr = NULL;

/* ========================================================================== */
/*  Init (constructor)                                                         */
/* ========================================================================== */

__attribute__((constructor))
static void xeno_constructor(void)
{
    xeno_open_log();
    xeno_log("XENO WRAPPER: constructor begin");

    void *h = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
    if (!h) {
        xeno_log("ERROR: failed to dlopen libvulkan.so");
        return;
    }

    real_vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)dlsym(h, "vkGetInstanceProcAddr");

    if (!real_vkGetInstanceProcAddr) {
        xeno_log("ERROR: failed to load real vkGetInstanceProcAddr");
    } else {
        xeno_log("Loaded real vkGetInstanceProcAddr");
    }
}

/* ========================================================================== */
/*  Intercept vkGetInstanceProcAddr                                           */
/* ========================================================================== */

PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance instance, const char *pName)
{
    if (!real_vkGetInstanceProcAddr)
        return NULL;

    /* Log first calls */
    if (pName) {
        xeno_log("vkGetInstanceProcAddr called for: %s", pName);
    }

    PFN_vkVoidFunction fn =
        real_vkGetInstanceProcAddr(instance, pName);

    /* We can intercept specific Vulkan functions here later */
    return fn;
}

/* ========================================================================== */
/*  Export ICD symbol (required by Eden)                                      */
/* ========================================================================== */

PFN_vkVoidFunction vk_icdGetInstanceProcAddr(VkInstance instance, const char *pName)
{
    return vkGetInstanceProcAddr(instance, pName);
}
