#include <utils/logger.h>
#include <utils/asserts.h>

int main(void) {
    ENSURE_MSG(1==0, "jvc theorm");

    FATAL("Some fatal message: %d %s", 13, "march");
    ERROR("Some error message: %d %s", 13, "april");
    WARN("Some warn message: %d %s", 13, "may");
    INFO("Some info message: %d %s", 13, "june");
    DEBUG("Some debug message: %d %s", 13, "july");
    TRACE("Some trace message: %d %s", 13, "august");
    
    return 0;
}
