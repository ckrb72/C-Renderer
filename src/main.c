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
#include "engine/input/input.h"

#include <linmath.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

bool should_quit = false;

Game_State state;

vec2 velocity = {0.5, 0.5};

Key_State keyboard_input;
Key_State left_input;

int main(int argc, char* argv[])
{
	//Setup Render State
	render_init(&state, WIN_WIDTH, WIN_HEIGHT);

	//Create initial Renders of Objects
	Render_Rect rectangle = rectangle_create((vec2){WIN_WIDTH / 2, WIN_HEIGHT / 2}, (vec2){400, 400});
	Render_Rect test = rectangle_create((vec2){50, 50}, (vec2){100, 100});
	Render_Rect block1 = rectangle_create((vec2){150, 150}, (vec2){100, 100});


	//Create Textures
	texture_create(&rectangle, "./awesomeface.png", CG_PNG);
	texture_create(&block1, "./gapple.png", CG_PNG);

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

	input_update(&state);

	//Shows difference between pressed and held

	//Pressed only happens once
	if(state.input.left == KS_HELD)
		test.pos[0] -= 0.75;
	
	//Held happens continually each frame
	if(state.input.right == KS_HELD)
		test.pos[0] += 0.75;

	if(state.input.down == KS_HELD)
		test.pos[1] += 0.75;
	
	if(state.input.up == KS_HELD)
		test.pos[1] -= 0.75;

	//Temporary Keyboard Input Handling
	//Will eventually put this in api but just need to figure out how it works first

	if(state.input.escape == KS_PRESSED)
		should_quit = true;

	rectangle.pos[0] += velocity[0];
	rectangle.pos[1] += velocity[1];

	//IDK
	SDL_KeyboardEvent(keyboard);

	if(rectangle.pos[0] >= WIN_WIDTH - rectangle.width / 2 || rectangle.pos[0] <= rectangle.width / 2)
		velocity[0] *= -1;
	
	if(rectangle.pos[1] >= WIN_HEIGHT - rectangle.height / 2 || rectangle.pos[1] <= rectangle.height / 2)
		velocity[1] *= -1;

	render_clear();

	//Draw Objects
	render_draw(&rectangle);
	render_draw(&test);
	render_draw(&block1);


	//Swaps buffers to buffer where everything is rendered
	render_display(&state);

	}
	
	return 0;
}
