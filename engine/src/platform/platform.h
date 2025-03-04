#pragma once

#include "defines.h"

typedef struct platform_state {
    void* internal_state;
} platform_state;

EXPORT b8 platform_start(platform_state* state, const char* name, i32 x, i32 y, i32 width, i32 height);
EXPORT b8 platform_stop(platform_state* state);
EXPORT b8 platform_pull_messages(platform_state* state);

EXPORT void* platform_alloc(u64 size, b8 is_aligned);
EXPORT void platform_free(void* block, b8 _is_aligned);
EXPORT void* platform_zero_memory(void* block, u64 size);
EXPORT void* platform_copy_memory(void* destination, const void* source, u64 size);
EXPORT void* platform_set_memory(void* block, i32 value, u64 size);

EXPORT void platform_print(const char* message, u8 color);
EXPORT void platform_printerr(const char* message, u8 color);


