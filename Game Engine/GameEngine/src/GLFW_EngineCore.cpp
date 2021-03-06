/*! \file This will hold the class definitions for the class GLFW_EngineCore.h */
// By Ryan Hood. 

#include "GLFW_EngineCore.h"
#include "Game.h"
#include <fstream>
#include <sstream>
#include <glm/detail/type_vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

std::vector<bool> GLFW_EngineCore::m_keyBuffer;
int GLFW_EngineCore::m_screenWidth;
int GLFW_EngineCore::m_screenHeight;

float GLFW_EngineCore::m_HorizontalAngle;
float GLFW_EngineCore::m_VerticalAngle;

GLFW_EngineCore::~GLFW_EngineCore()
{
	// cleanup
	glfwTerminate();
}

//-----------------------------------------------------------//
/*! InitWindow : This will be used to create a window for the game.
*Param One : The Width of the game window.
*Param Two : The Height of the game window.
*Param Three : The Name of the game window.
*/
bool GLFW_EngineCore::initWindow(int width, int height, std::string windowName)
{
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	m_screenWidth = width;
	m_screenHeight = height;

	m_window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	if (m_window == nullptr)
	{
		std::cout << "Failed to create GLFW m_window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return false;
	}

	// callback functions
	glfwSetFramebufferSizeCallback(m_window, windowResizeCallbackEvent);
	glfwSetKeyCallback(m_window, keyCallbackEvent);
	glfwSetCursorPosCallback(m_window, mouseMoveCallbackEvent);

	// make space for the keybuffer
	m_keyBuffer.resize(m_keyBufferSize);
	std::fill(m_keyBuffer.begin(), m_keyBuffer.end(), false);

	// set the shaders to the given default ones
	setDefaultShaders();

	// set the drawable model as a cube
	// note: this will be changed later when we can draw many kinds of objects
	initCubeModel();

	// enable depth test
	glEnable(GL_DEPTH_TEST);

	return true;
}

//-----------------------------------------------------------//
/*! RunEngine : This will be used to operate the game loop with the engine core.
*Param One : The game loop to run.
*/
bool GLFW_EngineCore::runEngine(Game& game)
{
	// for this example just give the game direct access to the engine
	// there are other ways this could be handled
	game.m_engineInterfacePtr = this;

	// message loop
	while (!glfwWindowShouldClose(m_window))
	{
		game.m_inputHandler->handleInputs(m_keyBuffer);
		
		game.m_Update(); // update game logic
		game.m_UpdateRotation(m_HorizontalAngle, m_VerticalAngle); 
		game.m_Render(); // prepare game to send info to the renderer in engine core

		// swap buffers
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	return true;
}

//-----------------------------------------------------------//
/*! RenderColouredBackground : This will be used to display a colourd background within the game.
*Param One : The Red value.
*Param Two : The Green value.
*Param Three : The Blue value.
*/
void GLFW_EngineCore::renderColouredBackground(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLFW_EngineCore::mouseMoveCallbackEvent(GLFWwindow * window, double xPos, double yPos)
{
	glfwGetCursorPos(window, &xPos, &yPos); 

	glfwSetCursorPos(window, m_screenWidth / 2, m_screenHeight / 2);

	float l_MoveSpeed = 0.005f; 

	m_HorizontalAngle = l_MoveSpeed * float(m_screenWidth / 2 - xPos);
	m_VerticalAngle = l_MoveSpeed * float(m_screenHeight / 2 - yPos);

}

//-----------------------------Private functions------------------------------
void GLFW_EngineCore::keyCallbackEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UNKNOWN || key > m_keyBufferSize)
	{
		return;
	}
	m_keyBuffer[key] = ((action == GLFW_PRESS || action == GLFW_REPEAT));

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void GLFW_EngineCore::windowResizeCallbackEvent(GLFWwindow* window, int width, int height)
{
	// change the opengl viewport to match the new m_window size
	m_screenWidth = width;
	m_screenHeight = height;
	glViewport(0, 0, width, height);
}

// loading some default shaders to get things up and running
void GLFW_EngineCore::setDefaultShaders()
{
	// Load contents of vertex file
	std::ifstream inFile("assets/shaders/defaultShader.vert");
	if (!inFile) {
		fprintf(stderr, "Error opening file: shader\n");
		exit(1);
	}

	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	std::string codeStr(code.str());
	const GLchar* vertex_shader[] = { codeStr.c_str() };

	// Load contents of fragment file
	std::ifstream inFile2("assets/shaders/defaultShader.frag");
	if (!inFile2) {
		fprintf(stderr, "Error opening file: shader\n");
		exit(1);
	}

	std::stringstream code2;
	code2 << inFile2.rdbuf();
	inFile2.close();
	std::string codeStr2(code2.str());
	const GLchar* fragment_shader[] = { codeStr2.c_str() };
	
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vertex_shader, NULL);
	glCompileShader(vertexShader);	
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, fragment_shader, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	m_defaultShaderProgram = glCreateProgram();
	glAttachShader(m_defaultShaderProgram, vertexShader);
	glAttachShader(m_defaultShaderProgram, fragmentShader);
	glLinkProgram(m_defaultShaderProgram);
	// check for linking errors
	glGetProgramiv(m_defaultShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_defaultShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(m_defaultShaderProgram);
}

// a simple function to initialise a cube model in memory
void GLFW_EngineCore::initCubeModel()
{
	// set up vertex and normal data
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
}

//-----------------------------------------------------------//
/*! SetCamera : This will be used to set the camera which will be used to display the scene.
*Param One : The camera which will be used for the game engine.
*/
void GLFW_EngineCore::setCamera(const Camera* cam)
{
	// set the view and projection components of our shader to the camera values
	glm::mat4 projection = glm::perspective(glm::radians(cam->getFOV()), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(m_defaultShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glUniformMatrix4fv(glGetUniformLocation(m_defaultShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(cam->getViewMatrix()));

	// be sure to activate shader when setting uniforms/drawing objects
	glUniform3f(glGetUniformLocation(m_defaultShaderProgram, "objectColour"), 1.0f, 0.6f, 0.61f);
	glUniform3f(glGetUniformLocation(m_defaultShaderProgram, "lightColour"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(m_defaultShaderProgram, "lightPos"), 0.0f, 2.0f, -2.0f);
	glUniform3fv(glGetUniformLocation(m_defaultShaderProgram, "viewPos"), 1, glm::value_ptr(cam->position()));
	
}

//-----------------------------------------------------------//
/*! DrawCube : This will draw all of the objects in a given scene as a cube.
*Param One : The model matrix of the object which should be drawn, (position, scale, ext.).
*/
void GLFW_EngineCore::drawCube(const glm::mat4& modelMatrix)
{
	// set the model component of our shader to the cube model
	glUniformMatrix4fv(glGetUniformLocation(m_defaultShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// the only thing we can draw so far is the cube, so we know it is bound already
	// this will obviously have to change later
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//-----------------------------------------------------------//
/*! DrawModel : This will be used to draw the models into a scene.
*Param One : The model which should be drawn.
*Param Two : The model matrix for that model, (position, scale, ext.).
*/
void GLFW_EngineCore::drawModel(Model* model, glm::mat4& modelMatrix)
{
	// set the model component of our shader to the object model
	glUniformMatrix4fv(glGetUniformLocation(m_defaultShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

	model->render(m_defaultShaderProgram);
}
