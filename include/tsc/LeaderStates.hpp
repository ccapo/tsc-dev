#ifndef LEADER_STATES_HPP
#define LEADER_STATES_HPP
//------------------------------------------------------------------------
//
// Name: LeaderStates.hpp
//
// Desc: All the states that can be assigned to the Leader class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Entity.hpp"
#include "Leader.hpp"
#include "Message.hpp"
#include "State.hpp"

class Leader;

// Provide easy access
#define LeaderAlertState LeaderAlert::Instance()
#define LeaderActiveState LeaderActive::Instance()

//------------------------------------------------------------------------
//
// This is the Alert state for the Leader.
//
//------------------------------------------------------------------------
class LeaderAlert : public State<Leader>
{
private:

	LeaderAlert(){}
	
	// Copy ctor and assignment should be private
	LeaderAlert(const LeaderAlert&);
	LeaderAlert &operator=(const LeaderAlert&);

public:

	// This is a singleton
	static LeaderAlert *Instance();
	
	void Enter(Leader *leader);
	bool Update(Leader *leader, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Leader *leader);
	void Exit(Leader *leader){}
	bool Receive(Leader *leader, const Message &msg);

};

//------------------------------------------------------------------------
//
// This is the Active state for the Leader.
//
//------------------------------------------------------------------------
class LeaderActive : public State<Leader>
{
private:
	
	LeaderActive(){}

	// Copy ctor and assignment should be private
	LeaderActive(const LeaderActive&);
	LeaderActive &operator=(const LeaderActive&);
 
public:

	// This is a singleton
	static LeaderActive *Instance();
	
	void Enter(Leader *leader);
	bool Update(Leader *leader, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Leader *leader);
	void Exit(Leader *leader){}
	bool Receive(Leader *leader, const Message &msg);

};

#endif
