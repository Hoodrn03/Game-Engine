/*! \file This will be used to manage all of the key game objects within the scene. */

#pragma once

#include "GameObject.h"

#include "TransformComponent.h"
#include "MoveComponent.h"
#include "CameraComponent.h"
#include "Model.h"
#include "ModelComponent.h"

/*! \class This object will manage most of the key objects within the game. */
class GameManager
{

public:

	//-----------------------------------------------------------//
	/*! Constructor
	*
	*/
	GameManager() 
	{
		GameObject *l_TempObject = new GameObject; 

		// Create The player object. 

		l_TempObject->addComponent(new TransformComponent(glm::vec3(0, 0, 2)));
		l_TempObject->addComponent(new ModelComponent(new Model("assets/models/Cube.obj")));
		l_TempObject->addComponent(new MoveComponent(l_TempObject));
		l_TempObject->m_id = "Player";

		v_GameObjects.push_back(l_TempObject); 

		l_TempObject = new GameObject;

		// Create the main camera object. 
		
		l_TempObject->addComponent(new TransformComponent());
		l_TempObject->addComponent(new CameraComponent(new Camera(), v_GameObjects[0], firstPersonCamera)); 
		l_TempObject->m_id = "Camera";

		v_GameObjects.push_back(l_TempObject);
		
	}

	//-----------------------------------------------------------//
	/*! Deconstructor
	*
	*/
	~GameManager() {}

	// Data Members

private:

	/*! \var A list of game object managed by this manager. */
	std::vector<GameObject*> v_GameObjects; 

	// Member Functions

public:

	//-----------------------------------------------------------//
	/*! GetGameObject : This will be used to get a specific game object.  
	*Param One : The position within the vector for the object. 
	*/
	GameObject* m_GetGameObject(int identifier) { return v_GameObjects[identifier]; }

	//-----------------------------------------------------------//
	/*! GetGameObject : This will be used to get a specific game object.
	*Param One : The name givdn to a specific game object. 
	*/
	GameObject* m_GetGameObject(std::string identifier)
	{
		if (v_GameObjects.size() > 0)
		{
			for (unsigned int i = 0; i < v_GameObjects.size(); i++)
			{
				if (v_GameObjects[i]->m_id == identifier)
				{
					return v_GameObjects[i];
				}
			}
		}

		return nullptr;
	}

	//-----------------------------------------------------------//
	/*! GetPlayerObject : This will search the vector for an object with the tag Player, 
	*
	*/
	GameObject * m_GetPlayerObject() 
	{
		if (v_GameObjects.size() > 0)
		{
			for (unsigned int i = 0; i < v_GameObjects.size(); i++)
			{
				if (v_GameObjects[i]->m_id == "Player")
				{
					return v_GameObjects[i]; 
				}
			}
		}

		return nullptr; 
	}

	//-----------------------------------------------------------//
	/*! GetCamera : This will look for a camera object within the vector and return the attached camera. 
	*
	*/
	Camera * m_GetCamera()
	{

		if (v_GameObjects.size() > 0)
		{
			for (unsigned int i = 0; i < v_GameObjects.size(); i++)
			{
				if (v_GameObjects[i]->m_id == "Camera")
				{
					return &v_GameObjects[i]->getComponent<CameraComponent>()->m_GetCamera();
				}
			}
		}

		return nullptr;
	}

	//-----------------------------------------------------------//
	/*! Update : This will be used to update all of the game objects. 
	*Param One : The change in time from last frame. 
	*/
	void m_Update(float dt)
	{
		if (v_GameObjects.size() > 0)
		{
			for (unsigned int i = 0; i < v_GameObjects.size(); i++)
			{
				v_GameObjects[i]->m_Update(dt); 
			}
		}
	}

	//-----------------------------------------------------------//
	/*! RotateWithMouse : Used to update the rotation of key game objects. 
	*Param One : The direction of the mouse in the X axis
	*Param Two : The direction of the mouse in the Y axis
	*/
	void RotateWithMouse(float moveX, float moveY)
	{
		if (moveX != 0)
		{
			if (v_GameObjects.size() > 0)
			{
				for (unsigned int i = 0; i < v_GameObjects.size(); i++)
				{
					if (v_GameObjects[i]->m_id == "Player")
					{
						if (moveX > 0)
						{
							if (v_GameObjects[i]->getComponent<MoveComponent>() != nullptr)
							{
								v_GameObjects[i]->getComponent<MoveComponent>()->OnMessage("rotRight");
							}
						}
						else if (moveX < 0)
						{
							if (v_GameObjects[i]->getComponent<MoveComponent>() != nullptr)
							{
								v_GameObjects[i]->getComponent<MoveComponent>()->OnMessage("rotLeft");
							}
						}
					}
				}
			}
		}

		if (moveY != 0)
		{
			if (v_GameObjects.size() > 0)
			{
				for (unsigned int i = 0; i < v_GameObjects.size(); i++)
				{
					if (v_GameObjects[i]->m_id == "Camera")
					{
						if (moveY > 0)
						{
							if (v_GameObjects[i]->getComponent<CameraComponent>() != nullptr)
							{
								v_GameObjects[i]->getComponent<CameraComponent>()->OnMessage("rotUp");
							}
						}
						else if (moveY < 0)
						{
							if (v_GameObjects[i]->getComponent<CameraComponent>() != nullptr)
							{
								v_GameObjects[i]->getComponent<CameraComponent>()->OnMessage("rotDown");
							}
						}
					}
				}
			}
		}
		
	}

	//-----------------------------------------------------------//
	/*! OnMessage : This will be use to pass messages to specific objects. 
	*
	*/
	void m_OnMessage(std::string m)
	{
	}

};