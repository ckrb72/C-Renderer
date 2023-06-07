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

	entity = entity_create((vec2){state.render.width / 2, state.render.height / 2}, (vec2){200, 200});
	
	entity.shader = shader_compile("./res/shaders/texture.vert", "./res/shaders/texture.frag");

	entity.texture = texture_load("./container.jpg", CG_JPG);

	entity_set_scale(&entity, (vec2){400, 400});

	Entity e2 = entity_create((vec2){state.render.width / 2, state.render.height / 2}, (vec2){200, 200});

	e2.shader = entity.shader;

	e2.texture = texture_load("./awesomeface.png", CG_PNG);

	entity_set_scale(&e2, (vec2){400, 400});

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	render_draw(&e2);

	//Swaps buffers to buffer where everything is rendered
	render_display(&state);

	}

	texture_delete(&entity.texture);
	texture_delete(&e2.texture);
	shader_delete(entity.shader);
	shader_delete(entity2.shader);
	
	return 0;
}
