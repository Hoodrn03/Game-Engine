/*! \file The camera will be used to display all of the items in the scene. */

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

/*! class The camera will be used to display all of the items in the scene. */
class Camera
{
public:

	// Data Members

	/*! \var The current position of the game camera. */
	glm::vec3 m_position;

	/*! \var The current direnction the camera is facing. */
	glm::quat m_orientation;

	/*! \var The field of view for the camera. */
	float m_fov;
	
	glm::mat4 m_ViewMatrix; 

	// Member Functions. 

public:

	//-----------------------------------------------------------//
	/*! Constructor 
	*
	*/
	Camera() : m_position(0), m_orientation(1,0,0,0), m_fov(45) {}

	//-----------------------------------------------------------//
	/*! Constructor
	*Param One : The starting position for the camera. 
	*/
	Camera(const glm::vec3& pos) : m_position(pos), m_orientation(1, 0, 0, 0),m_fov(45) {}

	//-----------------------------------------------------------//
	/*! Constructor
	*Param One : The starting position for the camera.
	*Param Two : The orientation for the starting camera. 
	*/
	Camera(const glm::vec3& pos, const glm::quat& orient) : m_position(pos), m_orientation(orient), m_fov(45) {}

	//-----------------------------------------------------------//
	/*! LookAt : This will be used to point the camera at a specific target. 
	*Param One : The vector3 for the target you wish to look at. 
	*/
	void lookAt(const glm::vec3& target) { m_orientation = (glm::toQuat(glm::lookAt(m_position, target, glm::vec3(0, 1, 0)))); }
	
	//-----------------------------------------------------------//
	/*! Position : This will return the current position of the camera. 
	*
	*/
	const glm::vec3& position() const { return m_position; }

	//-----------------------------------------------------------//
	/*! Orientation : This will return the current orientation of the camera. 
	*
	*/
	const glm::quat& orientation() const { return m_orientation; }

	//-----------------------------------------------------------//
	/*! GetViewMatrix : This will be used to transform vertices from world space to
	*						view space.
	*/
	glm::mat4 getViewMatrix() const { return m_ViewMatrix; }
	
	//-----------------------------------------------------------//
	/*! Translate : This will move the camera in the game space. 
	*Param One : A combination of X, Y and Z values for the new position. 
	*/
	void translate(const glm::vec3 &v) { m_position += v * m_orientation; }

	//-----------------------------------------------------------//
	/*! Translate : This will move the camera in the game space.
	*Param One : The new X value for the camera.
	*Param Two : The new Y value for the camera.
	*Param Three : The new Z value for the camera. 
	*/
	void translate(float x, float y, float z) { m_position += glm::vec3(x, y, z) * m_orientation; }

	//-----------------------------------------------------------//
	/*! Rotate : This will rotate the camera by a specific angle.  
	*Param One : The angle in which to rotate by. 
	*Param Two : The axis to rotate the camrea around. 
	*/
	void rotate(float angle, const glm::vec3 &axis) { m_orientation *= glm::angleAxis(angle, axis * m_orientation); }

	//-----------------------------------------------------------//
	/*! Rotate : This will rotate the camera by a specific angle.
	*Param One : The angle in which to rotate by.
	*Param Two : The new X value for the rotation's axis.
	*Param Three : The new Y value for the rotation's axis.
	*Param Four : The new Z value for the rotation's axis.
	*/
	void rotate(float angle, float x, float y, float z) { m_orientation *= glm::angleAxis(angle, glm::vec3(x, y, z) * m_orientation); }

	//-----------------------------------------------------------//
	/*! Yaw : This will rotate the camera by the angle around the Z-Axis.
	*Param One : The angle of which to rotate by. 
	*/
	void yaw(float angle) { rotate(angle, 0.0f, 1.0f, 0.0f); }

	//-----------------------------------------------------------//
	/*! Pitch : This will rotate the camera by the angle around the Y-Axis.
	*Param One : The angle of which to rotate by. 
	*/
	void pitch(float angle) { rotate(angle, 1.0f, 0.0f, 0.0f); }

	//-----------------------------------------------------------//
	/*! Roll : This will rotate the camera by the angle around the X-Axis.
	*Param One : The angle of which to rotate by. 
	*/
	void roll(float angle) { rotate(angle, 0.0f, 0.0f, 1.0f); }

	//-----------------------------------------------------------//
	/*! SetFOV : This will set a new value for the camera's field of view. 
	*Param One : The new field of view for the camera. 
	*/
	void setFOV(float fov) { m_fov = fov; }

	//-----------------------------------------------------------//
	/*! GetFOV : This will be used to get the current field of view. 
	*/
	const float getFOV() const { return m_fov; }
};
