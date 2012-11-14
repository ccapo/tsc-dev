#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for MapIdle
//
//------------------------------------------------------------------------
MapIdle *MapIdle::Instance()
{
	static MapIdle instance;
	return &instance;
}

bool MapIdle::Update(MapClass *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void MapIdle::Render(MapClass *map){}

//------------------------------------------------------------------------
//
// Methods for MapWorld
//
//------------------------------------------------------------------------
MapWorld *MapWorld::Instance()
{
	static MapWorld instance;
	return &instance;
}

void MapWorld::Enter(MapClass *map)
{
	int w, h;
	map->Img(new TCODImage("data/img/worldmap_new.png"));
	map->ImgThumb(new TCODImage("data/img/worldmap_new.png"));
	map->ImgThumb()->getSize(&w, &h);
	map->ImgThumb()->scale(2*w/31, 2*h/31);
}

bool MapWorld::Update(MapClass *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void MapWorld::Render(MapClass *map)
{
  int w = 2*DISPLAY_WIDTH, h = 2*DISPLAY_HEIGHT;
  int w2 = DISPLAY_WIDTH/4 + 3, h2 = NMSGS + 4;
  int tx = 3*DISPLAY_WIDTH/4 - 1, ty = DISPLAY_HEIGHT + 4;

  map->Img()->blit2x(TCODConsole::root, 0, 3, 0, 0, w, h);
  map->ImgThumb()->blit2x(TCODConsole::root, tx, ty);
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
  TCODConsole::root->printFrame(tx - 1, ty - 1, w2, h2, false, TCOD_BKGND_SET, "World Map");
}

void MapWorld::Exit(MapClass *map){}

//------------------------------------------------------------------------
//
// Methods for MapTemple
//
//------------------------------------------------------------------------
MapTemple *MapTemple::Instance()
{
	static MapTemple instance;
	return &instance;
}

void MapTemple::Enter(MapClass *map)
{
	int w, h;
	map->Img(new TCODImage("data/img/templemap_new.png"));
	map->ImgThumb(new TCODImage("data/img/templemap_new.png"));
	map->ImgThumb()->getSize(&w, &h);
	map->ImgThumb()->scale(2*w/15, 2*h/15);

	// Create and add the Guardian to the Entity Manager
	EntityManager()->Add(new Npc(ENTITY_GUARDIAN, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 - 1));
}

bool MapTemple::Update(MapClass *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void MapTemple::Render(MapClass *map)
{
  int w = 2*DISPLAY_WIDTH, h = 2*DISPLAY_HEIGHT;
  int w2 = DISPLAY_WIDTH/4 + 3, h2 = NMSGS + 4;
  int tx = 3*DISPLAY_WIDTH/4 - 1, ty = DISPLAY_HEIGHT + 4;

  map->Img()->blit2x(TCODConsole::root, 0, 3, 0, 0, w, h);
  map->ImgThumb()->blit2x(TCODConsole::root, tx, ty);
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
  TCODConsole::root->printFrame(tx - 1, ty - 1, w2, h2, false, TCOD_BKGND_SET, "Temple Map");
}

void MapTemple::Exit(MapClass *map)
{
	// Remove all the Entities from the Entity Manager
	EntityManager()->RemoveAll();

	GameEngine()->Player()->ResetNextValidID();
}

//------------------------------------------------------------------------
//
// Methods for MapTown
//
//------------------------------------------------------------------------
MapTown *MapTown::Instance()
{
	static MapTown instance;
	return &instance;
}

void MapTown::Enter(MapClass *map)
{
	int w, h;
	map->Img(new TCODImage("data/img/townmap_new.png"));
	map->ImgThumb(new TCODImage("data/img/townmap_new.png"));
	map->ImgThumb()->getSize(&w, &h);
	map->ImgThumb()->scale(2*w/15, 2*h/15);

	// Now add all the Shopkeepers
	for(int i = 1; i <= 3; i++)
	{
		int nx = RNG->getInt(DISPLAY_WIDTH/2 - 10, DISPLAY_WIDTH/2 + 10);
		int ny = RNG->getInt(DISPLAY_HEIGHT/2 - 10, DISPLAY_HEIGHT/2 + 10);
	
		// Create and add a Shopkeeper to the Entity Manager
		EntityManager()->Add(new Npc(ENTITY_SHOPKEEPER, nx, ny));
	}

	// Now add all the Townspeople
	for(int i = 1; i <= 10; i++)
	{
		int nx = RNG->getInt(DISPLAY_WIDTH/2 - 10, DISPLAY_WIDTH/2 + 10);
		int ny = RNG->getInt(DISPLAY_HEIGHT/2 - 10, DISPLAY_HEIGHT/2 + 10);

		// Create and add a Townsperson to the Entity Manager
		EntityManager()->Add(new Npc(ENTITY_TOWNSPERSON, nx, ny));
	}
}

bool MapTown::Update(MapClass *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void MapTown::Render(MapClass *map)
{
  int w = 2*DISPLAY_WIDTH, h = 2*DISPLAY_HEIGHT;
  int w2 = DISPLAY_WIDTH/4 + 3, h2 = NMSGS + 4;
  int tx = 3*DISPLAY_WIDTH/4 - 1, ty = DISPLAY_HEIGHT + 4;

  map->Img()->blit2x(TCODConsole::root, 0, 3, 0, 0, w, h);
  map->ImgThumb()->blit2x(TCODConsole::root, tx, ty);
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
  TCODConsole::root->printFrame(tx - 1, ty - 1, w2, h2, false, TCOD_BKGND_SET, "Town Map");
}

void MapTown::Exit(MapClass *map)
{
	// Remove all the Entities from the Entity Manager
	EntityManager()->RemoveAll();

	GameEngine()->Player()->ResetNextValidID();
}

//------------------------------------------------------------------------
//
// Methods for MapCave
//
//------------------------------------------------------------------------
MapCave *MapCave::Instance()
{
	static MapCave instance;
	return &instance;
}

void MapCave::Enter(MapClass *map)
{
	int lx = RNG->getInt(DISPLAY_WIDTH/2 - 10, DISPLAY_WIDTH/2 + 10);
	int ly = RNG->getInt(DISPLAY_HEIGHT/2 - 10, DISPLAY_HEIGHT/2 + 10);

	// Create a Leader
	Leader *leader = new Leader(lx, ly);

	// Add Leader to Entity Manager
	EntityManager()->Add(leader);

	// Now handle its Commanders and Peons
	for(int i = 1; i <= 3; i++)
	{
		int cx = RNG->getInt(lx - 10, lx + 10);
		int cy = RNG->getInt(ly - 10, ly + 10);

		// Create a Commander
		Commander *commander = new Commander(cx, cy);
	
		// Add Commander to Entity Manager
		EntityManager()->Add(commander);
	
		// Add Commander to Leader's Commander list
		leader->AddSubordinate(commander);
	
		// Store the Leader ID for this Commander
		commander->Superior(leader);

		// Now handle the Commander's Peons
		for(int j = 1; j <= 3; j++)
		{
			int px = RNG->getInt(cx - 2, cx + 2);
			int py = RNG->getInt(cy - 2, cy + 2);

			// Create a Peon
			Peon *peon = new Peon(px, py);

			// Add Peon to Entity Manager
			EntityManager()->Add(peon);

			// Add Peon to Commander's Peon list
			commander->AddSubordinate(peon);

			// Store the Commander ID for this Peon
			peon->Superior(commander);
		}
	}
}

bool MapCave::Update(MapClass *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void MapCave::Render(MapClass *map)
{
  int w = 2*DISPLAY_WIDTH, h = 2*DISPLAY_HEIGHT;
  int w2 = DISPLAY_WIDTH/4 + 3, h2 = NMSGS + 4;
  int tx = 3*DISPLAY_WIDTH/4 - 1, ty = DISPLAY_HEIGHT + 4;

	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
  TCODConsole::root->printFrame(tx - 1, ty - 1, w2, h2, false, TCOD_BKGND_SET, "Cave Map");
}

void MapCave::Exit(MapClass *map)
{
	// Remove all the Commanders from the Leader's Subordinate List, as well
	// as all the Peons from each Commander's Subordinate List
	//leader->RemoveAll();

	// Remove all the Entities from the Entity Manager
	EntityManager()->RemoveAll();

	GameEngine()->Player()->ResetNextValidID();
}
