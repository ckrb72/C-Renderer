/*
		To-Do List:

		MOST IMPORTANT: 
		- Batch Renderer to cut back on draw calls

		- Get Camera working so can move around the world

		- Add ECS system for managing entities. Might want to put this in a game rather than the renderer

		- Document API


		LESS IMPORTANT:
		- Add Benchmarking to see why so much cpu is being used up		

		- Finish IO System (Add config files and controller components)

		- Clean up the engine a little bit

		- FIX textures and add support for multiple textures

		- Create Controller functionality that allows for multiple configs for multiple players

		- Add wireframe viewer

		- Add UI and debug information

		- Maybe add circles

*/

#include <stdio.h>
#include <stdbool.h>

//Main headerfile for engine
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

	Render_Rect face = rectangle_create((vec2){(WIN_WIDTH / 2) - 50, (WIN_HEIGHT / 2) - 50}, (vec2){100, 100});

	texture_create(&face, "./res/textures/awesomeface.png", CG_PNG);

	//Need to make clipping rect somehow and upload it with correct uv coords

	int pause = 0;

	Render_Rect clip = rectangle_create((vec2){0,0}, (vec2){50, 50});

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
		if((state.input.left == KS_HELD || state.input.left ==  KS_PRESSED))
			face.pos[0] -= 10;
		
		if((state.input.right == KS_HELD || state.input.right == KS_PRESSED))
			face.pos[0] += 10;

		if((state.input.up == KS_HELD || state.input.up == KS_PRESSED))
			face.pos[1] -= 10;
			
		if((state.input.down == KS_HELD || state.input.down == KS_PRESSED))
			face.pos[1] += 10;

		clip.pos[0] += velocity[0];
		clip.pos[1] += velocity[1];
	
	}

	render_clear();

	//Draw Objects

	render_draw(&face, &clip, CG_QUAD);
	
	//Swaps buffers to buffer where everything is rendered
	render_display(&state);

	}
	
	return 0;
}
