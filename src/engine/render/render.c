#include <glad/glad.h>
#include <linmath.h>

#include "render.h"
#include "render_internal.h"

#include "../game_state.h"

#include <stdio.h>

//Initializes the render state
int render_init(Game_State* state, float width, float height)
{
    state->render.height = height;
    state->render.width = width;
    state->render.window = render_init_window(width, height);
    
    //Might not want to put this here. Don't really know right now.
    //Possibly could have each entity store it in a material struct along with the other uniforms it has
    //So could also put the model matrix in there and upadte it every time the scale or position is updated instead.
    mat4x4_ortho(state->render.projection, 0, state->render.width, state->render.height, 0, -2, 2);

    //So PNG's can have transparent backgrounds
    //MUST BE CALLED AFTER render_init_window AS OTHERWISE OPENGL CONTEXT ISN'T SET UP
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//Draws the entity given to the screen
void render_draw(Render_Rect* entity)
{
    //Uses the entity's shader
    glUseProgram(entity->shader);

    if(entity->texture.gl_texture != 0)
        glBindTexture(GL_TEXTURE_2D, entity->texture.gl_texture);

    //Need to make it so any projection matrix and model matrix can be used
    mat4x4 projection;

    //Creates orthographic projection matrix and sends it to the shader
	mat4x4_ortho(projection, 0, 800, 600, 0, -2, 2);
	glUniformMatrix4fv(glGetUniformLocation(entity->shader, "projection"), 1, GL_FALSE, &projection[0][0]);

    mat4x4 model;

    //Creates the model matrix, translates it to the position and scales it then send it to the shader
    mat4x4_translate(model, entity->pos[0], entity->pos[1], 0);
    mat4x4_scale_aniso(model, model, entity->width, entity->height, 1);

    glUniformMatrix4fv(glGetUniformLocation(entity->shader, "model"), 1, GL_FALSE, &model[0][0]);

    //Binds the VAO so all the buffer data is loaded
    glBindVertexArray(entity->buffer->vao);

    //Draws the entity
    glDrawElements(GL_TRIANGLES, entity->buffer->index_size, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

//Swaps the buffer, displaying what was just drawn to the screen using render_draw()
void render_display(Game_State* state)
{
    SDL_GL_SwapWindow(state->render.window);
}

//Clears the color buffer and sets the background color
//Gets the renderer ready for the next frame (Want to call at the beginning of each frame)
void render_clear()
{
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}