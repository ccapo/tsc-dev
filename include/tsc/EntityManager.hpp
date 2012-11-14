#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP
//------------------------------------------------------------------------
//
// Name: EntityManager.hpp
//
// Desc: Singleton class to handle the management of Entities.				 
//
// Author: Mat Buckland (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

class Entity;

// Provide easy access
#define EntityManager() EntityManagerClass::Instance()

class EntityManagerClass
{
private:

	typedef map<int, Entity*> EntityMap;

protected:

	// To facilitate quick lookup the entities are stored in a map, in which
	// pointers to entities are cross referenced by their identifying number
	EntityMap m_EntityMap;

	EntityManagerClass(){}

	// Copy ctor and assignment should be private
	EntityManagerClass(const EntityManagerClass&);
	EntityManagerClass &operator=(const EntityManagerClass&);

public:

	static EntityManagerClass *Instance();

	// Stores pEntity in m_EntityMap along with it's ID
	void Add(Entity *pEntity);

	// Returns a pointer to the Entity with the given ID
	Entity *GetEntity(int id) const;

	// Update all the Entities stored in m_EntityMap
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);

	// Render all the Entities stored in m_EntityMap
	void Render();

	// Removes pEntity from m_EntityMap
	void Remove(Entity *pEntity);

	// Removes all entities from m_EntityMap
	void RemoveAll(){m_EntityMap.clear();}

};

#endif
