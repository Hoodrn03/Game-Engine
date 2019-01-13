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

	m_MainCamera.addComponent(new TransformComponent(glm::vec3(0, 0, -10)));
	m_MainCamera.addComponent(new CameraComponent(new Camera(glm::vec3(0, 0, -10)), &m_MainCamera));
	m_MainCamera.addComponent(new MoveComponent(&m_MainCamera)); 
	m_MainCamera.m_id = "Camera"; 

	m_PlayerObject.addComponent(new TransformComponent(glm::vec3(0, 0, -10)));
	m_PlayerObject.addComponent(new MoveComponent(&m_PlayerObject));
	m_PlayerObject.addComponent(new CameraComponent(new Camera(), &m_PlayerObject, glm::vec3(0, 1, 0)));
	m_PlayerObject.addComponent(new ModelComponent(new Model("assets/models/Cube.obj")));
	m_PlayerObject.m_id = "Player";

	m_playerBackground.addComponent(new RedComponent);
	m_playerBackground.addComponent(new GreenComponent);
	m_playerBackground.addComponent(new BlueComponent); 

	m_CurrentScene = new Scene("assets/levels/levelOne.json");

	m_inputHandler = new InputHandler(&m_PlayerObject);
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
	m_CurrentTime = glfwGetTime(); 

	m_dt = float(m_CurrentTime - m_LastTime); 

	m_LastTime = m_CurrentTime; 

	m_MainCamera.m_Update(0.f); 
	m_PlayerObject.m_Update(0.f); 
}

void Game::m_UpdateRotation(float xAngle, float yAngle)
{
	xAngle * m_dt; 
	yAngle * m_dt; 

	m_PlayerObject.getComponent<CameraComponent>()->m_RotateCamera(xAngle, yAngle); 
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
	m_engineInterfacePtr->setCamera(&m_PlayerObject.getComponent<CameraComponent>()->m_GetCamera());

	// Render the current scene. 
	m_GameRenderer.m_Render(*&m_CurrentScene->m_GetGameObjects(), m_engineInterfacePtr);

	m_GameRenderer.m_Render(&m_PlayerObject, m_engineInterfacePtr);


}
