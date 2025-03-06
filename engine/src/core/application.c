#include "application.h"

#include "utils/logger.h"
#include "utils/asserts.h"
#include "platform/platform.h"

b8 application_init(Application* application, Game* game) {
    application->game = game;

    application->is_running = TRUE;
    application->is_suspended = FALSE;
    
    logger_start();    

    FATAL("Some fatal message: %d %s", 13, "march");
    ERROR("Some error message: %d %s", 13, "april");
    WARN("Some warn message: %d %s", 13, "may");
    INFO("Some info message: %d %s", 13, "june");
    DEBUG("Some debug message: %d %s", 13, "july");
    TRACE("Some trace message: %d %s", 13, "august");
    
    ENSURE_MSG(1==1, "should never fail");

    if (!platform_start(
        &application->platform, 
        game->config.name, 
        game->config.x, 
        game->config.y, 
        game->config.width, 
        game->config.height
    )) {
        ERROR("failed starting up platform");
        return FALSE;
    }

    return TRUE;
}

b8 application_start_loop(Application* application) {
    while(application->is_running) {
        platform_pull_messages(&application->platform);

        if (!application->game->update(application->game, 13.0)) {
            FATAL("Could not update the game state");
            application->is_running = FALSE;
            break;
        }

        if (!application->game->render(application->game, 13.0)) {
            FATAL("COuld not render the game state");
            application->is_running = FALSE;
            break;
        }
    }

    platform_stop(&application->platform);

    logger_stop();

    return TRUE;
}