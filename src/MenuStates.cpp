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
			menu->Selection(cursor);
			switch(cursor)
			{
				case MAIN_NEW:
				{
					Transmit->Send(GameEngine(), MSG_NEWGAME);
					break;
				}
				case MAIN_LOAD:
				{
					Transmit->Send(GameEngine(), MSG_LOADGAME);
					break;
				}
				case MAIN_HELP:
				{
					Transmit->Send(GameEngine(), MSG_HELPSCREEN);
					break;
				}
				case MAIN_QUIT:
				{
					Transmit->Send(GameEngine(), MSG_QUITGAME);
					status = false;
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
	key.vk = TCODK_NONE;
	key.c = 0;

	// Print game title and by line
	menu->Con(STATE_01)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_01)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_01)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_01)->setDefaultForeground(TCODColor::white);
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::white, TCODColor::lightBlue);

	int x = 2, y = 2;
	menu->Con(STATE_01)->print(x, y, "%cThe Serpentine Caves%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
	menu->Con(STATE_01)->print(x, h - 3, "%cv"VERSION"%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_01)->print(x, h - 1, "%cChris Capobianco%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

	//int istart = 256;
	//for(int i = 0; i < 32; i++) menu->Con(STATE_01)->putChar(x + i, h - 12, istart + i, TCOD_BKGND_NONE); istart += 32;
	//for(int i = 0; i < 32; i++) menu->Con(STATE_01)->putChar(x + i, h - 11, istart + i, TCOD_BKGND_NONE); istart += 32;
	//for(int i = 0; i < 32; i++) menu->Con(STATE_01)->putChar(x + i, h - 10, istart + i, TCOD_BKGND_NONE); istart += 32;
	//for(int i = 0; i < 32; i++) menu->Con(STATE_01)->putChar(x + i, h - 9,	istart + i, TCOD_BKGND_NONE); istart += 32;
	//for(int i = 0; i < 32; i++) menu->Con(STATE_01)->putChar(x + i, h - 8,	istart + i, TCOD_BKGND_NONE); istart += 32;
	//for(int i = 0; i < 32; i++) menu->Con(STATE_01)->putChar(x + i, h - 7,	istart + i, TCOD_BKGND_NONE); istart += 32;

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
	menu->DisplayProgress("Generating Serpentine Caves ", GameEngine()->Game()->FractionalProgress());
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
	menu->DisplayProgress("Loading Serpentine Caves", GameEngine()->Game()->FractionalProgress());
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
	menu->DisplayProgress("Saving Serpentine Caves ", GameEngine()->Game()->FractionalProgress());
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
		case TCODK_ENTER:
		{
			menu->Selection(NONE);
			Transmit->Send(GameEngine(), MSG_HELPSCREEN);
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

	// Set colours for frame and title
	menu->Con(STATE_02)->setAlignment(TCOD_LEFT);
	menu->Con(STATE_02)->setBackgroundFlag(TCOD_BKGND_SET);
	menu->Con(STATE_02)->setDefaultBackground(TCODColor::black);
	menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::red, TCODColor::black);

	// Print frame and title
	menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Game Help");

	// Print the information page contents
	int x = 4, y = 5;
	menu->Con(STATE_02)->print(x, y, "%cCommands%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	y += 2;
	for(int i = 0; i < nInfo; i++) menu->Con(STATE_02)->print(x, y++, Options[i].c_str());

	x = 4; y++;
	menu->Con(STATE_02)->print(x, y, "%cSaving%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	y += 2;
	menu->Con(STATE_02)->printRect(x, y, xend, yend, "Whenever the Player returns to the %cWorld Map%c, the game will automatically overwrite the existing save file.\n\nIf the Player expires, death is %cpermanent%c as the save file is %cdeleted%c.", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

	menu->Con(STATE_02)->print(xend, yend + 2, "%c[Enter]%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	return status;
}

void MenuHelp::Render(MenuClass *menu)
{
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
	int x = DISPLAY_WIDTH/2 - w/2, y = SCREEN_HEIGHT/2 - h/2;
	float ftrans = 0.9f;

	// In Game specific settings
	if(GameEngine()->Game()->InGame()) y = DISPLAY_HEIGHT/2 - h/2 + 3;

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

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::red, TCODColor::black);

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
				Transmit->Send(GameEngine(), MSG_BEGINGAME);
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

  switch(menu->IntroPage())
  {
    case INTRO_01:
    {
      // Clear the menu screen
      menu->Con(STATE_02)->clear();

      // Set colours
      menu->Con(STATE_02)->setAlignment(TCOD_LEFT);
      menu->Con(STATE_02)->setBackgroundFlag(TCOD_BKGND_SET);
      menu->Con(STATE_02)->setDefaultBackground(TCODColor::black);
      menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);

      // Print frame and title
      menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Introduction");

      // Print the introduction page contents
      menu->Con(STATE_02)->printRect(xstart, ystart, xend, yend, "Welome brave adventurer, thank you for heeding my pleas for help.\n\n\nI am the %cGuardian of Light%c, one of the five entrusted to protect this world.\n\n\nA %cPowerful Ancient Menace%c is gathering once again in the shadows, and threatens to destroy the peace and harmony of these lands.\n\n\nThis is why I have summoned you here, I must impress upon you to persue a perilous quest to rid the world of this threat.", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

      menu->Con(STATE_02)->print(xend, yend + 2, "%c[Enter]%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

      break;
    }
    case INTRO_02:
    {
      // Clear the menu screen
      menu->Con(STATE_02)->clear();

      // Set colours
      menu->Con(STATE_02)->setAlignment(TCOD_LEFT);
      menu->Con(STATE_02)->setBackgroundFlag(TCOD_BKGND_SET);
      menu->Con(STATE_02)->setDefaultBackground(TCODColor::black);
      menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);

      // Print frame and title
      menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Introduction");

      // Print the introduction page contents
      menu->Con(STATE_02)->printRect(xstart, ystart, xend, yend, "We know this power is gathering deep within\n%cThe Serpentine Caves%c, but where we know not.\n\n\nIt will be a difficult journey, so seek out the other four %cElemental Guardians%c for assistance. If they deem you worthy, they will grant you the ability to use their power.\n\n\nTo aid you on your quest I will grant my %cPower of Light%c, and any creature of the dark will be startled by its brilliance. Use this power wisely.\n\n\nGood luck brave hero, and may the record of your deeds be sung throughout the ages.", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

      menu->Con(STATE_02)->print(xend, yend + 2, "%c[Enter]%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

      break;
    }
    default: break;
  }
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
  static int menuCursor = 0;
  static int subMenuCursor = 0;
  static int subSubMenuCursor = -1;
  bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
  int ws = w - 17, hs = h - 2, i = 0;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;
  int xstart = 3, ystart = 3, xend = ws - 6, yend = hs - 6;
	map<int, string> Options;
	Options.insert(make_pair(i++, "%cEquipment%c"));
	Options.insert(make_pair(i++, "%cInventory%c"));
	Options.insert(make_pair(i++, "%cQuit Game%c"));

  // Game menu screen
  menu->Con(STATE_02, new TCODConsole(w, h));

  // Game submenu screen
  menu->Con(STATE_03, new TCODConsole(ws, hs));

	// Update Player Stats
  //GameEngine()->Player()->UpdateStats();

  // Key handler
  switch(key.vk)
  {
    case TCODK_DOWN:
    {
      // Move the cursor position down
      menuCursor = (menuCursor + 1) % NGAME;
      break;
    }
    case TCODK_UP:
    {
      // Move the cursor position up
      menuCursor--;
      if(menuCursor < 0) menuCursor = NGAME - 1;
      break;
    }
    case TCODK_ESCAPE:
    {
			menuCursor = 0;
			Transmit->Send(GameEngine(), MSG_GAMEMENU);
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
			switch(menuCursor)
      {
				case GAME_EQUIP:
				{
					Transmit->Send(GameEngine(), MSG_EQUIPINV);
					break;
				}
				case GAME_ITEMS:
				{
					Transmit->Send(GameEngine(), MSG_ITEMINV);
					break;
				}
				case GAME_EXIT:
				{
					//GameEngine()->Sound()->ToggleVolume(0.5f);
					Transmit->Send(GameEngine(), MSG_QUITGAME);
					status = false;
					break;
				}
				default: break;
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

  // Set colours for submenu
  menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
  menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
  menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
  menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);

  // Print frame and title
  menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Game Menu");
  menu->Con(STATE_02)->printFrame(1, 1, 15, 2*NGAME + 3, false, TCOD_BKGND_SET);
  menu->Con(STATE_02)->printFrame(1, 2*NGAME + 4, 15, h - 11, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

	x = 3, y = 12;
	menu->Con(STATE_02)->print(x, y, "%cHP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_02)->print(x + 4, y++, "%d/%d", GameEngine()->Player()->Stats()->HP(), GameEngine()->Player()->Stats()->HPMax());
	menu->Con(STATE_02)->print(x + 4, y++, "%d/%d", GameEngine()->Player()->HP(), GameEngine()->Player()->HPMax());

	menu->Con(STATE_02)->print(x, y, "%cMP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_02)->print(x + 4, y++, "%d/%d", GameEngine()->Player()->Stats()->MP(), GameEngine()->Player()->Stats()->MPMax());
	menu->Con(STATE_02)->print(x + 4, y++, "%d/%d", GameEngine()->Player()->MP(), GameEngine()->Player()->MPMax());

	menu->Con(STATE_02)->print(x, ++y, "%cStatus:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//for(int i = 0; i < 5; i++) if(GameEngin()->Player()->Health()->Status[i]) menu->Con(STATE_02)->print(x, ++y, "%s", GameEngin()->Player()->Health()->Name[i]);
	menu->Con(STATE_02)->print(x, ++y, "%s", "Healthy");

	//for(int i = 0; i < NSTATUS; i++)
	//{
	//	if(GameEngine()->Player()->Health()->Status[i])
	//	{
	//		menu->Con(STATE_02)->print(x, ++y, "%s", GameEngine()->Player()->Health()->StatusName[i]);
	//	}
	//}
	menu->Con(STATE_02)->print(x, ++y, "%s", "Burdened");
	menu->Con(STATE_02)->print(x, ++y, "%s", "Poisoned");
	menu->Con(STATE_02)->print(x, ++y, "%s", "Weakened");
	menu->Con(STATE_02)->print(x, ++y, "%s", "Sluggish");
	menu->Con(STATE_02)->print(x, ++y, "%s", "Feeble");
	menu->Con(STATE_02)->print(x, ++y, "%s", "Confused");

  // Compute the elapsed time in convenient units
  int nhours = static_cast<int>(GameEngine()->ElapsedTime()/(60.0f*60.0f));
  float time = GameEngine()->ElapsedTime() - (60.0f*60.0f)*static_cast<float>(nhours);
  int nmins = static_cast<int>(time/60.0f);
  int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

  x = 3, y = 24;
  menu->Con(STATE_02)->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_02)->print(x + 4, y++, "%d", GameEngine()->Player()->GP());
	menu->Con(STATE_02)->print(x + 4, y++, "%d", 100);
	y++;

  menu->Con(STATE_02)->print(x, y++, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  menu->Con(STATE_02)->print(x, y, "%02d:%02d:%02d", nhours, nmins, nsecs);

  // Print the menu options
  y = 1;
  for(int i = 0; i < NGAME; i++)
  {
    y += 2;
    if(i == menuCursor)
    {
      // Print each item
      menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
    }
    else
    {
      // Print each item
      menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    }
  }
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
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
  int ws = w - 17, hs = h - 2;

  // Game submenu screen
  menu->Con(STATE_03, new TCODConsole(ws, hs));

	switch(key.vk)
	{
		case TCODK_ESCAPE:
		{
			Transmit->Send(GameEngine(), MSG_EQUIPINV);
			break;
		}
		case TCODK_BACKSPACE:
  	{
    	// Save a screenshot
    	TCODSystem::saveScreenshot(NULL);
			break;
  	}
		case TCODK_CHAR:
		{
			switch(key.c)
			{
				case 'u':
				{
					//Transmit->Send(GameEngine(), MSG_EQUIPINVUSE);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

  // Set colours for submenu
  menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
  menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
  menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
  menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);

	menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

  // Equipment
  int x = 3, y = 3;
  menu->Con(STATE_03)->print(x, y, "%cEquipment%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

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
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
  int ws = w - 17, hs = h - 2;

  // Game submenu screen
  menu->Con(STATE_03, new TCODConsole(ws, hs));

	switch(key.vk)
	{
		case TCODK_ESCAPE:
		{
			Transmit->Send(GameEngine(), MSG_ITEMINV);
			break;
		}
		case TCODK_BACKSPACE:
  	{
    	// Save a screenshot
    	TCODSystem::saveScreenshot(NULL);
			break;
  	}
		case TCODK_CHAR:
		{
			switch(key.c)
			{
				case 'u':
				{
					//Transmit->Send(GameEngine(), MSG_ITEMINVUSE);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}

  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
  TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);

  // Set colours for submenu
  menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
  menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
  menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
  menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);

	menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

  // Equipment
  int x = 3, y = 3;
  menu->Con(STATE_03)->print(x, y, "%cItem Inventory%c", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

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
	bool status = true;
	switch(key.vk)
	{
		case TCODK_ESCAPE:
		{
			Transmit->Send(GameEngine(), MSG_ITEMSHOPMENU);
			break;
		}
		case TCODK_BACKSPACE:
  	{
    	// Save a screenshot
    	TCODSystem::saveScreenshot(NULL);
			break;
  	}
		case TCODK_CHAR:
		{
			switch(key.c)
			{
				case 'b':
				{
					Transmit->Send(GameEngine(), MSG_ITEMSHOPMENUBUY);
					break;
				}
				case 's':
				{
					Transmit->Send(GameEngine(), MSG_ITEMSHOPMENUSELL);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
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
	bool status = true;
	switch(key.vk)
	{
		case TCODK_ESCAPE:
		{
			Transmit->Send(GameEngine(), MSG_ITEMSHOPMENUBUY);
			break;
		}
		case TCODK_BACKSPACE:
  	{
    	// Save a screenshot
    	TCODSystem::saveScreenshot(NULL);
			break;
  	}
		case TCODK_CHAR:
		{
			switch(key.c)
			{
				case 'u':
				{
					//Transmit->Send(GameEngine(), MSG_ITEMPURCHASE);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
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
	bool status = true;
	switch(key.vk)
	{
		case TCODK_ESCAPE:
		{
			Transmit->Send(GameEngine(), MSG_ITEMSHOPMENUSELL);
			break;
		}
		case TCODK_BACKSPACE:
  	{
    	// Save a screenshot
    	TCODSystem::saveScreenshot(NULL);
			break;
  	}
		case TCODK_CHAR:
		{
			switch(key.c)
			{
				case 'u':
				{
					//Transmit->Send(GameEngine(), MSG_ITEMSALE);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
	return status;
}

void MenuItemShopSell::Render(MenuClass *menu)
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
	bool status = true;
	switch(key.vk)
	{
		case TCODK_ESCAPE:
		{
			Transmit->Send(GameEngine(), MSG_EQUIPSHOPMENU);
			break;
		}
		case TCODK_BACKSPACE:
  	{
    	// Save a screenshot
    	TCODSystem::saveScreenshot(NULL);
			break;
  	}
		case TCODK_CHAR:
		{
			switch(key.c)
			{
				case 'b':
				{
					Transmit->Send(GameEngine(), MSG_EQUIPSHOPMENUBUY);
					break;
				}
				case 's':
				{
					Transmit->Send(GameEngine(), MSG_EQUIPSHOPMENUSELL);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
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
	bool status = true;
	switch(key.vk)
	{
		case TCODK_ESCAPE:
		{
			Transmit->Send(GameEngine(), MSG_EQUIPSHOPMENUBUY);
			break;
		}
		case TCODK_BACKSPACE:
  	{
    	// Save a screenshot
    	TCODSystem::saveScreenshot(NULL);
			break;
  	}
		case TCODK_CHAR:
		{
			switch(key.c)
			{
				case 'u':
				{
					//Transmit->Send(GameEngine(), MSG_EQUIPPURCHASE);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
	return status;
}

void MenuEquipShopBuy::Render(MenuClass *menu)
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
	bool status = true;
	switch(key.vk)
	{
		case TCODK_ESCAPE:
		{
			Transmit->Send(GameEngine(), MSG_EQUIPSHOPMENUSELL);
			break;
		}
		case TCODK_BACKSPACE:
  	{
    	// Save a screenshot
    	TCODSystem::saveScreenshot(NULL);
			break;
  	}
		case TCODK_CHAR:
		{
			switch(key.c)
			{
				case 'u':
				{
					//Transmit->Send(GameEngine(), MSG_EQUIPSALE);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
	return status;
}

void MenuEquipShopSell::Render(MenuClass *menu)
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
  static int menuCursor = 0;
  bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
  int ws = w - 17, hs = h - 2, i = 0;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;
  int xstart = 3, ystart = 3, xend = ws - 6, yend = hs - 6;
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
      menuCursor = (menuCursor + 1) % NFERRY;
      break;
    }
    case TCODK_UP:
    {
      // Move the cursor position up
      menuCursor--;
      if(menuCursor < 0) menuCursor = NFERRY - 1;
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
      if(menuCursor == FERRY_TAKE)
      {
        //if(game.player.gp >= 25)
        //{
        //  game.player.gp -= 25;
        //  game.player.takeFerry(idprev);
				//	Transmit->Send(GameEngine(), MSG_FERRYTAKE);
        //}
      }
      else
      {
				menuCursor = 0;
				//GameEngine()->Sound()->ToggleVolume(0.5f);
				Transmit->Send(GameEngine(), MSG_FERRYMENU);
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

  // Set colours for submenu
  menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
  menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
  menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
  menu->Con(STATE_03)->setDefaultForeground(TCODColor::white);

  // Print frame and title
  menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Ferry");
  menu->Con(STATE_02)->printFrame(1, 1, 15, 2*NFERRY + 5, false, TCOD_BKGND_SET);
  menu->Con(STATE_02)->printFrame(1, 2*NFERRY + 6, 15, h - 11, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

  // Compute the elapsed time in convenient units
  int nhours = static_cast<int>(GameEngine()->ElapsedTime()/(60.0f*60.0f));
  float time = GameEngine()->ElapsedTime() - (60.0f*60.0f)*static_cast<float>(nhours);
  int nmins = static_cast<int>(time/60.0f);
  int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

  x = 3, y = 24;
  menu->Con(STATE_02)->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_02)->print(x + 4, y++, "%d", GameEngine()->Player()->GP());
	menu->Con(STATE_02)->print(x + 4, y++, "%d", 100);
	y++;

  menu->Con(STATE_02)->print(x, y, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  menu->Con(STATE_02)->print(x, ++y, "%02d:%02d:%02d", nhours, nmins, nsecs);

  // Print the menu options
  y = 1;
  for(int i = 0; i < NFERRY; i++)
  {
    y += 2;
    if(i == menuCursor)
    {
      // Print each item
      menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

      if(menuCursor == FERRY_TAKE)
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
  static int menuCursor = 0;
  bool status = true;
	int w = 3*DISPLAY_WIDTH/4 + 2, h = 3*DISPLAY_HEIGHT/4;
  int ws = w - 17, hs = h - 2, i = 0;
	int x = DISPLAY_WIDTH/2 - w/2, y = DISPLAY_HEIGHT/2 - h/2 + 3;
  int xstart = 3, ystart = 3, xend = ws - 6, yend = hs - 6;
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
      menuCursor = (menuCursor + 1) % NINN;
      break;
    }
    case TCODK_UP:
    {
      // Move the cursor position up
      menuCursor--;
      if(menuCursor < 0) menuCursor = NINN - 1;
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
      if(menuCursor == INN_STAY)
      {
        //if(GameEngine()->Player()->GP() >= 15)
        //{
          // Goodnight
          menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);
          menu->Con(STATE_03)->printRect(xstart, ystart, xend, yend, "Goodnight.");

          // Blit the inn submenu to the root console
          TCODConsole::blit(menu->Con(STATE_03), 0, 0, ws, hs, TCODConsole::root, x + 16, y + 1, 1.0f, 1.0f);

          //GameEngine()->Player()->DecreaseGP(15);

					Transmit->Send(GameEngine(), MSG_REST);
        //}
      }
      else
      {
				menuCursor = 0;
				//GameEngine()->Sound()->ToggleVolume(0.5f);
				Transmit->Send(GameEngine(), MSG_INNMENU);
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

  // Set colours for submenu
  menu->Con(STATE_03)->setAlignment(TCOD_LEFT);
  menu->Con(STATE_03)->setBackgroundFlag(TCOD_BKGND_SET);
  menu->Con(STATE_03)->setDefaultBackground(TCODColor::black);
  menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);

  // Print frame and title
  menu->Con(STATE_02)->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Inn");
  menu->Con(STATE_02)->printFrame(1, 1, 15, 2*(NINN + 1) + 3, false, TCOD_BKGND_SET);
  menu->Con(STATE_02)->printFrame(1, 2*(NINN + 1) + 4, 15, h - 11, false, TCOD_BKGND_SET);
	menu->Con(STATE_03)->printFrame(0, 0, ws, hs, false, TCOD_BKGND_SET);

  // Compute the elapsed time in convenient units
  int nhours = static_cast<int>(GameEngine()->ElapsedTime()/(60.0f*60.0f));
  float time = GameEngine()->ElapsedTime() - (60.0f*60.0f)*static_cast<float>(nhours);
  int nmins = static_cast<int>(time/60.0f);
  int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

  x = 3, y = 24;
  menu->Con(STATE_02)->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	//menu->Con(STATE_02)->print(x + 4, y++, "%d", GameEngine()->Player()->GP());
	menu->Con(STATE_02)->print(x + 4, y++, "%d", 100);
	y++;

  menu->Con(STATE_02)->print(x, y, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  menu->Con(STATE_02)->print(x, ++y, "%02d:%02d:%02d", nhours, nmins, nsecs);

  // Print the menu options
  y = NINN - 1;
  for(int i = 0; i < NINN; i++)
  {
    y += 2;
    if(i == menuCursor)
    {
      // Print each item
      menu->Con(STATE_02)->print(x, y, Options[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);

      if(menuCursor == INN_STAY)
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

	switch(key.vk)
	{
		case TCODK_ENTER:
		{
			Transmit->Send(GameEngine(), MSG_DEATH);
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

  // The death message screen
  menu->Con(STATE_02, new TCODConsole(w, h));

  // Delete the current save file
  if(TCODSystem::fileExists(SAVEGAME_FILENAME)) TCODSystem::deleteFile(SAVEGAME_FILENAME);

  // Set colours
  menu->Con(STATE_02)->setAlignment(TCOD_LEFT);
  menu->Con(STATE_02)->setBackgroundFlag(TCOD_BKGND_SET);
  menu->Con(STATE_02)->setDefaultBackground(TCODColor::black);
  menu->Con(STATE_02)->setDefaultForeground(TCODColor::white);
  TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::lighterYellow, TCODColor::black);
  TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::red, TCODColor::black);

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
	if(GameEngine()->Game()->InGame())
	{
  	// Render player hp bar
  	TCODConsole::root->setDefaultForeground(TCODColor::white);
  	TCODConsole::root->printEx(1, 1, TCOD_BKGND_NONE, TCOD_LEFT, "HP");
  	float hpfraction = static_cast<float>(GameEngine()->Player()->HP())/static_cast<float>(GameEngine()->Player()->HPMax());
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
  	float mpfraction = static_cast<float>(GameEngine()->Player()->MP())/static_cast<float>(GameEngine()->Player()->MPMax());
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

		// Other UI Stuff
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
