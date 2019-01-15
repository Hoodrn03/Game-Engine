
#pragma once

#include <iostream>

#include "Component.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "CameraComponent.h"

#define TRANSLATE_VALUE 0.01f
#define ROTATION_VALUE 0.005f

class MoveComponent : public Component
{

public: 

	MoveComponent(GameObject * movableObject) : m_ThisObject(movableObject) {};

	~MoveComponent() {};

private:

	// Data Members 

	GameObject * m_ThisObject; 

public:

	// Member Functions 

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
			m_ThisObject->getComponent<TransformComponent>()->translate(0, 0, -TRANSLATE_VALUE);
		}
		else if (m == "backward")
		{
			m_ThisObject->getComponent<TransformComponent>()->translate(0, 0, TRANSLATE_VALUE);
		}
		else if (m == "right")
		{
			m_ThisObject->getComponent<TransformComponent>()->translate(TRANSLATE_VALUE, 0, 0);
		}
		else if (m == "left")
		{
			m_ThisObject->getComponent<TransformComponent>()->translate(-TRANSLATE_VALUE, 0, 0);
		}
		else if (m == "rotLeft")
		{
			m_ThisObject->getComponent<TransformComponent>()->yaw(ROTATION_VALUE); 
		}
		else if (m == "rotRight")
		{
			m_ThisObject->getComponent<TransformComponent>()->yaw(-ROTATION_VALUE);
		}
		
	}




};