/*! \file This wil be the base engine core for the game engine, this will be evpaned upon
*			to create a better functioning game engine for different systems. 
*/

#pragma once

#include <string>
#include <iostream>
#include <glm/mat4x4.hpp>

#include "Model.h"

class Camera;
class Game;

/*! \class This will be the base engine core with the neccesary functions for the finilazed agem engine. */
class IEngineCore
{
public:

	//-----------------------------------------------------------//
	/*! Deconstructor
	*
	*/
	virtual ~IEngineCore() {}

	//-----------------------------------------------------------//
	/*! InitWindow : This will be used to crate the game window. 
	*Param One : The width for the game window. 
	*Param Two : The height for the game window. 
	*Param Three : The name for the game window. 
	*/
	virtual bool initWindow(int width, int height, std::string windowName) = 0;

	//-----------------------------------------------------------//
	/*! RunEngine : This will be used to run the main game loop. 
	*Param One : The game to run. 
	*/
	virtual bool runEngine(Game& game) = 0;

	// some simple drawing tools - will want to move these to a proper renderer class later
	
	//-----------------------------------------------------------//
	/*! RenderColouredBackground : This will be used to display a colourd background within the game.
	*Param One : The Red value.
	*Param Two : The Green value.
	*Param Three : The Blue value.
	*/
	virtual void renderColouredBackground(float r, float g, float b) = 0;
	
	//-----------------------------------------------------------//
	/*! SetCamera : This will be used to set the camera which will be used to display the scene.
	*Param One : The camera which will be used for the game engine.
	*/
	virtual	void setCamera(const Camera* cam) = 0;
	
	//-----------------------------------------------------------//
	/*! DrawCube : This will draw all of the objects in a given scene as a cube.
	*Param One : The model matrix of the object which should be drawn, (position, scale, ext.).
	*/
	virtual void drawCube(const glm::mat4& modelMatrix) = 0;
	
	//-----------------------------------------------------------//
	/*! DrawModel : This will be used to draw the models into a scene.
	*Param One : The model which should be drawn.
	*Param Two : The model matrix for that model, (position, scale, ext.).
	*/
	virtual void drawModel(Model * model, glm::mat4 & modelMatrix) = 0;
};
