#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for GameIdle
//
//------------------------------------------------------------------------
GameIdle *GameIdle::Instance()
{
	static GameIdle instance;
	return &instance;
}

bool GameIdle::Update(GameClass *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void GameIdle::Render(GameClass *game){}

//------------------------------------------------------------------------
//
// Methods for GameNew
//
//------------------------------------------------------------------------
GameNew *GameNew::Instance()
{
	static GameNew instance;
	return &instance;
}

bool GameNew::Update(GameClass *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	if(game->IsProgressComplete())
	{
		game->ResetProgress();
		Transmit->Send(GameEngine(), MSG_INTROGAME);
	}
	else
	{
#ifndef DEV
		usleep(250000);
#endif
		game->IncrementProgress();
	}

	return true;
}

void GameNew::Render(GameClass *game){}

//------------------------------------------------------------------------
//
// Methods for GameLoad
//
//------------------------------------------------------------------------
GameLoad *GameLoad::Instance()
{
	static GameLoad instance;
	return &instance;
}

bool GameLoad::Update(GameClass *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	if(game->IsProgressComplete())
	{
		game->ResetProgress();
		game->InGame(true);
		Transmit->Send(GameEngine(), MSG_ENTERWORLD);
	}
	else
	{
#ifndef DEV
		usleep(250000);
#endif
		game->IncrementProgress();
	}

	return true;
}

void GameLoad::Render(GameClass *game){}

//------------------------------------------------------------------------
//
// Methods for GameSave
//
//------------------------------------------------------------------------
GameSave *GameSave::Instance()
{
	static GameSave instance;
	return &instance;
}

bool GameSave::Update(GameClass *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	if(game->IsProgressComplete())
	{
		game->ResetProgress();
		Transmit->Send(GameEngine(), MSG_ENTERWORLD);
	}
	else
	{
#ifndef DEV
		usleep(250000);
#endif
		game->IncrementProgress();
	}

	return true;
}

void GameSave::Render(GameClass *game){}

//------------------------------------------------------------------------
//
// Methods for GameQuit
//
//------------------------------------------------------------------------
GameQuit *GameQuit::Instance()
{
	static GameQuit instance;
	return &instance;
}

bool GameQuit::Update(GameClass *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return false;}
void GameQuit::Render(GameClass *game){}
