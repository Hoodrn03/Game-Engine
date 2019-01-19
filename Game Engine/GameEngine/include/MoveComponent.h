/*! \file This component will be used to move the connected game object. */

#pragma once

#include <iostream>

#include "Component.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "CameraComponent.h"

#define TRANSLATE_VALUE 0.01f
#define ROTATION_VALUE 0.005f

/*! \class This component will be used to move the connected game object. */
class MoveComponent : public Component
{

public: 

	//-----------------------------------------------------------//
	/*! Constructor
	*Param One : This is the object this component is connected to.
	*/
	MoveComponent(GameObject * movableObject) : m_ThisObject(movableObject) {};

	//-----------------------------------------------------------//
	/*! Deconstructor
	*
	*/
	~MoveComponent() {};

private:

	// Data Members 

	/*! \var The game object this is connected to. */
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