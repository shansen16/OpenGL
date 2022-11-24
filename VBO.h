//vertex buffer object
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 colour;



};


class VBO 
{
	public:
		//reference ID of the VBO
		GLuint ID;
		//Constructor function 
		VBO(std::vector <Vertex>& vertices);
		VBO(std::vector <glm::vec3> points);

		void Bind();
		void Unbind();
		void Delete();
};
#endif // !VBO_CLASS_H
