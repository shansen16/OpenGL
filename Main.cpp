#include"Mesh.h"


unsigned int screenWidth = 800;
unsigned int screenHeight = 800;
float clipStart = 0.1f;
float clipEnd = 100.0f;
glm::vec3 defaultColour = glm::vec3(0.8f, 0.8f, 0.8f);

Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /      
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), defaultColour},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), defaultColour},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), defaultColour},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), defaultColour}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};
Vertex cubeVertices[] =
{  //               COORDINATES           /            COLORS          /
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f), defaultColour},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), defaultColour},
	Vertex{glm::vec3( 0.1f, -0.1f, -0.1f), defaultColour},
	Vertex{glm::vec3( 0.1f, -0.1f,  0.1f), defaultColour},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f), defaultColour},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f), defaultColour},
	Vertex{glm::vec3( 0.1f,  0.1f, -0.1f), defaultColour},
	Vertex{glm::vec3( 0.1f,  0.1f,  0.1f), defaultColour},
};


GLuint cubeIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


int main() 
{
	
	
	
	glfwInit();

	//this is giving the window object the information it needs
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//tells GLFW to use CORE profile, therefore only modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //what version of openGL is being used


	//creates a window object. Or a pointer to a window object?
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL", NULL, NULL);
	
	if (window == NULL) 
	{ //error handling
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//I think this like sets it as the current window. Like the one the program uses
	glfwMakeContextCurrent(window);

	//loads GLAD so it configures OpenGL
	gladLoadGL();

	//sets the start and end coordinates for the openGL rendering
	glViewport(0, 0, screenWidth, screenHeight);
	//sets a colour and nothing else
	
	//creates Shader object using shaders default.vert and default.frag
	Shader faceShaderProgram("face.vert", "default.frag");
	//Shader vertexShaderProgram("vertex.vert", "deafult.frag");



	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	Mesh floor(verts, ind, defaultColour);

	std::vector <Vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
	std::vector <GLuint> cubeInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
	Mesh cube(cubeVerts, cubeInd, defaultColour);

	glEnable(GL_DEPTH_TEST); //crucial piece of code. Goes more in depth in document. Needed to prevent overlapping and have the correct face of a mesh appears

	Camera camera(screenWidth, screenHeight, glm::vec3(2.0f, 2.0f, 5.0f));

	//stops the window from closing immediately and for some subroutines to be 
	while (!glfwWindowShouldClose(window)) 
	{
		//specifies colour of background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//clears the back buffer and assigns new colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //the GL_DEPTH_BUFFER_BIT solves the overlapping part
		//tells OpenGL what shader program to use
		faceShaderProgram.Activate();


		camera.Inputs(window);
		camera.updateMatrix(45.0f, clipStart, clipEnd);

		camera.Matrix(faceShaderProgram, "camMatrix");

		floor.Draw(camera, faceShaderProgram);
		cube.Draw(camera, faceShaderProgram);

		glfwSwapBuffers(window);

		//takes care of all GLFW events
		glfwPollEvents();
	}

	//delete all objects created
	
	faceShaderProgram.Delete();

	//terminating stuff
	glfwDestroyWindow(window);
	glfwTerminate();

	std::cout << "clip start" << clipStart << std::endl;
	std::cout << "clip end" << clipEnd << std::endl;

	return 0;
}