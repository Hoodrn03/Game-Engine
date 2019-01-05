/*! \file This will be used to control the color of items within the engine. */

#pragma once
#include "Component.h"

// This will be a default value for a colour change on the attached object. 
#define COLOUR_ADJUSTMENT_VALUE 0.001f

/*! \class This is a component which will control an objects colour. */
class ColourComponent : public Component
{
public:

	ColourComponent() : m_colourValue(0) {};

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
		if (m == "increase")
		{
			m_colourValue += COLOUR_ADJUSTMENT_VALUE;
		}
		else if (m == "decrease")
		{
			m_colourValue -= COLOUR_ADJUSTMENT_VALUE;
		}
	}

	float m_colourValue;
};

class RedComponent : public ColourComponent {};
class GreenComponent : public ColourComponent {};
class BlueComponent : public ColourComponent {};