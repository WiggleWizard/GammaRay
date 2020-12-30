#[vertex]
#version 450 core

layout(location = 0) in vec3 a_position;

out vec3 v_position;

void main()
{
    v_position = a_position;
    gl_Position = vec4(v_position, 1.0);
}

#[fragment]
#version 450 core

layout(location = 0) out vec4 color;

in vec3 v_position;

void main()
{
    color = vec4(v_position * 0.5 + 0.5, 1.0);
}
