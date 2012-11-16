#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP
//------------------------------------------------------------------------
//
// Name: GameEngine.hpp
//
// Desc: Singleton class to handle the management of modules
//
// Author: Chris Capobianco, 2012-10-06
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Sound.hpp"

class Module;

// Provide easy access
#define GameEngine() GameEngineClass::Instance()

class GameEngineClass
{
private:

	// A pointer to the game module
	GameClass *m_Game;

	// A pointer to the menu module
	MenuClass *m_Menu;

	// A pointer to the map module
	MapClass *m_Map;

	// A pointer to the sound module
	SoundClass *m_Sound;

	// A pointer to the player module
	PlayerClass *m_Player;

	// Fade In and Flag Out flags
	bool m_FadeIn, m_FadeOut;

	// Elapsed Time
	float m_ElapsedTime;

	GameEngineClass() : m_FadeIn(false), m_FadeOut(false), m_ElapsedTime(0.0f){}

	// Copy ctor and assignment should be private
	GameEngineClass(const GameEngineClass&);
	GameEngineClass &operator=(const GameEngineClass&);

public:

	static GameEngineClass *Instance();

	// Startup Game Engine
	void Startup(int narg, char *argv[]);

	// Shutdown Game Engine
	void Shutdown();

	// Update all the Modules
	bool Update(float elapsed, TCOD_key_t key, TCOD_mouse_t mouse);

	// Render all the Modules
	void Render();

	// Receive all messages
	bool Receive(const Message &msg);

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	GameClass *Game() const {return m_Game;}
	void Game(GameClass *pGame){m_Game = pGame;}

	MenuClass *Menu() const {return m_Menu;}
	void Menu(MenuClass *pMenu){m_Menu = pMenu;}

	MapClass *Map() const {return m_Map;}
	void Map(MapClass *pMap){m_Map = pMap;}

	SoundClass *Sound() const {return m_Sound;}
	void Sound(SoundClass *pSound){m_Sound = pSound;}

	PlayerClass *Player() const {return m_Player;}
	void Player(PlayerClass *pPlayer){m_Player = pPlayer;}

	bool FadeIn() const {return m_FadeIn;}
	void FadeIn(bool pFadeIn){m_FadeIn = pFadeIn;}

	bool FadeOut() const {return m_FadeOut;}
	void FadeOut(bool pFadeOut){m_FadeOut = pFadeOut;}

	float ElapsedTime() const {return m_ElapsedTime;}
	void UpdateElapsedTime(float pElapsed){m_ElapsedTime += pElapsed;}

};

#endif
