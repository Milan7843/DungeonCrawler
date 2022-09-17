#include "Renderer.h"

namespace Renderer
{
	namespace
	{
		unsigned int squareVAO;
	};

	void initialise()
	{
        // Creating the VAO for a square to draw 

        unsigned int squareVBO, squareEBO;
        float s = 0.5f;
        float vertices[] = {
            // Positions
            s,  s, 1.0f, 1.0f, // top right
            s, -s, 1.0f, 0.0f, // bottom right
            -s, -s, 0.0f, 0.0f, // bottom left
            -s,  s, 0.0f, 1.0f, // top left 
        };

        unsigned int indices[] = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        // Generating the required objects
        glGenVertexArrays(1, &squareVAO);
        glGenBuffers(1, &squareVBO);
        glGenBuffers(1, &squareEBO);

        // Making sure everything gets put on this specific VAO
        glBindVertexArray(squareVAO);

        // Binding the buffers
        glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareEBO);

        // Putting the indices and vertices into the buffers
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Letting OpenGL know how to interpret the data:
        // 2 floats for position
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // Another 2 floats for UV's
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Unbinding
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
	}
    unsigned int getSquareVAO()
    {
        return squareVAO;
    }
};
