#include "StdAfx.h"
#include "Setup.h"

#ifdef WIN32
#pragma warning(disable:4018)
#endif

#define	 Id_Bon_Maxskills	999994

class SCRIPT_DECL Bon_Maxskill : public GossipScript
{
	public:
	void GossipHello(Object * pObject, Player * Plr, bool AutoSend);
	void GossipSelectOption(Object * pObject, Player * Plr, uint32 Id, uint32 IntId, const char * Code);
	void GossipEnd(Object * pObject, Player * Plr);
	void Destroy()
	{delete this;}
};

void Bon_Maxskill::GossipHello(Object * pObject, Player * Plr, bool AutoSend)
{
	GossipMenu *Menu;
    objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);

    Menu->AddItem(0, "Vous êtes puissant mais pas très brillant, ce bon magique va rendre vos maniments digne d'un maître.", 1);
    Menu->SendTo(Plr);
};

void Bon_Maxskill::GossipSelectOption(Object * pObject, Player * Plr, uint32 Id, uint32 IntId, const char * Code)
{
	switch(IntId)
	{
		case 1 :
		{
			// Arbalètes
			if (Plr->_HasSkillLine(226))
				Plr->_AdvanceSkillLine(226, 400);
				
			// Arcs
			if (Plr->_HasSkillLine(45))
				Plr->_AdvanceSkillLine(45, 400);
				
			// Armes à feu
			if (Plr->_HasSkillLine(46))
				Plr->_AdvanceSkillLine(46, 400);
				
			// Armes d'hast
			if (Plr->_HasSkillLine(229))
				Plr->_AdvanceSkillLine(229, 400);
				
			// Armes de jet
			if (Plr->_HasSkillLine(176))
				Plr->_AdvanceSkillLine(176, 400);
				
			// Armes de pugilat
			if (Plr->_HasSkillLine(473))
				Plr->_AdvanceSkillLine(473, 400);
				
			// Baguettes
			if (Plr->_HasSkillLine(228))
				Plr->_AdvanceSkillLine(228, 400);
				
			// Bâtons
			if (Plr->_HasSkillLine(136))
				Plr->_AdvanceSkillLine(136, 400);
				
			// Dagues
			if (Plr->_HasSkillLine(173))
				Plr->_AdvanceSkillLine(173, 400);
				
			// Défense			
			if (Plr->_HasSkillLine(95))
				Plr->_AdvanceSkillLine(95, 400);
				
			// Epées à deux mains
			if (Plr->_HasSkillLine(55))
            Plr->_AdvanceSkillLine(55, 400);
				
			// Epées à une main
			if (Plr->_HasSkillLine(43))
				Plr->_AdvanceSkillLine(43, 400);
				
			// Haches à deux mains
			if (Plr->_HasSkillLine(172))
				Plr->_AdvanceSkillLine(172, 400);
				
			// Haches à une main
			if (Plr->_HasSkillLine(44))
				Plr->_AdvanceSkillLine(44, 400);
				
			// Mains nues
			if (Plr->_HasSkillLine(162))
				Plr->_AdvanceSkillLine(162, 400);	
				
			// Masses à deux mains
			if (Plr->_HasSkillLine(160))
				Plr->_AdvanceSkillLine(160, 400);
				
			// Masses à une main
			if (Plr->_HasSkillLine(54))
				Plr->_AdvanceSkillLine(54, 400);
				
			Plr->GetItemInterface()->RemoveItemAmt(Id_Bon_Maxskills, 1);
			Plr->Gossip_Complete();
			break;
		}
		default:
		{
			Plr->Gossip_Complete();
		}
	}
};

void Bon_Maxskill::GossipEnd(Object * pObject, Player * Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void Bon_Maxskills(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new Bon_Maxskill();
	mgr->register_item_gossip_script(Id_Bon_Maxskills, gs);
}