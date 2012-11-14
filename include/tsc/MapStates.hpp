#ifndef MAPSTATES_HPP
#define MAPSTATES_HPP
//------------------------------------------------------------------------
//
// Name: MapStates.hpp
//
// Desc: All the states that can be assigned to the Map class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

class MapClass;

// Provide easy access
#define MapIdleState MapIdle::Instance()
#define MapWorldState MapWorld::Instance()
#define MapTempleState MapTemple::Instance()
#define MapTownState MapTown::Instance()
#define MapCaveState MapCave::Instance()

//------------------------------------------------------------------------
//
// This is the Idle State for the MapClass
//
//------------------------------------------------------------------------
class MapIdle : public State<MapClass>
{
private:

	MapIdle(){}
	
	// Copy ctor and assignment should be private
	MapIdle(const MapIdle&);
	MapIdle &operator=(const MapIdle&);

public:

	// This is a singleton
	static MapIdle *Instance();
	
	void Enter(MapClass *map){}
	bool Update(MapClass *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MapClass *map);
	void Exit(MapClass *map){}
	bool Receive(MapClass *map, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the World State for the MapClass
//
//------------------------------------------------------------------------
class MapWorld : public State<MapClass>
{
private:

	MapWorld(){}
	
	// Copy ctor and assignment should be private
	MapWorld(const MapWorld&);
	MapWorld &operator=(const MapWorld&);

public:

	// This is a singleton
	static MapWorld *Instance();
	
	void Enter(MapClass *map);
	bool Update(MapClass *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MapClass *map);
	void Exit(MapClass *map);
	bool Receive(MapClass *map, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Temple State for the MapClass
//
//------------------------------------------------------------------------
class MapTemple : public State<MapClass>
{
private:

	MapTemple(){}
	
	// Copy ctor and assignment should be private
	MapTemple(const MapTemple&);
	MapTemple &operator=(const MapTemple&);

public:

	// This is a singleton
	static MapTemple *Instance();
	
	void Enter(MapClass *map);
	bool Update(MapClass *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MapClass *map);
	void Exit(MapClass *map);
	bool Receive(MapClass *map, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Town State for the MapClass
//
//------------------------------------------------------------------------
class MapTown : public State<MapClass>
{
private:
	
	MapTown(){}

	// Copy ctor and assignment should be private
	MapTown(const MapTown&);
	MapTown &operator=(const MapTown&);
 
public:

	// This is a singleton
	static MapTown *Instance();
	
	void Enter(MapClass *map);
	bool Update(MapClass *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MapClass *map);
	void Exit(MapClass *map);
	bool Receive(MapClass *map, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Cave State for the MapClass
//
//------------------------------------------------------------------------
class MapCave : public State<MapClass>
{
private:
	
	MapCave(){}

	// Copy ctor and assignment should be private
	MapCave(const MapCave&);
	MapCave &operator=(const MapCave&);
 
public:

	// This is a singleton
	static MapCave *Instance();
	
	void Enter(MapClass *map);
	bool Update(MapClass *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(MapClass *map);
	void Exit(MapClass *map);
	bool Receive(MapClass *map, const Message &msg){return true;}

};

#endif
