#ifndef SOUND_HPP
#define SOUND_HPP
//------------------------------------------------------------------------
//
// Name: Sound.hpp
//
// Desc: A class to implement a Sound
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Module.hpp"
#include "StateManager.hpp"
#include "SoundStates.hpp"

class SoundClass : public Module
{
private:

	// An instance of the State Manager class
	StateManager<SoundClass> *m_StateManager;

	// Copy ctor and assignment should be private
	SoundClass(const SoundClass&);
	SoundClass &operator=(const SoundClass&);

public:

	// The Sound Constructor
	SoundClass()
	{
		// Set up the State Manager
		m_StateManager = new StateManager<SoundClass>(this);
		m_StateManager->SetCurrentState(SoundMainMenuState);
	}

	// The Sound Destructor
	~SoundClass(){delete m_StateManager;}

	// Update the Sound
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return StateMgr()->Update(elapsed, key, mouse);}

	// Render the Sound
	void Render(){m_StateManager->Render();}

	// Handle Messages for the Sound
	bool HandleMessage(const Message &msg){return StateMgr()->HandleMessage(msg);}

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	StateManager<SoundClass> *StateMgr() const {return m_StateManager;}

};

#endif
