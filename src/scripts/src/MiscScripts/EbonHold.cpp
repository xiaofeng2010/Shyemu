/*
 * ArcScript Scripts for Arcemu MMORPG Server
 * Copyright (C) 2008-2009 Arcemu Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "StdAfx.h"
#include "Setup.h"

/*************Teleporters Begin**************/
// Notes: Please try to keep this file clean if modifications are made.
// Also, please include references to header files, and locations for easy access, thanks.
// Lower level of Ebon Hold Teleporter / Teleport up

class SCRIPT_DECL Doodad_Nox_portal_purple_bossroom01 : public GameObjectAIScript
 {
public:
	static GameObjectAIScript *Create(GameObject * GO) { return new Doodad_Nox_portal_purple_bossroom01(GO); }
    Doodad_Nox_portal_purple_bossroom01 (GameObject* goinstance) : GameObjectAIScript(goinstance)
     {
	    RegisterAIUpdateEvent(1);
	 }
     void AIUpdate()
	 {
         set<Player*>::iterator itr = _gameobject->GetInRangePlayerSetBegin();
         for(; itr != _gameobject->GetInRangePlayerSetEnd(); ++itr)
         {
		 Player * Plr = (*itr);
			if( _gameobject->CalcDistance( _gameobject, Plr ) <= 2.0f )
			{
				if(Plr->GetPositionZ() > 388.0f)
				 Plr->SafeTeleport( Plr->GetMapId(), Plr->GetInstanceID(), 2422.375977f, -5619.545410f, 420.643860f, 3.730638f);
				else
				Plr->SafeTeleport( Plr->GetMapId(), Plr->GetInstanceID(), 2402.206299f, -5632.441895f, 377.021484f, 3.725146f);
			}
         }
     }
};

// Upper level of Ebon Hold Teleporter / Teleports down

class SCRIPT_DECL Doodad_Nox_portal_purple_bossroom17 : public GameObjectAIScript
 {
public:
	static GameObjectAIScript *Create(GameObject * GO) { return new Doodad_Nox_portal_purple_bossroom17(GO); }
    Doodad_Nox_portal_purple_bossroom17 (GameObject* goinstance) : GameObjectAIScript(goinstance)
     {
	    RegisterAIUpdateEvent(1);
	 }
     void AIUpdate()
	 {
         set<Player*>::iterator itr = _gameobject->GetInRangePlayerSetBegin();
         for(; itr != _gameobject->GetInRangePlayerSetEnd(); ++itr)
         {
		 Player * Plr = (*itr);
			if( _gameobject->CalcDistance( _gameobject, Plr ) <= 2.0f )
			{
			   if(Plr->GetPositionZ() > 388.0f)
				 Plr->SafeTeleport( Plr->GetMapId(), Plr->GetInstanceID(), 2422.375977f, -5619.545410f, 420.643860f, 3.730638f);
				else
				Plr->SafeTeleport( Plr->GetMapId(), Plr->GetInstanceID(), 2402.206299f, -5632.441895f, 377.021484f, 3.725146f);
			}
         }
     }
};
/*************Teleporters End**************/


/*********************************************
// Scourge Gryphon Taxi Start
**********************************************/
class ScourgeGryphonOne : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* plr, bool AutoSend)
	{
		TaxiPath * path = sTaxiMgr.GetTaxiPath( 1053 );
		plr->TaxiStart( path, 26308, 0 );
	}

	void Destroy()
	{
		delete this;
	};
};

class ScourgeGryphonTwo : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* plr, bool AutoSend)
	{
		TaxiPath * path = sTaxiMgr.GetTaxiPath( 1054 );
		plr->TaxiStart( path, 26308, 0 );
	}

	void Destroy()
	{
		delete this;
	};
};

/***********CHAPITRE I***************************/
//TODO:
// On First Login le Son du Roi liche
// FIX Mettre un minimum de cosmetic pour les initiés a tuer
// FIX Prisonnier "neutre"
// Event du démoniste qui invoque un chevalier de la mort
// Quete Oeil d'acherus -> A faire via le core
// FIX Quete pour graver sa lame->A faire via le core
// FIX Event d'initié indigne
// FIX : AI d'initié indigne
// FIX Résolution immortel a mettre sur le DK
// FIX Waypoints
// AI des croisé écarlate
// AI des Villageois
// Event du démoniste qui invoque un chevalier de la mort mais échec -> 1min et 20s
// Event du forgeron



class PrisonnierEcarlate : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(PrisonnierEcarlate);

    PrisonnierEcarlate(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		_unit->GetAIInterface()->m_canMove = false;
		_unit->GetAIInterface()->disable_combat = true;
		_unit->GetAIInterface()->m_AllowedToEnterCombat = false;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
    }
};
class InitieIndigne : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(InitieIndigne);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    InitieIndigne(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			spells[i].speech = 0;
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(45462);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = false;
		spells[0].cooldown = 10;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 500;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 5.0f;

		spells[1].info = dbcSpell.LookupEntry(45902);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = false;
		spells[1].cooldown = 10;
		spells[1].perctrigger = 25.0f;
		spells[1].attackstoptimer = 500;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 5.0f;

		spells[2].info = dbcSpell.LookupEntry(45477);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = false;
		spells[2].cooldown = 10;
		spells[2].perctrigger = 25.0f;
		spells[2].attackstoptimer = 500;
		spells[2].mindist2cast = 0.0f;
		spells[2].maxdist2cast = 5.0f;
	
		
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		_unit->CastSpell(_unit, 41535, true);
    }


	void OnCombatStart(Unit* mTarget)
    {
		for (int i = 0; i < 3; i++)
			spells[i].casttime = 0;

		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		
		int RandomSpeach;
		RandomUInt(1000);
		RandomSpeach=rand()%20;

		_unit->RemoveAura(41535);
		_unit->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT,0);
		_unit->SetUInt32Value(UNIT_CHANNEL_SPELL,0);

		switch(_unit->GetUInt32Value(UNIT_FIELD_DISPLAYID))
		{
		case 25357:
			_unit->CastSpell(_unit, 51541, false);break;
		case 25372:
			_unit->CastSpell(_unit, 51550, false);break;
		case 25371:
			_unit->CastSpell(_unit, 51548, false);break;
		case 25362:
			_unit->CastSpell(_unit, 51540, false);break;
		case 25356:
			_unit->CastSpell(_unit, 51538, false);break;
		case 25368:
			_unit->CastSpell(_unit, 51544, false);break;
		case 25355:
			_unit->CastSpell(_unit, 51534, false);break;
		case 25359:
			_unit->CastSpell(_unit, 51539, false);break;
		case 25373:
			_unit->CastSpell(_unit, 51551, false);break;
		case 25363:
			_unit->CastSpell(_unit, 51542, false);break;
		case 25365:
			_unit->CastSpell(_unit, 51546, false);break;
		case 25370:
			_unit->CastSpell(_unit, 51545, false);break;
		case 25358:
			_unit->CastSpell(_unit, 51535, false);break;
		}

		_unit->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 38707);
		
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Au combat!");
				break;

			case 1:

				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Meurt!");
				break;

			case 2:
			{
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "La liberté est bientôt à moi!");
				break;
			}
		}
    }

    void OnDied(Unit* mKiller)
    {
		TO_PLAYER(mKiller)->RemoveNegativeAuras();
		QuestLogEntry * qst = TO_PLAYER(mKiller)->GetQuestLogForEntry(12848);
		if(qst)
		{	
			qst->SetMobCount( 0, 1 );
			qst->SendUpdateAddKill(0);
			qst->UpdatePlayerFields();
		}
		RemoveAIUpdateEvent();
	}

	void OnCombatStop(Unit* mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		//_unit->Despawn(0, 10000);
        RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}

	void SpellCast(float val)
    {
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit* target = (Unit*)NULL;
			for(int i=0;i<nrspells;i++)
			{
				if(!spells[i].perctrigger) continue;
				
				if(m_spellcheck[i])
				{
					if (!spells[i].instant)
						_unit->GetAIInterface()->StopMovement(1);
					
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
						case TARGET_RANDOM_FRIEND:
						case TARGET_RANDOM_SINGLE:
						case TARGET_RANDOM_DESTINATION:
							CastSpellOnRandomTarget(i, spells[i].mindist2cast, spells[i].maxdist2cast, spells[i].minhp2cast, spells[i].maxhp2cast); break;
					}
					
					if (spells[i].speech != 0)
					{
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech);
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				int32 t = (uint32)time(NULL);
				if(val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger) && t > spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					spells[i].casttime = t + spells[i].cooldown;
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
        }
    }

	void CastSpellOnRandomTarget(uint32 i, float mindist2cast, float maxdist2cast, int minhp2cast, int maxhp2cast)
	{
		if (!maxdist2cast) maxdist2cast = 100.0f;
		if (!maxhp2cast) maxhp2cast = 100;

		if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			std::vector<Unit*> TargetTable;		

			for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					Unit* RandomTarget = (Unit*)NULL;
					RandomTarget = TO_UNIT(*itr);

					if (RandomTarget->isAlive() && _unit->GetDistance2dSq(RandomTarget) >= mindist2cast*mindist2cast && _unit->GetDistance2dSq(RandomTarget) <= maxdist2cast*maxdist2cast && ((RandomTarget->GetHealthPct() >= minhp2cast && RandomTarget->GetHealthPct() <= maxhp2cast && spells[i].targettype == TARGET_RANDOM_FRIEND) || (_unit->GetAIInterface()->getThreatByPtr(RandomTarget) > 0 && isHostile(_unit, RandomTarget))))
					{
						TargetTable.push_back(RandomTarget);
					} 
				} 
			}

			if (_unit->GetHealthPct() >= minhp2cast && _unit->GetHealthPct() <= maxhp2cast && spells[i].targettype == TARGET_RANDOM_FRIEND)
				TargetTable.push_back(_unit);

			if (!TargetTable.size())
				return;

			size_t RandTarget = rand()%TargetTable.size();

			Unit* RTarget = TargetTable[RandTarget];

			if (!RTarget)
				return;

			switch (spells[i].targettype)
			{
			case TARGET_RANDOM_FRIEND:
			case TARGET_RANDOM_SINGLE:
				_unit->CastSpell(RTarget, spells[i].info, spells[i].instant); break;
			case TARGET_RANDOM_DESTINATION:
				_unit->CastSpellAoF(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), spells[i].info, spells[i].instant); break;
			}

			TargetTable.clear();
		}
	}

	protected:
		uint32 InitDisplay;
		uint64 ChannelObject;
		uint8 ChannelSpell;
		int nrspells;
};	

#define CN_INITIATE_1				29519
#define CN_INITIATE_2				29565
#define CN_INITIATE_3				29567
#define CN_INITIATE_4				29520
#define CN_INITIATE_5				29566

class AcherusSoulPrison : GameObjectAIScript
{
public:
    AcherusSoulPrison(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject * GO) { return new AcherusSoulPrison(GO); }

    void OnGameObjectActivate(Player * pPlayer)
    {
		if(pPlayer->HasQuest(12848))
		{
			float SSX = pPlayer->GetPositionX();
            float SSY = pPlayer->GetPositionY();
            float SSZ = pPlayer->GetPositionZ();
			float SSO = pPlayer->GetOrientation();
            Creature* pCreature = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(SSX, SSY, SSZ, SSO);
			if(!pCreature || !pCreature->isAlive())
            return;
			if (pCreature->GetEntry() == CN_INITIATE_5 || pCreature->GetEntry() == CN_INITIATE_1 || pCreature->GetEntry() == CN_INITIATE_2 || pCreature->GetEntry() == CN_INITIATE_3 || pCreature->GetEntry() == CN_INITIATE_4)
			{
				pPlayer->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Je te donne la clé pour te libérer.");
			    pCreature->SetUInt64Value(UNIT_FIELD_FLAGS, 0);
			    pCreature->GetAIInterface()->SetNextTarget(pPlayer);
				pCreature->GetAIInterface()->AttackReaction(pPlayer, 1, 0);
			}
		}
    }
};

// Script de merde by bloody, et oui il a du mal le petit, noraj mec =P
class OeilAcherus : GameObjectAIScript
{
public:
    OeilAcherus(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
    static GameObjectAIScript *Create(GameObject* GO) 
	{ 
	return new OeilAcherus(GO); 
	}

    void OnActivate(Player* pPlayer)
    {
		//pPlayer->CastSpell(pPlayer, 57532, true);
		CreatureProto * proto = CreatureProtoStorage.LookupEntry(30628);
		CreatureInfo * info = CreatureNameStorage.LookupEntry(30628);

		Creature* p = pPlayer->GetMapMgr()->CreateCreature(30628);
		p->SetInstanceID(pPlayer->GetMapMgr()->GetInstanceID());
		p->m_phase = pPlayer->m_phase;
	//	p->Load(proto, 1881.852051f, -5855.88814f, 192.349716f, 3.40f);

		p->Load(proto, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ() + 10.0f, 0.0f);

		pPlayer->SetUInt64Value(UNIT_FIELD_CHARM, p->GetGUID());

		p->PushToWorld(pPlayer->GetMapMgr());

		pPlayer->Possess(p);
		pPlayer->CastSpell(pPlayer, 51890, true);
    }
};

class OeilAcherusAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(OeilAcherusAI);

    OeilAcherusAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		_unit->EnableFlight();
    }
};

/***********CHAPITRE II**************************/
class ChevalierDeLaMortPhase1 : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(ChevalierDeLaMortPhase1);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    ChevalierDeLaMortPhase1(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			spells[i].speech = 0;
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(45462);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = false;
		spells[0].cooldown = 10;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 500;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 5.0f;

		spells[1].info = dbcSpell.LookupEntry(45902);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = false;
		spells[1].cooldown = 10;
		spells[1].perctrigger = 25.0f;
		spells[1].attackstoptimer = 500;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 5.0f;

		spells[2].info = dbcSpell.LookupEntry(45477);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = false;
		spells[2].cooldown = 10;
		spells[2].perctrigger = 25.0f;
		spells[2].attackstoptimer = 500;
		spells[2].mindist2cast = 0.0f;
		spells[2].maxdist2cast = 5.0f;

		if(_unit->m_phase == 2)
			_unit->SetUInt32Value(UNIT_NPC_FLAGS, 1);
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
	}


	void OnCombatStart(Unit* mTarget)
    {
		for (int i = 0; i < 3; i++)
			spells[i].casttime = 0;
		
		if(_unit->GetUInt32Value(UNIT_NPC_FLAGS) == 0)
		{
			int RandomSpeach;
			RandomSpeach=rand()%4;
		
			switch (RandomSpeach)
			{
				case 0:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Pas de potion!");
					break;
				case 1:	
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Je vais vous la mettre grave!");
					break;
				case 2:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Je vais t'arracher le coeur mon petit chou!");
					break;
				case 3:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Le roi-liche va voir qui est son vrai champion aujourd'hui!");
					break;
			}
		}
		if(_unit->GetUInt32Value(UNIT_NPC_FLAGS) != 0)
			_unit->SetUInt32Value(UNIT_NPC_FLAGS, 2);
    }

    void OnDied(Unit* mKiller)
    {
		if(mKiller->IsPlayer())
		{
			TO_PLAYER(mKiller)->RemoveNegativeAuras();
			QuestLogEntry * qst = TO_PLAYER(mKiller)->GetQuestLogForEntry(12733);
			if(qst)
			{	
				qst->SetMobCount( 0, qst->GetMobCount(0)+1 );
				qst->SendUpdateAddKill(0);
				qst->UpdatePlayerFields();
			}
			_unit->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 35);
			_unit->_setFaction();
			_unit->UpdateOppFactionSet();
			_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
			_unit->SetUInt32Value(UNIT_NPC_FLAGS, 1);
			TO_CREATURE(_unit)->Despawn(2000, 2500);
		}
	}

	void OnCombatStop(Unit* mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		//_unit->Despawn(0, 10000);
        //RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}

	void SpellCast(float val)
    {
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit* target = (Unit*)NULL;
			for(int i=0;i<nrspells;i++)
			{
				if(!spells[i].perctrigger) continue;
				
				if(m_spellcheck[i])
				{
					if (!spells[i].instant)
						_unit->GetAIInterface()->StopMovement(1);
					
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
						case TARGET_RANDOM_FRIEND:
						case TARGET_RANDOM_SINGLE:
						case TARGET_RANDOM_DESTINATION:
							CastSpellOnRandomTarget(i, spells[i].mindist2cast, spells[i].maxdist2cast, spells[i].minhp2cast, spells[i].maxhp2cast); break;
					}
					
					if (spells[i].speech != 0)
					{
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech);
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				int32 t = (uint32)time(NULL);
				if(val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger) && t > spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					spells[i].casttime = t + spells[i].cooldown;
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
        }
    }

	void CastSpellOnRandomTarget(uint32 i, float mindist2cast, float maxdist2cast, int minhp2cast, int maxhp2cast)
	{
		if (!maxdist2cast) maxdist2cast = 100.0f;
		if (!maxhp2cast) maxhp2cast = 100;

		if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			std::vector<Unit*> TargetTable;		

			for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					Unit* RandomTarget = (Unit*)NULL;
					RandomTarget = TO_UNIT(*itr);

					if (RandomTarget->isAlive() && _unit->GetDistance2dSq(RandomTarget) >= mindist2cast*mindist2cast && _unit->GetDistance2dSq(RandomTarget) <= maxdist2cast*maxdist2cast && ((RandomTarget->GetHealthPct() >= minhp2cast && RandomTarget->GetHealthPct() <= maxhp2cast && spells[i].targettype == TARGET_RANDOM_FRIEND) || (_unit->GetAIInterface()->getThreatByPtr(RandomTarget) > 0 && isHostile(_unit, RandomTarget))))
					{
						TargetTable.push_back(RandomTarget);
					} 
				} 
			}

			if (_unit->GetHealthPct() >= minhp2cast && _unit->GetHealthPct() <= maxhp2cast && spells[i].targettype == TARGET_RANDOM_FRIEND)
				TargetTable.push_back(_unit);

			if (!TargetTable.size())
				return;

			size_t RandTarget = rand()%TargetTable.size();

			Unit* RTarget = TargetTable[RandTarget];

			if (!RTarget)
				return;

			switch (spells[i].targettype)
			{
			case TARGET_RANDOM_FRIEND:
			case TARGET_RANDOM_SINGLE:
				_unit->CastSpell(RTarget, spells[i].info, spells[i].instant); break;
			case TARGET_RANDOM_DESTINATION:
				_unit->CastSpellAoF(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), spells[i].info, spells[i].instant); break;
			}

			TargetTable.clear();
		}
	}

	protected:
		int nrspells;
};

class SCRIPT_DECL DuelChevalierDeLaMortPhase1 : public GossipScript
{
public:
    void GossipHello(Object*  pObject, Player* Plr, bool AutoSend);
    void GossipSelectOption(Object*  pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code);
    void GossipEnd(Object*  pObject, Player* Plr);
	void Destroy()
	{
		delete this;
	}
};

void DuelChevalierDeLaMortPhase1::GossipHello(Object*  pObject, Player* Plr, bool AutoSend)
{
    GossipMenu *Menu;
    uint32 TextID = 1;
    // Hello (First) Menu.
    objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), TextID, Plr);
    if(Plr->HasQuest(12733))
	{
		Menu->AddItem( 10, "Faire un duel.", 1 );
		Menu->AddItem( 10, "Euh non rien.", 2);
	}

    if(AutoSend)
        Menu->SendTo(Plr);
}

#define SendQuickMenu(textid) objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), textid, Plr); \
    Menu->SendTo(Plr);

void DuelChevalierDeLaMortPhase1::GossipSelectOption(Object*  pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
{
	Creature* pCreature = (Creature*)NULL;
	pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?TO_CREATURE(pObject):(Creature*)NULL;
	if(!pCreature)
		return;

    switch(IntId)
    {
    case 1: 
		{
			pCreature->SetUInt32Value(UNIT_NPC_FLAGS, 0);
			pCreature->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 14);
			TO_CREATURE(pCreature)->_setFaction();
			pCreature->UpdateOppFactionSet();
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Prêt?... Allez c'est partie !");
			pCreature->GetAIInterface()->AttackReaction(Plr, 0, 0);
		}
        break;
	case 2:
		{
			GossipEnd(pObject, Plr);
		}break;
    }
}

void DuelChevalierDeLaMortPhase1::GossipEnd(Object*  pObject, Player* Plr)
{
    GossipScript::GossipEnd(pObject, Plr);
}

class SCRIPT_DECL VolerLeCheval : public GossipScript
{
public:
    void GossipHello(Object*  pObject, Player* Plr, bool AutoSend);
    void GossipSelectOption(Object*  pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code);
    void GossipEnd(Object*  pObject, Player* Plr);
	void Destroy()
	{
		delete this;
	}
};

void VolerLeCheval::GossipHello(Object*  pObject, Player* Plr, bool AutoSend)
{
    GossipMenu *Menu;
    uint32 TextID = 1;
    // Hello (First) Menu.
    objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), TextID, Plr);
    if(Plr->HasQuest(12680))
	{
		Menu->AddItem( 10, "Voler le cheval.", 1 );
		Menu->AddItem( 10, "Pas tout de suite.", 2);
	}

    if(AutoSend)
        Menu->SendTo(Plr);
}

#define SendQuickMenu(textid) objmgr.CreateGossipMenuForPlayer(&Menu, pCreature->GetGUID(), textid, Plr); \
    Menu->SendTo(Plr);

void VolerLeCheval::GossipSelectOption(Object*  pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
{
	Creature* pCreature = (Creature*)NULL;
	pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?TO_CREATURE(pObject):(Creature*)NULL;
	if(!pCreature)
		return;

    switch(IntId)
    {
    case 1: 
		{
			Plr->SetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID, pCreature->GetUInt32Value(UNIT_FIELD_DISPLAYID));
			pCreature->Despawn(1000, 9000);
			Plr->CastSpell(Plr, 52263, true);
		}
        break;
	case 2:
		{
			GossipEnd(pObject, Plr);
		}break;
    }
}

void VolerLeCheval::GossipEnd(Object*  pObject, Player* Plr)
{
    GossipScript::GossipEnd(pObject, Plr);
}

class SalanarLeCavalierQueteAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(SalanarLeCavalierQueteAI);

    SalanarLeCavalierQueteAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		RegisterAIUpdateEvent(2000);
    }		

    void AIUpdate()
	{
		for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
		{ 
			if(!(*itr)->m_phase == 32 && (*itr)->IsPlayer() && (*itr)->CalcDistance(_unit) <= 10.0f)
				TO_PLAYER(*itr)->RemoveAura(52263);
			else if(!((*itr)->IsPlayer()) && (*itr)->CalcDistance(_unit) > 4.0f)
				continue;

			Player* Plr = TO_PLAYER((*itr));
			if(Plr->GetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID))
			{
				switch(Plr->GetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID))
				{
				case 229:
				case 25571:
				case 25574:
					{
						QuestLogEntry * qst = Plr->GetQuestLogForEntry(12680);
						if(qst)
						{	
							Plr->RemoveAura(52263);
							Plr->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, 0);
							qst->SetMobCount( 0, 1 );
							qst->SendUpdateAddKill(0);
							qst->UpdatePlayerFields();
						}
					}break;
				case 25445:
					{
						QuestLogEntry * qst = Plr->GetQuestLogForEntry(12687);
						if(qst)
						{	
							Plr->RemoveAura(52693);
							Plr->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, 0);
							qst->SetMobCount( 0, 1 );
							qst->SendUpdateAddKill(0);
							qst->UpdatePlayerFields();
						}
					}break;
				}
			}
		}
	}
protected:
};

class CavalierNoirAcherus : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(CavalierNoirAcherus);

    CavalierNoirAcherus(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }	

	void OnDied(Unit* mKiller)
    {
		if(mKiller->IsPlayer())
		{
			QuestLogEntry * qst = TO_PLAYER(mKiller)->GetQuestLogForEntry(12687);
			if(qst)
			{	
				mKiller->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, 25445);
				TO_PLAYER(mKiller)->GetSession()->SendNotification("Retournez à Brèche-de-mort");
			}
		}
		RemoveAIUpdateEvent();
	}
protected:
};

/***********CHAPITRE III*************************/
class CitoyenDK : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(CitoyenDK);

    CitoyenDK(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		_unit->GetAIInterface()->m_AllowedToEnterCombat = false;
    }		

    void OnCombatStart(Unit* mTarget)
    {
		uint32 Chance = RandomUInt(3)+1;
		switch(Chance)
		{
		case 1:
			{
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "C'était pas la bonne semaine pour arrêter de boire!");
				_unit->GetAIInterface()->AttackReaction(mTarget, 0, 0);
			}break;
		case 2:
			{
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Euuhhnng... Je... Je crois que je me suis fais dessus...");
				_unit->GetAIInterface()->AttackReaction(mTarget, 0, 0);
			}break;
		case 3:
			{
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Non! Je vous en prie! J'ai... J'ai des enfants! Je... Je...");
				_unit->setEmoteState(18);
			}break;
		}
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnDied(Unit* mKiller)
    {
		if(mKiller && mKiller->IsPlayer())
		{
			QuestLogEntry * qst = TO_PLAYER(mKiller)->GetQuestLogForEntry(12722);
			if(qst)
			{	
				qst->SetMobCount( 1, qst->GetMobCount(1)+1 );
				qst->SendUpdateAddKill(1);
				qst->UpdatePlayerFields();
			}
		}
		RemoveAIUpdateEvent();
	}
protected:
};

/************CHAPITRE IV*************************/
class ViergeValkyrieSoin : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(ViergeValkyrieSoin);

    ViergeValkyrieSoin(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		RegisterAIUpdateEvent(5000);
    }		

    void AIUpdate()
	{
		for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
		{ 
			if(!(*itr)->IsPlayer())
				continue;
			Player* plr = TO_PLAYER((*itr));
			if(plr && plr->m_phase == 4)
			{
				plr->CastSpell(plr, 53642, true);
				plr->CastSpell(plr, 47668, true);
			}
		}
	}
protected:
};

class QueteLaissonsLasouffranceSoldiers : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(QueteLaissonsLasouffranceSoldiers);

	QueteLaissonsLasouffranceSoldiers(Creature* pCreature) : CreatureAIScript(pCreature){   }
	void OnDied(Unit* mKiller)
    {
		if(!mKiller->IsPlayer())
			return;
		QuestLogEntry * qst = TO_PLAYER(mKiller)->GetQuestLogForEntry(12678);
		if(qst)
		{	
			qst->SetMobCount( 0, qst->GetMobCount(0)+1 );
			qst->SendUpdateAddKill(0);
			qst->UpdatePlayerFields();
		}
		QuestLogEntry * qst2 = TO_PLAYER(mKiller)->GetQuestLogForEntry(12722);
		if(qst2)
		{	
			qst2->SetMobCount( 0, qst2->GetMobCount(0)+1 );
			qst2->SendUpdateAddKill(0);
			qst2->UpdatePlayerFields();
		}
		RemoveAIUpdateEvent();
	}
};

class QueteLaissonsLasouffrancePeasants : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(QueteLaissonsLasouffrancePeasants);

	QueteLaissonsLasouffrancePeasants(Creature* pCreature) : CreatureAIScript(pCreature){   }
	void OnDied(Unit* mKiller)
    {
		if(!mKiller->IsPlayer())
			return;
		QuestLogEntry * qst = TO_PLAYER(mKiller)->GetQuestLogForEntry(12678);
		if(qst)
		{	
			qst->SetMobCount( 1, qst->GetMobCount(1)+1 );
			qst->SendUpdateAddKill(1);
			qst->UpdatePlayerFields();
		}
		QuestLogEntry * qst2 = TO_PLAYER(mKiller)->GetQuestLogForEntry(12722);
		if(qst2)
		{	
			qst2->SetMobCount( 1, qst2->GetMobCount(1)+1 );
			qst2->SendUpdateAddKill(1);
			qst2->UpdatePlayerFields();
		}
		RemoveAIUpdateEvent();
	}
};

/*class LaPuissanceDuFleau : public QuestScript 
{ 
public:

	void OnQuestStart( Player* mTarget, QuestLogEntry * qLogEntry)
	{
		mTarget->m_phase = 4;
	}
};*/

class LaVolonteDuRoiLiche : public QuestScript 
{ 
public:

	void OnQuestStart( Player* mTarget, QuestLogEntry * qLogEntry)
	{
		mTarget->m_phase = 4;
	}
};

class ApocalypseEcarlate : public QuestScript 
{ 
public:

	void OnQuestStart( Player* mTarget, QuestLogEntry * qLogEntry)
	{
		mTarget->m_phase = 64;
	}
	void OnQuestFinished(Player* plr, Quest* qst, Object *qst_giver, uint32 reward_slot)
	{
		plr->m_phase = 1;
		plr->CastSpell(plr, 53822, true);
	}
};

/*class ReprendreAcherus : public QuestScript 
{ 
public:

	void OnQuestStart( Player* mTarget, QuestLogEntry * qLogEntry)
	{
		mTarget->m_phase = 5;
	}
};*/

void SetupEbonHold(ScriptMgr * mgr)
{
	mgr->register_creature_script( 28611, &QueteLaissonsLasouffranceSoldiers::Create);
	mgr->register_creature_script( 28608, &QueteLaissonsLasouffranceSoldiers::Create);
	mgr->register_creature_script( 28609, &QueteLaissonsLasouffranceSoldiers::Create);

	mgr->register_creature_script( 28936, &QueteLaissonsLasouffranceSoldiers::Create);
	mgr->register_creature_script( 28610, &QueteLaissonsLasouffranceSoldiers::Create);
	mgr->register_creature_script( 28939, &QueteLaissonsLasouffranceSoldiers::Create);
	mgr->register_creature_script( 28940, &QueteLaissonsLasouffranceSoldiers::Create);

	//mgr->register_quest_script( 12657, (QuestScript*)new LaPuissanceDuFleau );
	mgr->register_quest_script( 12714, (QuestScript*)new LaVolonteDuRoiLiche );
	mgr->register_quest_script( 12778, (QuestScript*)new ApocalypseEcarlate );
	//mgr->register_quest_script( 13165, (QuestScript*)new ReprendreAcherus );

	mgr->register_creature_script( 28576, &QueteLaissonsLasouffrancePeasants::Create);
	mgr->register_creature_script( 28557, &QueteLaissonsLasouffrancePeasants::Create);

	mgr->register_creature_script( 28941, &QueteLaissonsLasouffrancePeasants::Create);
	mgr->register_creature_script( 28942, &QueteLaissonsLasouffrancePeasants::Create);

	mgr->register_gameobject_script(191538, &Doodad_Nox_portal_purple_bossroom01::Create);
	mgr->register_gameobject_script(191539, &Doodad_Nox_portal_purple_bossroom17::Create);
	GossipScript * SGO = (GossipScript*) new ScourgeGryphonOne();
	mgr->register_gossip_script(29488, SGO);
	GossipScript * SGT = (GossipScript*) new ScourgeGryphonTwo();
	mgr->register_gossip_script(29501, SGT);

	mgr->register_creature_script( 29519, &InitieIndigne::Create);
	mgr->register_creature_script( 29520, &InitieIndigne::Create);
	mgr->register_creature_script( 29565, &InitieIndigne::Create);
	mgr->register_creature_script( 29567, &InitieIndigne::Create);
	mgr->register_creature_script( 29566, &InitieIndigne::Create);
	
	mgr->register_creature_script( 29566, &OeilAcherusAI::Create);

	mgr->register_creature_script( 28385, &PrisonnierEcarlate::Create);
	mgr->register_gameobject_script(191588, &AcherusSoulPrison::Create);
    mgr->register_gameobject_script(191577, &AcherusSoulPrison::Create);
    mgr->register_gameobject_script(191580, &AcherusSoulPrison::Create);
    mgr->register_gameobject_script(191581, &AcherusSoulPrison::Create);
    mgr->register_gameobject_script(191582, &AcherusSoulPrison::Create);
    mgr->register_gameobject_script(191583, &AcherusSoulPrison::Create);
    mgr->register_gameobject_script(191584, &AcherusSoulPrison::Create);
    mgr->register_gameobject_script(191585, &AcherusSoulPrison::Create);
    mgr->register_gameobject_script(191586, &AcherusSoulPrison::Create);
    mgr->register_gameobject_script(191587, &AcherusSoulPrison::Create);
    mgr->register_gameobject_script(191589, &AcherusSoulPrison::Create);
    mgr->register_gameobject_script(191590, &AcherusSoulPrison::Create);

	mgr->register_gameobject_script(191609, &OeilAcherus::Create);

	mgr->register_creature_script(28406, &ChevalierDeLaMortPhase1::Create);
	mgr->register_gossip_script( 28406, (GossipScript*) new DuelChevalierDeLaMortPhase1);
	mgr->register_gossip_script( 28605, (GossipScript*) new VolerLeCheval);
	mgr->register_gossip_script( 28606, (GossipScript*) new VolerLeCheval);
	mgr->register_gossip_script( 28607, (GossipScript*) new VolerLeCheval);
	mgr->register_creature_script( 28653, &SalanarLeCavalierQueteAI::Create);

	mgr->register_creature_script( 28768, &CavalierNoirAcherus::Create);

	mgr->register_creature_script( 28577, &CitoyenDK::Create);
	mgr->register_creature_script( 28576, &CitoyenDK::Create);
	mgr->register_creature_script( 28577, &CitoyenDK::Create);
	mgr->register_creature_script( 28559, &CitoyenDK::Create);
	mgr->register_creature_script( 28534, &ViergeValkyrieSoin::Create);
}