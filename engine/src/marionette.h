#include "core/application.h"
#include "utils/logger.h"
#include "utils/asserts.h"
#include "utils/cast.h"

#define GAME_INIT_ERROR -1
#define GAME_UNIMPLEMENTED_ERROR -2
#define APPLICATION_INIT_ERROR -3
#define APPLICATION_START_ERROR -4

int main() {
    Application application;
    Game game;
    
    if (!game_init(&game)) {
        FATAL("Could not init game instance");
        return GAME_INIT_ERROR;
    }

    if (!game.update || !game.render) {
        FATAL("Undefined game methods");
        return GAME_UNIMPLEMENTED_ERROR;
    }

    if (!application_init(&application, &game)) {
        FATAL("Coult not init application");
        return APPLICATION_INIT_ERROR;
    }
    
    if (!application_start_loop(&application)){
        FATAL("Could not start application");
        return APPLICATION_START_ERROR;
    }   
}