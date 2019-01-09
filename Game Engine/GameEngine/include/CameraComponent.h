

#pragma once

#include "Component.h"
#include "Camera.h"

#define TRANSLATE_VALUE 0.01f

class CameraComponent : public Component
{

public: 

	CameraComponent(Camera* connectedCamera) : m_ThisCamera(connectedCamera) {};

	~CameraComponent() {};

	// Data Members 

private: 

	Camera *m_ThisCamera; 

public:

	// Member Functions 

	const Camera *m_GetCamera() const { return m_ThisCamera; }

	//-----------------------------------------------------------//
	/*! OnUpdate : This will be used to call any update functions for this component.
	*
	*/
	void OnUpdate(float dt) override
	{

	}

	//-----------------------------------------------------------//
	/*! OnMessage : This will be use to react to a key press if required.
	*
	*/
	void OnMessage(const std::string m) override
	{
		if (m == "forward")
		{
			m_ThisCamera->translate(0, 0, TRANSLATE_VALUE);
		}
		else if (m == "backward")
		{
			m_ThisCamera->translate(0, 0, -TRANSLATE_VALUE);
		}
		else if (m == "right")
		{
			m_ThisCamera->translate(-TRANSLATE_VALUE, 0, 0);
		}
		else if (m == "left")
		{
			m_ThisCamera->translate(TRANSLATE_VALUE, 0, 0);
		}
		else if (m == "up")
		{
			m_ThisCamera->translate(0, -TRANSLATE_VALUE, 0);
		}
		else if (m == "down")
		{
			m_ThisCamera->translate(0, TRANSLATE_VALUE, 0);
		}
		else
		{
			std::cout << "Not a command." << std::endl; 
		}
	}

};


