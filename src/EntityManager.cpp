#include "Main.hpp"

//------------------------------- Instance ------------------------------------
//
// This class is a singleton
//
//-----------------------------------------------------------------------------
EntityManagerClass *EntityManagerClass::Instance()
{
	static EntityManagerClass instance;
	return &instance;
}

//--------------------------------- Add ---------------------------------------
//-----------------------------------------------------------------------------
void EntityManagerClass::Add(Entity *pEntity)
{
	m_EntityMap.insert(make_pair(pEntity->ID(), pEntity));
}

//------------------------------ GetEntity ------------------------------------
//-----------------------------------------------------------------------------
Entity *EntityManagerClass::GetEntity(int id) const
{
	// Find the entity
	EntityMap::const_iterator ent = m_EntityMap.find(id);

	// Assert that the entity is a member of the map
	assert((ent != m_EntityMap.end()) && "EntityManagerClass::GetEntity - Invalid ID");

	return ent->second;
}

//------------------------------ Update ---------------------------------------
//-----------------------------------------------------------------------------
bool EntityManagerClass::Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	for(EntityMap::iterator it = m_EntityMap.begin(); it != m_EntityMap.end(); it++)
	{
		status = status && it->second->Update(elapsed, key, mouse);
	}
	return status;
}

//------------------------------ Render ---------------------------------------
//-----------------------------------------------------------------------------
void EntityManagerClass::Render()
{
	for(EntityMap::iterator it = m_EntityMap.begin(); it != m_EntityMap.end(); it++)
	{
		it->second->Render();
	}
}

//----------------------------- Remove ----------------------------------------
//-----------------------------------------------------------------------------
void EntityManagerClass::Remove(Entity *pEntity)
{		
	m_EntityMap.erase(m_EntityMap.find(pEntity->ID()));
}
