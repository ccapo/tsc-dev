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
	StateManager<MenuClass> *m_StateManager[NSTATES];

	// Magic ID
	int m_MagicID;

	// Background image for main menu
	TCODImage *m_ImgBG;

	// Magic Icon
	TCODImage *m_MagicIcon;

	// Off-Screen Consoles
	TCODConsole *m_Con[NSTATES];

	// Highest Active State Index
	int m_ActiveStateID;

	// Copy ctor and assignment should be private
	MenuClass(const MenuClass&);
	MenuClass &operator=(const MenuClass&);

public:

	// Message Log
	map<int, string> MessageLog;
	map<int, string> MainOptions, HelpOptions, GameOptions, EquipOptions, EquipOptionsHorizontal;
	map<int, string> EquipListOptions, EquipShopOptions, ItemShopOptions, InnOptions, FerryOptions;
	string HelpText, IntroText[2], FerryText[2], InnText[2], DeathText;

	// The Menu Constructor
	MenuClass() : m_MagicID(0), m_ActiveStateID(0)
	{
		// Setup State Managers and Off-Screen Consoles
		for(int i = 0; i < NSTATES; i++)
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

		int i = 0;
		MainOptions.insert(make_pair(i++, "%cNew Game %c"));
		MainOptions.insert(make_pair(i++, "%cLoad Game%c"));
		MainOptions.insert(make_pair(i++, "%cGame Help%c"));
		MainOptions.insert(make_pair(i++, "%cQuit Game%c"));

		i = 0;
		HelpOptions.insert(make_pair(i++, "Move/Attack        :: Arrow Keys       "));
		HelpOptions.insert(make_pair(i++, "Use Magic          :: Left Mouse Button"));
		HelpOptions.insert(make_pair(i++, "Select Magic       :: Control          "));
		HelpOptions.insert(make_pair(i++, "Toggle Menu/Cancel :: Escape           "));
		HelpOptions.insert(make_pair(i++, "Select/Action      :: Enter            "));
		HelpOptions.insert(make_pair(i++, "Toggle Music       :: Pause            "));
		HelpOptions.insert(make_pair(i++, "Toggle Fullscreen  :: Alt + Enter      "));
		HelpOptions.insert(make_pair(i++, "Screen Capture     :: Backspace        "));
		HelpOptions.insert(make_pair(i++, "Game Help          :: ?                "));

		HelpText = "Whenever the Player returns to the %cWorld Map%c, the game will automatically overwrite the existing save file.\n\nIf the Player expires, death is %cpermanent%c as the save file is %cdeleted%c.";

		i = 0;
		IntroText[i++] = "Welome brave adventurer, thank you for heeding my pleas for help.\n\n\nI am the %cGuardian of Light%c, one of the five entrusted to protect this world.\n\n\nA %cPowerful Ancient Menace%c is gathering once again in the shadows, and threatens to destroy the peace and harmony of these lands.\n\n\nThis is why I have summoned you here, I must impress upon you to persue a perilous quest to rid the world of this threat.";
		IntroText[i++] = "We know this power is gathering deep within\n%cThe Serpentine Caves%c, but where we know not.\n\n\nIt will be a difficult journey, so seek out the other four %cElemental Guardians%c for assistance. If they deem you worthy, they will grant you the ability to use their power.\n\n\nTo aid you on your quest I will grant my %cPower of Light%c, and any creature of the dark will be startled by its brilliance. Use this power wisely.\n\n\nGood luck brave hero, and may the record of your deeds be sung throughout the ages.";

		i = 0;
		GameOptions.insert(make_pair(i++, "%cEquipment%c"));
		GameOptions.insert(make_pair(i++, "%cInventory%c"));
		GameOptions.insert(make_pair(i++, "%cQuit Game%c"));

		i = 0;
		EquipOptions.insert(make_pair(i++, "%cWeapon   %c ::"));
		EquipOptions.insert(make_pair(i++, "%cShield   %c ::"));
		EquipOptions.insert(make_pair(i++, "%cArmour   %c ::"));
		EquipOptions.insert(make_pair(i++, "%cAccessory%c ::"));

		i = 0;
		EquipOptionsHorizontal.insert(make_pair(i++, "%cWeapon%c"));
		EquipOptionsHorizontal.insert(make_pair(i++, "%cShield%c"));
		EquipOptionsHorizontal.insert(make_pair(i++, "%cArmour%c"));
		EquipOptionsHorizontal.insert(make_pair(i++, "%cAccessory%c"));

		i = 0;
		EquipListOptions.insert(make_pair(i++, "Weapons"));
		EquipListOptions.insert(make_pair(i++, "Shields"));
		EquipListOptions.insert(make_pair(i++, "Armour"));
		EquipListOptions.insert(make_pair(i++, "Accessories"));

		i = 0;
		EquipShopOptions.insert(make_pair(i++, "%cBuy Equip %c"));
		EquipShopOptions.insert(make_pair(i++, "%cSell Equip%c"));
		EquipShopOptions.insert(make_pair(i++, "%cExit Shop %c"));

		i = 0;
		ItemShopOptions.insert(make_pair(i++, "%cBuy Items %c"));
		ItemShopOptions.insert(make_pair(i++, "%cSell Items%c"));
		ItemShopOptions.insert(make_pair(i++, "%cExit Shop %c"));

		i = 0;
		FerryOptions.insert(make_pair(i++, "%cTake Ferry%c"));
		FerryOptions.insert(make_pair(i++, "%cExit Ferry%c"));

		i = 0;
		FerryText[i++] = "Where are you headed?\n\n\nMy fee is %c25 GP%c per trip.";
		FerryText[i++] = "Come back any time.";

		i = 0;
		InnOptions.insert(make_pair(i++, "%cStay Inn%c"));
		InnOptions.insert(make_pair(i++, "%cExit Inn%c"));

		i = 0;
		InnText[i++] = "Hello there young traveller.\n\n\nCan I interest you in a nice hearty meal, and a warm comfortable bed?\n\n\nWe charge %c15 GP%c per night, meal included.\n\n\nWould you care to stay?";
		InnText[i++] = "It is a shame to see you leave.\n\n\nPlease hurry back!";

		DeathText = "While your valiant efforts should be commended, they were all for naught.\n\n\nThe %cAncient Menance%c spread across these lands, killing all those that could fight and enslaving the rest.\n\n\nEventhough your part in this tale is over, perhaps a new hero will one day emerge from the remnants of these broken and shattered people.";
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
		TCOD_key_t k = {TCODK_NONE, 0};
		TCOD_mouse_t m = {0,0, 0,0, 0,0, 0,0};

		//cout << "Active State ID: " << m_ActiveStateID << endl;
		for(int i = 0; i < NSTATES; i++)
		{
			//cout << i << " Menu State: " << m_StateManager[i]->GetNameOfCurrentState() << endl;
			if(i == m_ActiveStateID)
			{
				status = status && m_StateManager[i]->Update(elapsed, key, mouse);
			}
			else
			{
				status = status && m_StateManager[i]->Update(elapsed, k, m);
			}
		}
		return status;
	}

	// Render the Menu
	void Render()
	{
		for(int i = 0; i < NSTATES; i++) m_StateManager[i]->Render();
	}

	// Handle Messages for the Message Log
	bool HandleMessage(const Message &msg){return m_StateManager[STATE_01]->HandleMessage(msg);}

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	StateManager<MenuClass> *StateMgr(int id) const {return m_StateManager[id];}

	TCODConsole *Con(int id) const {return m_Con[id];}
	void Con(int id, TCODConsole *pCon){m_Con[id] = pCon;}

	int ActiveStateID() const {return m_ActiveStateID;}
	void ActiveStateID(int pActiveStateID){m_ActiveStateID = pActiveStateID;}
	void IncreaseStateID(){m_ActiveStateID++; Clamp<int>(m_ActiveStateID, 0, NSTATES);}
	void DecreaseStateID(){m_ActiveStateID--; Clamp<int>(m_ActiveStateID, -1, NSTATES);}

	int MagicID() const {return m_MagicID;}
	void IncrementMagicID(){m_MagicID = (m_MagicID + 1) % NMAGIC;}

	TCODImage *ImgBG() const {return m_ImgBG;}
	void ImgBG(TCODImage *pImgBG){m_ImgBG = pImgBG;}

	TCODImage *MagicIcon() const {return m_MagicIcon;}
	void MagicIcon(TCODImage *pMagicIcon){m_MagicIcon = pMagicIcon;}

	// Displays Progress Bar
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
