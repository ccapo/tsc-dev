#include "libtcod.hpp"
#include <stdio.h>
#include <math.h>
#include <time.h>

// Size of the map portion shown on-screen
#define DISPLAY_WIDTH 120
#define DISPLAY_HEIGHT 72

// Size of the window
#define SCREEN_WIDTH (DISPLAY_WIDTH)
#define SCREEN_HEIGHT (5*DISPLAY_HEIGHT/4)

// Size of the map
#define MAP_WIDTH (2*DISPLAY_WIDTH)
#define MAP_HEIGHT (2*DISPLAY_HEIGHT)

// Size of the map
#define WIDTH (2*MAP_WIDTH)
#define HEIGHT (2*MAP_HEIGHT)

// Range of the height map
#define HM_MIN 0.75f
#define HM_MAX 0.95f

// Torch information
#define TORCH_RADIUS 15.0f
#define SQUARED_TORCH_RADIUS (TORCH_RADIUS*TORCH_RADIUS)

// Size of message log
#define NMSGS 14

struct Tile
{
	TCODColor c;
	bool isWalkable;
	bool isTransparent;
	bool isExplored;
};

struct Tile cell[WIDTH][HEIGHT];

TCODMap *fovMap = new TCODMap(WIDTH, HEIGHT);

uint32 seed = (uint32)time(NULL);
TCODRandom *rng = new TCODRandom(seed, TCOD_RNG_CMWC);
TCODNoise *torch = new TCODNoise(1, rng);
TCODNoise *terrain = new TCODNoise(2, rng);

int display_x = 0, display_y = 0;
bool recomputeFov = true;

// function building the heightmap
void buildHeightMap(TCODHeightMap *hm)
{
	hm->clear();
	//			mulx	muly	addx	addy	octaves	delta	scale
	hm->addFbm(terrain,	8.0f,	8.0f,	0.0f,	0.0f,	8.0f,	0.0f,	1.0f);
	hm->normalize(HM_MIN, HM_MAX);
}

void buildDungeon(TCODImage *img, TCODImage *img_thumb)
{
	int xmax = WIDTH, ymax = HEIGHT;
	int xcentre = WIDTH/2, ycentre = HEIGHT/2;
	TCODHeightMap *hm = new TCODHeightMap(WIDTH,HEIGHT);

	buildHeightMap(hm);

	for(int x = 0; x < xmax; x += xmax - 1)
	{
		for(int y = 0; y < ymax; y++)
		{
			cell[x][y].c = TCODColor::darkestGrey;
			cell[x][y].isWalkable = false;
			cell[x][y].isTransparent = false;
			img->putPixel(x,y,cell[x][y].c);
			img_thumb->putPixel(x,y,cell[x][y].c);
			fovMap->setProperties(x,y,cell[x][y].isTransparent,cell[x][y].isWalkable);

			int xl = xcentre, yl = ycentre;
			float zmax = hm->getValue(xl,yl);
			TCODLine::init(xl,yl,x,y);
			while(!TCODLine::step(&xl,&yl)) zmax += hm->getValue(xl,yl);

			xl = xcentre;
			yl = ycentre;
			float zthres = hm->getValue(x,y);
			float ztotal = hm->getValue(xl,yl)/zmax;
			TCODLine::init(xl,yl,x,y);

			float coef = (hm->getValue(xl,yl) - HM_MIN)/(HM_MAX - HM_MIN);
			cell[xl][yl].c = TCODColor::lerp(TCODColor::darkestGrey,TCODColor::darkerGrey,coef);
			cell[xl][yl].isWalkable = true;
			cell[xl][yl].isTransparent = true;
			img->putPixel(xl,yl,cell[xl][yl].c);
			img_thumb->putPixel(xl,yl,cell[xl][yl].c);

			while(!TCODLine::step(&xl,&yl))
			{
				if(ztotal < zthres)
				{
					float coef = (hm->getValue(xl,yl) - HM_MIN)/(HM_MAX - HM_MIN);
					cell[xl][yl].c = TCODColor::lerp(TCODColor::darkestGrey,TCODColor::darkerGrey,coef);
					cell[xl][yl].isWalkable = true;
					cell[xl][yl].isTransparent = true;
				}
				else
				{
					cell[xl][yl].c = TCODColor::darkestGrey;
					cell[xl][yl].isWalkable = false;
					cell[xl][yl].isTransparent = false;
				}
				ztotal += hm->getValue(xl,yl)/zmax;
				img->putPixel(xl,yl,cell[xl][yl].c);
				img_thumb->putPixel(xl,yl,cell[xl][yl].c);
			}
		}
	}

	for(int y = 0; y < ymax; y += ymax - 1)
	{
		for(int x = 0; x < xmax; x++)
		{
			cell[x][y].c = TCODColor::darkestGrey;
			cell[x][y].isWalkable = false;
			cell[x][y].isTransparent = false;
			img->putPixel(x,y,cell[x][y].c);
			img_thumb->putPixel(x,y,cell[x][y].c);
			fovMap->setProperties(x,y,cell[x][y].isTransparent,cell[x][y].isWalkable);

			int xl = xcentre, yl = ycentre;
			float zmax = hm->getValue(xl,yl);
			TCODLine::init(xl,yl,x,y);
			while(!TCODLine::step(&xl,&yl)) zmax += hm->getValue(xl,yl);

			xl = xcentre;
			yl = ycentre;
			float zthres = hm->getValue(x,y);
			float ztotal = hm->getValue(xl,yl)/zmax;
			TCODLine::init(xl,yl,x,y);

			float coef = (hm->getValue(xl,yl) - HM_MIN)/(HM_MAX - HM_MIN);
			cell[xl][yl].c = TCODColor::lerp(TCODColor::darkestGrey,TCODColor::darkerGrey,coef);
			cell[xl][yl].isWalkable = true;
			cell[xl][yl].isTransparent = true;
			img->putPixel(xl,yl,cell[xl][yl].c);
			img_thumb->putPixel(xl,yl,cell[xl][yl].c);

			while(!TCODLine::step(&xl,&yl))
			{
				if(ztotal < zthres)
				{
					float coef = (hm->getValue(xl,yl) - HM_MIN)/(HM_MAX - HM_MIN);
					cell[xl][yl].c = TCODColor::lerp(TCODColor::darkestGrey,TCODColor::darkerGrey,coef);
					cell[xl][yl].isWalkable = true;
					cell[xl][yl].isTransparent = true;
				}
				else
				{
					cell[xl][yl].c = TCODColor::darkestGrey;
					cell[xl][yl].isWalkable = false;
					cell[xl][yl].isTransparent = false;
				}
				ztotal += hm->getValue(xl,yl)/zmax;
				img->putPixel(xl,yl,cell[xl][yl].c);
				img_thumb->putPixel(xl,yl,cell[xl][yl].c);
			}
		}
	}

	for(int x = 1; x < xmax - 1; x++)
	{
		for(int y = 1; y < ymax - 1; y++)
		{
			float z = hm->getValue(x,y);
			if(z < 0.83f)
			{
				cell[x][y].c = TCODColor::darkestGrey;
				cell[x][y].isWalkable = false;
				cell[x][y].isTransparent = false;
				img->putPixel(x,y,cell[x][y].c);
				img_thumb->putPixel(x,y,cell[x][y].c);
			}
			cell[x][y].isExplored = false;
			fovMap->setProperties(x,y,cell[x][y].isTransparent,cell[x][y].isWalkable);
		}
	}
	//img->save("cavemap0.png");
	//img_thumb->save("cavemap_thumb0.png");
	delete hm;
	hm = NULL;
}

// Fill (over write) all pixels that are not the border color
void floodFill(TCODImage *img, TCODImage *img_thumb, int x, int y, TCODColor fill, TCODColor border)
{
	// Test pixel color
	if(img->getPixel(x,y) != border)
	{
		cell[x][y].isWalkable = false;
		cell[x][y].isTransparent = false;
		cell[x][y].c = fill;
		img->putPixel(x, y, fill);
		img_thumb->putPixel(x, y, fill);

		floodFill(img, img_thumb, x - 1, y,     fill, border);
		floodFill(img, img_thumb, x + 1, y,     fill, border);
		floodFill(img, img_thumb, x,     y - 1, fill, border);
		floodFill(img, img_thumb, x,     y + 1, fill, border);
	}
}

void moveDisplay(int target_x, int target_y)
{	
	// New display coordinates (top-left corner of the screen relative to the map)
	// Coordinates so that the target is at the center of the screen
	int x = target_x - DISPLAY_WIDTH/2;
	int y = target_y - DISPLAY_HEIGHT/2;

	// Make sure the DISPLAY doesn't see outside the map
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	if(x > MAP_WIDTH - DISPLAY_WIDTH - 1) x = MAP_WIDTH - DISPLAY_WIDTH - 1;
	if(y > MAP_HEIGHT - DISPLAY_HEIGHT - 1) y = MAP_HEIGHT - DISPLAY_HEIGHT - 1;

	if(x != display_x || y != display_y) recomputeFov = true;

	display_x = x; display_y = y;
}

int main(int argc, char *argv[])
{
	TCODImage *img = new TCODImage(WIDTH, HEIGHT);
	TCODImage *img_thumb = new TCODImage(WIDTH, HEIGHT);
	//const char font[] = "data/fonts/arial4x4.png";
	const char font[] = "data/fonts/arial8x8.png";
	//const char font[] = "data/fonts/arial12x12.png";
	//const char font[] = "data/fonts/dundalk12x12_gs_tc.png";
	int fontFlags = TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE;
	int nCol = 32, nRow = 8;
	TCOD_key_t key = {TCODK_NONE, 0};
	int px = 0, py = 0; // player position
	float torchx = 0.0f; // torch light position in the perlin noise
	TCODColor darkWall = TCODColor::darkestGrey;
	TCODColor lightWall(130, 110, 50);
	TCODColor darkGround = TCODColor::darkerGrey;
	TCODColor lightGround(200, 180, 50);

	TCODConsole::setCustomFont(font, fontFlags, nCol, nRow);
	TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "Cave Map", false, TCOD_RENDERER_SDL);

	int initialDelay = 100, interval = 10, maxFps = 24, nWalkable = 0;
	float fWalkable = 0.0f;
	TCODSystem::setFps(maxFps); // fps limited to 24
	TCODConsole::setKeyboardRepeat(initialDelay, interval);

	while(fWalkable < 0.4f)
	{
		seed++;
		rng = new TCODRandom(seed, TCOD_RNG_CMWC);
		terrain = new TCODNoise(2, rng);
		buildDungeon(img, img_thumb);

		px = 0; py = 0;
		while(!(cell[2*px][2*py].isWalkable || cell[2*px][2*py + 1].isWalkable || cell[2*px + 1][2*py].isWalkable || cell[2*px + 1][2*py + 1].isWalkable))
		{
			px = rng->getInt(0, MAP_WIDTH - 1);
			py = rng->getInt(0, MAP_HEIGHT - 1);
		}

		TCODDijkstra *dijkstra = new TCODDijkstra(fovMap); // allocate the path
		dijkstra->compute(2*px, 2*py); // calculate distance from (2*px, 2*py) to all other nodes
		nWalkable = 0;

		for(int x = 0; x < WIDTH; x++)
		{
			for(int y = 0; y < HEIGHT; y++)
			{
				if(cell[x][y].isWalkable)
				{
					if(!dijkstra->setPath(x,y))
					{
						floodFill(img, img_thumb, x, y, darkWall, darkWall);
					}
					else
					{
						nWalkable++;
					}
				}
			}
		}
		fWalkable = ((float)nWalkable)/((float)(WIDTH*HEIGHT));
		printf("%d %f\n", nWalkable, fWalkable);

		img->save("cavemap.png");
		img_thumb->save("cavemap_thumb.png");
	}

	while(!TCODConsole::isWindowClosed())
	{
		TCODConsole::root->clear();

		img = new TCODImage("cavemap.png");
		img_thumb = new TCODImage("cavemap_thumb.png");

		// Move the display
		moveDisplay(px, py);

		// Calculate the field of view from the player position
		if(recomputeFov)
		{
			recomputeFov = false;
			fovMap->computeFov(2*px, 2*py, (int)(TORCH_RADIUS), true, FOV_RESTRICTIVE);
		}

		// Torch position & intensity variation
		float dx = 0.0f, dy = 0.0f, di = 0.0f;

		// Slightly change the perlin noise parameter
		torchx += 0.2f;

		// Randomize the light position between -1.5 and 1.5
		float tdx = torchx + 20.0f;
		dx = torch->get(&tdx)*1.5f;
		tdx += 30.0f;
		dy = torch->get(&tdx)*1.5f;

		// Randomize the light intensity between -0.1 and 0.1
		di = 0.1f*torch->get(&torchx);

		// Draw the cave
		for(int x = 0; x < WIDTH; x++)
		{
			for(int y = 0; y < HEIGHT; y++)
			{
				bool visible = fovMap->isInFov(x, y);
				bool wall = !cell[x][y].isWalkable;
				//bool explored = cell[x][y].isExplored;

				//if(!visible)
				//{
				//	if(explored && wall) img->putPixel(x, y, TCODColor::darkestGrey);
				//}
				//else
				if(visible)
				{
					cell[x][y].isExplored = true;

					// Torch flickering FX
					TCODColor base = cell[x][y].c;
					TCODColor light = (wall ? lightWall : lightGround);
				
					// Cell distance to torch (squared)
					float dxx = (float)(x - 2*px) + dx;
					float dyy = (float)(y - 2*py) + dy;
					float r2 = dxx*dxx + dyy*dyy;
					if(r2 < SQUARED_TORCH_RADIUS)
					{
						// l = 1.0 at player position, 0.0 at a radius of TORCH_RADIUS cells
						//float l = 0.25f*SQUARED_TORCH_RADIUS/(0.25f*SQUARED_TORCH_RADIUS + r2) + di;
						float l1 = 1.0f/(1.0f + r2/20.0f);
						float l2 = l1 - 1.0f/(1.0f + SQUARED_TORCH_RADIUS);
						float l = l2/(1.0f - 1.0f/(1.0f + SQUARED_TORCH_RADIUS)) + di;
						l = CLAMP(0.0f, 1.0f, l);

						// Interpolate the color
						base = TCODColor::lerp(base, light, l);
					}
					light = base;
					img->putPixel(x, y, light);
					img_thumb->putPixel(x, y, light);
				}
			}
		}

		img->blit2x(TCODConsole::root, 0, 0, 2*display_x, 2*display_y, 2*DISPLAY_WIDTH, 2*DISPLAY_HEIGHT);

		img_thumb->putPixel(2*px, 2*py, TCODColor::white);
		img_thumb->scale(2*DISPLAY_WIDTH/4, 2*DISPLAY_HEIGHT/4);
		img_thumb->blit2x(TCODConsole::root, 3*DISPLAY_WIDTH/4, DISPLAY_HEIGHT);

		TCODConsole::root->setDefaultBackground(TCODColor::black);
		TCODConsole::root->setDefaultForeground(TCODColor::white);

		TCODConsole::root->printFrame(0, SCREEN_HEIGHT, 3*SCREEN_WIDTH/4, NMSGS + 4, false, TCOD_BKGND_SET, "Message Log");

		TCODConsole::root->putChar(px - display_x, py - display_y, '@', TCOD_BKGND_NONE);

		TCODConsole::root->flush();

		// Select the response for each keypress
		key = TCODConsole::checkForKeypress(TCOD_KEY_PRESSED);
		switch(key.vk)
		{
			case TCODK_UP:
			{
				if(py <= 1) py = 1;
				if(cell[2*px][2*(py - 1)].isWalkable || cell[2*px][2*(py - 1) + 1].isWalkable)
				{
					TCODConsole::root->putChar(px - display_x, py - display_y, ' ', TCOD_BKGND_NONE);
					py--;
					TCODConsole::root->putChar(px - display_x, py - display_y, '@', TCOD_BKGND_NONE);
					recomputeFov = true;
				}
				break;
			}
			case TCODK_DOWN:
			{
				if(py >= MAP_HEIGHT - 2) py = MAP_HEIGHT - 2;
				if(cell[2*px][2*(py + 1)].isWalkable || cell[2*px][2*(py + 1) - 1].isWalkable)
				{
					TCODConsole::root->putChar(px - display_x, py - display_y, ' ', TCOD_BKGND_NONE);
					py++;
					TCODConsole::root->putChar(px - display_x, py - display_y, '@', TCOD_BKGND_NONE);
					recomputeFov = true;
				}
				break;
			}
			case TCODK_LEFT:
			{
				if(px <= 1) px = 1;
				if(cell[2*(px - 1)][2*py].isWalkable || cell[2*(px - 1) + 1][2*py].isWalkable)
				{
					TCODConsole::root->putChar(px - display_x, py - display_y, ' ', TCOD_BKGND_NONE);
					px--;
					TCODConsole::root->putChar(px - display_x, py - display_y, '@', TCOD_BKGND_NONE);
					recomputeFov = true;
				}
				break;
			}
			case TCODK_RIGHT:
			{
				if(px >= MAP_WIDTH - 2) px = MAP_WIDTH - 2;
				if(cell[2*(px + 1)][2*py].isWalkable || cell[2*(px + 1) - 1][2*py].isWalkable)
				{
					TCODConsole::root->putChar(px - display_x, py - display_y, ' ', TCOD_BKGND_NONE);
					px++;
					TCODConsole::root->putChar(px - display_x, py - display_y, '@', TCOD_BKGND_NONE);
					recomputeFov = true;
				}
				break;
			}
			default: break;
		}
		if(key.vk == TCODK_ESCAPE) break;
	}

	printf("%u\n",seed);

	return 1;
}
