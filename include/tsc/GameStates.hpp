#ifndef GAMESTATES_HPP
#define GAMESTATES_HPP
//------------------------------------------------------------------------
//
// Name: GameStates.hpp
//
// Desc: All the states that can be assigned to the Game class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

class GameClass;

// Provide easy access
#define GameIdleState GameIdle::Instance()
#define GameNewState GameNew::Instance()
#define GameLoadState GameLoad::Instance()
#define GameSaveState GameSave::Instance()
#define GameQuitState GameQuit::Instance()

//------------------------------------------------------------------------
//
// This is the Idle State for the GameClass
//
//------------------------------------------------------------------------
class GameIdle : public State<GameClass>
{
private:

	GameIdle(){}
	
	// Copy ctor and assignment should be private
	GameIdle(const GameIdle&);
	GameIdle &operator=(const GameIdle&);

public:

	// This is a singleton
	static GameIdle *Instance();
	
	void Enter(GameClass *game){}
	bool Update(GameClass *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(GameClass *game);
	void Exit(GameClass *game){}
	bool Receive(GameClass *game, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the New State for the GameClass
//
//------------------------------------------------------------------------
class GameNew : public State<GameClass>
{
private:

	GameNew(){}
	
	// Copy ctor and assignment should be private
	GameNew(const GameNew&);
	GameNew &operator=(const GameNew&);

public:

	// This is a singleton
	static GameNew *Instance();
	
	void Enter(GameClass *game){}
	bool Update(GameClass *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(GameClass *game);
	void Exit(GameClass *game){}
	bool Receive(GameClass *game, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Load Game State for the GameClass
//
//------------------------------------------------------------------------
class GameLoad : public State<GameClass>
{
private:
	
	GameLoad(){}

	// Copy ctor and assignment should be private
	GameLoad(const GameLoad&);
	GameLoad &operator=(const GameLoad&);
 
public:

	// This is a singleton
	static GameLoad *Instance();
	
	void Enter(GameClass *game){}
	bool Update(GameClass *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(GameClass *game);
	void Exit(GameClass *game){}
	bool Receive(GameClass *game, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Save Game State for the GameClass
//
//------------------------------------------------------------------------
class GameSave : public State<GameClass>
{
private:
	
	GameSave(){}

	// Copy ctor and assignment should be private
	GameSave(const GameSave&);
	GameSave &operator=(const GameSave&);
 
public:

	// This is a singleton
	static GameSave *Instance();
	
	void Enter(GameClass *game){}
	bool Update(GameClass *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(GameClass *game);
	void Exit(GameClass *game){}
	bool Receive(GameClass *game, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Quit State for the GameClass
//
//------------------------------------------------------------------------
class GameQuit : public State<GameClass>
{
private:

	GameQuit(){}
	
	// Copy ctor and assignment should be private
	GameQuit(const GameQuit&);
	GameQuit &operator=(const GameQuit&);

public:

	// This is a singleton
	static GameQuit *Instance();
	
	void Enter(GameClass *game){}
	bool Update(GameClass *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(GameClass *game);
	void Exit(GameClass *game){}
	bool Receive(GameClass *game, const Message &msg){return true;}

};

#endif
