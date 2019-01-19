/*! \file This will be used to handle the game object's positioning 
*			within the finalized game. 
*/

#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

/*!\ class This component will allow for a game object to be positioned 
*			within the game world. 
*/
class TransformComponent : public Component
{
public:

	//-----------------------------------------------------------//
	/*! Constructor
	*
	*/
	TransformComponent() : m_position(0), m_orientation(1, 0, 0, 0), m_scale(1.0f) {}

	//-----------------------------------------------------------//
	/*! Constructor
	*Param One : The position in world space for the connected game object.
	*/
	TransformComponent(const glm::vec3& pos) : m_position(pos), m_orientation(1, 0, 0, 0), m_scale(1.0f) {}

	//-----------------------------------------------------------//
	/*! Constructor
	*Param One : The position in world space for the connected game object.
	*Param Two : The direction the game object is facing.
	*/
	TransformComponent(const glm::vec3& pos, const glm::quat& orient) : m_position(pos), m_orientation(orient), m_scale(1.0f) {}

	//-----------------------------------------------------------//
	/*! Constructor
	*Param One : The position in world space for the connected game object.
	*Param Two : The direction the game object is facing.
	*Param Three : The scaled size of the game object.
	*/
	TransformComponent(const glm::vec3& pos, const glm::quat& orient, const glm::vec3& scale) : m_position(pos), m_orientation(orient), m_scale(scale) {}


	// Member Functions 

	//-----------------------------------------------------------//
	/*! OnUpdate : This will be used to update this component. 
	*
	*/
	void OnUpdate(float dt) override {}
	
	//-----------------------------------------------------------//
	/*! OnMessage : This will allow for the component to respond to a key press.  
	*
	*/
	void OnMessage(const std::string m) override {}

	//-----------------------------------------------------------//
	/*! Position : This will be used to return the value of position. 
	*
	*/
	const glm::vec3& position() const { return m_position; }
	
	//-----------------------------------------------------------//
	/*! Orientation : This will return the current direction the game object is facing. 
	*
	*/
	const glm::quat& orientation() const { return m_orientation; }
	
	//-----------------------------------------------------------//
	/*! Scale : This will return the current scale factor for the game object. 
	*
	*/
	const glm::vec3& scale() const { return m_scale; }

	//-----------------------------------------------------------//
	/*! GetModelMatrix : This will use the current transform data to form a complete model matrix 
	*						allowing for the game object to be drawn. 
	*
	*/
	glm::mat4 getModelMatrix()
	{
		glm::mat4 transMatrix = glm::translate(glm::mat4(1.0f), m_position);
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);
		glm::mat4 rotMatrix = glm::mat4_cast(m_orientation);
		return transMatrix * rotMatrix * scaleMatrix;
	}

	//-----------------------------------------------------------//
	/*! Translate : This will move the connected game object by the value of 'v'
	*Param One : a set of coordinate of which to move the object by. 
	*/
	void translate(const glm::vec3 &v) { m_position += v; }
	
	//-----------------------------------------------------------//
	/*! Translate : This will move the game objtect by an x, y, z vlaue. 
	*Param One : The X value to move. 
	*Param Two : The Y vlaue to move.
	*Param Three : The Z value to move.
	*/
	void translate(float x, float y, float z) { m_position += glm::vec3(x, y, z); }

	//-----------------------------------------------------------//
	/*! Rotate : This will rotate the game object around a single axis.
	*Param One : The angle of whic to rotate by. 
	*Param Two : The fixed axix to rotate the object around. 
	*/
	void rotate(float angle, const glm::vec3 &axis) { m_orientation *= glm::angleAxis(angle, axis * m_orientation); }
	
	//-----------------------------------------------------------//
	/*! Rotate : This will rotate the game object around a single axis.
	*Param One : The angle of whic to rotate by.
	*Param Two : The X for the fixed axix to rotate the object around.
	*Param Three : : The Y for the fixed axix to rotate the object around.
	*Param Four : The Z for the fixed axix to rotate the object around.
	*/
	void rotate(float angle, float x, float y, float z) { m_orientation *= glm::angleAxis(angle, glm::vec3(x, y, z) * m_orientation); }

	//-----------------------------------------------------------//
	/*! ScaleUp : This will increate the scale of the game object by 'v'. 
	*Param One : A set of value of which to scale the object by. 
	*/
	void scaleUp(const glm::vec3 &v) { m_scale += v; }
	
	//-----------------------------------------------------------//
	/*! ScaleUp : This will increate the scale of the game object by 'v'.
	*Param One : The value of which to scale the object in the X axis.
	*Param Two : The value of which to scale the object in the Y axis.
	*Param Three : The value of which to scale the object in the Z axis.
	*/
	void scaleUp(float x, float y, float z) { m_scale += glm::vec3(x, y, z); }

	//-----------------------------------------------------------//
	/*! Yaw : This will rotate the game object by the angle around the Z-Axis.
	*Param One : The angle of which to rotate by.
	*/
	void yaw(float angle) { rotate(angle, 0.0f, 1.0f, 0.0f); }

	//-----------------------------------------------------------//
	/*! Pitch : This will rotate the game object by the angle around the Y-Axis.
	*Param One : The angle of which to rotate by.
	*/
	void pitch(float angle) { rotate(angle, 1.0f, 0.0f, 0.0f); }

	//-----------------------------------------------------------//
	/*! Roll : This will rotate the game object by the angle around the X-Axis.
	*Param One : The angle of which to rotate by.
	*/
	void roll(float angle) { rotate(angle, 0.0f, 0.0f, 1.0f); }

protected: 

	// Data Members 

	/*! \var The game world position for the game object. */
	glm::vec3 m_position;

	/*! \var The current scale factor the game object currently has. */
	glm::vec3 m_scale;

public:

	/*! \var The direction the game object is currently facing. */
	glm::quat m_orientation;

};
