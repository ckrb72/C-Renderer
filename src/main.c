#include <stdio.h>
#include <glad/glad.h>
#include <stdbool.h>
#define SDL_MAIN_HANDELED
#include <SDL2/SDL.h>
#include <linmath.h>
#include <stdlib.h>

#include "engine/game_state.h"
#include "engine/render/render.h"
#include "engine/shader/shader.h"

#include <linmath.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

bool should_quit = false;

Game_State state;

Entity entity;

Entity entity2;

int main(int argc, char* argv[])
{
	//Setup Render State
	render_init(&state, WIN_WIDTH, WIN_HEIGHT);

	Entity entity;

	entity = create_entity((vec2){state.render.width / 2, state.render.height / 2});

	entity2 = create_entity((vec2){0, 0});
	

	//poll events
	while(!should_quit)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					should_quit = true;
					break;
				default:
					break;
			}
		}

	entity.pos[0] += 1;
	entity.pos[1] += 1;

	entity2.pos[0] += 1;
	entity2.pos[1] += 1;

	render_clear();

	//Doesn't work right now for some reason. Need to debug this
	render_draw(&entity);

	render_draw(&entity2);

	//Swaps buffers to buffer where everything is rendered
	render_display(&state);

	}

	shader_delete(entity.shader);
	shader_delete(entity2.shader);
	
	return 0;
}
