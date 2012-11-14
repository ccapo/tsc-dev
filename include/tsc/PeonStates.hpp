#ifndef PEONSTATES_HPP
#define PEONSTATES_HPP
//------------------------------------------------------------------------
//
// Name: PeonStates.hpp
//
// Desc: All the states that can be assigned to the Peon class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

class Peon;

// Provide easy access
#define PeonPatrolState PeonPatrol::Instance()
#define PeonAttackState PeonAttack::Instance()
#define PeonDefendState PeonDefend::Instance()

//------------------------------------------------------------------------
//
// This is the patrol state for the Peon.
//
//------------------------------------------------------------------------
class PeonPatrol : public State<Peon>
{
private:

	PeonPatrol(){}
	
	// Copy ctor and assignment should be private
	PeonPatrol(const PeonPatrol&);
	PeonPatrol &operator=(const PeonPatrol&);

public:

	// This is a singleton
	static PeonPatrol *Instance();

	void Enter(Peon *peon){}
	bool Update(Peon *peon, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Peon *peon);
	void Exit(Peon *peon){}
	bool Receive(Peon *peon, const Message &msg);

};

//------------------------------------------------------------------------
//
// This is the attack state for the Peon
//
//------------------------------------------------------------------------
class PeonAttack : public State<Peon>
{
private:
	
	PeonAttack(){}

	// Copy ctor and assignment should be private
	PeonAttack(const PeonAttack&);
	PeonAttack &operator=(const PeonAttack&);
 
public:

	// This is a singleton
	static PeonAttack *Instance();
	
	void Enter(Peon *peon){}
	bool Update(Peon *peon, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Peon *peon);
	void Exit(Peon *peon){}
	bool Receive(Peon *peon, const Message &msg);

};

//------------------------------------------------------------------------
//
// This is the defend state for the Peon
//
//------------------------------------------------------------------------
class PeonDefend : public State<Peon>
{
private:
	
	PeonDefend(){}

	// Copy ctor and assignment should be private
	PeonDefend(const PeonDefend&);
	PeonDefend &operator=(const PeonDefend&);
 
public:

	// This is a singleton
	static PeonDefend *Instance();
	
	void Enter(Peon *peon){}
	bool Update(Peon *peon, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Peon *peon);
	void Exit(Peon *peon){}
	bool Receive(Peon *peon, const Message &msg);

};

#endif
