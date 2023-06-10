#shader vertex
#version 330 core
layout(location = 0) in vec3 v_pos;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position = projection * model * vec4(v_pos, 1.0);
}

#shader fragment
#version 330 core

out vec4 gl_Color;

void main()
{
    gl_Color = vec4(1.0, 0.0, 1.0, 1.0);
}