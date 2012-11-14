#ifndef PEON_HPP
#define PEON_HPP
//------------------------------------------------------------------------
//
// Name: Peon.hpp
//
// Desc: A class to implement a Peon
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Entity.hpp"
#include "State.hpp"
#include "StateManager.hpp"
#include "PeonStates.hpp"

class Peon : public Entity
{
private:

	// An instance of the State Manager class
	StateManager<Peon> *m_StateManager;

	// Direction the Peon is Patrolling
	int m_Direction;

	// Pointer to Superior
	Entity *m_Superior;

public:

	Peon(int x, int y) : Entity(ENTITY_PEON, LOCATION_CAVE, x, y, CHAR_ORGE_PEON_GREEN, TCODColor::white, 5, 0), m_Superior(NULL)
	{
		// Set up the State Manager
		m_StateManager = new StateManager<Peon>(this);
		m_StateManager->SetCurrentState(PeonPatrolState);

		IQ(RNG->getInt(80,100));

		Direction(RNG->getInt(1,4));
	}

	~Peon(){delete m_StateManager;}

	// Update the Peon
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return m_StateManager->Update(elapsed, key, mouse);}

	// Render the Peon
	void Render(){m_StateManager->Render();}

	// Handle Messages for the Peon
	bool HandleMessage(const Message &msg){return m_StateManager->HandleMessage(msg);}

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	StateManager<Peon> *StateMgr() const {return m_StateManager;}

	Entity *Superior() const {return m_Superior;}
	void Superior(Entity *pEntity) {m_Superior = pEntity;}

	int Direction() const {return m_Direction;}
	void Direction(int pDirection) {m_Direction = pDirection;}

};

#endif
