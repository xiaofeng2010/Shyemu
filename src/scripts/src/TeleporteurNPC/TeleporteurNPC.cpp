#include "StdAfx.h"
#include "Setup.h"

#ifdef WIN32
#pragma warning(disable:4305) // warning C4305: 'argument' : truncation from 'double' to 'float'
#endif

#define WARPNPC 999968

class SCRIPT_DECL Warper : public GossipScript
{
	public:
    void GossipHello(Object * pObject, Player * Plr, bool AutoSend);
    void GossipSelectOption(Object * pObject, Player * Plr, uint32 Id, uint32 IntId, const char * Code);
    void GossipEnd(Object * pObject, Player * Plr);
	void Destroy()
	{
		delete this;
	}
};

void Warper::GossipHello(Object * pObject, Player * Plr, bool AutoSend)
{
	GossipMenu * Menu;
	objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);
	if (Plr->getRace() == 2 || Plr->getRace() == 5 || Plr->getRace() == 6 || Plr->getRace() == 8 || Plr->getRace() == 10)
	{
		Menu->AddItem(1, "Capitales de la Horde", 1);
	}
	else
	{
		Menu->AddItem(0, "Capitales de l'Alliance", 2);
	}
	
	if(Plr->getLevel() >= 58)
	{
		Menu->AddItem(7, "Shattrath", 12);
	}
	
	if(Plr->getLevel() >= 68)
	{
		Menu->AddItem(7, "Dalaran", 13);
	}
	
	Menu->AddItem(10, "Zone Shop", 14);
	
	if(AutoSend)
		Menu->SendTo(Plr);
}

void Warper::GossipSelectOption(Object * pObject, Player * Plr, uint32 Id, uint32 IntId, const char * Code)
{
	Creature * pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?((Creature*)pObject):NULL;

	if(pCreature==NULL)
		return;

	GossipMenu * Menu;
	switch(IntId)
    {
        case 0:     // Retour au Debut
			GossipHello(pObject, Plr, true);
			break;
	                
        case 1:     // Horde
		{
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);
		
			Menu->AddItem(5, "Lune D'argent", 4);
			Menu->AddItem(5, "Orgrimmar", 5);
			Menu->AddItem(5, "Pitons-du-Tonnerre", 6);
			Menu->AddItem(5, "Fossoyeuse", 7);
			Menu->AddItem(0, "[Retour]", 99);
			Menu->SendTo(Plr);
		}
		break;

        case 2:     // Alliance
		{
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);
        
			Menu->AddItem(5, "L'Exodar", 8);
            Menu->AddItem(5, "Hurlevent", 9);
            Menu->AddItem(5, "Forgefer", 10);
            Menu->AddItem(5, "Darnassus", 11);
			Menu->AddItem(0, "[Retour]", 99);
            Menu->SendTo(Plr);
		}
		break;

        // Horde
        case 4:// Lune D'argent
        {
            Plr->EventTeleport(530, 9400.486328, -7278.376953, 14.206780);
        }
		break;

        case 5:// Orgrimmar
        {
            Plr->EventTeleport(1, 1371.068970, -4370.801758, 26.052483);
        }
		break;

        case 6:// Pitons du Tonnerre
       	{
            Plr->EventTeleport(1, -1304.569946, 205.285004, 68.681396);
        }
		break;

        case 7:// Fossoyeuse
        {
            Plr->EventTeleport(0, 1831.260010, 238.529999, 62.519913);
        }
		break;

        // Alliance 
        case 8: // L'Exodar
		{
            Plr->EventTeleport(530, -4072.202393, -12014.337891, -1.277277);
        }
		break;

        case 9: // Hurlevent
        {
            Plr->EventTeleport(0, -9100.480469, 406.950745, 92.594185);
        }
		break;

        case 10: // ForgeFer
        {
            Plr->EventTeleport(0, -5028.265137, -825.976563, 495.301575);
        }
		break;

        case 11: // Darnassus
        {
            Plr->EventTeleport(1, 9985.907227, 1971.155640, 1326.815674);
        }
		break;

        case 12: //Shattrath
		{
            Plr->EventTeleport(530, -1889.625366, 5482.142090, -12.428076);
		}
		break;
		
		case 13: //dalaran
		{
            Plr->EventTeleport(571, 5813.859375, 449.082581, 658.751038);
		}
		break;
		
		case 14: //Zone Shop
		{
            Plr->EventTeleport(1, -10105.4f, -3963.78f,	12.7774f);
		}
		break;
		
		case 99: // Retour au Depart
		{
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);
			if (Plr->getRace() == 2 || Plr->getRace() == 5 || Plr->getRace() == 6 || Plr->getRace() == 8 || Plr->getRace() == 10)
			{
				Menu->AddItem(1, "Capitales de la Horde", 1);
			}
			else
			{
				Menu->AddItem(0, "Capitales de l'Alliance", 2);
			}
	
			if(Plr->getLevel() >= 58)
			{
				Menu->AddItem(7, "Shattrath", 12);
			}
	
			if(Plr->getLevel() >= 68)
			{
				Menu->AddItem(7, "Dalaran", 13);
			}
	
			Menu->AddItem(10, "Zone Shop", 14);
			Menu->SendTo(Plr);
		}
		break;	
	}
}

void Warper::GossipEnd(Object * pObject, Player * Plr)
{
    GossipScript::GossipEnd(pObject, Plr);
}

void SetupWarper(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new Warper();
    /* Liste des Teleporteurs */
    mgr->register_gossip_script(WARPNPC, gs);
}