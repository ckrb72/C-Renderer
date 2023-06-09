/*
		To-Do List:
		- Finish IO System (Add config files and controller components)

		- Clean up the engine a little bit

		- Rework shaders a little bit so that entites that need common shaders reuse them rather than recompiling them each time, wasting
		memory on the gpu that could be saves fairly easily

		-FIX textures

*/

#include <stdio.h>
#include <glad/glad.h>
#include <stdbool.h>
#define SDL_MAIN_HANDELED
#include <SDL2/SDL.h>
#include <linmath.h>
#include <stdlib.h>
#include <time.h>

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

int main(int argc, char* argv[])
{
	//Setup Render State
	render_init(&state, WIN_WIDTH, WIN_HEIGHT);

	//Create initial Renders of Objects
	Render_Rect leftPaddle = rectangle_create((vec2){10, WIN_HEIGHT / 2}, (vec2){20, 100});
	Render_Rect rightPaddle = rectangle_create((vec2){WIN_WIDTH - 10, WIN_HEIGHT / 2}, (vec2){20, 100});

	texture_create(&leftPaddle, "./grass.png", CG_PNG);
	texture_create(&rightPaddle, "./grass.png", CG_PNG);

	srand(time(0));

	int x = rand() % 100;

	int y = rand() % 100;

	printf("X: %d, Y: %d\n", x, y);


	Render_Rect ball = rectangle_create((vec2){WIN_WIDTH / 2, WIN_HEIGHT / 2}, (vec2){20, 20});


	int pause = 0;

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

	if(state.input.space == KS_PRESSED)
		pause = !pause;
	
	if(state.input.escape == KS_PRESSED)
		should_quit = true;

	if(!pause)
	{
		if(leftPaddle.pos[1] > 50 && (state.input.up == KS_HELD || state.input.up == KS_PRESSED))
			leftPaddle.pos[1] -= 1.25;
		
		if(leftPaddle.pos[1] < (WIN_HEIGHT - 50) && (state.input.down == KS_HELD || state.input.up == KS_PRESSED))
			leftPaddle.pos[1] += 1.25;

		ball.pos[0] += velocity[0];
		ball.pos[1] += velocity[1];

		if(ball.pos[0] >= WIN_WIDTH - 10 || ball.pos[1] <= 10)
		{
			velocity[0] *= -1;
		}

		if(ball.pos[1] >= WIN_HEIGHT - 10 || ball.pos[1] <= 10)
			velocity[1] *= -1;
	}

	render_clear();

	//Draw Objects
	render_draw(&leftPaddle);
	render_draw(&rightPaddle);

	render_draw(&ball);
	//Swaps buffers to buffer where everything is rendered
	render_display(&state);

	}
	
	return 0;
}
