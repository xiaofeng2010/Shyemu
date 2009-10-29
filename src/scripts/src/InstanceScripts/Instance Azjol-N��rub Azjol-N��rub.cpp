#include "StdAfx.h"
#include "Setup.h"

#ifdef WIN32
#pragma warning(disable:4018)
#endif

/** Boss (3)

	Anub'arak
	Hadronox
	Krik'thir le Gardien de porte

**/

// Boss
#define Anub_arak					29120
// Sort
#define Marteler					53472
#define Effet_Marteler				53509
#define Effet_Marteler_Heroic		59432
#define Nécrophores_Effet			53520
#define Nécrophores_Summon			53521
#define Nuée_de_sauterelles			53467

class Anub_arakAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Anub_arakAI);
	SP_AI_Spell spells[5];
	bool m_spellcheck[5];

    Anub_arakAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 5;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Marteler);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = false;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 3200;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Effet_Marteler);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 60;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Effet_Marteler_Heroic);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 60;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1000;
		}
		
		spells[2].info = dbcSpell.LookupEntry(Nécrophores_Effet);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = false;
		spells[2].cooldown = 25;
		spells[2].perctrigger = 15.0f;
		spells[2].attackstoptimer = 4000;
		
		spells[3].info = dbcSpell.LookupEntry(Nécrophores_Summon);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 0.0f;
		spells[3].attackstoptimer = 1000;
		
		spells[4].info = dbcSpell.LookupEntry(Nuée_de_sauterelles);
		spells[4].targettype = TARGET_SELF;
		spells[4].instant = false;
		spells[4].cooldown = 60;
		spells[4].perctrigger = 25.0f;
		spells[4].attackstoptimer = 3000;
		spells[4].speech = 14060;
		spells[4].soundid = 14060;
		
		Phase = 0;
		Vague = 1;
		Temps_Necro = 1;
		RegisterAIUpdateEvent(1000);

		Petite_araignée1 = Petite_araignée2 = Petite_araignée3 = Petite_araignée4 = Petite_araignée5 = Petite_araignée6 = Petite_araignée7 = Moyenne_araignée = Grosee_araignée = NULL;
    }
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Phase = 1;
		Vague = 1;
		Temps_Necro = 1;
		
		RegisterAIUpdateEvent(1000);
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14054);
		_unit->PlaySoundToSet(14054);
    }

	void OnTargetDied(Unit * mTarget)
    {
		int RandomSpeach = RandomUInt(3);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14055);
				_unit->PlaySoundToSet(14055);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14056);
				_unit->PlaySoundToSet(14056);
				break;
				
			case 2:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14057);
				_unit->PlaySoundToSet(14057);
				break;
		}
	}

   void OnCombatStop(Unit * mTarget)
    {
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
        RemoveAIUpdateEvent();

		Phase = 0;
		Petite_araignée1 = Petite_araignée2 = Petite_araignée3 = Petite_araignée4 = Petite_araignée5 = Petite_araignée6 = Petite_araignée7 = Moyenne_araignée = Grosee_araignée = NULL;
		
		GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(548.939f, 412.406f, 285.034f, 192395);
		
		if(pDoor == 0)
			return;

        //Ouvre la porte
		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
    }

    void OnDied(Unit * mKiller)
    {
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14069);
		_unit->PlaySoundToSet(14069);
		RemoveAIUpdateEvent();
		
		GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(547.306f, 146.411f, 201.138f, 192395);
		
		if(pDoor == 0)
			return;

        //Ouvre la porte
		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
    }

    void AIUpdate()
	{
		switch (Phase)
		{
			case 0:
				Intro();
				break;
			case 1:
				Combat();
				break;
			case 2:
				Sous_Terre();
				break;
		}
	}
	
	void Intro()
	{
		for(std::set<Player*>::iterator Detection = _unit->GetInRangePlayerSetBegin(); Detection != _unit->GetInRangePlayerSetEnd(); Detection++)
		{
			if((*Detection)->GetTypeId() == TYPEID_PLAYER)
			{
				if(_unit->CalcDistance(*Detection) <= 80.0f)
				{
					_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14053);
					_unit->PlaySoundToSet(14053);
					Phase = 1;
				}
			}
		}
	}
	
	void Combat()
	{
		if(_unit->GetHealthPct() <= 75 && Vague == 1|| _unit->GetHealthPct() <= 50 && Vague == 2 || _unit->GetHealthPct() <= 25 && Vague == 3)
		{
			Vague++;
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			_unit->SetPosition(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ()-15, _unit->GetOrientation(), true);
			_unit->m_invisible = true;
			_unit->Root();
			_unit->GetAIInterface()->disable_melee = true;
			invocation = true;
			Invo = 1;
			Temps_araignée = 0;
			Phase = 2;
		}
		
		if(_unit->HasAura(Nécrophores_Effet))
		{
			if(Temps_Necro == 1)
			{
				_unit->CastSpell(_unit, spells[3].info, spells[3].instant);
				_unit->CastSpell(_unit, spells[3].info, spells[3].instant);
				Temps_Necro = 0;
			}
			else
			{
				Temps_Necro++;
			}
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}
	
	void Sous_Terre()
	{
		if(Empaler < 1)
		{
			
			std::vector<Unit*> TargetTable;	

			for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if ((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive() )
				{
					Unit* RandomTarget = NULL;
					RandomTarget = (Unit*)(*itr);
					TargetTable.push_back(RandomTarget);
				} 
			}

			if (!TargetTable.size())
				return;

			size_t RandTarget = rand()%TargetTable.size();

			Unit * RTarget = TargetTable[RandTarget];

			if (!RTarget)
				return;
			
			_unit->GetMapMgr()->GetInterface()->SpawnCreature(29184, RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation(), true, false, 0, 0);
			Empaler = 15;
		}
		else
		{
			Empaler--;
		}
				
		if(invocation)
		{
			if(Invo == 1 && Temps_araignée < 1)
			{
				Petite_araignée1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(29214, 568.539490f, 260.836517f, 223.441696f, 4.014956f, true, false, 0, 0);
				Petite_araignée2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(29214, 562.905945f, 241.292877f, 223.441711f, 1.904805f, true, false, 0, 0);
				Petite_araignée1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(568.539490f, 260.836517f, 223.441696f, 29214);
				Petite_araignée2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(562.905945f, 241.292877f, 223.441711f, 29214);
				
				std::vector<Unit*> TargetTable;	

				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
				{ 
					if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = (Unit*)(*itr);
						TargetTable.push_back(RandomTarget);
					} 
				}
	
				if (!TargetTable.size())
					return;

				size_t RandTarget = rand()%TargetTable.size();

				Unit * RTarget = TargetTable[RandTarget];

				if (!RTarget)
					return;
			
				Petite_araignée1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Petite_araignée2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Temps_araignée = 5;
				Invo++;
			}
				
			if(Invo == 2 && Temps_araignée < 1)
			{
				Petite_araignée3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(29214, 551.525879f, 235.689056f, 223.441727f, 1.604750f, true, false, 0, 0);
				Petite_araignée4 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(29214, 534.241943f, 247.985428f, 223.441742f, 0.260752f, true, false, 0, 0);
				Petite_araignée3 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(551.525879f, 235.689056f, 223.441727f, 29214);
				Petite_araignée4 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(534.241943f, 247.985428f, 223.441742f, 29214);

				std::vector<Unit*> TargetTable;	

				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
				{ 
					if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = (Unit*)(*itr);
						TargetTable.push_back(RandomTarget);
					} 
				}
	
				if (!TargetTable.size())
					return;

				size_t RandTarget = rand()%TargetTable.size();

				Unit * RTarget = TargetTable[RandTarget];

				if (!RTarget)
					return;
			
				Petite_araignée3->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Petite_araignée4->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Temps_araignée = 5;
				Invo++;
			}
				
			if(Invo == 3 && Temps_araignée < 1)
			{
				Grosee_araignée = _unit->GetMapMgr()->GetInterface()->SpawnCreature(29216, 550.919189f, 320.874023f, 236.312912f, 4.736823f, true, false, 0, 0);
				Grosee_araignée = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(550.919189f, 320.874023f, 236.312912f, 29216);

				std::vector<Unit*> TargetTable;	

				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
				{ 
					if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = (Unit*)(*itr);
						TargetTable.push_back(RandomTarget);
					} 
				}
	
				if (!TargetTable.size())
					return;

				size_t RandTarget = rand()%TargetTable.size();

				Unit * RTarget = TargetTable[RandTarget];

				if (!RTarget)
					return;
			
				Grosee_araignée->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Temps_araignée = 5;
				Invo++;
			}
				
			if(Invo == 4 && Temps_araignée < 1)
			{
				Petite_araignée5 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(29214, 534.141846f, 261.262115f, 223.441772f, 0.000000f, true, false, 0, 0);
				Moyenne_araignée = _unit->GetMapMgr()->GetInterface()->SpawnCreature(29217, 550.492249f, 287.368042f, 226.130203f, 4.630103f, true, false, 0, 0);
				Petite_araignée5 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(534.141846f, 261.262115f, 223.441772f, 29214);
				Moyenne_araignée = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(550.492249f, 287.368042f, 226.130203f, 29217);
				
				std::vector<Unit*> TargetTable;	

				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
				{ 
					if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = (Unit*)(*itr);
						TargetTable.push_back(RandomTarget);
					} 
				}
	
				if (!TargetTable.size())
					return;

				size_t RandTarget = rand()%TargetTable.size();

				Unit * RTarget = TargetTable[RandTarget];

				if (!RTarget)
					return;
			
				Petite_araignée5->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Moyenne_araignée->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Temps_araignée = 5;
				Invo++;
			}
				
			if(Invo == 5 && Temps_araignée < 1)
			{
				Petite_araignée6 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(29214, 548.798767f, 263.108459f, 223.570206f, 0.000000f, true, false, 0, 0);
				Petite_araignée7 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(29214, 551.776978f, 254.246994f, 223.889008f, 1.604750f, true, false, 0, 0);
				Petite_araignée6 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(548.798767f, 263.108459f, 223.570206f, 29214);
				Petite_araignée7 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(551.776978f, 254.246994f, 223.889008f, 29214);
				
				std::vector<Unit*> TargetTable;	

				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
				{ 
					if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = (Unit*)(*itr);
						TargetTable.push_back(RandomTarget);
					} 
				}
	
				if (!TargetTable.size())
					return;

				size_t RandTarget = rand()%TargetTable.size();

				Unit * RTarget = TargetTable[RandTarget];

				if (!RTarget)
					return;
			
				Petite_araignée6->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Petite_araignée7->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				invocation = false;
			}
			Temps_araignée--;
		}
		
		uint32 Araignées_mortes = 9;
		if ((Petite_araignée1 != NULL && !Petite_araignée1->isAlive()))
		{
			Araignées_mortes--;
		}
		
		if ((Petite_araignée2 != NULL && !Petite_araignée2->isAlive()))
		{
			Araignées_mortes--;
		}
		
		if ((Petite_araignée3 != NULL && !Petite_araignée3->isAlive()))
		{
			Araignées_mortes--;
		}
		
		if ((Petite_araignée4 != NULL && !Petite_araignée4->isAlive()))
		{
			Araignées_mortes--;
		}
		
		if ((Petite_araignée5 != NULL && !Petite_araignée5->isAlive()))
		{
			Araignées_mortes--;
		}
		
		if ((Petite_araignée6 != NULL && !Petite_araignée6->isAlive()))
		{
			Araignées_mortes--;
		}
		
		if ((Petite_araignée7 != NULL && !Petite_araignée7->isAlive()))
		{
			Araignées_mortes--;
		}
		
		if ((Moyenne_araignée != NULL && !Moyenne_araignée->isAlive()))
		{
			Araignées_mortes--;
		}
		
		if ((Grosee_araignée != NULL && !Grosee_araignée->isAlive()))
		{
			Araignées_mortes--;
		}
		
		if (Araignées_mortes == 0)
		{
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
			_unit->m_invisible = false;
			_unit->Unroot();
			_unit->SetPosition(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ()+15, _unit->GetOrientation());
			_unit->GetAIInterface()->disable_melee = false;
			Phase = 1;
		}
	}

	void SpellCast(float val)
    {
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
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
					Unit* RandomTarget = NULL;
					RandomTarget = (Unit*)(*itr);

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

			Unit * RTarget = TargetTable[RandTarget];

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
		bool invocation;
		int nrspells, Temps_Necro, Invo, Vague, Empaler;
		uint32 Phase, Temps_araignée;
		Unit * Petite_araignée1, * Petite_araignée2, * Petite_araignée3, * Petite_araignée4, * Petite_araignée5, * Petite_araignée6, * Petite_araignée7, * Moyenne_araignée, * Grosee_araignée;
};

// Boss
#define Hadronox					28921
// Sort
#define Nuage_d_acide				53400
#define Nuage_d_acide_Heroic		59419
#define Perce_armure				53418
#define Poison_de_sangsue			53030
#define Poison_de_sangsue_Heroic	59417
#define Saisie_au_filet				53406
#define Saisie_au_filet_Heroic		59420

class HadronoxAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(HadronoxAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    HadronoxAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Nuage_d_acide);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 23.5f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Nuage_d_acide_Heroic);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 23.5f;
			spells[0].attackstoptimer = 1000;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Perce_armure);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 25;
		spells[1].perctrigger = 25.0f;
		spells[1].attackstoptimer = 1000;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Poison_de_sangsue);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 35;
			spells[2].perctrigger = 20.0f;
			spells[2].attackstoptimer = 1000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Poison_de_sangsue);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 35;
			spells[2].perctrigger = 20.0f;
			spells[2].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[3].info = dbcSpell.LookupEntry(Saisie_au_filet);
			spells[3].targettype = TARGET_SELF;
			spells[3].instant = true;
			spells[3].cooldown = 45;
			spells[3].perctrigger = 18.0f;
			spells[3].attackstoptimer = 1000;
		}
		else
		{
			spells[3].info = dbcSpell.LookupEntry(Saisie_au_filet_Heroic);
			spells[3].targettype = TARGET_SELF;
			spells[3].instant = true;
			spells[3].cooldown = 45;
			spells[3].perctrigger = 18.0f;
			spells[3].attackstoptimer = 1000;
		}
    }
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(1000);
    }

	void OnTargetDied(Unit * mTarget)
    {
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value((UNIT_FIELD_MAXHEALTH*10)/100));
	}

   void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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
					Unit* RandomTarget = NULL;
					RandomTarget = (Unit*)(*itr);

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

			Unit * RTarget = TargetTable[RandTarget];

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

// Boss
#define Krik_thir_le_Gardien_de_porte		28684
// Sort
#define Fouet_mental						52586
#define Fouet_mental_heroic					59367
#define Frénésie							28747
#define Malédiction_de_fatigue				52592
#define Malédiction_de_fatigue_heroic		59368

class Krik_thir_le_Gardien_de_porteAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Krik_thir_le_Gardien_de_porteAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Krik_thir_le_Gardien_de_porteAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Fouet_mental);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 3000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 20.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Fouet_mental_heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 3000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 20.0f;
		}

		spells[1].info = dbcSpell.LookupEntry(Frénésie);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Malédiction_de_fatigue);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = false;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 30.0f;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Malédiction_de_fatigue_heroic);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = false;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 30.0f;
		}
		
		RegisterAIUpdateEvent(1000);
		Lancement_event = false;
		Groupe_Combat = false;
		Enrager = false;
		Temps_Invocation = 0;
		Chapitre = 0;
		Attente = 20;

		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;

		Lancement_event = false;
		Groupe_Combat = false;
		Enrager = false;
		Temps_Invocation = 0;
		Chapitre = 2;
		Attente = 20;
		RegisterAIUpdateEvent(1000);
	}

	void OnTargetDied(Unit * mTarget)
    {
		int RandomSpeach = RandomUInt(3);
		switch (RandomSpeach)
		{
			case 0:
				_unit->PlaySoundToSet(14076);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14077);
				_unit->PlaySoundToSet(14077);
				break;
				
			case 2:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14078);
				_unit->PlaySoundToSet(14078);
				break;
		}
	}

   void OnCombatStop(Unit * mTarget)
    {
	    _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14087);
		_unit->PlaySoundToSet(14087);
		RemoveAIUpdateEvent();
		
		GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(530.584f, 628.017f, 780.981f, 192395);

	    if(pDoor == 0)
            return;

        //Ouvre la porte
		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
    }

    void AIUpdate()
	{
		switch (Chapitre)
		{
			case 0:
				Tunnel();
				break;
			case 1:
				Invocation();
				break;
			case 2:
				Combat();
				break;
		}
	}
	
	void Tunnel()
	{
		for(std::set<Player*>::iterator Detection = _unit->GetInRangePlayerSetBegin(); Detection != _unit->GetInRangePlayerSetEnd(); Detection++)
		{
			if((*Detection)->GetTypeId() == TYPEID_PLAYER)
			{
				if(_unit->CalcDistance(*Detection) <= 80.0f)
				{
					int RandomSpeach = RandomUInt(3);
					switch (RandomSpeach)
					{
						case 0:
							_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14082);
							_unit->PlaySoundToSet(14082);
							Chapitre = 1;
							break;
						
						case 1:
							_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14083);
							_unit->PlaySoundToSet(14083);
							Chapitre = 1;
							break;
				
						case 2:
							_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14084);
							_unit->PlaySoundToSet(14084);
							Chapitre = 1;
							break;
					}
				}
			}
		}
	}
	
	void Invocation()
	{
		for(std::set<Player*>::iterator Detection = _unit->GetInRangePlayerSetBegin(); Detection != _unit->GetInRangePlayerSetEnd(); Detection++)
		{
			if((*Detection)->GetTypeId() == TYPEID_PLAYER)
			{
				if(_unit->CalcDistance(*Detection) <= 50.0f)
				{
					if(!Lancement_event)
					{
						Garde1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28731, 543.000000f, 665.000000f, 776.000000f, 1.000000f, true, false, 0, 0);
						Garde2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28734, 550.000000f, 668.000000f, 776.000000f, 1.000000f, true, false, 0, 0);
						Garde3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28733, 549.000000f, 662.000000f, 777.000000f, 1.000000f, true, false, 0, 0);
						Garde1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(543.000000f, 665.000000f, 776.000000f, 28731);
						Garde2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(550.000000f, 668.000000f, 776.000000f, 28734);
						Garde3 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(549.000000f, 662.000000f, 777.000000f, 28733);
						
						std::vector<Unit*> TargetTable;	

						for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
						{ 
							if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
							{
								Unit* RandomTarget = NULL;
								RandomTarget = (Unit*)(*itr);
								TargetTable.push_back(RandomTarget);
							} 
						}
	
						if (!TargetTable.size())
							return;

						size_t RandTarget = rand()%TargetTable.size();

						Unit * RTarget = TargetTable[RandTarget];

						if (!RTarget)
							return;
			
						Garde1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
						Garde2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
						Garde3->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14079);
						_unit->PlaySoundToSet(14079);
						Lancement_event = true;
						Groupe = 2;
					}
				}
			}
		}
		
		if(Lancement_event && Temps_Invocation == 45)
		{
			if(Groupe == 2 && Temps_Invocation == 45)
			{
				Garde4 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28729, 511.000000f, 666.000000f, 776.000000f, 0.000000f, true, false, 0, 0);
				Garde5 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28733, 506.000000f, 669.000000f, 776.000000f, 0.000000f, true, false, 0, 0);
				Garde6 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28732, 506.000000f, 664.000000f, 777.000000f, 0.000000f, true, false, 0, 0);
				Garde4 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(511.000000f, 666.000000f, 776.000000f, 28729);
				Garde5 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(506.000000f, 669.000000f, 776.000000f, 28733);
				Garde6 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(506.000000f, 664.000000f, 777.000000f, 28732);
						
				std::vector<Unit*> TargetTable;	

				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
				{ 
					if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = (Unit*)(*itr);
						TargetTable.push_back(RandomTarget);
					} 
				}
	
				if (!TargetTable.size())
					return;

				size_t RandTarget = rand()%TargetTable.size();

				Unit * RTarget = TargetTable[RandTarget];

				if (!RTarget)
					return;
			
				Garde4->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Garde5->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Garde6->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14080);
				_unit->PlaySoundToSet(14080);
				Temps_Invocation = 0;
				Groupe++;
			}
			
			if(Groupe == 3 && Temps_Invocation == 45)
			{
				Garde7 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28730, 526.000000f, 663.000000f, 776.000000f, 1.000000f, true, false, 0, 0);
				Garde8 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28734, 521.000000f, 659.000000f, 776.000000f, 1.000000f, true, false, 0, 0);
				Garde9 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28732, 531.000000f, 658.000000f, 776.000000f, 1.000000f, true, false, 0, 0);
				Garde7 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(526.000000f, 663.000000f, 776.000000f, 28730);
				Garde8 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(521.000000f, 659.000000f, 776.000000f, 28734);
				Garde9 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(531.000000f, 658.000000f, 776.000000f, 28732);
						
				std::vector<Unit*> TargetTable;	

				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
				{ 
					if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = (Unit*)(*itr);
						TargetTable.push_back(RandomTarget);
					} 
				}
	
				if (!TargetTable.size())
					return;

				size_t RandTarget = rand()%TargetTable.size();

				Unit * RTarget = TargetTable[RandTarget];

				if (!RTarget)
					return;
			
				Garde7->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Garde8->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Garde9->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14081);
				_unit->PlaySoundToSet(14081);
				Temps_Invocation = 0;
				Groupe++;
			}
			
			if(Groupe == 4 && Temps_Invocation == 45)
			{
				_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
				_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
				
				std::vector<Unit*> TargetTable;	

				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
				{ 
					if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = (Unit*)(*itr);
						TargetTable.push_back(RandomTarget);
					} 
				}
	
				if (!TargetTable.size())
					return;

				size_t RandTarget = rand()%TargetTable.size();

				Unit * RTarget = TargetTable[RandTarget];

				if (!RTarget)
					return;
			
				_unit->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				_unit->GetAIInterface()->MoveTo(533.401428f, 696.806091f, 776.063782f, 4.160246f);
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14075);
				_unit->PlaySoundToSet(14075);
				Chapitre = 2;
			}
		}
		else if(Lancement_event)
		{
			Temps_Invocation++;
		}
	}
	
	void Combat()
	{
		if(!Groupe_Combat && Attente < 1)
		{
			Groupe_Combat = true;
			Attente = 40;
			Groupe1_Combat = 1;
			Temps_Invocation_combat = 0;
		}
		else if(!Groupe_Combat)
		{
			Attente--;
		}
		
		if(Groupe_Combat)
		{
			if(Groupe1_Combat == 1 && Temps_Invocation_combat < 1)
			{
				PetitGarde1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 549.654358f, 656.206909f, 777.442200f, 2.032661f, true, false, 0, 0);
				PetitGarde2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 546.120239f, 654.717163f, 777.365967f, 2.005173f, true, false, 0, 0);
				GrandGarde1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28736, 549.796326f, 655.100586f, 777.427856f, 2.158449f, true, false, 0, 0);
				PetitGarde3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 547.819824f, 650.618347f, 777.333557f, 2.134760f, true, false, 0, 0);
				PetitGarde4 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 553.576355f, 654.769470f, 777.455933f, 2.181098f, true, false, 0, 0);
				PetitGarde1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(549.654358f, 656.206909f, 777.442200f, 28735);
				PetitGarde2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(546.120239f, 654.717163f, 777.365967f, 28735);
				GrandGarde1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(549.796326f, 655.100586f, 777.427856f, 28736);
				PetitGarde3 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(547.819824f, 650.618347f, 777.333557f, 28735);
				PetitGarde4 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(553.576355f, 654.769470f, 777.455933f, 28735);
						
				std::vector<Unit*> TargetTable;	

				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
				{ 
					if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = (Unit*)(*itr);
						TargetTable.push_back(RandomTarget);
					} 
				}
	
				if (!TargetTable.size())
					return;

				size_t RandTarget = rand()%TargetTable.size();

				Unit * RTarget = TargetTable[RandTarget];

				if (!RTarget)
					return;
			
				PetitGarde1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				PetitGarde2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				GrandGarde1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				PetitGarde3->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				PetitGarde4->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14085);
				_unit->PlaySoundToSet(14085);
				Temps_Invocation_combat = 2;
				Groupe1_Combat++;
			}
			
			if(Groupe1_Combat == 2 && Temps_Invocation_combat < 1)
			{
				PetitGarde5 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 519.320679f, 699.961243f, 776.691467f, 4.809954f, true, false, 0, 0);
				PetitGarde6 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 515.473816f, 698.295898f, 776.457947f, 5.006299f, true, false, 0, 0);
				GrandGarde2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28736, 517.909241f, 701.949219f, 777.024536f, 5.171238f, true, false, 0, 0);
				PetitGarde7 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 520.129761f, 704.614075f, 777.308472f, 4.984317f, true, false, 0, 0);
				PetitGarde8 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 523.838867f, 705.355408f, 777.242188f, 4.676356f, true, false, 0, 0);
				PetitGarde5 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(519.320679f, 699.961243f, 776.691467f, 28735);
				PetitGarde6 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(515.473816f, 698.295898f, 776.457947f, 28735);
				GrandGarde2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(517.909241f, 701.949219f, 777.024536f, 28736);
				PetitGarde7 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(520.129761f, 704.614075f, 777.308472f, 28735);
				PetitGarde8 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(523.838867f, 705.355408f, 777.242188f, 28735);
						
				std::vector<Unit*> TargetTable;	

				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
				{ 
					if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = (Unit*)(*itr);
						TargetTable.push_back(RandomTarget);
					} 
				}
	
				if (!TargetTable.size())
					return;

				size_t RandTarget = rand()%TargetTable.size();

				Unit * RTarget = TargetTable[RandTarget];

				if (!RTarget)
					return;
			
				PetitGarde5->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				PetitGarde6->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				GrandGarde2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				PetitGarde7->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				PetitGarde8->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Temps_Invocation_combat = 2;
				Groupe1_Combat++;
			}
			
			if(Groupe1_Combat == 3 && Temps_Invocation_combat < 1)
			{
				PetitGarde9 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 549.461060f, 685.378479f, 773.586975f, 2.909207f, true, false, 0, 0);
				PetitGarde10 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 549.916016f, 681.876648f, 774.196533f, 3.598787f, true, false, 0, 0);
				GrandGarde3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28736, 547.123901f, 684.325134f, 774.886658f, 3.155821f, true, false, 0, 0);
				PetitGarde11 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 545.293213f, 680.978455f, 775.385559f, 3.425997f, true, false, 0, 0);
				PetitGarde12 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 545.381348f, 685.674988f, 775.228027f, 3.371020f, true, false, 0, 0);
				PetitGarde9 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(549.461060f, 685.378479f, 773.586975f, 28735);
				PetitGarde10 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(549.916016f, 681.876648f, 774.196533f, 28735);
				GrandGarde3 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(547.123901f, 684.325134f, 774.886658f, 28736);
				PetitGarde11 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(545.293213f, 680.978455f, 775.385559f, 28735);
				PetitGarde12 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(545.381348f, 685.674988f, 775.228027f, 28735);
						
				std::vector<Unit*> TargetTable;	

				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
				{ 
					if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = (Unit*)(*itr);
						TargetTable.push_back(RandomTarget);
					} 
				}
	
				if (!TargetTable.size())
					return;

				size_t RandTarget = rand()%TargetTable.size();

				Unit * RTarget = TargetTable[RandTarget];

				if (!RTarget)
					return;
			
				PetitGarde9->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				PetitGarde10->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				GrandGarde3->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				PetitGarde11->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				PetitGarde12->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Temps_Invocation_combat = 2;
				Groupe1_Combat++;
			}
			
			if(Groupe1_Combat == 4 && Temps_Invocation_combat < 1)
			{
				PetitGarde13 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 504.050018f, 648.113770f, 777.474731f, 1.519049f, true, false, 0, 0);
				PetitGarde14 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 508.518188f, 652.080688f, 777.462830f, 1.219813f, true, false, 0, 0);
				GrandGarde4 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28736, 508.507874f, 648.324707f, 777.471863f, 1.490769f, true, false, 0, 0);
				PetitGarde15 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 504.145813f, 652.128662f, 777.499512f, 1.475847f, true, false, 0, 0);
				PetitGarde16 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28735, 511.186829f, 652.477051f, 777.430847f, 1.540250f, true, false, 0, 0);
				PetitGarde13 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(504.050018f, 648.113770f, 777.474731f, 28735);
				PetitGarde14 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(508.518188f, 652.080688f, 777.462830f, 28735);
				GrandGarde4 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(508.507874f, 648.324707f, 777.471863f, 28736);
				PetitGarde15 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(504.145813f, 652.128662f, 777.499512f, 28735);
				PetitGarde16 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(511.186829f, 652.477051f, 777.430847f, 28735);
						
				std::vector<Unit*> TargetTable;	

				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
				{ 
					if((*itr)->GetTypeId() == TYPEID_PLAYER && TO_UNIT((*itr))->isAlive())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = (Unit*)(*itr);
						TargetTable.push_back(RandomTarget);
					} 
				}
	
				if (!TargetTable.size())
					return;

				size_t RandTarget = rand()%TargetTable.size();

				Unit * RTarget = TargetTable[RandTarget];

				if (!RTarget)
					return;
			
				PetitGarde13->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				PetitGarde14->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				GrandGarde4->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				PetitGarde15->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				PetitGarde16->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Groupe_Combat = false;
			}
			Temps_Invocation_combat--;
		}
			
		if((_unit->GetHealthPct() <= 10) && !Enrager)
		{
			_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
			Enrager = true;
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}


	void SpellCast(float val)
    {
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
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
					Unit* RandomTarget = NULL;
					RandomTarget = (Unit*)(*itr);

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

			Unit * RTarget = TargetTable[RandTarget];

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
		bool Enrager, Lancement_event, Groupe_Combat;
		int nrspells, Groupe, Groupe1_Combat;
		uint32 Chapitre, Temps_Invocation, Temps_Invocation_combat, Attente;
		Unit * Garde1, * Garde2, * Garde3, * Garde4, * Garde5, * Garde6, * Garde7, * Garde8, * Garde9, * PetitGarde1, * PetitGarde2, * PetitGarde3, * PetitGarde4, * PetitGarde5, * PetitGarde6, * PetitGarde7, * PetitGarde8, * PetitGarde9, * PetitGarde10, * PetitGarde11, * PetitGarde12, * PetitGarde13, * PetitGarde14, * PetitGarde15, * PetitGarde16, * GrandGarde1, * GrandGarde2, * GrandGarde3, * GrandGarde4;
};

/** Add Boss (2)

	Cible d'empalement
	Nueux grouillant

**/

// Add Boss
#define Cible_d_empalement		29184
// Sort
#define Empaler					53454	
#define Empaler_heroic			59446
#define Empaler_Visuel			53455

class Cible_d_empalementAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Cible_d_empalementAI);
	Cible_d_empalementAI(Creature * pCreature) : CreatureAIScript(pCreature)
	{
		Visuel = false;
		Temps_Empaler = 3;
		_unit->m_invisible = true;
		RegisterAIUpdateEvent(100);
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
	}

	void AIUpdate()
	{
		if(!Visuel)
		{
			_unit->CastSpell(_unit, dbcSpell.LookupEntry(Empaler_Visuel), true);
			Visuel = true;
		}
		
		if(Temps_Empaler < 1)
		{
			for(std::set<Player*>::iterator TeleportItr = _unit->GetInRangePlayerSetBegin(); TeleportItr != _unit->GetInRangePlayerSetEnd(); TeleportItr++)
			{
				if((*TeleportItr)->GetTypeId() == TYPEID_PLAYER)
				{
					if(_unit->CalcDistance(*TeleportItr) <= 3.0f)
					{
						(*TeleportItr)->CastSpell((*TeleportItr), dbcSpell.LookupEntry(Empaler), true);
					}
				}
			}
			_unit->Despawn(0,0);
		}
		else
		{
			Temps_Empaler--;
		}
	}
	
	protected:
		bool Visuel;
		uint32 Temps_Empaler;
};

// Add Boss
#define Nueux_grouillant	28735

class Nueux_grouillantAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Nueux_grouillantAI);
	Nueux_grouillantAI(Creature * pCreature) : CreatureAIScript(pCreature)
	{}

	 void OnCombatStart(Unit * mTarget)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
		_unit->Despawn(3000,0);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
    }

	protected:
};

/** Mob (17)

	Assassin anub'ar
	Champion anub'ar
	Contaminateur grouillant
	Démon des cryptes anub'ar
	Ecraseur anub'ar
	Entoilage
	Exhalombre anu'bar
	Garde primordial anub'ar
	Gardien anub'ar
	Gardien Gashra
	Gardien Narjil
	Gardien Silthik
	Guerrier anub'ar
	Nécromancien anub'ar
	Tirailleur anu'bar
	Tisseur anub'ar
	Venimancien anub'ar

**/

// Mob
#define Assassin_anub_ar	29214
// Sort
#define Attaque_sournoise	52540

class Assassin_anub_arAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Assassin_anub_arAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Assassin_anub_arAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Attaque_sournoise);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 22;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 1000;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Champion_anub_ar1		28924
#define Champion_anub_ar2		29062
#define Champion_anub_ar3		29096
#define Champion_anub_ar4		29117
// Sort
#define Pourfendre				53317
#define Pourfendre_Heroic		59343
#define Volée_de_coups			53394
#define Volée_de_coups_Heroic	59344

class Champion_anub_arAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Champion_anub_arAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Champion_anub_arAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Pourfendre);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Pourfendre_Heroic);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Volée_de_coups);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Volée_de_coups_Heroic);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1000;
		}
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Contaminateur_grouillant	28736
// Sort
#define Jet_d_acide					52446
#define Jet_d_acide_Heroic			59363

class Contaminateur_grouillantAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Contaminateur_grouillantAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Contaminateur_grouillantAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Jet_d_acide);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Jet_d_acide_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
		_unit->Despawn(3000,0);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Démon_des_cryptes_anub_ar1	29051
#define Démon_des_cryptes_anub_ar2	29063
#define Démon_des_cryptes_anub_ar3	29067
#define Démon_des_cryptes_anub_ar4	29118
// Sort
#define Blessure_infectée			53330
#define Blessure_infectée_Heroic	59348
#define Rets_écrasants				53322
#define Rets_écrasants_Heroic		59347

class Démon_des_cryptes_anub_arAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Démon_des_cryptes_anub_arAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Démon_des_cryptes_anub_arAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Blessure_infectée);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 45;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Blessure_infectée_Heroic);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 45;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Rets_écrasants);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 35;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 500;
			spells[1].mindist2cast = 5.0f;
			spells[1].maxdist2cast = 30.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Rets_écrasants);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 35;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 500;
			spells[1].mindist2cast = 5.0f;
			spells[1].maxdist2cast = 30.0f;
		}
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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
					Unit* RandomTarget = NULL;
					RandomTarget = (Unit*)(*itr);

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

			Unit * RTarget = TargetTable[RandTarget];

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
#define Ecraseur_anub_ar	28922
// Sort
#define Choc				53318
#define Choc_Heroic			59346
#define Frénésie_EAA		53801

class Ecraseur_anub_arAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Ecraseur_anub_arAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Ecraseur_anub_arAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Choc);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = false;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1200;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Choc_Heroic);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = false;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1200;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Frénésie_EAA);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
		
		Enrager = false;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Enrager = false;
		
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		if (_unit->GetHealthPct() <= 25 && !Enrager)
		{
			_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
			Enrager = true;
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}

	void SpellCast(float val)
    {
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
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

	protected:
		bool Enrager;
		int nrspells;
};

// Mob
#define Entoilage		28619
// Sort
#define Entoilage_Sort	54453

class EntoilageAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(EntoilageAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    EntoilageAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Entoilage_Sort);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = false;
		spells[0].cooldown = 20;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 3000;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 30.0f;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};


// Mob
#define Exhalombre_anu_bar			28733
// Sort
#define Nova_de_l_ombre				52535
#define Nova_de_l_ombre_Heroic		59358
#define Trait_de_l_ombre			52534
#define Trait_de_l_ombre_Heroic		59357

class Exhalombre_anu_barAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Exhalombre_anu_barAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Exhalombre_anu_barAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Nova_de_l_ombre);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Nova_de_l_ombre_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Trait_de_l_ombre);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 40.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Trait_de_l_ombre_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 40.0f;
		}
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
		_unit->Despawn(3000,0);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Garde_primordial_anub_ar	29128
// Sort
#define Drain_de_puissance			54314
#define Drain_de_puissance_Heroic	59354
#define Marque_des_ténèbres			54309
#define Marque_des_ténèbres_Heroic	59352

class Garde_primordial_anub_arAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Garde_primordial_anub_arAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Garde_primordial_anub_arAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Drain_de_puissance);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 30;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Drain_de_puissance_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 30;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Marque_des_ténèbres);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 30.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Marque_des_ténèbres);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 30.0f;
		}
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Gardien_anub_ar				29216
// Sort
#define Fracasser_armure			53618
#define Fracasser_armure_Heroic		59350
#define Frappe						52532

class Gardien_anub_arAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Gardien_anub_arAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Gardien_anub_arAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Fracasser_armure);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Fracasser_armure_Heroic);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Frappe);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 15;
		spells[1].perctrigger = 38.0f;
		spells[1].attackstoptimer = 1000;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Gardien_Gashra				28730
// Sort
#define Enrager						52470	
#define Entoilage_GG				54453
#define Morsure_infectieuse			52469
#define Morsure_infectieuse_Heroic	59364

class Gardien_GashraAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Gardien_GashraAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Gardien_GashraAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}
		
		spells[0].info = dbcSpell.LookupEntry(Enrager);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 45;
		spells[0].perctrigger = 5.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Entoilage_GG);
		spells[1].targettype = TARGET_RANDOM_SINGLE;
		spells[1].instant = false;
		spells[1].cooldown = 25;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 3000;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 40.0f;
				
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Morsure_infectieuse);
			spells[2].targettype = TARGET_ATTACKING;
			spells[2].instant = true;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Morsure_infectieuse_Heroic);
			spells[2].targettype = TARGET_ATTACKING;
			spells[2].instant = true;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
		}
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
		_unit->Despawn(3000,0);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Gardien_Narjil					28729
// Sort
#define Entoilage_GN					54453
#define Morsure_infectieuse				52469
#define Morsure_infectieuse_Heroic		59364
#define Rets_aveuglants					52524
#define Rets_aveuglants_Heroic			59365

class Gardien_NarjilAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Gardien_NarjilAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Gardien_NarjilAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Entoilage_GN);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = false;
		spells[0].cooldown = 25;
		spells[0].perctrigger = 15.0f;
		spells[0].attackstoptimer = 3000;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 40.0f;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Morsure_infectieuse);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Morsure_infectieuse_Heroic);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Rets_aveuglants);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = false;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 10.0f;
			spells[2].attackstoptimer = 2000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Rets_aveuglants_Heroic);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = false;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 10.0f;
			spells[2].attackstoptimer = 2000;
		}
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
		_unit->Despawn(3000,0);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Gardien_Silthik					28730
// Sort
#define Entoilage_GS					54453
#define Jet_de_poison					52493
#define Jet_de_poison_Heroic			59366
#define Morsure_infectieuse				52469
#define Morsure_infectieuse_Heroic		59364

class Gardien_SilthikAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Gardien_SilthikAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Gardien_SilthikAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Entoilage_GS);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = false;
		spells[0].cooldown = 25;
		spells[0].perctrigger = 15.0f;
		spells[0].attackstoptimer = 3000;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 40.0f;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Jet_de_poison);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1500;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 100.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Jet_de_poison_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1500;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 100.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Morsure_infectieuse);
			spells[2].targettype = TARGET_ATTACKING;
			spells[2].instant = true;
			spells[2].cooldown = 15;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Morsure_infectieuse_Heroic);
			spells[2].targettype = TARGET_ATTACKING;
			spells[2].instant = true;
			spells[2].cooldown = 15;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
		}
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
		_unit->Despawn(3000,0);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Guerrier_anub_ar	28732
// Sort
#define Enchaînement		49806
#define Frappe				52532

class Guerrier_anub_arAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Guerrier_anub_arAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Guerrier_anub_arAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Enchaînement);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 20;
		spells[0].perctrigger = 15.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(Frappe);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = false;
		spells[1].cooldown = 15;
		spells[1].perctrigger = 25.0f;
		spells[1].attackstoptimer = 1000;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
		_unit->Despawn(3000,0);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Nécromancien_anub_ar1	28925
#define Nécromancien_anub_ar2	29064
#define Nécromancien_anub_ar3	29098
#define Nécromancien_anub_ar4	29119
// Sort
#define Animer_les_os			53334
#define Trait_de_l_ombre_NAA	53333

class Nécromancien_anub_arAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Nécromancien_anub_arAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Nécromancien_anub_arAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Animer_les_os);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = false;
		spells[0].cooldown = 60;
		spells[0].perctrigger = 10.0f;
		spells[0].attackstoptimer = 9000;

		spells[1].info = dbcSpell.LookupEntry(Trait_de_l_ombre);
		spells[1].targettype = TARGET_RANDOM_SINGLE;
		spells[1].instant = false;
		spells[1].cooldown = 15;
		spells[1].perctrigger = 25.0f;
		spells[1].attackstoptimer = 2000;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 20.0f;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Tirailleur_anu_bar		28734
// Sort
#define Attaque_sournoise		52540

class Tirailleur_anu_barAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Tirailleur_anu_barAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Tirailleur_anu_barAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Attaque_sournoise);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 35.0f;
		spells[0].attackstoptimer = 1000;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
		_unit->Despawn(3000, 0);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Tisseur_anub_ar			29335
// Sort
#define Entoilage_TAA			54453
#define Tir_de_rets				54290
#define Tir_de_rets_Heroic		59362

class Tisseur_anub_arAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Tisseur_anub_arAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Tisseur_anub_arAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Entoilage_TAA);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = false;
		spells[0].cooldown = 25;
		spells[0].perctrigger = 15.0f;
		spells[0].attackstoptimer = 3000;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 40.0f;

		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Tir_de_rets);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 18;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 30.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Tir_de_rets_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 18;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 30.0f;
		}
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

// Mob
#define Venimancien_anub_ar					29217
// Sort
#define Eclair_de_poison					53617
#define Eclair_de_poison_Heroic				59359
#define Salve_d_éclairs_de_poison			53616
#define Salve_d_éclairs_de_poison_Heroic	59360

class Venimancien_anub_arAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Venimancien_anub_arAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Venimancien_anub_arAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Eclair_de_poison);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Eclair_de_poison_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Salve_d_éclairs_de_poison);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 30;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Salve_d_éclairs_de_poison_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 30;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 1000;
		}
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
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
		    Unit *target = NULL;
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

	protected:
		int nrspells;
};

void Azjol_Nerub_Azjol_Nerub(ScriptMgr * mgr)
{
	// Boss
	mgr->register_creature_script(Anub_arak, 						&Anub_arakAI::Create);
	mgr->register_creature_script(Hadronox, 						&HadronoxAI::Create);
	mgr->register_creature_script(Krik_thir_le_Gardien_de_porte, 	&Krik_thir_le_Gardien_de_porteAI::Create);
	// Add
	mgr->register_creature_script(Cible_d_empalement,			 	&Cible_d_empalementAI::Create);
	mgr->register_creature_script(Nueux_grouillant,			 		&Nueux_grouillantAI::Create);

	// Mob
	mgr->register_creature_script(Assassin_anub_ar, 				&Assassin_anub_arAI::Create);
	mgr->register_creature_script(Champion_anub_ar1, 				&Champion_anub_arAI::Create);
	mgr->register_creature_script(Champion_anub_ar2, 				&Champion_anub_arAI::Create);
	mgr->register_creature_script(Champion_anub_ar3, 				&Champion_anub_arAI::Create);
	mgr->register_creature_script(Champion_anub_ar4, 				&Champion_anub_arAI::Create);
	mgr->register_creature_script(Contaminateur_grouillant, 		&Contaminateur_grouillantAI::Create);
	mgr->register_creature_script(Démon_des_cryptes_anub_ar1,		&Démon_des_cryptes_anub_arAI::Create);
	mgr->register_creature_script(Démon_des_cryptes_anub_ar2,		&Démon_des_cryptes_anub_arAI::Create);
	mgr->register_creature_script(Démon_des_cryptes_anub_ar3,		&Démon_des_cryptes_anub_arAI::Create);
	mgr->register_creature_script(Démon_des_cryptes_anub_ar4,		&Démon_des_cryptes_anub_arAI::Create);
	mgr->register_creature_script(Ecraseur_anub_ar, 				&Ecraseur_anub_arAI::Create);
	mgr->register_creature_script(Entoilage,		 				&EntoilageAI::Create);
	mgr->register_creature_script(Exhalombre_anu_bar, 				&Exhalombre_anu_barAI::Create);
	mgr->register_creature_script(Garde_primordial_anub_ar, 		&Garde_primordial_anub_arAI::Create);
	mgr->register_creature_script(Gardien_anub_ar, 					&Gardien_anub_arAI::Create);
	mgr->register_creature_script(Gardien_Gashra,	 				&Gardien_GashraAI::Create);
	mgr->register_creature_script(Gardien_Narjil,	 				&Gardien_NarjilAI::Create);
	mgr->register_creature_script(Gardien_Silthik,	 				&Gardien_SilthikAI::Create);
	mgr->register_creature_script(Guerrier_anub_ar, 				&Guerrier_anub_arAI::Create);
	mgr->register_creature_script(Nécromancien_anub_ar1,			&Nécromancien_anub_arAI::Create);
	mgr->register_creature_script(Nécromancien_anub_ar2,			&Nécromancien_anub_arAI::Create);
	mgr->register_creature_script(Nécromancien_anub_ar3,			&Nécromancien_anub_arAI::Create);
	mgr->register_creature_script(Nécromancien_anub_ar4,			&Nécromancien_anub_arAI::Create);
	mgr->register_creature_script(Tirailleur_anu_bar, 				&Tirailleur_anu_barAI::Create);
	mgr->register_creature_script(Tisseur_anub_ar, 					&Tisseur_anub_arAI::Create);
	mgr->register_creature_script(Venimancien_anub_ar, 				&Venimancien_anub_arAI::Create);
}
