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

	Render_Rect face = rectangle_create((vec2){(WIN_WIDTH / 2) - 60, (WIN_HEIGHT / 2) - 40}, (vec2){120, 80});

	//Need to figure out if clips should use texture width and height to decide values or rectangles width and heights
	//Right now they're based off of the texture w and h
	Render_Rect clip = rectangle_create((vec2){0,0}, (vec2){720, 80});

	texture_create(&face, "res/textures/Knight/Colour1/Outline/120x80_PNGSheets/_Attack2.png", CG_PNG);

	printf("Width: %u\n", face.texture.w);
	printf("Height: %u\n", face.texture.h);

	int pause = 0;

	int frame = 0;

	int run_frame = 0;

	int x = 0;

	Render_Rect clips[6];

	for(int i = 0; i < 6; i++)
	{
		clips[i].w = 120;
		clips[i].h = 80;
		clips[i].pos[0] = x;
		clips[i].pos[1] = 0;

		x += 120;
	}

	Render_Rect run_anim = rectangle_create((vec2){0, 0}, (vec2){120, 80});

	texture_create(&run_anim, "res/textures/Knight/Colour1/Outline/120x80_PNGSheets/_Run.png", CG_PNG);

	Render_Rect run_anim_clip[10];

	x = 0;

	for(int i = 0; i < 10; i++)
	{
		run_anim_clip[i].w = 120;
		run_anim_clip[i].h = 80;
		run_anim_clip[i].pos[0] = x;
		run_anim_clip[i].pos[1] = 0;

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
	Render_Rect* runCurrentClip = NULL;
	if(!pause)
	{
		currentClip = &clips[frame / 6];
		runCurrentClip = &run_anim_clip[run_frame / 10];

		if(state.input.right == KS_PRESSED || state.input.right == KS_HELD)
			run_anim.pos[0] += 1.0;
		if(state.input.left == KS_PRESSED || state.input.left == KS_HELD)
			run_anim.pos[0] -= 1.0;
		if(state.input.down== KS_PRESSED || state.input.down == KS_HELD)
			run_anim.pos[1] += 1.0;
		if(state.input.up == KS_PRESSED || state.input.up == KS_HELD)
			run_anim.pos[1] -= 1.0;
	}

	render_clear();

	//Draw Objects

	//Maybe change the render_draw function to have it add the data to a buffer on the graphics card
	//Then, in the render_display function, have it execute the draw call.
	//This is probably how we'll implement the batch renderer.

	//If you render this with the clip, then the uv's get changed for all textures to be rendered after this because of the use
	//of the static quad_buffer struct in render.c
	//Might need to makes this so that all the different quads have their own uv's in their texture struct
	render_draw(&face, currentClip, CG_QUAD);

	render_draw(&run_anim, runCurrentClip, CG_QUAD);
	
	//Swaps buffers to buffer where everything is rendered
	render_display(&state);

	frame++;
	run_frame++;

	if(run_frame / 10 >= 10)
	{
		run_frame = 0;
	}

	if(frame / 6 >= 6)
	{
		frame = 0;
	}

	}

	//Create function that uninitializes everything
	//CG_Quit();

	SDL_Quit();
	
	return 0;
}
