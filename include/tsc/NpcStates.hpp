#ifndef NPC_STATES_HPP
#define NPC_STATES_HPP
//------------------------------------------------------------------------
//
// Name: NpcStates.hpp
//
// Desc: All the states that can be assigned to the Npc class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Entity.hpp"
#include "Npc.hpp"
#include "Message.hpp"
#include "State.hpp"

class Npc;

// Provide easy access
#define NpcIdleState NpcIdle::Instance()
#define NpcActiveState NpcActive::Instance()

//------------------------------------------------------------------------
//
// This is the Idle State for the Npc.
//
//------------------------------------------------------------------------
class NpcIdle : public State<Npc>
{
private:

	NpcIdle(){}
	
	// Copy ctor and assignment should be private
	NpcIdle(const NpcIdle&);
	NpcIdle &operator=(const NpcIdle&);

public:

	// This is a singleton
	static NpcIdle *Instance();
	
	void Enter(Npc *Npc);
	bool Update(Npc *Npc, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Npc *Npc);
	void Exit(Npc *Npc){}
	bool Receive(Npc *Npc, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Active state for the Npc.
//
//------------------------------------------------------------------------
class NpcActive : public State<Npc>
{
private:
	
	NpcActive(){}

	// Copy ctor and assignment should be private
	NpcActive(const NpcActive&);
	NpcActive &operator=(const NpcActive&);
 
public:

	// This is a singleton
	static NpcActive *Instance();
	
	void Enter(Npc *Npc){}
	bool Update(Npc *Npc, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Npc *Npc);
	void Exit(Npc *Npc){}
	bool Receive(Npc *Npc, const Message &msg){return true;}

};

#endif
