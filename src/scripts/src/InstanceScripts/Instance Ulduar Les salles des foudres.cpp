#include "StdAfx.h"
#include "Setup.h"

#ifdef WIN32
#pragma warning(disable:4018)
#endif

/** Boss (20)

	Général Bjarngrim
	Ionar
	Loken
	Volkhan
	
**/

// Boss
#define Général_Bjarngrim	28586
// Sort Posture defensive
#define Aura_défensive		41105
#define Renvoi_de_sort		36096
#define Volée_de_coups		12555
#define Repousser_au_loin	52029
// Sort Posture Berserker
#define Aura_de_berserker	41107
#define Enchaînement		15284
// Sort Posture de combat
#define Aura_de_bataille	41106
#define Frappe_mortelle		16856
#define Tourbillon			52027

class Général_BjarngrimAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Général_BjarngrimAI);
	SP_AI_Spell spells[6];
	bool m_spellcheck[6];

    Général_BjarngrimAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 6;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Renvoi_de_sort);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 35;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Volée_de_coups);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 10;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
		
		spells[2].info = dbcSpell.LookupEntry(Repousser_au_loin);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = 15;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;
		
		spells[3].info = dbcSpell.LookupEntry(Enchaînement);
		spells[3].targettype = TARGET_ATTACKING;
		spells[3].instant = true;
		spells[3].cooldown = 15;
		spells[3].perctrigger = 0.0f;
		spells[3].attackstoptimer = 1000;
		
		spells[4].info = dbcSpell.LookupEntry(Frappe_mortelle);
		spells[4].targettype = TARGET_ATTACKING;
		spells[4].instant = true;
		spells[4].cooldown = 10;
		spells[4].perctrigger = 0.0f;
		spells[4].attackstoptimer = 1000;
		
		spells[5].info = dbcSpell.LookupEntry(Tourbillon);
		spells[5].targettype = TARGET_SELF;
		spells[5].instant = true;
		spells[5].cooldown = 20;
		spells[5].perctrigger = 0.0f;
		spells[5].attackstoptimer = 1000;

		force_changement = false;
		Changement1 = 5;
		Renvoie = 18;
		Volée = 5;
		Repousser = 8;
		Enchaine = 8;
		Frappe = 5;
		Tourbi = 10;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;

		force_changement = false;
		Changement1 = 5;
		Renvoie = 18;
		Volée = 5;
		Repousser = 8;
		Enchaine = 8;
		Frappe = 5;
		Tourbi = 10;
			
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14149);
		_unit->PlaySoundToSet(14149);
    }

	void OnTargetDied(Unit * mTarget)
    {
		int RandomSpeach = RandomUInt(3);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14153);
				_unit->PlaySoundToSet(14153);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14154);
				_unit->PlaySoundToSet(14154);
				break;

			case 2:
				_unit->PlaySoundToSet(14155);
				break;
		}
	}

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		_unit->RemoveAura(Aura_défensive);
		_unit->RemoveAura(Aura_de_berserker);
		_unit->RemoveAura(Aura_de_bataille);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14156);
		_unit->PlaySoundToSet(14156);
		_unit->RemoveAura(Aura_défensive);
		_unit->RemoveAura(Aura_de_berserker);
		_unit->RemoveAura(Aura_de_bataille);
		RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		if(!force_changement && Changement1 < 1 )
		{
			int RandomChangement = RandomUInt(3);
			switch (RandomChangement)
			{
				case 0:
					_unit->RemoveAura(Aura_de_berserker);
					_unit->RemoveAura(Aura_de_bataille);
					_unit->CastSpell(_unit, Aura_défensive, true);
					_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14150);
					_unit->PlaySoundToSet(14150);
					force_changement = true;
					Changement2 = 10;
					break;

				case 1:
					_unit->RemoveAura(Aura_défensive);
					_unit->RemoveAura(Aura_de_bataille);
					_unit->CastSpell(_unit, Aura_de_berserker, true);
					_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14152);
					_unit->PlaySoundToSet(14152);
					force_changement = true;
					Changement2 = 10;
					break;

				case 2:
					_unit->RemoveAura(Aura_défensive);
					_unit->RemoveAura(Aura_de_berserker);
					_unit->CastSpell(_unit, Aura_de_bataille, true);
					_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14151);
					_unit->PlaySoundToSet(14151);
					force_changement = true;
					Changement2 = 10;
					break;
			}
		}
		else
		{
			Changement1--;
		}
		
		if(Changement2 < 1)
		{
			if(_unit->HasAura(Aura_de_bataille))
			{
				int RandomChangement = RandomUInt(2);
				switch (RandomChangement)
				{
					case 0:
						_unit->RemoveAura(Aura_de_berserker);
						_unit->RemoveAura(Aura_de_bataille);
						_unit->CastSpell(_unit, Aura_défensive, true);
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14150);
						_unit->PlaySoundToSet(14150);
						Changement2 = 10;
						break;

					case 1:
						_unit->RemoveAura(Aura_défensive);
						_unit->RemoveAura(Aura_de_bataille);
						_unit->CastSpell(_unit, Aura_de_berserker, true);
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14152);
						_unit->PlaySoundToSet(14152);
						Changement2 = 10;
						break;
				}
			}
			else if(_unit->HasAura(Aura_de_berserker))
			{
				int RandomChangement = RandomUInt(2);
				switch (RandomChangement)
				{
					case 0:
						_unit->RemoveAura(Aura_défensive);
						_unit->RemoveAura(Aura_de_berserker);
						_unit->CastSpell(_unit, Aura_de_bataille, true);
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14151);
						_unit->PlaySoundToSet(14151);
						Changement2 = 10;
						break;

					case 1:
						_unit->RemoveAura(Aura_de_berserker);
						_unit->RemoveAura(Aura_de_bataille);
						_unit->CastSpell(_unit, Aura_défensive, true);
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14150);
						_unit->PlaySoundToSet(14150);
						Changement2 = 10;
						break;
				}
			}
			else if(_unit->HasAura(Aura_défensive))
			{
				int RandomChangement = RandomUInt(2);
				switch (RandomChangement)
				{
					case 0:
						_unit->RemoveAura(Aura_défensive);
						_unit->RemoveAura(Aura_de_berserker);
						_unit->CastSpell(_unit, Aura_de_bataille, true);
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14151);
						_unit->PlaySoundToSet(14151);
						Changement2 = 10;
						break;

					case 1:
						_unit->RemoveAura(Aura_défensive);
						_unit->RemoveAura(Aura_de_bataille);
						_unit->CastSpell(_unit, Aura_de_berserker, true);
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14152);
						_unit->PlaySoundToSet(14152);
						Changement2 = 10;
						break;
				}
			}
		}
		else
		{
			Changement2--;
		}
		
		if(_unit->HasAura(Aura_défensive))
		{
			if (Renvoie < 1 && _unit->GetCurrentSpell() == NULL)
			{
				_unit->CastSpell(spells[0].targettype, spells[0].info, spells[0].instant);
				Renvoie = 14;
			}
			else if (Volée < 1 && _unit->GetCurrentSpell() == NULL)
			{
				_unit->CastSpell(spells[1].targettype, spells[1].info, spells[1].instant);
				Volée = 3;
			}
			else if (Repousser < 1 && _unit->GetCurrentSpell() == NULL)
			{
				_unit->CastSpell(spells[2].targettype, spells[2].info, spells[2].instant);
				Repousser = 4;
			}
			else
			{
				Renvoie--;
				Volée--;
				Repousser--;
			}
		}

		if(_unit->HasAura(Aura_de_berserker))
		{
			if (Enchaine < 1 && _unit->GetCurrentSpell() == NULL)
			{
				_unit->CastSpell(spells[3].targettype, spells[3].info, spells[3].instant);
				Enchaine = 4;
			}
			else
			{
				Enchaine--;
			}
		}
				
		if(_unit->HasAura(Aura_de_bataille))
		{
			if (Frappe < 1 && _unit->GetCurrentSpell() == NULL)
			{
				_unit->CastSpell(spells[4].targettype, spells[4].info, spells[4].instant);
				Frappe = 2;
			}
			else if (Tourbi < 1 && _unit->GetCurrentSpell() == NULL)
			{
				_unit->CastSpell(spells[5].targettype, spells[5].info, spells[5].instant);
				_unit->GetAIInterface()->StopMovement(8000);
				Tourbi = 2;
			}
			else
			{
				Frappe--;
				Tourbi--;
			}
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
		bool force_changement;
		int nrspells;
		uint32 Changement1, Changement2, Renvoie, Volée, Repousser, Enchaine, Frappe, Tourbi;
};

// Boss
#define Ionar						28546
// Sort
#define Foudre_en_boule				52780
#define Foudre_en_boule_Heroic		59800
#define Surcharge_statique			52658
#define Surcharge_statique_Heroic	59795

class IonarAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(IonarAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    IonarAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Foudre_en_boule);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 100.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Foudre_en_boule_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 100.0f;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Surcharge_statique);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 100.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Surcharge_statique_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 100.0f;
		}
    }
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;

		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14453);
		_unit->PlaySoundToSet(14453);
    }

	void OnTargetDied(Unit * mTarget)
    {
		int RandomSpeach = RandomUInt(3);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14456);
				_unit->PlaySoundToSet(14456);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14457);
				_unit->PlaySoundToSet(14457);
				break;

			case 2:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14458);
				_unit->PlaySoundToSet(14458);
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
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14459);
		_unit->PlaySoundToSet(14459);
		RemoveAIUpdateEvent();
		
		GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(1074.3f, -232.213f, 62.5531f, 191326);

	    if(pDoor == 0)
            return;

        //Ouvre la porte
		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
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
#define Loken					28923
// Sort
#define Arc_éclair				52921
#define Nova_de_foudre			52960
#define Nova_de_foudre_Heroic	59835

class LokenAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(LokenAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    LokenAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Arc_éclair);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = true;
		spells[0].cooldown = 10;
		spells[0].perctrigger = 45.0f;
		spells[0].attackstoptimer = 1000;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 50.0f;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Nova_de_foudre);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 5000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Nova_de_foudre_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 5000;
		}

		Phrase1 = false;
		Phrase2 = false;
		Phrase3 = false;
    }
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;

		Phrase1 = false;
		Phrase2 = false;
		Phrase3 = false;

		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14162);
		_unit->PlaySoundToSet(14162);
    }

	void OnTargetDied(Unit * mTarget)
    {
		int RandomSpeach = RandomUInt(3);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14166);
				_unit->PlaySoundToSet(14166);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14167);
				_unit->PlaySoundToSet(14167);
				break;

			case 2:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14168);
				_unit->PlaySoundToSet(14168);
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
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14172);
		_unit->PlaySoundToSet(14172);
		RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		if((_unit->GetHealthPct() <= 75) && !Phrase1)
		{
			_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14169);
			_unit->PlaySoundToSet(14169);
			Phrase1 = true;
		}

		if((_unit->GetHealthPct() <= 50) && !Phrase2)
		{
			_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14170);
			_unit->PlaySoundToSet(14170);
			Phrase2 = true;
		}

		if((_unit->GetHealthPct() <= 25) && !Phrase3)
		{
			_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 14171);
			_unit->PlaySoundToSet(14171);
			Phrase3 = true;
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
		bool Phrase1, Phrase2, Phrase3;
		int nrspells;
};

// Boss
#define Volkhan							28587
// Sort
#define Chaleur							52387
#define Chaleur_Heroic					59528
#define Hargne							52238
#define Piétinement_fracassant 			52237
#define Piétinement_fracassant_Heroic	59529

struct Coordonnée
{
    float x;
    float y;
    float z;
    float o;
};

static Coordonnée Event_Enclume[] =
{
	{ },
    { 1328.027466f, -92.807968f, 56.717873f, 2.279595f },
};

#define cour	256

class VolkhanAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(VolkhanAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    VolkhanAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Hargne);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Piétinement_fracassant);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 30;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 3000;
			spells[1].speech = 13963;
			spells[1].soundid = 13963;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Nova_de_foudre_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 30;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 3000;
			spells[1].speech = 13963;
			spells[1].soundid = 13963;
		}
		
		Enclume = 1;
		Appel_Golem = false;
    }
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;

		Enclume = 1;
		Appel_Golem = false;

		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 13960);
		_unit->PlaySoundToSet(13960);
    }

	void OnTargetDied(Unit * mTarget)
    {
		int RandomSpeach = RandomUInt(3);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 13965);
				_unit->PlaySoundToSet(13965);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 13966);
				_unit->PlaySoundToSet(13966);
				break;

			case 2:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 13967);
				_unit->PlaySoundToSet(13967);
				break;
		}
	}

   void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));

		if(Golem_1 != NULL)
		{
			Golem_1->GetAIInterface()->disable_combat = true;
		}
		if(Golem_2 != NULL)
		{
			Golem_2->GetAIInterface()->disable_combat = true;
		}
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 13968);
		_unit->PlaySoundToSet(13968);
		RemoveAIUpdateEvent();
		
		GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(1277.44f, -164.663f, 53.5171f, 191325);

	    if(pDoor == 0)
            return;

        //Ouvre la porte
		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
    }

    void AIUpdate()
	{
		if(((_unit->GetHealthPct() <= 80) && Enclume == 1) || ((_unit->GetHealthPct() <= 60) && Enclume == 2) || ((_unit->GetHealthPct() <= 40) && Enclume == 3) || ((_unit->GetHealthPct() <= 20) && Enclume == 4))
		{
			for (int i = 1; i < 2; i++)
			{
				_unit->GetAIInterface()->addWayPoint(CreateWaypoint(i, 0, cour));
			}

			_unit->GetAIInterface()->StopMovement(1000);
			_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
			_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			_unit->GetAIInterface()->setWaypointToMove(1);
			Appel_Golem = true;
			Enclume++;
		}

		if(Golem_vers_boss && Temps_position < 1)
		{
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
			
			Golem_1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Golem_2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Golem_vers_boss = false;
		}
		else if (Golem_vers_boss)
		{
			Temps_position--;
		}

		if(!Appel_Golem)	
		{
			float val = (float)RandomFloat(100.0f);
			SpellCast(val);
		}
	}

	void OnReachWP(uint32 iWaypointId, bool bForwards)
    {
		switch (iWaypointId)
		{
			case 1:
			{
				int RandomSpeach = RandomUInt(3);
				switch (RandomSpeach)
				{
					case 0:
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 13961);
						_unit->PlaySoundToSet(13961);
						break;
					
					case 1:
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 13962);
						_unit->PlaySoundToSet(13962);
						break;
				}

				Golem_1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28695, 1329.410156f, -88.923073f, 56.717873f, 5.453895f, true, false, 0, 0);
				Golem_1->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(1329.410156f, -88.923073f, 56.717873f, 28695);

				Golem_2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(28695, 1318.171021f, -97.138092f, 56.673134f, 4.696771f, true, false, 0, 0);
				Golem_2->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(1318.171021f, -97.138092f, 56.673134f, 28695);
				
				_unit->GetAIInterface()->SetAIState(STATE_ATTACKING);
				Appel_Golem = false;
				Golem_vers_boss = true;
				Temps_position = 2;
			}break;
		}
    }

    inline WayPoint* CreateWaypoint(int id, uint32 waittime, uint32 flags)
    {
        WayPoint * wp = _unit->CreateWaypointStruct();
        wp->id = id;
        wp->x = Event_Enclume[id].x;
        wp->y = Event_Enclume[id].y;
        wp->z = Event_Enclume[id].z;
        wp->o = Event_Enclume[id].o;
        wp->waittime = waittime;
        wp->flags = flags;
        wp->forwardemoteoneshot = 0;
        wp->forwardemoteid = 0;
        wp->backwardemoteoneshot = 0;
        wp->backwardemoteid = 0;
        wp->forwardskinid = 0;
        wp->backwardskinid = 0;
        return wp;
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
		bool Appel_Golem, Golem_vers_boss;
		int nrspells, Enclume, Temps_position;
		Unit * Golem_1, * Golem_2;
};

/** Mob (20)
	
	Assemblage forge-foudre
	Avant-garde en titane
	Berserker en acier durci
	Brise-siège en titane
	Etincelle d'Ionar
	Formerune forge-foudre
	Foudroyeur en titane
	Géant forge-foudre
	Golem en fusion
	Lieutenant forge-foudre
	Mande-ciel en acier durci
	Ragevapeur caustique
	Réparateur forge-foudre
	Revenant furie-des-tempêtes
	Saccageur en acier durci
	Scorie
	Sentinelle forge-foudre
	Tacticien forge-foudre
	Tempête-de-feu déchaînée
	Vortex orageux

**/
// Mob
#define Assemblage_forge_foudre			28835
// Sort
#define Coup_de_poing_runique			53068
#define Coup_de_poing_runique_Heroic	59151
#define Focalisation_runique			61596
#define Focalisation_runique_Heroic		61579
#define Fourche_d_éclairs				53167
#define Fourche_d_éclairs_Heroic		59152

class Assemblage_forge_foudreAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Assemblage_forge_foudreAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Assemblage_forge_foudreAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Coup_de_poing_runique);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Coup_de_poing_runique_Heroic);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Focalisation_runique);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 5.0f;
			spells[1].maxdist2cast = 35.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Focalisation_runique_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 5.0f;
			spells[1].maxdist2cast = 35.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Fourche_d_éclairs);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = false;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 45.0f;
			spells[2].attackstoptimer = 2000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 30.0f;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Fourche_d_éclairs_Heroic);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = false;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 45.0f;
			spells[2].attackstoptimer = 2000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 30.0f;
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
#define Avant_garde_en_titane			28838
// Sort
#define Lance_trempée_de_poison			53059
#define Lance_trempée_de_poison_Heroic	59178

class Avant_garde_en_titaneAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Avant_garde_en_titaneAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Avant_garde_en_titaneAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Lance_trempée_de_poison);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 5.0f;
			spells[0].maxdist2cast = 35.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Lance_trempée_de_poison_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 5.0f;
			spells[0].maxdist2cast = 35.0f;
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
#define Berserker_en_acier_durci	28579
// Sort
#define Enrager						61369
#define Lancer_une_arme				52740
#define Lancer_une_arme_Heroic		59259

class Berserker_en_acier_durciAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Berserker_en_acier_durciAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Berserker_en_acier_durciAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Enrager);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Lancer_une_arme);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 28.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 30.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Lancer_une_arme);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 28.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 30.0f;
		}
		
		Rage = false;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Rage = false;
			
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
		if((_unit->GetHealthPct() <= 15) && !Rage)
		{
			_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
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
		bool Rage;
		int nrspells;
};

// Mob
#define Brise_siège_en_titane	28961
// Sort
#define Coup_pénétrant			52890
#define Cri_effrayant			19134		// a fix plus tard
#define Froissement				52891
#define Froissement_Heroic		59173
#define Hurlement_perçant		23600

class Brise_siège_en_titaneAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Brise_siège_en_titaneAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    Brise_siège_en_titaneAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Coup_pénétrant);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 30.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Cri_effrayant);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Froissement);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 45;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Froissement_Heroic);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 45;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 1000;
		}
		
		spells[3].info = dbcSpell.LookupEntry(Hurlement_perçant);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = 45;
		spells[3].perctrigger = 18.0f;
		spells[3].attackstoptimer = 1000;
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
#define Etincelle_d_Ionar					28926		// A retest
// Sort
#define Visuel_de_l_étincelle_d_Ionar		52662
#define Brûlure_en_arc_de_cercle			52671		// fontionne pas
#define Brûlure_en_arc_de_cercle_Heroic		59834

class Etincelle_d_IonarAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Etincelle_d_IonarAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Etincelle_d_IonarAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Brûlure_en_arc_de_cercle);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 5.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Brûlure_en_arc_de_cercle);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 5.0f;
		}
		
		Visuel = 0;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Visuel = 0;
			
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
		if(Visuel == 0)
		{
			_unit->CastSpell(_unit, Visuel_de_l_étincelle_d_Ionar, true);
			Visuel = 0;
		}
		else
		{
			Visuel--;
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
		int nrspells, Visuel;
};

// Mob
#define Formerune_forge_foudre		28836
// Sort
#define Déluge_chargé				53049

class Formerune_forge_foudreAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Formerune_forge_foudreAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Formerune_forge_foudreAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Déluge_chargé);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = false;
		spells[0].cooldown = 35;
		spells[0].perctrigger = 30.0f;
		spells[0].attackstoptimer = 6000;
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
#define Foudroyeur_en_titane		28965
// Sort
#define Déviation					52879
#define Déviation_Heroic			59181
#define Lancer						52904
#define Lancer_Heroic				59179
#define Lancer_mortel				52885
#define Lancer_mortel_Heroic		59180

class Foudroyeur_en_titaneAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Foudroyeur_en_titaneAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Foudroyeur_en_titaneAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Déviation);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Déviation_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Lancer);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1500;
			spells[1].mindist2cast = 30.0f;
			spells[1].maxdist2cast = 30.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Lancer_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 30.0f;
			spells[1].attackstoptimer = 1500;
			spells[1].mindist2cast = 8.0f;
			spells[1].maxdist2cast = 30.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Lancer);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = true;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 20.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 8.0f;
			spells[2].maxdist2cast = 30.0f;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Lancer);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = true;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 20.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 8.0f;
			spells[2].maxdist2cast = 30.0f;
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
#define Géant_forge_foudre			28920
// Sort
#define Eclair_de_tempête			53072
#define Eclair_de_tempête_Heroic	59155
#define Frappe_de_l_âme				32315
#define Orage						53071
#define Orage_Heroic				59154

class Géant_forge_foudreAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Géant_forge_foudreAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Géant_forge_foudreAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Eclair_de_tempête);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 35.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Eclair_de_tempête_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 35.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Frappe_de_l_âme);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 15;
		spells[1].perctrigger = 35.0f;
		spells[1].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Orage);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 40;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 2000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Orage_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 40;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 2000;
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
#define Golem_en_fusion				28695
// Sort
#define Fracasser					52429
#define Fracasser_Heroic			59527
#define Frappe_d_immolation			52433
#define Frappe_d_immolation_Heroic	59530
#define Vague_explosive				23113

class Golem_en_fusionAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Golem_en_fusionAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Golem_en_fusionAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Fracasser);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 35;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Fracasser_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 45;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Frappe_d_immolation);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Frappe_d_immolation_Heroic);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 1000;
		}
		
		spells[2].info = dbcSpell.LookupEntry(Vague_explosive);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = 20;
		spells[2].perctrigger = 22.0f;
		spells[2].attackstoptimer = 1000;
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
		_unit->Despawn(0,0);
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
#define Lieutenant_forge_foudre		29240
// Sort
#define Rénovation_de_l_acier		59160		
#define Soudure_a_l_arc				59085	// a fix

class Lieutenant_forge_foudreAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Lieutenant_forge_foudreAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Lieutenant_forge_foudreAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Rénovation_de_l_acier);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = false;
		spells[0].cooldown = 45;
		spells[0].perctrigger = 15.0f;
		spells[0].attackstoptimer = 1500;
		
		spells[0].info = dbcSpell.LookupEntry(Soudure_a_l_arc);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = true;
		spells[0].cooldown = 20;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 1000;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 40.0f;
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
#define Mande_ciel_en_acier_durci				28580
// Sort
#define Balle_percutante						52754
#define Balle_percutante_Heroic					59148
#define Désengagement							61507
#define Flèches_multiples_percutantes			52755
#define Flèches_multiples_percutantes_Heroic 	59147
#define Tir										16100
#define Tir_Heroic								61515

class Mande_ciel_en_acier_durciAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Mande_ciel_en_acier_durciAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    Mande_ciel_en_acier_durciAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Balle_percutante);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 5.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Balle_percutante_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 5.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Désengagement);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 40;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Flèches_multiples_percutantes);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = true;
			spells[2].cooldown = 15;
			spells[2].perctrigger = 20.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 5.0f;
			spells[2].maxdist2cast = 30.0f;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Flèches_multiples_percutantes_Heroic);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = true;
			spells[2].cooldown = 15;
			spells[2].perctrigger = 20.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 5.0f;
			spells[2].maxdist2cast = 30.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[3].info = dbcSpell.LookupEntry(Tir);
			spells[3].targettype = TARGET_RANDOM_SINGLE;
			spells[3].instant = true;
			spells[3].cooldown = 15;
			spells[3].perctrigger = 30.0f;
			spells[3].attackstoptimer = 1000;
			spells[3].mindist2cast = 5.0f;
			spells[3].maxdist2cast = 30.0f;
		}
		else
		{
			spells[3].info = dbcSpell.LookupEntry(Tir_Heroic);
			spells[3].targettype = TARGET_RANDOM_SINGLE;
			spells[3].instant = true;
			spells[3].cooldown = 15;
			spells[3].perctrigger = 30.0f;
			spells[3].attackstoptimer = 1000;
			spells[3].mindist2cast = 5.0f;
			spells[3].maxdist2cast = 30.0f;
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
#define Ragevapeur_caustique		28583
// Sort
#define Explosion_de_vapeur			52531
#define Explosion_de_vapeur_Heroic	59141

class Ragevapeur_caustiqueAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Ragevapeur_caustiqueAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Ragevapeur_caustiqueAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_de_vapeur);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_de_vapeur);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 25;
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
#define Réparateur_forge_foudre		28582
// Sort
#define Coup_de_marteau				52773
#define Rénovation_de_l_acier		59160

class Réparateur_forge_foudreAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Réparateur_forge_foudreAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Réparateur_forge_foudreAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Coup_de_marteau);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 20;
		spells[0].perctrigger = 30.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Rénovation_de_l_acier);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = false;
		spells[1].cooldown = 40;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 1500;
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
#define Revenant_furie_des_tempêtes		28826
// Sort
#define Electrochoc						53043
#define Electrochoc_Heroic				59168
#define Trait_de_tonnerre				52905
#define Trait_de_tonnerre_Heroic		59167

class Revenant_furie_des_tempêtesAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Revenant_furie_des_tempêtesAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Revenant_furie_des_tempêtesAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Electrochoc);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 20.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Electrochoc_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 20.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Trait_de_tonnerre);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 35;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 3000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 100.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Trait_de_tonnerre_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 35;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 3000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 100.0f;
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
#define Saccageur_en_acier_durci	28578
// Sort
#define Enchaînement_SEAD			42724
#define Heurt_de_bouclier			15655
#define Heurt_de_bouclier_Heroic	59142

class Saccageur_en_acier_durciAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Saccageur_en_acier_durciAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Saccageur_en_acier_durciAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Enchaînement_SEAD);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 30.0f;
		spells[0].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Heurt_de_bouclier);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 40;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Heurt_de_bouclier_Heroic);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 40;
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
#define Scorie					28585
// Sort
#define Fondre_armure			61509
#define Fondre_armure_Heroic	61510
#define Vague_explosive			23113	
#define Vague_explosive_Heroic	22424

class ScorieAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(ScorieAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    ScorieAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Fondre_armure);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 35;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Fondre_armure_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 35;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Vague_explosive);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 30.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Vague_explosive);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 30.0f;
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
#define Sentinelle_forge_foudre		28837
// Sort
#define Beuglement_fulminant		53047
#define Sommeil						53045
#define Sommeil_Heroic				59165

class Sentinelle_forge_foudreAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Sentinelle_forge_foudreAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Sentinelle_forge_foudreAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}
		
		spells[0].info = dbcSpell.LookupEntry(Beuglement_fulminant);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 35;
		spells[0].perctrigger = 5.0f;
		spells[0].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Sommeil);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 30;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Sommeil_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 30;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
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
#define Tacticien_forge_foudre	28581
// Sort
#define Rayon_a_souder			52778
#define Rayon_a_souder_Heroic	59166
#define Soudure_a_l_arc			59085	// a fix

class Tacticien_forge_foudreAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Tacticien_forge_foudreAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Tacticien_forge_foudreAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Rayon_a_souder);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 5000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Rayon_a_souder_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 5000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Soudure_a_l_arc);
		spells[1].targettype = TARGET_RANDOM_SINGLE;
		spells[1].instant = true;
		spells[1].cooldown = 20;
		spells[1].perctrigger = 25.0f;
		spells[1].attackstoptimer = 1000;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 40.0f;
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
#define Tempête_de_feu_déchaînée	28584
// Sort
#define Explosion_de_lave			53788
#define Explosion_de_lave_Heroic	59182
#define Postcombustion				52624

class Tempête_de_feu_déchaînéeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Tempête_de_feu_déchaînéeAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Tempête_de_feu_déchaînéeAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_de_lave);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_de_lave_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Postcombustion);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = false;
		spells[1].cooldown = 40;
		spells[1].perctrigger = 18.0f;
		spells[1].attackstoptimer = 2500;
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
#define Vortex_orageux	28547
// Sort
#define Cyclone			60236
#define Eclair			53044
#define Eclair_Heroic	59169

class Vortex_orageuxAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Vortex_orageuxAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Vortex_orageuxAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Cyclone);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = false;
		spells[0].cooldown = 25;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 1500;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 30.0f;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Eclair);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 30.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 40.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Eclair);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 30.0f;
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

void Ulduar_Les_salles_des_foudres(ScriptMgr * mgr)
{
	// Boss
	mgr->register_creature_script(Général_Bjarngrim,				&Général_BjarngrimAI::Create);
	mgr->register_creature_script(Ionar,							&IonarAI::Create);
	mgr->register_creature_script(Loken,							&LokenAI::Create);
	mgr->register_creature_script(Volkhan,							&VolkhanAI::Create);
	// Mob
	mgr->register_creature_script(Assemblage_forge_foudre,			&Assemblage_forge_foudreAI::Create);
	mgr->register_creature_script(Avant_garde_en_titane,			&Avant_garde_en_titaneAI::Create);
	mgr->register_creature_script(Berserker_en_acier_durci,			&Berserker_en_acier_durciAI::Create);
	mgr->register_creature_script(Brise_siège_en_titane,			&Brise_siège_en_titaneAI::Create);
	mgr->register_creature_script(Etincelle_d_Ionar,				&Etincelle_d_IonarAI::Create);
	mgr->register_creature_script(Formerune_forge_foudre,			&Formerune_forge_foudreAI::Create);
	mgr->register_creature_script(Foudroyeur_en_titane,				&Foudroyeur_en_titaneAI::Create);
	mgr->register_creature_script(Géant_forge_foudre,				&Géant_forge_foudreAI::Create);
	mgr->register_creature_script(Golem_en_fusion,					&Golem_en_fusionAI::Create);
	mgr->register_creature_script(Lieutenant_forge_foudre,			&Lieutenant_forge_foudreAI::Create);
	mgr->register_creature_script(Mande_ciel_en_acier_durci,		&Mande_ciel_en_acier_durciAI::Create);
	mgr->register_creature_script(Ragevapeur_caustique,				&Ragevapeur_caustiqueAI::Create);
	mgr->register_creature_script(Réparateur_forge_foudre,			&Réparateur_forge_foudreAI::Create);
	mgr->register_creature_script(Revenant_furie_des_tempêtes,		&Revenant_furie_des_tempêtesAI::Create);
	mgr->register_creature_script(Saccageur_en_acier_durci,			&Saccageur_en_acier_durciAI::Create);
	mgr->register_creature_script(Scorie,							&ScorieAI::Create);
	mgr->register_creature_script(Sentinelle_forge_foudre,			&Sentinelle_forge_foudreAI::Create);
	mgr->register_creature_script(Tacticien_forge_foudre,			&Tacticien_forge_foudreAI::Create);
	mgr->register_creature_script(Tempête_de_feu_déchaînée,			&Tempête_de_feu_déchaînéeAI::Create);
	mgr->register_creature_script(Vortex_orageux,					&Vortex_orageuxAI::Create);
}