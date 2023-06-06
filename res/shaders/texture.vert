#version 330 core
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 vertex_tex_coords;

out vec2 fragment_tex_coords;
out vec3 fragment_position;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position = projection * model * vec4(a_pos, 1.0);
    fragment_tex_coords = vertex_tex_coords;
    fragment_position = a_pos;
}