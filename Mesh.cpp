#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, glm::vec3 colour)
{
	/*for (int i = 0; i < sizeof(paraVertices) / sizeof(glm::vec3); i++)
	{
		Mesh::vertices.push_back(Vertex{ paraVertices[i], colour });
	}*/
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::colour = colour;
	

	VAO.Bind();

	//Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices);
	//Generates Element Buffer Object and links it to vertices
	EBO EBO(indices);

	// Link VBO attributes such as coordinates and colours to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	//Unbinds all objects to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}


void Mesh::Draw(Camera& camera, Shader& shader)
{
	Mesh::camera = camera; //I think this should work. Problem is that I'm not sure if I change attributes of the camera class if the attributes here will change or not
	//it's possible that the sollution to this will be something like Mesh::camera*  = camera*

	shader.Activate();
	VAO.Bind();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	for (int i = 0; i < sizeof(vertices) / sizeof(Vertex); i++)
	{
		Vertex activeVertex = vertices[i];
		glm::vec4 transformation = camera.cameraMatrix * glm::vec4(activeVertex.position, 1);
		Node node(glm::vec2(transformation.x, transformation.y), 32, 0.01f);
	}
}



//edit mode

//Node Mesh::CreateNode(glm::vec2 position, int sides, float radius)
//{
//	
//	std::vector <glm::vec3> points;
//	points.push_back(glm::vec3(position, 0));
//	for (int i = 1; i < sides; i++)
//	{
//		points.push_back( (glm::vec3(radius * cos((1 - i) * 2 * pi / sides), radius * sin((1 - i) * 2 * pi / sides), 0)) +glm::vec3(position, 0));
//	}
//	std::vector <GLuint> indices;
//	for (int i = 0; i < sides - 1; i++)
//	{
//		indices.push_back(0);
//		indices.push_back(i);
//		indices.push_back(i+1);
//	}
//	indices.push_back(0);
//	indices.push_back(sides);
//	indices.push_back(1);
//	
//	return Node(points, indices);
//}
Node::Node(glm::vec2 position, int sides, float radius)
{
	Node::shaderProgram = Shader("vertex.vert", "default.frag");
	std::vector <glm::vec3> points;
	points.push_back(glm::vec3(position, 0));
	for (int i = 1; i < sides; i++)
	{
		points.push_back((glm::vec3(radius * cos((1 - i) * 2 * pi / sides), radius * sin((1 - i) * 2 * pi / sides), 0)) + glm::vec3(position, 0));
	}
	std::vector <GLuint> indices;
	for (int i = 0; i < sides - 1; i++)
	{
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	indices.push_back(0);
	indices.push_back(sides);
	indices.push_back(1);
	Node::points = points;
	Node::indices = indices;
}
void Node::Draw()
{
	shaderProgram.Activate();
	// Bind the VAO so OpenGL knows to use it
	VAO.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}
//Node::Node(glm::vec2 position, int sides, float radius)
//{
//	Node::shaderProgram = Shader("vertex.vert", "default.frag");
//	std::vector <glm::vec3> points;
//	points.push_back(glm::vec3(position, 0));
//	for (int i = 1; i < sides; i++)
//	{
//		points.push_back((glm::vec3(radius * cos((1 - i) * 2 * pi / sides), radius * sin((1 - i) * 2 * pi / sides), 0)) + glm::vec3(position, 0));
//	}
//	std::vector <GLuint> indices;
//	for (int i = 0; i < sides - 1; i++)
//	{
//		indices.push_back(0);
//		indices.push_back(i);
//		indices.push_back(i + 1);
//	}
//	indices.push_back(0);
//	indices.push_back(sides);
//	indices.push_back(1);
//	Node::points = points;
//	Node::indices = indices;
//}
//void Node::Draw()
//{
//	shaderProgram.Activate();
//	// Bind the VAO so OpenGL knows to use it
//	VAO.Bind();
//	// Draw primitives, number of indices, datatype of indices, index of indices
//	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
//}
