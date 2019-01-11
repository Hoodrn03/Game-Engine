/*! \file This will be the engine core which will be used on windows operating 
*			systems. 
*/
// By Ryan Hood. 

#pragma once

#include "IEngineCore.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/mat4x4.hpp>

#include "Camera.h"
#include "Model.h"

class Game;

/*! \class This is the version of the engine core which will be run on windows. */
class GLFW_EngineCore : public IEngineCore
{

public:

	//-----------------------------------------------------------//
	/*! Constructor 
	*
	*/
	~GLFW_EngineCore() override;

	// Member Functions 

	//-----------------------------------------------------------//
	/*! InitWindow : This will be used to create a window for the game. 
	*Param One : The Width of the game window. 
	*Param Two : The Height of the game window. 
	*Param Three : The Name of the game window. 
	*/
	bool initWindow(int width, int height, std::string windowName) override;

	//-----------------------------------------------------------//
	/*! RunEngine : This will be used to operate the game loop with the engine core. 
	*Param One : The game loop to run. 
	*/
	bool runEngine(Game& game) override;

	//-----------------------------------------------------------//
	/*! RenderColouredBackground : This will be used to display a colourd background within the game. 
	*Param One : The Red value. 
	*Param Two : The Green value. 
	*Param Three : The Blue value. 
	*/
	void renderColouredBackground(float r, float g, float b) override;

	//-----------------------------------------------------------//
	/*! SetCamera : This will be used to set the camera which will be used to display the scene. 
	*Param One : The camera which will be used for the game engine. 
	*/
	void setCamera(const Camera* cam) override;

	//-----------------------------------------------------------//
	/*! DrawCube : This will draw all of the objects in a given scene as a cube. 
	*Param One : The model matrix of the object which should be drawn, (position, scale, ext.). 
	*/
	void drawCube(const glm::mat4& modelMatrix) override;

	//-----------------------------------------------------------//
	/*! DrawModel : This will be used to draw the models into a scene. 
	*Param One : The model which should be drawn. 
	*Param Two : The model matrix for that model, (position, scale, ext.). 
	*/
	void drawModel(Model * model, glm::mat4 & modelMatrix) override;

private: 

	static void mouseMoveCallbackEvent(GLFWwindow* window, double xPos, double yPos);

	static void keyCallbackEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void windowResizeCallbackEvent(GLFWwindow* window, int width, int height);

	void setDefaultShaders();

	void initCubeModel();

	// Data Members

private:

	/*! \var The current game window. */
	GLFWwindow* m_window;
	
	GLuint m_defaultShaderProgram; 

	/*! \var The width of the game window. */
	static int m_screenWidth;

	/*! \var The height of the game window. */
	static int m_screenHeight;

	/*! \var A list of inputs the game can recives in a single frame. */
	static std::vector<bool> m_keyBuffer;

	/*! \var The maximum number of inputs the game can take in a single frame. */
	static const int m_keyBufferSize = 400;




};

