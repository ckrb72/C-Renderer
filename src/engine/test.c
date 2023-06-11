/*
		To-Do List:
		
		- Get Camera working so can move around the world

		- Finish IO System (Add config files and controller components)

		- Clean up the engine a little bit

		- Rework shaders a little bit so that entites that need common shaders reuse them rather than recompiling them each time, wasting
		memory on the gpu that could be saves fairly easily

		- FIX textures and add support for multiple textures

		- Create Controller functionality that allows for multiple configs for multiple players

		- Add wireframe viewer

		- Add UI and debug information

		- Maybe add circles

		- Document API

*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "engine.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

bool should_quit = false;

Renderer state;

vec2 velocity = {0.5, 0.5};

int main(int argc, char* argv[])
{
	//Setup Render State
	render_init(&state, WIN_WIDTH, WIN_HEIGHT);

	shader_init();

	Render_Rect box = rectangle_create((vec2){WIN_WIDTH / 2, WIN_HEIGHT / 2}, (vec2){100, 100});

	Render_Rect image = rectangle_create((vec2){WIN_WIDTH / 2, WIN_HEIGHT / 2}, (vec2){100, 100});

	texture_create(&image, "./res/textures/awesomeface.png", CG_PNG);

	int pause = 0;

	//poll events
	while(!should_quit)
	{

		//This should be in input_handle when implemented
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

	//Need to add something like this to clean up main
	//input_handle(&state);

	if(state.input.space == KS_PRESSED)
		pause = !pause;
	
	if(state.input.escape == KS_PRESSED)
		should_quit = true;

	if(!pause)
	{
		if(box.pos[0] > box.width / 2 && (state.input.left == KS_HELD || state.input.left ==  KS_PRESSED))
			box.pos[0] -= 1.75;
		
		if(box.pos[0] < WIN_WIDTH - (box.width / 2) && (state.input.right == KS_HELD || state.input.right == KS_PRESSED))
			box.pos[0] += 1.75;

		if(box.pos[1] > box.height / 2 && (state.input.up == KS_HELD || state.input.up == KS_PRESSED))
			box.pos[1] -= 1.75;
			
		if(box.pos[1] < WIN_HEIGHT - (box.height / 2) && (state.input.down == KS_HELD || state.input.down == KS_PRESSED))
			box.pos[1] += 1.75;
		
		image.pos[0] += velocity[0];
		image.pos[1] += velocity[1];

		if(image.pos[0] < image.width / 2 || image.pos[0] > WIN_WIDTH - (image.width / 2))
			velocity[0] *= -1;
		
		if(image.pos[1] < image.height / 2 || image.pos[1] > WIN_HEIGHT - (image.width / 2))
			velocity[1] *= -1;
	}

	render_clear();

	//Draw Objects
	render_draw(&box, CG_QUAD);
	render_draw(&image, CG_QUAD);
	
	//Swaps buffers to buffer where everything is rendered
	render_display(&state);

	}
	
	return 0;
}
