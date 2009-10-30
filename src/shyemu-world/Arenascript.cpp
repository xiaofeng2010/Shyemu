//Arena PvP Script
//Made By Jotox/Classic

//------------------------------
//Configs.
//------------------------------
//Level required to participate.
#define REQUIRED_LEVEL 80

//Base amount of points awarded
#define NUM_POINTS 40

//Number of points lost on death
#define POINTS_DEATH 10

//Allow parties to PvP (0 for no)
#define PARTY_ALLOWED 1

//Allow Raids to PvP (0 for no) Default: no (It results in 30 vs 1)
#define RAIDS_ALLOWED 0

//---------------------------
//End Config.
//---------------------------


#include "StdAfx.h"
#include "Setup.h"

void GivePoints( Player* player, int32 points)
{
	if( points < 0 )
		player->m_arenaPoints = ((int32)player->m_arenaPoints > (-1)*(points)) ? player->m_arenaPoints + points : 0;//Subtract points, or set to 0 if they don't have enough.
	else
		player->m_arenaPoints += points;
	player->SetUInt32Value(PLAYER_FIELD_ARENA_CURRENCY, player->m_arenaPoints);
}

void OnPlayerKill(Player * pPlayer, Player * pVictim)
{
	if( pPlayer->getLevel() < REQUIRED_LEVEL || pVictim->getLevel() < REQUIRED_LEVEL)
		return;
	if( !pPlayer->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_FREE_FOR_ALL_PVP) || !pVictim->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_FREE_FOR_ALL_PVP) )
		return;

	Group *pGroup = pPlayer->GetGroup();
	if( pGroup && pGroup->GetGroupType() == GROUP_TYPE_RAID && RAIDS_ALLOWED==0)
	{
		SubGroup * sgr;
		for(uint32 i = 0; i < pPlayer->GetGroup()->GetSubGroupCount(); ++i)
		{
			sgr = pPlayer->GetGroup()->GetSubGroup(i);
			pPlayer->GetGroup()->Lock();
			for(GroupMembersSet::iterator itr = sgr->GetGroupMembersBegin(); itr != sgr->GetGroupMembersEnd(); ++itr)
			{
				if((*itr)->m_loggedInPlayer)
					(*itr)->m_loggedInPlayer->BroadcastMessage("%sYou cannot gain arena points while in a raid group.", "|cffff0000");
			}
			pPlayer->GetGroup()->Unlock();
		}
		return;
	}

	int32 Points = NUM_POINTS;
	
	if( PARTY_ALLOWED!=0 && pPlayer->GetGroup() )
	{
		set<Player*> group_members;
		Group * Group = pPlayer->GetGroup();
		SubGroup * SubGroup = pGroup->GetSubGroup(pPlayer->GetSubGroup());
		if( !Group || !SubGroup )
			return;//Just in case.
		for(GroupMembersSet::iterator itr = SubGroup->GetGroupMembersBegin(); itr != SubGroup->GetGroupMembersEnd(); itr++)
		{
			PlayerInfo * pi = (*itr);
			Player * gm = objmgr.GetPlayer(pi->guid);
			if( !gm || gm == pPlayer)
				continue;
			if(gm->isInRange(pPlayer, 100.0f) && gm->CombatStatus.IsInCombat())
				group_members.insert(gm);
		}
		Points = (Points / group_members.size());//Divide by group members.
		if( Points % 5)
				Points += 5 - (Points % 5);//Round up to the nearest 5.
		for(set<Player*>::iterator itr = group_members.begin(); itr != group_members.end(); itr++)
		{
			GivePoints((*itr), Points);
			(*itr)->BroadcastMessage("You have gained %u Arena Points from a party member's kill.", Points);
		}
	}
	
	GivePoints( pPlayer, Points );
	if( pPlayer->GetSession() )
		pPlayer->GetSession()->SendNotification("%sYou gain %u Arena Points.", "|cff00ff00", Points);
	
	GivePoints( pVictim, (-1)*(int32)POINTS_DEATH);
	if(pVictim->GetSession())
		pVictim->GetSession()->SendNotification("%sYou lose %u Arena Points.", "|cffff0000", POINTS_DEATH);
}


void SetupArenaPvP(ScriptMgr * mgr)
{
   mgr->register_hook(SERVER_HOOK_EVENT_ON_KILL_PLAYER, &OnPlayerKill);
}