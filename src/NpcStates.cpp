#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for Idle
//
//------------------------------------------------------------------------
NpcIdle *NpcIdle::Instance()
{
	static NpcIdle instance;
	return &instance;
}

void NpcIdle::Enter(Npc *npc){}

bool NpcIdle::Update(Npc *npc, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void NpcIdle::Render(Npc *npc)
{
	TCODConsole::root->setChar(npc->X(), npc->Y() + 3, npc->Sym());
	TCODConsole::root->setCharForeground(npc->X(), npc->Y() + 3, npc->Colour());
}

//------------------------------------------------------------------------
//
// Methods for Active
//
//------------------------------------------------------------------------
NpcActive *NpcActive::Instance()
{
	static NpcActive instance;
	return &instance;
}

bool NpcActive::Update(Npc *npc, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void NpcActive::Render(Npc *npc)
{
	TCODConsole::root->setChar(npc->X(), npc->Y() + 3, npc->Sym());
	TCODConsole::root->setCharForeground(npc->X(), npc->Y() + 3, npc->Colour());
}
