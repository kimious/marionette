#pragma once

typedef struct GameConfig {
    i16 x;
    i16 y;
    i16 width;
    i16 height;
    char* name;
} GameConfig;

typedef struct Game {
    GameConfig config;
    void* state;
    
    b8 (*update)(struct Game* game_instance, f32 elapsed_time);
    b8 (*render)(struct Game* game_instance, f32 elapsed_time);
} Game;

extern b8 game_init(Game* game);