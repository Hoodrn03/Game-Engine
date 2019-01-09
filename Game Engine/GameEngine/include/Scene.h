/*! \file Thisw ill be used to manage the current scene loaded in the game engine. */

#pragma once

#include "IEngineCore.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "Model.h"

#include <json/json.h>

#include <fstream>
#include <sstream>

/*! \class The current scene loaded into the game engine. */
class Scene
{

public:

	//-----------------------------------------------------------//
	/*! Constructor 
	*Param One : The location for the level, to load.
	*/
	Scene(std::string levelFile);

	//-----------------------------------------------------------//
	/*! Deconstructor 
	*
	*/
	~Scene();

	// Data Members 

private:

	/*! \var A list of game object making up the scene. */
	std::vector<GameObject> v_GameObjects; 

	// Member Functions

public:

	//-----------------------------------------------------------//
	/*! Update : Used to update the current scene. 
	*
	*/
	void m_Update();

	//-----------------------------------------------------------//
	/*! Render : Used to render the current scene. 
	*Param One : The current engine core being used. 
	*/
	void m_Render(IEngineCore * engineInterface);

	//-----------------------------------------------------------//
	/*! GetGameObjects : Used to get the list of game object currently in the scene. 
	*
	*/
	std::vector<GameObject> m_GetGameObjects(); 

	//-----------------------------------------------------------//
	/*! LoadLevelJson : This will load the game scene from a json file. 
	*
	*/
	bool m_LoadLevelJson(std::string levelFile);

};