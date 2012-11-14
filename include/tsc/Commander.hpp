#ifndef COMMANDER_HPP
#define COMMANDER_HPP
//------------------------------------------------------------------------
//
// Name: Commander.hpp
//
// Desc: A class to implement a Commander
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Entity.hpp"
#include "Peon.hpp"
#include "CommanderStates.hpp"
#include "StateManager.hpp"
#include "MessageTransmitter.hpp"

class Commander : public Entity
{
private:

	typedef map<int, Peon*> SubordinateMap;

protected:

	// An instance of the State Manager class
	StateManager<Commander> *m_StateManager;

	// Map of Peons
	SubordinateMap m_SubordinateMap;

	// Pointer to Superior
	Entity *m_Superior;

public:

	Commander(int x, int y) : Entity(ENTITY_COMMANDER, LOCATION_CAVE, x, y, CHAR_ORGE_WARRIOR_GREEN, TCODColor::white, 10, 5), m_Superior(NULL)
	{
		// Set up the State Manager
		m_StateManager = new StateManager<Commander>(this);
		m_StateManager->SetCurrentState(CommanderAlertState);

		IQ(RNG->getInt(100,120));
	}

	~Commander(){delete m_StateManager;}

	// Update the Commander
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return m_StateManager->Update(elapsed, key, mouse);}

	// Render the Commander
	void Render(){m_StateManager->Render();}

	// Handle Messages for the Commander
	bool HandleMessage(const Message &msg){return m_StateManager->HandleMessage(msg);}

	// Stores peon in m_SubordinateMap along with it's ID
	void AddSubordinate(Peon *peon){m_SubordinateMap.insert(make_pair(peon->ID(), peon));}

	// Returns a pointer to the Peon with the given ID
	Peon *Subordinate(int id) const
	{
		// Find the Peon
		SubordinateMap::const_iterator ent = m_SubordinateMap.find(id);

		// Assert that the entity is a member of the map
		assert((ent != m_SubordinateMap.end()) && "Commander::Subordinate : invalid ID");

		return ent->second;
	}

	// Send a message to all the Peons stored in m_SubordinateMap
	void PageSubordinates(int msg)
	{
		for(SubordinateMap::iterator it = m_SubordinateMap.begin(); it != m_SubordinateMap.end(); it++)
		{
			Transmit->Send(it->second, msg);
		}
	}

	// Removes peon from m_SubordinateMap
	void RemoveSubordinate(Peon *peon){m_SubordinateMap.erase(m_SubordinateMap.find(peon->ID()));}

	// Removes all Peons from m_SubordinateMap
	void RemoveAll(){m_SubordinateMap.clear();}

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	StateManager<Commander> *StateMgr() const {return m_StateManager;}

	Entity *Superior() const {return m_Superior;}
	void Superior(Entity *pEntity) {m_Superior = pEntity;}

};

#endif
