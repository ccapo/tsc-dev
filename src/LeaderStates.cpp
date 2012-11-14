#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for Alert
//
//------------------------------------------------------------------------
LeaderAlert *LeaderAlert::Instance()
{
	static LeaderAlert instance;
	return &instance;
}

void LeaderAlert::Enter(Leader *leader)
{
	leader->PageSubordinates(MSG_PATROL);
}

bool LeaderAlert::Update(Leader *leader, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void LeaderAlert::Render(Leader *leader)
{
	TCODConsole::root->setChar(leader->X(), leader->Y() + 3, leader->Sym());
	TCODConsole::root->setCharForeground(leader->X(), leader->Y() + 3, leader->Colour());
}

bool LeaderAlert::Receive(Leader *leader, const Message &msg)
{
	bool status = true;
	switch(msg.Msg)
	{
		case MSG_THREAT:
		{
			leader->StateMgr()->ChangeState(LeaderActiveState);
			break;
		}
		default: break;
	}
	return status;
}

//------------------------------------------------------------------------
//
// Methods for Active
//
//------------------------------------------------------------------------
LeaderActive *LeaderActive::Instance()
{
	static LeaderActive instance;
	return &instance;
}

void LeaderActive::Enter(Leader *leader)
{	
	leader->PageSubordinates(MSG_ATTACK);
}

bool LeaderActive::Update(Leader *leader, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void LeaderActive::Render(Leader *leader)
{
	TCODConsole::root->setChar(leader->X(), leader->Y() + 3, leader->Sym());
	TCODConsole::root->setCharForeground(leader->X(), leader->Y() + 3, leader->Colour());
}

bool LeaderActive::Receive(Leader *leader, const Message &msg)
{
	bool status = true;
	switch(msg.Msg)
	{
		case MSG_SAFE:
		{
			leader->StateMgr()->ChangeState(LeaderAlertState);
			break;
		}
		default: break;
	}
	return status;
}
