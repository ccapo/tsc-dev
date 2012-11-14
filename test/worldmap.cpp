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
//uint32 seed = 0xdeadbeef;
//uint32 seed = 1323922807U;
//uint32 seed = 1323922959U;
//uint32 seed = 1323923881U;
//uint32 seed = 1323925313U;
//uint32 seed = 1323928046U;
//uint32 seed = 1323928645U;
//uint32 seed = 1323928835U;
//uint32 seed = 1323929019U;
//uint32 seed = 1323929348U;
//uint32 seed = 1323932429U;
//uint32 seed = 1323969825U;
//uint32 seed = 1324021782U;
//uint32 seed = 1327125869U;
uint32 seed = 1327128580U;

TCODRandom *rnd=new TCODRandom(seed,TCOD_RNG_CMWC);
TCODNoise *noise=new TCODNoise(2,rnd);

static const float hWater = 0.0f;
static const float hSand = 0.1f;
static const float hGrass = 0.5f;
static const float hMax = 1.0f;

// TCOD's land color map
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

// function building the heightmap
void buildMap(TCODHeightMap *hm)
{
	addHill(hm,600,16.0*WIDTH/400,0.7,0.3);
	hm->normalize();
	//			mulx			muly	addx	addy	octaves	delta	scale
	hm->addFbm(noise,	2.20*WIDTH/800,	2.20*WIDTH/800,	-20.0f,	15.0f,	32.0f,	0.0f,	2.0f);
	hm->normalize(-hMax,hMax);

	hm->add(-0.1f);
	hm->clamp(-hMax,hMax);
	hm->normalize(-hMax,hMax);
}

bool hasWaterOnbBorder(TCODHeightMap *hm, float waterLevel)
{
	int count = 0;
	for(int x = 0; x < WIDTH; x++) 
	{
		if(hm->getValue(x,0) < waterLevel) count++;
		if(hm->getValue(x,HEIGHT - 1) < waterLevel) count++;
	}
	for(int y = 1; y < HEIGHT - 1; y++)
	{
		if(hm->getValue(0,y) < waterLevel) count++;
		if(hm->getValue(WIDTH - 1,y) < waterLevel) count++;
	}
	return (count == 2*(WIDTH + HEIGHT - 1));
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

	TCOD_key_t key = {TCODK_NONE,0};
	TCODColor c;
	bool isIsland = false;
	int nLand = 0;
	float h, fLand = 0.0f;

	TCODConsole::setCustomFont(font, fontFlags, nCol, nRow);
	TCODConsole::initRoot(SCREEN_WIDTH, 5*SCREEN_HEIGHT/4, "World Map", false);

	buildMap(hm);

	while(fLand < 0.6f || !isIsland)
	{
//		seed++;
//		rnd = new TCODRandom(seed,TCOD_RNG_CMWC);
//		noise = new TCODNoise(2,rnd);
//		buildMap(hm);

		nLand = hm->countCells(hWater, hMax);
		fLand = ((float)nLand)/((float)(WIDTH*HEIGHT));
		isIsland = hasWaterOnbBorder(hm, hWater);

		for(int x = 0; x < WIDTH; x++)
		{
			for(int y = 0; y < HEIGHT; y++)
			{
				h = hm->getValue(x, y);

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

		imgMap->save("worldmap.png");
		imgMap->blit2x(TCODConsole::root, 0, 0);

		imgMap_small->save("worldmap_small.png");
		imgMap_small->blit2x(TCODConsole::root, 3*SCREEN_WIDTH/4, SCREEN_HEIGHT);

		TCODConsole::root->flush();

		key = TCODConsole::checkForKeypress();
		if(key.vk == TCODK_ENTER) break;
	}

	printf("%u %d %f\n", seed, isIsland, fLand);
	TCODConsole::waitForKeypress(true);

	return 1;
}
