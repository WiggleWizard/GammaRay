#[vertex]
#version 450 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

out vec3 v_position;
out vec4 v_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    v_position = a_position;
    v_color = model * a_color;

    gl_Position = projection * view * model * vec4(a_position, 1.0);
    gl_Position = vec4(v_position, 1.0);
}

#[fragment]
#version 450 core

layout(location = 0) out vec4 color;

in vec3 v_position;
in vec4 v_color;

void main()
{
    color = vec4(v_position * 0.5 + 0.5, 1.0);
    color = v_color;
}
