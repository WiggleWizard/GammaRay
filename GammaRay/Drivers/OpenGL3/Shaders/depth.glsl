#[vertex]
#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

out vec3 v_position;
out vec4 v_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#[fragment]
#version 450 core
out vec4 FragColor;

float near = 0.1; 
float far  = 5.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{             
    float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    FragColor = vec4(vec3(depth), 1.0);
}
