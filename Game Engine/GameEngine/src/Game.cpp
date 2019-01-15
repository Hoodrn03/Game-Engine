/*! \file This will hold the class definitions for the class Game.h */
// By Ryan Hood. 

#include <fstream>
#include <sstream>

#include "Game.h"

#include "TransformComponent.h"
#include "ColourComponent.h"
#include "CameraComponent.h"
#include "MoveComponent.h"


//-----------------------------------------------------------//
/*! Constructor
*
*/
Game::Game()
{
	m_engineInterfacePtr = nullptr;

	m_playerBackground.addComponent(new RedComponent);
	m_playerBackground.addComponent(new GreenComponent);
	m_playerBackground.addComponent(new BlueComponent); 

	m_CurrentScene = new Scene("assets/levels/levelOne.json");

	m_inputHandler = new InputHandler(m_GameManager.m_GetGameObject(0));
}

//-----------------------------------------------------------//
/*! Deconstructor
*
*/
Game::~Game()
{
}

//-----------------------------------------------------------//
/*! Update : Called once every frame.
*
*/
void Game::m_Update()
{

	// Update Delta time (Change in time since last frame). 
	m_CurrentTime = glfwGetTime(); 

	m_dt = float(m_CurrentTime - m_LastTime); 

	m_LastTime = m_CurrentTime; 

	// Update Game Objects

	m_GameManager.m_Update(m_dt); 
}

void Game::m_UpdateRotation(float xAngle, float yAngle)
{
	m_GameManager.RotateWithMouse(xAngle, yAngle); 
}

//-----------------------------------------------------------//
/*! Render : Will draw all items at the end of the frame.
*
*/
void Game::m_Render()
{
	float redValue = 0, greenValue = 0, blueValue = 0;

	if (m_playerBackground.getComponent<RedComponent>())
	{
		redValue = m_playerBackground.getComponent<RedComponent>()->m_colourValue;
	}
	if (m_playerBackground.getComponent<GreenComponent>())
	{
		greenValue = m_playerBackground.getComponent<GreenComponent>()->m_colourValue;
	}
	if (m_playerBackground.getComponent<BlueComponent>())
	{
		blueValue = m_playerBackground.getComponent<BlueComponent>()->m_colourValue;
	}

	// Pass object details to the engine to render the next frame
	m_engineInterfacePtr->renderColouredBackground(redValue, greenValue, blueValue);

	// Update Camera. 
	m_engineInterfacePtr->setCamera(m_GameManager.m_GetCamera());

	// Render the current scene. 
	m_GameRenderer.m_Render(*&m_CurrentScene->m_GetGameObjects(), m_engineInterfacePtr);

	m_GameRenderer.m_Render(m_GameManager.m_GetPlayerObject(), m_engineInterfacePtr);


}
