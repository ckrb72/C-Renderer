/*
		To-Do List:

		MOST IMPORTANT: 

		- Fix textures (for some reason the bottom get clipped and is wrapped around to the top)

		- Batch Renderer to cut back on draw calls

		- Complete animation system

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

#include "time/engine_time.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

bool should_quit = false;

Renderer state;

vec2 velocity = {0.5, 0.5};

int main(int argc, char* argv[])
{
	//Setup Render State
	//CG_Init();
	render_init(&state, WIN_WIDTH, WIN_HEIGHT);

	shader_init();

	Render_Rect face = rectangle_create((vec2){0, 0}, (vec2){720, 480});

	//Need to figure out if clips should use texture width and height to decide values or rectangles width and heights
	//Right now they're based off of the texture w and h

	texture_create(&face, "res/textures/Knight/Colour1/Outline/120x80_PNGSheets/_Attack2.png", CG_PNG);
	
	int pause = 0;

	int frame = 0;

	int x = 0;

	Render_Rect clips[10];

	for(int i = 0; i < 10; i++)
	{
		clips[i].w = 120;
		clips[i].h = 80;
		clips[i].pos[0] = x;
		clips[i].pos[1] = 0;

		x += 120;
	}

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

	//sets delta_time
	time_update(&state);

	//Need to add something like this to clean up main
	//input_handle(&state);

	if(state.input.space == KS_PRESSED)
		pause = !pause;
	
	if(state.input.escape == KS_PRESSED)
		should_quit = true;

	Render_Rect* currentClip = NULL;
	if(!pause)
	{
		currentClip = &clips[frame / 10];
		//clip.pos[0] += (face.width / 6);
	}

	render_clear();

	//Draw Objects

	//Maybe change the render_draw function to have it add the data to a buffer on the graphics card
	//Then, in the render_display function, have it execute the draw call.
	//This is probably how we'll implement the batch renderer.
	render_draw(&face, currentClip, CG_QUAD);
	
	//Swaps buffers to buffer where everything is rendered
	render_display(&state);

	frame++;

	if(frame / 10 >= 10)
	{
		frame = 0;
	}

	}

	//Create function that uninitializes everything
	//CG_Quit();

	SDL_Quit();
	
	return 0;
}
