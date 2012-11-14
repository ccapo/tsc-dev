#include "libtcod.hpp"
#include <stdio.h>
#include <math.h>
#include <time.h>

// Size of the Height Map
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 72

#define WIDTH (2*SCREEN_WIDTH)
#define HEIGHT (2*SCREEN_HEIGHT)

// Range of the Height Map
#define HM_MIN 0.75f
#define HM_MAX 0.95f

// Torch Information
#define TORCH_RADIUS 24.0f
#define SQUARED_TORCH_RADIUS (TORCH_RADIUS*TORCH_RADIUS)

// Size of Message Log
#define NMSGS 14

#define NNEIGHBOURS 8

struct Tile
{
	TCODColor c;
	bool isWalkable;
	bool isTransparent;
	bool isExplored;
	float scent;
	float oldScent;
};

struct Tile cell[WIDTH][HEIGHT];

TCODMap *fovMap = new TCODMap(WIDTH,HEIGHT);

uint32 seed = (uint32)time(NULL);
TCODRandom *rnd = new TCODRandom(seed,TCOD_RNG_CMWC);
TCODNoise *noise1d = new TCODNoise(1,rnd);
TCODNoise *noise2d = new TCODNoise(2,rnd);

// function building the heightmap
void buildHeightMap(TCODHeightMap *hm)
{
	hm->clear();
	//			mulx	muly	addx	addy	octaves	delta	scale
	hm->addFbm(noise2d,	8.0f,	8.0f,	0.0f,	0.0f,	8.0f,	0.0f,	1.0f);
	hm->normalize(HM_MIN,HM_MAX);
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
			img_thumb->putPixel(x/4,y/4,cell[x][y].c);
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
			img_thumb->putPixel(xl/4,yl/4,cell[xl][yl].c);

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
				img_thumb->putPixel(xl/4,yl/4,cell[xl][yl].c);
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
			img_thumb->putPixel(x/4,y/4,cell[x][y].c);
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
			img_thumb->putPixel(xl/4,yl/4,cell[xl][yl].c);

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
				img_thumb->putPixel(xl/4,yl/4,cell[xl][yl].c);
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
				img_thumb->putPixel(x/4,y/4,cell[x][y].c);
			}
			cell[x][y].isExplored = false;
			fovMap->setProperties(x,y,cell[x][y].isTransparent,cell[x][y].isWalkable);
		}
	}
	//img->save("scentmap0.png");
	//img_thumb->save("scentmap_thumb0.png");
	delete hm;
}

// Fill (over write) all pixels that are not the border color
void FloodFill(TCODImage *img, TCODImage *img_thumb, int x, int y, TCODColor fill_color, TCODColor border_color)
{
	// Test pixel color
	if(img->getPixel(x,y) != border_color)
	{
		cell[x][y].isWalkable = false;
		cell[x][y].isTransparent = false;
		cell[x][y].c = fill_color;
		img->putPixel(x, y, fill_color);
		img_thumb->putPixel(x/4, y/4, fill_color);

		FloodFill(img, img_thumb, x - 1, y,     fill_color, border_color);
		FloodFill(img, img_thumb, x + 1, y,     fill_color, border_color);
		FloodFill(img, img_thumb, x,     y - 1, fill_color, border_color);
		FloodFill(img, img_thumb, x,     y + 1, fill_color, border_color);
	}
}

int main(int argc, char *argv[])
{
	TCODImage *img = new TCODImage(WIDTH,HEIGHT);
	TCODImage *img_thumb = new TCODImage(WIDTH/4,HEIGHT/4);
	//const char font[] = "data/fonts/arial4x4.png";
	const char font[] = "data/fonts/arial8x8.png";
	//const char font[] = "data/fonts/arial12x12.png";
	//const char font[] = "data/fonts/dundalk12x12_gs_tc.png";
	int fontFlags = TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE;
	int nCol = 32, nRow = 8;
	TCOD_key_t key = {TCODK_NONE,0};
	int px = 0, py = 0; // player position
	bool recomputeFov = true;
	float torchx = 0.0f; // torch light position in the perlin noise
	TCODColor darkWall = TCODColor::darkestGrey;
	TCODColor lightWall(130,110,50);
	TCODColor darkGround = TCODColor::darkerGrey;
	TCODColor lightGround(200,180,50);

	int xoff[NNEIGHBOURS] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int yoff[NNEIGHBOURS] = {-1, -1, -1, 0, 0, 1, 1, 1};
	float scent_0 = 1.0f, d = 1.0f/32.0f, lambda = 1.0f;

	TCODConsole::setCustomFont(font,fontFlags,nCol,nRow);
	TCODConsole::initRoot(SCREEN_WIDTH, 5*SCREEN_HEIGHT/4, "Scent Map", false, TCOD_RENDERER_SDL);

	int initialDelay = 100, interval = 10, maxFps = 24, nWalkable = 0;
	float fWalkable = 0.0f;
	TCODSystem::setFps(maxFps); // fps limited to 24
	TCODConsole::setKeyboardRepeat(initialDelay, interval);

	while(fWalkable < 0.4f)
	{
		//TCODSystem::sleepMilli(1000);
		seed++; // = (uint32)time(NULL);
		rnd = new TCODRandom(seed,TCOD_RNG_CMWC);
		noise2d = new TCODNoise(2,rnd);
		buildDungeon(img, img_thumb);

		px = 0;
		py = 0;
		while(!cell[2*px][2*py].isWalkable && !cell[2*px][2*py+1].isWalkable && !cell[2*px+1][2*py].isWalkable && !cell[2*px+1][2*py+1].isWalkable)
		{
			px = rnd->getInt(0, SCREEN_WIDTH - 1);
			py = rnd->getInt(0, SCREEN_HEIGHT - 1);
		}

		TCODDijkstra *dijkstra = new TCODDijkstra(fovMap); // allocate the path
		dijkstra->compute(2*px,2*py); // calculate distance from 2*px,2*py to all other nodes
		nWalkable = 0;

		for(int x = 0; x < WIDTH; x++)
		{
			for(int y = 0; y < HEIGHT; y++)
			{
				if(cell[x][y].isWalkable)
				{
					if(!dijkstra->setPath(x,y))
					{
						FloodFill(img, img_thumb, x, y, darkWall, darkWall);
					}
					else
					{
						nWalkable++;
					}
				}
			}
		}
		fWalkable = ((float)nWalkable)/((float)(WIDTH*HEIGHT));
		//printf("%d %f\n",nWalkable,fWalkable);

		img->save("scentmap.png");
		img_thumb->save("scentmap_thumb.png");
	}

	for(int x = 0; x < WIDTH; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			cell[x][y].scent = 0.0f;
			cell[x][y].oldScent = 0.0f;
		}
	}

	while(!TCODConsole::isWindowClosed())
	{
		TCODConsole::root->clear();

		img = new TCODImage("scentmap.png");
		img_thumb = new TCODImage("scentmap_thumb.png");

		// calculate the field of view from the player position
		if(recomputeFov)
		{
			recomputeFov = false;
			fovMap->computeFov(2*px,2*py,(int)(TORCH_RADIUS),true,FOV_RESTRICTIVE);
		}

		// torch position & intensity variation
		float dx = 0.0f, dy = 0.0f, di = 0.0f;

		// slightly change the perlin noise parameter
		torchx += 0.2f;

		// randomize the light position between -1.5 and 1.5
		float tdx = torchx + 20.0f;
		dx = noise1d->get(&tdx)*1.5f;
		tdx += 30.0f;
		dy = noise1d->get(&tdx)*1.5f;

		// randomize the light intensity between -0.1 and 0.1
		di = 0.1f*noise1d->get(&torchx);

		cell[2*px][2*py].oldScent = scent_0;
		cell[2*px+1][2*py].oldScent = scent_0;
		cell[2*px][2*py+1].oldScent = scent_0;
		cell[2*px+1][2*py+1].oldScent = scent_0;

		for(int x = 1; x < WIDTH - 1; x++)
		{
			for(int y = 1; y < HEIGHT - 1; y++)
			{
				if(cell[x][y].isWalkable)
				{
					float sdiff = 0.0f;
					for(int z = 0; z < NNEIGHBOURS; z++) sdiff += cell[x + xoff[z]][y + yoff[z]].oldScent - cell[x][y].oldScent;
					cell[x][y].scent = lambda*(cell[x][y].oldScent + d*sdiff);
				}
				else
				{
					cell[x][y].scent = 0.0f;
				}
			}
		}

		for(int x = 1; x < WIDTH - 1; x++)
		{
			for(int y = 1; y < HEIGHT - 1; y++)
			{
				cell[x][y].oldScent = cell[x][y].scent;
			}
		}

		// draw the dungeon
		for(int x = 1; x < WIDTH - 1; x++)
		{
			for(int y = 1; y < HEIGHT - 1; y++)
			{
				bool visible = fovMap->isInFov(x,y);
				bool wall = !cell[x][y].isWalkable;
				//bool explored = cell[x][y].isExplored;

				//if(!visible)
				//{
				//	if(explored && wall) img->putPixel(x,y,TCODColor::darkestGrey);
				//}
				//else
				if(visible)
				{
					cell[x][y].isExplored = true;

					// torch flickering FX
					TCODColor base =  cell[x][y].c;
					TCODColor light = (wall ? lightWall : lightGround);
				
					// cell distance to torch (squared)
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
						l = CLAMP(0.0f,1.0f,l);

						// interpolate the color
						base = TCODColor::lerp(base,light,l);
					}
					light = base;
					img->putPixel(x,y,light);
				}
			}
		}

		img->blit2x(TCODConsole::root,0,0);

		img_thumb->putPixel(2*px/4,2*py/4,TCODColor::white);
		img_thumb->blit2x(TCODConsole::root, 3*SCREEN_WIDTH/4, 4*SCREEN_HEIGHT/4);

		TCODConsole::root->setDefaultBackground(TCODColor::black);
		TCODConsole::root->setDefaultForeground(TCODColor::white);

		TCODConsole::root->printFrame(0,SCREEN_HEIGHT,3*SCREEN_WIDTH/4,NMSGS + 4,false,TCOD_BKGND_SET,"Message Log");

		TCODConsole::root->putChar(px,py,'@',TCOD_BKGND_NONE);

		TCODConsole::root->flush();

		// Select the response for each keypress
		key = TCODConsole::checkForKeypress(TCOD_KEY_PRESSED);
		switch(key.vk)
		{
			case TCODK_UP:
			{
				if(py <= 1) py = 1;
				if(cell[2*px][2*(py - 1)].isWalkable || cell[2*px+1][2*(py - 1)].isWalkable || cell[2*px][2*(py - 1)+1].isWalkable || cell[2*px+1][2*(py - 1)+1].isWalkable)
				{
					TCODConsole::root->putChar(px,py,' ',TCOD_BKGND_NONE);
					py--;
					TCODConsole::root->putChar(px,py,'@',TCOD_BKGND_NONE);
					recomputeFov = true;
				}
				break;
			}
			case TCODK_DOWN:
			{
				if(py >= SCREEN_HEIGHT - 2) py = SCREEN_HEIGHT - 2;
				if(cell[2*px][2*(py + 1)].isWalkable || cell[2*px+1][2*(py + 1)].isWalkable || cell[2*px][2*(py + 1)+1].isWalkable || cell[2*px+1][2*(py + 1)+1].isWalkable)
				{
					TCODConsole::root->putChar(px,py,' ',TCOD_BKGND_NONE);
					py++;
					TCODConsole::root->putChar(px,py,'@',TCOD_BKGND_NONE);
					recomputeFov = true;
				}
				break;
			}
			case TCODK_LEFT:
			{
				if(px <= 1) px = 1;
				if(cell[2*(px - 1)][2*py].isWalkable || cell[2*(px - 1)+1][2*py].isWalkable || cell[2*(px - 1)][2*py+1].isWalkable || cell[2*(px - 1)+1][2*py+1].isWalkable)
				{
					TCODConsole::root->putChar(px,py,' ',TCOD_BKGND_NONE);
					px--;
					TCODConsole::root->putChar(px,py,'@',TCOD_BKGND_NONE);
					recomputeFov = true;
				}
				break;
			}
			case TCODK_RIGHT:
			{
				if(px >= SCREEN_WIDTH - 2) px = SCREEN_WIDTH - 2;
				if(cell[2*(px + 1)][2*py].isWalkable || cell[2*(px + 1)+1][2*py].isWalkable || cell[2*(px + 1)][2*py+1].isWalkable || cell[2*(px + 1)+1][2*py+1].isWalkable)
				{
					TCODConsole::root->putChar(px,py,' ',TCOD_BKGND_NONE);
					px++;
					TCODConsole::root->putChar(px,py,'@',TCOD_BKGND_NONE);
					recomputeFov = true;
				}
				break;
			}
			default: break;
		}
		if(key.vk == TCODK_ENTER) break;
	}

	//printf("%u\n",seed);

	return 1;
}
