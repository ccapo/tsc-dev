#include <stdio.h>
#include <stdlib.h>
#include <libtcod.hpp>

#define fontSize 8

int main(int argc, char *argv[])
{
	// Initialize console
	TCOD_renderer_t renderer = TCOD_RENDERER_SDL;
	TCODConsole::setCustomFont("data/fonts/terminal.png", TCOD_FONT_LAYOUT_ASCII_INCOL|TCOD_FONT_TYPE_GREYSCALE);
	TCODConsole::initRoot(80, 25, "Test", false, renderer);

	// Load image
	//TCODImage *pImg = new TCODImage("data/img/old/magic_icon.orig.png");
	TCODImage *pImg = new TCODImage("data/fonts/monsters/will-o-the-whisp/will-o-the-whisp.png");
	if(!pImg) printf("Failed to load image.\n");

	// Make sure the screen is set to reasonable defaults and clear    
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->clear();

	// Create the char-cell version of the image
	int w, h;
	pImg->getSize(&w, &h);

	int iconWidth = 1;
	while (iconWidth*fontSize <= w) iconWidth++;
	iconWidth--;

	int iconHeight = 1;
	while (iconHeight*fontSize <= h) iconHeight++;
	iconHeight--;

	w = iconWidth*fontSize;
	h = iconHeight*fontSize;
	pImg->scale(w, h);

	int fontx = 0, fonty = 1, ascii = 2;
	for (int x = 0; x < iconWidth; x++)
	{
		for (int y = 0; y < iconHeight; y++)
		{
			TCODConsole::mapAsciiCodeToFont(ascii, fontx, fonty);
			TCODSystem::updateChar(ascii, fontx, fonty, pImg, x*fontSize, y*fontSize);
			fonty++;

			if (fonty == 16)
			{
				fonty = 0;
				fontx++;
			}

			ascii++;
			if (ascii == ' ') ascii = 128;
		}
	}

	// Display the 'image' via character cells
	ascii = 2;
	for (int x = 0; x < iconWidth; x++)
	{
		for (int y = 0; y < iconHeight; y++)
		{
			//TCODConsole::root->putChar(x, y, ascii);
			TCODConsole::root->setChar(x, y, ascii);
			TCODConsole::root->setCharForeground(x, y, TCODColor::white);
			ascii++;
		}
	}

	// Display the first cells worth of the image
	int fontWidth, fontHeight;
	TCODSystem::getCharSize(&fontWidth, &fontHeight);
	pImg->blit2x(TCODConsole::root, 20, 0);

	// Flush screen and wait for keypress
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->printEx(79, 24, TCOD_BKGND_NONE, TCOD_RIGHT, "Press key to continue.");
	TCODConsole::flush();
	TCODConsole::waitForKeypress(true);

	// Cleanup
	delete pImg;
	return 0;

}
