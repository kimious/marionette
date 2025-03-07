#include <marionette.h>

// TODO: remove when memory management api is implemebnted 
#include <platform/platform.h>

typedef struct GameState {
    f32 elasped_time;
} GameState;

b8 game_update(Game* game, f32 elapsed_time);
b8 game_render(Game* game, f32 elapsed_time);

b8 game_init(Game* game) {
    game->config.x = 100;
    game->config.y = 100;
    game->config.width = 1280;
    game->config.height = 720;
    game->config.name = "marionette test";

    game->update = game_update; 
    game->render = game_render;

    game->state = platform_allocate(sizeof(game_render), false);

    return true;
}

b8 game_update(Game* game, f32 elapsed_time) {
    CAST(GameState*, state, game->state);
    state->elasped_time = elapsed_time;
    return true;
}

b8 game_render(Game* game, f32 elapsed_time) {
    CAST(GameState*, state, game->state);
    DEBUG("rendering game, time = %f", state->elasped_time);
    return true;
}