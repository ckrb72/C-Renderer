#pragma once
#include "../engine_state.h"

static unsigned long previous = 0;
static unsigned long current = 0;

void time_update(Renderer* renderer)
{
    current = SDL_GetTicks64();
    renderer->delta_time = (current - previous) / 1000.0f;
    previous = current;
}