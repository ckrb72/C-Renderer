/*
		To-Do List:
		- Possibly rework the way entities work. As of right now they don't really make sense from a rendering perspective
		and aren't general enough to really render anything
			Might want to rethink the whole "entity" thing and reframe it more as a storage for buffers rather than an individual entity
		
		- Create IO system. SDL has it's own keyboard and mouse system but might be beneficial to make own

		- Clean up the engine a little bit

		- Rework shaders a little bit so that entites that need common shaders reuse them rather than recompiling them each time, wasting
		memory on the gpu that could be saves fairly easily

		- Change Entity struct to Render_Rect to make it more in line with what it is doing (I abstracted away too much and essentially made a game rather than a renderer)

		-FIX textures

*/

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

	texture_create(&gapple, "./awesomeface.png", CG_PNG);

	entity_set_scale(&gapple, (vec2){50, 50});

	Entity grass_blocks[8];

	Texture grass_texture = texture_load("./grass.png", CG_PNG);

	for(int i = 0; i < sizeof(grass_blocks) / sizeof(Entity); i++)
	{
		grass_blocks[i] = entity_create((vec2){50 + (i * 100), WIN_HEIGHT - 50}, (vec2){100, 100});
		shader_set(&grass_blocks[i], gapple.shader);
		texture_set(&grass_blocks[i], grass_texture);
	}

	Entity leftrectangel = entity_create((vec2){10, state.render.height / 2 -50}, (vec2){20, 100});

	leftrectangel.shader=shader_compile("./res/shaders/line.vert", "./res/shaders/line.frag");

	Entity rightranlgec = entity_create((vec2){state.render.width -10, state.render.height / 2 -50}, (vec2){20, 100});

	rightranlgec.shader=leftrectangel.shader;

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
		int leftrectangeltop = leftrectangel.pos[1]+10;
		int leftrectangelbot = leftrectangel.pos[1]-10;

		int rightrectangeltop = rightranlgec.pos[1]+10;
		int rightrectangelbot = rightranlgec.pos[1]-10;

	
	//Need to fix collisions
	if(gapple.pos[0] >= leftrectangel.pos[0] - 10 && gapple.pos[0] <= leftrectangel.pos[0] + 10 && gapple.pos[1] >= leftrectangel.pos[1] - 50 && gapple.pos[1] <= leftrectangel.pos[1] + 50)
	{
		gapple.pos[0] = leftrectangel.pos[0];
		velocity[1] *= -1;
	}
	
	if(gapple.pos[0] >= rightranlgec.pos[0] - 10 && gapple.pos[0] <= rightranlgec.pos[0] + 10 && gapple.pos[1] >= rightranlgec.pos[1] - 50 && gapple.pos[1] <= rightranlgec.pos[1] + 50)
	{
		gapple.pos[0] = rightranlgec.pos[0];
		velocity[1] *= -1;
	}


	if(gapple.pos[1] >= WIN_HEIGHT -120 || gapple.pos[1] <= 20)
		velocity[1] *= -1;
	
	gapple.pos[0] += velocity[0];
	gapple.pos[1] += velocity[1];

	render_clear();

	render_draw(&gapple);

	//Probably would want to batch render this but don't know how to make the vbo dynamic at this point
	for(int i = 0; i < sizeof(grass_blocks) / sizeof(Entity); i++)
	{
		render_draw(&grass_blocks[i]);
	}

	render_draw(&leftrectangel);
	render_draw(&rightranlgec);

	//Swaps buffers to buffer where everything is rendered
	render_display(&state);

	}

	texture_delete(&gapple.texture);
	texture_delete(&grass_blocks[0].texture);
	
	return 0;
}
