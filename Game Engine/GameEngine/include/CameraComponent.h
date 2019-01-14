

#pragma once

#include "Component.h"

#include "GameObject.h"
#include "Camera.h"

#define MouseSpeed 0.0005f

#define ROTATION_VALUE 0.005f

enum cameraType
{
	staticCamera = 0x300,
	thirdPersonCamera = 0x400,
	firstPersonCamera = 0x500
};


class CameraComponent : public Component
{

public: 

	CameraComponent(Camera* connectCamera, GameObject* connectObject) : 
		m_ThisCamera(connectCamera), m_ThisObject(connectObject) {};

	CameraComponent(Camera* connectCamera, GameObject* connectObject, glm::vec3 offset) :
		m_ThisCamera(connectCamera), m_ThisObject(connectObject), m_CameraOffset(offset) {};

	CameraComponent(Camera* connectCamera, GameObject* connectObject, cameraType selection) :
		m_ThisCamera(connectCamera), m_ThisObject(connectObject), m_CameraType(selection) 
	{
		switch (m_CameraType)
		{
		case staticCamera:
			break;

		case firstPersonCamera:
			m_CameraOffset = glm::vec3(0, 1, 0);
			break;

		case thirdPersonCamera:
			m_CameraOffset = glm::vec3(0, 2, -2);
			break;

		default:
			break;
		}
	};

	CameraComponent(Camera* connectCamera, GameObject* connectObject, glm::vec3 offset, cameraType selection) :
		m_ThisCamera(connectCamera), m_ThisObject(connectObject), m_CameraOffset(offset), m_CameraType(selection) {};

	~CameraComponent() {};

	// Data Members 

public:

	cameraType m_CameraType;

private: 

	GameObject * m_ThisObject; 
	
	Camera * m_ThisCamera; 

	glm::vec3 m_CameraOffset = glm::vec3(0, 0, 0); 

	glm::vec3 m_direction; 

public:

	// Member Functions 

	Camera &m_GetCamera() { return *m_ThisCamera; }

	void m_SetCameraOffset(glm::vec3 newCameraOffset) { m_CameraOffset = newCameraOffset; }

	//-----------------------------------------------------------//
	/*! OnUpdate : This will be used to call any update functions for this component.
	*
	*/
	void OnUpdate(float dt) override
	{
		if (m_ThisCamera->position() != m_ThisObject->getComponent<TransformComponent>()->position())
		{
			switch (m_CameraType)
			{
			case staticCamera:
				break;

			case firstPersonCamera:
				
				m_ThisCamera->m_position = m_ThisObject->getComponent<TransformComponent>()->position() + m_CameraOffset;
				
				if (m_ThisCamera->orientation().y != m_ThisObject->getComponent<TransformComponent>()->orientation().y)
				{
					m_ThisCamera->m_orientation.y = m_ThisObject->getComponent<TransformComponent>()->orientation().y;
					m_ThisCamera->m_orientation.z = m_ThisObject->getComponent<TransformComponent>()->orientation().z;
					m_ThisCamera->m_orientation.w = m_ThisObject->getComponent<TransformComponent>()->orientation().w;
				}

				break;

			case thirdPersonCamera:

				m_ThisCamera->m_position = m_ThisObject->getComponent<TransformComponent>()->position() + m_CameraOffset;
				m_ThisCamera->lookAt(m_ThisObject->getComponent<TransformComponent>()->position());
				
				break;
			
			default:
				
				m_ThisCamera->m_position = m_ThisObject->getComponent<TransformComponent>()->position() + m_CameraOffset;

				if (m_ThisCamera->orientation().y != m_ThisObject->getComponent<TransformComponent>()->orientation().y)
				{
					m_ThisCamera->m_orientation.y = m_ThisObject->getComponent<TransformComponent>()->orientation().y;
					m_ThisCamera->m_orientation.z = m_ThisObject->getComponent<TransformComponent>()->orientation().z;
					m_ThisCamera->m_orientation.w = m_ThisObject->getComponent<TransformComponent>()->orientation().w;
				}

				break;
			}
		}
	}

	//-----------------------------------------------------------//
	/*! OnMessage : This will be use to react to a key press if required.
	*
	*/
	void OnMessage(const std::string m) override
	{
		if (m == "rotUp")
		{
			m_ThisCamera->pitch(-ROTATION_VALUE);
		}
		else if (m == "rotDown")
		{
			m_ThisCamera->pitch(ROTATION_VALUE);
		}
	}
};


