#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for PeonPatrol
//
//------------------------------------------------------------------------
PeonPatrol *PeonPatrol::Instance()
{
	static PeonPatrol instance;
	return &instance;
}

bool PeonPatrol::Update(Peon *peon, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	LocationType loc = GameEngine()->Player()->Location();

	if(loc == LOCATION_CAVE) Transmit->Send(peon->Superior(), MSG_THREAT);

	peon->Direction(RNG->getInt(1, 9));

	switch(peon->Direction())
	{
		case 1:
		{
			if(peon->Y() <= 1) peon->Y(1);
			//if(GameEngine()->Map()->IsWalkable(peon->X(), peon->Y() - 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X(), peon->Y() - 1) < 0)
				//{
					peon->DecreaseY();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X(), peon->Y() - 1);
				//}
			//}
			break;
		}
		case 2:
		{
			if(peon->Y() >= DISPLAY_HEIGHT - 2) peon->Y(DISPLAY_HEIGHT - 2);
			//if(GameEngine()->Map()->IsWalkable(peon->X(), peon->Y() + 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X(), peon->Y() + 1) < 0)
				//{
					peon->IncreaseY();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X(), peon->Y() + 1);
				//}
			//}
			break;
		}
		case 3:
		{
			if(peon->X() <= 1) peon->X(1);
			//if(GameEngine()->Map()->IsWalkable(peon->X() - 1, peon->Y()))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() - 1, peon->Y()) < 0)
				//{
					peon->DecreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() - 1, peon->Y());
				//}
			//}
			break;
		}
		case 4:
		{
			if(peon->X() >= DISPLAY_WIDTH - 2) peon->X(DISPLAY_WIDTH - 2);
			//if(GameEngine()->Map()->IsWalkable(peon->X() + 1, peon->Y()))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() + 1, peon->Y()) < 0)
				//{
					peon->IncreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() + 1, peon->Y());
				//}
			//}
			break;
		}
		case 5:
		{
			if(peon->Y() <= 1) peon->Y(1);
			if(peon->X() <= 1) peon->X(1);
			//if(GameEngine()->Map()->IsWalkable(peon->X() - 1, peon->Y() - 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() - 1, peon->Y() - 1) < 0)
				//{
					peon->DecreaseY();
					peon->DecreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() - 1, peon->Y() - 1);
				//}
			//}
			break;
		}
		case 6:
		{
			if(peon->Y() <= 1) peon->Y(1);
			if(peon->X() >= DISPLAY_WIDTH - 2) peon->X(DISPLAY_WIDTH - 2);
			//if(GameEngine()->Map()->IsWalkable(peon->X() + 1, peon->Y() - 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() + 1, peon->Y() - 1) < 0)
				//{
					peon->DecreaseY();
					peon->IncreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() + 1, peon->Y() - 1);
				//}
			//}
			break;
		}
		case 7:
		{
			if(peon->Y() >= DISPLAY_HEIGHT - 2) peon->Y(DISPLAY_HEIGHT - 2);
			if(peon->X() <= 1) peon->X(1);
			//if(GameEngine()->Map()->IsWalkable(peon->X() - 1, peon->Y() + 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() - 1, peon->Y() + 1) < 0)
				//{
					peon->IncreaseY();
					peon->DecreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() - 1, peon->Y() + 1);
				//}
			//}
			break;
		}
		case 8:
		{
			if(peon->Y() >= DISPLAY_HEIGHT - 2) peon->Y(DISPLAY_HEIGHT - 2);
			if(peon->X() >= DISPLAY_WIDTH - 2) peon->X(DISPLAY_WIDTH - 2);
			//if(GameEngine()->Map()->IsWalkable(peon->X() + 1, peon->Y() + 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() + 1, peon->Y() + 1) < 0)
				//{
					peon->IncreaseY();
					peon->IncreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() + 1, peon->Y() + 1);
				//}
			//}
			break;
		}
		default: break;
	}
	return status;
}

void PeonPatrol::Render(Peon *peon)
{
	TCODConsole::root->setChar(peon->X(), peon->Y() + 3, peon->Sym());
	TCODConsole::root->setCharForeground(peon->X(), peon->Y() + 3, peon->Colour());
}

bool PeonPatrol::Receive(Peon *peon, const Message &msg)
{
	bool status = true;
	switch(msg.Msg)
	{
		case MSG_ATTACK:
		{
			peon->StateMgr()->ChangeState(PeonAttackState);
			break;
		}
		case MSG_DEFEND:
		{
			peon->StateMgr()->ChangeState(PeonDefendState);
			break;
		}
		default: break;
	}
	return status;
}

//------------------------------------------------------------------------
//
// Methods for PeonAttack
//
//------------------------------------------------------------------------
PeonAttack *PeonAttack::Instance()
{
	static PeonAttack instance;
	return &instance;
}

bool PeonAttack::Update(Peon *peon, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	LocationType loc = GameEngine()->Player()->Location();

	if(loc != LOCATION_CAVE) Transmit->Send(peon->Superior(), MSG_SAFE);

	peon->Direction(RNG->getInt(1, 9));

	switch(peon->Direction())
	{
		case 1:
		{
			if(peon->Y() <= 1) peon->Y(1);
			//if(GameEngine()->Map()->IsWalkable(peon->X(), peon->Y() - 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X(), peon->Y() - 1) < 0)
				//{
					peon->DecreaseY();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X(), peon->Y() - 1);
				//}
			//}
			break;
		}
		case 2:
		{
			if(peon->Y() >= DISPLAY_HEIGHT - 2) peon->Y(DISPLAY_HEIGHT - 2);
			//if(GameEngine()->Map()->IsWalkable(peon->X(), peon->Y() + 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X(), peon->Y() + 1) < 0)
				//{
					peon->IncreaseY();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X(), peon->Y() + 1);
				//}
			//}
			break;
		}
		case 3:
		{
			if(peon->X() <= 1) peon->X(1);
			//if(GameEngine()->Map()->IsWalkable(peon->X() - 1, peon->Y()))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() - 1, peon->Y()) < 0)
				//{
					peon->DecreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() - 1, peon->Y());
				//}
			//}
			break;
		}
		case 4:
		{
			if(peon->X() >= DISPLAY_WIDTH - 2) peon->X(DISPLAY_WIDTH - 2);
			//if(GameEngine()->Map()->IsWalkable(peon->X() + 1, peon->Y()))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() + 1, peon->Y()) < 0)
				//{
					peon->IncreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() + 1, peon->Y());
				//}
			//}
			break;
		}
		case 5:
		{
			if(peon->Y() <= 1) peon->Y(1);
			if(peon->X() <= 1) peon->X(1);
			//if(GameEngine()->Map()->IsWalkable(peon->X() - 1, peon->Y() - 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() - 1, peon->Y() - 1) < 0)
				//{
					peon->DecreaseY();
					peon->DecreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() - 1, peon->Y() - 1);
				//}
			//}
			break;
		}
		case 6:
		{
			if(peon->Y() <= 1) peon->Y(1);
			if(peon->X() >= DISPLAY_WIDTH - 2) peon->X(DISPLAY_WIDTH - 2);
			//if(GameEngine()->Map()->IsWalkable(peon->X() + 1, peon->Y() - 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() + 1, peon->Y() - 1) < 0)
				//{
					peon->DecreaseY();
					peon->IncreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() + 1, peon->Y() - 1);
				//}
			//}
			break;
		}
		case 7:
		{
			if(peon->Y() >= DISPLAY_HEIGHT - 2) peon->Y(DISPLAY_HEIGHT - 2);
			if(peon->X() <= 1) peon->X(1);
			//if(GameEngine()->Map()->IsWalkable(peon->X() - 1, peon->Y() + 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() - 1, peon->Y() + 1) < 0)
				//{
					peon->IncreaseY();
					peon->DecreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() - 1, peon->Y() + 1);
				//}
			//}
			break;
		}
		case 8:
		{
			if(peon->Y() >= DISPLAY_HEIGHT - 2) peon->Y(DISPLAY_HEIGHT - 2);
			if(peon->X() >= DISPLAY_WIDTH - 2) peon->X(DISPLAY_WIDTH - 2);
			//if(GameEngine()->Map()->IsWalkable(peon->X() + 1, peon->Y() + 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() + 1, peon->Y() + 1) < 0)
				//{
					peon->IncreaseY();
					peon->IncreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() + 1, peon->Y() + 1);
				//}
			//}
			break;
		}
		default: break;
	}
	return status;
}

void PeonAttack::Render(Peon *peon)
{
	TCODConsole::root->setChar(peon->X(), peon->Y() + 3, peon->Sym());
	TCODConsole::root->setCharForeground(peon->X(), peon->Y() + 3, peon->Colour());
}

bool PeonAttack::Receive(Peon *peon, const Message &msg)
{
	bool status = true;
	switch(msg.Msg)
	{
		case MSG_PATROL:
		{
			peon->StateMgr()->ChangeState(PeonPatrolState);
			break;
		}
		case MSG_DEFEND:
		{
			peon->StateMgr()->ChangeState(PeonDefendState);
			break;
		}
		default: break;
	}
	return status;
}

//------------------------------------------------------------------------
//
// Methods for PeonDefend
//
//------------------------------------------------------------------------
PeonDefend *PeonDefend::Instance()
{
	static PeonDefend instance;
	return &instance;
}

bool PeonDefend::Update(Peon *peon, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	LocationType loc = GameEngine()->Player()->Location();

	if(loc != LOCATION_CAVE) Transmit->Send(peon->Superior(), MSG_SAFE);

	peon->Direction(RNG->getInt(1, 9));

	switch(peon->Direction())
	{
		case 1:
		{
			if(peon->Y() <= 1) peon->Y(1);
			//if(GameEngine()->Map()->IsWalkable(peon->X(), peon->Y() - 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X(), peon->Y() - 1) < 0)
				//{
					peon->DecreaseY();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X(), peon->Y() - 1);
				//}
			//}
			break;
		}
		case 2:
		{
			if(peon->Y() >= DISPLAY_HEIGHT - 2) peon->Y(DISPLAY_HEIGHT - 2);
			//if(GameEngine()->Map()->IsWalkable(peon->X(), peon->Y() + 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X(), peon->Y() + 1) < 0)
				//{
					peon->IncreaseY();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X(), peon->Y() + 1);
				//}
			//}
			break;
		}
		case 3:
		{
			if(peon->X() <= 1) peon->X(1);
			//if(GameEngine()->Map()->IsWalkable(peon->X() - 1, peon->Y()))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() - 1, peon->Y()) < 0)
				//{
					peon->DecreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() - 1, peon->Y());
				//}
			//}
			break;
		}
		case 4:
		{
			if(peon->X() >= DISPLAY_WIDTH - 2) peon->X(DISPLAY_WIDTH - 2);
			//if(GameEngine()->Map()->IsWalkable(peon->X() + 1, peon->Y()))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() + 1, peon->Y()) < 0)
				//{
					peon->IncreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() + 1, peon->Y());
				//}
			//}
			break;
		}
		case 5:
		{
			if(peon->Y() <= 1) peon->Y(1);
			if(peon->X() <= 1) peon->X(1);
			//if(GameEngine()->Map()->IsWalkable(peon->X() - 1, peon->Y() - 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() - 1, peon->Y() - 1) < 0)
				//{
					peon->DecreaseY();
					peon->DecreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() - 1, peon->Y() - 1);
				//}
			//}
			break;
		}
		case 6:
		{
			if(peon->Y() <= 1) peon->Y(1);
			if(peon->X() >= DISPLAY_WIDTH - 2) peon->X(DISPLAY_WIDTH - 2);
			//if(GameEngine()->Map()->IsWalkable(peon->X() + 1, peon->Y() - 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() + 1, peon->Y() - 1) < 0)
				//{
					peon->DecreaseY();
					peon->IncreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() + 1, peon->Y() - 1);
				//}
			//}
			break;
		}
		case 7:
		{
			if(peon->Y() >= DISPLAY_HEIGHT - 2) peon->Y(DISPLAY_HEIGHT - 2);
			if(peon->X() <= 1) peon->X(1);
			//if(GameEngine()->Map()->IsWalkable(peon->X() - 1, peon->Y() + 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() - 1, peon->Y() + 1) < 0)
				//{
					peon->IncreaseY();
					peon->DecreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() - 1, peon->Y() + 1);
				//}
			//}
			break;
		}
		case 8:
		{
			if(peon->Y() >= DISPLAY_HEIGHT - 2) peon->Y(DISPLAY_HEIGHT - 2);
			if(peon->X() >= DISPLAY_WIDTH - 2) peon->X(DISPLAY_WIDTH - 2);
			//if(GameEngine()->Map()->IsWalkable(peon->X() + 1, peon->Y() + 1))
			//{
				//if(GameEngine()->Map()->GetEntityID(peon->X() + 1, peon->Y() + 1) < 0)
				//{
					peon->IncreaseY();
					peon->IncreaseX();
				//}
				//else
				//{
					// Attack Entity!
					//GameEngine()->Map()->AttackEntity(peon->X() + 1, peon->Y() + 1);
				//}
			//}
			break;
		}
		default: break;
	}
	return status;
}

void PeonDefend::Render(Peon *peon)
{
	TCODConsole::root->setChar(peon->X(), peon->Y() + 3, peon->Sym());
	TCODConsole::root->setCharForeground(peon->X(), peon->Y() + 3, peon->Colour());
}

bool PeonDefend::Receive(Peon *peon, const Message &msg)
{
	bool status = true;
	switch(msg.Msg)
	{
		case MSG_PATROL:
		{
			peon->StateMgr()->ChangeState(PeonPatrolState);
			break;
		}
		case MSG_ATTACK:
		{
			peon->StateMgr()->ChangeState(PeonAttackState);
			break;
		}
		default: break;
	}
	return status;
}
