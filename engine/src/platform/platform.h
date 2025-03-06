#pragma once

#include "defines.h"

typedef struct Platform {
    void* state;
} Platform;

b8 platform_start(Platform* platform, const char* name, i32 x, i32 y, i32 width, i32 height);
b8 platform_stop(Platform* platform);
b8 platform_pull_messages(Platform* platform);

EXPORT void* platform_allocate(u64 size, b8 is_aligned);
EXPORT void platform_free(void* block, b8 _is_aligned);
EXPORT void* platform_zero_memory(void* block, u64 size);
EXPORT void* platform_copy_memory(void* destination, const void* source, u64 size);
EXPORT void* platform_set_memory(void* block, i32 value, u64 size);

EXPORT void platform_print(const char* message, u8 color);
EXPORT void platform_printerr(const char* message, u8 color);


