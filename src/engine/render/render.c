#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif

#include <linmath.h>

#include "render.h"
#include "render_internal.h"

#include "../engine_state.h"

#include <stdio.h>

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//Prototypes of render functions
static void render_quad(void* data, void* clip);
static void render_circle(void* data, void* clip);

//Array of function pointers to render functions
static void (*func_ptr_arr[3])(void* data, void* clip) = {0, render_quad, render_circle};

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//Buffers

//Want to put the static buffer in here so the quad struct doesn't need to know anything about buffers at all
//This way we can just have a position, size, texture, and shader and not have to keep a reference to the buffer in the actual struct itself
//Buffer for quads
//static buffer_t quad_buffer = {0};


typedef struct
{
    unsigned int vao, vbo, ebo;

    unsigned int uv;

    unsigned int index_size;
}buffer_t;

static buffer_t quad_buffer = {0};

static buffer_t buffer_init(float* vertexBuffer, unsigned int vertexSize, unsigned int* elementBuffer, unsigned int elementSize);

static void quad_buffer_init();

//Only generates Quad uv's at this point. Might have to change later
static void gen_quad_uv(Render_Rect* quad, Render_Rect* clip);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//Main render functions

//Initializes the render state
int render_init(Renderer* state, float width, float height)
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

    quad_buffer_init();

    return 0;
}

//Draws the entity given to the screen
void render_draw(void* data,void* clip, Render_Type type)
{
    //Indexes into the function pointer array, "dereferencing", or calling, the function at the index given by the type
    (*func_ptr_arr[type])(data, clip);
}

//Swaps the buffer, displaying what was just drawn to the screen using render_draw()
void render_display(Renderer* state)
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


//Individual Render Functions
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


//OpenGL calls for rendering a rectangle
static void render_quad(void* data, void* clip)
{

    Render_Rect* entity = (Render_Rect*)data;

    if(clip)
        gen_quad_uv(entity, (Render_Rect*)clip);
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
    mat4x4_scale_aniso(model, model, entity->w, entity->h, 1);

    glUniformMatrix4fv(glGetUniformLocation(entity->shader, "model"), 1, GL_FALSE, &model[0][0]);

    //Binds the VAO so all the buffer data is loaded
    glBindVertexArray(quad_buffer.vao);

    //Draws the entity
    glDrawElements(GL_TRIANGLES, quad_buffer.index_size, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

//OpenGL calls for rendering a circle
static void render_circle(void* data, void* clip)
{
    printf("NOT IMPLEMENTED YET\n");
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//Buffer Initialization Functions

static buffer_t buffer_init(float* vertexBuffer, unsigned int vertexSize, unsigned int* elementBuffer, unsigned int elementSize)
{
    buffer_t buffer = {0};

    glGenVertexArrays(1, &buffer.vao);
    glGenBuffers(1, &buffer.vbo);
    glGenBuffers(1, &buffer.ebo);

    glBindVertexArray(buffer.vao);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertexBuffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementSize, elementBuffer, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    buffer.index_size = elementSize;

    return buffer;
}

static void quad_buffer_init()
{

    //Might want to change this back to what it normally was
    //For some reason moving feels weird now but might just be a placebo
    float vertices[] = 
    {
        0.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0,
        0.0, 1.0, 0.0
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    quad_buffer = buffer_init(vertices, sizeof(vertices), indices, sizeof(indices));

    
    //The x coords work fine but the y coords are flipped vertically because of the way
    //stbi loads images. It puts the [0][0] in the top left corner instead of the bottom
    //left corner how opengl expects it to be. So we could either flip the pixels, which is
    //expensive, figure out how to load the images ourselves, which is time consuming,
    //or just keep in mind that our engine loads the images upside down and we need to convert
    //that back to the correct uv, which is what we're going to do.

    /*
        STBI_IMAGE:
        [0][0], [1][0], [2][0], ...
        .
        .
        .

        vs.
        
        OPENGL:
        .
        .
        .
        .
        [0][0], [1][0], [2][0], ...
    */

    float texCoords[] = 
    {
        0.0, 1.0,
        1.0, 1.0,
        1.0, 0.0,
        0.0, 0.0
    };

    glBindVertexArray(quad_buffer.vao);

    glGenBuffers(1, &quad_buffer.uv);
    glBindBuffer(GL_ARRAY_BUFFER, quad_buffer.uv);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

//Need to make it so that it only effects the quad currently being worked on. So maybe have each quad hold a
//uv buffer? Would need to think about how to do this efficiently
static void gen_quad_uv(Render_Rect* quad, Render_Rect* clip)
{
 
    float uv[] =
    {
        clip->pos[0] / quad->texture.w, 1 - (clip->pos[1] / quad->texture.h),
        (clip->pos[0] + clip->w) / quad->texture.w, 1 - (clip->pos[1] / quad->texture.h),
        (clip->pos[0] + clip->w) / quad->texture.w, 1 - ((clip->pos[1] + clip->h) / quad->texture.h),
        clip->pos[0] /  quad->texture.w, 1 - ((clip->pos[1] + clip->h) / quad->texture.h)
    };

    //This works if you do the clip width and height based off of the quad (ex. Quad is (200, 200), clip would be (50, 50) for a quarter of the quad)
    /*float uv[] =
    {
        clip->pos[0] / quad->w, (1 - clip->pos[1]) / quad->h,
        (clip->pos[0] + clip->w) / quad->w, (1 - clip->pos[1]) / quad->h,
        (clip->pos[0] + clip->w) / quad->w, (1 - (clip->pos[1] + clip->h)) / quad->h,
        clip->pos[0] /  quad->w, (1 - (clip->pos[1] + clip->h)) / quad->h
    };*/

    glBindBuffer(GL_ARRAY_BUFFER, quad_buffer.uv);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_DYNAMIC_DRAW);

}