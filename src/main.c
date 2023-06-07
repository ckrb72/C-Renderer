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
#include "engine/texture/texture.h"
#include <linmath.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

bool should_quit = false;

Game_State state;

vec2 velocity = {0.5, 0.5};

int main(int argc, char* argv[])
{
	//Setup Render State
	render_init(&state, WIN_WIDTH, WIN_HEIGHT);

	Entity gapple = entity_create((vec2){state.render.width / 2, state.render.height / 2}, (vec2){200, 200});

	texture_create(&gapple, "./gapple.png", CG_PNG);

	entity_set_scale(&gapple, (vec2){50, 50});

	Entity grass_blocks[8];

	Texture grass_texture = texture_load("./grass.png", CG_PNG);

	for(int i = 0; i < sizeof(grass_blocks) / sizeof(Entity); i++)
	{
		grass_blocks[i] = entity_create((vec2){50 + (i * 100), WIN_HEIGHT - 50}, (vec2){100, 100});
		shader_set(&grass_blocks[i], gapple.shader);
		texture_set(&grass_blocks[i], grass_texture);
	}


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

	if(gapple.pos[0] >= WIN_WIDTH - 20 || gapple.pos[0] <= 20)
		velocity[0] *= -1;
	
	if(gapple.pos[1] >= WIN_HEIGHT -120 || gapple.pos[1] <= 20)
		velocity[1] *= -1;
	
	gapple.pos[0] += velocity[0];
	gapple.pos[1] += velocity[1];

	render_clear();

	render_draw(&gapple);

	for(int i = 0; i < sizeof(grass_blocks) / sizeof(Entity); i++)
	{
		render_draw(&grass_blocks[i]);
	}

	//Swaps buffers to buffer where everything is rendered
	render_display(&state);

	}

	texture_delete(&gapple.texture);
	
	return 0;
}
