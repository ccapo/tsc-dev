#ifndef LEADER_HPP
#define LEADER_HPP
//------------------------------------------------------------------------
//
// Name: Leader.hpp
//
// Desc: A class to implement a Leader
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Entity.hpp"
#include "Commander.hpp"
#include "LeaderStates.hpp"
#include "StateManager.hpp"
#include "MessageTransmitter.hpp"

class Leader : public Entity
{
private:

	typedef map<int, Commander*> SubordinateMap;

protected:

	// An instance of the State Manager class
	StateManager<Leader> *m_StateManager;

	// Map of Commanders
	SubordinateMap m_SubordinateMap;

public:

	Leader(int x, int y) : Entity(ENTITY_LEADER, LOCATION_CAVE, x, y, CHAR_ORGE_WARRIOR_RED, TCODColor::white, 20, 10)
	{
		// Set up the State Manager
		m_StateManager = new StateManager<Leader>(this);
		m_StateManager->SetCurrentState(LeaderAlertState);

		IQ(RNG->getInt(120,140));
	}

	~Leader(){delete m_StateManager;}

	// Update the Leader
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return m_StateManager->Update(elapsed, key, mouse);}

	// Render the Leader
	void Render(){m_StateManager->Render();}

	// Handle Messages for the Leader
	bool HandleMessage(const Message &msg){return m_StateManager->HandleMessage(msg);}

	// Stores cmdr in m_SubordinateMap along with it's ID
	void AddSubordinate(Commander *cmdr){m_SubordinateMap.insert(make_pair(cmdr->ID(), cmdr));}

	// Returns a pointer to the Commander with the given ID
	Commander *Subordinate(int id) const
	{
		// Find the Commander
		SubordinateMap::const_iterator ent = m_SubordinateMap.find(id);

		// Assert that the entity is a member of the map
		assert((ent != m_SubordinateMap.end()) && "Leader::Subordinate : Invalid ID");

		return ent->second;
	}

	// Send a message to all the Commanders stored in m_SubordinateMap
	void PageSubordinates(int msg)
	{
		for(SubordinateMap::iterator it = m_SubordinateMap.begin(); it != m_SubordinateMap.end(); it++)
		{
			Transmit->Send(it->second, msg);
		}
	}

	// Removes cmdr from m_SubordinateMap
	void RemoveSubordinate(Commander *cmdr){m_SubordinateMap.erase(m_SubordinateMap.find(cmdr->ID()));}

	// Removes all Commanders from m_SubordinateMap
	void RemoveAll()
	{
		for(SubordinateMap::iterator it = m_SubordinateMap.begin(); it != m_SubordinateMap.end(); it++)
		{
			it->second->RemoveAll();
		}
		m_SubordinateMap.clear();
	}

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	StateManager<Leader> *StateMgr() const {return m_StateManager;}

};

#endif
