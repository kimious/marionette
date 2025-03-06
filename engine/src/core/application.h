#pragma once

#include "defines.h"
#include "platform/platform.h"
#include "core/game.h"

typedef struct Application {
    Game* game;
    Platform platform;
    b8 is_running;
    b8 is_suspended;
} Application;

EXPORT b8 application_init(Application* application, Game* game);

EXPORT b8 application_start_loop(Application* application);