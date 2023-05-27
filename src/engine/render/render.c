#include <glad/glad.h>
#include <linmath.h>

#include "render.h"
#include "render_internal.h"

#include "../game_state.h"

#include <stdio.h>


int render_init(Game_State* state, float width, float height)
{
    state->render.height = height;
    state->render.width = width;
    state->render.window = render_init_window(width, height);
}

void render_draw(Entity* entity)
{
    glUseProgram(entity->shader);

    //Need to make it so any projection matrix and model matrix can be used
    mat4x4 projection;

	mat4x4_ortho(projection, 0, 800, 600, 0, -2, 2);
	glUniformMatrix4fv(glGetUniformLocation(entity->shader, "projection"), 1, GL_FALSE, &projection[0][0]);

    mat4x4 model;

    mat4x4_translate(model, entity->pos[0], entity->pos[1], 0);
    mat4x4_scale_aniso(model, model, 200, 200, 1);

    glUniformMatrix4fv(glGetUniformLocation(entity->shader, "model"), 1, GL_FALSE, &model[0][0]);

    glBindVertexArray(entity->buffer.vao);
    glDrawElements(GL_TRIANGLES, entity->buffer.index_size, GL_UNSIGNED_INT, 0);


    glBindVertexArray(0);
}

void render_display(Game_State* state)
{
    SDL_GL_SwapWindow(state->render.window);
}

void render_clear()
{
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}