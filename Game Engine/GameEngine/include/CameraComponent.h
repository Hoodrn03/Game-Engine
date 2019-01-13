

#pragma once

#include "Component.h"

#include "GameObject.h"
#include "Camera.h"

#define MouseSpeed 0.0005f

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

	~CameraComponent() {};

	// Data Members 

private: 

	GameObject * m_ThisObject; 
	
	Camera * m_ThisCamera; 

	cameraType m_CameraType; 

	glm::vec3 m_CameraOffset; 

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
			m_ThisCamera->m_position = m_ThisObject->getComponent<TransformComponent>()->position() + m_CameraOffset;

			// std::cout << "CameraMove"; 
		}
	}

	//-----------------------------------------------------------//
	/*! OnMessage : This will be use to react to a key press if required.
	*
	*/
	void OnMessage(const std::string m) override
	{
	}

	void m_RotateCamera(float xAngle, float yAngle)
	{
		m_direction = glm::vec3(
			cos(yAngle) * sin(xAngle),
			sin(yAngle),
			cos(yAngle) * cos(xAngle)
		);

		// Right vector
		glm::vec3 l_right = glm::vec3(
			sin(xAngle - 3.14f / 2.0f),
			0,
			cos(xAngle - 3.14f / 2.0f)
		);

		// Up vector : perpendicular to both direction and right
		glm::vec3 l_up = glm::cross(l_right, m_direction);

		glm::mat4 viewMatrix = glm::lookAt(m_ThisCamera->position(), m_ThisCamera->position() + m_direction, l_up); 

		m_ThisCamera->m_ViewMatrix = viewMatrix; 

	}
};


