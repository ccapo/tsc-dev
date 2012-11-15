#ifndef MENU_HPP
#define MENU_HPP
//------------------------------------------------------------------------
//
// Name: Menu.hpp
//
// Desc: A class to implement a Menu
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "MenuStates.hpp"
#include "Module.hpp"
#include "StateManager.hpp"

class MenuClass : public Module
{
private:

	// The instances of the State Manager class
	StateManager<MenuClass> *m_StateManager[NCONSOLES];

	// Dialog Page Indicators
	int m_IntroPage;

	// Menu Selection and Subselection
	int m_Selection, m_SubSelection;

	// Magic ID
	int m_MagicID;

	// Background image for main menu
	TCODImage *m_ImgBG;

	// Magic Icon
  TCODImage *m_MagicIcon;

	// Off-Screen Consoles
	TCODConsole *m_Con[NCONSOLES];

	// Highest Active State Index
	int m_ActiveStateID;

	// Copy ctor and assignment should be private
	MenuClass(const MenuClass&);
	MenuClass &operator=(const MenuClass&);

public:

	// Message Log
	std::map<int, string> MessageLog;

	// The Menu Constructor
	MenuClass() : m_IntroPage(INTRO_01), m_Selection(NONE), m_SubSelection(NONE), m_MagicID(0), m_ActiveStateID(0)
	{
		// Setup State Managers and Off-Screen Consoles
		for(int i = 0; i < NCONSOLES; i++)
		{
			// State Manager
			m_StateManager[i] = new StateManager<MenuClass>(this);
			m_StateManager[i]->SetCurrentState(MenuIdleState);

			// Off-Screen Console
			m_Con[i] = new TCODConsole(0, 0);
		}

		// Set up the State Manager
		m_StateManager[m_ActiveStateID]->SetCurrentState(MenuMainState);

		// Background image for main menu
		m_ImgBG = new TCODImage("data/img/menu_bg.png");

		// Magic Icon
		m_MagicIcon = new TCODImage("data/img/magic_light.png");

		// Initialize the Message Log
		for(int i = 0; i < NMSGS; i++) MessageLog.insert(make_pair(i, ""));
	}

	// The Menu Destructor
	~MenuClass()
	{
		delete [] m_StateManager;
		delete [] m_Con;
		delete m_ImgBG;
		delete m_MagicIcon;
	}

	// Update the Menu
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
	{
		bool status = true;
		TCOD_key_t k0 = {TCODK_NONE, 0};
		TCOD_mouse_t m0 = {0,0, 0,0, 0,0, 0,0};

		//for(int i = 0; i < NCONSOLES; i++) cout << i << " Menu State: " << m_StateManager[i]->GetNameOfCurrentState() << endl;
		//cout << "Active State ID: " << m_ActiveStateID << endl;

		for(int i = 0; i < NCONSOLES; i++)
		{
			if(i == m_ActiveStateID)
			{
				status = status && m_StateManager[i]->Update(elapsed, key, mouse);
			}
			else
			{
				status = status && m_StateManager[i]->Update(elapsed, k0, m0);
			}
		}
		return status;
	}

	// Render the Menu
	void Render()
	{
		for(int i = 0; i < NCONSOLES; i++) m_StateManager[i]->Render();
	}

	// Handle Messages for the Message Log
	bool HandleMessage(const Message &msg){return m_StateManager[CON_01]->HandleMessage(msg);}

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	StateManager<MenuClass> *StateMgr(int id) const {return m_StateManager[id];}
	void ResetAll()
	{
		for(int i = 0; i < NCONSOLES; i++) m_StateManager[i]->ChangeState(MenuIdleState);
		m_ActiveStateID = -1;
	}

	TCODConsole *Con(int id) const {return m_Con[id];}
	void Con(int id, TCODConsole *pCon){m_Con[id] = pCon;}

	int ActiveStateID() const {return m_ActiveStateID;}
	void IncreaseStateID(){m_ActiveStateID++; Clamp<int>(m_ActiveStateID, 0, NCONSOLES);}
	void DecreaseStateID(){m_ActiveStateID--; Clamp<int>(m_ActiveStateID, 0, NCONSOLES);}

	int IntroPage() const {return m_IntroPage;}
	bool IsIntroComplete() const {return m_IntroPage >= NINTRO;}
	void ResetIntroPage(){m_IntroPage = INTRO_01;}
	void IncrementIntroPage(){m_IntroPage++;}

	int Selection() const {return m_Selection;}
	void Selection(int pSelection){m_Selection = pSelection;}

	int SubSelection() const {return m_SubSelection;}
	void SubSelection(int pSubSelection){m_SubSelection = pSubSelection;}

	int MagicID() const {return m_MagicID;}
	void IncrementMagicID(){m_MagicID = (m_MagicID + 1) % NMAGIC;}

	TCODImage *ImgBG() const {return m_ImgBG;}
	void ImgBG(TCODImage *pImgBG){m_ImgBG = NULL; m_ImgBG = pImgBG;}

	TCODImage *MagicIcon() const {return m_MagicIcon;}
	void MagicIcon(TCODImage *pMagicIcon){m_MagicIcon = NULL; m_MagicIcon = pMagicIcon;}

	void DisplayProgress(const char msg[], float fraction)
	{
		int length = static_cast<int>(fraction*SCREEN_WIDTH/2);
		TCODConsole::root->setDefaultBackground(TCODColor::black);
		TCODConsole::root->setDefaultForeground(TCODColor::white);
		TCODConsole::root->clear();
		TCODConsole::root->printEx(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 4, TCOD_BKGND_NONE, TCOD_CENTER, msg);
		if(length > 0)
		{
			TCODConsole::root->setDefaultBackground(TCODColor::red);
			TCODConsole::root->rect(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, length, 2, false, TCOD_BKGND_SET);
		}
		if(length < SCREEN_WIDTH/2)
		{
			TCODConsole::root->setDefaultBackground(TCODColor::darkestRed);
			TCODConsole::root->rect(SCREEN_WIDTH/4 + length, SCREEN_HEIGHT/2, SCREEN_WIDTH/2 - length, 2, false, TCOD_BKGND_SET);
		}
	}
};

#endif
