#include "libtcod.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>

using namespace std;

int main()
{
	TCODConsole *con;
	bool showMenu;
	int size;
	std::map<int, std::string> list;
	int hw = 30 - 4, cursor = 0, start = 0;
	TCOD_key_t key;

	TCODConsole::setCustomFont("data/fonts/arial12x12.png", TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE, 32, 8);
	TCODConsole::initRoot(80, 60, "Scrolling Menu", false);
	con = new TCODConsole(40, 30);
	showMenu = false;

	size = 50;
	string str;
	TCODRandom *rng = TCODRandom::getInstance();
	TCODNamegen::parse("data/namegen/equip_names.cfg");
	for(int i = 0; i < size; i++)
	{
		str.clear();
		str.append("%c");
		str.append(TCODNamegen::generate("Weapon Name", rng));
		str.resize(18,' ');
		str.append("%c");
		list.insert(make_pair(i, str));
	}

	while( !TCODConsole::isWindowClosed() )
	{
		// Update
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

		if( showMenu )
		{
			switch(key.vk)
			{
				case TCODK_UP:
				{
					if( cursor == start )
					{
						start--;
						cursor--;
						if( cursor < 0 )
						{
							start = 0;
							cursor = 0;
						}
					}
					else
					{
						cursor--;
					}
					break;
				}
				case TCODK_DOWN:
				{
					if( cursor == start + hw - 1 )
					{
						start++;
						cursor++;
						if( cursor >= size )
						{
							cursor = size - 1;
							start = cursor - hw + 1;
						}
					}
					else
					{
						cursor++;
					}
					break;
				}
				case TCODK_ESCAPE:
				{
					showMenu = !showMenu;
					cursor = 0;
					start = 0;
					break;
				}
				default: break;
			}

			int w = 40, h = 30;
			int x = 2, y = 2;
			con->setAlignment(TCOD_LEFT);
			con->setBackgroundFlag(TCOD_BKGND_SET);
			con->setDefaultBackground(TCODColor::black);
			con->setDefaultForeground(TCODColor::white);
			con->clear();
			con->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Weapon List");
			TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
			TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::blue);

			for(int i = start; i < start + hw; i++)
			{
				if( i == cursor )
				{
					con->print(x, y++, list[i].c_str(), TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
				}
				else
				{
					con->print(x, y++, list[i].c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
				}
			}
		}
		else
		{
			switch(key.vk)
			{
				case TCODK_ESCAPE:
				{
					showMenu = !showMenu;
					cursor = 0;
					start = 0;
					break;
				}
				default: break;
			}
		}

		// Render
		TCODConsole::root->clear();

		for(int x = 0; x < 80; x++)
		{
			for(int y = 0; y < 60; y++)
			{
				TCODConsole::root->setCharBackground(x, y, TCODColor(50,50,150));
			}
		}

		if( showMenu )
		{
			int w = 40, h = 30;
			int x = w - w/2, y = h - h/2;
			TCODConsole::blit(con, 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
		}


		TCODConsole::flush();
	}
	return 0;
}
