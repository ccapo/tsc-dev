#include "libtcod.hpp"
#include <stdio.h>
#include <math.h>
#include <time.h>

// Size of the console
#define SCREEN_WIDTH (3*80/2)
#define SCREEN_HEIGHT (3*48/2)

// Size of the height map
#define WIDTH (2*SCREEN_WIDTH)
#define HEIGHT (2*SCREEN_HEIGHT)

//uint32 seed = (uint32)time(NULL);
//uint32 seed = 1327465929U;
uint32 seed_town = 1327466111U; // town
uint32 seed_temple = 1327466445U; // temple

TCODRandom *rnd;
TCODNoise *noise;

// Height map values
static const float hWater = 0.0f;
static const float hSand = 0.1f;
static const float hGrass = 0.5f;
static const float hMax = 1.0f;

// Colour map values
static const int MAX_COLOR_KEY = 5;
static const TCODColor keyColor[MAX_COLOR_KEY] = {
	TCODColor(47,47,64),		// 0, deep water
	TCODColor(111,127,159),		// 1, water-sand transition
	TCODColor(191,191,159),		// 2, sand
	TCODColor(63,127,31),		// 3, sand-grass transition
	TCODColor(31,63,31)		// 4, grass
};

void addHill(TCODHeightMap *hm, int nbHill, float baseRadius, float radiusVar, float height)
{
	for (int i = 0; i < nbHill; i++)
	{
		float hillMinRadius = baseRadius*(1.0f - radiusVar);
		float hillMaxRadius = baseRadius*(1.0f + radiusVar);
		float radius = rnd->getFloat(hillMinRadius, hillMaxRadius);
		float theta = rnd->getFloat(0.0f, 6.283185f); // between 0 and 2*Pi
		float dist = rnd->getFloat(0.0f, (float)MIN(WIDTH,HEIGHT)/2 - radius);
		int xh = (int)(WIDTH/2 + cos(theta)*dist);
		int yh = (int)(HEIGHT/2 + sin(theta)*dist);
		hm->addHill((float)xh, (float)yh, radius, height);
	}
}

// function building the town heightmap
void buildTownMap(TCODHeightMap *hm)
{
	hm->clear();
	//			mulx			muly	addx	addy	octaves	delta	scale
	hm->addFbm(noise,	2.20*WIDTH/800,	2.20*WIDTH/800,	-20.0f,	15.0f,	32.0f,	0.0f,	2.0f);
	hm->normalize(hWater,hMax);
}

// function building the temple heightmap
void buildTempleMap(TCODHeightMap *hm)
{
	hm->clear();
	addHill(hm,600,16.0*WIDTH/400,0.7,0.3);
	hm->normalize();
	//			mulx			muly	addx	addy	octaves	delta	scale
	hm->addFbm(noise,	2.20*WIDTH/800,	2.20*WIDTH/800,	-20.0f,	15.0f,	32.0f,	0.0f,	2.0f);
	hm->normalize(hWater,hMax);

	hm->add(-0.1f);
	hm->clamp(hWater,hMax);
	hm->normalize(hWater,hMax);
}

// test code to print the heightmap
// to compile this file on Linux :
//  g++ hm.cpp -o hm -I include/ -L lib/ -ltcod -ltcodxx -lm -Wl,-rpath=lib/
// to compile this file on Windows/mingw32 :
//  g++ hm.cpp -o hm.exe -I include/ -L lib -ltcod-mingw

int main(int argc, char *argv[])
{
	TCODHeightMap *hm = new TCODHeightMap(WIDTH, HEIGHT);
	TCODImage *imgMap = new TCODImage(WIDTH, HEIGHT);
	TCODImage *imgMap_small = new TCODImage(WIDTH/4, HEIGHT/4);

	//const char *font = "data/fonts/arial4x4.png";
	const char *font = "data/fonts/arial8x8.png";
	//const char *font = "data/fonts/dundalk12x12_gs_tc.png";
	int fontFlags = TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE;
	int nCol = 32, nRow = 8;

	//TCOD_key_t key = {TCODK_NONE,0};
	TCODColor c;

	TCODConsole::setCustomFont(font, fontFlags, nCol, nRow);
	TCODConsole::initRoot(SCREEN_WIDTH, 5*SCREEN_HEIGHT/4, "World Map", false);

//	while(true)
//	{
//		seed_town++;
		rnd = new TCODRandom(seed_town,TCOD_RNG_CMWC);
		noise = new TCODNoise(2,rnd);
		buildTownMap(hm);

		for(int x = 0; x < WIDTH; x++)
		{
			for(int y = 0; y < HEIGHT; y++)
			{
				float h = hm->getValue(x, y);

				if(h >= hGrass)
				{
					c = TCODColor::lerp(keyColor[3], keyColor[4], (h - hGrass)/(hMax - hGrass));
				}
				else if(h >= hSand)
				{
					c = TCODColor::lerp(keyColor[2], keyColor[3], (h - hSand)/(hGrass - hSand));
				}
				else if(h >= hWater)
				{
					c = TCODColor::lerp(keyColor[1], keyColor[2], (h - hWater)/(hSand - hWater));
				}
				else
				{
					c = TCODColor::lerp(keyColor[1], keyColor[0], ABS(h));
				}
				imgMap->putPixel(x, y, c);
				imgMap_small->putPixel(x/4, y/4, c);
			}
		}

		imgMap->save("townmap.png");
		imgMap->blit2x(TCODConsole::root, 0, 0);

		imgMap_small->save("townmap_small.png");
		imgMap_small->blit2x(TCODConsole::root, 3*SCREEN_WIDTH/4, SCREEN_HEIGHT);

		TCODConsole::root->flush();

		printf("%u\n", seed_temple);

		TCODConsole::waitForKeypress(true);
//		key = TCODConsole::waitForKeypress(true);
//		if(key.vk == TCODK_BACKSPACE) break;
//	}

//	while(true)
//	{
//		seed_temple++;
		rnd = new TCODRandom(seed_temple,TCOD_RNG_CMWC);
		noise = new TCODNoise(2,rnd);
		buildTempleMap(hm);

		for(int x = 0; x < WIDTH; x++)
		{
			for(int y = 0; y < HEIGHT; y++)
			{
				float h = hm->getValue(x, y);

				if(h >= hGrass)
				{
					c = TCODColor::lerp(keyColor[3], keyColor[4], (h - hGrass)/(hMax - hGrass));
				}
				else if(h >= hSand)
				{
					c = TCODColor::lerp(keyColor[2], keyColor[3], (h - hSand)/(hGrass - hSand));
				}
				else if(h >= hWater)
				{
					c = TCODColor::lerp(keyColor[1], keyColor[2], (h - hWater)/(hSand - hWater));
				}
				else
				{
					c = TCODColor::lerp(keyColor[1], keyColor[0], ABS(h));
				}
				imgMap->putPixel(x, y, c);
				imgMap_small->putPixel(x/4, y/4, c);
			}
		}

		imgMap->save("templemap.png");
		imgMap->blit2x(TCODConsole::root, 0, 0);

		imgMap_small->save("templemap_small.png");
		imgMap_small->blit2x(TCODConsole::root, 3*SCREEN_WIDTH/4, SCREEN_HEIGHT);

		TCODConsole::root->flush();

		printf("%u\n", seed_town);

		TCODConsole::waitForKeypress(true);
//		key = TCODConsole::waitForKeypress(true);
//		if(key.vk == TCODK_BACKSPACE) break;
//	}

	return 1;
}
