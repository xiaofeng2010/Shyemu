///////////////////////////////////
//	Scripter par Ax0ne team	//
//		Par Balthazar	         //
/////////////////////////////////

#include "StdAfx.h"
#include "Setup.h"

#ifdef WIN32
#pragma warning(disable:4305)
#endif

#define INFORMATION_NPC 999967

class SCRIPT_DECL InformationNPC : public GossipScript
{
	public:
	void GossipHello(Object * pObject, Player * Plr, bool AutoSend);
	void GossipSelectOption(Object * pObject, Player * Plr, uint32 Id, uint32 IntId, const char * Code);
	void GossipEnd(Object * pObject, Player * Plr);
	void Destroy()
	{delete this;}
};
   
void InformationNPC::GossipHello(Object * pObject, Player * Plr, bool AutoSend)
{
    GossipMenu * Menu;
    objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);

    Menu->AddItem(0, "Bienvenue", 1);
	Menu->AddItem(0, "Les Règles fondamentales du serveur", 2);
	Menu->AddItem(0, "Les sanctions.", 3);
	Menu->AddItem(0, "Droits des MJ.", 4);
	Menu->AddItem(0, "Le Systeme de vote", 5);
	Menu->AddItem(0, "Le Forum", 6);
	Menu->AddItem(0, "La Boutique", 7);
	//Menu->AddItem(0, "Les nouveautés", 15);

	if(AutoSend)
    Menu->SendTo(Plr);
}

void InformationNPC::GossipSelectOption(Object * pObject, Player * Plr, uint32 Id, uint32 IntId, const char * Code)
{		
	Creature * pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?((Creature*)pObject):NULL;

	if(pCreature==NULL)
		return;

	switch(IntId)
    {
		case 0: // Retour
		{
			GossipHello(pObject, Plr, true);
		}	
        break;

		case 1: // Bienvenue
		{
			GossipMenu *Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);

			Menu->AddItem(0, "Bienvenue sur ce serveur développé par l'équipe d'Eternal Realms pour un plus grand confort et plaisir de jeu.", 8);
			Menu->AddItem(0, "Instances scriptées quasi officiel pour plus de défis", 8);
			Menu->AddItem(0, "Deux zones d'achats personnalisées", 8);
			Menu->AddItem(0, "Le reste, c'est à vous de le découvrir.", 8);
			Menu->AddItem(0, "Serveur est en constante évolution, toute l'équipe vous souhaite un agréable jeu.", 8);
			Menu->AddItem(0, "[Retour].", 99);
			Menu->SendTo(Plr);
		}	
        break;

		case 2: // Règles
		{
			GossipMenu *Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);
				
			Menu->AddItem(0, "Respect de la communauté exigé, surveiller votre langage sous peine de sanction", 9);
			Menu->AddItem(0, "Tout acte de triche sur le serveur est passible d'un bannissement définitif", 9);
			Menu->AddItem(0, "Tout exploitation de bugs est passible d'un avertisement et si récidive de graves sanctions", 9);
			Menu->AddItem(0, "Tout bugs rencontré doit être signalé sur le forum", 9);
			Menu->AddItem(0, "[Retour].", 99);
			Menu->SendTo(Plr);
		}	
		break;

		case 3: // Sanction
		{
			GossipMenu *Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);

			Menu->AddItem(0, "Bannissement définitif d'un compte ou d'un joueur).", 10);
			Menu->AddItem(0, "Bannissement d'un compte ou d'un joueur à durée déterminé.", 10);
			Menu->AddItem(0, "Suppression de personnage.", 10);
			Menu->AddItem(0, "Mute d'un compte.", 10);
			Menu->AddItem(0, "Avertissement verbal ou écrit avant sanctions.", 10);
			Menu->AddItem(0, "[Retour].", 99);
			Menu->SendTo(Plr);
		}
		break;

		case 4: // MJ
		{
			GossipMenu *Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);

			Menu->AddItem(0, "Ils ne peuvent pas vous donner de niveau.", 11);
			Menu->AddItem(0, "Ils ne peuvent pas vous donner d'or.", 11);
			Menu->AddItem(0, "Les MJs ne sont pas des taxis, sauf event organisé par le staff.", 11);
			Menu->AddItem(0, "Les Admin et les MJ sont là pour vous aider en cas de besoin dans le jeu", 11);
			Menu->AddItem(0, "Ils peuvent vous réssuciter en cas de bug de résurrection, ou pendant un évent organisé", 11);
			Menu->AddItem(0, "Ils peuvent vous téléporter uniquement si vous êtes bloqué. (Sous la map ou autre.)", 11);
			Menu->AddItem(0, "Ils peuvent résoudre un conflit entre plusieurs joueurs.", 11);
			Menu->AddItem(0, "En cas de demande de récupération, adressez-vous sur le forum dans la rubrique adéquate.", 11);
			Menu->AddItem(0, "[Retour].", 99);
			Menu->SendTo(Plr);
		}	
        break;

		case 5: // vote
		{
			GossipMenu *Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);

			Menu->AddItem(0, "Un système de vote par nom de compte est présent sur le site, il permet d'augmenter la population du serveur et récompenser les meilleurs votants", 12);
			Menu->AddItem(0, "[Retour].", 99);
			Menu->SendTo(Plr);
		}
        break;

		case 6: // Forum
		{
			GossipMenu *Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);

			Menu->AddItem(0, "Le forum a pour adresse : http://forum.eternal-realms.com/", 13);
			Menu->AddItem(0, "Un forum est a votre disposition :", 13);
			Menu->AddItem(0, " - Pour mettre vos screens en cas de problème rencontré en jeu.", 13);
			Menu->AddItem(0, " - Pour informer les admins des nouveaux bugs.", 13);
			Menu->AddItem(0, " - Pour proposer des améliorations en jeu.", 13);
			Menu->AddItem(0, "[Retour].", 99);
			Menu->SendTo(Plr);
		}
        break;

		case 7: // Boutique
		{
			GossipMenu *Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);

			Menu->AddItem(0, "Une section sur le forum est réserver a la boutique, qui vous permet de avoir des items et des armes spéciale VIP pour améliorer votre personnage et contribuer au bon maintient du serveur.", 14);
			Menu->AddItem(0, "[Retour].", 99);
			Menu->SendTo(Plr);
		}	
        break;

		// Message bienvenue
		case 8:	
		{
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Bon jeu." );
			Plr->Gossip_Complete();	
		}	
		break;

		case 9: 
		{
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Merci de respecter les régles, si vous ne voulez pas être sanctionné." );
			Plr->Gossip_Complete();	
		}	
		break;

		// Message Sanctions
		case 10:
        {
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Vous êtes maintenant au courant des mesures prises sur le serveur." );
			Plr->Gossip_Complete();	
		}	
		break;

		// Message MJ 
		case 11:
        {
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Merci de ne pas déranger les MJ pour rien." );
			Plr->Gossip_Complete();	
		}	
		break;

		// Message vote
		case 12:
        {
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Pensez à voter." );
			Plr->Gossip_Complete();	
		}	
		break;

		//Message Forum
		case 13:
		{
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "N'oubliez pas de vous inscrire." );
			Plr->Gossip_Complete();	
		}	
		break;

		// Message Boutique
		case 14:
        {
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "N'oubliez pas de venir jetez un coup d'oeil." );
			Plr->Gossip_Complete();	
		}	
		break;
		//Message de nouveautés
		case 15:
			{
				GossipMenu *Menu;
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1000003, Plr);
			}break;

		case 99: //Retour au Depart
        { 
			GossipMenu *Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);

			Menu->AddItem(0, "Bienvenue", 1);
			Menu->AddItem(0, "Les Règles fondamentales du serveur", 2);
			Menu->AddItem(0, "Les sanctions.", 3);
			Menu->AddItem(0, "Droits des MJ.", 4);
			Menu->AddItem(0, "Le Systeme de vote", 5);
			Menu->AddItem(0, "Le Forum", 6);
			Menu->AddItem(0, "La Boutique", 7);
			Menu->SendTo(Plr); 
		} 
		break;
	}
};

void InformationNPC::GossipEnd(Object * pObject, Player * Plr)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void SetupInformationNPC(ScriptMgr * mgr)
{
	GossipScript * gs = (GossipScript*) new InformationNPC();
	mgr->register_gossip_script(INFORMATION_NPC, gs);
}