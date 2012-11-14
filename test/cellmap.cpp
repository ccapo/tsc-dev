#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "libtcod.hpp"

#define NX 120
#define NY 72

// Size of the window
#define SCREEN_WIDTH (NX)
#define SCREEN_HEIGHT (5*NY/4 + 2)

#define NITEMMAX 64
#define NCREATUREMAX 256
#define NCORPSEMAX 1024
#define NLOCATIONMAX 32

#define NCAVES 4

#define NMSGS 16

struct Item
{
	bool inUse;		// Item In Use flag
	int x, y;		// Item position
	TCODColor colour;	// Item Colour
	char sym;		// Item Symbol
	int cost;		// Item Cost
	int hp;			// Health Points
	int str, spd;		// Strength and Speed
	int wil, acu;		// Willpower and Acuity
	float mass;		// Item Mass

	Item();			// The Default The Constructor
};

// The class that holds information about each map cell
struct Stats
{
	int hpmax;		// Max. Health Points
	int str, spd;		// Strength and Speed
	int ap, app;		// Physical Attack Power and Percentage
	int dp, dpp;		// Physical Defense Power and Percentage
	int mpmax;		// Max. Magic Points
	int wil, acu;		// Willpower and Acuity
	int map, mapp;		// Magic Attack Power and Percentage
	int mdp, mdpp;		// Magic Defense Power and Percentage

	Stats();		// The Default Stats Constructor
};

struct Creature
{
	bool inUse;								// Creature's In Use flag
	Stats base;								// Creature's Base Stats
	Stats stats;								// Creature's Current Stats
	int hp;									// Creature's Current Number of Health Points
	int mp;									// Creature's Current Number of Magic Points
	int x, y;								// Creature Position
	TCODColor colour;							// Creature Colour
	char sym;								// Creature Symbol
	float walkTimer;							// Creature's Walk Timer

	Creature();								// The Default Creature Constructor
	//void updateStats();							// Update Creature stats
	//void updateStatus();							// Update Creature status
	//void update(float elapsed, TCOD_key_t key, TCOD_mouse_t mouse);	// Update Creature
	//void takeDamage(float elapsed);					// Creature Take Damage
};

struct Corpse
{
	bool inUse;		// Corpse In Use flag
	int x, y;		// Corpse Position
	TCODColor colour;	// Corpse Colour
	char sym;		// Corpse Symbol
	Item token;		// Corpse Token

	Corpse();		// The Default Corpse Constructor
};

struct Location
{

	int x, y;		// Location Position
	TCODColor colour;	// Location Colour
	char sym;		// Location Symbol
	bool inUse;		// Location In Use flag

	Location();		// The Default Location Constructor
};

struct Cell
{
	int itemID;		// Item ID
	int creatureID;		// Creature ID
	int corpseID;		// Corpse ID
	int locationID;		// Location ID

	Cell();			// The Default Cell Constructor
};

struct SubCell
{
	TCODColor baseColour;		// Base terrain colour
	TCODColor finalColour;		// Modified colour (weather/torchlight), ready to be displayed
	bool isWater;			// Used to indicate whether the cell contains water
	bool isLava;			// Used to indicate whether the cell contains lava
	bool isExplored;		// Used to indicate whether the player has seen/visited this cell

	SubCell();			// The Default SubCell Constructor
};

class Cave
{
	public:
	Cell cells[NX*NY];
	SubCell subcells[4*NX*NY];

	TCODMap *map;
	TCODMap *fov;

	TCODImage *img;
	TCODImage *img_thumb;

	int nitems, ncreatures, ncorpses, nlocations;
	Item items[NITEMMAX];
	Creature creatures[NCREATUREMAX];
	Corpse corpses[NCORPSEMAX];
	Location locations[NLOCATIONMAX];

	int upx, upy, downx, downy;

	Cave();			// The Default Cave Constructor

	void generateHeightMap(TCODHeightMap *hmap);
	void generateCave(int lvl);

	inline bool isFovWalkable(int x, int y) { return fov->isWalkable(x, y); }
	inline bool isFovTransparent(int x, int y) { return fov->isTransparent(x, y); }

	inline int getItemID(int x, int y) { return cells[x + NX*y].itemID; }
	inline int getCreatureID(int x, int y) { return cells[x + NX*y].creatureID; }
	inline int getCorpseID(int x, int y) { return cells[x + NX*y].corpseID; }
	inline int getLocationID(int x, int y) { return cells[x + NX*y].locationID; }
	inline bool hasToken(int x, int y) { if(getCorpseID(x, y) >= 0) return corpses[getCorpseID(x, y)].token.inUse; else return false; }

	void addItem(int x, int y);
	void removeItem(int x, int y);

	void addCreature(int x, int y);
	void removeCreature(int x, int y);

	void addCorpse(int x, int y);
	void removeCorpse(int x, int y);
	void removeToken(int x, int y);

	void addLocation(int x, int y, TCODColor colour, char sym);
};

class Player
{
	public:
	Stats base;								// Player's Base Stats
	Stats stats;								// Player's Current Stats
	int hp;									// Player's Current Number of Health Points
	int mp;									// Player's Current Number of Magic Points
	int x, y;								// Player Position
	TCODColor colour;							// Player Colour
	char sym;								// Player Symbol
	int gp;									// Player Gold Points
	float time;								// Elapsed Time
	float walkTimer;							// Player's Walk Timer
	float magicTimer;							// Player's Walk Timer
	TCODPath *path;

	Player();								// The Default Player Constructor
	//void updateStats();							// Update Player stats
	//void updateStatus();							// Update Player status
	//void takeDamage(float elapsed);					// Player Take Damage
	void update(float elapsed, TCOD_key_t key, TCOD_mouse_t mouse);		// Update Player
	void render(void);							// Render Player
};

class Game
{
	public:
	uint32 seed;
	TCODRandom *rng;
	TCODNoise *terrain;

	int level;								// Current level

	Cave caves[NCAVES];							// Cave objects
	Player player;								// Player object

	Game();									// The Default Game Constructor

	void update(float elapsed, TCOD_key_t key, TCOD_mouse_t mouse);		// Update Game
	void render(void);							// Render Game
};

Game game;

Item::Item(): inUse(false), x(0), y(0), colour(TCODColor::blue), sym('#'), cost(10), hp(5), str(2), spd(2), wil(2), acu(2), mass(1.0f) {}

Stats::Stats(): hpmax(10), str(2), spd(12), ap(4), app(50), dp(4), dpp(50), mpmax(5), wil(2), acu(2), map(2), mapp(25), mdp(2), mdpp(25) {}

Creature::Creature(): inUse(false), hp(10), mp(5), x(0), y(0), colour(TCODColor::yellow), sym('m'), walkTimer(0.0f) {}

Corpse::Corpse(): inUse(false), x(0), y(0), colour(TCODColor::red), sym('%') {}

Location::Location(): x(0), y(0), colour(TCODColor::white), sym(TCOD_CHAR_RADIO_SET), inUse(false) {}

Cell::Cell(): itemID(-1), creatureID(-1), corpseID(-1), locationID(-1) {}

SubCell::SubCell(): baseColour(TCODColor::black), finalColour(TCODColor::white), isWater(false), isLava(false), isExplored(false) {}

Cave::Cave(): nitems(0), ncreatures(0), ncorpses(0), nlocations(0), upx(-1), upy(-1), downx(-1), downy(-1)
{
	map = new TCODMap(NX, NY);
	fov = new TCODMap(2*NX, 2*NY);

	img = new TCODImage(2*NX, 2*NY);
	img_thumb = new TCODImage(2*NX/4, 2*NY/4);
}

void Cave::addItem(int x, int y)
{
	for(int i = 0; i < nitems; i++)
	{
		if(!items[i].inUse)
		{
			items[i].inUse = true;
			items[i].x = x;
			items[i].y = y;
			cells[x + NX*y].itemID = i;
			break;
		}
	}
}

void Cave::removeItem(int x, int y)
{
	int id = cells[x + NX*y].itemID;
	items[id].inUse = false;
	cells[x + NX*y].itemID = -1;
}

void Cave::addCreature(int x, int y)
{
	for(int i = 0; i < ncreatures; i++)
	{
		if(!creatures[i].inUse)
		{
			creatures[i].inUse = true;
			creatures[i].x = x;
			creatures[i].y = y;
			cells[x + NX*y].creatureID = i;
			break;
		}
	}
}

void Cave::removeCreature(int x, int y)
{
	int id = cells[x + NX*y].creatureID;
	creatures[id].inUse = false;
	cells[x + NX*y].creatureID = -1;
}

void Cave::addCorpse(int x, int y)
{
	corpses[ncorpses].inUse = true;
	corpses[ncorpses].x = x;
	corpses[ncorpses].y = y;
	cells[x + NX*y].corpseID = ncorpses;
	corpses[ncorpses].token.inUse = true;
	ncorpses++;
}

void Cave::removeCorpse(int x, int y)
{
	int id = cells[x + NX*y].corpseID;
	corpses[id].inUse = false;
	cells[x + NX*y].corpseID = -1;
}

void Cave::removeToken(int x, int y)
{
	int id = cells[x + NX*y].corpseID;
	if(id >= 0 && corpses[id].token.inUse) corpses[id].token.inUse = false;
}

void Cave::addLocation(int x, int y, TCODColor colour, char sym)
{
	for(int i = 0; i < nlocations; i++)
	{
		if(!locations[i].inUse)
		{
			locations[i].inUse = true;
			locations[i].x = x;
			locations[i].y = y;
			locations[i].colour = colour;
			locations[i].sym = sym;
			cells[x + NX*y].locationID = i;
			break;
		}
	}
}

// Method for making the heightmap
void Cave::generateHeightMap(TCODHeightMap *hmap)
{
	hmap->clear();
	//addHill(hmap, 600, 16.0*2*NX/400, 0.7, 0.3);
	hmap->normalize();
	//				mulx		muly		addx	addy	octaves	delta	scale
	hmap->addFbm(game.terrain,	2.20*2*NX/800,	2.20*2*NY/800,	-20.0f,	15.0f,	32.0f,	0.0f,	2.0f);
	hmap->normalize(-1.0f,1.0f);

	hmap->add(-0.1f);
	hmap->clamp(-1.0f,1.0f);
	hmap->normalize(-1.0f,1.0f);
}

// Method for constructing the heightmap
void Cave::generateCave(int lvl)
{
	game.seed++;
	game.rng = new TCODRandom(game.seed, TCOD_RNG_CMWC);
	game.terrain = new TCODNoise(2, game.rng);

	TCODHeightMap *hmap = new TCODHeightMap(2*NX, 2*NY);
	generateHeightMap(hmap);

	nitems = 4 + (int)((NITEMMAX - 4)*((float)(lvl)/(float)(NCAVES)));
	ncreatures = 16 + (int)((NCREATUREMAX - 16)*((float)(lvl)/(float)(NCAVES)));
	nlocations = 2;

	for(int x = 0; x < 2*NX; x++)
	{
		for(int y = 0; y < 2*NY; y++)
		{
			int offset = x + 2*NX*y;
			float h = hmap->getValue(x, y);

			if(h >= 0.5f)
			{
				subcells[offset].baseColour = TCODColor::lerp(TCODColor(63,127,31), TCODColor(31,63,31), (h - 0.5f)/(1.0f - 0.5f));
				fov->setProperties(x, y, true, true);
			}
			else if(h >= 0.1f)
			{
				subcells[offset].baseColour = TCODColor::lerp(TCODColor(191,191,159), TCODColor(63,127,31), (h - 0.1f)/(0.5f - 0.1f));
				fov->setProperties(x, y, true, true);
			}
			else if(h >= 0.0f)
			{
				subcells[offset].baseColour = TCODColor::lerp(TCODColor(111,127,159), TCODColor(191,191,159), (h - 0.0f)/(0.1f - 0.0f));
				fov->setProperties(x, y, true, false);
			}
			else
			{
				subcells[offset].baseColour = TCODColor::lerp(TCODColor(111,127,159), TCODColor(47,47,64), ABS(h));
				subcells[offset].isWater = true;
				fov->setProperties(x, y, true, false);
			}
			img->putPixel(x, y, subcells[offset].baseColour);
			//img_thumb->putPixel(x/4, y/4, subcells[offset].baseColour);
		}
	}

	// Set walk and transparent information in the normal resolution map
	for(int x = 0; x < NX; x++)
	{
		for(int y = 0; y < NY; y++)
		{
			bool trans = true, walk = true;
			if(!fov->isTransparent(2*x    , 2*y    )) trans = false;
			if(!fov->isTransparent(2*x + 1, 2*y    )) trans = false;
			if(!fov->isTransparent(2*x    , 2*y + 1)) trans = false;
			if(!fov->isTransparent(2*x + 1, 2*y + 1)) trans = false;
			if(!fov->isWalkable(2*x    , 2*y    )) walk = false;
			if(!fov->isWalkable(2*x + 1, 2*y    )) walk = false;
			if(!fov->isWalkable(2*x    , 2*y + 1)) walk = false;
			if(!fov->isWalkable(2*x + 1, 2*y + 1)) walk = false;
			map->setProperties(x, y, trans, walk);
		}
	}

	// Assign the location of the up and down stairs, ensuring they are sufficiently far apart
	int px = NX/2, py = NY/2;
	upx = px; upy = py;
	addLocation(upx, upy, TCODColor::lightGrey, TCOD_CHAR_ARROW2_N);

	downx = game.rng->getInt(0, NX - 1);
	downy = game.rng->getInt(0, NY - 1);
	while(!(map->isWalkable(downx, downy) && pow(downx - px, 2) + pow(downy - py, 2) >= 100))
	{
		downx = game.rng->getInt(0, NX - 1);
		downy = game.rng->getInt(0, NY - 1);
	}
	addLocation(downx, downy, TCODColor::lightGrey, TCOD_CHAR_ARROW2_S);

	for(int i = 0; i < ncreatures; i++)
	{
		int qx = game.rng->getInt(0, NX - 1);
		int qy = game.rng->getInt(0, NY - 1);
		while(!(map->isWalkable(qx, qy) && pow(qx - px, 2) + pow(qy - py, 2) >= 100))
		{
			qx = game.rng->getInt(0, NX - 1);
			qy = game.rng->getInt(0, NY - 1);
		}
		addCreature(qx, qy);
	}

	for(int i = 0; i < nitems; i++)
	{
		int qx = game.rng->getInt(0, NX - 1);
		int qy = game.rng->getInt(0, NY - 1);
		while(!(map->isWalkable(qx, qy) && pow(qx - px, 2) + pow(qy - py, 2) >= 100))
		{
			qx = game.rng->getInt(0, NX - 1);
			qy = game.rng->getInt(0, NY - 1);
		}
		addItem(qx, qy);
	}

	delete hmap;
	hmap = NULL;

	img->save("celltest.png");
	//img_thumb->save("celltest_thumb.png");
}

Player::Player(): hp(10), mp(5), x(NX/2), y(NY/2), colour(TCODColor::white), sym('@'), gp(0), time(0.0f), walkTimer(0.0f), magicTimer(0.0f) {}

void Player::update(float elapsed, TCOD_key_t key, TCOD_mouse_t mouse)
{
	Cave *cave = &game.caves[game.level];

	if(cave->getItemID(x, y) >= 0)
	{
		printf("You found an item!\n");
		cave->removeItem(x, y);
	}

	if(cave->getCorpseID(x, y) >= 0)
	{
		if(cave->hasToken(x, y))
		{
			printf("You found a token!\n");
			cave->removeToken(x, y);
		}
	}

	if(walkTimer*(float)stats.spd >= 1.0f)
	{
		walkTimer = 0.0f;

		//if(!path->isEmpty())
		//{
		//	int px, py;
		//	if(path->walk(&px, &py, true))
		//	{
		//		TCODConsole::root->putChar(x, y, ' ', TCOD_BKGND_NONE);
		//		x = px; y = py;
		//		TCODConsole::root->putChar(x, y, sym, TCOD_BKGND_NONE);
		//	}
		//}

		switch(key.vk)
		{
			case TCODK_UP:
			{
				if(y <= 1) y = 1;
				if(cave->map->isWalkable(x, y - 1))
				{
					int id = cave->getCreatureID(x, y - 1);
					if(id < 0)
					{
						TCODConsole::root->putChar(x, y, ' ', TCOD_BKGND_NONE);
						y--;
						TCODConsole::root->putChar(x, y, sym, TCOD_BKGND_NONE);
						//recomputeFov = true;
					}
					else
					{
						// Attack!
						if(cave->creatures[id].hp > 0)
						{
							cave->creatures[id].hp--;
							printf("Attack Creature: %d\n", cave->creatures[id].hp);

							if(cave->creatures[id].hp <= 0)
							{
								printf("Creature Died!\n");
								cave->removeCreature(x, y - 1);
								cave->addCorpse(x, y - 1);
							}
						}
					}
				}
				break;
			}
			case TCODK_DOWN:
			{
				if(y >= NY - 2) y = NY - 2;
				if(cave->map->isWalkable(x, y + 1))
				{
					int id = cave->getCreatureID(x, y + 1);
					if(id < 0)
					{
						TCODConsole::root->putChar(x, y, ' ', TCOD_BKGND_NONE);
						y++;
						TCODConsole::root->putChar(x, y, sym, TCOD_BKGND_NONE);
						//recomputeFov = true;
					}
					else
					{
						// Attack!
						if(cave->creatures[id].hp > 0)
						{
							cave->creatures[id].hp--;
							printf("Attack Creature: %d\n", cave->creatures[id].hp);

							if(cave->creatures[id].hp <= 0)
							{
								printf("Creature Died!\n");
								cave->removeCreature(x, y + 1);
								cave->addCorpse(x, y + 1);
							}
						}
					}
				}
				break;
			}
			case TCODK_LEFT:
			{
				if(x <= 1) x = 1;
				if(cave->map->isWalkable(x - 1, y))
				{
					int id = cave->getCreatureID(x - 1, y);
					if(id < 0)
					{
						TCODConsole::root->putChar(x, y, ' ', TCOD_BKGND_NONE);
						x--;
						TCODConsole::root->putChar(x, y, sym, TCOD_BKGND_NONE);
						//recomputeFov = true;
					}
					else
					{
						// Attack!
						if(cave->creatures[id].hp > 0)
						{
							cave->creatures[id].hp--;
							printf("Attack Creature: %d\n", cave->creatures[id].hp);

							if(cave->creatures[id].hp <= 0)
							{
								printf("Creature Died!\n");
								cave->removeCreature(x - 1, y);
								cave->addCorpse(x - 1, y);
							}
						}
					}
				}
				break;
			}
			case TCODK_RIGHT:
			{
				if(x >= NX - 2) x = NX - 2;
				if(cave->map->isWalkable(x + 1, y))
				{
					int id = cave->getCreatureID(x + 1, y);
					if(id < 0)
					{
						TCODConsole::root->putChar(x, y, ' ', TCOD_BKGND_NONE);
						x++;
						TCODConsole::root->putChar(x, y, sym, TCOD_BKGND_NONE);
						//recomputeFov = true;
					}
					else
					{
						// Attack!
						if(cave->creatures[id].hp > 0)
						{
							cave->creatures[id].hp--;
							printf("Attack Creature: %d\n", cave->creatures[id].hp);
					
							if(cave->creatures[id].hp <= 0)
							{
								printf("Creature Died!\n");
								cave->removeCreature(x + 1, y);
								cave->addCorpse(x + 1, y);
							}
						}
					}
				}
				break;
			}
			default: break;
		}
	}
	else
	{
		walkTimer += elapsed;
	}

	if(key.vk == TCODK_ENTER)
	{
		if(x == cave->downx && y == cave->downy)
		{
			game.level++;
			if(game.level >= NCAVES) game.level = 0;
			cave = &game.caves[game.level];
			x = cave->upx; y = cave->upy;
			//path = new TCODPath(cave->map);
			//path->compute(cave->upx, cave->upy, cave->downx, cave->downy);
		}
		else if(x == cave->upx && y == cave->upy)
		{
			game.level--;
			if(game.level < 0) game.level = NCAVES - 1;
			cave = &game.caves[game.level];
			x = cave->downx; y = cave->downy;
			//path = new TCODPath(cave->map);
			//path->compute(cave->downx, cave->downy, cave->upx, cave->upy);
		}
	}
}

void Player::render(void)
{
	TCODConsole::root->setDefaultForeground(colour);
	TCODConsole::root->putChar(x, y, sym, TCOD_BKGND_NONE);
}

Game::Game(): level(0)
{
	seed = (uint32)time(NULL);
	rng = TCODRandom::getInstance();
	terrain = new TCODNoise(2, rng);
}

void Game::update(float elapsed, TCOD_key_t key, TCOD_mouse_t mouse)
{
	player.update(elapsed, key, mouse);
}

void Game::render(void)
{
	Cave *cave = &caves[level];

	TCODConsole::root->clear();

	cave->img->save("celltest.png");
	cave->img->blit2x(TCODConsole::root, 0, 0);

	cave->img_thumb = new TCODImage("celltest.png");
	cave->img_thumb->scale(2*NX/4, 2*NY/4);
	cave->img_thumb->putPixel(2*player.x/4, 2*player.y/4, player.colour);
	cave->img_thumb->blit2x(TCODConsole::root, 3*NX/4 - 1, NY + 1);

	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->printFrame(0, NY, 3*NX/4 - 2, NMSGS + 4, false, TCOD_BKGND_SET, "Message Log");
	TCODConsole::root->printFrame(3*NX/4 - 2, NY, NX/4 + 2, NMSGS + 4, false, TCOD_BKGND_SET, "Level %d", level + 1);

	for(int i = 0; i < cave->ncorpses; i++)
	{
		if(cave->corpses[i].inUse)
		{
			TCODConsole::root->setDefaultForeground(cave->corpses[i].colour);
			TCODConsole::root->putChar(cave->corpses[i].x, cave->corpses[i].y, cave->corpses[i].sym, TCOD_BKGND_NONE);
		}
	}
	for(int i = 0; i < cave->nitems; i++)
	{
		if(cave->items[i].inUse)
		{
			TCODConsole::root->setDefaultForeground(cave->items[i].colour);
			TCODConsole::root->putChar(cave->items[i].x, cave->items[i].y, cave->items[i].sym, TCOD_BKGND_NONE);
		}
	}
	for(int i = 0; i < cave->ncreatures; i++)
	{
		if(cave->creatures[i].inUse)
		{
			TCODConsole::root->setDefaultForeground(cave->creatures[i].colour);
			TCODConsole::root->putChar(cave->creatures[i].x, cave->creatures[i].y, cave->creatures[i].sym, TCOD_BKGND_NONE);
		}
	}
	for(int i = 0; i < cave->nlocations; i++)
	{
		if(cave->locations[i].inUse)
		{
			TCODConsole::root->setDefaultForeground(cave->locations[i].colour);
			TCODConsole::root->putChar(cave->locations[i].x, cave->locations[i].y, cave->locations[i].sym, TCOD_BKGND_NONE);
		}
	}

	player.render();
}

int main(void)
{
	//const char *font = "data/fonts/arial4x4.png";
	const char *font = "data/fonts/arial8x8.png";
	int fontFlags = TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE;
	int nCol = 32, nRow = 8, maxFps = 24;
	int initialDelay = 100, interval = 10;
	TCOD_key_t key = TCODConsole::checkForKeypress(TCOD_KEY_PRESSED);
	TCOD_mouse_t mouse = TCODMouse::getStatus();

	TCODConsole::setCustomFont(font, fontFlags, nCol, nRow);
	TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "Cell Test", false);
	TCODSystem::setFps(maxFps);
	TCODConsole::setKeyboardRepeat(initialDelay, interval);

	for(int i = 0; i < NCAVES; i++) game.caves[i].generateCave(i);

	while(!TCODConsole::isWindowClosed())
	{
		game.update(TCODSystem::getLastFrameLength(), key, mouse);

		game.render();

		TCODConsole::root->flush();

		// Select the response for each keypress
		key = TCODConsole::checkForKeypress(TCOD_KEY_PRESSED);
		mouse = TCODMouse::getStatus();

		if(key.vk == TCODK_ESCAPE) break;
	}

	return 1;
}
