#version 460 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position = projection * vec4(position, 0.0, 1.0);
    TexCoords = uv;
}