#ifndef ENGINE_HPP
#define ENGINE_HPP
//------------------------------------------------------------------------
//
// Name: Engine.hpp
//
// Desc: Singleton class to handle the management of modules
//
// Author: Chris Capobianco, 2012-10-06
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Sound.hpp"

class Module;

// Provide easy access
#define Engine() EngineClass::Instance()

class EngineClass
{
private:

	// A pointer to the game module
	GameClass *m_Game;

	// A pointer to the menu module
	MenuClass *m_Menu;

	// A pointer to the map module
	MapClass *m_Map;

	// A pointer to the sound module
	SoundClass *m_Sound;

	// A pointer to the Player module
	PlayerClass *m_Player;

	// Fade In and Flag Out flags
	bool m_FadeIn, m_FadeOut;

	// Elapsed Time
	float m_ElapsedTime;

	EngineClass() : m_FadeIn(false), m_FadeOut(false), m_ElapsedTime(0.0f){}

	// Copy ctor and assignment should be private
	EngineClass(const EngineClass&);
	EngineClass &operator=(const EngineClass&);

public:

	static EngineClass *Instance();

	// Startup Engine
	void Startup(int narg, char *argv[]);

	// Shutdown Engine
	void Shutdown();

	// Update all the Modules
	bool Update(float elapsed, TCOD_key_t key, TCOD_mouse_t mouse);

	// Render all the Modules
	void Render();

	// Receive all messages
	bool Receive(const Message &msg);

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	GameClass *Game() const {return m_Game;}
	void Game(GameClass *pGame){m_Game = pGame;}

	MenuClass *Menu() const {return m_Menu;}
	void Menu(MenuClass *pMenu){m_Menu = pMenu;}

	MapClass *Map() const {return m_Map;}
	void Map(MapClass *pMap){m_Map = pMap;}

	SoundClass *Sound() const {return m_Sound;}
	void Sound(SoundClass *pSound){m_Sound = pSound;}

	PlayerClass *Player() const {return m_Player;}
	void Player(PlayerClass *pPlayer){m_Player = pPlayer;}

	bool FadeIn() const {return m_FadeIn;}
	void FadeIn(bool pFadeIn){m_FadeIn = pFadeIn;}

	bool FadeOut() const {return m_FadeOut;}
	void FadeOut(bool pFadeOut){m_FadeOut = pFadeOut;}

	float ElapsedTime() const {return m_ElapsedTime;}
	void UpdateElapsedTime(float pElapsed){m_ElapsedTime += pElapsed;}

	// Update Status Panel
	void UpdateStatusPanel(TCODConsole *con)
	{
		int x = 3, y = 12;

		// Set text colours
		TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
		TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::green, TCODColor::black);

		con->print(x, y, "%cHP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		con->print(x + 4, y++, "%d/%d", Player()->HP(), Player()->HPMax());

		con->print(x, y, "%cMP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		con->print(x + 4, y++, "%d/%d", Player()->MP(), Player()->MPMax());

		con->print(x, ++y, "%cStatus:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//for(int i = 0; i < 5; i++) if(Player()->Health()->Status[i]) con->print(x, ++y, "%s", Player()->Health()->Name[i]);
		con->print(x, ++y, "%s", "Healthy");

		//for(int i = 0; i < NSTATUS; i++)
		//{
		//	if(Player()->Health()->Status[i])
		//	{
		//		con->print(x, ++y, "%s", Player()->Health()->StatusName[i]);
		//	}
		//}
		con->print(x, ++y, "%s", "Burdened");
		con->print(x, ++y, "%s", "Poisoned");
		con->print(x, ++y, "%s", "Weakened");
		con->print(x, ++y, "%s", "Sluggish");
		con->print(x, ++y, "%s", "Feeble");
		con->print(x, ++y, "%s", "Confused");

		// Compute the elapsed time in convenient units
		int nhours = static_cast<int>(ElapsedTime()/(60.0f*60.0f));
		float time = ElapsedTime() - (60.0f*60.0f)*static_cast<float>(nhours);
		int nmins = static_cast<int>(time/60.0f);
		int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

		x = 3, y = 24;
		con->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 4, y++, "%d", Eng->Player()->GP());
		con->print(x + 4, y++, "%d", 100);
		y++;

		con->print(x, y++, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		con->print(x, y, "%02d:%02d:%02d", nhours, nmins, nsecs);
	}

	// Update Stats Panel
	void UpdateStatsPanel(TCODConsole *con)
	{
		int x = 2, y = NEQUIPTYPE + 6;

		// Set text colours
		TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
		TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::green, TCODColor::black);

		//float xpfraction = static_cast<float>(game.Player.xp)/static_cast<float>(game.Player.xpnext);
		float xpfraction = static_cast<float>(0)/static_cast<float>(100);
		int xpbar = static_cast<int>(14.0f*xpfraction);
		if(xpbar > 0)
		{
			con->setDefaultBackground(TCODColor::darkGreen);
			con->rect(x, y + 2, xpbar, 1, true, TCOD_BKGND_SET);
		}
		if(xpbar < 14)
		{
			con->setDefaultBackground(TCODColor::darkerGreen);
			con->rect(x + xpbar, y + 2, 14 - xpbar, 1, true, TCOD_BKGND_SET);
		}
		con->setDefaultBackground(TCODColor::black);
		con->print(x, y, "%cLVL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.Player.lvl);
		con->print(x + 7, y++, "%2d", 1);
		con->print(x, y++, "%cXP   :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->printEx(x + 7, y++, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", game.Player.xp, game.Player.xpnext);
		con->printEx(x + 7, y++, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", 0, 100);

		y += 2;
		con->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.Player.stats.hpmax);
		con->print(x + 7, y++, "%2d", 20);

		con->print(x, y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.Player.stats.ap);
		con->print(x + 7, y++, "%2d", 4);
		con->print(x, y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.Player.stats.dp);
		con->print(x + 7, y++, "%2d", 2);

		con->print(x, y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.Player.stats.str);
		con->print(x + 7, y++, "%2d", 10);
		con->print(x, y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.Player.stats.spd);
		con->print(x + 7, y++, "%2d", 12);

		y += 2;
		con->print(x, y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.Player.stats.mpmax);
		con->print(x + 7, y++, "%2d", 10);

		con->print(x, y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.Player.stats.map);
		con->print(x + 7, y++, "%2d", 5);
		con->print(x, y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.Player.stats.mdp);
		con->print(x + 7, y++, "%2d", 2);

		con->print(x, y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.Player.stats.wil);
		con->print(x + 7, y++, "%2d", 6);
		con->print(x, y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.Player.stats.acu);
		con->print(x + 7, y++, "%2d", 3);
	}

	// Update Stats Panel
	//void UpdateStatsPanel(TCODConsole *con, Stats stats)
	void UpdateStatsPanel(TCODConsole *con, int stats[10])
	{
		int x = 2, y = NEQUIPTYPE + 6, i = 0;
		if(!Menu()->StateMgr(STATE_04)->IsInState(MenuIdleState)) y = 2;

		// Set text colours
		TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
		TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::green, TCODColor::black);

		//float xpfraction = static_cast<float>(game.player.xp)/static_cast<float>(game.player.xpnext);
		float xpfraction = static_cast<float>(0)/static_cast<float>(100);
		int xpbar = static_cast<int>(14.0f*xpfraction);
		if(xpbar > 0)
		{
			con->setDefaultBackground(TCODColor::darkGreen);
			con->rect(x, y + 2, xpbar, 1, true, TCOD_BKGND_SET);
		}
		if(xpbar < 14)
		{
			con->setDefaultBackground(TCODColor::darkerGreen);
			con->rect(x + xpbar, y + 2, 14 - xpbar, 1, true, TCOD_BKGND_SET);
		}
		con->setDefaultBackground(TCODColor::black);
		con->print(x, y, "%cLVL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.Player.lvl);
		con->print(x + 7, y++, "%2d", 1);
		con->print(x, y++, "%cXP   :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->printEx(x + 7, y++, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", game.Player.xp, game.Player.xpnext);
		con->printEx(x + 7, y++, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", 0, 100);

		y += 2;
		con->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.hpmax);
		//DisplayUpdatedStat(con, x, y, game.player.stats.hpmax, stats.hpmax);
		con->print(x + 7, y, "%2d", 20);
		DisplayUpdatedStat(con, x, y, 20, stats[i++]);

		con->print(x, ++y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.ap);
		//DisplayUpdatedStat(con, x, y, game.player.stats.ap, stats.ap);
		con->print(x + 7, y, "%2d", 4);
		DisplayUpdatedStat(con, x, y, 4, stats[i++]);

		con->print(x, ++y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.dp);
		//DisplayUpdatedStat(con, x, y, game.player.stats.dp, stats.dp);
		con->print(x + 7, y, "%2d", 2);
		DisplayUpdatedStat(con, x, y, 2, stats[i++]);

		con->print(x, ++y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.str);
		//DisplayUpdatedStat(con, x, y, game.player.stats.str, stats.str);
		con->print(x + 7, y, "%2d", 10);
		DisplayUpdatedStat(con, x, y, 10, stats[i++]);

		con->print(x, ++y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.spd);
		//DisplayUpdatedStat(con, x, y, game.player.stats.spd, stats.spd);
		con->print(x + 7, y, "%2d", 12);
		DisplayUpdatedStat(con, x, y, 12, stats[i++]);

		y += 2;
		con->print(x, ++y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.mpmax);
		//DisplayUpdatedStat(con, x, y, game.player.stats.mpmax, stats.mpmax);
		con->print(x + 7, y, "%2d", 10);
		DisplayUpdatedStat(con, x, y, 10, stats[i++]);

		con->print(x, ++y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.map);
		//DisplayUpdatedStat(con, x, y, game.player.stats.map, stats.map);
		con->print(x + 7, y, "%2d", 5);
		DisplayUpdatedStat(con, x, y, 5, stats[i++]);

		con->print(x, ++y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.mdp);
		//DisplayUpdatedStat(con, x, y, game.player.stats.mdp, stats.mdp);
		con->print(x + 7, y, "%2d", 2);
		DisplayUpdatedStat(con, x, y, 2, stats[i++]);

		con->print(x, ++y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.wil);
		//DisplayUpdatedStat(con, x, y, game.player.stats.wil, stats.wil);
		con->print(x + 7, y, "%2d", 6);
		DisplayUpdatedStat(con, x, y, 6, stats[i++]);

		con->print(x, ++y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.acu);
		//DisplayUpdatedStat(con, x, y, game.player.stats.acu, stats.acu);
		con->print(x + 7, y, "%2d", 3);
		DisplayUpdatedStat(con, x, y, 3, stats[i++]);
	}

	// Update Equip Stats Panel
	void UpdateEquipStatsPanel(TCODConsole *con)
	{
		int h = 3*DISPLAY_HEIGHT/4, hs = h - 2;
		int x = 2, y = 2*hs/3 + 1 + 2;
		if(!Menu()->StateMgr(STATE_04)->IsInState(MenuIdleState)) y = (hs - 5)/2 + 3 + 2;

		// Set text colours
		TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
		TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::green, TCODColor::black);

		con->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.player.stats.hpmax);
		con->print(x + 7, y++, "%2d", 20);

		con->print(x, y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.player.stats.ap);
		con->print(x + 7, y++, "%2d", 4);
		con->print(x, y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.player.stats.dp);
		con->print(x + 7, y++, "%2d", 2);

		con->print(x, y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.player.stats.str);
		con->print(x + 7, y++, "%2d", 10);
		con->print(x, y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.player.stats.spd);
		con->print(x + 7, y++, "%2d", 12);

		x += 20; y = 2*hs/3 + 1 + 2;
		if(!Menu()->StateMgr(STATE_04)->IsInState(MenuIdleState)) y = (hs - 5)/2 + 3 + 2;
		con->print(x, y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.player.stats.mpmax);
		con->print(x + 7, y++, "%2d", 10);

		con->print(x, y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.player.stats.map);
		con->print(x + 7, y++, "%2d", 5);
		con->print(x, y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.player.stats.mdp);
		con->print(x + 7, y++, "%2d", 2);

		con->print(x, y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.player.stats.wil);
		con->print(x + 7, y++, "%2d", 6);
		con->print(x, y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.player.stats.acu);
		con->print(x + 7, y++, "%2d", 3);
	}

	// Update Equip Stats Panel
	//void UpdateEquipStatsPanel(TCODConsole *con, Stats stats)
	void UpdateEquipStatsPanel(TCODConsole *con, int stats[10])
	{
		int h = 3*DISPLAY_HEIGHT/4, hs = h - 2;
		int x = 2, y = 2*hs/3 + 1 + 2, i = 0;
		if(!Menu()->StateMgr(STATE_04)->IsInState(MenuIdleState)) y = (hs - 5)/2 + 3 + 2;

		// Set text colours
		TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
		TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::green, TCODColor::black);

		con->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y++, "%2d", game.player.stats.hpmax);
		//DisplayUpdatedStat(con, x, y, game.player.stats.hpmax, stats.hpmax);
		con->print(x + 7, y, "%2d", 20);
		DisplayUpdatedStat(con, x, y, 20, stats[i++]);

		con->print(x, ++y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.ap);
		//DisplayUpdatedStat(con, x, y, game.player.stats.ap, stats.ap);
		con->print(x + 7, y, "%2d", 4);
		DisplayUpdatedStat(con, x, y, 4, stats[i++]);

		con->print(x, ++y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.dp);
		//DisplayUpdatedStat(con, x, y, game.player.stats.dp, stats.dp);
		con->print(x + 7, y, "%2d", 2);
		DisplayUpdatedStat(con, x, y, 2, stats[i++]);

		con->print(x, ++y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.str);
		//DisplayUpdatedStat(con, x, y, game.player.stats.str, stats.str);
		con->print(x + 7, y, "%2d", 10);
		DisplayUpdatedStat(con, x, y, 10, stats[i++]);

		con->print(x, ++y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.spd);
		//DisplayUpdatedStat(con, x, y, game.player.stats.spd, stats.spd);
		con->print(x + 7, y, "%2d", 12);
		DisplayUpdatedStat(con, x, y, 12, stats[i++]);

		x += 20; y = 2*hs/3 + 1 + 2;
		if(!Menu()->StateMgr(STATE_04)->IsInState(MenuIdleState)) y = (hs - 5)/2 + 3 + 2;
		con->print(x, y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.mpmax);
		//DisplayUpdatedStat(con, x, y, game.player.stats.mpmax, stats.mpmax);
		con->print(x + 7, y, "%2d", 10);
		DisplayUpdatedStat(con, x, y, 10, stats[i++]);

		con->print(x, ++y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.map);
		//DisplayUpdatedStat(con, x, y, game.player.stats.map, stats.map);
		con->print(x + 7, y, "%2d", 5);
		DisplayUpdatedStat(con, x, y, 5, stats[i++]);

		con->print(x, ++y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.mdp);
		//DisplayUpdatedStat(con, x, y, game.player.stats.mdp, stats.mdp);
		con->print(x + 7, y, "%2d", 2);
		DisplayUpdatedStat(con, x, y, 2, stats[i++]);

		con->print(x, ++y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.wil);
		//DisplayUpdatedStat(con, x, y, game.player.stats.wil, stats.wil);
		con->print(x + 7, y, "%2d", 6);
		DisplayUpdatedStat(con, x, y, 6, stats[i++]);

		con->print(x, ++y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//con->print(x + 7, y, "%2d", game.player.stats.acu);
		//DisplayUpdatedStat(con, x, y, game.player.stats.acu, stats.acu);
		con->print(x + 7, y, "%2d", 3);
		DisplayUpdatedStat(con, x, y, 3, stats[i++]);
	}

	// Displays Preview of Player Stats 
	void DisplayUpdatedStat(TCODConsole *con, int x, int y, int oldstat, int newstat)
	{
		char str[CHARMAX];

		// Set text colours
		TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
		TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);
		TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::green, TCODColor::black);

		x += 10;
		con->print(x, y, "%c", TCOD_CHAR_ARROW_E);
		sprintf(str, "%s%2d%s", "%c", newstat, "%c");
		x += 2;
		if(newstat > oldstat)
		{
			con->print(x, y, str, TCOD_COLCTRL_5, TCOD_COLCTRL_STOP);
		}
		else if(newstat < oldstat)
		{
			con->print(x, y, str, TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
		}
		else
		{
			con->print(x, y, str, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
		}
	}
};

#endif
