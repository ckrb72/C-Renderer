#version 330 core
in vec2 fragment_tex_coords;
out vec4 gl_Color;
in vec3 fragment_position;

uniform sampler2D tex;

void main()
{
    gl_Color = texture(tex, fragment_tex_coords);
}