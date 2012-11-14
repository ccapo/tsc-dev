#ifndef ENTITY_HPP
#define ENTITY_HPP
//------------------------------------------------------------------------
//
// Name: Entity.hpp
//
// Desc: Base class to define a common interface for all game entities
//
// Author: Mat Buckland (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "libtcod.hpp"
#include "Utils.hpp"

struct Message;

class Entity
{
private:

	// Each entity has a unique ID
	int m_ID;

	// This is the next valid ID, each time an Entity is instantiated this value is updated
	static int m_NextValidID;

	// Every entity has a type associated with it
	int m_Type;

	// This must be called within each constructor to make sure the ID is set
	// correctly. It verifies that the value passed to the method is greater
	// or equal to the next valid ID, before setting the ID and incrementing
	// the next valid ID
	void SetID();

protected:

	// Its location in the world
	LocationType m_Location;
	
	// Its position within its location
	int m_X, m_Y;

	TCODColor m_Colour;

	// Entity Symbol
	int m_Sym;

	// The magnitude of this object's bounding radius
	float m_Radius;

	// Current and maximum health
	int m_HP, m_HPMax;

	// Current and maximum magic
	int m_MP, m_MPMax;

	// The Entity's Intelligence Quotient (IQ)
	int m_IQ;

	Entity(int type, LocationType loc, int x, int y, int sym, TCODColor colour, int hpmax, int mpmax);

public:

	virtual ~Entity(){}

	virtual bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;};
	virtual void Render() = 0;
	virtual bool HandleMessage(const Message &msg){return true;}

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	int ID() const {return m_ID;}

	// Use this to grab the next valid ID
	static int NextValidID(){return m_NextValidID;}
	
	// This can be used to reset the next ID
	static void ResetNextValidID(){m_NextValidID = 1;}

	int Type() const {return m_Type;}
	void Type(int pType){m_Type = pType;}

	LocationType Location() const {return m_Location;}
	void Location(LocationType pLocation){m_Location = pLocation;}

	int X() const {return m_X;}
	void X(int val){m_X = val;}
	void IncreaseX(){m_X++;}
	void DecreaseX(){m_X--;}

	int Y() const {return m_Y;}
	void Y(int val){m_Y = val;}
	void IncreaseY(){m_Y++;}
	void DecreaseY(){m_Y--;}

	int Sym() const {return m_Sym;}
	void Sym(int pSym){m_Sym = pSym;}

	TCODColor Colour() const {return m_Colour;}
	void Colour(TCODColor pColour){m_Colour = pColour;}

	float GetRadius() const {return m_Radius;}
	void SetRadius(float pRadius){m_Radius = pRadius;}

	int HP() const {return m_HP;}
	void HP(int pHP){m_HP = pHP;}
	int HPMax() const {return m_HPMax;}
	void HPMax(int pHPMax){m_HPMax = pHPMax;}
	void ResetHP(){m_HP = m_HPMax;}
	bool Injured(){return m_HP < m_HPMax;}
	void IncreaseHP(int pHP){m_HP += pHP; Clamp<int>(m_HP, 0, m_HPMax);}
	void DecreaseHP(int pHP){m_HP -= pHP; Clamp<int>(m_HP, 0, m_HPMax);}

	int MP() const {return m_MP;}
	void MP(int pMP){m_MP = pMP;}
	int MPMax() const {return m_MPMax;}
	void MPMax(int pMPMax){m_MPMax = pMPMax;}
	void ResetMP(){m_MP = m_MPMax;}
	void IncreaseMP(int pMP){m_MP += pMP; Clamp<int>(m_MP, 0, m_MPMax);}
	void DecreaseMP(int pMP){m_MP -= pMP; Clamp<int>(m_MP, 0, m_MPMax);}

	int IQ() const {return m_IQ;}
	void IQ(int pIQ){m_IQ = pIQ;}

};
 
#endif
