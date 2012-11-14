#ifndef STATE_HPP
#define STATE_HPP
//------------------------------------------------------------------------
//
// Name: State.hpp
//
// Desc: Abstract base class to define an interface for a state
//
// Author: Mat Buckland (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

template <class state_type>
class State
{
public:

	virtual ~State(){}

	// This will execute when the state is entered
	virtual void Enter(state_type*) = 0;

	// This is the states normal update function
	virtual bool Update(state_type*, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse) = 0;

	// This is the states normal render function
	virtual void Render(state_type*) = 0;

	// This will execute when the state is exited. 
	virtual void Exit(state_type*) = 0;

	// This executes if the agent receives a message from the message Transmiter
	virtual bool Receive(state_type*, const Message&) = 0;
};

#endif
