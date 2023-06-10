#include "../../engine/engine.h"


int should_quit = 0;

Renderer state = {0};

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

int main()
{
    printf("Hello World!\n");

    render_init(&state, WIN_WIDTH, WIN_HEIGHT);

    while(!should_quit)
    {

        //This should be in input_handle() when implemented
        SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					should_quit = 1;
					break;
				default:
					break;
			}
		}

        input_update(&state);

        render_clear();

        render_display(&state);
    }
}