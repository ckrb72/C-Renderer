#version 330 core

out vec4 gl_Color;
in vec3 g_Position;

void main()
{
    gl_Color = vec4(g_Position, 1.0);
}