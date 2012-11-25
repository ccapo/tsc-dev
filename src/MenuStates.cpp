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
	int w = 64, h = SCREEN_HEIGHT/2;

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
					Transmit->Send(Engine(), MSG_GAMEHELP);
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

	// Print the menu options
	y = NMAIN;
	for(int i = 0; i < NMAIN; i++)
	{
		y += 2;
		if(i == cursor)
		{
			// Print currently selected item
			menu->Con(STATE_01)->print(x, y, menu->MainOptions[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		else
		{
			// Print all other menu items
			menu->Con(STATE_01)->print(x, y, menu->MainOptions[i].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
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
	int xend = w - 8, yend = h - 4;

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
			Transmit->Send(Engine(), MSG_GAMEHELP);
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
	for(int i = 0; i < NHELP; i++) menu->Con(STATE_02)->print(x, y++, menu->HelpOptions[i].c_str());

	y++;
	menu->Con(STATE_02)->print(x, y++, "%cSaving%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	menu->Con(STATE_02)->printRect(x, ++y, xend, yend, menu->HelpText.c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

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
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int xstart = 4, ystart = 7, xend = w - 8, yend = h - 4;

	// The Introduction Screen
	menu->Con(STATE_02, new TCODConsole(w, h));

	switch(key.vk)
	{
		case TCODK_ENTER:
		{
			cursor++;
			if(cursor >= NINTRO) Transmit->Send(Engine(), MSG_BEGINGAME);
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

	switch(cursor)
	{
		case INTRO_01:
		{
			// Print the introduction page contents
			menu->Con(STATE_02)->printRect(xstart, ystart, xend, yend, menu->IntroText[INTRO_01].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			break;
		}
		case INTRO_02:
		{
			// Print the introduction page contents
			menu->Con(STATE_02)->printRect(xstart, ystart, xend, yend, menu->IntroText[INTRO_02].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
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
	int ws = w - 16, hs = h - 2;
	int xstart = 3, ystart = 3, xend = ws - 6, yend = hs - 6;

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
	menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 1, 14, 2*NGAME + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 2*NGAME + 4, 14, h - 11, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

	// Display Player Status Panel
	Engine()->UpdateStatusPanel(menu->Con(STATE_02));

	// Print the menu options
	int x = 3, y = 1;
	for(int i = 0; i < NGAME; i++)
	{
		y += 2;
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, menu->GameOptions[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			switch(cursor)
			{
				case GAME_EQUIP:
				{
					int xe = 2, ye = 2;
					menu->Con(STATE_03)->clear();
					menu->Con(STATE_03)->printFrame(0, 0, ws, NEQUIPTYPE + 4, false, TCOD_BKGND_SET, "Equipment");
					menu->Con(STATE_03)->printFrame(0, NEQUIPTYPE + 4, 18, hs - (NEQUIPTYPE + 4), false, TCOD_BKGND_SET, "Stats");
					menu->Con(STATE_03)->printFrame(18, NEQUIPTYPE + 4, ws - 18, hs - (NEQUIPTYPE + 4), false, TCOD_BKGND_SET);

					// Equipment
					for(int j = 0; j < NEQUIPTYPE; j++)
					{
						menu->Con(STATE_03)->print(xe, ye++, menu->EquipOptions[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
					}
					ye = 2;
					menu->Con(STATE_03)->print(xe + 13, ye++, Engine()->Map()->WeaponNames[WEAPON_01].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 13, ye++, Engine()->Map()->ShieldNames[SHIELD_01].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 13, ye++, Engine()->Map()->ArmourNames[ARMOUR_01].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
					menu->Con(STATE_03)->print(xe + 13, ye++, Engine()->Map()->AccessoryNames[ACCESSORY_01].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

					// List Current Stats
					Engine()->UpdateStatsPanel(menu->Con(STATE_03));

					break;
				}
				case GAME_ITEMS:
				{
					int xi = 2, yi = 2;
					menu->Con(STATE_03)->clear();
					menu->Con(STATE_03)->printFrame(0, 0, ws, hs - (NHIDES + 4), false, TCOD_BKGND_SET, "Items");
					menu->Con(STATE_03)->printFrame(0, hs - (NHIDES + 4), ws, NHIDES + 4, false, TCOD_BKGND_SET, "Hides");

					// Items
					//for(int i = 0; i < game.player.itemInv.nitems; i++)
					for(int i = 0; i < NITEMS; i++)
					{
						//int j = game.player.itemInv.index[i];
						//menu->Con(STATE_03)->print(xi, ++yi, game.player.itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xi + 21, yi, " : %2d", game.player.itemInv.count[j]);
						menu->Con(STATE_03)->print(xi, yi, "%cRare Mushroom%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						menu->Con(STATE_03)->print(xi + 21, yi++, " :: %2d", 2);
					}

					// Hide Invetory
					yi = DISPLAY_HEIGHT/2 - 2;

					//for(int i = 0; i < game.player.hideInv.nhides; i++)
					for(int i = 0; i < NHIDES; i++)
					{
						//int j = game.player.hideInv.index[i];
						//menu->Con(STATE_03)->print(xi, ++yi, game.player.hideInv.hides[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xi + 21, yi, " :: %2d", game.player.hideInv.count[j]);
						menu->Con(STATE_03)->print(xi, yi, "%cRare Hide%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						menu->Con(STATE_03)->print(xi + 21, yi++, " :: %2d", 3);
					}
					break;
				}
				default: break;
			}
		}
		else
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, menu->GameOptions[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
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
	int ws = w - 16, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2;
	int x = 2, y = 2;

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

	// Print Frames
	menu->Con(STATE_03)->printFrame(0, 0, ws, NEQUIPTYPE + 4, false, TCOD_BKGND_SET, "Equipment");
	menu->Con(STATE_03)->printFrame(0, NEQUIPTYPE + 4, 18, hs - (NEQUIPTYPE + 4), false, TCOD_BKGND_SET, "Stats");

	// List Current Equipment
	for(int i = 0; i < NEQUIPTYPE; i++)
	{
		// Highlight Selection
		if(i == cursor)
		{
			menu->Con(STATE_03)->print(x, y, menu->EquipOptions[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			int xb = ws - 18, yb = NEQUIPTYPE + 6;
			switch(cursor)
			{
				case WEAPON:
				{
					menu->Con(STATE_03)->printFrame(18, NEQUIPTYPE + 4, ws - 18, hs - (NEQUIPTYPE + 4), false, TCOD_BKGND_SET, menu->EquipListOptions[i].c_str());
					for(int j = 0; j < NWEAPONS; j++)
					{
						menu->Con(STATE_03)->print(xb, yb, Engine()->Map()->WeaponNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						yb++;
					}
					break;
				}
				case SHIELD:
				{
					menu->Con(STATE_03)->printFrame(18, NEQUIPTYPE + 4, ws - 18, hs - (NEQUIPTYPE + 4), false, TCOD_BKGND_SET, menu->EquipListOptions[i].c_str());
					for(int j = 0; j < NSHIELDS; j++)
					{
						menu->Con(STATE_03)->print(xb, yb, Engine()->Map()->ShieldNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						yb++;
					}
					break;
				}
				case ARMOUR:
				{
					menu->Con(STATE_03)->printFrame(18, NEQUIPTYPE + 4, ws - 18, hs - (NEQUIPTYPE + 4), false, TCOD_BKGND_SET, menu->EquipListOptions[i].c_str());
					for(int j = 0; j < NARMOUR; j++)
					{
						menu->Con(STATE_03)->print(xb, yb, Engine()->Map()->ArmourNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						yb++;
					}
					break;
				}
				case ACCESSORY:
				{
					menu->Con(STATE_03)->printFrame(18, NEQUIPTYPE + 4, ws - 18, hs - (NEQUIPTYPE + 4), false, TCOD_BKGND_SET, menu->EquipListOptions[i].c_str());
					for(int j = 0; j < NACCESSORY; j++)
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
			menu->Con(STATE_03)->print(x, y, menu->EquipOptions[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		y++;
	}

	// Currently Equipped
	x += 13; y = 2;
	menu->Con(STATE_03)->print(x, y++, Engine()->Map()->WeaponNames[WEAPON_01].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x, y++, Engine()->Map()->ShieldNames[SHIELD_01].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x, y++, Engine()->Map()->ArmourNames[ARMOUR_01].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	menu->Con(STATE_03)->print(x, y++, Engine()->Map()->AccessoryNames[ACCESSORY_01].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	// List Current Stats
	Engine()->UpdateStatsPanel(menu->Con(STATE_03));

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipInv::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2 - (NEQUIPTYPE + 4);
	int x = 2, y = 2;

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

	// Print Frames
	menu->Con(STATE_04)->printFrame(0, 0, 18, hs, false, TCOD_BKGND_SET, "Stats");
	menu->Con(STATE_04)->printFrame(18, 0, ws - 18, hs, false, TCOD_BKGND_SET, "Weapons");

	// List Current Equipment
	//Stats stats = game.player.stats;
	int stats[10] = {30, 6, 1, 15, 8, 15, 4, 4, 8, 1};
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
			//stats += game.player.equipInv.Weapons[j].stats;
		}
		else
		{
			//menu->Con(STATE_04)->print(x + 18, y++, game.player.equipInv.Weapons[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->WeaponNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	// List Current Stats and Preview New Stats
	Engine()->UpdateStatsPanel(menu->Con(STATE_04), stats);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuWeaponInv::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - (NEQUIPTYPE + 4);
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3 + (NEQUIPTYPE + 4);

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2 - (NEQUIPTYPE + 4);
	int x = 2, y = 2;

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

	// Print Frames
	menu->Con(STATE_04)->printFrame(0, 0, 18, hs, false, TCOD_BKGND_SET, "Stats");
	menu->Con(STATE_04)->printFrame(18, 0, ws - 18, hs, false, TCOD_BKGND_SET, "Shields");

	// List Current Equipment
	//Stats stats = game.player.stats;
	int stats[10] = {30, 6, 1, 15, 8, 15, 4, 4, 8, 1};
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
			//stats += game.player.equipInv.Shields[j].stats;
		}
		else
		{
			//menu->Con(STATE_04)->print(x + 18, y++, game.player.equipInv.Shields[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->ShieldNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	// List Current Stats and Preview New Stats
	Engine()->UpdateStatsPanel(menu->Con(STATE_04), stats);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuShieldInv::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - (NEQUIPTYPE + 4);
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3 + (NEQUIPTYPE + 4);

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2 - (NEQUIPTYPE + 4);
	int x = 2, y = 2;

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

	// Print Frames
	menu->Con(STATE_04)->printFrame(0, 0, 18, hs, false, TCOD_BKGND_SET, "Stats");
	menu->Con(STATE_04)->printFrame(18, 0, ws - 18, hs, false, TCOD_BKGND_SET, "Armour");

	// List Current Equipment
	//Stats stats = game.player.stats;
	int stats[10] = {30, 6, 1, 15, 8, 15, 4, 4, 8, 1};
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
			//stats += game.player.equipInv.Armours[j].stats;
		}
		else
		{
			//menu->Con(STATE_04)->print(x + 18, y++, game.player.equipInv.Armours[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->ArmourNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	// List Current Stats and Preview New Stats
	Engine()->UpdateStatsPanel(menu->Con(STATE_04), stats);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuArmourInv::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - (NEQUIPTYPE + 4);
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3 + (NEQUIPTYPE + 4);

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2 - (NEQUIPTYPE + 4);
	int x = 2, y = 2;

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

	// Print Frames
	menu->Con(STATE_04)->printFrame(0, 0, 18, hs, false, TCOD_BKGND_SET, "Stats");
	menu->Con(STATE_04)->printFrame(18, 0, ws - 18, hs, false, TCOD_BKGND_SET, "Accessories");

	// List Current Equipment
	//Stats stats = game.player.stats;
	int stats[10] = {30, 6, 1, 15, 8, 15, 4, 4, 8, 1};
	for(int i = 0; i < NACCESSORY; i++)
	{
		// Highlight Selection
		if(i == cursor)
		{
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->AccessoryNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_04)->print(x + 18, hs - 3, game.player.equipInv.Accessory[j].desc);
			menu->Con(STATE_04)->print(x + 18, hs - 3, "MAP +4");

			//stats -= game.player.equipInv.equiped[ACCESSORY].stats;
			//stats += game.player.equipInv.Accessory[j].stats;
		}
		else
		{
			//menu->Con(STATE_04)->print(x + 18, y++, game.player.equipInv.Accessory[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x + 18, y++, Engine()->Map()->AccessoryNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
	}

	// List Current Stats and Preview New Stats
	Engine()->UpdateStatsPanel(menu->Con(STATE_04), stats);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuAccessoryInv::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - (NEQUIPTYPE + 4);
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3 + (NEQUIPTYPE + 4);

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2;
  int yend = NITEMS + 3;

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % MAX(1, NITEMS + NHIDES);
			break;
		}
		case TCODK_UP:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = MAX(0, NITEMS + NHIDES - 1);
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
			//if(cursor < NITEMS)
			//{
			//	Engine()->Player()->UseItem(&cursor);
			//}
			//else
			//{
			//	Engine()->Player()->DropHide(&cursor);
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

	// Set colours for submenu
	menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);
	menu->Con(STATE_03)->clear();

	// Print Frames
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs - (NHIDES + 4), false, TCOD_BKGND_SET, "Items");
	menu->Con(STATE_03)->printFrame(0, hs - (NHIDES + 4), ws, NHIDES + 4, false, TCOD_BKGND_SET, "Hides");

	// Items
	int x = 2, y = 2;
	//menu->Con(STATE_03)->print(x, y, "%cItems%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 27, y++, "%cQty%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

	//for(int i = 0; i < game.player.itemInv.nitems; i++)
	for(int i = 0; i < NITEMS; i++)
	{
		//int j = game.player.itemInv.index[i];
		if(i == cursor)
		{
			//menu->Con(STATE_03)->print(x, ++y, game.player.itemInv.items[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 21, y, " :: %2d", game.player.itemInv.count[j]);
			//menu->Con(STATE_03)->print(x, yend, game.player.itemInv.items[j].desc);
			menu->Con(STATE_03)->print(x, y, "%cRare Mushroom%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x + 21, y++, " :: %2d", 2);
			menu->Con(STATE_03)->print(x, yend, "Very Rare");
		}
		else
		{
			//menu->Con(STATE_03)->print(x, ++y, game.player.itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 21, y, " :: %2d", game.player.itemInv.count[j]);
			menu->Con(STATE_03)->print(x, y, "%cRare Mushroom%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x + 21, y++, " :: %2d", 2);
		}
	}

	// Hide Invetory
	y = DISPLAY_HEIGHT/2 - 2;
	//menu->Con(STATE_03)->print(x, y, "%cHides%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_03)->print(x + 27, y++, "%cQty%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

	//for(int i = 0; i < game.player.hideInv.nhides; i++)
	for(int i = 0; i < NHIDES; i++)
	{
		if(i == cursor - NITEMS)
		{
			//int j = game.player.hideInv.index[i];
			//menu->Con(STATE_03)->print(x, ++y, game.player.hideInv.hides[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 21, y, " :: %2d", game.player.hideInv.count[j]);
			menu->Con(STATE_03)->print(x, y, "%cRare Hide%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x + 21, y++, " :: %2d", 3);
		}
		else
		{
			//int j = game.player.hideInv.index[i];
			//menu->Con(STATE_03)->print(x, ++y, game.player.hideInv.hides[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x + 21, y, " :: %2d", game.player.hideInv.count[j]);
			menu->Con(STATE_03)->print(x, y, "%cRare Hide%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x + 21, y++, " :: %2d", 3);
		}
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuItemInv::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = hs - 6;

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
					Transmit->Send(Engine(), MSG_ITEMSHOPBUY);
					break;
				}
				case ITEMSHOP_SELL:
				{
					// Got anything I can take off your hands?
					Transmit->Send(Engine(), MSG_ITEMSHOPSELL);
					break;
				}
				case ITEMSHOP_EXIT:
				{
					// Exit Menu
					//Engine()->Sound()->ToggleVolume(0.5f);
					Transmit->Send(Engine(), MSG_ITEMSHOP);
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
	menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 1, 14, 2*NITEMSHOP + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 2*NITEMSHOP + 4, 14, h - 11, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs - (NHIDES + 4), false, TCOD_BKGND_SET, "Items");
	menu->Con(STATE_03)->printFrame(0, hs - (NHIDES + 4), ws, NHIDES + 4, false, TCOD_BKGND_SET, "Hides");

	// Display Player Status Panel
	Engine()->UpdateStatusPanel(menu->Con(STATE_02));

	// Print the menu options
	int x = 3, y = NITEMSHOP - 2;
	for(int i = 0; i < NITEMSHOP; i++)
	{
		y += 2;
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, menu->ItemShopOptions[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			switch(cursor)
			{
				case ITEMSHOP_BUY:
				{
					// Items
					int xb = 2, yb = 2;

					//for(int i = 0; i < wmap->locations[id].itemInv.nitems; i++)
					for(int i = 0; i < NITEMS; i++)
					{
						//int j = wmap->locations[id].itemInv.index[i];
						//menu->Con(STATE_03)->print(xb, yb, wmap->locations[id].itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xb + 22, yb, " :: %2d", wmap->locations[id].itemInv.count[j]);
						//menu->Con(STATE_03)->print(xb + 27, yb++, " %3d GP", wmap->locations[id].itemInv.price[j]);
						menu->Con(STATE_03)->print(xb, yb, "%cRare Mushroom%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						menu->Con(STATE_03)->print(xb + 21, yb, " :: %2d", 2);
						menu->Con(STATE_03)->print(xb + 27, yb++, " %3d GP", 20);
					}
					break;
				}
				case ITEMSHOP_SELL:
				{
					// Items
					int xs = 2, ys = 2;

					//for(int i = 0; i < game.player.itemInv.nitems; i++)
					for(int i = 0; i < NITEMS; i++)
					{
						//int j = game.player.itemInv.index[i];
						//menu->Con(STATE_03)->print(xs, ys, game.player.itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xs + 21, ys, " :: %2d", game.player.itemInv.count[j]);
						//menu->Con(STATE_03)->print(xs + 27, ys++, " %3d GP", MAX(1, wmap->locations[id].itemInv.price[j]/2));
						menu->Con(STATE_03)->print(xs, ys, "%cRare Mushroom%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						menu->Con(STATE_03)->print(xs + 21, ys, " :: %2d", 2);
						menu->Con(STATE_03)->print(xs + 27, ys++, " %3d GP", 10);
					}

					// Hide Invetory
					ys = DISPLAY_HEIGHT/2 - 2;

					//for(int i = 0; i < game.player.hideInv.nhides; i++)
					for(int i = 0; i < NHIDES; i++)
					{
						//int j = game.player.hideInv.index[i];
						//menu->Con(STATE_03)->print(xs, ys, game.player.hideInv.hides[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xs + 21, ys, " :: %2d", game.player.hideInv.count[j]);
						//menu->Con(STATE_03)->print(xs + 27, ys++, " %3d GP", MAX(1, wmap->locations[id].hideInv.price[j]));
						menu->Con(STATE_03)->print(xs, ys, "%cRare Hide%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						menu->Con(STATE_03)->print(xs + 21, ys, " :: %2d", 3);
						menu->Con(STATE_03)->print(xs + 27, ys++, " %3d GP", 5);
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
			menu->Con(STATE_02)->print(x, y, menu->ItemShopOptions[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
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
	int ws = w - 16, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = NITEMS + 3;
	int x = 2, y = 2;

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

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
			Transmit->Send(Engine(), MSG_ITEMSHOPBUY);
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
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs - (NHIDES + 4), false, TCOD_BKGND_SET, "Items");
	menu->Con(STATE_03)->printFrame(0, hs - (NHIDES + 4), ws, NHIDES + 4, false, TCOD_BKGND_SET, "Hides");

	//for(int i = 0; i < wmap->locations[id].itemInv.nitems; i++)
	for(int i = 0; i < NITEMS; i++)
	{
		//int j = wmap->locations[id].itemInv.index[i];
		if(i == cursor)
		{
			//menu->Con(STATE_03)->print(x, y, wmap->locations[id].itemInv.items[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x, yend, wmap->locations[id].itemInv.items[j].desc);
			menu->Con(STATE_03)->print(x, y, "%cRare Mushroom%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, yend, "Very Rare");

			//menu->Con(STATE_03)->print(x + 21, y, " :: %2d", wmap->locations[id].itemInv.count[j]);
			//menu->Con(STATE_03)->print(x + 27, y, " %3d GP", wmap->locations[id].itemInv.price[j]);
			menu->Con(STATE_03)->print(x + 21, y, " :: %2d", 2);
			menu->Con(STATE_03)->print(x + 27, y, " %3d GP", 20);
		}
		else
		{
			//menu->Con(STATE_03)->print(x, y, wmap->locations[id].itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, y, "%cRare Mushroom%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);

			//menu->Con(STATE_03)->print(x + 21, y, " :: %2d", wmap->locations[id].itemInv.count[j]);
			//menu->Con(STATE_03)->print(x + 27, y, " %3d GP", wmap->locations[id].itemInv.price[j]);
			menu->Con(STATE_03)->print(x + 21, y, " :: %2d", 2);
			menu->Con(STATE_03)->print(x + 27, y, " %3d GP", 20);
		}
		y++;
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuItemShopBuy::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = NITEMS + 3;
	int x = 2, y = 2;

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

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
			Transmit->Send(Engine(), MSG_ITEMSHOPSELL);
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
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs - (NHIDES + 4), false, TCOD_BKGND_SET, "Items");
	menu->Con(STATE_03)->printFrame(0, hs - (NHIDES + 4), ws, NHIDES + 4, false, TCOD_BKGND_SET, "Hides");

	//for(int i = 0; i < wmap->locations[id].itemInv.nitems; i++)
	for(int i = 0; i < NITEMS; i++)
	{
		//int j = wmap->locations[id].itemInv.index[i];
		if(i == cursor)
		{
			//menu->Con(STATE_03)->print(x, y, game.player.itemInv.items[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			//menu->Con(STATE_03)->print(x, yend, game.player.itemInv.items[j].desc);
			menu->Con(STATE_03)->print(x, y, "%cRare Mushroom%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, yend, "Very Rare");

			//menu->Con(STATE_03)->print(x + 21, y, " :: %2d", game.player.itemInv.count[j]);
			//menu->Con(STATE_03)->print(x + 27, y, " %3d GP", MAX(1, wmap->locations[id].itemInv.price[j]/2));
			menu->Con(STATE_03)->print(x + 21, y, " :: %2d", 2);
			menu->Con(STATE_03)->print(x + 27, y, " %3d GP", 10);
		}
		else
		{
			//menu->Con(STATE_03)->print(x, y, game.player.itemInv.items[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, y, "%cRare Mushroom%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);

			//menu->Con(STATE_03)->print(x + 21, y, " :: %2d", game.player.itemInv.count[j]);
			//menu->Con(STATE_03)->print(x + 27, y, " %3d GP", MAX(1, wmap->locations[id].itemInv.price[j]/2));
			menu->Con(STATE_03)->print(x + 21, y, " :: %2d", 2);
			menu->Con(STATE_03)->print(x + 27, y, " %3d GP", 10);
		}
		y++;
	}

	y = DISPLAY_HEIGHT/2 - 2;
	//for(int i = 0; i < game.player.hideInv.nhides; i++)
	for(int i = 0; i < NHIDES; i++)
	{
		//int j = game.player.hideInv.index[i];
		//if(i == cursor - game.player.itemInv.nitems)
		if(i == cursor - NITEMS)
		{
			//menu->Con(STATE_03)->print(x, y, game.player.hideInv.hides[j].name, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, y, "%cRare Hide%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			//menu->Con(STATE_03)->print(x + 21, y, " :: %2d", game.player.hideInv.count[j]);
			//menu->Con(STATE_03)->print(x + 27, y, " %3d GP", MAX(1, wmap->locations[id].hideInv.price[j]));
			menu->Con(STATE_03)->print(x + 21, y, " :: %2d", 3);
			menu->Con(STATE_03)->print(x + 27, y, " %3d GP", 5);
		}
		else
		{
			//menu->Con(STATE_03)->print(x, y, game.player.hideInv.hides[j].name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			menu->Con(STATE_03)->print(x, y, "%cRare Hide%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);

			//menu->Con(STATE_03)->print(x + 21, y, " :: %2d", game.player.hideInv.count[j]);
			//menu->Con(STATE_03)->print(x + 27, y, " %3d GP", MAX(1, wmap->locations[id].hideInv.price[j]));
			menu->Con(STATE_03)->print(x + 21, y, " :: %2d", 3);
			menu->Con(STATE_03)->print(x + 27, y, " %3d GP", 5);
		}
		y++;
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuItemShopSell::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	//TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = hs - 6;

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
					Transmit->Send(Engine(), MSG_EQUIPSHOPBUY);
					break;
				}
				case EQUIPSHOP_SELL:
				{
					// Got anything I can take off your hands?
					Transmit->Send(Engine(), MSG_EQUIPSHOPSELL);
					break;
				}
				case EQUIPSHOP_EXIT:
				{
					// Exit Menu
					//Engine()->Sound()->ToggleVolume(0.5f);
					Transmit->Send(Engine(), MSG_EQUIPSHOP);
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
	menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 1, 14, 2*NEQUIPSHOP + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 2*NEQUIPSHOP + 4, 14, h - 11, false, TCOD_BKGND_SET);

	menu->Con(STATE_03)->printFrame(0, 0, ws, 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 5, ws, hs/3 + 1 + 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 2*hs/3 + 1, ws, hs/3, false, TCOD_BKGND_SET);

	// Display Player Status Panel
	Engine()->UpdateStatusPanel(menu->Con(STATE_02));

	// Print the menu options
	int x = 3, y = NEQUIPSHOP - 2;
	for(int i = 0; i < NEQUIPSHOP; i++)
	{
		y += 2;
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, menu->EquipShopOptions[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			switch(cursor)
			{
				case EQUIPSHOP_BUY:
				{
					// List Equipment Types
					int xb = 2, yb = 2;
					for(int i = 0; i < NEQUIPTYPE; i++)
					{
						menu->Con(STATE_03)->print(xb, yb, menu->EquipOptionsHorizontal[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
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
						menu->Con(STATE_03)->print(xb, yb, menu->EquipOptionsHorizontal[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
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
			menu->Con(STATE_02)->print(x, y, menu->EquipShopOptions[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
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
	int ws = w - 16, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = hs - 6;

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

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
			Transmit->Send(Engine(), MSG_EQUIPSHOPBUY);
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
				case WEAPON:
				{
					Transmit->Send(Engine(), MSG_EQUIPSHOPBUYWEAPON);
					break;
				}
				case SHIELD:
				{
					Transmit->Send(Engine(), MSG_EQUIPSHOPBUYSHIELD);
					break;
				}
				case ARMOUR:
				{
					Transmit->Send(Engine(), MSG_EQUIPSHOPBUYARMOUR);
					break;
				}
				case ACCESSORY:
				{
					Transmit->Send(Engine(), MSG_EQUIPSHOPBUYACCESSORY);
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

	// Print frame and title
	menu->Con(STATE_03)->printFrame(0, 0, ws, 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 5, ws, hs/3 + 1 + 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 2*hs/3 + 1, ws, hs/3, false, TCOD_BKGND_SET);

	// Print the menu options
	int x = 2, y = 2, xe = 2;
	for(int i = 0; i < NEQUIPTYPE; i++)
	{
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_03)->print(x, y, menu->EquipOptionsHorizontal[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			y += 5;

			switch(cursor)
			{
				case WEAPON:
				{
					for(int j = 0; j < NWEAPONS; j++)
					{
						menu->Con(STATE_03)->print(xe, y, Engine()->Map()->WeaponNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
						menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", 100);
						y++;
					}
					break;
				}
				case SHIELD:
				{
					for(int j = 0; j < NSHIELDS; j++)
					{
						menu->Con(STATE_03)->print(xe, y, Engine()->Map()->ShieldNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
						menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", 100);
						y++;
					}
					break;
				}
				case ARMOUR:
				{
					for(int j = 0; j < NARMOUR; j++)
					{
						menu->Con(STATE_03)->print(xe, y, Engine()->Map()->ArmourNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
						menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", 100);
						y++;
					}
					break;
				}
				case ACCESSORY:
				{
					for(int j = 0; j < NACCESSORY; j++)
					{
						menu->Con(STATE_03)->print(xe, y, Engine()->Map()->AccessoryNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
						menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", 100);
						y++;
					}
					break;
				}
				default: break;
			}
		}
		else
		{
			// Print each item
			menu->Con(STATE_03)->print(x, y, menu->EquipOptionsHorizontal[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
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
	int ws = w - 16, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuEquipShopBuyWeapon
//
//------------------------------------------------------------------------
MenuEquipShopBuyWeapon *MenuEquipShopBuyWeapon::Instance()
{
	static MenuEquipShopBuyWeapon instance;
	return &instance;
}

bool MenuEquipShopBuyWeapon::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = 2, y = 2, yend = hs/2;

	// Game submenu screen
	menu->Con(STATE_04, new TCODConsole(ws, hs));

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NWEAPONS;
			break;
		}
		case TCODK_RIGHT:
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
		case TCODK_LEFT:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NWEAPONS - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_EQUIPSHOPBUYWEAPON);
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
			//Engine()->Player()->BuyEquip(WEAPON, &cursor);
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

	// Print frame and title
	menu->Con(STATE_04)->printFrame(0, 0, ws, hs/2 + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_04)->printFrame(0, hs/2 + 3, ws, hs - (hs/2 + 3), false, TCOD_BKGND_SET);

	//Stats stats = game.player.stats;
	int stats[10] = {30, 6, 1, 15, 8, 15, 4, 4, 8, 1};
	for(int i = 0; i < NWEAPONS; i++)
	{
		if(i == cursor)
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->WeaponNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x, yend, "AP +2");

			//stats -= game.player.equipInv.equiped[WEAPON].stats;
			//stats += game.player.equipInv.Weapons[i].stats;
		}
		else
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->WeaponNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		//menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
		menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", 100);
		y++;
	}

	// Update Equip Stats Panel
	Engine()->UpdateEquipStatsPanel(menu->Con(STATE_04), stats);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipShopBuyWeapon::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1 + 5, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuEquipShopBuyShield
//
//------------------------------------------------------------------------
MenuEquipShopBuyShield *MenuEquipShopBuyShield::Instance()
{
	static MenuEquipShopBuyShield instance;
	return &instance;
}

bool MenuEquipShopBuyShield::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = 2, y = 2, yend = hs/2;

	// Game submenu screen
	menu->Con(STATE_04, new TCODConsole(ws, hs));

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NSHIELDS;
			break;
		}
		case TCODK_RIGHT:
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
		case TCODK_LEFT:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NSHIELDS - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_EQUIPSHOPBUYSHIELD);
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
			//Engine()->Player()->BuyEquip(SHIELD, &cursor);
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

	// Print frame and title
	menu->Con(STATE_04)->printFrame(0, 0, ws, hs/2 + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_04)->printFrame(0, hs/2 + 3, ws, hs - (hs/2 + 3), false, TCOD_BKGND_SET);


	//Stats stats = game.player.stats;
	int stats[10] = {30, 6, 1, 15, 8, 15, 4, 4, 8, 1};
	for(int i = 0; i < NSHIELDS; i++)
	{
		if(i == cursor)
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->ShieldNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x, yend, "DP +2");

			//stats -= game.player.equipInv.equiped[SHIELD].stats;
			//stats += game.player.equipInv.Shields[i].stats;
		}
		else
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->ShieldNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		//menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
		menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", 100);
		y++;
	}

	// Update Equip Stats Panel
	Engine()->UpdateEquipStatsPanel(menu->Con(STATE_04), stats);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipShopBuyShield::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1 + 5, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuEquipShopBuyArmour
//
//------------------------------------------------------------------------
MenuEquipShopBuyArmour *MenuEquipShopBuyArmour::Instance()
{
	static MenuEquipShopBuyArmour instance;
	return &instance;
}

bool MenuEquipShopBuyArmour::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = 2, y = 2, yend = hs/2;

	// Game submenu screen
	menu->Con(STATE_04, new TCODConsole(ws, hs));

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NARMOUR;
			break;
		}
		case TCODK_RIGHT:
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
		case TCODK_LEFT:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NARMOUR - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_EQUIPSHOPBUYARMOUR);
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
			//Engine()->Player()->BuyEquip(ARMOUR, &cursor);
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

	// Print frame and title
	menu->Con(STATE_04)->printFrame(0, 0, ws, hs/2 + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_04)->printFrame(0, hs/2 + 3, ws, hs - (hs/2 + 3), false, TCOD_BKGND_SET);


	//Stats stats = game.player.stats;
	int stats[10] = {30, 6, 1, 15, 8, 15, 4, 4, 8, 1};
	for(int i = 0; i < NARMOUR; i++)
	{
		if(i == cursor)
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->ArmourNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x, yend, "DP +4");

			//stats -= game.player.equipInv.equiped[ARMOUR].stats;
			//stats += game.player.equipInv.Armour[i].stats;
		}
		else
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->ArmourNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		//menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
		menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", 100);
		y++;
	}

	// Update Equip Stats Panel
	Engine()->UpdateEquipStatsPanel(menu->Con(STATE_04), stats);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipShopBuyArmour::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1 + 5, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuEquipShopBuyAccessory
//
//------------------------------------------------------------------------
MenuEquipShopBuyAccessory *MenuEquipShopBuyAccessory::Instance()
{
	static MenuEquipShopBuyAccessory instance;
	return &instance;
}

bool MenuEquipShopBuyAccessory::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = 2, y = 2, yend = hs/2;

	// Game submenu screen
	menu->Con(STATE_04, new TCODConsole(ws, hs));

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NACCESSORY;
			break;
		}
		case TCODK_RIGHT:
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
		case TCODK_LEFT:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NACCESSORY - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_EQUIPSHOPBUYACCESSORY);
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
			//Engine()->Player()->BuyEquip(ACCESSORY, &cursor);
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

	// Print frame and title
	menu->Con(STATE_04)->printFrame(0, 0, ws, hs/2 + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_04)->printFrame(0, hs/2 + 3, ws, hs - (hs/2 + 3), false, TCOD_BKGND_SET);

	//Stats stats = game.player.stats;
	int stats[10] = {30, 6, 1, 15, 8, 15, 4, 4, 8, 1};
	for(int i = 0; i < NACCESSORY; i++)
	{
		if(i == cursor)
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->AccessoryNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x, yend, "MAP +2 MDP +2");

			//stats -= game.player.equipInv.equiped[ACCESSORY].stats;
			//stats += game.player.equipInv.Accessory[i].stats;
		}
		else
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->AccessoryNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		//menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
		menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", 100);
		y++;
	}

	// Update Equip Stats Panel
	Engine()->UpdateEquipStatsPanel(menu->Con(STATE_04), stats);

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipShopBuyAccessory::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1 + 5, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = hs - 6;

	// Game submenu screen
	menu->Con(STATE_03, new TCODConsole(ws, hs));

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
			Transmit->Send(Engine(), MSG_EQUIPSHOPSELL);
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
				case WEAPON:
				{
					Transmit->Send(Engine(), MSG_EQUIPSHOPSELLWEAPON);
					break;
				}
				case SHIELD:
				{
					Transmit->Send(Engine(), MSG_EQUIPSHOPSELLSHIELD);
					break;
				}
				case ARMOUR:
				{
					Transmit->Send(Engine(), MSG_EQUIPSHOPSELLARMOUR);
					break;
				}
				case ACCESSORY:
				{
					Transmit->Send(Engine(), MSG_EQUIPSHOPSELLACCESSORY);
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

	// Print frame and title
	menu->Con(STATE_03)->printFrame(0, 0, ws, 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 5, ws, hs/3 + 1 + 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 2*hs/3 + 1, ws, hs/3, false, TCOD_BKGND_SET);

	// Print the menu options
	int x = 2, y = 2, xe = 2;
	for(int i = 0; i < NEQUIPTYPE; i++)
	{
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_03)->print(x, y, menu->EquipOptionsHorizontal[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			y += 5;

			switch(cursor)
			{
				case WEAPON:
				{
					for(int j = 0; j < NWEAPONS; j++)
					{
						menu->Con(STATE_03)->print(xe, y, Engine()->Map()->WeaponNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
						menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", 100);
						y++;
					}
					break;
				}
				case SHIELD:
				{
					for(int j = 0; j < NSHIELDS; j++)
					{
						menu->Con(STATE_03)->print(xe, y, Engine()->Map()->ShieldNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
						menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", 100);
						y++;
					}
					break;
				}
				case ARMOUR:
				{
					for(int j = 0; j < NARMOUR; j++)
					{
						menu->Con(STATE_03)->print(xe, y, Engine()->Map()->ArmourNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
						menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", 100);
						y++;
					}
					break;
				}
				case ACCESSORY:
				{
					for(int j = 0; j < NACCESSORY; j++)
					{
						menu->Con(STATE_03)->print(xe, y, Engine()->Map()->AccessoryNames[j].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
						//menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
						menu->Con(STATE_03)->print(xe + 23, y, " :: %4d GP", 100);
						y++;
					}
					break;
				}
				default: break;
			}
		}
		else
		{
			// Print each item
			menu->Con(STATE_03)->print(x, y, menu->EquipOptionsHorizontal[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
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
	int ws = w - 16, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuEquipShopSellWeapon
//
//------------------------------------------------------------------------
MenuEquipShopSellWeapon *MenuEquipShopSellWeapon::Instance()
{
	static MenuEquipShopSellWeapon instance;
	return &instance;
}

bool MenuEquipShopSellWeapon::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = 2, y = 2, yend = hs/2;

	// Game submenu screen
	menu->Con(STATE_04, new TCODConsole(ws, hs));

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NWEAPONS;
			break;
		}
		case TCODK_RIGHT:
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
		case TCODK_LEFT:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NWEAPONS - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_EQUIPSHOPSELLWEAPON);
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
			//Engine()->Player()->SellEquip(WEAPON, &cursor);
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

	// Print frame and title
	menu->Con(STATE_04)->printFrame(0, 0, ws, hs/2 + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_04)->printFrame(0, hs/2 + 3, ws, hs - (hs/2 + 3), false, TCOD_BKGND_SET);

	for(int i = 0; i < NWEAPONS; i++)
	{
		if(i == cursor)
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->WeaponNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x, yend, "AP +2");
		}
		else
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->WeaponNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		//menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
		menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", 100);
		y++;
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipShopSellWeapon::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1 + 5, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuEquipShopSellShield
//
//------------------------------------------------------------------------
MenuEquipShopSellShield *MenuEquipShopSellShield::Instance()
{
	static MenuEquipShopSellShield instance;
	return &instance;
}

bool MenuEquipShopSellShield::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = 2, y = 2, yend = hs/2;

	// Game submenu screen
	menu->Con(STATE_04, new TCODConsole(ws, hs));

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NSHIELDS;
			break;
		}
		case TCODK_RIGHT:
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
		case TCODK_LEFT:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NSHIELDS - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_EQUIPSHOPSELLSHIELD);
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
			//Engine()->Player()->SellEquip(SHIELD, &cursor);
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

	// Print frame and title
	menu->Con(STATE_04)->printFrame(0, 0, ws, hs/2 + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_04)->printFrame(0, hs/2 + 3, ws, hs - (hs/2 + 3), false, TCOD_BKGND_SET);

	for(int i = 0; i < NSHIELDS; i++)
	{
		if(i == cursor)
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->ShieldNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x, yend, "DP +2");
		}
		else
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->ShieldNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		//menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
		menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", 100);
		y++;
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipShopSellShield::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1 + 5, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuEquipShopSellArmour
//
//------------------------------------------------------------------------
MenuEquipShopSellArmour *MenuEquipShopSellArmour::Instance()
{
	static MenuEquipShopSellArmour instance;
	return &instance;
}

bool MenuEquipShopSellArmour::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = 2, y = 2, yend = hs/2;

	// Game submenu screen
	menu->Con(STATE_04, new TCODConsole(ws, hs));

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NARMOUR;
			break;
		}
		case TCODK_RIGHT:
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
		case TCODK_LEFT:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NARMOUR - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_EQUIPSHOPSELLARMOUR);
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
			//Engine()->Player()->SellEquip(ARMOUR, &cursor);
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

	// Print frame and title
	menu->Con(STATE_04)->printFrame(0, 0, ws, hs/2 + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_04)->printFrame(0, hs/2 + 3, ws, hs - (hs/2 + 3), false, TCOD_BKGND_SET);

	for(int i = 0; i < NARMOUR; i++)
	{
		if(i == cursor)
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->ArmourNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x, yend, "DP +4");
		}
		else
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->ArmourNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		//menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
		menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", 100);
		y++;
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipShopSellArmour::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1 + 5, 1.0f, 1.0f);
}

//------------------------------------------------------------------------
//
// Methods for MenuEquipShopSellAccessory
//
//------------------------------------------------------------------------
MenuEquipShopSellAccessory *MenuEquipShopSellAccessory::Instance()
{
	static MenuEquipShopSellAccessory instance;
	return &instance;
}

bool MenuEquipShopSellAccessory::Update(MenuClass *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	static int cursor = 0;
	bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = 2, y = 2, yend = hs/2;

	// Game submenu screen
	menu->Con(STATE_04, new TCODConsole(ws, hs));

	// Key handler
	switch(key.vk)
	{
		case TCODK_DOWN:
		{
			// Move the cursor position down
			cursor = (cursor + 1) % NACCESSORY;
			break;
		}
		case TCODK_RIGHT:
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
		case TCODK_LEFT:
		{
			// Move the cursor position up
			cursor--;
			if(cursor < 0) cursor = NACCESSORY - 1;
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_EQUIPSHOPSELLACCESSORY);
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
			//Engine()->Player()->SellEquip(ACCESSORY, &cursor);
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

	// Print frame and title
	menu->Con(STATE_04)->printFrame(0, 0, ws, hs/2 + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_04)->printFrame(0, hs/2 + 3, ws, hs - (hs/2 + 3), false, TCOD_BKGND_SET);

	for(int i = 0; i < NACCESSORY; i++)
	{
		if(i == cursor)
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->AccessoryNames[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			menu->Con(STATE_04)->print(x, yend, "MAP +2 MDP +2");
		}
		else
		{
			menu->Con(STATE_04)->print(x, y, Engine()->Map()->AccessoryNames[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
		}
		//menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", MAX(1, wmap->locations[id].equipInv.price[j]));
		menu->Con(STATE_04)->print(x + 23, y, " :: %4d GP", 100);
		y++;
	}

	if(key.vk == TCODK_ESCAPE) cursor = 0;
	key.vk = TCODK_NONE;
	key.c = 0;

	return status;
}

void MenuEquipShopSellAccessory::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int ws = w - 16, hs = h - 2 - 5;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_04), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1 + 5, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = hs - 6;

	//int id = game.worldID - 1, idprev = id - 1, idnext = id + 1;
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
	menu->Con(STATE_02)->printFrame(1, 1, 14, 2*NFERRY + 5, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 2*NFERRY + 6, 14, h - 11, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

	// Display Player Status Panel
	Engine()->UpdateStatusPanel(menu->Con(STATE_02));

	// Print the menu options
	int x = 3, y = 1;
	for(int i = 0; i < NFERRY; i++)
	{
		y += 2;
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, menu->FerryOptions[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			if(cursor == FERRY_TAKE)
			{
				// Travel to the previous town
				menu->Con(STATE_03)->printRect(xstart, ystart, xend, yend, menu->FerryText[FERRY_TAKE].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			}
			else
			{
				// Hurry Back!
				menu->Con(STATE_03)->printRect(xstart, ystart, xend, yend, menu->FerryText[FERRY_EXIT].c_str());
			}
		}
		else
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, menu->FerryOptions[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
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
	int ws = w - 16, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	int ws = w - 16, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;
	int xstart = 2, ystart = 2, xend = ws - 6, yend = hs - 6;

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
					TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);

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
	menu->Con(STATE_02)->printFrame(1, 1, 14, 2*(NINN + 1) + 3, false, TCOD_BKGND_SET);
	menu->Con(STATE_02)->printFrame(1, 2*(NINN + 1) + 4, 14, h - 11, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

	// Display Player Status Panel
	Engine()->UpdateStatusPanel(menu->Con(STATE_02));

	// Print the menu options
	x = 3, y = NINN - 1;
	for(int i = 0; i < NINN; i++)
	{
		y += 2;
		if(i == cursor)
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, menu->InnOptions[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

			if(cursor == INN_STAY)
			{
				// Stay Night at Inn
				menu->Con(STATE_03)->printRect(xstart, ystart, xend, yend, menu->InnText[INN_STAY].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
			}
			else
			{
				// Hurry Back!
				menu->Con(STATE_03)->printRect(xstart, ystart, xend, yend, menu->InnText[INN_EXIT].c_str());
			}
		}
		else
		{
			// Print each item
			menu->Con(STATE_02)->print(x, y, menu->InnOptions[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
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
	int ws = w - 16, hs = h - 2;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;

	// Blit the inn menu and submenu to the root console
	TCODConsole::blit(menu->Con(STATE_02), 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
	TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 15, y + 1, 1.0f, 1.0f);
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
	menu->Con(STATE_02)->printRect(xstart, ystart, xend, yend, menu->DeathText.c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

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
