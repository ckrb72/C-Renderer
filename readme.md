# Graphics Renderer

Basic 2D renderer made for fun and learning purposes. Written completely in C using OpenGL as the graphics api and SDL2 for creating the window context. No sdl functions are used for graphics except for the ones
to create the valid opengl window and context. Some SDL2 functions are used for things such as keyboard states.

## Compilation - 

Everything in the dependencies folder should be linked to, as well as the SDL2 dll in the workspace directory.

To get started clone or fork the repository to a local directory on your computer.

If you are using vscode, set the default build task by pressing ctrl+shft+p and typing "Configure Default Build Task".

Choose gcc and go into the tasks.json file in your .vscode folder that was generated.

Here, you can add all of the flags and linker commands needed for the project. 

If you need to know specifically what to put here, just dm me.

Now, whenever you want to build the program, just hit ctrl+shft+b and it will automatically run the command specified in the tasks.json folder.

Might add makefiles later on but for now this is how we are going to do this.