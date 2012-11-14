//------------------------------------------------------------------------
//
// Name: Main.cpp
//
// Desc: Calls and updates the game instance
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Main.hpp"

// Global Seed Value
uint32 seed = 0;

int main(int narg, char *argv[])
{
	bool status = true;

	// Startup the Game Engine
	GameEngine()->Startup(narg, argv);

	// Loop through a few Update calls
	while(status && !TCODConsole::isWindowClosed())
	{
		// Update the Game Engine
		status = GameEngine()->Update();

		// Render using the Game Engine
		GameEngine()->Render();
	}

	// Shutdown the Game Engine
	GameEngine()->Shutdown();

	return 0;
}
