#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for PlayerIdle
//
//------------------------------------------------------------------------
PlayerIdle *PlayerIdle::Instance()
{
	static PlayerIdle instance;
	return &instance;
}
void PlayerIdle::Enter(PlayerClass *player){}
bool PlayerIdle::Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void PlayerIdle::Render(PlayerClass *player)
{
	if(Engine()->Game()->InGame())
	{
		TCODConsole::root->setChar(player->X(), player->Y() + 3, player->Sym());
		TCODConsole::root->setCharForeground(player->X(), player->Y() + 3, player->Colour());
	}
}

//------------------------------------------------------------------------
//
// Methods for PlayerIntro
//
//------------------------------------------------------------------------
PlayerIntro *PlayerIntro::Instance()
{
	static PlayerIntro instance;
	return &instance;
}

void PlayerIntro::Enter(PlayerClass *player){}
bool PlayerIntro::Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void PlayerIntro::Render(PlayerClass *player)
{
	TCODConsole::root->setChar(player->X(), player->Y() + 3, player->Sym());
	TCODConsole::root->setCharForeground(player->X(), player->Y() + 3, player->Colour());
}

//------------------------------------------------------------------------
//
// Methods for PlayerWorld
//
//------------------------------------------------------------------------
PlayerWorld *PlayerWorld::Instance()
{
	static PlayerWorld instance;
	return &instance;
}

void PlayerWorld::Enter(PlayerClass *player)
{
	// If the Player is not already located at the cave, change location to the cave
	if(player->Location() != LOCATION_WORLD) player->Location(LOCATION_WORLD);
}

bool PlayerWorld::Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	if(TCODConsole::isKeyPressed(TCODK_UP))
	{
		if(player->Y() <= 1) player->Y(1);
		//if(Engine()->Map()->IsWalkable(player->X(), player->Y() - 1))
		{
			//if(Engine()->Map()->GetEntityID(player->X(), player->Y() - 1) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->DecreaseY();
				player->Sym(CHAR_PLAYER_UP);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X(), player->Y() - 1);
			}
		}
	}
	if(TCODConsole::isKeyPressed(TCODK_DOWN))
	{
		if(player->Y() >= DISPLAY_HEIGHT - 2) player->Y(DISPLAY_HEIGHT - 2);
		//if(Engine()->Map()->IsWalkable(player->X(), player->Y() + 1))
		{
			//if(Engine()->Map()->GetEntityID(player->X(), player->Y() + 1) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->IncreaseY();
				player->Sym(CHAR_PLAYER_DOWN);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X(), player->Y() + 1);
			}
		}
	}
	if(TCODConsole::isKeyPressed(TCODK_LEFT))
	{
		if(player->X() <= 1) player->X(1);
		//if(Engine()->Map()->IsWalkable(player->X() - 1, player->Y()))
		{
			//if(Engine()->Map()->GetEntityID(player->X() - 1, player->Y()) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->DecreaseX();
				player->Sym(CHAR_PLAYER_LEFT);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X() - 1, player->Y());
			}
		}
	}
	if(TCODConsole::isKeyPressed(TCODK_RIGHT))
	{
		if(player->X() >= DISPLAY_WIDTH - 2) player->X(DISPLAY_WIDTH - 2);
		//if(Engine()->Map()->IsWalkable(player->X() + 1, player->Y()))
		{
			//if(Engine()->Map()->GetEntityID(player->X() + 1, player->Y()) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->IncreaseX();
				player->Sym(CHAR_PLAYER_RIGHT);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X() + 1, player->Y());
			}
		}
	}

	switch(key.vk)
	{
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_GAMEMENU);
			break;
		}
		case TCODK_CONTROL:
		{
			Engine()->Menu()->IncrementMagicID();
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
				case 'c':
				{
					Transmit->Send(Engine()->Menu(), MSG_MSGLOG, "Entered Caves");
					Transmit->Send(Engine(), MSG_ENTERCAVE);
					break;
				}
				case 't':
				{
					Transmit->Send(Engine()->Menu(), MSG_MSGLOG, "Entered Town");
					Transmit->Send(Engine(), MSG_ENTERTOWN);
					break;
				}
				case 's':
				{
					Transmit->Send(Engine()->Menu(), MSG_MSGLOG, "Entered Temple");
					Transmit->Send(Engine(), MSG_ENTERTEMPLE);
					break;
				}
				case '?':
				{
					Transmit->Send(Engine(), MSG_GAMEHELP);
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
	return status;
}

void PlayerWorld::Render(PlayerClass *player)
{
	TCODConsole::root->setChar(player->X(), player->Y() + 3, player->Sym());
	TCODConsole::root->setCharForeground(player->X(), player->Y() + 3, player->Colour());
}

//------------------------------------------------------------------------
//
// Methods for PlayerTemple
//
//------------------------------------------------------------------------
PlayerTemple *PlayerTemple::Instance()
{
	static PlayerTemple instance;
	return &instance;
}

void PlayerTemple::Enter(PlayerClass *player)
{
	// If the Player is not already located at the cave, change location to the cave
	if(player->Location() != LOCATION_TEMPLE) player->Location(LOCATION_TEMPLE);
}

bool PlayerTemple::Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	if(TCODConsole::isKeyPressed(TCODK_UP))
	{
		if(player->Y() <= 1) player->Y(1);
		//if(Engine()->Map()->IsWalkable(player->X(), player->Y() - 1))
		{
			//if(Engine()->Map()->GetEntityID(player->X(), player->Y() - 1) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->DecreaseY();
				player->Sym(CHAR_PLAYER_UP);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X(), player->Y() - 1);
			}
		}
	}
	if(TCODConsole::isKeyPressed(TCODK_DOWN))
	{
		if(player->Y() >= DISPLAY_HEIGHT - 2) player->Y(DISPLAY_HEIGHT - 2);
		//if(Engine()->Map()->IsWalkable(player->X(), player->Y() + 1))
		{
			//if(Engine()->Map()->GetEntityID(player->X(), player->Y() + 1) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->IncreaseY();
				player->Sym(CHAR_PLAYER_DOWN);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X(), player->Y() + 1);
			}
		}
	}
	if(TCODConsole::isKeyPressed(TCODK_LEFT))
	{
		if(player->X() <= 1) player->X(1);
		//if(Engine()->Map()->IsWalkable(player->X() - 1, player->Y()))
		{
			//if(Engine()->Map()->GetEntityID(player->X() - 1, player->Y()) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->DecreaseX();
				player->Sym(CHAR_PLAYER_LEFT);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X() - 1, player->Y());
			}
		}
	}
	if(TCODConsole::isKeyPressed(TCODK_RIGHT))
	{
		if(player->X() >= DISPLAY_WIDTH - 2) player->X(DISPLAY_WIDTH - 2);
		//if(Engine()->Map()->IsWalkable(player->X() + 1, player->Y()))
		{
			//if(Engine()->Map()->GetEntityID(player->X() + 1, player->Y()) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->IncreaseX();
				player->Sym(CHAR_PLAYER_RIGHT);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X() + 1, player->Y());
			}
		}
	}

	switch(key.vk)
	{
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_GAMEMENU);
			break;
		}
		case TCODK_CONTROL:
		{
			Engine()->Menu()->IncrementMagicID();
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
				case 'w':
				{
					Transmit->Send(Engine()->Menu(), MSG_MSGLOG, "Exited Temple");
					Transmit->Send(Engine(), MSG_SAVEGAME);
					break;
				}
				case '?':
				{
					Transmit->Send(Engine(), MSG_GAMEHELP);
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
	return status;
}

void PlayerTemple::Render(PlayerClass *player)
{
	TCODConsole::root->setChar(player->X(), player->Y() + 3, player->Sym());
	TCODConsole::root->setCharForeground(player->X(), player->Y() + 3, player->Colour());
}

//------------------------------------------------------------------------
//
// Methods for PlayerTown
//
//------------------------------------------------------------------------
PlayerTown *PlayerTown::Instance()
{
	static PlayerTown instance;
	return &instance;
}

void PlayerTown::Enter(PlayerClass *player)
{
	// If the Player is not already located at the cave, change location to the cave
	if(player->Location() != LOCATION_TOWN) player->Location(LOCATION_TOWN);
}

bool PlayerTown::Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	if(TCODConsole::isKeyPressed(TCODK_UP))
	{
		if(player->Y() <= 1) player->Y(1);
		//if(Engine()->Map()->IsWalkable(player->X(), player->Y() - 1))
		{
			//if(Engine()->Map()->GetEntityID(player->X(), player->Y() - 1) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->DecreaseY();
				player->Sym(CHAR_PLAYER_UP);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X(), player->Y() - 1);
			}
		}
	}
	if(TCODConsole::isKeyPressed(TCODK_DOWN))
	{
		if(player->Y() >= DISPLAY_HEIGHT - 2) player->Y(DISPLAY_HEIGHT - 2);
		//if(Engine()->Map()->IsWalkable(player->X(), player->Y() + 1))
		{
			//if(Engine()->Map()->GetEntityID(player->X(), player->Y() + 1) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->IncreaseY();
				player->Sym(CHAR_PLAYER_DOWN);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X(), player->Y() + 1);
			}
		}
	}
	if(TCODConsole::isKeyPressed(TCODK_LEFT))
	{
		if(player->X() <= 1) player->X(1);
		//if(Engine()->Map()->IsWalkable(player->X() - 1, player->Y()))
		{
			//if(Engine()->Map()->GetEntityID(player->X() - 1, player->Y()) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->DecreaseX();
				player->Sym(CHAR_PLAYER_LEFT);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X() - 1, player->Y());
			}
		}
	}
	if(TCODConsole::isKeyPressed(TCODK_RIGHT))
	{
		if(player->X() >= DISPLAY_WIDTH - 2) player->X(DISPLAY_WIDTH - 2);
		//if(Engine()->Map()->IsWalkable(player->X() + 1, player->Y()))
		{
			//if(Engine()->Map()->GetEntityID(player->X() + 1, player->Y()) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->IncreaseX();
				player->Sym(CHAR_PLAYER_RIGHT);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X() + 1, player->Y());
			}
		}
	}

	switch(key.vk)
	{
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_GAMEMENU);
			break;
		}
		case TCODK_CONTROL:
		{
			Engine()->Menu()->IncrementMagicID();
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
				case 'w':
				{
					Transmit->Send(Engine()->Menu(), MSG_MSGLOG, "Exited Town");
					Transmit->Send(Engine(), MSG_SAVEGAME);
					break;
				}
				case 'i':
				{
					Transmit->Send(Engine(), MSG_ITEMSHOP);
					break;
				}
				case 'e':
				{
					Transmit->Send(Engine(), MSG_EQUIPSHOP);
					break;
				}
				case 'n':
				{
					Transmit->Send(Engine(), MSG_INNMENU);
					break;
				}
				case 'f':
				{
					Transmit->Send(Engine(), MSG_FERRYMENU);
					break;
				}
				case '?':
				{
					Transmit->Send(Engine(), MSG_GAMEHELP);
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
	return status;
}

void PlayerTown::Render(PlayerClass *player)
{
	TCODConsole::root->setChar(player->X(), player->Y() + 3, player->Sym());
	TCODConsole::root->setCharForeground(player->X(), player->Y() + 3, player->Colour());
}

//------------------------------------------------------------------------
//
// Methods for PlayerCave
//
//------------------------------------------------------------------------
PlayerCave *PlayerCave::Instance()
{
	static PlayerCave instance;
	return &instance;
}

void PlayerCave::Enter(PlayerClass *player)
{
	// If the Player is not already located at the cave, change location to the cave
	if(player->Location() != LOCATION_CAVE) player->Location(LOCATION_CAVE);
}

bool PlayerCave::Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;

	// Check player's health
	if(player->HP() <= 0)
	{
		player->Sym(CHAR_SKULL);
		player->Colour(TCODColor::darkRed);
		Transmit->Send(Engine()->Menu(), MSG_MSGLOG, "You Died");
		Transmit->Send(Engine(), MSG_DEATH);
		key.vk = TCODK_NONE;
		key.c = 0;
		return status;
	}

	if(TCODConsole::isKeyPressed(TCODK_UP))
	{
		if(player->Y() <= 1) player->Y(1);
		//if(Engine()->Map()->IsWalkable(player->X(), player->Y() - 1))
		{
			//if(Engine()->Map()->GetEntityID(player->X(), player->Y() - 1) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->DecreaseY();
				player->Sym(CHAR_PLAYER_UP);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X(), player->Y() - 1);
			}
		}
	}
	if(TCODConsole::isKeyPressed(TCODK_DOWN))
	{
		if(player->Y() >= DISPLAY_HEIGHT - 2) player->Y(DISPLAY_HEIGHT - 2);
		//if(Engine()->Map()->IsWalkable(player->X(), player->Y() + 1))
		{
			//if(Engine()->Map()->GetEntityID(player->X(), player->Y() + 1) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->IncreaseY();
				player->Sym(CHAR_PLAYER_DOWN);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X(), player->Y() + 1);
			}
		}
	}
	if(TCODConsole::isKeyPressed(TCODK_LEFT))
	{

		if(player->X() <= 1) player->X(1);
		//if(Engine()->Map()->IsWalkable(player->X() - 1, player->Y()))
		{
			//if(Engine()->Map()->GetEntityID(player->X() - 1, player->Y()) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->DecreaseX();
				player->Sym(CHAR_PLAYER_LEFT);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X() - 1, player->Y());
			}
		}
	}
	if(TCODConsole::isKeyPressed(TCODK_RIGHT))
	{
		if(player->X() >= DISPLAY_WIDTH - 2) player->X(DISPLAY_WIDTH - 2);
		//if(Engine()->Map()->IsWalkable(player->X() + 1, player->Y()))
		{
			//if(Engine()->Map()->GetEntityID(player->X() + 1, player->Y()) < 0)
			{
				//Engine()->Map()->Visited(player->X(), player->Y(), false);
				player->IncreaseX();
				player->Sym(CHAR_PLAYER_RIGHT);
				//Engine()->Map()->Visited(player->X(), player->Y(), true);
				//Engine()->Map()->RecomputeFOV(true);
			}
			//else
			{
				// Attack Entity!
				//Engine()->Map()->AttackEntity(player->X() + 1, player->Y());
			}
		}
	}

	switch(key.vk)
	{
		case TCODK_INSERT:
		{
			player->DecreaseHP(1);
			break;
		}
		case TCODK_DELETE:
		{
			player->DecreaseMP(1);
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(Engine(), MSG_GAMEMENU);
			break;
		}
		case TCODK_CONTROL:
		{
			Engine()->Menu()->IncrementMagicID();
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
				case 'w':
				{
					Transmit->Send(Engine()->Menu(), MSG_MSGLOG, "Exited Caves");
					Transmit->Send(Engine(), MSG_SAVEGAME);
					break;
				}
				case '?':
				{
					Transmit->Send(Engine(), MSG_GAMEHELP);
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
	return status;
}

void PlayerCave::Render(PlayerClass *player)
{
	TCODConsole::root->setChar(player->X(), player->Y() + 3, player->Sym());
	TCODConsole::root->setCharForeground(player->X(), player->Y() + 3, player->Colour());
}

//------------------------------------------------------------------------
//
// Methods for PlayerRest
//
//------------------------------------------------------------------------
PlayerRest *PlayerRest::Instance()
{
	static PlayerRest instance;
	return &instance;
}

void PlayerRest::Enter(PlayerClass *player)
{
	// If the Player is not already located in a town, he must change his location to a town
	if(player->Location() != LOCATION_TOWN) player->Location(LOCATION_TOWN); 
}

bool PlayerRest::Update(PlayerClass *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	if(player->Injured())
	{
		player->ResetHP();
		player->ResetMP();
	}
	else	
	{
		Transmit->Send(Engine()->Menu(), MSG_MSGLOG, "Rested at Town Inn");
		Transmit->Send(Engine(), MSG_REST);
	}
	key.vk = TCODK_NONE;
	key.c = 0;
	return status;
}

void PlayerRest::Render(PlayerClass *player){}
