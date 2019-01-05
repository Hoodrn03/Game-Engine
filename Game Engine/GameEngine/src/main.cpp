/*! \file This will be the entry point for the application, it will initiate all of 
*			the game items, as well as select the engine core (system the application 
*			will run on).
*/

#define USE_GLFW 1
#ifdef USE_GLFW
	#include "GLFW_EngineCore.h"
#endif

#include "Game.h"


//-----------------------------------------------------------//
/*! Main : The entry point for the application. 
*
*/
int main(int argc, char* argv[])
{
	/*! \var The engine core for the game. Yet to be selected.*/
	IEngineCore* l_EngineCore;

	/*! \var The name for the running game.*/
	std::string l_GameName = "Game Engine"; 


	// Select which engine core to use. 
#ifdef USE_GLFW
	l_EngineCore = new GLFW_EngineCore;
#endif

	if (!l_EngineCore->initWindow(800, 600, l_GameName))
	{
		return -1;
	}

	/*! \var The game to be run. */
	Game l_GameEngine;

	l_EngineCore->runEngine(l_GameEngine);

	return 0;
}
