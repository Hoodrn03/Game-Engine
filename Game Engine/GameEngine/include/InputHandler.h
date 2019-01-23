/*! \file This will be used to handle all of the inputs for the game engine. */

#pragma once

#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

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

	//-----------------------------------------------------------//
	/*! ClassName : This will be used to help load and output this action. 
	*
	*/
	virtual const char* m_ClassName() = 0;
};

/*! \class Used to rotate the player. */
class RotLeft : public InputCommand
{
	virtual const char* m_ClassName() { return "RotLeft"; };

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
	virtual const char* m_ClassName() { return "RotRight"; };

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
	virtual const char* m_ClassName() { return "MoveForward"; };

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
	virtual const char* m_ClassName() { return "MoveBackward"; };

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
	virtual const char* m_ClassName() { return "MoveLeft"; };

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
	virtual const char* m_ClassName() { return "MoveRight"; };

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
	virtual const char* m_ClassName() { return "NextCamera"; }; 

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
	InputHandler(GameManager* gameManager) : m_GameManager(gameManager)
	{
		// the idea will be to map the keys directly from a config file that can be loaded in
		// and changed on the fly

		m_LoadConfig(); 
	}

	//-----------------------------------------------------------//
	/*! Deconstructor 
	*
	*/
	~InputHandler()
	{
		m_OutputConfig(); 
	}

	//-----------------------------------------------------------//
	/*! LoadConfig : This will be used to read the config file for the game and 
	*					adjust the key commands used. 
	*
	*/
	void m_LoadConfig()
	{
		ifstream l_MyFile;

		std::string l_Line; 

		l_MyFile.open("assets/config/config.txt");

		if (l_MyFile.is_open())
		{
			while (getline(l_MyFile, l_Line))
			{
				std::stringstream l_ss(l_Line);

				int l_InputKey;
				std::string l_ActionClass; 

				l_ss >> l_InputKey; 

				std::cout << l_InputKey << std::endl;

				l_ss >> l_ActionClass;

				if (l_ActionClass == "MoveForward")
				{
					m_controlMapping[l_InputKey] = new MoveForward;
				}
				else if (l_ActionClass == "MoveBackward")
				{
					m_controlMapping[l_InputKey] = new MoveBackward;
				}
				else if (l_ActionClass == "MoveLeft")
				{
					m_controlMapping[l_InputKey] = new MoveLeft;
				}
				else if (l_ActionClass == "MoveRight")
				{
					m_controlMapping[l_InputKey] = new MoveRight;
				}
				else if (l_ActionClass == "NextCamera")
				{
					m_controlMapping[l_InputKey] = new NextCamera;
				}
			}

			l_MyFile.close();

			std::cout << "Config Loaded" << std::endl;
		}
	}

	//-----------------------------------------------------------//
	/*! OutputConfig : This will write the current key commands for the engine to a 
	*					config file within assets. 
	*
	*/
	void m_OutputConfig()
	{

		ofstream l_MyFile;

		l_MyFile.open("assets/config/config.txt");

		if (l_MyFile.is_open())
		{
			for (auto const& x : m_controlMapping)
			{
				l_MyFile << x.first << " "; 
				l_MyFile << x.second->m_ClassName() << std::endl;
			}

			l_MyFile.close(); 

			std::cout << "Config Updated" << std::endl;
		}
		else
		{
			std::cout << "Error opening file." << std::endl;
		}

	}

	//-----------------------------------------------------------//
	/*! ClassName : This will beused to get the name of the class, used for the 
	*				reading/writing to the config file. 
	*
	*/
	virtual const char* m_ClassName() { return "InputHandler"; }

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
