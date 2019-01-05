/*! \file This is the base component which all of the other engine components 
*			will inherit from. 
*/

#pragma once

#include <string>

/*!\class This is the base component and will be inherited from. */
class Component
{
public:

	//-----------------------------------------------------------//
	/*! OnUpdate : This will be used to call any update functions for this component.
	*
	*/
	virtual void OnUpdate(float dt) = 0;

	//-----------------------------------------------------------//
	/*! OnMessage : This will be use to react to a key press if required.
	*
	*/
	virtual void OnMessage(const std::string m) = 0;

};

