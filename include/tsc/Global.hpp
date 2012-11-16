#ifndef GLOBAL_HPP
#define GLOBAL_HPP
//------------------------------------------------------------------------
//
// Name: Global.hpp
//
// Description: Global constants
//
// Author: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
//
// The Serpentine Caves
// Copyright (c) 2011, 2012 Christopher Claudio Capobianco
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of Christopher Claudio Capobianco may not be used to endorse
//       or promote products derived from this software without specific prior
//       written permission.
//
// THIS SOFTWARE IS PROVIDED BY CHRISTOPHER CLAUDIO CAPOBIANCO ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL CHRISTOPHER CLAUDIO CAPOBIANCO BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Mingos' Noise Demo 2
// Copyright (c) 2010 Dominik Marczuk
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of Dominik Marczuk may not be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY DOMINIK MARCZUK ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL DOMINIK MARCZUK BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include <cassert>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <typeinfo>
#include <unistd.h>
#include <vector>
#include "libtcod.hpp"

using namespace std;

// Version
#define VERSION "0.3.1"

// Save game magic number
#define SAVEGAME_MAGIC_NUMBER 0xFD051E4F

// Save game file name
#define SAVEGAME_FILENAME "data/.save/savedgame.gz"

// Size of the map portion shown on-screen
#define DISPLAY_WIDTH 70
#define DISPLAY_HEIGHT 42
//#define DISPLAY_WIDTH 120
//#define DISPLAY_HEIGHT 72

// Size of the window
#define SCREEN_WIDTH (DISPLAY_WIDTH)
#define SCREEN_HEIGHT (5*DISPLAY_HEIGHT/4 + 5)

// Size of the map
#define MAP_WIDTH (2*DISPLAY_WIDTH)
#define MAP_HEIGHT (2*DISPLAY_HEIGHT)

// Size of the 2x map
#define MAP_WIDTH2 (2*MAP_WIDTH)
#define MAP_HEIGHT2 (2*MAP_HEIGHT)
#define SCALE_FACTOR (2*MAP_WIDTH2/DISPLAY_WIDTH)

// Size of the static image maps
#define IMAGE_WIDTH 70
#define IMAGE_HEIGHT 42
//#define IMAGE_WIDTH 120
//#define IMAGE_HEIGHT 72

// Size of the static image maps
#define IMAGE_WIDTH2 (2*IMAGE_WIDTH)
#define IMAGE_HEIGHT2 (2*IMAGE_HEIGHT)

// Maximum frame rate
#define MAXFPS 25

// Range of the height map
#define HM_MIN 0.75f
#define HM_MAX 0.95f

// Max. size of lists
#define NITEMMAX 64
#define NCREATUREMAX 1024
#define NCORPSEMAX 1024
#define NPCMAX 64
#define NLOCATIONMAX 32

// Number of regions
#define NREGIONS 4
#define NITEMS_REGION (NITEMS/NREGIONS)

// Number of cave regions
#define NCAVE_REGIONS 4

// Number of cave levels per region
#define NLEVELS_REGION 1

// Max. of messages
#define NMSGS 8

// Number of cells that border a cell
#define NBORDER 8

// Torch Information
#define TORCH_RADIUS 24.0f
#define SQUARED_TORCH_RADIUS (TORCH_RADIUS*TORCH_RADIUS)

// Number of sound channels
#define NCHANNEL 2

// Maximum size for character strings
#define CHARMAX 128

#define LEVELMAX 50

#define HPMIN 25
#define HPMAX 750

#define APMIN 4
#define APMAX 50

#define DPMIN 2
#define DPMAX 50

#define STRMIN 10
#define STRMAX 50

#define SPDMIN 1
#define SPDMAX FPSMAX

#define MPMIN 15
#define MPMAX 250

#define MAPMIN 2
#define MAPMAX 50

#define MDPMIN 1
#define MDPMAX 50

#define WILMIN 2
#define WILMAX 50

#define ACUMIN 1
#define ACUMAX 50

// List of Entities
enum EntityType
{
	ENTITY_DEFAULT = -1,
	ENTITY_PLAYER,
	ENTITY_GUARDIAN,
	ENTITY_SHOPKEEPER,
	ENTITY_TOWNSPERSON,
	ENTITY_LEADER,
	ENTITY_COMMANDER,
	ENTITY_PEON,
	ENTITY_SPECIAL
};

// List of Locations
enum LocationType
{
	LOCATION_DEFAULT = -1,
	LOCATION_WORLD,
	LOCATION_TEMPLE,
	LOCATION_TOWN,
	LOCATION_CAVE,
	NLOCATIONS
};

// List of Magic Types
enum MagicType
{
	MAGIC_LIGHT,
	MAGIC_FIRE,
	MAGIC_WATER,
	MAGIC_WIND,
	MAGIC_EARTH,
	NMAGIC
};

// List of Menu States
enum MenuStates
{
	STATE_01,
	STATE_02,
	STATE_03,
	STATE_04,
	NSTATES
};

// Main Menu Pption Identifiers
enum MainMenu
{
	NONE = -1,
	MAIN_NEW,
	MAIN_LOAD,
	MAIN_HELP,
	MAIN_QUIT,
	NMAIN
};

// Intro Page Identifiers
enum IntroPage
{
	INTRO_01,
	INTRO_02,
	NINTRO
};

// Game Menu Option Identifiers
enum GameMenu
{
	GAME_EQUIP,
	GAME_ITEMS,
	GAME_EXIT,
	NGAME,
	CHANGE_EQUIP
};

// Item Shop Menu Option Identifiers
enum ItemShopMenu
{
	ITEMSHOP_BUY,
	ITEMSHOP_SELL,
	ITEMSHOP_EXIT,
	NITEMSHOP
};

// Equip Shop Menu Option Identifiers
enum EquipShopMenu
{
	EQUIPSHOP_BUY,
	EQUIPSHOP_SELL,
	EQUIPSHOP_EXIT,
	NEQUIPSHOP
};

// Inn Menu Option Identifiers
enum InnMenu
{
	INN_STAY,
	INN_EXIT,
	NINN
};

// Ferry Menu Option Identifiers
enum FerryMenu
{
	FERRY_TAKE,
	FERRY_EXIT,
	NFERRY
};

// Health Status Options
enum HealthStatus
{
  STATUS_BURDENED,
  STATUS_POISONED,
  STATUS_WEAKENED,
  STATUS_SLUGGISH,
  STATUS_FEEBLE,
  STATUS_CONFUSED,
  NSTATUS
};


// List Of Possible Messages
enum MsgType
{
	MSG_DEFAULT = -1,
	// These messages are sent by the player or module to the game engine
	MSG_IDLE,
	MSG_NEWGAME,
	MSG_LOADGAME,
	MSG_SAVEGAME,
	MSG_QUITGAME,
	MSG_INTROGAME,
	MSG_BEGINGAME,
	MSG_HELPSCREEN,
	MSG_ENTERWORLD,
	MSG_ENTERTEMPLE,
	MSG_ENTERTOWN,
	MSG_ENTERCAVE,
	MSG_GUARDIANDIALOG,
	MSG_NPCDIALOG,
	MSG_GAMEMENU,
	MSG_ITEMINV,
	MSG_EQUIPINV,
	MSG_ITEMSHOPMENU,
	MSG_ITEMSHOPMENUBUY,
	MSG_ITEMSHOPMENUSELL,
	MSG_EQUIPSHOPMENU,
	MSG_EQUIPSHOPMENUBUY,
	MSG_EQUIPSHOPMENUSELL,
	MSG_INNMENU,
	MSG_REST,
	MSG_FERRYMENU,
	MSG_FERRYTAKE,
	MSG_MSGLOG,
	MSG_DEATH,
	// These messages are sent between entities
	MSG_PATROL,
	MSG_ATTACK,
	MSG_DEFEND,
	MSG_SAFE,
	MSG_THREAT
};

// List of Tile Character Types
enum CharType
{
	// Default Character Tile
	CHAR_DEFAULT = -1,

	// Magic Charge Bar
	CHAR_CHARGEBAR = 256,

	// Player Tiles
	CHAR_PLAYER_RIGHT,
	CHAR_PLAYER_DOWN,
	CHAR_PLAYER_LEFT,
	CHAR_PLAYER_UP,

	// NPC Tiles
	CHAR_GUARDIAN,
	CHAR_KEEPER,
	CHAR_PERSON,

	// Monster Tiles
	CHAR_GUARD_GREY,
	CHAR_GUARD_RED,
	CHAR_GUARD_GOLD,

	CHAR_WARLOCK_PURPLE,
	CHAR_WARLOCK_WHITE,
	CHAR_WARLOCK_RED,

	CHAR_NECROMANCER_APPENTICE,
	CHAR_NECROMANCER_MASTER,

	CHAR_DARKELF_ARCHER,
	CHAR_DARKELF_WARRIOR,
	CHAR_DARKELF_MAGE,

	CHAR_DWARF_WARRIOR,
	CHAR_DWARF_AXEBEARER,
	CHAR_DWARF_MAGE,
	CHAR_DWARF_HERO,

	CHAR_UNDEAD_DWARF_WARRIOR,
	CHAR_UNDEAD_DWARF_AXEBEARER,
	CHAR_UNDEAD_DWARF_MAGE,
	CHAR_UNDEAD_DWARF_HERO,

	CHAR_GOBLIN_PEON,
	CHAR_GOBLIN_WARRIOR,
	CHAR_GOBLIN_MAGE,

	CHAR_IMP_BLUE,
	CHAR_IMP_RED,

	CHAR_ORGE_PEON_GREEN,
	CHAR_ORGE_WARRIOR_GREEN,

	CHAR_ORGE_PEON_RED,
	CHAR_ORGE_WARRIOR_RED,

	CHAR_SKELETON_PEON,
	CHAR_SKELETON_WARRIOR,
	CHAR_SKELETON_HERO,
	CHAR_SKELETON_MAGE,

	CHAR_SPRITE_RED,
	CHAR_SPRITE_BLUE,
	CHAR_SPRITE_GREEN,
	CHAR_SPRITE_YELLOW,

	CHAR_ORC_PEON,
	CHAR_ORC_WARRIOR,
	CHAR_ORC_HERO,
	CHAR_ORC_MAGE,

	CHAR_DEMON_PEON,
	CHAR_DEMON_HERO,
	CHAR_DEMON_MAGE,

	CHAR_FLAYER_WARRIOR,
	CHAR_FLAYER_MAGE,

	CHAR_SKULL,

	CHAR_GOLEM_GREY,
	CHAR_GOLEM_BROWN,
	CHAR_GOLEM_RED,

	CHAR_SLIME_BROWN,
	CHAR_SLIME_GREEN,

	CHAR_EYEBALL,

	CHAR_VERMIN_BROWN,
	CHAR_VERMIN_GREEN,

	CHAR_SNAKE_PURLE,
	CHAR_SNAKE_GREEN,

	CHAR_SCORPIAN_YELLOW,
	CHAR_SCORPIAN_BLACK,

	CHAR_SPIDER_BLACK,
	CHAR_SPIDER_RED,
	CHAR_SPIDER_GREEN,

	CHAR_PYTHON_RED,
	CHAR_PYTHON_BROWN,
	CHAR_PYTHON_YELLOW,

	CHAR_BAT_BROWN,
	CHAR_BAT_BLUE,

	// Environment Tiles
	CHAR_TREE_A,
	CHAR_TREE_B,
	CHAR_TREE_C,
	CHAR_TREE_D,
	CHAR_TREE_E,
	CHAR_TREE_F,
	CHAR_TREE_G,

	CHAR_SHRUB_A,
	CHAR_SHRUB_B,
	CHAR_SHRUB_C,
	CHAR_SHRUB_D,
	CHAR_MUSHROOM,
	CHAR_FLOWERS_WHITE,
	CHAR_FLOWERS_BLUE,

	CHAR_TEMPLE,
	CHAR_TOWN,
	CHAR_CAVE,

	CHAR_BED,
	CHAR_TABLE,
	CHAR_BOOKCASE,
	CHAR_CHAIR_RIGHT,
	CHAR_CHAIR_LEFT,

	// Minor Boss Tiles (Upper Portion)
	CHAR_DEMONLORD_WHITE_UL,
	CHAR_DEMONLORD_WHITE_UR,

	CHAR_DEMONLORD_RED_UL,
	CHAR_DEMONLORD_RED_UR,

	CHAR_CYCLOPS_UL,
	CHAR_CYCLOPS_UR,

	CHAR_DRAGON_LARGE_RED_UL,
	CHAR_DRAGON_LARGE_RED_UR,

	CHAR_DRAGON_LARGE_YELLOW_UL,
	CHAR_DRAGON_LARGE_YELLOW_UR,

	CHAR_DRAGON_LARGE_GREEN_UL,
	CHAR_DRAGON_LARGE_GREEN_UR,

	CHAR_DRAGON_LARGE_BLUE_UL,
	CHAR_DRAGON_LARGE_BLUE_UR,

	CHAR_DRAGON_LARGE_GREY_UL,
	CHAR_DRAGON_LARGE_GREY_UR,

	CHAR_MINOTAUR_UL,
	CHAR_MINOTAUR_UR,

	CHAR_LIZARD_GIANT_UL,
	CHAR_LIZARD_GIANT_UR,

	CHAR_MEDUSA_UL,
	CHAR_MEDUSA_UR,

	CHAR_FLYING_BRAIN_UL,
	CHAR_FLYING_BRAIN_UR,

	CHAR_SLIMELORD_UL,
	CHAR_SLIMELORD_UR,

	CHAR_BEHOLDER_UL,
	CHAR_BEHOLDER_UR,

	CHAR_BEHEMOTH_UL,
	CHAR_BEHEMOTH_UR,

	// Final Boss Tiles (Upper Portion)
	CHAR_FINAL_BOSS_UL,
	CHAR_FINAL_BOSS_UR,

	// Minor Boss Tiles (Lower Portion)
	CHAR_DEMONLORD_WHITE_LL,
	CHAR_DEMONLORD_WHITE_LR,

	CHAR_DEMONLORD_RED_LL,
	CHAR_DEMONLORD_RED_LR,

	CHAR_CYCLOPS_LL,
	CHAR_CYCLOPS_LR,

	CHAR_DRAGON_LARGE_RED_LL,
	CHAR_DRAGON_LARGE_RED_LR,

	CHAR_DRAGON_LARGE_YELLOW_LL,
	CHAR_DRAGON_LARGE_YELLOW_LR,

	CHAR_DRAGON_LARGE_GREEN_LL,
	CHAR_DRAGON_LARGE_GREEN_LR,

	CHAR_DRAGON_LARGE_BLUE_LL,
	CHAR_DRAGON_LARGE_BLUE_LR,

	CHAR_DRAGON_LARGE_GREY_LL,
	CHAR_DRAGON_LARGE_GREY_LR,

	CHAR_MINOTAUR_LL,
	CHAR_MINOTAUR_LR,

	CHAR_LIZARD_GIANT_LL,
	CHAR_LIZARD_GIANT_LR,

	CHAR_MEDUSA_LL,
	CHAR_MEDUSA_LR,

	CHAR_FLYING_BRAIN_LL,
	CHAR_FLYING_BRAIN_LR,

	CHAR_SLIMELORD_LL,
	CHAR_SLIMELORD_LR,

	CHAR_BEHOLDER_LL,
	CHAR_BEHOLDER_LR,

	CHAR_BEHEMOTH_LL,
	CHAR_BEHEMOTH_LR,

	// Final Boss Tiles (Lower Portion)
	CHAR_FINAL_BOSS_LL,
	CHAR_FINAL_BOSS_LR
};

// Macros
#define IN_RECTANGLE(x,y,w,h) ((unsigned)(x) < (unsigned)(w) && (unsigned)(y) < (unsigned)(h))

#define SQRDIST(x1,y1,x2,y2) (((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2)))

#define ALL9FOV1XWALKABLE(x,y) (fov1x->isWalkable((x)-1,(y)-1) && fov1x->isWalkable((x),(y)-1) && fov1x->isWalkable((x)+1,(y)-1) && fov1x->isWalkable((x)-1,(y)) && fov1x->isWalkable((x),(y)) && fov1x->isWalkable((x)+1,(y)) && fov1x->isWalkable((x)-1,(y)+1) && fov1x->isWalkable((x),(y)+1) && fov1x->isWalkable((x)+1,(y)+1))

#define ANY9FOV1XWALKABLE(x,y) (fov1x->isWalkable((x)-1,(y)-1) || fov1x->isWalkable((x),(y)-1) || fov1x->isWalkable((x)+1,(y)-1) || fov1x->isWalkable((x)-1,(y)) || fov1x->isWalkable((x),(y)) || fov1x->isWalkable((x)+1,(y)) || fov1x->isWalkable((x)-1,(y)+1) || fov1x->isWalkable((x),(y)+1) || fov1x->isWalkable((x)+1,(y)+1))

#define ALL25FOV2XWALKABLE(x,y) (fov2x->isWalkable((x)-2,(y)-2) && fov2x->isWalkable((x)-1,(y)-2) && fov2x->isWalkable((x),(y)-2) && fov2x->isWalkable((x)+1,(y)-2) && fov2x->isWalkable((x)+2,(y)-2) && fov2x->isWalkable((x)-2,(y)-1) && fov2x->isWalkable((x)-1,(y)-1) && fov2x->isWalkable((x),(y)-1) && fov2x->isWalkable((x)+1,(y)-1) && fov2x->isWalkable((x)+2,(y)-1) && fov2x->isWalkable((x)-2,(y)) && fov2x->isWalkable((x)-1,(y)) && fov2x->isWalkable((x),(y)) && fov2x->isWalkable((x)+1,(y)) && fov2x->isWalkable((x)+2,(y)) && fov2x->isWalkable((x)-2,(y)+1) && fov2x->isWalkable((x)-1,(y)+1) && fov2x->isWalkable((x),(y)+1) && fov2x->isWalkable((x)+1,(y)+1) && fov2x->isWalkable((x)+2,(y)+1) && fov2x->isWalkable((x)-2,(y)+2) && fov2x->isWalkable((x)-1,(y)+2) && fov2x->isWalkable((x),(y)+2) && fov2x->isWalkable((x)+1,(y)+2) && fov2x->isWalkable((x)+2,(y)+2))

#define ANY25FOV2XWALKABLE(x,y) (fov2x->isWalkable((x)-2,(y)-2) || fov2x->isWalkable((x)-1,(y)-2) || fov2x->isWalkable((x),(y)-2) || fov2x->isWalkable((x)+1,(y)-2) || fov2x->isWalkable((x)+2,(y)-2) || fov2x->isWalkable((x)-2,(y)-1) || fov2x->isWalkable((x)-1,(y)-1) || fov2x->isWalkable((x),(y)-1) || fov2x->isWalkable((x)+1,(y)-1) || fov2x->isWalkable((x)+2,(y)-1) || fov2x->isWalkable((x)-2,(y)) || fov2x->isWalkable((x)-1,(y)) || fov2x->isWalkable((x),(y)) || fov2x->isWalkable((x)+1,(y)) || fov2x->isWalkable((x)+2,(y)) || fov2x->isWalkable((x)-2,(y)+1) || fov2x->isWalkable((x)-1,(y)+1) || fov2x->isWalkable((x),(y)+1) || fov2x->isWalkable((x)+1,(y)+1) || fov2x->isWalkable((x)+2,(y)+1) || fov2x->isWalkable((x)-2,(y)+2) || fov2x->isWalkable((x)-1,(y)+2) || fov2x->isWalkable((x),(y)+2) || fov2x->isWalkable((x)+1,(y)+2) || fov2x->isWalkable((x)+2,(y)+2))

#endif
