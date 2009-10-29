#include "StdAfx.h"
#include "Setup.h"

#ifdef WIN32
#pragma warning(disable:4305)        // warning C4305: 'argument' : truncation from 'double' to 'float'
#endif

#define	 Powerlevel_Blizz	999999

class SCRIPT_DECL Bon_PowerlevelBlizz : public GossipScript
{
	public:
	void GossipHello(Object * pObject, Player * Plr, bool AutoSend);
	void GossipSelectOption(Object * pObject, Player * Plr, uint32 Id, uint32 IntId, const char * Code);
	void GossipEnd(Object * pObject, Player * Plr);
	void Destroy()
	{delete this;}
};

void Bon_PowerlevelBlizz::GossipHello(Object * pObject, Player * Plr, bool AutoSend)
{
	GossipMenu * Menu;
    objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);

    Menu->AddItem(0, "Increase my level", 1);
    Menu->SendTo(Plr);
};

void Bon_PowerlevelBlizz::GossipSelectOption(Object * pObject, Player * Plr, uint32 Id, uint32 IntId, const char * Code)
{
	switch(IntId)
	{
		case 1 :
		{
			if ( (Plr->getLevel() >= 10) && (Plr->getLevel() <= 19))
			{
				uint32 level = Plr->GetUInt32Value(UNIT_FIELD_LEVEL);
				LevelInfo * Info = objmgr.GetLevelInfo(Plr->getRace(), Plr->getClass(), level);
				Plr->ApplyLevelInfo(Info, level+10);
				Plr->GetItemInterface()->RemoveItemAmt(Powerlevel_Blizz, 1);
				Plr->Gossip_Complete();
				break;
			}
			else if ( (Plr->getLevel() >= 20) && (Plr->getLevel() <= 29))
			{
				uint32 level = Plr->GetUInt32Value(UNIT_FIELD_LEVEL);
				LevelInfo * Info = objmgr.GetLevelInfo(Plr->getRace(), Plr->getClass(), level);
				Plr->ApplyLevelInfo(Info, level+9);
				Plr->GetItemInterface()->RemoveItemAmt(Powerlevel_Blizz, 1);
				Plr->Gossip_Complete();
				break;
			}
			else if ( (Plr->getLevel() >= 30) && (Plr->getLevel() <= 39))
			{
				uint32 level = Plr->GetUInt32Value(UNIT_FIELD_LEVEL);
				LevelInfo * Info = objmgr.GetLevelInfo(Plr->getRace(), Plr->getClass(), level);
				Plr->ApplyLevelInfo(Info, level+8);
				Plr->GetItemInterface()->RemoveItemAmt(Powerlevel_Blizz, 1);
				Plr->Gossip_Complete();
				break;
			}
			else if ( (Plr->getLevel() >= 40) && (Plr->getLevel() <= 49))
			{
				uint32 level = Plr->GetUInt32Value(UNIT_FIELD_LEVEL);
				LevelInfo * Info = objmgr.GetLevelInfo(Plr->getRace(), Plr->getClass(), level);
				Plr->ApplyLevelInfo(Info, level+7);
				Plr->GetItemInterface()->RemoveItemAmt(Powerlevel_Blizz, 1);
				Plr->Gossip_Complete();
				break;
			}
			else if ( (Plr->getLevel() >= 50) && (Plr->getLevel() <= 59))
			{
				uint32 level = Plr->GetUInt32Value(UNIT_FIELD_LEVEL);
				LevelInfo * Info = objmgr.GetLevelInfo(Plr->getRace(), Plr->getClass(), level);
				Plr->ApplyLevelInfo(Info, level+6);
				Plr->GetItemInterface()->RemoveItemAmt(Powerlevel_Blizz, 1);
				Plr->Gossip_Complete();
				break;
			}
			else if ( (Plr->getLevel() >= 60) && (Plr->getLevel() <= 69))
			{
				uint32 level = Plr->GetUInt32Value(UNIT_FIELD_LEVEL);
				LevelInfo * Info = objmgr.GetLevelInfo(Plr->getRace(), Plr->getClass(), level);
				Plr->ApplyLevelInfo(Info, level+4);
				Plr->GetItemInterface()->RemoveItemAmt(Powerlevel_Blizz, 1);
				Plr->Gossip_Complete();
				break;
			}
			else if ( (Plr->getLevel() >= 70) && (Plr->getLevel() < 79))
			{
				uint32 level = Plr->GetUInt32Value(UNIT_FIELD_LEVEL);
				LevelInfo * Info = objmgr.GetLevelInfo(Plr->getRace(), Plr->getClass(), level);
				Plr->ApplyLevelInfo(Info, level+2);
				Plr->GetItemInterface()->RemoveItemAmt(Powerlevel_Blizz, 1);
				Plr->Gossip_Complete();
				break;
			}
			else if ( (Plr->getLevel() == 79) && (Plr->getLevel() < 80))
			{
				uint32 level = Plr->GetUInt32Value(UNIT_FIELD_LEVEL);
				LevelInfo * Info = objmgr.GetLevelInfo(Plr->getRace(), Plr->getClass(), level);
				Plr->ApplyLevelInfo(Info, level+1);
				Plr->GetItemInterface()->RemoveItemAmt(Powerlevel_Blizz, 1);
				Plr->Gossip_Complete();
				break;
			}
			else if ((Plr->getLevel() < 10))
			{
				Plr->BroadcastMessage("You Can Use This Function From Level 10.");
			}
			else
			{
				Plr->BroadcastMessage("You Reached The Maximum Level.");
			}
		}
		default:
		{
			Plr->Gossip_Complete();
		}
	}
};

void Bon_PowerlevelBlizz::GossipEnd(Object * pObject, Player * Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void Bon_Powerlevel_Blizz(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new Bon_PowerlevelBlizz();
	mgr->register_item_gossip_script(Powerlevel_Blizz, gs);
}