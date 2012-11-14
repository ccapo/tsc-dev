#ifndef PLAYERSTATES_HPP
#define PLAYERSTATES_HPP
//------------------------------------------------------------------------
//
// Name: PlayerStates.hpp
//
// Desc: All the states that can be assigned to the Player class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

class PlayerClass;

// Provide easy access
#define PlayerIdleState PlayerIdle::Instance()
#define PlayerIntroState PlayerIntro::Instance()
#define PlayerWorldState PlayerWorld::Instance()
#define PlayerTempleState PlayerTemple::Instance()
#define PlayerTownState PlayerTown::Instance()
#define PlayerCaveState PlayerCave::Instance()
#define PlayerRestState PlayerRest::Instance()

//-------------------------------------------------------------------------
//
// In this state the Player is Idle
//
//-------------------------------------------------------------------------
class PlayerIdle : public State<PlayerClass>
{
private:
	
	PlayerIdle(){}

	// Copy ctor and assignment should be private
	PlayerIdle(const PlayerIdle&);
	PlayerIdle &operator=(const PlayerIdle&);
 
public:

	// This is a singleton
	static PlayerIdle *Instance();

	void Enter(PlayerClass *player);
	bool Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(PlayerClass *player);
	void Exit(PlayerClass *player){}
	bool Receive(PlayerClass *player, const Message &msg){return true;}

};

//-------------------------------------------------------------------------
//
// In this state the Player is in the Introduction
//
//-------------------------------------------------------------------------
class PlayerIntro : public State<PlayerClass>
{
private:
	
	PlayerIntro(){}

	// Copy ctor and assignment should be private
	PlayerIntro(const PlayerIntro&);
	PlayerIntro &operator=(const PlayerIntro&);
 
public:

	// This is a singleton
	static PlayerIntro *Instance();

	void Enter(PlayerClass *player);
	bool Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(PlayerClass *player);
	void Exit(PlayerClass *player){}
	bool Receive(PlayerClass *player, const Message &msg){return true;}

};

//-------------------------------------------------------------------------
//
// In this state the Player is in the World Map
//
//-------------------------------------------------------------------------
class PlayerWorld : public State<PlayerClass>
{
private:
	
	PlayerWorld(){}

	// Copy ctor and assignment should be private
	PlayerWorld(const PlayerWorld&);
	PlayerWorld &operator=(const PlayerWorld&);
 
public:

	// This is a singleton
	static PlayerWorld *Instance();

	void Enter(PlayerClass *player);
	bool Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(PlayerClass *player);
	void Exit(PlayerClass *player){}
	bool Receive(PlayerClass *player, const Message &msg){return true;}

};

//-------------------------------------------------------------------------
//
// In this state the Player is in the Temple Map
//
//-------------------------------------------------------------------------
class PlayerTemple : public State<PlayerClass>
{
private:
	
	PlayerTemple(){}

	// Copy ctor and assignment should be private
	PlayerTemple(const PlayerTemple&);
	PlayerTemple &operator=(const PlayerTemple&);
 
public:

	// This is a singleton
	static PlayerTemple *Instance();

	void Enter(PlayerClass *player);
	bool Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(PlayerClass *player);
	void Exit(PlayerClass *player){}
	bool Receive(PlayerClass *player, const Message &msg){return true;}

};

//-------------------------------------------------------------------------
//
// In this state the Player is in the Town Map
//
//-------------------------------------------------------------------------
class PlayerTown : public State<PlayerClass>
{
private:
	
	PlayerTown(){}

	// Copy ctor and assignment should be private
	PlayerTown(const PlayerTown&);
	PlayerTown &operator=(const PlayerTown&);
 
public:

	// This is a singleton
	static PlayerTown *Instance();
	void Enter(PlayerClass *player);
	bool Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(PlayerClass *player);
	void Exit(PlayerClass *player){}
	bool Receive(PlayerClass *player, const Message &msg){return true;}

};

//-------------------------------------------------------------------------
//
// In this state the Player is in the Cave Map
//
//-------------------------------------------------------------------------
class PlayerCave : public State<PlayerClass>
{
private:
	
	PlayerCave(){}

	// Copy ctor and assignment should be private
	PlayerCave(const PlayerCave&);
	PlayerCave &operator=(const PlayerCave&);
 
public:

	// This is a singleton
	static PlayerCave *Instance();

	void Enter(PlayerClass *player);
	bool Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(PlayerClass *player);
	void Exit(PlayerClass *player){}
	bool Receive(PlayerClass *player, const Message &msg){return true;}

};

//----------------------------------------------------------------------------
//
// In this state the Player is at Rest
//
//----------------------------------------------------------------------------
class PlayerRest : public State<PlayerClass>
{
private:
	
	PlayerRest(){}

	// Copy ctor and assignment should be private
	PlayerRest(const PlayerRest&);
	PlayerRest &operator=(const PlayerRest&);
 
public:

	// This is a singleton
	static PlayerRest *Instance();

	void Enter(PlayerClass *player);
	bool Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(PlayerClass *player);
	void Exit(PlayerClass *player){}
	bool Receive(PlayerClass *player, const Message &msg){return true;}

};

#endif
