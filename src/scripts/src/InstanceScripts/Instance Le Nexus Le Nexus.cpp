#include "StdAfx.h"
#include "Setup.h"

/** Boss (4)

	Anomalus
	Grand magus Telestra
	Keristrasza
	Ormorok le Sculpte-arbre

**/

// Boss
#define Anomalus					26763
// Sort
#define Attraction_arcanique		57063
#define Bouclier_des_failles		47748
#define Charger_les_failles			47747
#define Etincelle					47751
#define Etincelle_heroic			57062

class AnomalusAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(AnomalusAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    AnomalusAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Attraction_arcanique);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = true;
		spells[0].cooldown = 25;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 1000;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 50.0f;

		spells[1].info = dbcSpell.LookupEntry(Bouclier_des_failles);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
		
		spells[2].info = dbcSpell.LookupEntry(Charger_les_failles);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[3].info = dbcSpell.LookupEntry(Etincelle);
			spells[3].targettype = TARGET_RANDOM_SINGLE;
			spells[3].instant = true;
			spells[3].cooldown = 15;
			spells[3].perctrigger = 38.0f;
			spells[3].attackstoptimer = 1000;
			spells[3].mindist2cast = 0.0f;
			spells[3].maxdist2cast = 40.0f;
		}
		else
		{
			spells[3].info = dbcSpell.LookupEntry(Etincelle);
			spells[3].targettype = TARGET_RANDOM_SINGLE;
			spells[3].instant = true;
			spells[3].cooldown = 15;
			spells[3].perctrigger = 38.0f;
			spells[3].attackstoptimer = 1000;
			spells[3].mindist2cast = 0.0f;
			spells[3].maxdist2cast = 40.0f;
		}
		
		Vague = 1;
		Phase = 0;
    }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Vague = 1;
		Phase = 0;

		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Le chaos appel.");
		_unit->PlaySoundToSet(13186);
    }

   void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		_unit->RemoveAura(Bouclier_des_failles);		
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		GameObjectPointer pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(281.923f, -25.4521f, -16.9398f, 188526);

	    if(pDoor == 0)
            return;

        //Permettre que la shere soit utilisable
		pDoor->SetUInt32Value(GAMEOBJECT_FLAGS, 0);
		
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Bien sûr.");
		_unit->PlaySoundToSet(13187);
		RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		switch (Phase)
		{
			case 0:
				Phase1();
				break;
			case 1:
				Phase2();
				break;
			case 2:
				Phase3();
				break;
		}
	}
	
	void Phase1()
	{
		if(_unit->GetHealthPct() <= 75 && Vague == 1|| _unit->GetHealthPct() <= 50 && Vague == 2 || _unit->GetHealthPct() <= 25 && Vague == 3)
		{
			Vague++;
			Voix = true;
			Phase = 1;
		}

		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}
	
	void Phase2()
	{
		if(Voix)
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "La réalité... détramés.");
			_unit->PlaySoundToSet(13188);
			
			int RandomSpeach = RandomUInt(2);
			switch (RandomSpeach)
			{
				case 0:
				{
					Faille1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(26918, 652.694031f, -273.651245f, -8.750579f, 3.765200f, true, false, 0, 0);
					Faille2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(26918, 626.705017f, -305.252930f, -9.441467f, 1.334393f, true, false, 0, 0);
 					Faille1->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(652.694031f, -273.651245f, -8.750579f, 26918);
					Faille2->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(626.705017f, -305.252930f, -9.441467f, 26918);
					
					std::vector<UnitPointer> TargetTable; 
			
					for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
					{ 
						if ((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
						{
							UnitPointer RandomTarget = NULLUNIT;
							RandomTarget = TO_UNIT(*itr);
							TargetTable.push_back(RandomTarget);
						} 
					}

					if (!TargetTable.size())
						return;

					size_t RandTarget = rand()%TargetTable.size();
					UnitPointer RTarget = TargetTable[RandTarget];

					if (!RTarget)
						return;
				
					Faille1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
					Faille2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				}
				break;
				
				case 1:
				{
					Faille1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(26918, 651.034790f, -297.092834f, -9.363692f, 2.121362f, true, false, 0, 0);
					Faille2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(26918, 621.560608f, -282.248230f, -9.044844f, 0.596905f, true, false, 0, 0);
					Faille1->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(651.034790f, -297.092834f, -9.363692f, 26918);
					Faille2->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(621.560608f, -282.248230f, -9.044844f, 26918);
					
					std::vector<UnitPointer> TargetTable; 
			
					for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
					{ 
						if ((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
						{
							UnitPointer RandomTarget = NULLUNIT;
							RandomTarget = TO_UNIT(*itr);
							TargetTable.push_back(RandomTarget);
						} 
					}

					if (!TargetTable.size())
						return;

					size_t RandTarget = rand()%TargetTable.size();
					UnitPointer RTarget = TargetTable[RandTarget];

					if (!RTarget)
						return;
				
					Faille1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
					Faille2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				}
				break;
				
				case 2:
				{
					Faille1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(26918, 639.876343f, -313.089844f, -9.477963f, 1.594356f, true, false, 0, 0);
					Faille2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(26918, 634.896667f, -266.541321f, -8.453812f, 3.529578f, true, false, 0, 0);
					Faille1->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(639.876343f, -313.089844f, -9.477963f, 26918);
					Faille2->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(634.896667f, -266.541321f, -8.453812f, 26918);
					
					std::vector<UnitPointer> TargetTable; 
			
					for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
					{ 
						if ((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
						{
							UnitPointer RandomTarget = NULLUNIT;
							RandomTarget = TO_UNIT(*itr);
							TargetTable.push_back(RandomTarget);
						} 
					}

					if (!TargetTable.size())
						return;

					size_t RandTarget = rand()%TargetTable.size();
					UnitPointer RTarget = TargetTable[RandTarget];

					if (!RTarget)
						return;
				
					Faille1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
					Faille2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				}
				break;
			}
			Phase = 2;
		}
	}
	
	void Phase3()
	{
		if(Voix)
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Indestructible.");
			_unit->PlaySoundToSet(13189);
			_unit->CastSpell(Faille1, spells[2].info, spells[2].instant);
			_unit->CastSpell(Faille2, spells[2].info, spells[2].instant);
			_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
			Voix = false;
		}
		
		uint32 Faille_mortes = 2;
		
		if ((Faille1 != NULL && !Faille1->isAlive()))
		{
			Faille_mortes--;
		}
		
		if ((Faille2 != NULL && !Faille2->isAlive()))
		{
			Faille_mortes--;
		}
		
		if (Faille_mortes == 0 || !_unit->HasAura(Bouclier_des_failles))
		{
			_unit->RemoveAura(Bouclier_des_failles);
			Phase = 0;
		}
	}

	void SpellCast(float val)
    {
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr)  
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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
		bool Voix;
		int nrspells, Vague;
		uint32 Phase;
		UnitPointer Faille1, Faille2;
};

// Boss
#define Grand_magus_Telestra		26731
// Sort
#define Bombe_incendiaire			47773
#define Bombe_incendiaire_Heroic	56934
#define Nova_de_glace				47772
#define Nova_de_glace_Heroic		56935
#define Puits_de_gravité			47756

class Grand_magus_TelestraAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Grand_magus_TelestraAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Grand_magus_TelestraAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Bombe_incendiaire);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 55.0f;
			spells[0].attackstoptimer = 1500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Bombe_incendiaire);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 55.0f;
			spells[0].attackstoptimer = 1500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Nova_de_glace);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 30.0f;
			spells[1].attackstoptimer = 2000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Nova_de_glace_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 2000;
		}
		
		spells[2].info = dbcSpell.LookupEntry(Puits_de_gravité);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = false;
		spells[2].cooldown = 35;
		spells[2].perctrigger = 25.0f;
		spells[2].attackstoptimer = 7000;
		
		Phase = 0;
		Vague = 1;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Phase = 0;
		Vague = 1;

		RegisterAIUpdateEvent(1000);
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Vous savez ce que l'on dit sur la curiosité.");
		_unit->PlaySoundToSet(13319);
    }

	void OnTargetDied(UnitPointer mTarget)
    {
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "La mort vous va si bien!");
		_unit->PlaySoundToSet(13324);
	}

   void OnCombatStop(UnitPointer mTarget)
    {
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		GameObjectPointer pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(322.153f, 14.6832f, -16.8019f, 188527);

	    if(pDoor == 0)
            return;

        //Permettre que la shere soit utilisable
		pDoor->SetUInt32Value(GAMEOBJECT_FLAGS, 0);
		
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Maudit... hasard.");
		_unit->PlaySoundToSet(13320);
		RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		switch (Phase)
		{
			case 0:
				Phase1();
				break;
			case 1:
				Phase2();
				break;
			case 2:
				Phase3();
				break;
		}
	}
	
	void Phase1()
	{
		if(_unit->GetHealthPct() <= 50 && Vague == 1) 
		{
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			_unit->m_invisible = true;
			_unit->GetAIInterface()->disable_melee = true;
			voix = true;
			Invocation_des_clones = true;
			Phase = 1;
			Vague++;
		}
		else if(_unit->GetHealthPct() <= 15 && Vague == 2)
		{
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			_unit->m_invisible = true;
			_unit->GetAIInterface()->disable_melee = true;
			voix = true;
			Invocation_des_clones = true;
			Phase = 1;
			Vague++;
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}
	
	void Phase2()
	{
		if(voix)
		{
			int RandomSpeach = RandomUInt(2);
			switch (RandomSpeach)
			{
				case 0:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Vous allez être trop bien servi.");
					_unit->PlaySoundToSet(13321);
					voix = false;
					break;
				
				case 1:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Il y en aura assez pour tout le monde.");
					_unit->PlaySoundToSet(13322);
					voix = false;
					break;
			}
		}
		
		if(Invocation_des_clones)
		{
			Clone_de_givre 	= _unit->GetMapMgr()->GetInterface()->SpawnCreature(26930, _unit->GetPositionX()-5, _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			Clone_de_feu 	= _unit->GetMapMgr()->GetInterface()->SpawnCreature(26928, _unit->GetPositionX()+5, _unit->GetPositionY()-5, _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			Clone_d_arcane 	= _unit->GetMapMgr()->GetInterface()->SpawnCreature(26929, _unit->GetPositionX()+5, _unit->GetPositionY()+15, _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			
			Clone_de_givre->GetAIInterface()->m_moveRun = true;
			Clone_de_feu->GetAIInterface()->m_moveRun = true;
			Clone_d_arcane->GetAIInterface()->m_moveRun = true;
			
			std::vector<UnitPointer> TargetTable; 
			
			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if ((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
				{
					UnitPointer RandomTarget = NULLUNIT;
					RandomTarget = TO_UNIT(*itr);
					TargetTable.push_back(RandomTarget);
				} 
			}

			if (!TargetTable.size())
				return;

			size_t RandTarget = rand()%TargetTable.size();
			UnitPointer RTarget = TargetTable[RandTarget];

			if (!RTarget)
				return;
				
			Clone_de_givre->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Clone_de_feu->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Clone_d_arcane->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Invocation_des_clones = false;
		}
	
		uint32 Clone = 3;
		if ((Clone_de_givre != NULL && !Clone_de_givre->isAlive()))
		{
			Clone--;
		}
		
		if ((Clone_de_feu != NULL && !Clone_de_feu->isAlive()))
		{
			Clone--;
		}
		
		if ((Clone_d_arcane != NULL && !Clone_d_arcane->isAlive()))
		{
			Clone--;
		}
		
		if (Clone == 0)
		{
			_unit->SetPosition(504.995667f, 89.183929f, -16.124613f, 3.861017f, false);
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
			_unit->m_invisible = false;
			_unit->GetAIInterface()->disable_melee = false;
			_unit->GetAIInterface()->StopMovement(7000);
			_unit->CastSpell(_unit, spells[2].info, spells[2].instant);
			
			if(Vague == 2)
			{
				Phase = 0;
			}
			else if(Vague = 3)
			{
				Phase = 0;
			}
		}
	}
	
	void Phase3()
	{
		if(voix)
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Et maintenant finissons le travail!");
			_unit->PlaySoundToSet(13323);
			voix = false;
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}

	void SpellCast(float val)
    {
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr)  
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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
		bool voix, Invocation_des_clones;
		int nrspells, Vague;
		uint32 Phase;
		UnitPointer Clone_de_givre, Clone_de_feu, Clone_d_arcane;
};

// Boss
#define Keristrasza							26723
// Sort
#define Prison_gelée						47854
#define Chaînes_de_cristal					50997
#define Coup_de_queue						50155
#define Cristalliser						48179
#define Enrager 							8599
#define Froid_intense						48095
#define Souffle_de_cristal_de_feu			48096
#define Souffle_de_cristal_de_feu_heroic	57091

class KeristraszaAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(KeristraszaAI);
	SP_AI_Spell spells[5];
	bool m_spellcheck[5];

    KeristraszaAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 5;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Chaînes_de_cristal);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = true;
		spells[0].cooldown = 20;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 1000;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 45.0f;
		spells[0].speech = "Restez. Profitez de vos derniers instants.";
		spells[0].soundid = 13451;

		spells[1].info = dbcSpell.LookupEntry(Coup_de_queue);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 15;
		spells[1].perctrigger = 35.0f;
		spells[1].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode == MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Cristalliser);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 15.0f;
			spells[2].attackstoptimer = 1000;
		}
		
		spells[3].info = dbcSpell.LookupEntry(Enrager);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 0.0f;
		spells[3].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[4].info = dbcSpell.LookupEntry(Souffle_de_cristal_de_feu);
			spells[4].targettype = TARGET_RANDOM_SINGLE;
			spells[4].instant = false;
			spells[4].cooldown = 20;
			spells[4].perctrigger = 20.0f;
			spells[4].attackstoptimer = 1000;
			spells[4].mindist2cast = 0.0f;
			spells[4].maxdist2cast = 30.0f;
		}
		else
		{
			spells[4].info = dbcSpell.LookupEntry(Souffle_de_cristal_de_feu_heroic);
			spells[4].targettype = TARGET_RANDOM_SINGLE;
			spells[4].instant = false;
			spells[4].cooldown = 20;
			spells[4].perctrigger = 20.0f;
			spells[4].attackstoptimer = 1000;
			spells[4].mindist2cast = 0.0f;
			spells[4].maxdist2cast = 30.0f;
		}
		
		_unit->CastSpell(_unit, Prison_gelée, true);
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		Rage = false;
	}
	
	void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Rage = false;

		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "La préservé? Pourquoi? La vérité n'est pas là. Non non non non... ha ha ha... Seulement dans l'emprise! Je le vois maintenant!");
		_unit->PlaySoundToSet(13450);
    }

	void OnTargetDied(UnitPointer mTarget)
    {
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Voilà enfin la vérité!");
		_unit->PlaySoundToSet(13453);
	}

   void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		_unit->RemoveAura(Enrager);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Reine Dragon... lieuse de vie... préserve... moi.");
		_unit->PlaySoundToSet(13454);
		RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		unordered_set<PlayerPointer>::iterator DetectionItr = _unit->GetInRangePlayerSetBegin();
		for(; DetectionItr != _unit->GetInRangePlayerSetEnd(); DetectionItr++)
		{
			if((*DetectionItr)->GetTypeId() == TYPEID_PLAYER)
			{
				if( _unit->CalcDistance((*DetectionItr)) <= 80.0f )
				{
					(*DetectionItr)->CastSpell((*DetectionItr), dbcSpell.LookupEntry(Froid_intense), true);
				}
			}
		}
		
		if(_unit->GetHealthPct() <= 25 && !Rage)
		{
			_unit->CastSpell(_unit, spells[3].info, spells[3].instant);
			_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Finissons-en! Finissons-en! Tuer-moi, où je jure sur la Reine Dragon que vous ne verrez plus jamais la lumière du jour!");
			_unit->PlaySoundToSet(13452);
			Rage = true;
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}

	void SpellCast(float val)
    {
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr)  
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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
		bool Rage;
		int nrspells;
};


// Boss
#define Ormorok_le_Sculpte_arbre			26794
// Sort
#define Frénésie							57086
#define Frénésie_heroic						48017
#define Piétiner							48016
#define Piétiner_heroic						57066
#define Renvoi_de_sort						47981

class Ormorok_le_Sculpte_arbreAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Ormorok_le_Sculpte_arbreAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Ormorok_le_Sculpte_arbreAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Frénésie);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = -1;
			spells[0].perctrigger = 0.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Frénésie_heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = -1;
			spells[0].perctrigger = 0.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Piétiner);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Piétiner_heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1000;
		}

		spells[2].info = dbcSpell.LookupEntry(Renvoi_de_sort);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = false;
		spells[2].cooldown = 55;
		spells[2].perctrigger = 15.0f;
		spells[2].attackstoptimer = 2000;
		spells[2].speech = "Arrière!";
		spells[2].soundid = 13331;
		
		Rage = false;
		Invocation = 30;
		Pointe_de_Crystal = 8;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Rage = false;
		Invocation = 30;
		Pointe_de_Crystal = 8;

		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Nooon!");
		_unit->PlaySoundToSet(13328);
    }

	void OnTargetDied(UnitPointer mTarget)
    {
		_unit->PlaySoundToSet(13329);
	}

   void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		_unit->RemoveAura(Frénésie);
		_unit->RemoveAura(Frénésie_heroic);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		GameObjectPointer pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(282.664f, 13.9118f, -16.6055f, 188528);

	    if(pDoor == 0)
            return;

        //Permettre que la shere soit utilisable
		pDoor->SetUInt32Value(GAMEOBJECT_FLAGS, 0);
		
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Aaggh!");
		_unit->PlaySoundToSet(13330);
		RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		if(_unit->GetHealthPct() <= 25 && !Rage)
		{
			_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
			Rage = true;
		}
		
		if(Pointe_de_Crystal < 1)
		{
			_unit->GetAIInterface()->StopMovement(4000);
			_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Saiiiigne!");
			_unit->PlaySoundToSet(13332);
			
			int RandomSpeach = RandomUInt(1);
			switch (RandomSpeach)
			{
				case 0:
				{
					for (int i = 1; i < 7; i++)
					{
						_unit->GetMapMgr()->GetInterface()->SpawnCreature(27099, _unit->GetPositionX()+( i * 3), _unit->GetPositionY()+( i * 3), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
						_unit->GetMapMgr()->GetInterface()->SpawnCreature(27099, _unit->GetPositionX()+( i * 3), _unit->GetPositionY()-( i * 3), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
						_unit->GetMapMgr()->GetInterface()->SpawnCreature(27099, _unit->GetPositionX()-( i * 3), _unit->GetPositionY()+( i * 3), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
						_unit->GetMapMgr()->GetInterface()->SpawnCreature(27099, _unit->GetPositionX()-( i * 3), _unit->GetPositionY()-( i * 3), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
					}
					break;
				}
				case 1:
				{
					for (int i = 1; i < 7; i++)
					{
						_unit->GetMapMgr()->GetInterface()->SpawnCreature(27099, _unit->GetPositionX()+( i * 3), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
						_unit->GetMapMgr()->GetInterface()->SpawnCreature(27099, _unit->GetPositionX(), _unit->GetPositionY()-( i * 3), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
						_unit->GetMapMgr()->GetInterface()->SpawnCreature(27099, _unit->GetPositionX(), _unit->GetPositionY()+( i * 3), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
						_unit->GetMapMgr()->GetInterface()->SpawnCreature(27099, _unit->GetPositionX()-( i * 3), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
					}
					break;
				}
			}
			Pointe_de_Crystal = 8;
		}
		else if(Invocation < 1 && _unit->GetMapMgr()->iInstanceMode == MODE_HEROIC)
		{
			std::vector<UnitPointer> TargetTable; 
			
			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if ((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
				{
					UnitPointer RandomTarget = NULLUNIT;
					RandomTarget = TO_UNIT(*itr);

					TargetTable.push_back(RandomTarget);
				} 
			}


			if (!TargetTable.size())
				return;

			size_t RandTarget = rand()%TargetTable.size();

			UnitPointer RTarget = TargetTable[RandTarget];

			if (!RTarget)
				return;
				
			_unit->GetMapMgr()->GetInterface()->SpawnCreature(32665, RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation(), true, false, 0, 0);
			Invocation = 30;
		}
		else
		{
			Pointe_de_Crystal--;
			Invocation--;
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}

	void SpellCast(float val)
    {
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr)  
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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
		bool Rage;
		int nrspells;
		uint32 Pointe_de_Crystal, Invocation;
};


/** Gameobjet event (3)

	Sphère de confinement d' Anomalus 
	Sphère de confinement de  la Grand magus Telestra
	Sphère de confinement d' Ormorok le Sculpte-arbre
	
**/

// Gameobject
#define Sphère_de_confinement_d_Anomalus	188526

class Sphère_de_confinement_d_AnomalusAI : public GameObjectAIScript
{
public:
	Sphère_de_confinement_d_AnomalusAI(GameObjectPointer goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObjectPointer GO) { return new Sphère_de_confinement_d_AnomalusAI(GO); }
	
	void OnActivate(PlayerPointer pPlayer)
	{
		GameObjectPointer pDoor  = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(281.923f, -25.4521f, -16.9398f, 188526);
		GameObjectPointer pDoor2 = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(322.153f, 14.6832f, -16.8019f, 188527);
		GameObjectPointer pDoor3 = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(282.664f, 13.9118f, -16.6055f, 188528);
		UnitPointer Keris =  pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(302.152008f, -5.190070f, -15.564100f, 26723);

		if((pDoor2->GetUInt32Value(GAMEOBJECT_FLAGS) == 1) || (pDoor3->GetUInt32Value(GAMEOBJECT_FLAGS) == 1))
            return;

		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		pDoor->SetUInt32Value(GAMEOBJECT_FLAGS, 1);
		pDoor2->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		pDoor2->SetUInt32Value(GAMEOBJECT_FLAGS, 1);
		pDoor3->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		pDoor3->SetUInt32Value(GAMEOBJECT_FLAGS, 1);
		Keris->RemoveAura(Prison_gelée);
		Keris->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
		Keris->GetAIInterface()->SetAllowedToEnterCombat(true);
		Keris->GetAIInterface()->m_moveRun = true;
		
		std::vector<UnitPointer> TargetTable; 
			
		for(unordered_set<ObjectPointer>::iterator itr = Keris->GetInRangeSetBegin(); itr != Keris->GetInRangeSetEnd(); ++itr) 
		{ 
			if ((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
			{
				UnitPointer RandomTarget = NULLUNIT;
				RandomTarget = TO_UNIT(*itr);
				TargetTable.push_back(RandomTarget);
			} 
		}

		if (!TargetTable.size())
			return;

		size_t RandTarget = rand()%TargetTable.size();
		UnitPointer RTarget = TargetTable[RandTarget];

		if (!RTarget)
			return;
				
		Keris->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
	}
};

// Gameobject
#define Sphère_de_confinement_du_Grand_magus_Telestra	188527

class Sphère_de_confinement_du_Grand_magus_TelestraAI : public GameObjectAIScript
{
public:
	Sphère_de_confinement_du_Grand_magus_TelestraAI(GameObjectPointer goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObjectPointer GO) { return new Sphère_de_confinement_du_Grand_magus_TelestraAI(GO); }
	
	void OnActivate(PlayerPointer pPlayer)
	{
		GameObjectPointer pDoor  = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(281.923f, -25.4521f, -16.9398f, 188526);
		GameObjectPointer pDoor2 = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(322.153f, 14.6832f, -16.8019f, 188527);
		GameObjectPointer pDoor3 = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(282.664f, 13.9118f, -16.6055f, 188528);
		UnitPointer Keris =  pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(302.152008f, -5.190070f, -15.564100f, 26723);

		if((pDoor->GetUInt32Value(GAMEOBJECT_FLAGS) == 1) || (pDoor3->GetUInt32Value(GAMEOBJECT_FLAGS) == 1))
            return;

		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		pDoor->SetUInt32Value(GAMEOBJECT_FLAGS, 1);
		pDoor2->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		pDoor2->SetUInt32Value(GAMEOBJECT_FLAGS, 1);
		pDoor3->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		pDoor3->SetUInt32Value(GAMEOBJECT_FLAGS, 1);
		Keris->RemoveAura(Prison_gelée);
		Keris->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
		Keris->GetAIInterface()->SetAllowedToEnterCombat(true);
		Keris->GetAIInterface()->m_moveRun = true;
		
		std::vector<UnitPointer> TargetTable; 
			
		for(unordered_set<ObjectPointer>::iterator itr = Keris->GetInRangeSetBegin(); itr != Keris->GetInRangeSetEnd(); ++itr) 
		{ 
			if ((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
			{
				UnitPointer RandomTarget = NULLUNIT;
				RandomTarget = TO_UNIT(*itr);
				TargetTable.push_back(RandomTarget);
			} 
		}

		if (!TargetTable.size())
			return;

		size_t RandTarget = rand()%TargetTable.size();
		UnitPointer RTarget = TargetTable[RandTarget];

		if (!RTarget)
			return;
				
		Keris->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
	}
};

// Gameobject
#define Sphère_de_confinement_d_Ormorok_le_Sculpte_arbre	188528

class Sphère_de_confinement_d_Ormorok_le_Sculpte_arbreAI : public GameObjectAIScript
{
public:
	Sphère_de_confinement_d_Ormorok_le_Sculpte_arbreAI(GameObjectPointer goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObjectPointer GO) { return new Sphère_de_confinement_d_Ormorok_le_Sculpte_arbreAI(GO); }
	
	void OnActivate(PlayerPointer pPlayer)
	{
		GameObjectPointer pDoor  = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(281.923f, -25.4521f, -16.9398f, 188526);
		GameObjectPointer pDoor2 = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(322.153f, 14.6832f, -16.8019f, 188527);
		GameObjectPointer pDoor3 = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(282.664f, 13.9118f, -16.6055f, 188528);
		UnitPointer Keris =  pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(302.152008f, -5.190070f, -15.564100f, 26723);

		if((pDoor->GetUInt32Value(GAMEOBJECT_FLAGS) == 1) || (pDoor2->GetUInt32Value(GAMEOBJECT_FLAGS) == 1))
            return;

		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		pDoor->SetUInt32Value(GAMEOBJECT_FLAGS, 1);
		pDoor2->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		pDoor2->SetUInt32Value(GAMEOBJECT_FLAGS, 1);
		pDoor3->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		pDoor3->SetUInt32Value(GAMEOBJECT_FLAGS, 1);
		Keris->RemoveAura(Prison_gelée);
		Keris->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
		Keris->GetAIInterface()->SetAllowedToEnterCombat(true);
		Keris->GetAIInterface()->m_moveRun = true;
		
		std::vector<UnitPointer> TargetTable; 
			
		for(unordered_set<ObjectPointer>::iterator itr = Keris->GetInRangeSetBegin(); itr != Keris->GetInRangeSetEnd(); ++itr) 
		{ 
			if ((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
			{
				UnitPointer RandomTarget = NULLUNIT;
				RandomTarget = TO_UNIT(*itr);
				TargetTable.push_back(RandomTarget);
			} 
		}

		if (!TargetTable.size())
			return;

		size_t RandTarget = rand()%TargetTable.size();
		UnitPointer RTarget = TargetTable[RandTarget];

		if (!RTarget)
			return;
				
		Keris->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
	}
};

/** Add Boss (6)

	Faille_chaotique
	Grand magus Telestra clone de givre
	Grand magus Telestra clone de feu
	Grand magus Telestra clone d' arcane
	Noueur cristallin
	Pointe de cristal
	
**/

// Mob
#define Faille_chaotique					26918
// Sort
#define Aura_de_faille_chaotique			47687
#define Vague_d_énergie_chaotique			47688
#define Vague_d_énergie_chaotique_chargée	47737

class Faille_chaotiqueAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Faille_chaotiqueAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Faille_chaotiqueAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Vague_d_énergie_chaotique);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 35.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 15.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Vague_d_énergie_chaotique_chargée);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 35.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 50.0f;
		}
		
		Visuel = false;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Visuel = false;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->Despawn(5000,0);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		_unit->Despawn(2000,0);
		RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		if(!Visuel)
		{
			_unit->CastSpell(_unit, dbcSpell.LookupEntry(Aura_de_faille_chaotique), true);
			Visuel = true;
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}

	void SpellCast(float val)
    {
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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
		bool Visuel;
		int nrspells;
};

// Add Boss
#define Grand_magus_Telestra_clone_de_givre		26930
// Sort
#define Barbelés_de_glace						47729
#define Barbelés_de_glace_Heroic				56937
#define Blizzard								47727
#define Blizzard_Heroic							56936

class Grand_magus_Telestra_clone_de_givreAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Grand_magus_Telestra_clone_de_givreAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Grand_magus_Telestra_clone_de_givreAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Barbelés_de_glace);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 45.0f;
			spells[0].attackstoptimer = 500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 100.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Barbelés_de_glace_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 45.0f;
			spells[0].attackstoptimer = 500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 100.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Blizzard);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 45;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 6000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Blizzard_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 45;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 6000;
		}
		
		RegisterAIUpdateEvent(1000);
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->Despawn(2000,0);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		_unit->Despawn(2000,0);
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Add Boss
#define Grand_magus_Telestra_clone_de_feu		26928
// Sort
#define Brûlure									47723
#define Brûlure_Heroic							56938
#define Trait_de_feu							47721
#define Trait_de_feu_heroic						56939

class Grand_magus_Telestra_clone_de_feuAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Grand_magus_Telestra_clone_de_feuAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Grand_magus_Telestra_clone_de_feuAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Brûlure);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 35.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Brûlure_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 35.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Trait_de_feu);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 20.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Trait_de_feu_heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 20.0f;
		}
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->Despawn(5000,0);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		_unit->Despawn(2000,0);
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Add Boss
#define Grand_magus_Telestra_clone_d_arcane		26929
// Sort
#define Arrêt_du_temps							47736
#define Bestiole								47731

class Grand_magus_Telestra_clone_d_arcaneAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Grand_magus_Telestra_clone_d_arcaneAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Grand_magus_Telestra_clone_d_arcaneAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Arrêt_du_temps);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = false;
		spells[0].cooldown = 20;
		spells[0].perctrigger = 35.0f;
		spells[0].attackstoptimer = 1500;
		
		spells[1].info = dbcSpell.LookupEntry(Bestiole);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = false;
		spells[1].cooldown = 25;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 1500;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->Despawn(5000,0);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
		_unit->Despawn(2000,0);
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Add Boss
#define Noueur_cristallin		32665
// Sort
#define Enchevêtrer				61556

class Noueur_cristallinAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Noueur_cristallinAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Noueur_cristallinAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Enchevêtrer);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = false;
		spells[0].cooldown = 10;
		spells[0].perctrigger = 35.0f;
		spells[0].attackstoptimer = 1000;
	}

	void OnDamageTaken(UnitPointer mAttacker, float fAmount)
	{
		_unit->CastSpell(spells[0].targettype, spells[0].info, spells[0].instant);
	}
	
	void SpellCast(float val)
    {
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    UnitPointer target = NULLUNIT;
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
					}
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
	
	protected:
		int nrspells;
};


// Add Boss
#define Pointe_de_cristal					27099
// Sort
#define Pointe_de_cristal_Visual 			50442
#define Pointe_de_cristal_Spell				47944
#define Pointe_de_cristal_Spell_heroic		57067

class Pointe_de_cristalAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Pointe_de_cristalAI);
	Pointe_de_cristalAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
	{
		Visuel = false;
		Temps_pointe = 4;
		_unit->m_invisible = true;
		RegisterAIUpdateEvent(1000);
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
	}

	void AIUpdate()
	{
		if(!Visuel)
		{
			_unit->CastSpell(_unit, dbcSpell.LookupEntry(Pointe_de_cristal_Visual), true);
			Visuel = true;
		}
		
		if(Temps_pointe < 1)
		{
			unordered_set<PlayerPointer>::iterator TeleportItr = _unit->GetInRangePlayerSetBegin();
			for(; TeleportItr != _unit->GetInRangePlayerSetEnd(); TeleportItr++)
			{
				if((*TeleportItr)->GetTypeId() == TYPEID_PLAYER)
				{
					if( _unit->CalcDistance((*TeleportItr)) <= 3.0f )
					{
						if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
						{
							_unit->CastSpell(_unit, dbcSpell.LookupEntry(Pointe_de_cristal_Spell), true);
						}
						else
						{
							_unit->CastSpell(_unit, dbcSpell.LookupEntry(Pointe_de_cristal_Spell_heroic), true);
						}
					}
				}
			}
			_unit->Despawn(0,0);
		}
		else
		{
			Temps_pointe--;
		}
	}
	
	protected:
		bool Visuel;
		uint32 Temps_pointe;
};

/** Mob (23)

		Ame en peine de mana affolée
		Ascendant chasseur de mages
		Berserker de l'Alliance
		Berserker de la Horde
		Clerc de l'Alliance
		Clerc de la Horde
		Commandant Kolurg
		Commandant Rudebarbe
		Commandant de l'Alliance
		Commandant de la Horde
	Effilocheur cristallin
		Eruption de mana affolée
		Forestier de l'Alliance
		Forestier de la Horde
		Gardien azur
		Initié chasseur de mages
		Lieuse-d'écailles azur
		Magus azur
		Massacreur azur
		Pourfendeur de mages
		Protecteur cristallin
		Régisseur
		Sylvenier cristallin

**/

// Mob
#define Ame_en_peine_de_mana_affolée	26746
// Sort
#define Projectiles_des_arcanes			33833

class Ame_en_peine_de_mana_affoléeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Ame_en_peine_de_mana_affoléeAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Ame_en_peine_de_mana_affoléeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Projectiles_des_arcanes);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = true;
		spells[0].cooldown = 10;
		spells[0].perctrigger = 65.0f;
		spells[0].attackstoptimer = 1000;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 30.0f;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Mob
#define Ascendant_chasseur_de_mages			26727
// Sort
#define Aura_de_Hâte_des_arcanes			50182
#define Aura_de_Hâte_des_arcanes_Heroic		56827
#define Boule_de_feu						12466
#define Boule_de_feu_Heroic					17290
#define Cône_de_froid						15244
#define Cône_de_froid_Heroic				38384
#define Eclair_de_givre						12737
#define Eclair_de_givre_Heroic				56837
#define Explosion_des_arcanes				34933
#define Explosion_des_arcanes_Heroic		56825
#define Métamorphose						13323
#define Piège_d_immolation					47784
#define Piège_givrant						55040
#define Pluie_de_feu						36808
#define Pluie_de_feu_Heroic					39376

class Ascendant_chasseur_de_magesAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Ascendant_chasseur_de_magesAI);
	SP_AI_Spell spells[9];
	bool m_spellcheck[9];

    Ascendant_chasseur_de_magesAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 9;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Aura_de_Hâte_des_arcanes);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 60;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Aura_de_Hâte_des_arcanes);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 60;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Boule_de_feu);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 3000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 40.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Boule_de_feu_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 3000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 40.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Cône_de_froid);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 20;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Cône_de_froid_Heroic);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 20;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[3].info = dbcSpell.LookupEntry(Eclair_de_givre);
			spells[3].targettype = TARGET_RANDOM_SINGLE;
			spells[3].instant = false;
			spells[3].cooldown = 15;
			spells[3].perctrigger = 20.0f;
			spells[3].attackstoptimer = 3000;
			spells[3].mindist2cast = 0.0f;
			spells[3].maxdist2cast = 40.0f;
		}
		else
		{
			spells[3].info = dbcSpell.LookupEntry(Eclair_de_givre_Heroic);
			spells[3].targettype = TARGET_RANDOM_SINGLE;
			spells[3].instant = false;
			spells[3].cooldown = 15;
			spells[3].perctrigger = 20.0f;
			spells[3].attackstoptimer = 3000;
			spells[3].mindist2cast = 0.0f;
			spells[3].maxdist2cast = 40.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[4].info = dbcSpell.LookupEntry(Explosion_des_arcanes);
			spells[4].targettype = TARGET_SELF;
			spells[4].instant = true;
			spells[4].cooldown = 20;
			spells[4].perctrigger = 25.0f;
			spells[4].attackstoptimer = 1000;
		}
		else
		{
			spells[4].info = dbcSpell.LookupEntry(Explosion_des_arcanes_Heroic);
			spells[4].targettype = TARGET_SELF;
			spells[4].instant = true;
			spells[4].cooldown = 20;
			spells[4].perctrigger = 25.0f;
			spells[4].attackstoptimer = 1000;
		}
		
		spells[5].info = dbcSpell.LookupEntry(Métamorphose);
		spells[5].targettype = TARGET_RANDOM_SINGLE;
		spells[5].instant = false;
		spells[5].cooldown = 40;
		spells[5].perctrigger = 5.0f;
		spells[5].attackstoptimer = 1500;
		spells[5].mindist2cast = 0.0f;
		spells[5].maxdist2cast = 30.0f;
		
		spells[6].info = dbcSpell.LookupEntry(Piège_d_immolation);
		spells[6].targettype = TARGET_SELF;
		spells[6].instant = true;
		spells[6].cooldown = 40;
		spells[6].perctrigger = 6.0f;
		spells[6].attackstoptimer = 1000;
		
		spells[7].info = dbcSpell.LookupEntry(Piège_givrant);
		spells[7].targettype = TARGET_SELF;
		spells[7].instant = true;
		spells[7].cooldown = 40;
		spells[7].perctrigger = 7.0f;
		spells[7].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[8].info = dbcSpell.LookupEntry(Pluie_de_feu);
			spells[8].targettype = TARGET_RANDOM_DESTINATION;
			spells[8].instant = false;
			spells[8].cooldown = 30;
			spells[8].perctrigger = 10.0f;
			spells[8].attackstoptimer = 9000;
			spells[8].mindist2cast = 0.0f;
			spells[8].maxdist2cast = 30.0f;
		}
		else
		{
			spells[8].info = dbcSpell.LookupEntry(Pluie_de_feu_Heroic);
			spells[8].targettype = TARGET_RANDOM_DESTINATION;
			spells[8].instant = false;
			spells[8].cooldown = 30;
			spells[8].perctrigger = 10.0f;
			spells[8].attackstoptimer = 9000;
			spells[8].mindist2cast = 0.0f;
			spells[8].maxdist2cast = 30.0f;
		}
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Mob
#define Berserker_de_l_Alliance		26800
// Sort
#define Choc_martial				38682
#define Frénésie_BDLA				47774

class Berserker_de_l_AllianceAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Berserker_de_l_AllianceAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Berserker_de_l_AllianceAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Choc_martial);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 20;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(Frénésie_BDLA);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 40;
		spells[1].perctrigger = 5.0f;
		spells[1].attackstoptimer = 1000;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					}
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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

	protected:
		int nrspells;
};

// Mob
#define Berserker_de_la_Horde	26799
// Sort
#define Choc_martial			38682
#define Frénésie_BDLH			47774

class Berserker_de_la_HordeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Berserker_de_la_HordeAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Berserker_de_la_HordeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Choc_martial);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 20;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(Frénésie_BDLH);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 40;
		spells[1].perctrigger = 5.0f;
		spells[1].attackstoptimer = 1000;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					}
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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

	protected:
		int nrspells;
};

// Mob
#define Clerc_de_l_Alliance				26805
// Sort
#define Mot_de_l_ombre_Mort				47697
#define Mot_de_l_ombre_Mort_Heroic		56920
#define Mot_de_pouvoir_Bouclier			17139
#define Mot_de_pouvoir_Bouclier_Heroic	35944

class Clerc_de_l_AllianceAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Clerc_de_l_AllianceAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Clerc_de_l_AllianceAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Mot_de_l_ombre_Mort);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Mot_de_l_ombre_Mort_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Mot_de_pouvoir_Bouclier);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 40;
			spells[1].perctrigger = 10.0f;
			spells[1].attackstoptimer = 1500;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Mot_de_pouvoir_Bouclier_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 40;
			spells[1].perctrigger = 10.0f;
			spells[1].attackstoptimer = 1500;
		}
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Mob
#define Clerc_de_la_Horde		26803
// Sort
#define Mot_de_l_ombre_Mort				47697
#define Mot_de_l_ombre_Mort_Heroic		56920
#define Mot_de_pouvoir_Bouclier			17139
#define Mot_de_pouvoir_Bouclier_Heroic	35944

class Clerc_de_la_HordeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Clerc_de_la_HordeAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Clerc_de_la_HordeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Mot_de_l_ombre_Mort);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Mot_de_l_ombre_Mort_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Mot_de_pouvoir_Bouclier);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 40;
			spells[1].perctrigger = 10.0f;
			spells[1].attackstoptimer = 1500;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Mot_de_pouvoir_Bouclier_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 40;
			spells[1].perctrigger = 10.0f;
			spells[1].attackstoptimer = 1500;
		}
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Mob
#define Commandant_Kolurg		26798
// Sort
#define Cri_de_guerre			31403
#define Cri_effrayant			19134	// a imuniser contre peur
#define Tourbillon				38619

class Commandant_KolurgAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Commandant_KolurgAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Commandant_KolurgAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Cri_de_guerre);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 180;
		spells[0].perctrigger = 5.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Cri_effrayant);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 55;
		spells[1].perctrigger = 5.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(Tourbillon);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = 20;
		spells[2].perctrigger = 25.0f;
		spells[2].attackstoptimer = 1000;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					}
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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

	protected:
		int nrspells;
};

// Mob
#define Commandant_Rudebarbe	26796
// Sort
#define Cri_de_guerre			31403
#define Cri_effrayant			19134	// a imuniser contre peur
#define Tourbillon				38619

class Commandant_RudebarbeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Commandant_RudebarbeAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Commandant_RudebarbeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Cri_de_guerre);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 180;
		spells[0].perctrigger = 5.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Cri_effrayant);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 55;
		spells[1].perctrigger = 5.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(Tourbillon);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = 20;
		spells[2].perctrigger = 25.0f;
		spells[2].attackstoptimer = 1000;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					}
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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

	protected:
		int nrspells;
};

// Mob
#define Commandant_de_l_Alliance	27949
// Sort
#define Cri_de_guerre				31403
#define Tourbillon					38619

class Commandant_de_l_AllianceAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Commandant_de_l_AllianceAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Commandant_de_l_AllianceAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Cri_de_guerre);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 180;
		spells[0].perctrigger = 5.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(Tourbillon);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 20;
		spells[1].perctrigger = 25.0f;
		spells[1].attackstoptimer = 1000;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					}
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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

	protected:
		int nrspells;
};

// Mob
#define Commandant_de_la_Horde		27947
// Sort
#define Cri_de_guerre				31403
#define Tourbillon					38619

class Commandant_de_la_HordeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Commandant_de_la_HordeAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Commandant_de_la_HordeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Cri_de_guerre);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 180;
		spells[0].perctrigger = 5.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(Tourbillon);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 20;
		spells[1].perctrigger = 25.0f;
		spells[1].attackstoptimer = 1000;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					}
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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

	protected:
		int nrspells;
};

// Mob
#define Effilocheur_cristallin			26793
// Sort
#define Aura_de_régénération			52067
#define Aura_de_régénération_Heroic		57056
#define Cosse							48082
#define Enraciner						48053
#define Fleur_de_cristal				48058

// Mob
#define Eruption_de_mana_affolée	26737
// Sort
#define Brûlure_de_mana				48054
#define Brûlure_de_mana_Heroic		57047
#define Mana_libre					29882	// cast le spell lors de sa mort
#define Nova_des_arcanes			47696	// voir pk il soigne
#define Nova_des_arcanes_Heroic		57046

class Eruption_de_mana_affoléeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Eruption_de_mana_affoléeAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Eruption_de_mana_affoléeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Brûlure_de_mana);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Brûlure_de_mana_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Nova_des_arcanes);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1500;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Nova_des_arcanes_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1500;
		}
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Mob
#define Forestier_de_l_Alliance		26802
// Sort
#define Tir							15620
#define Tir_Heroic					22907
#define Tir_accéléré				48191
#define Tir_incendiaire				47777
#define Tir_incendiaire_Heroic		56933

class Forestier_de_l_AllianceAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Forestier_de_l_AllianceAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Forestier_de_l_AllianceAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Tir);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 5;
			spells[0].perctrigger = 45.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 5.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Tir_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 5;
			spells[0].perctrigger = 45.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 5.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Tir_accéléré);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = false;
		spells[1].cooldown = 30;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 8000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Tir_incendiaire);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = false;
			spells[2].cooldown = 20;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 5.0f;
			spells[2].maxdist2cast = 30.0f;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Tir_incendiaire_Heroic);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = false;
			spells[2].cooldown = 20;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 5.0f;
			spells[2].maxdist2cast = 30.0f;
		}
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Mob
#define Forestier_de_la_Horde		26801
// Sort
#define Tir							15620
#define Tir_Heroic					22907
#define Tir_accéléré				48191
#define Tir_incendiaire				47777
#define Tir_incendiaire_Heroic		56933

class Forestier_de_la_HordeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Forestier_de_la_HordeAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Forestier_de_la_HordeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Tir);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 5;
			spells[0].perctrigger = 45.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 5.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Tir_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 5;
			spells[0].perctrigger = 45.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 5.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Tir_accéléré);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = false;
		spells[1].cooldown = 30;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 8000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Tir_incendiaire);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = false;
			spells[2].cooldown = 20;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 5.0f;
			spells[2].maxdist2cast = 30.0f;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Tir_incendiaire_Heroic);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = false;
			spells[2].cooldown = 20;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 5.0f;
			spells[2].maxdist2cast = 30.0f;
		}
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Mob
#define Gardien_azur				26716
// Sort
#define Bouclier_de_mana			17741
#define Bouclier_de_mana_Heroic		56778
#define Silence						56777

class Gardien_azurAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Gardien_azurAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Gardien_azurAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Bouclier_de_mana);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 60;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Bouclier_de_mana_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 60;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Silence);
		spells[1].targettype = TARGET_RANDOM_SINGLE;
		spells[1].instant = true;
		spells[1].cooldown = 15;
		spells[1].perctrigger = 25.0f;
		spells[1].attackstoptimer = 1000;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 20.0f;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Mob
#define Initié_chasseur_de_mages	26728
// Sort
#define Brûlure_magique				50198
#define Brûlure_magique_Heroic		56860
#define Drain_de_mana				17682

class Initié_chasseur_de_magesAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Initié_chasseur_de_magesAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Initié_chasseur_de_magesAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Brûlure_magique);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 20.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Brûlure_magique_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 20.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Drain_de_mana);
		spells[1].targettype = TARGET_RANDOM_SINGLE;
		spells[1].instant = false;
		spells[1].cooldown = 20;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 5000;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 20.0f;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Mob
#define Lieuse_d_écailles_azur				26735
// Sort
#define Déflagration_des_arcanes			38881
#define Déflagration_des_arcanes_Heroic		56969

class Lieuse_d_écailles_azurAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Lieuse_d_écailles_azurAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Lieuse_d_écailles_azurAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Déflagration_des_arcanes);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 2500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Déflagration_des_arcanes_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 2500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Mob
#define Magus_azur					26722
// Sort
#define Eclair_de_givre_MA			15530
#define Eclair_de_givre_Heroic_MA	56775
#define Horion_des_arcanes			37132
#define Horion_des_arcanes_Heroic	56776

class Magus_azurAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Magus_azurAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Magus_azurAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Eclair_de_givre_MA);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 3000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Eclair_de_givre_Heroic_MA);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 3000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Horion_des_arcanes);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 20.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Horion_des_arcanes_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 20.0f;
		}
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Mob
#define Massacreur_azur		26734
// Sort
#define Enchaînement		15284
#define Frappe_mortelle		39171

class Massacreur_azurAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Massacreur_azurAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Massacreur_azurAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Enchaînement);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Frappe_mortelle);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 30;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 1000;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					}
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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

	protected:
		int nrspells;
};

// Mob
#define Pourfendeur_de_mages	26730
// Sort
#define Extraire_la_magie		50131

class Pourfendeur_de_magesAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Pourfendeur_de_magesAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Pourfendeur_de_magesAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Extraire_la_magie);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 25;
		spells[0].perctrigger = 15.0f;
		spells[0].attackstoptimer = 1000;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					}
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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

	protected:
		int nrspells;
};

// Mob
#define Protecteur_cristallin			26792
// Sort
#define Chaînes_de_cristal_PC			47698
#define Chaînes_de_cristal_Heroic_PC	57050
#define Coup_de_tonnerre				30633
#define Projection_d_éclats				50302
#define Projection_d_éclats_Heroic		57051

class Protecteur_cristallinAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Protecteur_cristallinAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Protecteur_cristallinAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Chaînes_de_cristal_PC);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Chaînes_de_cristal_Heroic_PC);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Coup_de_tonnerre);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = false;
		spells[1].cooldown = 30;
		spells[1].perctrigger = 10.0f;
		spells[1].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Projection_d_éclats);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 20.0f;
			spells[2].attackstoptimer = 1000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Projection_d_éclats);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 20.0f;
			spells[2].attackstoptimer = 1000;
		}
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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
			std::vector<UnitPointer> TargetTable;	

			for(unordered_set<ObjectPointer>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					UnitPointer RandomTarget = NULLUNIT;
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

			UnitPointer RTarget = TargetTable[RandTarget];

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

// Mob
#define Régisseur			26729
// Sort
#define Brise_sort			47780
#define Torrent_arcanique	47779

class RégisseurAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(RégisseurAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    RégisseurAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Brise_sort);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 20.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Torrent_arcanique);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 30;
		spells[1].perctrigger = 10.0f;
		spells[1].attackstoptimer = 1000;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					}
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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

	protected:
		int nrspells;
};

// Mob
#define Sylvenier_cristallin	28231
// Sort
#define Cuir_épais				50994

class Sylvenier_cristallinAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Sylvenier_cristallinAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Sylvenier_cristallinAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Cuir_épais);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 45;
		spells[0].perctrigger = 55.0f;
		spells[0].attackstoptimer = 1000;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(UnitPointer mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(UnitPointer mKiller)
    {
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
		    UnitPointer target = NULLUNIT;
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
					}
					
					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
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

	protected:
		int nrspells;
};

void Le_Nexus_Le_Nexus(ScriptMgr * mgr)
{
	// Boss
	mgr->register_creature_script(Anomalus,					 							&AnomalusAI::Create);
	mgr->register_creature_script(Grand_magus_Telestra,		 							&Grand_magus_TelestraAI::Create);
	mgr->register_creature_script(Keristrasza,					 						&KeristraszaAI::Create);
	mgr->register_creature_script(Ormorok_le_Sculpte_arbre,		 						&Ormorok_le_Sculpte_arbreAI::Create);
	// GameObject Event
	mgr->register_gameobject_script(Sphère_de_confinement_d_Anomalus, 					&Sphère_de_confinement_d_AnomalusAI::Create);
	mgr->register_gameobject_script(Sphère_de_confinement_du_Grand_magus_Telestra, 		&Sphère_de_confinement_du_Grand_magus_TelestraAI::Create);
	mgr->register_gameobject_script(Sphère_de_confinement_d_Ormorok_le_Sculpte_arbre, 	&Sphère_de_confinement_d_Ormorok_le_Sculpte_arbreAI::Create);
	// Add Boss
	mgr->register_creature_script(Faille_chaotique,										&Faille_chaotiqueAI::Create);
	mgr->register_creature_script(Grand_magus_Telestra_clone_de_givre,					&Grand_magus_Telestra_clone_de_givreAI::Create);
	mgr->register_creature_script(Grand_magus_Telestra_clone_de_feu,					&Grand_magus_Telestra_clone_de_feuAI::Create);
	mgr->register_creature_script(Grand_magus_Telestra_clone_d_arcane,					&Grand_magus_Telestra_clone_d_arcaneAI::Create);
	mgr->register_creature_script(Noueur_cristallin,									&Noueur_cristallinAI::Create);
	mgr->register_creature_script(Pointe_de_cristal,									&Pointe_de_cristalAI::Create);
	// Mobs
	mgr->register_creature_script(Ame_en_peine_de_mana_affolée,							&Ame_en_peine_de_mana_affoléeAI::Create);
	mgr->register_creature_script(Ascendant_chasseur_de_mages,							&Ascendant_chasseur_de_magesAI::Create);
	mgr->register_creature_script(Berserker_de_l_Alliance, 								&Berserker_de_l_AllianceAI::Create);
	mgr->register_creature_script(Berserker_de_la_Horde, 								&Berserker_de_la_HordeAI::Create);
	mgr->register_creature_script(Clerc_de_l_Alliance,									&Clerc_de_l_AllianceAI::Create);
	mgr->register_creature_script(Clerc_de_la_Horde,									&Clerc_de_la_HordeAI::Create);
	mgr->register_creature_script(Commandant_Kolurg,									&Commandant_KolurgAI::Create);
	mgr->register_creature_script(Commandant_Rudebarbe,									&Commandant_RudebarbeAI::Create);
	mgr->register_creature_script(Commandant_de_l_Alliance,								&Commandant_de_l_AllianceAI::Create);
	mgr->register_creature_script(Commandant_de_la_Horde,								&Commandant_de_la_HordeAI::Create);
	mgr->register_creature_script(Ame_en_peine_de_mana_affolée,							&Ame_en_peine_de_mana_affoléeAI::Create);
	mgr->register_creature_script(Eruption_de_mana_affolée, 							&Eruption_de_mana_affoléeAI::Create);
	mgr->register_creature_script(Forestier_de_l_Alliance,								&Forestier_de_l_AllianceAI::Create);
	mgr->register_creature_script(Forestier_de_la_Horde,								&Forestier_de_la_HordeAI::Create);
	mgr->register_creature_script(Gardien_azur, 										&Gardien_azurAI::Create);
	mgr->register_creature_script(Initié_chasseur_de_mages, 							&Initié_chasseur_de_magesAI::Create);
	mgr->register_creature_script(Lieuse_d_écailles_azur,								&Lieuse_d_écailles_azurAI::Create);
	mgr->register_creature_script(Magus_azur,											&Magus_azurAI::Create);
	mgr->register_creature_script(Massacreur_azur,										&Massacreur_azurAI::Create);
	mgr->register_creature_script(Pourfendeur_de_mages,									&Pourfendeur_de_magesAI::Create);
	mgr->register_creature_script(Protecteur_cristallin,								&Protecteur_cristallinAI::Create);
	mgr->register_creature_script(Régisseur,											&RégisseurAI::Create);
	mgr->register_creature_script(Sylvenier_cristallin, 								&Sylvenier_cristallinAI::Create);
}