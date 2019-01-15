/*! \file This will hold the main game loop; meanining it will control all of 
*			rendering and updating of game logic for the engine.
*/
// By Ryan Hood. 

#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "IEngineCore.h"
#include "InputHandler.h"
#include "GameObject.h"
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "GameManager.h"

/*! \class The main game loop, this holds both the update and render functions. */
class Game
{

public:

	//-----------------------------------------------------------//
	/*! Constructor 
	*
	*/
	Game();
	
	//-----------------------------------------------------------//
	/*! Deconstructor
	*
	*/
	~Game();

	// Data Members 

private:

	/*! \var The background for the game. */
	GameObject m_playerBackground;

	/*! \var This will be the current scene loaded into the game engine. */
	Scene* m_CurrentScene; 

	Renderer m_GameRenderer; 

	GameManager m_GameManager; 

public:

	/*! \var A pointer to the current engine core. */
	IEngineCore* m_engineInterfacePtr;

	/*! \var This will handle all of the user inputs for the engine, it will send messages to 
	*			other functions when keys are pressed. 
	*/
	InputHandler* m_inputHandler;

	float m_dt = 0; 

	double m_CurrentTime, m_LastTime; 

	// Member Functons 

public:

	//-----------------------------------------------------------//
	/*! Update : Called once every frame. 
	*
	*/
	void m_Update();

	void m_UpdateRotation(float xAngle, float yAngle);

	//-----------------------------------------------------------//
	/*! Render : Will draw all items at the end of the frame. 
	*
	*/
	void m_Render();

};
