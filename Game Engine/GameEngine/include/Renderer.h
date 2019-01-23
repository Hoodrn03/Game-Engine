/*! \file This will be used to render all of the game objects. */

#pragma once

#include "IEngineCore.h"

#include "GameObject.h"
#include "ModelComponent.h"
#include "TransformComponent.h"

/*! \class This will be used to render game objects. */
class Renderer
{

public: 

	//-----------------------------------------------------------//
	/*! Constructor
	*
	*/
	Renderer();

	//-----------------------------------------------------------//
	/*! Deconstructor
	*
	*/
	~Renderer(); 

	// Data Members 

private:


	// Member Functions

public:

	//-----------------------------------------------------------//
	/*! Render : This will render the game object passed into it. 
	*Param One : The game object to draw. 
	*Param Two : The current engine core for the game. 
	*/
	void m_Render(GameObject *drawable, IEngineCore *core);

	//-----------------------------------------------------------//
	/*! Render : This will render the game object passed into it. 
	*Param One : A list of game objects to render. 
	*Param Two : The current engine core for the game. 
	*/
	void m_Render(std::vector<GameObject> &drawable, IEngineCore *core);

	//-----------------------------------------------------------//
	/*! Render : This will render the game object passed into it.
	*Param One : A list of game objects to render.
	*Param Two : The current engine core for the game.
	*/
	void m_Render(std::vector<GameObject*> drawable, IEngineCore *core);
};