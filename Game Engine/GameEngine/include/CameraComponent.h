/*! \file This will be used to add a camera to a game object. */

#pragma once

#include "Component.h"

#include "GameObject.h"
#include "Camera.h"

#define ROTATION_VALUE 0.005f

/*! \enum The type of camera for the object. */
enum cameraType
{
	staticCamera = 0x300, 
	thirdPersonCamera = 0x400,
	firstPersonCamera = 0x500
};

/*! \class This component will allow for a camera to be attached to an object. */
class CameraComponent : public Component
{

public: 

	//-----------------------------------------------------------//
	/*! Constructor
	*Param One : The camera object connected to this object. 
	*Param Two : The game object this component is connected to. 
	*/
	CameraComponent(Camera* connectCamera, GameObject* connectObject) : 
		m_ThisCamera(connectCamera), m_ThisObject(connectObject) {};

	//-----------------------------------------------------------//
	/*! Constructor
	*Param One : The camera object connected to this object. 
	*Param Two : The game object this component is connected to. 
	*Param Three : The offset of the camera from the game object. 
	*/
	CameraComponent(Camera* connectCamera, GameObject* connectObject, glm::vec3 offset) :
		m_ThisCamera(connectCamera), m_ThisObject(connectObject), m_CameraOffset(offset) {};

	//-----------------------------------------------------------//
	/*! Constructor
	*Param One : The camera object connected to this object.
	*Param Two : The game object this component is connected to.
	*Param Three : The type for this camera. 
	*/
	CameraComponent(Camera* connectCamera, GameObject* connectObject, cameraType selection) :
		m_ThisCamera(connectCamera), m_ThisObject(connectObject), m_CameraType(selection) 
	{
		switch (m_CameraType)
		{
		case staticCamera:
			break;

		case firstPersonCamera:
			m_CameraOffset = glm::vec3(0, -0.75, 0);
			break;

		case thirdPersonCamera:
			m_CameraOffset = glm::vec3(0, -1, -3);
			break;

		default:
			break;
		}
	};

	//-----------------------------------------------------------//
	/*! Constructor
	*Param One : The camera object connected to this object.
	*Param Two : The game object this component is connected to.
	*Param Three : The offset of the camera from the game object.
	*Param Four : The type for this camera.
	*/
	CameraComponent(Camera* connectCamera, GameObject* connectObject, glm::vec3 offset, cameraType selection) :
		m_ThisCamera(connectCamera), m_ThisObject(connectObject), m_CameraOffset(offset), m_CameraType(selection) {};

	//-----------------------------------------------------------//
	/*! Deconstructor
	*
	*/
	~CameraComponent() {};

	// Data Members 

public:

	/*! \var The current type for this camera. */
	cameraType m_CameraType;

private: 

	/*! \var The game object this camera is connected to. */
	GameObject * m_ThisObject; 
	
	/*! \var The camera object to connect to the object. */
	Camera * m_ThisCamera; 

	/*! \var The offset applied to the camera. */
	glm::vec3 m_CameraOffset = glm::vec3(0, 0, 0); 

public:

	// Member Functions 

	//-----------------------------------------------------------//
	/*! GetCamera : This will return the connected game object. 
	*
	*/
	Camera &m_GetCamera() { return *m_ThisCamera; }

	//-----------------------------------------------------------//
	/*! SetCameraOffset
	*Param One : The vector (X, Y, Z) to offset the camera by. 
	*/
	void m_SetCameraOffset(glm::vec3 newCameraOffset) { m_CameraOffset = newCameraOffset; }

	//-----------------------------------------------------------//
	/*! OnUpdate : This will be used to call any update functions for this component.
	*
	*/
	void OnUpdate(float dt) override
	{
		if (m_CameraType == firstPersonCamera)
		{
			m_ThisCamera->m_position = (-m_ThisObject->getComponent<TransformComponent>()->position() + m_CameraOffset);

			m_ThisCamera->m_orientation = glm::quat(-m_ThisObject->getComponent<TransformComponent>()->orientation());
		}

		else if (m_CameraType == thirdPersonCamera)
		{
			m_ThisCamera->m_position = (-m_ThisObject->getComponent<TransformComponent>()->position() + m_CameraOffset);
		}
	}

	//-----------------------------------------------------------//
	/*! OnMessage : This will be use to react to a key press if required.
	*
	*/
	void OnMessage(const std::string m) override
	{

	}
};


