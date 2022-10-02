#version 460 core

out vec4 FragColor;

in vec2 textureCoords;

uniform sampler2D baseTexture;

void main()
{
    FragColor = vec4(1.-texture(baseTexture, textureCoords).rgb, 1.0);
}
