#include <utils/logger.h>
#include <utils/asserts.h>
#include <platform/platform.h>

int main(void) {
    FATAL("Some fatal message: %d %s", 13, "march");
    ERROR("Some error message: %d %s", 13, "april");
    WARN("Some warn message: %d %s", 13, "may");
    INFO("Some info message: %d %s", 13, "june");
    DEBUG("Some debug message: %d %s", 13, "july");
    TRACE("Some trace message: %d %s", 13, "august");
    
    ENSURE_MSG(1==1, "should never fail");

    platform_state state;
    if (platform_start(&state, "Marionette Test", 300, 300, 1280, 720)) {
        while(TRUE) {
            platform_pull_messages(&state);
        }
    }
    platform_stop(&state);

    return 0;
}
