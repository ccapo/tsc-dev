#ifndef COMMANDER_STATES_HPP
#define COMMANDER_STATES_HPP
//------------------------------------------------------------------------
//
// Name: CommanderStates.hpp
//
// Desc: All the states that can be assigned to the Commander class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Entity.hpp"
#include "Commander.hpp"
#include "Message.hpp"
#include "State.hpp"

class Commander;

// Provide easy access
#define CommanderAlertState CommanderAlert::Instance()
#define CommanderActiveState CommanderActive::Instance()

//------------------------------------------------------------------------
//
// This is the CommanderAlert state for the Commander.
//
//------------------------------------------------------------------------
class CommanderAlert : public State<Commander>
{
private:

	CommanderAlert(){}
	
	// Copy ctor and assignment should be private
	CommanderAlert(const CommanderAlert&);
	CommanderAlert &operator=(const CommanderAlert&);

public:

	// This is a singleton
	static CommanderAlert *Instance();
	
	void Enter(Commander *cmdr);
	bool Update(Commander *cmdr, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Commander *cmdr);
	void Exit(Commander *cmdr){}
	bool Receive(Commander *cmdr, const Message &msg);

};

//------------------------------------------------------------------------
//
// This is the CommanderActive state for the Commander.
//
//------------------------------------------------------------------------
class CommanderActive : public State<Commander>
{
private:
	
	CommanderActive(){}

	// Copy ctor and assignment should be private
	CommanderActive(const CommanderActive&);
	CommanderActive &operator=(const CommanderActive&);
 
public:

	// This is a singleton
	static CommanderActive *Instance();
	
	void Enter(Commander *cmdr);
	bool Update(Commander *cmdr, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Commander *cmdr);
	void Exit(Commander *cmdr){}
	bool Receive(Commander *cmdr, const Message &msg);

};

#endif
