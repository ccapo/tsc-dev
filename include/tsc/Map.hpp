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

	// The Map Constructor
	MapClass()
	{
		// Set up the State Manager
		m_StateManager = new StateManager<MapClass>(this);
		m_StateManager->SetCurrentState(MapIdleState);

  	// Image and thumbnail
  	m_Img = new TCODImage("data/img/worldmap_new.png");
  	m_ImgThumb = new TCODImage("data/img/worldmap_new.png");
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
