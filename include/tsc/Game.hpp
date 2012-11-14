#ifndef GAME_HPP
#define GAME_HPP
//------------------------------------------------------------------------
//
// Name: Game.hpp
//
// Desc: A class to implement a Game
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Module.hpp"
#include "StateManager.hpp"
#include "GameStates.hpp"

class GameClass : public Module
{
private:

	// An instance of the State Manager class
	StateManager<GameClass> *m_StateManager;

	// Progress Indicator
	int m_Progress;

	// Max. Progress Indicator
	int m_ProgressMax;

	// Switch when game is active
	bool m_InGame;

	// Copy ctor and assignment should be private
	GameClass(const GameClass&);
	GameClass &operator=(const GameClass&);

public:

	// The Game Constructor
	GameClass() : m_Progress(0), m_ProgressMax(5), m_InGame(false)
	{
		// Set up the State Manager
		m_StateManager = new StateManager<GameClass>(this);
		m_StateManager->SetCurrentState(GameIdleState);
	}

	// The Game Destructor
	~GameClass(){delete m_StateManager;}

	// Update the Game
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return m_StateManager->Update(elapsed, key, mouse);}

	// Render the Game
	void Render(){m_StateManager->Render();}

	// Handle Messages for the Game
	bool HandleMessage(const Message &msg){return m_StateManager->HandleMessage(msg);}

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	StateManager<GameClass> *StateMgr() const {return m_StateManager;}

	bool IsProgressComplete() const {return m_Progress >= m_ProgressMax;}
	float FractionalProgress() const {return static_cast<float>(m_Progress)/static_cast<float>(m_ProgressMax);}
	void IncrementProgress(){m_Progress++;}
	void ResetProgress(){m_Progress = 0;}

	bool InGame() const {return m_InGame;}
	void InGame(bool bval){m_InGame = bval;}

};

#endif
