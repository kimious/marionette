#pragma once

#include "defines.h"

#define MASSERTIONS_ENABLED

#ifdef MASSERTIONS_ENABLED

#include <intrin.h>
EXPORT void fail(const char* expression, const char* message, const char* file, i32 line);
#define ENSURE(expr)                                                    \
    {                                                                   \
        if(expr) {                                                      \
        } else {                                                        \
            fail(#expr, "", __FILE__, __LINE__);                        \
            __debugbreak();                                             \
        }                                                               \
    }                                                                   \

#define ENSURE_MSG(expr, message)                                       \
    {                                                                   \
        if(expr) {                                                      \
        } else {                                                        \
            fail(#expr, message, __FILE__, __LINE__);                   \
            __debugbreak();                                             \
        }                                                               \
    }                                                                   \

#ifdef _DEBUG
#define ENSURE_DEBUG(expr)                                              \
    {                                                                   \
        if(expr) {                                                      \
        } else {                                                        \
            fail(#expr, "", __FILE__, __LINE__);                        \
            __debugbreak();                                             \
        }                                                               \
    }  
#else
#define ENSURE_DEBUG(expr)
#endif

#else
#define ENSURE(expr)
#define ENSURE_MSG(expr)
#define ENSURE_DEBUG(expr)
#endif