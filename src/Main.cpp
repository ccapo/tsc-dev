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
	float elapsed;
	TCOD_key_t key;
	TCOD_mouse_t mouse;

	// Startup the Engine
	Engine()->Startup(narg, argv);

	// Loop through a few Update calls
	while(status && !TCODConsole::isWindowClosed())
	{
		// Update the Engine
		status = Engine()->Update(TCODSystem::getLastFrameLength(), key, mouse);

		// Render using the Engine
		Engine()->Render();

		// Flush Updates to Console
		TCODConsole::root->flush();

		// Get Keyboard and Mouse Input
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &key, &mouse);
	}

	// Shutdown the Engine
	Engine()->Shutdown();

	return 0;
}
