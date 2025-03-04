#include "logger.h"
#include "asserts.h"
#include "platform/platform.h"

// TODO: temporary, remove when logger is finished
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

b8 start_logger() {
    // TODO: create the log file in fs
    return TRUE;
}

void stop_logger() {
    // TODO: flush log messages
}

void log_message(log_level level, const char* message, ...) {
    local const char* level_codes[6] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE"};

    b8 is_error = level < LOG_LEVEL_WARN;

    char pre_out[32000];
    memset(pre_out, 0, sizeof(pre_out));

    __builtin_va_list args;
    va_start(args, message);
    vsnprintf(pre_out, sizeof(pre_out), message, args);
    va_end(args);

    char out[32000];
    sprintf(out, "[%s]: %s\n", level_codes[level], pre_out);
    
    if (is_error) {
        platform_printerr(out, level);
    } else {
        platform_print(out, level);
    }
}


void fail(const char* expression, const char* message, const char* file, i32 line) {
    FATAL("failed asserting %s, %s (%s:%d)", expression, message, file, line);
}