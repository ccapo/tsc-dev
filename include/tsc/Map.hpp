#ifndef MAP_HPP
#define MAP_HPP
//------------------------------------------------------------------------
//
// Name: Map.hpp
//
// Desc: A class to implement a Map
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Module.hpp"
#include "StateManager.hpp"
#include "MapStates.hpp"

class MapClass : public Module
{
private:

	// An instance of the State Manager class
	StateManager<MapClass> *m_StateManager;

  TCODImage *m_Img;
  TCODImage *m_ImgThumb;

	// Copy ctor and assignment should be private
	MapClass(const MapClass&);
	MapClass &operator=(const MapClass&);

public:

	map<int, string> WeaponNames;
	map<int, string> ShieldNames;
	map<int, string> ArmourNames;
	map<int, string> AccessoryNames;

	// The Map Constructor
	MapClass()
	{
		// Set up the State Manager
		m_StateManager = new StateManager<MapClass>(this);
		m_StateManager->SetCurrentState(MapIdleState);

  	// Image and thumbnail
  	m_Img = new TCODImage("data/img/worldmap_new.png");
  	m_ImgThumb = new TCODImage("data/img/worldmap_new.png");

		string tmp;
		TCODNamegen::parse("data/namegen/equip_names.cfg");
		for(int i = 0; i < NWEAPONS; i++)
		{
			tmp.clear();
			tmp.append("%c");
			tmp.append(TCODNamegen::generate("Weapon Name", RNG));
			tmp.resize(18,' ');
			tmp.append("%c");
			WeaponNames.insert(make_pair(i, tmp));

			tmp.clear();
			tmp.append("%c");
			tmp.append(TCODNamegen::generate("Shield Name", RNG));
			tmp.resize(18,' ');
			tmp.append("%c");
			ShieldNames.insert(make_pair(i, tmp));

			tmp.clear();
			tmp.append("%c");
			tmp.append(TCODNamegen::generate("Armour Name", RNG));
			tmp.resize(18,' ');
			tmp.append("%c");
			ArmourNames.insert(make_pair(i, tmp));

			tmp.clear();
			tmp.append("%c");
			tmp.append(TCODNamegen::generate("Accessory Name", RNG));
			tmp.resize(18,' ');
			tmp.append("%c");
			AccessoryNames.insert(make_pair(i, tmp));
		}
	}

	// The Map Destructor
	~MapClass(){delete m_StateManager;}

	// Update the Map
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return StateMgr()->Update(elapsed, key, mouse);}

	// Render the Map
	void Render(){StateMgr()->Render();}

	// Handle Messages for the Map
	bool HandleMessage(const Message &msg){return StateMgr()->HandleMessage(msg);}

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	StateManager<MapClass> *StateMgr() const {return m_StateManager;}

	TCODImage *Img() const {return m_Img;}
	void Img(TCODImage *pImg){m_Img = NULL; m_Img = pImg;}

	TCODImage *ImgThumb() const {return m_ImgThumb;}
	void ImgThumb(TCODImage *pImgThumb){m_ImgThumb = NULL; m_ImgThumb = pImgThumb;}

};

#endif
