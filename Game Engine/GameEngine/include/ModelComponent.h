/*! \file This will allow for a game object to have a model attached to it. */

#pragma once

#include "Component.h"
#include "Model.h"

/*! \class This component will allow for the assignment of a model to a game object. */
class ModelComponent : public Component
{
public: 

	//-----------------------------------------------------------//
	/*! Constructor
	*Param One : The model the game object should display within the game. 
	*/
	ModelComponent(Model *targetModel) : m_ThisModel(targetModel) {}

	//-----------------------------------------------------------//
	/*! Deconstructor
	*
	*/
	~ModelComponent() {}

	// Data Members

	/*! \var The connected model. */
	Model * m_ThisModel; 

	// Member Functions

public:

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

	}

};
