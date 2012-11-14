#ifndef PLAYER_HPP
#define PLAYER_HPP
//------------------------------------------------------------------------
//
// Name: Player.hpp
//
// Desc: A class defining the Player
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Entity.hpp"
#include "StateManager.hpp"
#include "PlayerStates.hpp"

class PlayerClass : public Entity
{
private:

	// An instance of the state Manager class
	StateManager<PlayerClass> *m_StateManager;

public:

	PlayerClass() : Entity(ENTITY_PLAYER, LOCATION_TOWN, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 + 1, CHAR_PLAYER_DOWN, TCODColor::white, 20, 10)
	{
		// Setup State Manager
		m_StateManager = new StateManager<PlayerClass>(this);
		m_StateManager->SetCurrentState(PlayerIdleState);

		IQ(RNG->getInt(100, 140));
	}

	~PlayerClass(){delete m_StateManager;}

	// Update the Player
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return m_StateManager->Update(elapsed, key, mouse);}

	// Render the Player
	void Render(){m_StateManager->Render();}

	// Handle Messages for the Player
	bool HandleMessage(const Message &msg){return m_StateManager->HandleMessage(msg);}

	//-------------------------------------------------------------
	// Accessors
	//-------------------------------------------------------------
	StateManager<PlayerClass> *StateMgr() const {return m_StateManager;}

};

#endif
