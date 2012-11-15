#include "Main.hpp"

//-------------------------------- Instance -----------------------------------
//
// This class is a singleton
//
//-----------------------------------------------------------------------------
GameEngineClass *GameEngineClass::Instance()
{
	static GameEngineClass instance;
	return &instance;
}

//-------------------------------- Startup ------------------------------------
//-----------------------------------------------------------------------------
void GameEngineClass::Startup(int narg, char *argv[])
{
	int fontFlags = TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE;
	int nFont = 0, iFont = 2, nCol = 32, nRow = 13;
	int initialDelay = 100, interval = 1000/MAX(1,MAXFPS);
	bool fullscreen = false;
	map<int, string> Fonts;
	Fonts.insert(make_pair(nFont++, "data/fonts/arial4x4.png"));
	Fonts.insert(make_pair(nFont++, "data/fonts/arial8x8.png"));
	Fonts.insert(make_pair(nFont++, "data/fonts/arial16x16.png"));
	TCOD_renderer_t renderer = TCOD_RENDERER_SDL;

	// Initialize Fonts
	TCODConsole::setCustomFont(Fonts[iFont].c_str(), fontFlags, nCol, nRow);

	// Initialize Root Console
	TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "The Serpentine Caves v"VERSION, fullscreen, renderer);

	// Set keyboard repeat delay
	TCODConsole::setKeyboardRepeat(initialDelay, interval);

	// Show cursor
	TCODMouse::showCursor(true);

	// Limit the framerate to maxFps FPS
	TCODSystem::setFps(MAXFPS);

	// Assign extra ascii keys
	int x = 0, y = 8;
	TCODConsole::mapAsciiCodeToFont(CHAR_CHARGEBAR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_PLAYER_RIGHT, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PLAYER_DOWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PLAYER_LEFT, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PLAYER_UP, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_GUARDIAN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_KEEPER, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PERSON, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_GUARD_GREY, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_GUARD_RED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_GUARD_GOLD, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_WARLOCK_PURPLE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_WARLOCK_WHITE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_WARLOCK_RED, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_NECROMANCER_APPENTICE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_NECROMANCER_MASTER, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DARKELF_ARCHER, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DARKELF_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DARKELF_MAGE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DWARF_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DWARF_AXEBEARER, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DWARF_MAGE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DWARF_HERO, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_UNDEAD_DWARF_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_UNDEAD_DWARF_AXEBEARER, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_UNDEAD_DWARF_MAGE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_UNDEAD_DWARF_HERO, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_GOBLIN_PEON, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_GOBLIN_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_GOBLIN_MAGE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_IMP_BLUE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_IMP_RED, x++, y);
	x = 0; y++;

	TCODConsole::mapAsciiCodeToFont(CHAR_ORGE_PEON_GREEN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ORGE_WARRIOR_GREEN, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_ORGE_PEON_RED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ORGE_WARRIOR_RED, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SKELETON_PEON, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SKELETON_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SKELETON_HERO, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SKELETON_MAGE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SPRITE_RED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SPRITE_BLUE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SPRITE_GREEN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SPRITE_YELLOW, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_ORC_PEON, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ORC_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ORC_HERO, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ORC_MAGE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DEMON_PEON, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMON_HERO, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMON_MAGE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_FLAYER_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FLAYER_MAGE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SKULL, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_GOLEM_GREY, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_GOLEM_BROWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_GOLEM_RED, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SLIME_BROWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SLIME_GREEN, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_EYEBALL, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_VERMIN_BROWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_VERMIN_GREEN, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SNAKE_PURLE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SNAKE_GREEN, x++, y);
	x = 0; y++;

	TCODConsole::mapAsciiCodeToFont(CHAR_SCORPIAN_YELLOW, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SCORPIAN_BLACK, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SPIDER_BLACK, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SPIDER_RED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SPIDER_GREEN, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_PYTHON_RED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PYTHON_BROWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PYTHON_YELLOW, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_BAT_BROWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_BAT_BLUE, x++, y);

	// Environment Tiles
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_A, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_B, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_C, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_D, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_E, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_F, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_G, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SHRUB_A, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SHRUB_B, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SHRUB_C, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SHRUB_D, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_MUSHROOM, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FLOWERS_WHITE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FLOWERS_BLUE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_TEMPLE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TOWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_CAVE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_BED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TABLE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_BOOKCASE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_CHAIR_RIGHT, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_CHAIR_LEFT, x++, y);
	x = 0; y++;

	// Minor Bosses (Upper Portion)
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_WHITE_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_WHITE_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_RED_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_RED_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_CYCLOPS_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_CYCLOPS_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_RED_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_RED_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_YELLOW_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_YELLOW_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREEN_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREEN_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_BLUE_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_BLUE_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREY_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREY_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_MINOTAUR_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_MINOTAUR_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_LIZARD_GIANT_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_LIZARD_GIANT_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_MEDUSA_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_MEDUSA_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_FLYING_BRAIN_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FLYING_BRAIN_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SLIMELORD_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SLIMELORD_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_BEHOLDER_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_BEHOLDER_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_BEHEMOTH_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_BEHEMOTH_UR, x++, y);

	// Final Boss (Upper Portion)
	TCODConsole::mapAsciiCodeToFont(CHAR_FINAL_BOSS_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FINAL_BOSS_UR, x++, y);
	x = 0; y++;

	// Minor Bosses (Lower Portion)
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_WHITE_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_WHITE_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_RED_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_RED_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_CYCLOPS_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_CYCLOPS_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_RED_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_RED_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_YELLOW_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_YELLOW_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREEN_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREEN_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_BLUE_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_BLUE_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREY_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREY_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_MINOTAUR_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_MINOTAUR_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_LIZARD_GIANT_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_LIZARD_GIANT_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_MEDUSA_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_MEDUSA_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_FLYING_BRAIN_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FLYING_BRAIN_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SLIMELORD_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SLIMELORD_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_BEHOLDER_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_BEHOLDER_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_BEHEMOTH_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_BEHEMOTH_LR, x++, y);

	// Final Boss (Lower Portion)
	TCODConsole::mapAsciiCodeToFont(CHAR_FINAL_BOSS_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FINAL_BOSS_LR, x++, y);

	// Libtcod credits
	TCODConsole::credits();

	// Clear root console
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->clear();

	// Initialize Random Number Generator
	// If present, get seed value from the command line
	seed = static_cast<uint32>(time(NULL));
	if(narg == 2) seed = static_cast<uint32>(atoi(argv[1]));

	// Add Modules to Game Engine
	Game(new GameClass());			// Game Module
	Menu(new MenuClass());			// Menu Module
	Map(new MapClass());				// Map Module
	Sound(new SoundClass());		// Sound Module
	Player(new PlayerClass());	// Player Module
}

//-------------------------------- Shutdown -----------------------------------
//-----------------------------------------------------------------------------
void GameEngineClass::Shutdown()
{
	// Remove all the Entities from the Entity Manager
	EntityManager()->RemoveAll();

	// Fade Out
	for(int i = 1; i <= 2*MAXFPS; i++)
	{
		int fade = 255*(2*MAXFPS - i)/(2*MAXFPS - 1);
		TCODConsole::setFade(fade, TCODColor::black);
		TCODConsole::root->flush();
	}
}

//--------------------------------- Update ------------------------------------
//-----------------------------------------------------------------------------
bool GameEngineClass::Update()
{
	bool status = true;

	elapsed = TCODSystem::getLastFrameLength();
	UpdateElapsedTime(elapsed);

	status = status && Game()->Update(elapsed, key, mouse);						// Update Game
	status = status && Sound()->Update(elapsed, key, mouse);					// Update Sound
	status = status && Map()->Update(elapsed, key, mouse);						// Update Map
	status = status && EntityManager()->Update(elapsed, key, mouse);	// Update Entities
	status = status && Player()->Update(elapsed, key, mouse);					// Update Player
	status = status && Menu()->Update(elapsed, key, mouse);						// Update Menu

	return status;
}

//--------------------------------- Render ------------------------------------
//-----------------------------------------------------------------------------
void GameEngineClass::Render()
{
	// Fade Out
	if(FadeOut())
	{
		FadeOut(false);
		for(int i = 1; i <= MAXFPS; i++)
		{
			int fade = 255*(MAXFPS - i)/(MAXFPS - 1);
			TCODConsole::setFade(fade, TCODColor::black);
			TCODConsole::root->flush();
		}
	}

	// Clear root console
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->clear();

	Game()->Render();						// Render Game
	Sound()->Render();					// Render Sound
	Map()->Render();						// Render Map
	EntityManager()->Render();	// Render Entities
	Player()->Render();					// Render Player
	Menu()->Render();						// Render Menu

	// Fade In
	if(FadeIn())
	{
		FadeIn(false);
		for(int i = 1; i <= MAXFPS; i++)
		{
			int fade = 255*(i - 1)/(MAXFPS - 1);
			TCODConsole::setFade(fade, TCODColor::black);
			TCODConsole::root->flush();
		}
	}

	// Flush Updates to Console
	TCODConsole::root->flush();

	// Get Keyboard and Mouse Input
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &key, &mouse);
}

//--------------------------------- Receive -----------------------------------
//-----------------------------------------------------------------------------
bool GameEngineClass::Receive(const Message &msg)
{
	bool status = true;
	static bool HelpFlag = false;
	static bool MenuFlag = false;
	static bool ItemInvFlag = false;
	static bool EquipInvFlag = false;
	static bool ItemShopFlag = false;
	static bool ItemShopBuyFlag = false;
	static bool ItemShopSellFlag = false;
	static bool EquipShopFlag = false;
	static bool EquipShopBuyFlag = false;
	static bool EquipShopSellFlag = false;
	static bool FerryFlag = false;
	static bool InnFlag = false;
	static bool RestFlag = false;
	static bool DeathFlag = false;

	switch(msg.Msg)
	{
		case MSG_NEWGAME:
		{
			FadeIn(true);
			FadeOut(true);
			Game()->StateMgr()->ChangeState(GameNewState);
			Sound()->StateMgr()->ChangeState(SoundNewState);
			Menu()->StateMgr(CON_01)->ChangeState(MenuNewState);
			break;
		}
		case MSG_LOADGAME:
		{
			FadeIn(true);
			FadeOut(true);
			Game()->StateMgr()->ChangeState(GameLoadState);
			Menu()->StateMgr(CON_01)->ChangeState(MenuLoadState);
			break;
		}
		case MSG_SAVEGAME:
		{
			FadeIn(true);
			FadeOut(true);

			Game()->StateMgr()->ChangeState(GameSaveState);
			Player()->StateMgr()->ChangeState(PlayerIdleState);
			Menu()->StateMgr(CON_01)->ChangeState(MenuSaveState);
			break;
		}
		case MSG_QUITGAME:
		{
			Game()->StateMgr()->ChangeState(GameQuitState);
			Sound()->StateMgr()->ChangeState(SoundQuitState);
			break;
		}
		case MSG_INTROGAME:
		{
			FadeIn(true);
			FadeOut(true);
			Game()->StateMgr()->ChangeState(GameIdleState);
			Sound()->StateMgr()->ChangeState(SoundTempleState);
			Map()->StateMgr()->ChangeState(MapTempleState);
			Player()->StateMgr()->ChangeState(PlayerIntroState);
			Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
			Menu()->StateMgr(CON_02)->ChangeState(MenuIntroState);
			break;
		}
		case MSG_BEGINGAME:
		{
			Game()->InGame(true);
			Player()->StateMgr()->ChangeState(PlayerTempleState);
			Menu()->StateMgr(CON_02)->ChangeState(MenuIdleState);
			break;
		}
		case MSG_ENTERWORLD:
		{
			FadeIn(true);
			FadeOut(true);
			Game()->StateMgr()->ChangeState(GameIdleState);
			Sound()->StateMgr()->ChangeState(SoundWorldState);
			Map()->StateMgr()->ChangeState(MapWorldState);
			Player()->StateMgr()->ChangeState(PlayerWorldState);
			Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
			break;
		}
		case MSG_ENTERTOWN:
		{
			FadeIn(true);
			FadeOut(true);
			Sound()->StateMgr()->ChangeState(SoundTownState);
			Map()->StateMgr()->ChangeState(MapTownState);
			Player()->StateMgr()->ChangeState(PlayerTownState);
			break;
		}
		case MSG_ENTERTEMPLE:
		{
			FadeIn(true);
			FadeOut(true);
			Sound()->StateMgr()->ChangeState(SoundTempleState);
			Map()->StateMgr()->ChangeState(MapTempleState);
			Player()->StateMgr()->ChangeState(PlayerTempleState);
			break;
		}
		case MSG_ENTERCAVE:
		{
			FadeIn(true);
			FadeOut(true);
			Sound()->StateMgr()->ChangeState(SoundCaveState);
			Map()->StateMgr()->ChangeState(MapCaveState);
			Player()->StateMgr()->ChangeState(PlayerCaveState);
			break;
		}
		case MSG_HELPSCREEN:
		{
			HelpFlag = !HelpFlag;
			if(HelpFlag)
			{
				Player()->StateMgr()->ChangeState(PlayerIdleState);
				if(Game()->InGame())
				{
					Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				}
				else
				{
					Menu()->StateMgr(CON_01)->ChangeState(MenuMainState);
				}
				Menu()->StateMgr(CON_02)->ChangeState(MenuHelpState);
			}
			else
			{
				Player()->StateMgr()->RevertToPreviousState();
				Menu()->StateMgr(CON_02)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_GAMEMENU:
		{
			MenuFlag = !MenuFlag;
			if(MenuFlag)
			{
				Player()->StateMgr()->ChangeState(PlayerIdleState);
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuGameState);
			}
			else
			{
				Player()->StateMgr()->RevertToPreviousState();
				Menu()->StateMgr(CON_02)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPINV:
		{
			EquipInvFlag = !EquipInvFlag;
			if(EquipInvFlag)
			{
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuGameState);
				Menu()->StateMgr(CON_03)->ChangeState(MenuEquipInvState);
			}
			else
			{
				Menu()->StateMgr(CON_03)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_ITEMINV:
		{
			ItemInvFlag = !ItemInvFlag;
			if(ItemInvFlag)
			{
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuGameState);
				Menu()->StateMgr(CON_03)->ChangeState(MenuItemInvState);
			}
			else
			{
				Menu()->StateMgr(CON_03)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_ITEMSHOPMENU:
		{
			ItemShopFlag = !ItemShopFlag;
			if(ItemShopFlag)
			{
				Player()->StateMgr()->ChangeState(PlayerIdleState);
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuItemShopState);
			}
			else
			{
				Player()->StateMgr()->RevertToPreviousState();
				Menu()->StateMgr(CON_02)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_ITEMSHOPMENUBUY:
		{
			ItemShopBuyFlag = !ItemShopBuyFlag;
			if(ItemShopBuyFlag)
			{
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuItemShopState);
				Menu()->StateMgr(CON_03)->ChangeState(MenuItemShopBuyState);
			}
			else
			{
				Menu()->StateMgr(CON_03)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_ITEMSHOPMENUSELL:
		{
			ItemShopSellFlag = !ItemShopSellFlag;
			if(ItemShopSellFlag)
			{
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuItemShopState);
				Menu()->StateMgr(CON_03)->ChangeState(MenuItemShopSellState);
			}
			else
			{
				Menu()->StateMgr(CON_03)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPMENU:
		{
			EquipShopFlag = !EquipShopFlag;
			if(EquipShopFlag)
			{
				Player()->StateMgr()->ChangeState(PlayerIdleState);
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuEquipShopState);
			}
			else
			{
				Player()->StateMgr()->RevertToPreviousState();
				Menu()->StateMgr(CON_02)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPMENUBUY:
		{
			EquipShopBuyFlag = !EquipShopBuyFlag;
			if(EquipShopBuyFlag)
			{
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuEquipShopState);
				Menu()->StateMgr(CON_03)->ChangeState(MenuEquipShopBuyState);
			}
			else
			{
				Menu()->StateMgr(CON_03)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPMENUSELL:
		{
			EquipShopSellFlag = !EquipShopSellFlag;
			if(EquipShopSellFlag)
			{
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuEquipShopState);
				Menu()->StateMgr(CON_03)->ChangeState(MenuEquipShopSellState);
			}
			else
			{
				Menu()->StateMgr(CON_03)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_FERRYMENU:
		{
			FerryFlag = !FerryFlag;
			if(FerryFlag)
			{
				Player()->StateMgr()->ChangeState(PlayerIdleState);
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuFerryState);
			}
			else
			{
				Player()->StateMgr()->RevertToPreviousState();
				Menu()->StateMgr(CON_02)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_INNMENU:
		{
			InnFlag = !InnFlag;
			if(InnFlag)
			{
				Player()->StateMgr()->ChangeState(PlayerIdleState);
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuInnState);
			}
			else
			{
				Player()->StateMgr()->RevertToPreviousState();
				Menu()->StateMgr(CON_02)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_REST:
		{
			RestFlag = !RestFlag;
			if(RestFlag)
			{
				FadeOut(true);
				Sound()->StateMgr()->ChangeState(SoundRestState);
				Player()->StateMgr()->ChangeState(PlayerRestState);
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuRestState);
			}
			else
			{
				FadeIn(true);
				InnFlag = false;
				Sound()->StateMgr()->RevertToPreviousState();
				Player()->StateMgr()->ChangeState(PlayerTownState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_DEATH:
		{
			DeathFlag = !DeathFlag;
			if(DeathFlag)
			{
				Player()->StateMgr()->ChangeState(PlayerIdleState);
				Menu()->StateMgr(CON_01)->ChangeState(MenuUIState);
				Menu()->StateMgr(CON_02)->ChangeState(MenuDeathState);
			}
			else
			{
				Menu()->StateMgr(CON_02)->ChangeState(MenuIdleState);
			}
			break;
		}
		default: break;
	}
	return status;
}
