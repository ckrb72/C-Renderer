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

Entity entity;

Entity entity2;

int main(int argc, char* argv[])
{
	//Setup Render State
	render_init(&state, WIN_WIDTH, WIN_HEIGHT);

	Entity entity;

	entity = create_entity((vec2){state.render.width / 2, state.render.height / 2});
	
	entity.shader = shader_compile("./res/shaders/texture.vert", "./res/shaders/texture.frag");

	//FIXME: BEWARE
	//texture_load won't work with png's yet because I haven't added GL_RGBA yet to the function but will do that soon.
	entity.texture = texture_load("./container.jpg", CG_JPG);

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

	entity.pos[0] += 0.5;
	entity.pos[1] += 0.5;

	render_clear();

	//Doesn't work right now for some reason. Need to debug this
	render_draw(&entity);

	//Swaps buffers to buffer where everything is rendered
	render_display(&state);

	}

	shader_delete(entity.shader);
	shader_delete(entity2.shader);
	
	return 0;
}
