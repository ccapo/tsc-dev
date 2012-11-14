#ifndef NPC_HPP
#define NPC_HPP
//------------------------------------------------------------------------
//
// Name: Npc.hpp
//
// Desc: A class to implement a Npc
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Entity.hpp"
#include "NpcStates.hpp"
#include "StateManager.hpp"
#include "MessageTransmitter.hpp"

class Npc : public Entity
{
private:

	// An instance of the State Manager class
	StateManager<Npc> *m_StateManager;

public:

	Npc(int type, int x, int y) : Entity(type, LOCATION_DEFAULT, x, y, CHAR_DEFAULT, TCODColor::white, 0, 0)
	{
		// Set up the State Manager
		m_StateManager = new StateManager<Npc>(this);
		m_StateManager->SetCurrentState(NpcIdleState);

		switch(type)
		{
			case ENTITY_GUARDIAN:
			{
				Location(LOCATION_TEMPLE);
				Sym(CHAR_GUARDIAN);
				Colour(TCODColor::lighterYellow);
				break;
			}
			case ENTITY_SHOPKEEPER:
			{
				Location(LOCATION_TOWN);
				Sym(CHAR_KEEPER);
				break;
			}
			case ENTITY_TOWNSPERSON:
			{
				Location(LOCATION_TOWN);
				Sym(CHAR_PERSON);
				break;
			}
			default: break;
		}
	}

	~Npc(){delete m_StateManager;}

	// Update the Npc
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return m_StateManager->Update(elapsed, key, mouse);}

	// Render the Npc
	void Render(){m_StateManager->Render();}

	// Handle Messages for the Npc
	bool HandleMessage(const Message &msg){return m_StateManager->HandleMessage(msg);}

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	StateManager<Npc> *StateMgr() const {return m_StateManager;}

};

#endif
