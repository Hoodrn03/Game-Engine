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

	/*! \var This will be used move the game object in a direction. */
	glm::vec3 m_MoveVector; 

public:

	// Member Functions 

	//-----------------------------------------------------------//
	/*! OnUpdate : This will be used to call any update functions for this component.
	*
	*/
	void OnUpdate(float dt) override
	{
		// If the move vector is not equal to (0, 0, 0) the object should be moving. 
		if (m_MoveVector != glm::vec3(0, 0, 0))
		{
			m_ThisObject->getComponent<TransformComponent>()->translate(m_MoveVector);

			m_MoveVector = glm::vec3(0, 0, 0);
		}
	}

	//-----------------------------------------------------------//
	/*! OnMessage : This will be use to react to a key press if required.
	*
	*/
	void OnMessage(const std::string m) override
	{

		// Use a direction in which to move and multiply it by the objects orientation; this will then use the 
		// direction the object is facing to move it in that direction. 
		if (m == "forward")
		{
			m_MoveVector = glm::vec3(0, 0, -TRANSLATE_VALUE) * m_ThisObject->getComponent<TransformComponent>()->m_orientation;
		}
		else if (m == "backward")
		{
			m_MoveVector = glm::vec3(0, 0, TRANSLATE_VALUE) * m_ThisObject->getComponent<TransformComponent>()->m_orientation; 
		}
		else if (m == "right")
		{
			m_MoveVector = glm::vec3(TRANSLATE_VALUE, 0, 0) * m_ThisObject->getComponent<TransformComponent>()->m_orientation;
		}
		else if (m == "left")
		{
			m_MoveVector = glm::vec3(-TRANSLATE_VALUE, 0, 0) * m_ThisObject->getComponent<TransformComponent>()->m_orientation;
		}

		if(m == "rotLeft")
		{
			m_ThisObject->getComponent<TransformComponent>()->yaw(ROTATION_VALUE); 
		}
		else if (m == "rotRight")
		{
			m_ThisObject->getComponent<TransformComponent>()->yaw(-ROTATION_VALUE);
		}
		
	}




};