#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for CommanderAlert
//
//------------------------------------------------------------------------
CommanderAlert *CommanderAlert::Instance()
{
	static CommanderAlert instance;
	return &instance;
}

void CommanderAlert::Enter(Commander *cmdr)
{
	cmdr->PageSubordinates(MSG_PATROL);
}

bool CommanderAlert::Update(Commander *cmdr, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void CommanderAlert::Render(Commander *cmdr)
{
	TCODConsole::root->setChar(cmdr->X(), cmdr->Y() + 3, cmdr->Sym());
	TCODConsole::root->setCharForeground(cmdr->X(), cmdr->Y() + 3, cmdr->Colour());
}

bool CommanderAlert::Receive(Commander *cmdr, const Message &msg)
{
	bool status = true;
	switch(msg.Msg)
	{
		case MSG_THREAT:
		{
			Transmit->Send(cmdr->Superior(), MSG_THREAT);
			cmdr->StateMgr()->ChangeState(CommanderActiveState);
			break;
		}
		case MSG_ATTACK:
		{
			cmdr->StateMgr()->ChangeState(CommanderActiveState);
			break;
		}
		default: break;
	}
	return status;
}

//------------------------------------------------------------------------
//
// Methods for CommanderActive
//
//------------------------------------------------------------------------
CommanderActive *CommanderActive::Instance()
{
	static CommanderActive instance;
	return &instance;
}

void CommanderActive::Enter(Commander *cmdr)
{	
	cmdr->PageSubordinates(MSG_ATTACK);
}

bool CommanderActive::Update(Commander *cmdr, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void CommanderActive::Render(Commander *cmdr)
{
	TCODConsole::root->setChar(cmdr->X(), cmdr->Y() + 3, cmdr->Sym());
	TCODConsole::root->setCharForeground(cmdr->X(), cmdr->Y() + 3, cmdr->Colour());
}

bool CommanderActive::Receive(Commander *cmdr, const Message &msg)
{
	bool status = true;
	switch(msg.Msg)
	{
		case MSG_SAFE:
		{
			Transmit->Send(cmdr->Superior(), MSG_SAFE);
			cmdr->StateMgr()->ChangeState(CommanderAlertState);
			break;
		}
		case MSG_PATROL:
		{
			cmdr->StateMgr()->ChangeState(CommanderAlertState);
			break;
		}
		default:
		{
			status = false;
			break;
		}
	}
	return status;
}
