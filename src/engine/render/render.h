#pragma once
#include <SDL2/SDL.h>
#include "../game_state.h"
#include "../entity/entity.h"

int render_init(Game_State* state, float width, float height);
void render_display(Game_State* state);
void render_clear();

void render_draw(Entity* entity);