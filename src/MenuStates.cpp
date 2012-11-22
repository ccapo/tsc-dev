#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for MenuIdle
//
//------------------------------------------------------------------------
MenuIdle *MenuIdle::Instance()
{
	static MenuIdle instance;
	return &instance;
}
void MenuIdle::Enter(MenuClass *menu){menu->DecreaseStateID();}
bool MenuIdle::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void MenuIdle::Render(MenuClass *menu){}
void MenuIdle::Exit(MenuClass *menu){menu->IncreaseStateID();}

//------------------------------------------------------------------------
//
// Methods for MenuMain
//
//------------------------------------------------------------------------
MenuMain *MenuMain::Instance()
{
	static MenuMain instance;
	return &instance;
}

bool MenuMain::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	static int cursor = 0;
	int w = 64, h = SCREEN_HEIGHT/2, i = 0;
	map<int, string> Options;
	Options.insert(make_pair(i++, "%cNew Game %c"));
	Options.insert(make_pair(i++, "%cLoad Game%c"));
	Options.insert(make_pair(i++, "%cGame Help%c"));
	Options.insert(make_pair(i++, "%cQuit Game%c"));

	// Main menu screen
	menu->Con(STATE_01, new TCODConsole(w, h));

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NMAIN;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NMAIN - 1;
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			// Select the item at the current cursor position
			switch(cursor)
			{
				case MAIN_NEW:
				{
					Transmit->Send(Engine(), MSG_NEWGAME);
					break;
				}
				case MAIN_LOAD:
				{
					Transmit->Send(Engine(), MSG_LOADGAME);
					break;
				}
				case MAIN_HELP:
				{
					Transmit->Send(Engine(), MSG_HELPSCREEN);
					break;
				}
				case MAIN_QUIT:
				{
					Transmit->Send(Engine(), MSG_QUITGAME);
					status = false;
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::white, TCODColor::lightBlue);

	// Print game title and by line
	menu->Con(STATE_01)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_01)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_01)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_01)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_01)->clear();

	int x = 2, y = 2;
	menu->Con(STATE_01)->print(x, y, "%cThe Serpentine Caves%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
	menu->Con(STATE_01)->print(x, h - 3, "%cv"VERSION"%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_01)->print(x, h - 1, "%cChris Capobianco%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

	//int istart = 256;
	//for(int i = 0; i < 32; i++) menu->Con(STATE_01)->putChar(x + i, h - 12, istart + i, TCOD_BKGND_NONE); istart += 32;
	//for(int i = 0; i < 32; i++) menu->Con(STATE_01)->putChar(x + i, h - 11, istart + i, TCOD_BKGND_NONE); istart += 32;
	//for(int i = 0; i < 32; i++) menu->Con(STATE_01)->putChar(x + i, h - 10, istart + i, TCOD_BKGND_NONE); istart += 32;
	//for(int i = 0; i < 32; i++) menu->Con(STATE_01)->putChar(x + i, h - 9, istart + i, TCOD_BKGND_NONE); istart += 32;
	//for(int i = 0; i < 32; i++) menu->Con(STATE_01)->putChar(x + i, h - 8, istart + i, TCOD_BKGND_NONE); istart += 32;
	//for(int i = 0; i < 32; i++) menu->Con(STATE_01)->putChar(x + i, h - 7, istart + i, TCOD_BKGND_NONE); istart += 32;

	// Print the menu options
	y = NMAIN;
	for(int i = 0; i < NMAIN; i++)
	{
		y += 2;
		if(i == cursor)
		{
			// Print currently selected item
			menu->Con(STATE_01)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		else
		{
			// Print all other menu items
			menu->Con(STATE_01)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
		}
	}

	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuMain::Render(MenuClass *menu)
{
	int w = 24, h = SCREEN_HEIGHT/2, x = SCREEN_WIDTH/8, y = SCREEN_HEIGHT/4;

	// Blit the background image to the root console
	menu->ImgBG()->blit2x(TCODConsole::root, 0, y/2);

	// Blit the main menu to the root console
	TCODConsole::blit(menu->Con(STATE_01), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuNew
//
//------------------------------------------------------------------------
MenuNew *MenuNew::Instance()
{
	static MenuNew instance;
	return &instance;
}

bool MenuNew::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void MenuNew::Render(MenuClass *menu)
{
	menu->DisplayProgress("Generating Serpentine Caves ", Engine()->Game()->FractionalProgress());
}

//------------------------------------------------------------------------
//
// Methods for MenuLoad
//
//------------------------------------------------------------------------
MenuLoad *MenuLoad::Instance()
{
	static MenuLoad instance;
	return &instance;
}

bool MenuLoad::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void MenuLoad::Render(MenuClass *menu)
{
	menu->DisplayProgress("Loading Serpentine Caves", Engine()->Game()->FractionalProgress());
}

//------------------------------------------------------------------------
//
// Methods for MenuSave
//
//------------------------------------------------------------------------
MenuSave *MenuSave::Instance()
{
	static MenuSave instance;
	return &instance;
}

bool MenuSave::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void MenuSave::Render(MenuClass *menu)
{
	menu->DisplayProgress("Saving Serpentine Caves ", Engine()->Game()->FractionalProgress());
}

//------------------------------------------------------------------------
//
// Methods for MenuHelp
//
//------------------------------------------------------------------------
MenuHelp *MenuHelp::Instance()
{
	static MenuHelp instance;
	return &instance;
}

bool MenuHelp::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int xend = w - 8, yend = h - 4, nInfo = 0;
	map<int, string> Options;
	Options.insert(make_pair(nInfo++, "Move/Attack        :: Arrow Keys       "));
	Options.insert(make_pair(nInfo++, "Use Magic          :: Left Mouse Button"));
	Options.insert(make_pair(nInfo++, "Select Magic       :: Control          "));
	Options.insert(make_pair(nInfo++, "Toggle Menu/Cancel :: Escape           "));
	Options.insert(make_pair(nInfo++, "Select/Action      :: Enter            "));
	Options.insert(make_pair(nInfo++, "Toggle Music       :: Pause            "));
	Options.insert(make_pair(nInfo++, "Toggle Fullscreen  :: Alt + Enter      "));
	Options.insert(make_pair(nInfo++, "Screen Capture     :: Backspace        "));
	Options.insert(make_pair(nInfo++, "Game Help          :: ?                "));

	// The Help Screen
	menu->Con(STATE_02, new TCODConsole(w, h));

	switch(key.vk)
	{
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			Transmit->Send(Engine(), MSG_HELPSCREEN);
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::red, TCODColor::black);

	// Set default console colours
	menu->Con(STATE_02)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_02)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_02)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_02)->clear();

	// Print frame and title
	menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Game Help");

	// Print the information page contents
	int x = 4, y = 5;
	menu->Con(STATE_02)->print(x, y++, "%cCommands%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	y++;
	for(int i = 0; i < nInfo; i++) menu->Con(STATE_02)->print(x, y++, Options[i].c_str());

	menu->Con(STATE_02)->print(x, ++y, "%cSaving%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	y++;
	menu->Con(STATE_02)->printRect(x, ++y, xend, yend, "Whenever the Player returns to the %cWorld Map%c, the game will automatically overwrite the existing save file.\n\nIf the Player expires, death is %cpermanent%c as the save file is %cdeleted%c.", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

	menu->Con(STATE_02)->print(xend, yend + 2, "%c[Enter]%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	return status;
}

void MenuHelp::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int x = DISPLAY_WIDTH/2 - w/2, y = SCREEN_HEIGHT/2 - h/2;

	// In Game specific settings
	if(Engine()->Game()->InGame()) y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the info screen to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 0.85f);
}

//------------------------------------------------------------------------
//
// Methods for MenuIntro
//
//------------------------------------------------------------------------
MenuIntro *MenuIntro::Instance()
{
	static MenuIntro instance;
	return &instance;
}

bool MenuIntro::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int xstart = 4, ystart = 7, xend = w - 8, yend = h - 4;

	// The Introduction Screen
	menu->Con(STATE_02, new TCODConsole(w, h));

	switch(key.vk)
	{
		case TCODK_ENTER:
		{
			menu->IncrementIntroPage();
			if(menu->IsIntroComplete())
			{
				menu->ResetIntroPage();
				Transmit->Send(Engine(), MSG_BEGINGAME);
			}
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::red, TCODColor::black);

	// Set default console colours
	menu->Con(STATE_02)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_02)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_02)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_02)->clear();

	// Print frame and title
	menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Introduction");

	switch(menu->IntroPage())
	{
		case INTRO_01:
		{
			// Print the introduction page contents
			menu->Con(STATE_02)->printRect(xstart, ystart, xend, yend, "Welome brave adventurer, thank you for heeding my pleas for help.\n\n\nI am the %cGuardian of Light%c, one of the five entrusted to protect this world.\n\n\nA %cPowerful Ancient Menace%c is gathering once again in the shadows, and threatens to destroy the peace and harmony of these lands.\n\n\nThis is why I have summoned you here, I must impress upon you to persue a perilous quest to rid the world of this threat.", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			break;
		}
		case INTRO_02:
		{
			// Print the introduction page contents
			menu->Con(STATE_02)->printRect(xstart, ystart, xend, yend, "We know this power is gathering deep within\n%cThe Serpentine Caves%c, but where we know not.\n\n\nIt will be a difficult journey, so seek out the other four %cElemental Guardians%c for assistance. If they deem you worthy, they will grant you the ability to use their power.\n\n\nTo aid you on your quest I will grant my %cPower of Light%c, and any creature of the dark will be startled by its brilliance. Use this power wisely.\n\n\nGood luck brave hero, and may the record of your deeds be sung throughout the ages.", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
			break;
		}
		default: break;
	}

	menu->Con(STATE_02)->print(xend, yend + 2, "%c[Enter]%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	return status;
}

void MenuIntro::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the introduction screen to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 0.85f);
}

//------------------------------------------------------------------------
//
// Methods for MenuGame
//
//------------------------------------------------------------------------
MenuGame *MenuGame::Instance()
{
	static MenuGame instance;
	return &instance;
}

bool MenuGame::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2, i = 0, j = 0;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;
	int xstart = 3, ystart = 3, xend = ws - 6, yend = hs - 6;
	map<int, string> Options, SubOptions;
	Options.insert(make_pair(i++, "%cEquipment%c"));
	Options.insert(make_pair(i++, "%cInventory%c"));
	Options.insert(make_pair(i++, "%cQuit Game%c"));
	SubOptions.insert(make_pair(j++, "%cWeapon   %c"));
	SubOptions.insert(make_pair(j++, "%cShield   %c"));
	SubOptions.insert(make_pair(j++, "%cArmour   %c"));
	SubOptions.insert(make_pair(j++, "%cAccessory%c"));

	// Game menu screen
	menu->Con(STATE_02, new TCODConsole(w, h));

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

	// Update Player Stats
	//Engine()->Player()->UpdateStats();

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NGAME;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NGAME - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			// Exit Menu
			Transmit->Send(Engine(), MSG_GAMEMENU);
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			// Select the item at the current cursor position
			switch(cursor)
			{
				case GAME_EQUIP:
				{
					Transmit->Send(Engine(), MSG_EQUIPINV);
					break;
				}
				case GAME_ITEMS:
				{
					Transmit->Send(Engine(), MSG_ITEMINV);
					break;
				}
				case GAME_EXIT:
				{
					//Engine()->Sound()->ToggleVolume(0.5f);
					Transmit->Send(Engine(), MSG_QUITGAME);
					status = false;
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_02)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_02)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_02)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_02)->clear();

	// Set default colours for console
	menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_03)->clear();

	// Print frame and title
	menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Game Menu");
	menu->Con(STATE_02)->printFrame(1, 1, 15, 2*NGAME + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 2*NGAME + 4, 15, h - 11, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

	x = 3, y = 12;
	menu->Con(STATE_02)->print(x, y, "%cHP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_02)->print(x + 4, y++, "%d/%d", Engine()->Player()->Stats()->HP(), Engine()->Player()->Stats()->HPMax());
	menu->Con(STATE_02)->print(x + 4, y++, "%d/%d", Engine()->Player()->HP(), Engine()->Player()->HPMax());

	menu->Con(STATE_02)->print(x, y, "%cMP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_02)->print(x + 4, y++, "%d/%d", Engine()->Player()->Stats()->MP(), Engine()->Player()->Stats()->MPMax());
	menu->Con(STATE_02)->print(x + 4, y++, "%d/%d", Engine()->Player()->MP(), Engine()->Player()->MPMax());

	menu->Con(STATE_02)->print(x, ++y, "%cStatus:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//for(int i = 0; i < 5; i++) if(GameEngin()->Player()->Health()->Status[i]) menu->Con(STATE_02)->print(x, ++y, "%s", GameEngin()->Player()->Health()->Name[i]);
	menu->Con(STATE_02)->print(x, ++y, "%s", "Healthy");

	//for(int i = 0; i < NSTATUS; i++)
	//{
	//	if(Engine()->Player()->Health()->Status[i])
	//	{
	//		menu->Con(STATE_02)->print(x, ++y, "%s", Engine()->Player()->Health()->StatusName[i]);
	//	}
	//}
	menu->Con(STATE_02)->print(x, ++y, "%s", "Burdened");
	menu->Con(STATE_02)->print(x, ++y, "%s", "Poisoned");
	menu->Con(STATE_02)->print(x, ++y, "%s", "Weakened");
	menu->Con(STATE_02)->print(x, ++y, "%s", "Sluggish");
	menu->Con(STATE_02)->print(x, ++y, "%s", "Feeble");
	menu->Con(STATE_02)->print(x, ++y, "%s", "Confused");

	// Compute the elapsed time in convenient units
	int nhours = static_cast<int>(Engine()->ElapsedTime()/(60.0f*60.0f));
	float time = Engine()->ElapsedTime() - (60.0f*60.0f)*static_cast<float>(nhours);
	int nmins = static_cast<int>(time/60.0f);
	int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

	x = 3, y = 24;
	menu->Con(STATE_02)->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_02)->print(x + 4, y++, "%d", Engine()->Player()->GP());
	menu->Con(STATE_02)->print(x + 4, y++, "%d", 100);
	y++;

	menu->Con(STATE_02)->print(x, y++, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_02)->print(x, y, "%02d:%02d:%02d", nhours, nmins, nsecs);

	// Print the menu options
	y = 1;
	for(int i = 0; i < NGAME; i++)
	{
		y += 2;
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			switch(cursor)
			{
				case GAME_EQUIP:
				{
					int xe = 2, ye = 2;
					menu->Con(STATE_03)->clear();
					menu->Con(STATE_03)->printFrame(0, 0, ws, NEQUIPTYPE + 6, false, TCOD_BKGND_SET);
					menu->Con(STATE_03)->printFrame(0, NEQUIPTYPE + 6, 18, hs - (NEQUIPTYPE + 6), false, TCOD_BKGND_SET);
					menu->Con(STATE_03)->printFrame(18, NEQUIPTYPE + 6, ws - 18, hs - (NEQUIPTYPE + 6), false, TCOD_BKGND_SET);

					// Equipment
					menu->Con(STATE_03)->print(xe, ye, "%cEquipment%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
					ye += 2;

					for(int i = 0; i < NEQUIPTYPE; i++)
					{
						//menu->Con(STATE_03)->print(xe, ye, game.player.equipInv.equiped[i].label, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xe + 13, ye, game.player.equipInv.equiped[i].name, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
						menu->Con(STATE_03)->print(xe, ye, SubOptions[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						switch(i)
						{
							case WEAPON:
							{
								menu->Con(STATE_03)->print(xe + 13, ye, Engine()->Map()->WeaponNames[0].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
								break;
							}
							case SHIELD:
							{
								menu->Con(STATE_03)->print(xe + 13, ye, Engine()->Map()->ShieldNames[0].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
								break;
							}
							case ARMOUR:
							{
								menu->Con(STATE_03)->print(xe + 13, ye, Engine()->Map()->ArmourNames[0].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
								break;
							}
							case ACCESSORY:
							{
								menu->Con(STATE_03)->print(xe + 13, ye, Engine()->Map()->AccessoryNames[0].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
								break;
							}
							default: break;
						}
						ye++;
					}

					ye = NEQUIPTYPE + 8;
					menu->Con(STATE_03)->print(xe, ye, "%cStats%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->putChar(xe + 8, ye, CHAR_PLAYER_RIGHT, TCOD_BKGND_NONE);
					ye += 2;

					//float xpfraction = static_cast<float>(game.player.xp)/static_cast<float>(game.player.xpnext);
					//int xpbar = static_cast<int>(14.0f*xpfraction);
					//if(xpbar > 0)
					//{
					//		menu->Con(STATE_03)->setDefaultBackground(TCODColor::darkGreen);
					//		menu->Con(STATE_03)->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
					//}
					//if(xpbar < 14)
					//{
					//		menu->Con(STATE_03)->setDefaultBackground(TCODColor::darkerGreen);
					//		menu->Con(STATE_03)->rect(x + xpbar, y + 1, 14 - xpbar, 1, true, TCOD_BKGND_SET);
					//}
					//menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
					//menu->Con(STATE_03)->print(x, y, "%cLVL%c : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.lvl);
					//menu->Con(STATE_03)->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", game.player.xp, game.player.xpnext);
					float xpfraction = static_cast<float>(0)/static_cast<float>(100);
					int xpbar = static_cast<int>(14.0f*xpfraction);
					if(xpbar > 0)
					{
							menu->Con(STATE_03)->setDefaultBackground(TCODColor::darkGreen);
							menu->Con(STATE_03)->rect(xe, ye + 1, xpbar, 1, true, TCOD_BKGND_SET);
					}
					if(xpbar < 14)
					{
							menu->Con(STATE_03)->setDefaultBackground(TCODColor::darkerGreen);
							menu->Con(STATE_03)->rect(xe + xpbar, ye + 1, 14 - xpbar, 1, true, TCOD_BKGND_SET);
					}
					menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
					menu->Con(STATE_03)->print(xe, ye, "%cLVL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 7, ye++, "%2d", 1);
					menu->Con(STATE_03)->printEx(xe + 7, ye, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", 0, 100);

					//y++;
					//menu->Con(STATE_03)->print(x, y, "%cHPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.hpmax);
					ye++;
					menu->Con(STATE_03)->print(xe, ye, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 7, ye++, "%2d", 20);

					//menu->Con(STATE_03)->print(x, y, "%cATK%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.ap);
					//menu->Con(STATE_03)->print(x, y, "%cDEF%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.dp);
					menu->Con(STATE_03)->print(xe, ye, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 7, ye++, "%2d", 4);
					menu->Con(STATE_03)->print(xe, ye, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 7, ye++, "%2d", 2);

					//menu->Con(STATE_03)->print(x, y, "%cSTR%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.str);
					//menu->Con(STATE_03)->print(x, y, "%cSPD%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.spd);
					menu->Con(STATE_03)->print(xe, ye, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 7, ye++, "%2d", 10);
					menu->Con(STATE_03)->print(xe, ye, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 7, ye++, "%2d", 12);

					//y++;
					//menu->Con(STATE_03)->print(x, y, "%cMPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.mpmax);
					ye++;
					menu->Con(STATE_03)->print(xe, ye, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 7, ye++, "%2d", 10);

					//menu->Con(STATE_03)->print(x, y, "%cM.ATK%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.map);
					//menu->Con(STATE_03)->print(x, y, "%cM.DEF%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.mdp);
					menu->Con(STATE_03)->print(xe, ye, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 7, ye++, "%2d", 5);
					menu->Con(STATE_03)->print(xe, ye, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 7, ye++, "%2d", 2);

					//menu->Con(STATE_03)->print(x, y, "%cWIL%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.wil);
					//menu->Con(STATE_03)->print(x, y, "%cACU%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.acu);
					menu->Con(STATE_03)->print(xe, ye, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 7, ye++, "%2d", 6);
					menu->Con(STATE_03)->print(xe, ye, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 7, ye++, "%2d", 3);

					break;
				}
				case GAME_ITEMS:
				{
					int NITEMS = 10, NHIDES = 6;
					int xi = 2, yi = 2;
					menu->Con(STATE_03)->clear();
					menu->Con(STATE_03)->printFrame(0, 0, ws, hs - (NHIDES + 6), false, TCOD_BKGND_SET);
					menu->Con(STATE_03)->printFrame(0, hs - (NHIDES + 6), ws, NHIDES + 6, false, TCOD_BKGND_SET);

					// Items
					menu->Con(STATE_03)->print(xi, yi, "%cItems%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xi + 27, yi++, "%cQty%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

					//for(int i = 0; i < game.player.itemInv.nitems; i++)
					for(int i = 0; i < NITEMS; i++)
					{
						//int j = game.player.itemInv.index[i];
						//menu->Con(STATE_03)->print(xi, ++yi, game.player.itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xi + 24, yi, " : %2d", game.player.itemInv.count[j]);
						menu->Con(STATE_03)->print(xi, ++yi, "%cRare Item%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						menu->Con(STATE_03)->print(xi + 24, yi, " : %2d", 2);
					}

					// Hide Invetory
					yi = DISPLAY_HEIGHT/2 - 2;
					menu->Con(STATE_03)->print(xi, yi, "%cHides%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xi + 27, yi++, "%cQty%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

					//for(int i = 0; i < game.player.hideInv.nhides; i++)
					for(int i = 0; i < NHIDES; i++)
					{
						//int j = game.player.hideInv.index[i];
						//menu->Con(STATE_03)->print(xi, ++yi, game.player.hideInv.hides[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xi + 24, yi, " : %2d", game.player.hideInv.count[j]);
						menu->Con(STATE_03)->print(xi, ++yi, "%cRare Hide%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						menu->Con(STATE_03)->print(xi + 24, yi, " : %2d", 3);
					}
					break;
				}
				default: break;
			}
		}
		else
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuGame::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuEquipInv
//
//------------------------------------------------------------------------
MenuEquipInv *MenuEquipInv::Instance()
{
	static MenuEquipInv instance;
	return &instance;
}

bool MenuEquipInv::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	static int cursor = 0;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2, i = 0, j = 0;
	map<int, string> Options, SubOptions;
	Options.insert(make_pair(i++, "%cWeapon   %c"));
	Options.insert(make_pair(i++, "%cShield   %c"));
	Options.insert(make_pair(i++, "%cArmour   %c"));
	Options.insert(make_pair(i++, "%cAccessory%c"));
	SubOptions.insert(make_pair(j++, "%cWeapon List%c"));
	SubOptions.insert(make_pair(j++, "%cShield List%c"));
	SubOptions.insert(make_pair(j++, "%cArmour List%c"));
	SubOptions.insert(make_pair(j++, "%cAccessory List%c"));

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NEQUIPTYPE;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NEQUIPTYPE - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			// Exit Menu
			Transmit->Send(Engine(), MSG_EQUIPINV);
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			// Select the item at the current cursor position
			switch(cursor)
			{
				case WEAPON:
				{
					Transmit->Send(Engine(), MSG_WEAPONINV);
					break;
				}
				case SHIELD:
				{
					Transmit->Send(Engine(), MSG_SHIELDINV);
					break;
				}
				case ARMOUR:
				{
					Transmit->Send(Engine(), MSG_ARMOURINV);
					break;
				}
				case ACCESSORY:
				{
					Transmit->Send(Engine(), MSG_ACCESSORYINV);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_03)->clear();

	// Print frames
	menu->Con(STATE_03)->printFrame(0, 0, ws, NEQUIPTYPE + 6, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, NEQUIPTYPE + 6, 18, hs - (NEQUIPTYPE + 6), false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(18, NEQUIPTYPE + 6, ws - 18, hs - (NEQUIPTYPE + 6), false, TCOD_BKGND_SET);

	// Equipment
	int x = 2, y = 2;
	menu->Con(STATE_03)->print(x, y, "%cEquipment%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	y += 2;

	// List Current Equipment
	for(int i = 0; i < NEQUIPTYPE; i++)
	{
		// Highlight Selection
		if(i == cursor)
		{
			//menu->Con(STATE_03)->print(x, y, game.player.equipInv.equiped[i].label, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 13, y, game.player.equipInv.equiped[i].name, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			int xb = ws - 17, yb = NEQUIPTYPE + 8;
			switch(cursor)
			{
				case WEAPON:
				{
					menu->Con(STATE_03)->print(x + 13, y, Engine()->Map()->WeaponNames[0].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

					menu->Con(STATE_03)->print(xb, yb, SubOptions[i].c_str(), TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
					yb += 2;
					for(int j = 0; j < 9; j++)
					{
						menu->Con(STATE_03)->print(xb, yb, Engine()->Map()->WeaponNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						yb++;
					}
					break;
				}
				case SHIELD:
				{
					menu->Con(STATE_03)->print(x + 13, y, Engine()->Map()->ShieldNames[0].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

					menu->Con(STATE_03)->print(xb, yb, SubOptions[i].c_str(), TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
					yb += 2;
					for(int j = 0; j < 9; j++)
					{
						menu->Con(STATE_03)->print(xb, yb, Engine()->Map()->ShieldNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						yb++;
					}
					break;
				}
				case ARMOUR:
				{
					menu->Con(STATE_03)->print(x + 13, y, Engine()->Map()->ArmourNames[0].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

					menu->Con(STATE_03)->print(xb, yb, SubOptions[i].c_str(), TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
					yb += 2;
					for(int j = 0; j < 9; j++)
					{
						menu->Con(STATE_03)->print(xb, yb, Engine()->Map()->ArmourNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						yb++;
					}
					break;
				}
				case ACCESSORY:
				{
					menu->Con(STATE_03)->print(x + 13, y, Engine()->Map()->AccessoryNames[0].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

					menu->Con(STATE_03)->print(xb, yb, SubOptions[i].c_str(), TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
					yb += 2;
					for(int j = 0; j < 9; j++)
					{
						menu->Con(STATE_03)->print(xb, yb, Engine()->Map()->AccessoryNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						yb++;
					}
					break;
				}
				default: break;
			}
		}
		else
		{
			//menu->Con(STATE_03)->print(x, y, game.player.equipInv.equiped[i].label, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 13, y, game.player.equipInv.equiped[i].name, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 13, y, Options[i].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

			switch(i)
			{
				case WEAPON:
				{
					menu->Con(STATE_03)->print(x + 13, y, Engine()->Map()->WeaponNames[0].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
					break;
				}
				case SHIELD:
				{
					menu->Con(STATE_03)->print(x + 13, y, Engine()->Map()->ShieldNames[0].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
					break;
				}
				case ARMOUR:
				{
					menu->Con(STATE_03)->print(x + 13, y, Engine()->Map()->ArmourNames[0].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
					break;
				}
				case ACCESSORY:
				{
					menu->Con(STATE_03)->print(x + 13, y, Engine()->Map()->AccessoryNames[0].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
					break;
				}
				default: break;
			}
		}
		y++;
	}

	// List Current Stats
	y = NEQUIPTYPE + 8;
	menu->Con(STATE_03)->print(x, y, "%cStats%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->putChar(x + 8, y, CHAR_PLAYER_RIGHT, TCOD_BKGND_NONE);
	y += 2;

	//float xpfraction = static_cast<float>(game.player.xp)/static_cast<float>(game.player.xpnext);
	//int xpbar = static_cast<int>(14.0f*xpfraction);
	//if(xpbar > 0)
	//{
	//	menu->Con(STATE_03)->setDefaultBackground(TCODColor::darkGreen);
	//	menu->Con(STATE_03)->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
	//}
	//if(xpbar < 14)
	//{
	//	menu->Con(STATE_03)->setDefaultBackground(TCODColor::darkerGreen);
	//	menu->Con(STATE_03)->rect(x + xpbar, y + 1, 14 - xpbar, 1, true, TCOD_BKGND_SET);
	//}
	//menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	//menu->Con(STATE_03)->print(x, y, "%cLVL%c : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.lvl);
	//menu->Con(STATE_03)->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", game.player.xp, game.player.xpnext);
	float xpfraction = static_cast<float>(0)/static_cast<float>(100);
	int xpbar = static_cast<int>(14.0f*xpfraction);
	if(xpbar > 0)
	{
		menu->Con(STATE_03)->setDefaultBackground(TCODColor::darkGreen);
		menu->Con(STATE_03)->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
	}
	if(xpbar < 14)
	{
		menu->Con(STATE_03)->setDefaultBackground(TCODColor::darkerGreen);
		menu->Con(STATE_03)->rect(x + xpbar, y + 1, 14 - xpbar, 1, true, TCOD_BKGND_SET);
	}
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_03)->print(x, y, "%cLVL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 7, y++, "%2d", 1);
	menu->Con(STATE_03)->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", 0, 100);

	//y++;
	//menu->Con(STATE_03)->print(x, y, "%cHPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.hpmax);
	y++;
	menu->Con(STATE_03)->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 7, y++, "%2d", 20);

	//menu->Con(STATE_03)->print(x, y, "%cATK%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.ap);
	//menu->Con(STATE_03)->print(x, y, "%cDEF%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.dp);
	menu->Con(STATE_03)->print(x, y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 7, y++, "%2d", 4);
	menu->Con(STATE_03)->print(x, y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 7, y++, "%2d", 2);

	//menu->Con(STATE_03)->print(x, y, "%cSTR%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.str);
	//menu->Con(STATE_03)->print(x, y, "%cSPD%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.spd);
	menu->Con(STATE_03)->print(x, y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 7, y++, "%2d", 10);
	menu->Con(STATE_03)->print(x, y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 7, y++, "%2d", 12);

	//y++;
	//menu->Con(STATE_03)->print(x, y, "%cMPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.mpmax);
	y++;
	menu->Con(STATE_03)->print(x, y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 7, y++, "%2d", 10);

	//menu->Con(STATE_03)->print(x, y, "%cM.ATK%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.map);
	//menu->Con(STATE_03)->print(x, y, "%cM.DEF%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.mdp);
	menu->Con(STATE_03)->print(x, y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 7, y++, "%2d", 5);
	menu->Con(STATE_03)->print(x, y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 7, y++, "%2d", 2);

	//menu->Con(STATE_03)->print(x, y, "%cWIL%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.wil);
	//menu->Con(STATE_03)->print(x, y, "%cACU%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.acu);
	menu->Con(STATE_03)->print(x, y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 7, y++, "%2d", 6);
	menu->Con(STATE_03)->print(x, y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 7, y++, "%2d", 3);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipInv::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuWeaponInv
//
//------------------------------------------------------------------------
MenuWeaponInv *MenuWeaponInv::Instance()
{
	static MenuWeaponInv instance;
	return &instance;
}

bool MenuWeaponInv::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	static int cursor = 0;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2 - (NEQUIPTYPE + 6), NWEAPONS = 9;

	// Game submenu screen
	menu->Con(STATE_04, new TCODConsole(ws, hs));

	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NWEAPONS;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NWEAPONS - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			// Exit Menu
			Transmit->Send(Engine(), MSG_WEAPONINV);
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			// Swap equipment
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_04)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_04)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_04)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_04)->clear();

	// Print frames
	menu->Con(STATE_04)->printFrame(0, 0, 18, hs, false, TCOD_BKGND_SET);
	menu->Con(STATE_04)->printFrame(18, 0, ws - 18, hs, false, TCOD_BKGND_SET);

	// Equipment
	int x = 2, y = 2;
	menu->Con(STATE_04)->print(x + 18, y, "%cWeapon List%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	y += 2;

	// List Current Equipment
	//Stats stats = game.player.stats;
	for(int i = 0; i < NWEAPONS; i++)
	{
		// Highlight Selection
		if(i == cursor)
		{
			//menu->Con(STATE_04)->print(x + 18, y++, game.player.equipInv.Weapons[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_04)->print(x + 18, hs - 3, game.player.equipInv.Weapons[j].desc);
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->WeaponNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x + 18, hs - 3, "AP +2");

			//stats -= game.player.equipInv.equiped[WEAPON].stats;
			//stats.hpmax -= game.player.equipInv.equiped[WEAPON].stats.hpmax;
			//stats.mpmax -= game.player.equipInv.equiped[WEAPON].stats.mpmax;

			//stats += game.player.equipInv.Weapons[j].stats;
			//stats.hpmax += game.player.equipInv.Weapons[j].stats.hpmax;
			//stats.mpmax += game.player.equipInv.Weapons[j].stats.mpmax;
		}
		else
		{
			//menu->Con(STATE_04)->print(x + 18, y++, game.player.equipInv.Weapons[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->WeaponNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	// List Current Stats
	y = 2;
	menu->Con(STATE_04)->print(x, y, "%cStats%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->putChar(x + 8, y, CHAR_PLAYER_RIGHT, TCOD_BKGND_NONE);
	y += 2;

	//float xpfraction = static_cast<float>(game.player.xp)/static_cast<float>(game.player.xpnext);
	//int xpbar = static_cast<int>(14.0f*xpfraction);
	//if(xpbar > 0)
	//{
	//	menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkGreen);
	//	menu->Con(STATE_04)->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
	//}
	//if(xpbar < 14)
	//{
	//	menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkerGreen);
	//	menu->Con(STATE_04)->rect(x + xpbar, y + 1, 14 - xpbar, 1, true, TCOD_BKGND_SET);
	//}
	//menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	//menu->Con(STATE_04)->print(x, y, "%cLVL%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y++, "%2d", game.player.lvl);
	//menu->Con(STATE_04)->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", game.player.xp, game.player.xpnext);
	float xpfraction = static_cast<float>(0)/static_cast<float>(100);
	int xpbar = static_cast<int>(14.0f*xpfraction);
	if(xpbar > 0)
	{
		menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkGreen);
		menu->Con(STATE_04)->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
	}
	if(xpbar < 14)
	{
		menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkerGreen);
		menu->Con(STATE_04)->rect(x + xpbar, y + 1, 14 - xpbar, 1, true, TCOD_BKGND_SET);
	}
	menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_04)->print(x, y, "%cLVL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y++, "%2d", 1);
	menu->Con(STATE_04)->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", 0, 100);

	//y++;
	//menu->Con(STATE_04)->print(x, y, "%cHPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.hpmax);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.hpmax, stats.hpmax);
	y++;
	menu->Con(STATE_04)->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 20);
	menu->DisplayUpdatedStat(x, y, 20, 30);

	//menu->Con(STATE_04)->print(x, ++y, "%cMPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.mpmax);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.mpmax, stats.mpmax);
	menu->Con(STATE_04)->print(x, ++y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 10);
	menu->DisplayUpdatedStat(x, y, 10, 15);

	//y++;
	//menu->Con(STATE_04)->print(x, ++y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.ap);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.ap, stats.ap);
	y++;
	menu->Con(STATE_04)->print(x, ++y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 4);
	menu->DisplayUpdatedStat(x, y, 4, 6);

	//menu->Con(STATE_04)->print(x, ++y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.dp);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.dp, stats.dp);
	menu->Con(STATE_04)->print(x, ++y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 2);
	menu->DisplayUpdatedStat(x, y, 2, 1);

	//menu->Con(STATE_04)->print(x, ++y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.str);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.str, stats.str);
	menu->Con(STATE_04)->print(x, ++y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 10);
	menu->DisplayUpdatedStat(x, y, 10, 15);

	//menu->Con(STATE_04)->print(x, ++y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.spd);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.spd, stats.spd);
	menu->Con(STATE_04)->print(x, ++y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 12);
	menu->DisplayUpdatedStat(x, y, 12, 8);

	//menu->Con(STATE_04)->print(x, ++y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.map);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.map, stats.map);
	menu->Con(STATE_04)->print(x, ++y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 5);
	menu->DisplayUpdatedStat(x, y, 5, 4);

	//menu->Con(STATE_04)->print(x, ++y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.mdp);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.mdp, stats.mdp);
	menu->Con(STATE_04)->print(x, ++y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 2);
	menu->DisplayUpdatedStat(x, y, 2, 4);

	//menu->Con(STATE_04)->print(x, ++y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.wil);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.wil, stats.wil);
	menu->Con(STATE_04)->print(x, ++y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 6);
	menu->DisplayUpdatedStat(x, y, 6, 8);

	//menu->Con(STATE_04)->print(x, ++y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.acu);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.acu, stats.acu);
	menu->Con(STATE_04)->print(x, ++y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 3);
	menu->DisplayUpdatedStat(x, y, 3, 1);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuWeaponInv::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2 - (NEQUIPTYPE + 6);
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3 + (NEQUIPTYPE + 6);

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuShieldInv
//
//------------------------------------------------------------------------
MenuShieldInv *MenuShieldInv::Instance()
{
	static MenuShieldInv instance;
	return &instance;
}

bool MenuShieldInv::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	static int cursor = 0;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2 - (NEQUIPTYPE + 6), NSHIELDS = 9;

	// Game submenu screen
	menu->Con(STATE_04, new TCODConsole(ws, hs));

	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NSHIELDS;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NSHIELDS - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			// Exit Menu
			Transmit->Send(Engine(), MSG_SHIELDINV);
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			// Swap equipment
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_04)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_04)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_04)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_04)->clear();

	// Print frames
	menu->Con(STATE_04)->printFrame(0, 0, 18, hs, false, TCOD_BKGND_SET);
	menu->Con(STATE_04)->printFrame(18, 0, ws - 18, hs, false, TCOD_BKGND_SET);

	// Equipment
	int x = 2, y = 2;
	menu->Con(STATE_04)->print(x + 18, y, "%cShield List%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	y += 2;

	// List Current Equipment
	//Stats stats = game.player.stats;
	for(int i = 0; i < NSHIELDS; i++)
	{
		// Highlight Selection
		if(i == cursor)
		{
			//menu->Con(STATE_04)->print(x + 18, y++, game.player.equipInv.Shields[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_04)->print(x + 18, hs - 3, game.player.equipInv.Shields[j].desc);
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->ShieldNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x + 18, hs - 3, "DP +2");

			//stats -= game.player.equipInv.equiped[SHIELD].stats;
			//stats.hpmax -= game.player.equipInv.equiped[SHIELD].stats.hpmax;
			//stats.mpmax -= game.player.equipInv.equiped[SHIELD].stats.mpmax;

			//stats += game.player.equipInv.Shields[j].stats;
			//stats.hpmax += game.player.equipInv.Shields[j].stats.hpmax;
			//stats.mpmax += game.player.equipInv.Shields[j].stats.mpmax;
		}
		else
		{
			//menu->Con(STATE_04)->print(x + 18, y++, game.player.equipInv.Shields[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->ShieldNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	// List Current Stats
	y = 2;
	menu->Con(STATE_04)->print(x, y, "%cStats%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->putChar(x + 8, y, CHAR_PLAYER_RIGHT, TCOD_BKGND_NONE);
	y += 2;

	//float xpfraction = static_cast<float>(game.player.xp)/static_cast<float>(game.player.xpnext);
	//int xpbar = static_cast<int>(14.0f*xpfraction);
	//if(xpbar > 0)
	//{
	//	menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkGreen);
	//	menu->Con(STATE_04)->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
	//}
	//if(xpbar < 14)
	//{
	//	menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkerGreen);
	//	menu->Con(STATE_04)->rect(x + xpbar, y + 1, 14 - xpbar, 1, true, TCOD_BKGND_SET);
	//}
	//menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	//menu->Con(STATE_04)->print(x, y, "%cLVL%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y++, "%2d", game.player.lvl);
	//menu->Con(STATE_04)->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", game.player.xp, game.player.xpnext);
	float xpfraction = static_cast<float>(0)/static_cast<float>(100);
	int xpbar = static_cast<int>(14.0f*xpfraction);
	if(xpbar > 0)
	{
		menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkGreen);
		menu->Con(STATE_04)->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
	}
	if(xpbar < 14)
	{
		menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkerGreen);
		menu->Con(STATE_04)->rect(x + xpbar, y + 1, 14 - xpbar, 1, true, TCOD_BKGND_SET);
	}
	menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_04)->print(x, y, "%cLVL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y++, "%2d", 1);
	menu->Con(STATE_04)->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", 0, 100);

	//y++;
	//menu->Con(STATE_04)->print(x, y, "%cHPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.hpmax);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.hpmax, stats.hpmax);
	y++;
	menu->Con(STATE_04)->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 20);
	menu->DisplayUpdatedStat(x, y, 20, 30);

	//menu->Con(STATE_04)->print(x, ++y, "%cMPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.mpmax);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.mpmax, stats.mpmax);
	menu->Con(STATE_04)->print(x, ++y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 10);
	menu->DisplayUpdatedStat(x, y, 10, 15);

	//y++;
	//menu->Con(STATE_04)->print(x, ++y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.ap);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.ap, stats.ap);
	y++;
	menu->Con(STATE_04)->print(x, ++y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 4);
	menu->DisplayUpdatedStat(x, y, 4, 6);

	//menu->Con(STATE_04)->print(x, ++y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.dp);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.dp, stats.dp);
	menu->Con(STATE_04)->print(x, ++y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 2);
	menu->DisplayUpdatedStat(x, y, 2, 1);

	//menu->Con(STATE_04)->print(x, ++y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.str);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.str, stats.str);
	menu->Con(STATE_04)->print(x, ++y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 10);
	menu->DisplayUpdatedStat(x, y, 10, 15);

	//menu->Con(STATE_04)->print(x, ++y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.spd);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.spd, stats.spd);
	menu->Con(STATE_04)->print(x, ++y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 12);
	menu->DisplayUpdatedStat(x, y, 12, 8);

	//menu->Con(STATE_04)->print(x, ++y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.map);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.map, stats.map);
	menu->Con(STATE_04)->print(x, ++y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 5);
	menu->DisplayUpdatedStat(x, y, 5, 4);

	//menu->Con(STATE_04)->print(x, ++y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.mdp);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.mdp, stats.mdp);
	menu->Con(STATE_04)->print(x, ++y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 2);
	menu->DisplayUpdatedStat(x, y, 2, 4);

	//menu->Con(STATE_04)->print(x, ++y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.wil);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.wil, stats.wil);
	menu->Con(STATE_04)->print(x, ++y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 6);
	menu->DisplayUpdatedStat(x, y, 6, 8);

	//menu->Con(STATE_04)->print(x, ++y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.acu);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.acu, stats.acu);
	menu->Con(STATE_04)->print(x, ++y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 3);
	menu->DisplayUpdatedStat(x, y, 3, 1);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuShieldInv::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2 - (NEQUIPTYPE + 6);
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3 + (NEQUIPTYPE + 6);

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuArmourInv
//
//------------------------------------------------------------------------
MenuArmourInv *MenuArmourInv::Instance()
{
	static MenuArmourInv instance;
	return &instance;
}

bool MenuArmourInv::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	static int cursor = 0;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2 - (NEQUIPTYPE + 6), NARMOUR = 9;

	// Game submenu screen
	menu->Con(STATE_04, new TCODConsole(ws, hs));

	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NARMOUR;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NARMOUR - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			// Exit Menu
			Transmit->Send(Engine(), MSG_ARMOURINV);
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			// Swap equipment
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_04)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_04)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_04)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_04)->clear();

	// Print frames
	menu->Con(STATE_04)->printFrame(0, 0, 18, hs, false, TCOD_BKGND_SET);
	menu->Con(STATE_04)->printFrame(18, 0, ws - 18, hs, false, TCOD_BKGND_SET);

	// Equipment
	int x = 2, y = 2;
	menu->Con(STATE_04)->print(x + 18, y, "%cArmour List%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	y += 2;

	// List Current Equipment
	//Stats stats = game.player.stats;
	for(int i = 0; i < NARMOUR; i++)
	{
		// Highlight Selection
		if(i == cursor)
		{
			//menu->Con(STATE_04)->print(x + 18, y++, game.player.equipInv.Armours[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_04)->print(x + 18, hs - 3, game.player.equipInv.Armours[j].desc);
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->ArmourNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x + 18, hs - 3, "DP +4");

			//stats -= game.player.equipInv.equiped[ARMOUR].stats;
			//stats.hpmax -= game.player.equipInv.equiped[ARMOUR].stats.hpmax;
			//stats.mpmax -= game.player.equipInv.equiped[ARMOUR].stats.mpmax;

			//stats += game.player.equipInv.Armours[j].stats;
			//stats.hpmax += game.player.equipInv.Armours[j].stats.hpmax;
			//stats.mpmax += game.player.equipInv.Armours[j].stats.mpmax;
		}
		else
		{
			//menu->Con(STATE_04)->print(x + 18, y++, game.player.equipInv.Armours[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->ArmourNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	// List Current Stats
	y = 2;
	menu->Con(STATE_04)->print(x, y, "%cStats%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->putChar(x + 8, y, CHAR_PLAYER_RIGHT, TCOD_BKGND_NONE);
	y += 2;

	//float xpfraction = static_cast<float>(game.player.xp)/static_cast<float>(game.player.xpnext);
	//int xpbar = static_cast<int>(14.0f*xpfraction);
	//if(xpbar > 0)
	//{
	//	menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkGreen);
	//	menu->Con(STATE_04)->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
	//}
	//if(xpbar < 14)
	//{
	//	menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkerGreen);
	//	menu->Con(STATE_04)->rect(x + xpbar, y + 1, 14 - xpbar, 1, true, TCOD_BKGND_SET);
	//}
	//menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	//menu->Con(STATE_04)->print(x, y, "%cLVL%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y++, "%2d", game.player.lvl);
	//menu->Con(STATE_04)->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", game.player.xp, game.player.xpnext);
	float xpfraction = static_cast<float>(0)/static_cast<float>(100);
	int xpbar = static_cast<int>(14.0f*xpfraction);
	if(xpbar > 0)
	{
		menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkGreen);
		menu->Con(STATE_04)->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
	}
	if(xpbar < 14)
	{
		menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkerGreen);
		menu->Con(STATE_04)->rect(x + xpbar, y + 1, 14 - xpbar, 1, true, TCOD_BKGND_SET);
	}
	menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_04)->print(x, y, "%cLVL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y++, "%2d", 1);
	menu->Con(STATE_04)->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", 0, 100);

	//y++;
	//menu->Con(STATE_04)->print(x, y, "%cHPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.hpmax);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.hpmax, stats.hpmax);
	y++;
	menu->Con(STATE_04)->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 20);
	menu->DisplayUpdatedStat(x, y, 20, 30);

	//menu->Con(STATE_04)->print(x, ++y, "%cMPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.mpmax);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.mpmax, stats.mpmax);
	menu->Con(STATE_04)->print(x, ++y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 10);
	menu->DisplayUpdatedStat(x, y, 10, 15);

	//y++;
	//menu->Con(STATE_04)->print(x, ++y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.ap);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.ap, stats.ap);
	y++;
	menu->Con(STATE_04)->print(x, ++y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 4);
	menu->DisplayUpdatedStat(x, y, 4, 6);

	//menu->Con(STATE_04)->print(x, ++y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.dp);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.dp, stats.dp);
	menu->Con(STATE_04)->print(x, ++y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 2);
	menu->DisplayUpdatedStat(x, y, 2, 1);

	//menu->Con(STATE_04)->print(x, ++y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.str);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.str, stats.str);
	menu->Con(STATE_04)->print(x, ++y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 10);
	menu->DisplayUpdatedStat(x, y, 10, 15);

	//menu->Con(STATE_04)->print(x, ++y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.spd);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.spd, stats.spd);
	menu->Con(STATE_04)->print(x, ++y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 12);
	menu->DisplayUpdatedStat(x, y, 12, 8);

	//menu->Con(STATE_04)->print(x, ++y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.map);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.map, stats.map);
	menu->Con(STATE_04)->print(x, ++y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 5);
	menu->DisplayUpdatedStat(x, y, 5, 4);

	//menu->Con(STATE_04)->print(x, ++y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.mdp);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.mdp, stats.mdp);
	menu->Con(STATE_04)->print(x, ++y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 2);
	menu->DisplayUpdatedStat(x, y, 2, 4);

	//menu->Con(STATE_04)->print(x, ++y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.wil);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.wil, stats.wil);
	menu->Con(STATE_04)->print(x, ++y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 6);
	menu->DisplayUpdatedStat(x, y, 6, 8);

	//menu->Con(STATE_04)->print(x, ++y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.acu);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.acu, stats.acu);
	menu->Con(STATE_04)->print(x, ++y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 3);
	menu->DisplayUpdatedStat(x, y, 3, 1);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuArmourInv::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2 - (NEQUIPTYPE + 6);
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3 + (NEQUIPTYPE + 6);

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuAccessoryInv
//
//------------------------------------------------------------------------
MenuAccessoryInv *MenuAccessoryInv::Instance()
{
	static MenuAccessoryInv instance;
	return &instance;
}

bool MenuAccessoryInv::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	static int cursor = 0;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2 - (NEQUIPTYPE + 6), NACCESSORY = 9;

	// Game submenu screen
	menu->Con(STATE_04, new TCODConsole(ws, hs));

	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NACCESSORY;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NACCESSORY - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			// Exit Menu
			Transmit->Send(Engine(), MSG_ACCESSORYINV);
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			// Swap equipment
			//Engine()->Player()->UseEquip(ACCESSORY, &cursor)
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_04)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_04)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_04)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_04)->clear();

	// Print frames
	menu->Con(STATE_04)->printFrame(0, 0, 18, hs, false, TCOD_BKGND_SET);
	menu->Con(STATE_04)->printFrame(18, 0, ws - 18, hs, false, TCOD_BKGND_SET);

	// Equipment
	int x = 2, y = 2;
	menu->Con(STATE_04)->print(x + 18, y, "%cAccessory List%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	y += 2;

	// List Current Equipment
	//Stats stats = game.player.stats;
	for(int i = 0; i < NACCESSORY; i++)
	{
		// Highlight Selection
		if(i == cursor)
		{
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->AccessoryNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_04)->print(x + 18, hs - 3, game.player.equipInv.Accessory[j].desc);
			menu->Con(STATE_04)->print(x + 18, hs - 3, "MAP +4");

			//stats -= game.player.equipInv.equiped[ACCESSORY].stats;
			//stats.hpmax -= game.player.equipInv.equiped[ACCESSORY].stats.hpmax;
			//stats.mpmax -= game.player.equipInv.equiped[ACCESSORY].stats.mpmax;

			//stats += game.player.equipInv.Accessory[j].stats;
			//stats.hpmax += game.player.equipInv.Accessory[j].stats.hpmax;
			//stats.mpmax += game.player.equipInv.Accessory[j].stats.mpmax;
		}
		else
		{
			//menu->Con(STATE_04)->print(x + 18, y++, game.player.equipInv.Accessory[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->AccessoryNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	// List Current Stats
	y = 2;
	menu->Con(STATE_04)->print(x, y, "%cStats%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->putChar(x + 8, y, CHAR_PLAYER_RIGHT, TCOD_BKGND_NONE);
	y += 2;

	//float xpfraction = static_cast<float>(game.player.xp)/static_cast<float>(game.player.xpnext);
	//int xpbar = static_cast<int>(14.0f*xpfraction);
	//if(xpbar > 0)
	//{
	//	menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkGreen);
	//	menu->Con(STATE_04)->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
	//}
	//if(xpbar < 14)
	//{
	//	menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkerGreen);
	//	menu->Con(STATE_04)->rect(x + xpbar, y + 1, 14 - xpbar, 1, true, TCOD_BKGND_SET);
	//}
	//menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	//menu->Con(STATE_04)->print(x, y, "%cLVL%c  : ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y++, "%2d", game.player.lvl);
	//menu->Con(STATE_04)->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", game.player.xp, game.player.xpnext);
	float xpfraction = static_cast<float>(0)/static_cast<float>(100);
	int xpbar = static_cast<int>(14.0f*xpfraction);
	if(xpbar > 0)
	{
		menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkGreen);
		menu->Con(STATE_04)->rect(x, y + 1, xpbar, 1, true, TCOD_BKGND_SET);
	}
	if(xpbar < 14)
	{
		menu->Con(STATE_04)->setDefaultBackground(TCODColor::darkerGreen);
		menu->Con(STATE_04)->rect(x + xpbar, y + 1, 14 - xpbar, 1, true, TCOD_BKGND_SET);
	}
	menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_04)->print(x, y, "%cLVL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y++, "%2d", 1);
	menu->Con(STATE_04)->printEx(x + 7, y, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", 0, 100);

	//y++;
	//menu->Con(STATE_04)->print(x, y, "%cHPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.hpmax);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.hpmax, stats.hpmax);
	y++;
	menu->Con(STATE_04)->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 20);
	menu->DisplayUpdatedStat(x, y, 20, 30);

	//menu->Con(STATE_04)->print(x, ++y, "%cMPMAX%c: ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.mpmax);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.mpmax, stats.mpmax);
	menu->Con(STATE_04)->print(x, ++y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 10);
	menu->DisplayUpdatedStat(x, y, 10, 15);

	//y++;
	//menu->Con(STATE_04)->print(x, ++y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.ap);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.ap, stats.ap);
	y++;
	menu->Con(STATE_04)->print(x, ++y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 4);
	menu->DisplayUpdatedStat(x, y, 4, 6);

	//menu->Con(STATE_04)->print(x, ++y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.dp);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.dp, stats.dp);
	menu->Con(STATE_04)->print(x, ++y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 2);
	menu->DisplayUpdatedStat(x, y, 2, 1);

	//menu->Con(STATE_04)->print(x, ++y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.str);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.str, stats.str);
	menu->Con(STATE_04)->print(x, ++y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 10);
	menu->DisplayUpdatedStat(x, y, 10, 15);

	//menu->Con(STATE_04)->print(x, ++y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.spd);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.spd, stats.spd);
	menu->Con(STATE_04)->print(x, ++y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 12);
	menu->DisplayUpdatedStat(x, y, 12, 8);

	//menu->Con(STATE_04)->print(x, ++y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.map);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.map, stats.map);
	menu->Con(STATE_04)->print(x, ++y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 5);
	menu->DisplayUpdatedStat(x, y, 5, 4);

	//menu->Con(STATE_04)->print(x, ++y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.mdp);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.mdp, stats.mdp);
	menu->Con(STATE_04)->print(x, ++y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 2);
	menu->DisplayUpdatedStat(x, y, 2, 4);

	//menu->Con(STATE_04)->print(x, ++y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.wil);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.wil, stats.wil);
	menu->Con(STATE_04)->print(x, ++y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 6);
	menu->DisplayUpdatedStat(x, y, 6, 8);

	//menu->Con(STATE_04)->print(x, ++y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_04)->print(x + 7, y, "%2d", game.player.stats.acu);
	//menu->DisplayUpdatedStat(x, y, game.player.stats.acu, stats.acu);
	menu->Con(STATE_04)->print(x, ++y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_04)->print(x + 7, y, "%2d", 3);
	menu->DisplayUpdatedStat(x, y, 3, 1);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuAccessoryInv::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2 - (NEQUIPTYPE + 6);
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3 + (NEQUIPTYPE + 6);

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuItemInv
//
//------------------------------------------------------------------------
MenuItemInv *MenuItemInv::Instance()
{
	static MenuItemInv instance;
	return &instance;
}

bool MenuItemInv::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	static int cursor = 0;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int NITEMS = 10, NHIDES = 6;
  int yend = NITEMS + 5;

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NITEMS;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NITEMS - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			// Exit Menu
			Transmit->Send(Engine(), MSG_ITEMINV);
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			// Use Item
			//Engine()->Player()->UseItem(&cursor);
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set colours for submenu
	menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_03)->clear();

	// Print frames
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs - (NHIDES + 6), false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, hs - (NHIDES + 6), ws, NHIDES + 6, false, TCOD_BKGND_SET);

	// Items
	int x = 2, y = 2;
	menu->Con(STATE_03)->print(x, y, "%cItems%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 27, y++, "%cQty%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

	//for(int i = 0; i < game.player.itemInv.nitems; i++)
	for(int i = 0; i < NITEMS; i++)
	{
		//int j = game.player.itemInv.index[i];
		if(i == cursor)
		{
			//menu->Con(STATE_03)->print(x, ++y, game.player.itemInv.items[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 24, y, " : %2d", game.player.itemInv.count[j]);
			//menu->Con(STATE_03)->print(x, yend, game.player.itemInv.items[j].desc);
			menu->Con(STATE_03)->print(x, ++y, "%cRare Item%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x + 24, y, " : %2d", 2);
			menu->Con(STATE_03)->print(x, yend, "Very Rare");
		}
		else
		{
			//menu->Con(STATE_03)->print(x, ++y, game.player.itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 24, y, " : %2d", game.player.itemInv.count[j]);
			menu->Con(STATE_03)->print(x, ++y, "%cRare Item%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x + 24, y, " : %2d", 2);
		}
	}

	// Hide Invetory
	y = DISPLAY_HEIGHT/2 - 2;
	menu->Con(STATE_03)->print(x, y, "%cHides%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 27, y++, "%cQty%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

	//for(int i = 0; i < game.player.hideInv.nhides; i++)
	for(int i = 0; i < NHIDES; i++)
	{
		//int j = game.player.hideInv.index[i];
		//menu->Con(STATE_03)->print(x, ++y, game.player.hideInv.hides[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		//menu->Con(STATE_03)->print(x + 24, y, " : %2d", game.player.hideInv.count[j]);
		menu->Con(STATE_03)->print(x, ++y, "%cRare Hide%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		menu->Con(STATE_03)->print(x + 24, y, " : %2d", 3);
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuItemInv::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuGuardian
//
//------------------------------------------------------------------------
MenuGuardian *MenuGuardian::Instance()
{
	static MenuGuardian instance;
	return &instance;
}

bool MenuGuardian::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void MenuGuardian::Render(MenuClass *menu){}

//------------------------------------------------------------------------
//
// Methods for MenuNpc
//
//------------------------------------------------------------------------
MenuNpc *MenuNpc::Instance()
{
	static MenuNpc instance;
	return &instance;
}

bool MenuNpc::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void MenuNpc::Render(MenuClass *menu){}

//------------------------------------------------------------------------
//
// Methods for MenuItemShop
//
//------------------------------------------------------------------------
MenuItemShop *MenuItemShop::Instance()
{
	static MenuItemShop instance;
	return &instance;
}

bool MenuItemShop::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2, i = 0;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = hs - 6;
	int NITEMS = 10, NHIDES = 6;

	map<int, string> Options;
	Options.insert(make_pair(i++, "%cBuy Items %c"));
	Options.insert(make_pair(i++, "%cSell Items%c"));
	Options.insert(make_pair(i++, "%cExit Shop %c"));

	// Game menu screen
	menu->Con(STATE_02, new TCODConsole(w, h));

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

	//int id = game.worldID - 1;
	//WorldMap *wmap = &game.world[0];

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NITEMSHOP;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NITEMSHOP - 1;
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			switch(cursor)
			{
				case ITEMSHOP_BUY:
				{
					// Buy Something!
					Transmit->Send(Engine(), MSG_ITEMSHOPMENUBUY);
					break;
				}
				case ITEMSHOP_SELL:
				{
					// Got anything I can take off your hands?
					Transmit->Send(Engine(), MSG_ITEMSHOPMENUSELL);
					break;
				}
				case ITEMSHOP_EXIT:
				{
					// Exit Menu
					//Engine()->Sound()->ToggleVolume(0.5f);
					Transmit->Send(Engine(), MSG_ITEMSHOPMENU);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_02)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_02)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_02)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_02)->clear();

	// Set default colours for console
	menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_03)->clear();

	// Print frame and title
	menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Item Shop");
	menu->Con(STATE_02)->printFrame(1, 1, 15, 2*NITEMSHOP + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 2*NITEMSHOP + 4, 15, h - 11, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs - (NHIDES + 6), false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, hs - (NHIDES + 6), ws, NHIDES + 6, false, TCOD_BKGND_SET);

	// Compute the elapsed time in convenient units
	int nhours = static_cast<int>(Engine()->ElapsedTime()/(60.0f*60.0f));
	float time = Engine()->ElapsedTime() - (60.0f*60.0f)*static_cast<float>(nhours);
	int nmins = static_cast<int>(time/60.0f);
	int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

	int x = 3, y = 24;
	menu->Con(STATE_02)->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_02)->print(x + 4, y++, "%d", Engine()->Player()->GP());
	menu->Con(STATE_02)->print(x + 4, y++, "%d", 100);
	y++;

	menu->Con(STATE_02)->print(x, y, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_02)->print(x, ++y, "%02d:%02d:%02d", nhours, nmins, nsecs);

	// Print the menu options
	y = NITEMSHOP - 2;
	for(int i = 0; i < NITEMSHOP; i++)
	{
		y += 2;
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			switch(cursor)
			{
				case ITEMSHOP_BUY:
				{
					// Items
					int xb = 2, yb = 2;
					menu->Con(STATE_03)->print(xb, yb, "%cItems%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xb + 27, yb++, "%cQty GP%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

					//for(int i = 0; i < wmap->locations[id].itemInv.nitems; i++)
					for(int i = 0; i < NITEMS; i++)
					{
						//int j = wmap->locations[id].itemInv.index[i];
						//menu->Con(STATE_03)->print(xb, ++yb, wmap->locations[id].itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xb + 24, yb, " : %2d", wmap->locations[id].itemInv.count[j]);
						//menu->Con(STATE_03)->print(xb + 30, yb, " %3d", wmap->locations[id].itemInv.price[j]);
						menu->Con(STATE_03)->print(xb, ++yb, "%cRare Item%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						menu->Con(STATE_03)->print(xb + 24, yb, " : %2d", 2);
						menu->Con(STATE_03)->print(xb + 29, yb, " %3d", 20);
					}
					break;
				}
				case ITEMSHOP_SELL:
				{
					// Items
					int xs = 2, ys = 2;
					menu->Con(STATE_03)->print(xs, ys, "%cItems%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xs + 27, ys++, "%cQty GP%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

					//for(int i = 0; i < game.player.itemInv.nitems; i++)
					for(int i = 0; i < NITEMS; i++)
					{
						//int j = game.player.itemInv.index[i];
						//menu->Con(STATE_03)->print(xs, ++ys, game.player.itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xs + 24, ys, " : %2d", game.player.itemInv.count[j]);
						//menu->Con(STATE_03)->print(xs + 30, ys, " %3d", MAX(1, wmap->locations[id].itemInv.price[j]/2));
						menu->Con(STATE_03)->print(xs, ++ys, "%cRare Item%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						menu->Con(STATE_03)->print(xs + 24, ys, " : %2d", 2);
						menu->Con(STATE_03)->print(xs + 29, ys, " %3d", 10);
					}

					// Hide Invetory
					ys = DISPLAY_HEIGHT/2 - 2;
					menu->Con(STATE_03)->print(xs, ys, "%cHides%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xs + 27, ys++, "%cQty GP%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

					//for(int i = 0; i < game.player.hideInv.nhides; i++)
					for(int i = 0; i < NHIDES; i++)
					{
						//int j = game.player.hideInv.index[i];
						//menu->Con(STATE_03)->print(xs, ++ys, game.player.hideInv.hides[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xs + 24, ys, " : %2d", game.player.hideInv.count[j]);
						//menu->Con(STATE_03)->print(xs + 30, ys, " %3d", MAX(1, wmap->locations[id].hideInv.price[j]));
						menu->Con(STATE_03)->print(xs, ++ys, "%cRare Hide%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						menu->Con(STATE_03)->print(xs + 24, ys, " : %2d", 3);
						menu->Con(STATE_03)->print(xs + 29, ys, " %3d", 5);
					}
					break;
				}
				case ITEMSHOP_EXIT:
				{
					// Hurry Back!
					menu->Con(STATE_03)->clear();
					menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);
					menu->Con(STATE_03)->printRect(xstart, ystart, xend, yend, "Come back any time.");
					break;
				}
				default: break;
			}
		}
		else
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	if(cursor == ITEMSHOP_EXIT && key.vk == TCODK_ENTER) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuItemShop::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuItemShopBuy
//
//------------------------------------------------------------------------
MenuItemShopBuy *MenuItemShopBuy::Instance()
{
	static MenuItemShopBuy instance;
	return &instance;
}

bool MenuItemShopBuy::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int NITEMS = 10, NHIDES = 6;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = NITEMS + 5;

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

	//int id = game.worldID - 1;
	//WorldMap *wmap = &game.world[0];

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			//cursor = (cursor + 1) % MAX(1, wmap->locations[id].itemInv.nitems);
			cursor = (cursor + 1) % MAX(1, NITEMS);
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			//if(cursor < 0) cursor = MAX(0, wmap->locations[id].itemInv.nitems - 1);
			if(cursor < 0) cursor = MAX(0, NITEMS - 1);
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_ITEMSHOPMENUBUY);
			break;
		}
		case TCODK_ENTER:
		{
			//Engine()->Player()->BuyItem(&cursor);
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_03)->clear();

	// Print frame and title
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs - (NHIDES + 6), false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, hs - (NHIDES + 6), ws, NHIDES + 6, false, TCOD_BKGND_SET);

	// Items
	int x = 2, y = 2;
	menu->Con(STATE_03)->print(x, y, "%cItems%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 27, y++, "%cQty GP%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

	//for(int i = 0; i < wmap->locations[id].itemInv.nitems; i++)
	for(int i = 0; i < NITEMS; i++)
	{
		//int j = wmap->locations[id].itemInv.index[i];
		if(i == cursor)
		{
			//menu->Con(STATE_03)->print(x, ++y, wmap->locations[id].itemInv.items[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x, yend, wmap->locations[id].itemInv.items[j].desc);
			menu->Con(STATE_03)->print(x, ++y, "%cRare Item%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, yend, "Very Rare");
		}
		else
		{
			//menu->Con(STATE_03)->print(x, ++y, wmap->locations[id].itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, ++y, "%cRare Item%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		//menu->Con(STATE_03)->print(x + 24, y, " : %2d", wmap->locations[id].itemInv.count[j]);
		//menu->Con(STATE_03)->print(x + 29, y, " %3d", wmap->locations[id].itemInv.price[j]);
		menu->Con(STATE_03)->print(x + 24, y, " : %2d", 2);
		menu->Con(STATE_03)->print(x + 29, y, " %3d", 20);
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuItemShopBuy::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuItemShopSell
//
//------------------------------------------------------------------------
MenuItemShopSell *MenuItemShopSell::Instance()
{
	static MenuItemShopSell instance;
	return &instance;
}

bool MenuItemShopSell::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int NITEMS = 10, NHIDES = 6;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = NITEMS + 5;

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

	//int id = game.worldID - 1;
	//WorldMap *wmap = &game.world[0];

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			//cursor = (cursor + 1) % MAX(1, game.player.itemInv.nitems + game.player.hideInv.nhides);
			cursor = (cursor + 1) % MAX(1, NITEMS + NHIDES);
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			//if(cursor < 0) cursor = MAX(0, game.player.itemInv.nitems + game.player.hideInv.nhides - 1);
			if(cursor < 0) cursor = MAX(0, NITEMS + NHIDES - 1);
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_ITEMSHOPMENUSELL);
			break;
		}
		case TCODK_ENTER:
		{
			//if(cursor < Engine()->Player()->ItemInv()->Nitems)
			//{
			//	Engine()->Player()->SellItem(&cursor);
			//}
			//else
			//{
			//	Engine()->Player()->SellHide(&cursor);
			//}
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_03)->clear();

	// Print frame and title
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs - (NHIDES + 6), false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, hs - (NHIDES + 6), ws, NHIDES + 6, false, TCOD_BKGND_SET);

	// Items
	int x = 2, y = 2;
	menu->Con(STATE_03)->print(x, y, "%cItems%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 27, y++, "%cQty GP%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

	//for(int i = 0; i < wmap->locations[id].itemInv.nitems; i++)
	for(int i = 0; i < NITEMS; i++)
	{
		//int j = wmap->locations[id].itemInv.index[i];
		if(i == cursor)
		{
			//menu->Con(STATE_03)->print(x, ++y, game.player.itemInv.items[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x, yend, game.player.itemInv.items[j].desc);
			menu->Con(STATE_03)->print(x, ++y, "%cRare Item%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, yend, "Very Rare");
		}
		else
		{
			//menu->Con(STATE_03)->print(x, ++y, game.player.itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, ++y, "%cRare Item%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		//menu->Con(STATE_03)->print(x + 24, y, " : %2d", game.player.itemInv.count[j]);
		//menu->Con(STATE_03)->print(x + 29, y, " %3d", MAX(1, wmap->locations[id].itemInv.price[j]/2));
		menu->Con(STATE_03)->print(x + 24, y, " : %2d", 2);
		menu->Con(STATE_03)->print(x + 29, y, " %3d", 20);
	}

	y = DISPLAY_HEIGHT/2 - 2;
	menu->Con(STATE_03)->print(x, y, "%cHides%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x + 27, y++, "%cQty GP%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

	//for(int i = 0; i < game.player.hideInv.nhides; i++)
	for(int i = 0; i < NHIDES; i++)
	{
		//int j = game.player.hideInv.index[i];
		//if(i == cursor - game.player.itemInv.nitems)
		if(i == cursor - NITEMS)
		{
			//menu->Con(STATE_03)->print(x, ++y, game.player.hideInv.hides[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, ++y, "%cRare Hide%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
		}
		else
		{
			//menu->Con(STATE_03)->print(x, ++y, game.player.hideInv.hides[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, ++y, "%cRare Hide%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		//menu->Con(STATE_03)->print(x + 24, y, " : %2d", game.player.hideInv.count[j]);
		//menu->Con(STATE_03)->print(x + 29, y, " %3d", MAX(1, wmap->locations[id].hideInv.price[j]));
		menu->Con(STATE_03)->print(x + 24, y, " : %2d", 3);
		menu->Con(STATE_03)->print(x + 29, y, " %3d", 5);
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuItemShopSell::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	//TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuEquipShop
//
//------------------------------------------------------------------------
MenuEquipShop *MenuEquipShop::Instance()
{
	static MenuEquipShop instance;
	return &instance;
}

bool MenuEquipShop::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2, i = 0, j = 0;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = hs - 6;
	map<int, string> Options, SubOptions;
	Options.insert(make_pair(i++, "%cBuy Equip %c"));
	Options.insert(make_pair(i++, "%cSell Equip%c"));
	Options.insert(make_pair(i++, "%cExit Shop %c"));
	SubOptions.insert(make_pair(j++, "%cWeapon%c"));
	SubOptions.insert(make_pair(j++, "%cShield%c"));
	SubOptions.insert(make_pair(j++, "%cArmour%c"));
	SubOptions.insert(make_pair(j++, "%cAccessory%c"));

	// Game menu screen
	menu->Con(STATE_02, new TCODConsole(w, h));

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

	//int id = game.worldID - 1;
	//WorldMap *wmap = &game.world[0];

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NEQUIPSHOP;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NEQUIPSHOP - 1;
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			switch(cursor)
			{
				case EQUIPSHOP_BUY:
				{
					// Buy Something!
					Transmit->Send(Engine(), MSG_EQUIPSHOPMENUBUY);
					break;
				}
				case EQUIPSHOP_SELL:
				{
					// Got anything I can take off your hands?
					Transmit->Send(Engine(), MSG_EQUIPSHOPMENUSELL);
					break;
				}
				case EQUIPSHOP_EXIT:
				{
					// Exit Menu
					//Engine()->Sound()->ToggleVolume(0.5f);
					Transmit->Send(Engine(), MSG_EQUIPSHOPMENU);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_02)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_02)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_02)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_02)->clear();

	// Set default colours for console
	menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_03)->clear();

	// Print frame and title
	menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Equip Shop");
	menu->Con(STATE_02)->printFrame(1, 1, 15, 2*NEQUIPSHOP + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 2*NEQUIPSHOP + 4, 15, h - 11, false, TCOD_BKGND_SET);

	menu->Con(STATE_03)->printFrame(0, 0, ws, 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 5, ws, hs/3 + 1 + 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 2*hs/3 + 1, ws, hs/3, false, TCOD_BKGND_SET);

	// Compute the elapsed time in convenient units
	int nhours = static_cast<int>(Engine()->ElapsedTime()/(60.0f*60.0f));
	float time = Engine()->ElapsedTime() - (60.0f*60.0f)*static_cast<float>(nhours);
	int nmins = static_cast<int>(time/60.0f);
	int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

	int x = 3, y = 24;
	menu->Con(STATE_02)->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_02)->print(x + 4, y++, "%d", Engine()->Player()->GP());
	menu->Con(STATE_02)->print(x + 4, y++, "%d", 100);
	y++;

	menu->Con(STATE_02)->print(x, y, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_02)->print(x, ++y, "%02d:%02d:%02d", nhours, nmins, nsecs);

	// Print the menu options
	y = NEQUIPSHOP - 2;
	for(int i = 0; i < NEQUIPSHOP; i++)
	{
		y += 2;
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			switch(cursor)
			{
				case EQUIPSHOP_BUY:
				{
					// List Equipment Types
					int xb = 2, yb = 2;
					for(int i = 0; i < NEQUIPTYPE; i++)
					{
						menu->Con(STATE_03)->print(xb, yb, SubOptions[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						xb += 8;
					}
					break;
				}
				case EQUIPSHOP_SELL:
				{
					// List Equipment Types
					int xb = 2, yb = 2;
					for(int i = 0; i < NEQUIPTYPE; i++)
					{
						menu->Con(STATE_03)->print(xb, yb, SubOptions[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						xb += 8;
					}
					break;
				}
				case EQUIPSHOP_EXIT:
				{
					// Hurry Back!
					menu->Con(STATE_03)->clear();
					menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);
					menu->Con(STATE_03)->printRect(xstart, ystart, xend, yend, "Come back any time.");
					break;
				}
				default: break;
			}
		}
		else
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	if(cursor == EQUIPSHOP_EXIT && key.vk == TCODK_ENTER) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipShop::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuEquipShopBuy
//
//------------------------------------------------------------------------
MenuEquipShopBuy *MenuEquipShopBuy::Instance()
{
	static MenuEquipShopBuy instance;
	return &instance;
}

bool MenuEquipShopBuy::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2, i = 0;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = hs - 6;
	map<int, string> Options;
	Options.insert(make_pair(i++, "%cWeapon%c"));
	Options.insert(make_pair(i++, "%cShield%c"));
	Options.insert(make_pair(i++, "%cArmour%c"));
	Options.insert(make_pair(i++, "%cAccessory%c"));

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

	// Game submenu screen
	//menu->Con(STATE_04, new TCODConsole(ws, hs));

	//int id = game.worldID - 1;
	//WorldMap *wmap = &game.world[0];

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NEQUIPTYPE;
			break;
		}
		case TCODK_RIGHT:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NEQUIPTYPE;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NEQUIPTYPE - 1;
			break;
		}
		case TCODK_LEFT:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NEQUIPTYPE - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_EQUIPSHOPMENUBUY);
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			//Engine()->Player()->BuyEquip(&cursor);
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_03)->clear();

	// Set default colours for console
	//menu->Con(STATE_04)->setAlignment(TCOD_LEFT);
	//menu->Con(STATE_04)->setBackgroundFlag(TCOD_BKGND_SET);
	//menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	//menu->Con(STATE_04)->setDefaultForeground(TCODColor::white);
	//menu->Con(STATE_04)->clear();

	// Print frame and title
	menu->Con(STATE_03)->printFrame(0, 0, ws, 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 5, ws, hs/3 + 1 + 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 2*hs/3 + 1, ws, hs/3, false, TCOD_BKGND_SET);

	// Print the menu options
	int x = 2, y = 2;
	for(int i = 0; i < NEQUIPTYPE; i++)
	{
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_03)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			y += 5;

			switch(cursor)
			{
				case WEAPON:
				{
					for(int j = 0; j < 9; j++)
					{
						menu->Con(STATE_03)->print(2, y, Engine()->Map()->WeaponNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						y++;
					}
					break;
				}
				case SHIELD:
				{
					for(int j = 0; j < 9; j++)
					{
						menu->Con(STATE_03)->print(2, y, Engine()->Map()->ShieldNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						y++;
					}
					break;
				}
				case ARMOUR:
				{
					for(int j = 0; j < 9; j++)
					{
						menu->Con(STATE_03)->print(2, y, Engine()->Map()->ArmourNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						y++;
					}
					break;
				}
				case ACCESSORY:
				{
					for(int j = 0; j < 9; j++)
					{
						menu->Con(STATE_03)->print(2, y, Engine()->Map()->AccessoryNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						y++;
					}
					break;
				}
				default: break;
			}

			int xb = 2, yb = 2*hs/3 + 1 + 2;
			menu->Con(STATE_03)->print(xb, yb, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.hpmax);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 20);

			menu->Con(STATE_03)->print(xb, yb, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.ap);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 4);
			menu->Con(STATE_03)->print(xb, yb, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.dp);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 2);

			menu->Con(STATE_03)->print(xb, yb, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.str);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 10);
			menu->Con(STATE_03)->print(xb, yb, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.spd);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 12);

			xb += 18; yb = 2*hs/3 + 1 + 2;
			menu->Con(STATE_03)->print(xb, yb, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.mpmax);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 10);

			menu->Con(STATE_03)->print(xb, yb, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.map);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 5);
			menu->Con(STATE_03)->print(xb, yb, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.mdp);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 2);

			menu->Con(STATE_03)->print(xb, yb, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.wil);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 6);
			menu->Con(STATE_03)->print(xb, yb, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.acu);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 3);
		}
		else
		{
			// Print each item
			menu->Con(STATE_03)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		x += 8; y = 2;
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipShopBuy::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	//TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuEquipShopSell
//
//------------------------------------------------------------------------
MenuEquipShopSell *MenuEquipShopSell::Instance()
{
	static MenuEquipShopSell instance;
	return &instance;
}

bool MenuEquipShopSell::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2, i = 0;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = hs - 6;
	map<int, string> Options;
	Options.insert(make_pair(i++, "%cWeapon%c"));
	Options.insert(make_pair(i++, "%cShield%c"));
	Options.insert(make_pair(i++, "%cArmour%c"));
	Options.insert(make_pair(i++, "%cAccessory%c"));

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

	// Game submenu screen
	//menu->Con(STATE_04, new TCODConsole(ws, hs));

	//int id = game.worldID - 1;
	//WorldMap *wmap = &game.world[0];

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NEQUIPTYPE;
			break;
		}
		case TCODK_RIGHT:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NEQUIPTYPE;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NEQUIPTYPE - 1;
			break;
		}
		case TCODK_LEFT:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NEQUIPTYPE - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_EQUIPSHOPMENUSELL);
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			//Engine()->Player()->SellEquip(&cursor);
			break;
		}
		default: break;
	}

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_03)->clear();

	// Set default colours for console
	//menu->Con(STATE_04)->setAlignment(TCOD_LEFT);
	//menu->Con(STATE_04)->setBackgroundFlag(TCOD_BKGND_SET);
	//menu->Con(STATE_04)->setDefaultBackground(TCODColor::black);
	//menu->Con(STATE_04)->setDefaultForeground(TCODColor::white);
	//menu->Con(STATE_04)->clear();

	// Print frame and title
	menu->Con(STATE_03)->printFrame(0, 0, ws, 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 5, ws, hs/3 + 1 + 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 2*hs/3 + 1, ws, hs/3, false, TCOD_BKGND_SET);

	// Print the menu options
	int x = 2, y = 2;
	for(int i = 0; i < NEQUIPTYPE; i++)
	{
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_03)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			y += 5;

			switch(cursor)
			{
				case WEAPON:
				{
					for(int j = 0; j < 9; j++)
					{
						menu->Con(STATE_03)->print(2, y, Engine()->Map()->WeaponNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						y++;
					}
					break;
				}
				case SHIELD:
				{
					for(int j = 0; j < 9; j++)
					{
						menu->Con(STATE_03)->print(2, y, Engine()->Map()->ShieldNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						y++;
					}
					break;
				}
				case ARMOUR:
				{
					for(int j = 0; j < 9; j++)
					{
						menu->Con(STATE_03)->print(2, y, Engine()->Map()->ArmourNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						y++;
					}
					break;
				}
				case ACCESSORY:
				{
					for(int j = 0; j < 9; j++)
					{
						menu->Con(STATE_03)->print(2, y, Engine()->Map()->AccessoryNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						y++;
					}
					break;
				}
				default: break;
			}

			int xb = 2, yb = 2*hs/3 + 1 + 2;
			menu->Con(STATE_03)->print(xb, yb, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.hpmax);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 20);

			menu->Con(STATE_03)->print(xb, yb, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.ap);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 4);
			menu->Con(STATE_03)->print(xb, yb, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.dp);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 2);

			menu->Con(STATE_03)->print(xb, yb, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.str);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 10);
			menu->Con(STATE_03)->print(xb, yb, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 7, y++, "%2d", game.player.stats.spd);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 12);

			xb += 18; yb = 2*hs/3 + 1 + 2;
			menu->Con(STATE_03)->print(xb, yb, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.mpmax);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 10);

			menu->Con(STATE_03)->print(xb, yb, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.map);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 5);
			menu->Con(STATE_03)->print(xb, yb, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.mdp);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 2);

			menu->Con(STATE_03)->print(xb, yb, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.wil);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 6);
			menu->Con(STATE_03)->print(xb, yb, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", game.player.stats.acu);
			menu->Con(STATE_03)->print(xb + 7, yb++, "%2d", 3);
		}
		else
		{
			// Print each item
			menu->Con(STATE_03)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		x += 8; y = 2;
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipShopSell::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	//TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuFerry
//
//------------------------------------------------------------------------
MenuFerry *MenuFerry::Instance()
{
	static MenuFerry instance;
	return &instance;
}

bool MenuFerry::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2, i = 0;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = hs - 6;
	//int id = game.worldID - 1, idprev = id - 1, idnext = id + 1;
	map<int, string> Options;
	Options.insert(make_pair(i++, "%cTake Ferry%c"));
	Options.insert(make_pair(i++, "%cExit Ferry%c"));

	//if(idprev < TOWN_01) idprev = TOWN_12;
	//if(idnext > TOWN_12) idnext = TOWN_01;

	//sprintf(options[0], "%s%s%s", "%c", wmap->locations[idprev].name, "%c");
	//sprintf(options[1], "%s%s%s", "%c", wmap->locations[idnext].name, "%c");

	// Game menu screen
	menu->Con(STATE_02, new TCODConsole(w, h));

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NFERRY;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NFERRY - 1;
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			// Select the item at the current cursor position
			if(cursor == FERRY_TAKE)
			{
				//if(Engine()->Player()->GP() >= 25)
				//{
				//	Engine()->Player()->DecreaseGP(25);
				//	Engine()->Player()->TakeFerry(idprev);
				//	Transmit->Send(Engine(), MSG_FERRYTAKE);
				//}
			}
			else
			{
				//Engine()->Sound()->ToggleVolume(0.5f);
				Transmit->Send(Engine(), MSG_FERRYMENU);
			}
			break;
		}
		default: break;
	}

	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);

	// Set colours for frame and title
	menu->Con(STATE_02)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_02)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_02)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_02)->clear();

	// Set colours for submenu
	menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_03)->clear();

	// Print frame and title
	menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Ferry");
	menu->Con(STATE_02)->printFrame(1, 1, 15, 2*NFERRY + 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 2*NFERRY + 6, 15, h - 11, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

	// Compute the elapsed time in convenient units
	int nhours = static_cast<int>(Engine()->ElapsedTime()/(60.0f*60.0f));
	float time = Engine()->ElapsedTime() - (60.0f*60.0f)*static_cast<float>(nhours);
	int nmins = static_cast<int>(time/60.0f);
	int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

	x = 3, y = 24;
	menu->Con(STATE_02)->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_02)->print(x + 4, y++, "%d", Engine()->Player()->GP());
	menu->Con(STATE_02)->print(x + 4, y++, "%d", 100);
	y++;

	menu->Con(STATE_02)->print(x, y, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_02)->print(x, ++y, "%02d:%02d:%02d", nhours, nmins, nsecs);

	// Print the menu options
	y = 1;
	for(int i = 0; i < NFERRY; i++)
	{
		y += 2;
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			if(cursor == FERRY_TAKE)
			{
				// Travel to the previous town
				menu->Con(STATE_03)->printRect(xstart, ystart, xend, yend, "Where are you headed?\n\n\nMy fee is %c25 GP%c per trip.", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			}
			else
			{
				// Hurry Back!
				menu->Con(STATE_03)->printRect(xstart, ystart, xend, yend, "Come back any time.");
			}
		}
		else
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	if(cursor == FERRY_EXIT && key.vk == TCODK_ENTER) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuFerry::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuInn
//
//------------------------------------------------------------------------
MenuInn *MenuInn::Instance()
{
	static MenuInn instance;
	return &instance;
}

bool MenuInn::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2, i = 0;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = hs - 6;
	map<int, string> Options;
	Options.insert(make_pair(i++, "%cStay at Inn%c"));
	Options.insert(make_pair(i++, "%cExit Inn   %c"));

	// Game menu screen
	menu->Con(STATE_02, new TCODConsole(w, h));

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NINN;
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NINN - 1;
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_ENTER:
		{
			// Select the item at the current cursor position
			if(cursor == INN_STAY)
			{
				//if(Engine()->Player()->GP() >= 15)
				//{
					// Goodnight
					menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);
					menu->Con(STATE_03)->printRect(xstart, ystart, xend, yend, "Goodnight.");

					// Blit the inn submenu to the root console
					TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);

					//Engine()->Player()->DecreaseGP(15);

					Transmit->Send(Engine(), MSG_REST);
				//}
			}
			else
			{
				//Engine()->Sound()->ToggleVolume(0.5f);
				Transmit->Send(Engine(), MSG_INNMENU);
			}
			break;
		}
		default: break;
	}

	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);

	// Set colours for frame and title
	menu->Con(STATE_02)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_02)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_02)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_02)->clear();

	// Set colours for submenu
	menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_03)->clear();

	// Print frame and title
	menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Inn");
	menu->Con(STATE_02)->printFrame(1, 1, 15, 2*(NINN + 1) + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 2*(NINN + 1) + 4, 15, h - 11, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

	// Compute the elapsed time in convenient units
	int nhours = static_cast<int>(Engine()->ElapsedTime()/(60.0f*60.0f));
	float time = Engine()->ElapsedTime() - (60.0f*60.0f)*static_cast<float>(nhours);
	int nmins = static_cast<int>(time/60.0f);
	int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

	x = 3, y = 24;
	menu->Con(STATE_02)->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_02)->print(x + 4, y++, "%d", Engine()->Player()->GP());
	menu->Con(STATE_02)->print(x + 4, y++, "%d", 100);
	y++;

	menu->Con(STATE_02)->print(x, y, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	menu->Con(STATE_02)->print(x, ++y, "%02d:%02d:%02d", nhours, nmins, nsecs);

	// Print the menu options
	y = NINN - 1;
	for(int i = 0; i < NINN; i++)
	{
		y += 2;
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			if(cursor == INN_STAY)
			{
				// Stay Night at Inn
				menu->Con(STATE_03)->printRect(xstart, ystart, xend, yend, "Hello there young traveller.\n\n\nCan I interest you in a nice hearty meal, and a warm comfortable bed?\n\n\nWe charge %c15 GP%c per night, meal included.\n\n\nWould you care to stay?", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			}
			else
			{
				// Hurry Back!
				menu->Con(STATE_03)->printRect(xstart, ystart, xend, yend, "It is a shame to see you leave.\n\n\nPlease hurry back!");
			}
		}
		else
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	if(cursor == INN_EXIT && key.vk == TCODK_ENTER) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuInn::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 17, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuRest
//
//------------------------------------------------------------------------
MenuRest *MenuRest::Instance()
{
	static MenuRest instance;
	return &instance;
}

bool MenuRest::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void MenuRest::Render(MenuClass *menu){}

//------------------------------------------------------------------------
//
// Methods for MenuDeath
//
//------------------------------------------------------------------------
MenuDeath *MenuDeath::Instance()
{
	static MenuDeath instance;
	return &instance;
}

bool MenuDeath::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int xstart = 4, ystart = 9, xend = w - 8, yend = h - 4;

	// The death message screen
	menu->Con(STATE_02, new TCODConsole(w, h));

	switch(key.vk)
	{
		case TCODK_ENTER:
		{
			Transmit->Send(Engine(), MSG_DEATH);
			status = false;
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		default: break;
	}

	// Delete the current save file
	if(TCODSystem::fileExists(SAVEGAME_FILENAME)) TCODSystem::deleteFile(SAVEGAME_FILENAME);

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::red, TCODColor::black);

	// Set default colours for console
	menu->Con(STATE_02)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_02)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_02)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_02)->clear();

	// Print frame and title
	menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Game Over");

	// Print the death page contents
	menu->Con(STATE_02)->printRect(xstart, ystart, xend, yend, "While your valiant efforts should be commended, they were all for naught.\n\n\nThe %cAncient Menance%c spread across these lands, killing all those that could fight and enslaving the rest.\n\n\nEventhough your part in this tale is over, perhaps a new hero will one day emerge from the remnants of these broken and shattered people.", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

	menu->Con(STATE_02)->print(xend, yend + 2, "%c[Enter]%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	return status;
}

void MenuDeath::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the death screen to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 0.85f);
}

//------------------------------------------------------------------------
//
// Methods for MenuUI
//
//------------------------------------------------------------------------
MenuUI *MenuUI::Instance()
{
	static MenuUI instance;
	return &instance;
}

bool MenuUI::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 - 2, h = NMSGS + 4;

	// The Message Log
	menu->Con(STATE_01, new TCODConsole(w, h));

	// Set colours for frame and title
	menu->Con(STATE_01)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_01)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_01)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_01)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_01)->clear();

	// Print frame and title
	menu->Con(STATE_01)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Message Log");

	// Print contents of activity log to con
	int x = 2, y = NMSGS + 1;
	for(int i = 0; i < NMSGS; i++) menu->Con(STATE_01)->print(x, y--, menu->MessageLog[i].c_str());

	return status;
}

void MenuUI::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 - 2, h = NMSGS + 4;
	int x = 0, y = DISPLAY_HEIGHT + 3;
	int frame = static_cast<int>(1000.0f*TCODSystem::getLastFrameLength());
	int fps = TCODSystem::getFps();

	// Blit the Message Log to the root console
	TCODConsole::blit(menu->Con(STATE_01), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);

	// Various UI stuff
	if(Engine()->Game()->InGame())
	{
		// Render player hp bar
		TCODConsole::root->setDefaultForeground(TCODColor::white);
		TCODConsole::root->printEx(1, 1, TCOD_BKGND_NONE, TCOD_LEFT, "HP");
		float hpfraction = static_cast<float>(Engine()->Player()->HP())/static_cast<float>(Engine()->Player()->HPMax());
		int hpbar = static_cast<int>(20.0f*hpfraction);
		if(hpbar > 0)
		{
			TCODConsole::root->setDefaultBackground(TCODColor::red);
			TCODConsole::root->rect(4, 1, hpbar, 1, true, TCOD_BKGND_SET);
		}
		if(hpbar < 20)
		{
			TCODConsole::root->setDefaultBackground(TCODColor::darkerRed);
			TCODConsole::root->rect(4 + hpbar, 1, 20 - hpbar, 1, true, TCOD_BKGND_SET);
		}

		// Render player mp bar
		TCODConsole::root->setDefaultForeground(TCODColor::white);
		TCODConsole::root->printEx(DISPLAY_WIDTH - 24, 1, TCOD_BKGND_NONE, TCOD_LEFT, "MP");
		float mpfraction = static_cast<float>(Engine()->Player()->MP())/static_cast<float>(Engine()->Player()->MPMax());
		int mpbar = static_cast<int>(20.0f*mpfraction);
		if(mpbar > 0)
		{
			TCODConsole::root->setDefaultBackground(TCODColor::blue);
			TCODConsole::root->rect(DISPLAY_WIDTH - 21, 1, mpbar, 1, true, TCOD_BKGND_SET);
		}
		if(mpbar < 20)
		{
			TCODConsole::root->setDefaultBackground(TCODColor::darkerBlue);
			TCODConsole::root->rect(DISPLAY_WIDTH - 21 + mpbar, 1, 20 - mpbar, 1, true, TCOD_BKGND_SET);
		}

		// Render player magic selection
		switch(menu->MagicID())
		{
			case MAGIC_LIGHT:
			{
				TCODConsole::root->setDefaultForeground(TCODColor::white);
				TCODConsole::root->printEx(DISPLAY_WIDTH/2 - 2, 1, TCOD_BKGND_NONE, TCOD_LEFT, "Light Magic");
				menu->MagicIcon(new TCODImage("data/img/magic_light.png"));
				menu->MagicIcon()->blit2x(TCODConsole::root, DISPLAY_WIDTH/2 - 6, 0);
				break;
			}
			case MAGIC_FIRE:
			{
				TCODConsole::root->setDefaultForeground(TCODColor::white);
				TCODConsole::root->printEx(DISPLAY_WIDTH/2 - 2, 1, TCOD_BKGND_NONE, TCOD_LEFT, "Fire Magic");
				menu->MagicIcon(new TCODImage("data/img/magic_fire.png"));
				menu->MagicIcon()->blit2x(TCODConsole::root, DISPLAY_WIDTH/2 - 6, 0);
				break;
			}
			case MAGIC_WATER:
			{
				TCODConsole::root->setDefaultForeground(TCODColor::white);
				TCODConsole::root->printEx(DISPLAY_WIDTH/2 - 2, 1, TCOD_BKGND_NONE, TCOD_LEFT, "Water Magic");
				menu->MagicIcon(new TCODImage("data/img/magic_water.png"));
				menu->MagicIcon()->blit2x(TCODConsole::root, DISPLAY_WIDTH/2 - 6, 0);
				break;
			}
			case MAGIC_WIND:
			{
				TCODConsole::root->setDefaultForeground(TCODColor::white);
				TCODConsole::root->printEx(DISPLAY_WIDTH/2 - 2, 1, TCOD_BKGND_NONE, TCOD_LEFT, "Wind Magic");
				menu->MagicIcon(new TCODImage("data/img/magic_wind.png"));
				menu->MagicIcon()->blit2x(TCODConsole::root, DISPLAY_WIDTH/2 - 6, 0);
				break;
			}
			case MAGIC_EARTH:
			{
				TCODConsole::root->setDefaultForeground(TCODColor::white);
				TCODConsole::root->printEx(DISPLAY_WIDTH/2 - 2, 1, TCOD_BKGND_NONE, TCOD_LEFT, "Earth Magic");
				menu->MagicIcon(new TCODImage("data/img/magic_earth.png"));
				menu->MagicIcon()->blit2x(TCODConsole::root, DISPLAY_WIDTH/2 - 6, 0);
				break;
			}
			default: break;
		}

		// Misc UI Stuff
		//TCODConsole::root->setDefaultBackground(TCODColor::lightGrey);
		//TCODConsole::root->setDefaultForeground(TCODColor::white);
		//for(int i = 0; i < SCREEN_WIDTH; i++) TCODConsole::root->putChar(i, 4, ' ' ,TCOD_BKGND_MULTIPLY);
		//TCODConsole::root->printEx(1, 4, TCOD_BKGND_NONE, TCOD_LEFT, "[alt+enter]: toggle fullscreen");
		//TCODConsole::root->printEx(SCREEN_WIDTH - 3, 4, TCOD_BKGND_NONE, TCOD_RIGHT, "[backspace]: screen capture");
		//for(int i = 0; i < SCREEN_WIDTH; i++) TCODConsole::root->putChar(i, 5, ' ' ,TCOD_BKGND_MULTIPLY);
		//TCODConsole::root->printEx(1, 5, TCOD_BKGND_NONE, TCOD_LEFT, "[pause]: toggle music");
		//TCODConsole::root->printEx(SCREEN_WIDTH - 2, 5, TCOD_BKGND_NONE, TCOD_RIGHT, "last frame: %3d ms (%3d fps)", frame, fps);
	}
}

bool MenuUI::Receive(MenuClass *menu, const Message &msg)
{
	if(msg.Msg == MSG_MSGLOG)
	{
		// Shift previous entries down one index
		for(int i = NMSGS - 1; i > 0; i--) menu->MessageLog[i] = menu->MessageLog[i - 1];

		// Store new message in the first entry of the activity log
		menu->MessageLog[0] = msg.data;
	}
	return true;
}
