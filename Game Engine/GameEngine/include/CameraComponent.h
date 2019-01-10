

#pragma once

#include "Component.h"

#include "GameObject.h"
#include "Camera.h"

class CameraComponent : public Component
{

public: 

	CameraComponent(Camera* connectCamera, GameObject* connectObject) : 
		m_ThisCamera(connectCamera), m_ThisObject(connectObject) {};

	~CameraComponent() {};

	// Data Members 

private: 

	GameObject * m_ThisObject; 
	
	Camera * m_ThisCamera; 

public:

	// Member Functions 

	const Camera *m_GetCamera() const { return m_ThisCamera; }

	//-----------------------------------------------------------//
	/*! OnUpdate : This will be used to call any update functions for this component.
	*
	*/
	void OnUpdate(float dt) override
	{
		if (m_ThisObject->getComponent<TransformComponent>()->position() != m_ThisCamera->position())
		{
			m_ThisCamera->m_position = m_ThisObject->getComponent<TransformComponent>()->position();
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


