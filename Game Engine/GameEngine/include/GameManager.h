#pragma once

#include "GameObject.h"

#include "TransformComponent.h"
#include "MoveComponent.h"
#include "CameraComponent.h"
#include "Model.h"
#include "ModelComponent.h"

class GameManager
{

public:

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

	~GameManager() {}

	// Data Members

private:

	std::vector<GameObject*> v_GameObjects; 

	// Member Functions

public:

	GameObject* m_GetGameObject(int identifier) { return v_GameObjects[identifier]; }

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
					if (v_GameObjects[i]->m_id == "Player")
					{
						if (moveY > 0)
						{
							if (v_GameObjects[i]->getComponent<MoveComponent>() != nullptr)
							{
								v_GameObjects[i]->getComponent<MoveComponent>()->OnMessage("rotUp");
							}
						}
						else if (moveY < 0)
						{
							if (v_GameObjects[i]->getComponent<MoveComponent>() != nullptr)
							{
								v_GameObjects[i]->getComponent<MoveComponent>()->OnMessage("rotDown");
							}
						}
					}
				}
			}
		}
		
	}

	void m_OnMessage(std::string m)
	{
	}

};