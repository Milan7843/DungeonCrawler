#version 460 core

out vec4 FragColor;

in vec2 textureCoords;

uniform sampler2D baseTexture;
uniform vec2 windowSize;

void main()
{
    FragColor = vec4(vec3(1.0f) - texture(baseTexture, textureCoords).rgb, 1.0);
}
