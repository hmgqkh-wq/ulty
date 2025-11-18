cmake_minimum_required(VERSION 3.10)
project(vulkan.xeno_wrapper C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# include directory
include_directories(include)

# Sources — only the three files required for B-EASY
add_library(vulkan.xeno_wrapper SHARED
    src/intercept.c
    src/logger.c
    src/feature_dump.c
)

# Link liblog only on Android; always link dl
if (CMAKE_SYSTEM_NAME STREQUAL "Android")
    target_link_libraries(vulkan.xeno_wrapper log dl)
else()
    target_link_libraries(vulkan.xeno_wrapper dl)
endif()

# Ensure output filename matches Eden requirements (libvulkan.xeno_wrapper.so)
set_target_properties(vulkan.xeno_wrapper PROPERTIES
    OUTPUT_NAME "vulkan.xeno_wrapper"
)
