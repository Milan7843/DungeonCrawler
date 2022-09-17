#include "Image.h"

#include "SimpleGUI.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stbi_image.h>

SimpleGUIComponent::Image::Image(const char* imagePath,
	unsigned int windowWidth, unsigned int windowHeight,
    glm::vec2 position, glm::vec2 size, glm::vec2 scale)
    : SimpleGUIComponent::Rectangle(windowWidth, windowHeight, position, size, scale)
{
	float aspectRatio{ loadImage(imagePath) };
}

SimpleGUIComponent::Image::Image(const char* imagePath, 
	unsigned int windowWidth, unsigned int windowHeight, 
	float imageHeight, glm::vec2 position, glm::vec2 scale)
	: SimpleGUIComponent::Rectangle(windowWidth, windowHeight, position, glm::vec2(imageHeight), scale)
{
	float aspectRatio{ loadImage(imagePath) };

	this->size.x *= aspectRatio;

	std::cout << "r: " << aspectRatio << ", " << size.x << ", " << size.y << std::endl;
}

SimpleGUIComponent::Image::~Image()
{
}

void SimpleGUIComponent::Image::render(unsigned int guiShader, unsigned int textShader, unsigned int width, unsigned int height)
{
	Item::render(guiShader, textShader, width, height);

	glUseProgram(guiShader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Setting the uniforms
	glm::vec2 screenPosition{ getPosition(width, height) };
	glm::vec2 screenSize{ getSize(width, height) };
	glUniform2f(glGetUniformLocation(guiShader, "position"), screenPosition.x, screenPosition.y);
	glUniform2f(glGetUniformLocation(guiShader, "size"), screenSize.x, screenSize.y);
	glUniform1i(glGetUniformLocation(guiShader, "useTexture"), 1); // Use the texture
	glUniform1i(glGetUniformLocation(guiShader, "textureSampler"), 0);

	// Draw call
	glBindVertexArray(SimpleGUI::quadVAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

float SimpleGUIComponent::Image::loadImage(const char* imagePath)
{
	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(imagePath, &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else
	{
		std::cout << "Failed to load image: " << imagePath << ".\nReason: " << stbi_failure_reason() << std::endl;
	}

	stbi_image_free(data);

	return (float)width / (float)height;
}
