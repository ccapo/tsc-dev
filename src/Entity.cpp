#include "Main.hpp"

int Entity::m_NextValidID = 0;

//------------------------------ ctor -----------------------------------------
//-----------------------------------------------------------------------------
Entity::Entity(int type, LocationType loc, int x, int y, int sym, TCODColor colour, int hpmax, int mpmax) : m_Type(type), m_Location(loc), m_X(x), m_Y(y), m_Sym(sym), m_Colour(colour), m_Radius(0.5*sqrt(2.0)), m_HP(hpmax), m_HPMax(hpmax), m_MP(mpmax), m_MPMax(mpmax), m_IQ(0)
{
	SetID();
}

//----------------------------- SetID -----------------------------------------
//
// This must be called within each constructor to make sure the ID is set
// correctly. It verifies that the value passed to the method is greater
// or equal to the next valid ID, before setting the ID and incrementing
// the next valid ID
//
//-----------------------------------------------------------------------------
void Entity::SetID()
{
	m_ID = m_NextValidID;
	m_NextValidID++;
}
