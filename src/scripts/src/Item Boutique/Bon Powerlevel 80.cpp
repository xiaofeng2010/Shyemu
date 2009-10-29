#include "StdAfx.h"
#include "Setup.h"

#ifdef WIN32
#pragma warning(disable:4305)        // warning C4305: 'argument' : truncation from 'double' to 'float'
#endif

#define	 Powerlevel_80	999995

class SCRIPT_DECL Bon_Powerlevel80 : public GossipScript
{
	public:
	void GossipHello(Object * pObject, Player * Plr, bool AutoSend);
	void GossipSelectOption(Object * pObject, Player * Plr, uint32 Id, uint32 IntId, const char * Code);
	void GossipEnd(Object * pObject, Player * Plr);
	void Destroy()
	{delete this;}
};

void Bon_Powerlevel80::GossipHello(Object * pObject, Player * Plr, bool AutoSend)
{
	GossipMenu * Menu;
    objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);

    Menu->AddItem(0, "Préparez-vous à être propulsé dans les hauts rangs des chevaliers légendaires", 1);
    Menu->SendTo(Plr);
};

void Bon_Powerlevel80::GossipSelectOption(Object * pObject, Player * Plr, uint32 Id, uint32 IntId, const char * Code)
{
	switch(IntId)
	{
		case 1 :
		{
			if ( Plr->getLevel() >= 70 ) 
			{
				uint32 level = Plr->GetUInt32Value(UNIT_FIELD_LEVEL);
				LevelInfo * Info = objmgr.GetLevelInfo(Plr->getRace(), Plr->getClass(), 80);
				Plr->ApplyLevelInfo(Info, 80);
				Plr->GetItemInterface()->RemoveItemAmt(Powerlevel_80, 1);
				Plr->Gossip_Complete();
				break;
			}
		}
		default:
		{
			Plr->Gossip_Complete();
		}
	}
};

void Bon_Powerlevel80::GossipEnd(Object * pObject, Player * Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void Bon_Powerlevel_80(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new Bon_Powerlevel80();
	mgr->register_item_gossip_script(Powerlevel_80, gs);
}