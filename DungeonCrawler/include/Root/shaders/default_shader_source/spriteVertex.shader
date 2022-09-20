#version 460 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 model;

uniform float renderDepth;

void main()
{
    // Screen position
    gl_Position = projection * model * vec4(position, 0.0, 1.0);
    // Depth
    gl_Position.z = renderDepth;
    TexCoords = uv;
}