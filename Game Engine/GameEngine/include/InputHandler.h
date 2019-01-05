/*! \file This will be used to handle all of the inputs for the game engine. */

#pragma once
#include <map>
#include "GameObject.h"
#include <vector>
#include "TransformComponent.h"

/*! \class Handles all of the inputs within the game. */
class InputCommand
{

public:

	//-----------------------------------------------------------//
	/*! Deconstructor 
	*
	*/
	virtual ~InputCommand() {}
	
	//-----------------------------------------------------------//
	/*! Execute : This will be used to run code from a key press. 
	*
	*/
	virtual void execute(GameObject& playerBackground) = 0;
};

/*! \struct This is the active event handler within the finished game. */
struct InputHandler
{	
	/*! \var A pointer to a player object. */
	GameObject* m_playerCube;

	/*! \var This will hold all of the key commands and the action the key will cause. */
	std::map<int, InputCommand*> m_controlMapping;

	//-----------------------------------------------------------//
	/*! Constructor 
	*Param One : A pointer to the player object. 
	*/
	InputHandler(GameObject* playerCube) : m_playerCube(playerCube)
	{
		// the idea will be to map the keys directly from a config file that can be loaded in
		// and changed on the fly
		
		// m_controlMapping[65] = 

	}

	//-----------------------------------------------------------//
	/*! HandleInputs : This will use a list of keys pressed this frame 
	*					and activate thir related functions. 
	*Param One : A vector of keys pressed. 
	*/
	void handleInputs(const std::vector<bool>& keyBuffer)
	{
		for(const auto& mapEntry : m_controlMapping)
		{
			if(keyBuffer[mapEntry.first])
			{
				mapEntry.second->execute(*m_playerCube);
			}
		}

	}
};
