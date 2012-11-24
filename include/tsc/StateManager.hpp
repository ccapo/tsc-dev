#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP
//------------------------------------------------------------------------
//
// Name: StateManager.hpp
//
// Desc: State Manager class. Inherit from this class and create some 
//			 states to give your agents FSM functionality
//
// Author: Mat Buckland (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "State.hpp"

template <class state_type>
class StateManager
{
private:

	// A pointer to the agent that owns this instance
	state_type *m_Owner;

	// The current state of the agent
	State<state_type> *m_CurrentState;
	
	// A record of the last state of the agent
	State<state_type> *m_PreviousState;

public:

	StateManager(state_type *owner) : m_Owner(owner), m_CurrentState(NULL), m_PreviousState(NULL){}

	virtual ~StateManager(){}

	// Use these methods to initialize the FSM
	void SetCurrentState(State<state_type> *s){m_CurrentState = s;}
	void SetPreviousState(State<state_type> *s){m_PreviousState = s;}
	
	// Call this to Update the State Manager
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse) const
	{
		bool status = false;

		// Call the Update method for the Current State
		if(m_CurrentState) status = m_CurrentState->Update(m_Owner, elapsed, key, mouse);

		return status;
	}

	// Call this to Render the State Manager
	void Render()
	{
		// Call the Render method for the Current State
		if(m_CurrentState) m_CurrentState->Render(m_Owner);
	}

	bool HandleMessage(const Message &msg) const
	{
		bool status = false;

		// First see if the current state is valid and that it can handle the message
		if(m_CurrentState && m_CurrentState->Receive(m_Owner, msg)) status = true;

		return status;
	}

	// Change to a new state
	void ChangeState(State<state_type> *pNewState)
	{
		assert(pNewState && "StateManager::ChangeState - Trying to assign null state to current state");

		// Keep a record of the previous state
		m_PreviousState = m_CurrentState;

		// Call the exit method of the existing state
		m_CurrentState->Exit(m_Owner);

		// Change state to the new state
		m_CurrentState = pNewState;

		// Call the entry method of the new state
		m_CurrentState->Enter(m_Owner);
	}

	// Change state back to the previous state
	void RevertToPreviousState()
	{
		ChangeState(m_PreviousState);
	}

	// Returns true if the current state's type is equal to the type of the class passed as a parameter. 
	bool IsInState(State<state_type> *st) const
	{
		if(typeid(*m_CurrentState) == typeid(*st)) return true;
		return false;
	}

	State<state_type> *CurrentState() const {return m_CurrentState;}
	State<state_type> *PreviousState() const {return m_PreviousState;}

	// Only ever used during debugging to grab the name of the current state
	string GetNameOfCurrentState() const
	{
		string s(typeid(*m_CurrentState).name());

		// Remove the 'class ' part from the front of the string
		//if(s.size() > 5) s.erase(0, 6);
		s.erase(0, 1);

		return s;
	}
};

#endif
