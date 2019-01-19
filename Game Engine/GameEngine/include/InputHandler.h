/*! \file This will be used to handle all of the inputs for the game engine. */

#pragma once
#include <map>
#include <vector>

#include "GameObject.h"

#include "GameManager.h"

#include "TransformComponent.h"
#include "MoveComponent.h"

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

/*! \class Used to rotate the player. */
class RotLeft : public InputCommand
{
	void execute(GameObject& playerBackground) override
	{
		try
		{
			if (playerBackground.getComponent<MoveComponent>() != nullptr)
			{
				playerBackground.getComponent<MoveComponent>()->OnMessage("rotLeft");
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
		}
	}
};

/*! \class Used to rotate the player. */
class RotRight : public InputCommand
{
	void execute(GameObject& playerBackground) override
	{
		try
		{
			if (playerBackground.getComponent<MoveComponent>() != nullptr)
			{
				playerBackground.getComponent<MoveComponent>()->OnMessage("rotRight");
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
		}
	}
};

/*! \class Used to move the player. */
class MoveForward : public InputCommand
{
	void execute(GameObject& playerBackground) override
	{
		try
		{
			if (playerBackground.getComponent<MoveComponent>() != nullptr)
			{
				playerBackground.getComponent<MoveComponent>()->OnMessage("forward");
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
		}
	}
};

/*! \class Used to move the player. */
class MoveBackward : public InputCommand
{
	void execute(GameObject& playerBackground) override
	{
		try
		{
			if (playerBackground.getComponent<MoveComponent>() != nullptr)
			{
				playerBackground.getComponent<MoveComponent>()->OnMessage("backward");
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
		}
	}
};

/*! \class Used to move the player. */
class MoveLeft : public InputCommand
{
	void execute(GameObject& playerBackground) override
	{
		try
		{
			if (playerBackground.getComponent<MoveComponent>() != nullptr)
			{
				playerBackground.getComponent<MoveComponent>()->OnMessage("left");
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
		}
	}
};

/*! \class Used to move the player. */
class MoveRight : public InputCommand
{
	void execute(GameObject& playerBackground) override
	{
		try
		{
			if (playerBackground.getComponent<MoveComponent>() != nullptr)
			{
				playerBackground.getComponent<MoveComponent>()->OnMessage("right");
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what(); 
		}
	}
};

/*! \class This will switch the current type of camera. */
class NextCamera : public InputCommand
{
	void execute(GameObject& gameCamera) override
	{
		try
		{
			if (gameCamera.getComponent<CameraComponent>() != nullptr)
			{
				if (gameCamera.getComponent<CameraComponent>()->m_CameraType == firstPersonCamera)
				{
					gameCamera.getComponent<CameraComponent>()->m_SetCameraType(thirdPersonCamera);
				}
				else if (gameCamera.getComponent<CameraComponent>()->m_CameraType == thirdPersonCamera)
				{
					gameCamera.getComponent<CameraComponent>()->m_SetCameraType(staticCamera);
				}
				else
				{
					gameCamera.getComponent<CameraComponent>()->m_SetCameraType(firstPersonCamera); 
				}
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
		}
	}
};


/*! \struct This is the active event handler within the finished game. */
struct InputHandler
{	
	/*! \var A pointer to a player object. */
	GameObject* m_playerCube;

	/*! \var A pointer to the game manager. */
	GameManager* m_GameManager; 

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
		
		m_controlMapping[87] = new MoveForward; 
		m_controlMapping[83] = new MoveBackward; 
		m_controlMapping[65] = new MoveLeft;
		m_controlMapping[68] = new MoveRight; 
	}

	//-----------------------------------------------------------//
	/*! Constructor
	*Param One : A pointer to the player object.
	*/
	InputHandler(GameManager* gameManager) : m_GameManager(gameManager)
	{
		// the idea will be to map the keys directly from a config file that can be loaded in
		// and changed on the fly

		m_controlMapping[87] = new MoveForward;
		m_controlMapping[83] = new MoveBackward;
		m_controlMapping[65] = new MoveLeft;
		m_controlMapping[68] = new MoveRight;

		m_controlMapping[90] = new NextCamera; 
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
				if (mapEntry.first == 90)
				{
					mapEntry.second->execute(*m_GameManager->m_GetGameObject("Camera"));
				}
				else
				{
					mapEntry.second->execute(*m_GameManager->m_GetGameObject("Player"));
				}
			}
		}

	}
};
