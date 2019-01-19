/*! \file This will hold the main game loop; meanining it will control all of 
*			rendering and updating of game logic for the engine.
*/

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

	/*! \var This will handle all of the rendering for the game. */
	Renderer m_GameRenderer; 

	/*! \var This will control the main game objects for the game. */
	GameManager m_GameManager; 

public:

	/*! \var A pointer to the current engine core. */
	IEngineCore* m_engineInterfacePtr;

	/*! \var This will handle all of the user inputs for the engine, it will send messages to 
	*			other functions when keys are pressed. 
	*/
	InputHandler* m_inputHandler;

	/*! \var The delta (change) in time since last frame. */
	float m_dt = 0; 

	/*! \var The current time and last time used to work out delta time. */
	double m_CurrentTime, m_LastTime; 

	// Member Functons 

public:

	//-----------------------------------------------------------//
	/*! Update : Called once every frame. 
	*
	*/
	void m_Update();

	//-----------------------------------------------------------//
	/*! Update Rotation : This will be used to update the rotation of the main game objets.
	*Param One : The direction of the mouse on the X axis.
	*Param Two : The direction of the mouse on the Y axis.
	*/
	void m_UpdateRotation(float xAngle, float yAngle);

	//-----------------------------------------------------------//
	/*! Render : Will draw all items at the end of the frame. 
	*
	*/
	void m_Render();

};
