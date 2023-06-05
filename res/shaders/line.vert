#version 330 core
layout(location = 0) in vec3 v_Position;
out vec3 g_Position;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position = projection * model * vec4(v_Position, 1.0);
    g_Position = v_Position;
}