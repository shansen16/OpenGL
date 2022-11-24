#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include "Camera.h"


class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	glm::vec3 colour;
	Camera camera;
	VAO VAO;

	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, glm::vec3 colour);

	void Draw(Camera& camera, Shader& shader);

	//edit mode
	//Node CreateNode(glm::vec2 position, int sides, float radius); //is used to create a regular polygon with a given number of sides. With enough side this effectively becomes a circle
};

class Node
{
public:
	std::vector <glm::vec3> points;
	std::vector <GLuint> indices;
	
	Node(glm::vec2 position, int sides, float radius);
	void Draw();
private:
	VAO VAO;
	Shader shaderProgram;
};

#endif
