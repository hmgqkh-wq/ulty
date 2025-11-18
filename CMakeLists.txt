cmake_minimum_required(VERSION 3.10)
project(vulkan.xeno_wrapper C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_library(vulkan.xeno_wrapper SHARED
    src/intercept.c
    src/logger.c
    src/feature_dump.c
)

target_link_libraries(vulkan.xeno_wrapper dl log)
