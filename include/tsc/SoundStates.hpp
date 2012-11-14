#ifndef SOUNDSTATES_HPP
#define SOUNDSTATES_HPP
//------------------------------------------------------------------------
//
// Name: SoundStates.hpp
//
// Desc: All the states that can be assigned to the Sound class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

class SoundClass;

// Provide easy access
#define SoundIdleState SoundIdle::Instance()
#define SoundMainMenuState SoundMainMenu::Instance()
#define SoundNewState SoundNew::Instance()
#define SoundWorldState SoundWorld::Instance()
#define SoundTempleState SoundTemple::Instance()
#define SoundTownState SoundTown::Instance()
#define SoundCaveState SoundCave::Instance()
#define SoundRestState SoundRest::Instance()
#define SoundQuitState SoundQuit::Instance()

//------------------------------------------------------------------------
//
// This is the Idle State for the SoundClass
//
//------------------------------------------------------------------------
class SoundIdle : public State<SoundClass>
{
private:
	
	SoundIdle(){}

	// Copy ctor and assignment should be private
	SoundIdle(const SoundIdle&);
	SoundIdle &operator=(const SoundIdle&);
 
public:

	// This is a singleton
	static SoundIdle *Instance();
	
	void Enter(SoundClass *sound){}
	bool Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(SoundClass *sound);
	void Exit(SoundClass *sound){}
	bool Receive(SoundClass *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Main Menu State for the SoundClass
//
//------------------------------------------------------------------------
class SoundMainMenu : public State<SoundClass>
{
private:
	
	SoundMainMenu(){}

	// Copy ctor and assignment should be private
	SoundMainMenu(const SoundMainMenu&);
	SoundMainMenu &operator=(const SoundMainMenu&);
 
public:

	// This is a singleton
	static SoundMainMenu *Instance();
	
	void Enter(SoundClass *sound);
	bool Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(SoundClass *sound);
	void Exit(SoundClass *sound);
	bool Receive(SoundClass *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the New Game State for the SoundClass
//
//------------------------------------------------------------------------
class SoundNew : public State<SoundClass>
{
private:

	SoundNew(){}
	
	// Copy ctor and assignment should be private
	SoundNew(const SoundNew&);
	SoundNew &operator=(const SoundNew&);

public:

	// This is a singleton
	static SoundNew *Instance();
	
	void Enter(SoundClass *sound);
	bool Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(SoundClass *sound);
	void Exit(SoundClass *sound);
	bool Receive(SoundClass *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the World State for the SoundClass
//
//------------------------------------------------------------------------
class SoundWorld : public State<SoundClass>
{
private:

	SoundWorld(){}
	
	// Copy ctor and assignment should be private
	SoundWorld(const SoundWorld&);
	SoundWorld &operator=(const SoundWorld&);

public:

	// This is a singleton
	static SoundWorld *Instance();
	
	void Enter(SoundClass *sound);
	bool Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(SoundClass *sound);
	void Exit(SoundClass *sound);
	bool Receive(SoundClass *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Temple State for the SoundClass
//
//------------------------------------------------------------------------
class SoundTemple : public State<SoundClass>
{
private:
	
	SoundTemple(){}

	// Copy ctor and assignment should be private
	SoundTemple(const SoundTemple&);
	SoundTemple &operator=(const SoundTemple&);
 
public:

	// This is a singleton
	static SoundTemple *Instance();
	
	void Enter(SoundClass *sound);
	bool Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(SoundClass *sound);
	void Exit(SoundClass *sound);
	bool Receive(SoundClass *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Town State for the SoundClass
//
//------------------------------------------------------------------------
class SoundTown : public State<SoundClass>
{
private:
	
	SoundTown(){}

	// Copy ctor and assignment should be private
	SoundTown(const SoundTown&);
	SoundTown &operator=(const SoundTown&);
 
public:

	// This is a singleton
	static SoundTown *Instance();
	
	void Enter(SoundClass *sound);
	bool Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(SoundClass *sound);
	void Exit(SoundClass *sound);
	bool Receive(SoundClass *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Cave State for the SoundClass
//
//------------------------------------------------------------------------
class SoundCave : public State<SoundClass>
{
private:
	
	SoundCave(){}

	// Copy ctor and assignment should be private
	SoundCave(const SoundCave&);
	SoundCave &operator=(const SoundCave&);
 
public:

	// This is a singleton
	static SoundCave *Instance();
	
	void Enter(SoundClass *sound);
	bool Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(SoundClass *sound);
	void Exit(SoundClass *sound);
	bool Receive(SoundClass *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Rest State for the SoundClass
//
//------------------------------------------------------------------------
class SoundRest : public State<SoundClass>
{
private:
	
	SoundRest(){}

	// Copy ctor and assignment should be private
	SoundRest(const SoundRest&);
	SoundRest &operator=(const SoundRest&);
 
public:

	// This is a singleton
	static SoundRest *Instance();
	
	void Enter(SoundClass *sound);
	bool Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(SoundClass *sound);
	void Exit(SoundClass *sound);
	bool Receive(SoundClass *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Quit State for the SoundClass
//
//------------------------------------------------------------------------
class SoundQuit : public State<SoundClass>
{
private:
	
	SoundQuit(){}

	// Copy ctor and assignment should be private
	SoundQuit(const SoundQuit&);
	SoundQuit &operator=(const SoundQuit&);
 
public:

	// This is a singleton
	static SoundQuit *Instance();
	
	void Enter(SoundClass *sound);
	bool Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(SoundClass *sound);
	void Exit(SoundClass *sound);
	bool Receive(SoundClass *sound, const Message &msg){return true;}

};

#endif
