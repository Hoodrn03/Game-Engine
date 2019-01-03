/*! \file This will hold the class definitions for the class Game.h */

#include "Game.h"
#include "TransformComponent.h"
#include "ColourComponent.h"
#include <fstream>
#include <sstream>

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

	m_CurrentScene = new Scene();

	m_CurrentScene->m_LoadLevelJson("assets/levels/testScene.json"); 

	m_inputHandler = new InputHandler(&m_CurrentScene->m_GetGameObjects()[0]);
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
	m_engineInterfacePtr->setCamera(&m_camera);

	// Render the current scene. 
	m_CurrentScene->m_Render(m_engineInterfacePtr);
	
}
