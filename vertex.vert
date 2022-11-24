#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// Outputs the colour for the Fragment Shader
out vec3 colour;

void main()
{
	gl_Position = vec4(aPos, 1.0); //changes the position of the vertices 
	// Assigns the colours from the Vertex Data to colour
	colour = aColor;
}