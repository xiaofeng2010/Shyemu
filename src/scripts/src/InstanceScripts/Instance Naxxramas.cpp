#include "StdAfx.h"
#include "Setup.h"

#ifdef WIN32
#pragma warning(disable:4018)
#endif

/** Boss (20)

		Anub'Rekhan
		Baron Vaillefendre
		Dame Blaumeux
		Feugen
		Gluth
		Gothik le Moissonneur
		Grande veuve Faerlina
		Grobbulus
	Heigan l'Impur
		Horreb
		Instructeur Razuvious
		Kel'Thuzad
		Le Recousu
		Maexxna
		Noth le Porte-peste
		Saphiron
		Sire Zeliek
		Stalagg
	Thaddius
		Thane Korth'azz

**/

// Boss
#define Anub_Rekhan						15956
// Sort
#define Berserk							26662
#define Empaler							28783
#define Empaler_Heroic					56090
#define Nuée_de_sauterelles				54021
#define Nuée_de_sauterelles_Heroic		28785

class Anub_RekhanAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Anub_RekhanAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Anub_RekhanAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Berserk);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Empaler);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 45;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 5000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Empaler_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 45;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 5000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Nuée_de_sauterelles);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = false;
			spells[2].cooldown = 90;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 3000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Nuée_de_sauterelles_Heroic);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = false;
			spells[2].cooldown = 90;
			spells[2].perctrigger = 25.0f;
			spells[2].attackstoptimer = 3000;
		}
		
		Enrage = false;
		Non_nuéé = false;
		Add = true;
		Lancement_event = false;
		Decompte_Combat = 0;
		Phase = 0;
		
		RegisterAIUpdateEvent(1000);
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Enrage = false;
		Non_nuéé = false;
		Add = true;
		Lancement_event = true;
		Decompte_Combat = 0;
		Phase = 1;

		RegisterAIUpdateEvent(1000);
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			Démon_Crypte1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16573, 3300.500000f, -3503.570068f, 287.161011f, 2.321290f, true, false, 0, 0);
			Démon_Crypte1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3300.500000f, -3503.570068f, 287.161011f, 16573);
						
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
			
			Démon_Crypte1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
		}
		else
		{
			Démon_Crypte1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16573, 3300.500000f, -3503.570068f, 287.161011f, 2.321290f, true, false, 0, 0);
			Démon_Crypte2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16573, 3301.465332f, -3448.500000f, 287.077789f, 3.947731f, true, false, 0, 0);
			Démon_Crypte1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3300.500000f, -3503.570068f, 287.161011f, 16573);
			Démon_Crypte2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3301.465332f, -3448.500000f, 287.077789f, 16573);
						
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
			
			Démon_Crypte1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Démon_Crypte2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
		}
		
		int RandomSpeach = RandomUInt(2);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8785);
				_unit->PlaySoundToSet(8785);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8786);
				_unit->PlaySoundToSet(8786);
				break;
				
			case 2:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8787);
				_unit->PlaySoundToSet(8787);
				break;
		}
	}
	

	void OnTargetDied(Unit * mTarget)
    {
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8789);
		_unit->PlaySoundToSet(8789);
	}

    void OnCombatStop(Unit * mTarget)
    {
		_unit->RemoveAura(Berserk);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		_unit->RemoveAura(Berserk);
		RemoveAIUpdateEvent();
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
		}
	}
	
	void Intro()
	{
		for(std::set<Player*>::iterator Detection = _unit->GetInRangePlayerSetBegin(); Detection != _unit->GetInRangePlayerSetEnd(); Detection++)
		{
			if((*Detection)->GetTypeId() == TYPEID_PLAYER)
			{
				int RandomSpeach = RandomUInt(3);
				switch (RandomSpeach)
				{
					case 0:
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8788);
						_unit->PlaySoundToSet(8788);
						Phase = 1;
						break;
				
					case 1:
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8790);
						_unit->PlaySoundToSet(8790);
						Phase = 1;
						break;
				
					case 2:
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8791);
						_unit->PlaySoundToSet(8791);
						Phase = 1;
						break;
						
					case 3:
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8792);
						_unit->PlaySoundToSet(8792);
						Phase = 1;
						break;
						
					case 4:
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8793);
						_unit->PlaySoundToSet(8793);
						Phase = 1;
						break;
				}
			}
		}
	}

    void Combat()
	{
		if(Lancement_event)
		{
			if(!Enrage && Decompte_Combat >= 600)
			{
				_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
				Enrage = true;
			}
			else if(!Enrage)
			{
				Decompte_Combat++;
			}
			
			if(((_unit->HasAura(Nuée_de_sauterelles)) && Add) || ((_unit->HasAura(Nuée_de_sauterelles_Heroic)) && Add))
			{
				int RandomSpawn = RandomUInt(1);
				switch (RandomSpawn)
				{
					case 0:
					{
						Démon_Crypte3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16573, 3300.500000f, -3503.570068f, 287.161011f, 2.321290f, true, false, 0, 0);
						Démon_Crypte3 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3300.500000f, -3503.570068f, 287.161011f, 16573);

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
				
						Démon_Crypte3->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
						Add = false;
						Non_nuéé = true;
						break;
					}
					
					case 1:
					{
						Démon_Crypte3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16573, 3301.465332f, -3448.500000f, 287.077789f, 3.947731f, true, false, 0, 0);
						Démon_Crypte3 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3301.465332f, -3448.500000f, 287.077789f, 16573);

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
				
						Démon_Crypte3->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
						Add = false;
						Non_nuéé = true;
						break;
					}
				}
			}
			else if((Non_nuéé && !_unit->HasAura(Nuée_de_sauterelles)) || (Non_nuéé && !_unit->HasAura(Nuée_de_sauterelles_Heroic)))
			{
				Non_nuéé = false;
				Add = true;
			}
				
			float val = (float)RandomFloat(100.0f);
			SpellCast(val);
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
		bool Enrage, Non_nuéé, Add, Lancement_event;
		int nrspells;
		uint32 Decompte_Combat,	Phase;
		Unit * Démon_Crypte1, * Démon_Crypte2, * Démon_Crypte3;
};

// Boss
#define Baron_Vaillefendre		30549
// Sort
#define Marque_de_Vaillefendre	28834
#define Ombre_impie				28882
#define Ombre_impie_heroic		57369
#define Berserk_BV				26662
#define Galot					256

bool Mort_Vaillefendre;
bool Mort_Blaumeux;
bool Mort_Zeliek;
bool Mort_Korth_azz;

struct Coordonnée
{
    float x;
    float y;
    float z;
    float o;
};

static Coordonnée Porte_Nord[] =
{
	{ },
    { 2545.157959f, -2969.647705f, 241.309708f, 5.478341f },
	{ 2587.148193f, -2967.077637f, 241.335281f, 0.209101f },
};

class Baron_VaillefendreAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Baron_VaillefendreAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Baron_VaillefendreAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Marque_de_Vaillefendre);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Ombre_impie);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1500;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 25.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Ombre_impie_heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1500;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 25.0f;
		}
		
		spells[2].info = dbcSpell.LookupEntry(Berserk_BV);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;
		
		Phase = 0;
		Temps_Marque = 24;
		Marque = 0;
		Enrage = false;
		lancement_event = true;
		Combat_lancer = false;
		Mort_Vaillefendre = false;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		
		RegisterAIUpdateEvent(500);
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
		
		Phase = 1;
		Temps_Marque = 24;
		Marque = 0;
		Enrage = false;
		Combat_lancer = true;
		Mort_Vaillefendre = false;
		RegisterAIUpdateEvent(1000);
	}

	void OnCombatStop(Unit * mTarget)
    {
		_unit->RemoveAura(Berserk_BV);
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		RemoveAIUpdateEvent();
		
		if(Combat_lancer)
		{
			Phase = 0;
			lancement_event = true;
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			Combat_lancer = false;
			_unit->SetPosition(2527.280029f, -2953.679932f, 245.552002f, 5.330330f, false);
		}
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		Mort_Vaillefendre = true;
		
		if(Mort_Blaumeux && Mort_Zeliek && Mort_Korth_azz)
		{
			_unit->GetMapMgr()->GetInterface()->SpawnGameObject(181366, 2519.668213f, -2950.441895f, 245.552444f, 5.690034, true, false, 0);
		}
    }
	
	void AIUpdate()
	{
		switch (Phase)
		{
			case 0:
				Changement_position();
				break;
			case 1:
				Combat();
				break;
		}
	}
	
	void Changement_position()
	{
		if(lancement_event)
		{
			for(std::set<Player*>::iterator Detection = _unit->GetInRangePlayerSetBegin(); Detection != _unit->GetInRangePlayerSetEnd(); Detection++)
			{
				if((*Detection)->GetTypeId() == TYPEID_PLAYER)
				{
					if(_unit->CalcDistance(*Detection) <= 43.0f)
					{
						for (int i = 1; i < 4; i++)
						{
							_unit->GetAIInterface()->addWayPoint(CreateWaypoint(i, 0, Galot));
						}
		
						_unit->GetAIInterface()->StopMovement(1000);
						_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
						_unit->GetAIInterface()->setWaypointToMove(1);
						lancement_event = false;
					}
				}
			}
		}
	}
	
	void Combat()
	{
		if(!Enrage && Temps_Marque < 1)
		{
			std::vector<Unit*> TargetTable;	

			for( set<Player*>::iterator PlayerIter = _unit->GetInRangePlayerSetBegin(); PlayerIter != _unit->GetInRangePlayerSetEnd(); ++PlayerIter ) 
			{ 
				if (_unit->CalcDistance((*PlayerIter)) < 45.0f)
				{
					TargetTable.push_back(*PlayerIter);
				} 
			}
	
			if (!TargetTable.size())
				return;
				
			for(size_t i= 0 ; i<TargetTable.size(); i++)
			{
				_unit->CastSpell(TargetTable[i], spells[0].info, spells[0].instant);
				
				for (int Nombre_Marque = 0; Nombre_Marque < 100; Nombre_Marque++)
				{
					if (TargetTable[i]->FindAuraCountByHash(SPELL_HASH_MARK_OF_RIVENDARE, Nombre_Marque))
					{
						switch (Nombre_Marque)
						{
						
							case 2:
								_unit->DealDamage(TargetTable[i], 500, 0, 0, 0, true);
								break;
							
							case 3:
								_unit->DealDamage(TargetTable[i], 1500, 0, 0, 0, true);
								break;
						
							case 4:
								_unit->DealDamage(TargetTable[i], 4000, 0, 0, 0, true);
								break;
								
							case 5:
								_unit->DealDamage(TargetTable[i], 12500, 0, 0, 0, true);
								break;
								
							case 6:
								_unit->DealDamage(TargetTable[i], 20000, 0, 0, 0, true);
								break;
						}
						
						if (Nombre_Marque > 6)
						{
							_unit->DealDamage(TargetTable[i], 14000 + (Nombre_Marque * 1000), 0, 0, 0, true);
						}
					}
				}
			}
			
			Marque++;
			Temps_Marque = 12;
		}
		else if(!Enrage)
		{
			Temps_Marque--;
		}
		
		if(!Enrage && Marque == 100)
		{
			Enrage = true;
			_unit->CastSpell(_unit, spells[2].info, spells[2].instant);
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}
	
	void OnReachWP(uint32 iWaypointId, bool bForwards)
    {
		switch (iWaypointId)
		{
			case 1:
			{
				_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
				_unit->GetAIInterface()->setWaypointToMove(2);
			}break;
			
			case 2:
			{
				_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
				_unit->GetAIInterface()->SetAIState(STATE_ATTACKING);
				
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
				Phase = 1;
			}break;
		}
    }
	
	inline WayPoint* CreateWaypoint(int id, uint32 waittime, uint32 flags)
    {
        WayPoint * wp = _unit->CreateWaypointStruct();
        wp->id = id;
        wp->x = Porte_Nord[id].x;
        wp->y = Porte_Nord[id].y;
        wp->z = Porte_Nord[id].z;
        wp->o = Porte_Nord[id].o;
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
		bool Enrage, lancement_event, Combat_lancer;
		int nrspells, Marque;
		uint32 Temps_Marque, Phase;
};
	
// Boss
#define Dame_Blaumeux				16065
// Sort
#define Marque_de_Blaumeux			28833
#define Trait_de_l_ombre			57374
#define Trait_de_l_ombre_Heroic		57464
#define Berserk_DB					26662
#define Zone_de_Vide				28863
#define Douleur_inflexible			57381

static Coordonnée Porte_Sud[] =
{
	{ },
    { 2496.755859f, -2938.776855f, 241.277374f, 2.436032f },
	{ 2466.223389f, -2951.101807f, 241.275909f, 5.987597f },
};

class Dame_BlaumeuxAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Dame_BlaumeuxAI);
	SP_AI_Spell spells[5];
	bool m_spellcheck[5];

    Dame_BlaumeuxAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 5;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Marque_de_Blaumeux);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Trait_de_l_ombre);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 5;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 45.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Trait_de_l_ombre_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 5;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 45.0f;
		}
		
		spells[2].info = dbcSpell.LookupEntry(Berserk_DB);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;
		
		spells[3].info = dbcSpell.LookupEntry(Zone_de_Vide);
		spells[3].targettype = TARGET_RANDOM_DESTINATION;
		spells[3].instant = true;
		spells[3].cooldown = 25;
		spells[3].perctrigger = 15.0f;
		spells[3].attackstoptimer = 1000;
		spells[3].mindist2cast = 0.0f;
		spells[3].maxdist2cast = 45.0f;
		
		spells[4].info = dbcSpell.LookupEntry(Douleur_inflexible);
		spells[4].targettype = TARGET_SELF;
		spells[4].instant = false;
		spells[4].cooldown = 35;
		spells[4].perctrigger = 25.0f;
		spells[4].attackstoptimer = 2000;
		
		Phase = 0;
		Temps_Marque = 24;
		Marque = 0;
		Enrage = false;
		lancement_event = true;
		Combat_lancer = false;
		Mort_Blaumeux = false;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		
		RegisterAIUpdateEvent(500);
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
		
		Phase = 1;
		Temps_Marque = 24;
		Marque = 0;
		Enrage = false;
		Combat_lancer = true;
		Mort_Blaumeux = false;
		RegisterAIUpdateEvent(1000);
	}

	void OnCombatStop(Unit * mTarget)
    {
		_unit->RemoveAura(Berserk_DB);
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		RemoveAIUpdateEvent();
		
		if(Combat_lancer)
		{
			Phase = 0;
			lancement_event = true;
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			Combat_lancer = false;
			
			_unit->SetPosition(2517.620117f, -2959.379883f, 245.636002f, 5.724680f, false);
		}
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		Mort_Blaumeux = true;
		
		if(Mort_Vaillefendre && Mort_Zeliek && Mort_Korth_azz)
		{
			_unit->GetMapMgr()->GetInterface()->SpawnGameObject(181366, 2519.668213f, -2950.441895f, 245.552444f, 5.690034, true, false, 0);
		}
    }
	
	void AIUpdate()
	{
		switch (Phase)
		{
			case 0:
				Changement_position();
				break;
			case 1:
				Combat();
				break;
		}
	}
	
	void Changement_position()
	{
		if(lancement_event)
		{
			for(std::set<Player*>::iterator Detection = _unit->GetInRangePlayerSetBegin(); Detection != _unit->GetInRangePlayerSetEnd(); Detection++)
			{
				if((*Detection)->GetTypeId() == TYPEID_PLAYER)
				{
					if(_unit->CalcDistance(*Detection) <= 45.0f)
					{
						for (int i = 1; i < 4; i++)
						{
							_unit->GetAIInterface()->addWayPoint(CreateWaypoint(i, 0, Galot));
						}
		
						_unit->GetAIInterface()->StopMovement(1000);
						_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
						_unit->GetAIInterface()->setWaypointToMove(1);
						lancement_event = false;
					}
				}
			}
		}
	}
	
	void Combat()
	{
		if(!Enrage && Temps_Marque < 1)
		{
			std::vector<Unit*> TargetTable;	

			for( set<Player*>::iterator PlayerIter = _unit->GetInRangePlayerSetBegin(); PlayerIter != _unit->GetInRangePlayerSetEnd(); ++PlayerIter ) 
			{ 
				if (_unit->CalcDistance((*PlayerIter)) < 45.0f)
				{
					TargetTable.push_back(*PlayerIter);
				} 
			}
	
			if (!TargetTable.size())
				return;
				
			for(size_t i= 0 ; i<TargetTable.size(); i++)
			{
				_unit->CastSpell(TargetTable[i], spells[0].info, spells[0].instant);
				
				for (int Nombre_Marque = 0; Nombre_Marque < 100; Nombre_Marque++)
				{
					if (TargetTable[i]->FindAuraCountByHash(SPELL_HASH_MARK_OF_BLAUMEUX, Nombre_Marque))
					{
						switch (Nombre_Marque)
						{
						
							case 2:
								_unit->DealDamage(TargetTable[i], 500, 0, 0, 0, true);
								break;
							
							case 3:
								_unit->DealDamage(TargetTable[i], 1500, 0, 0, 0, true);
								break;
						
							case 4:
								_unit->DealDamage(TargetTable[i], 4000, 0, 0, 0, true);
								break;
								
							case 5:
								_unit->DealDamage(TargetTable[i], 12500, 0, 0, 0, true);
								break;
								
							case 6:
								_unit->DealDamage(TargetTable[i], 20000, 0, 0, 0, true);
								break;
						}
						
						if (Nombre_Marque > 6)
						{
							_unit->DealDamage(TargetTable[i], 14000 + (Nombre_Marque * 1000), 0, 0, 0, true);
						}
					}
				}
			}
			
			Marque++;
			Temps_Marque = 15;
		}
		else if(!Enrage)
		{
			Temps_Marque--;
		}
		
		if(!Enrage && Marque == 100)
		{
			Enrage = true;
			_unit->CastSpell(_unit, spells[2].info, spells[2].instant);
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}
	
	void OnReachWP(uint32 iWaypointId, bool bForwards)
    {
		switch (iWaypointId)
		{
			case 1:
			{
				_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
				_unit->GetAIInterface()->setWaypointToMove(2);
			}break;
			
			case 2:
			{
				_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
				_unit->GetAIInterface()->SetAIState(STATE_ATTACKING);
				
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
				Phase = 1;
			}break;
		}
    }
	
	inline WayPoint* CreateWaypoint(int id, uint32 waittime, uint32 flags)
    {
        WayPoint * wp = _unit->CreateWaypointStruct();
        wp->id = id;
        wp->x = Porte_Sud[id].x;
        wp->y = Porte_Sud[id].y;
        wp->z = Porte_Sud[id].z;
        wp->o = Porte_Sud[id].o;
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
		bool Enrage, lancement_event, Combat_lancer;
		int nrspells, Marque;
		uint32 Temps_Marque, Phase;
};

// Boss
#define Gluth					15932
// Sort
#define	Blessure_mortelle		54378
#define Enrager					28371
#define Décimer					28374
#define Berserk_GH				26662
	
class GluthAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(GluthAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    GluthAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Blessure_mortelle);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 35.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(Enrager);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 45;
		spells[1].perctrigger = 20.0f;
		spells[1].attackstoptimer = 1000;
		
		spells[2].info = dbcSpell.LookupEntry(Décimer);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;
		
		spells[3].info = dbcSpell.LookupEntry(Berserk_GH);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 0.0f;
		spells[3].attackstoptimer = 1000;
		
		Temps_Décimer = 110;
		Decompte_Combat = 0;
		Temps_Croq_zombie = 10;
		Enrage = false;
		Croq_zombie_spawn = false;
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Temps_Décimer = 110;
		Decompte_Combat = 0;
		Temps_Croq_zombie = 10;
		Enrage = false;
		Croq_zombie_spawn = false;
			
		RegisterAIUpdateEvent(1000);
	}

    void OnCombatStop(Unit * mTarget)
    {
        _unit->RemoveAura(Berserk_GH);
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		_unit->RemoveAura(Berserk);
		RemoveAIUpdateEvent();
    }
	
	void AIUpdate()
	{
		if(!Enrage && Decompte_Combat >= 480)
		{
			_unit->CastSpell(_unit, spells[3].info, spells[3].instant);
			Enrage = true;
		}
		else if(!Enrage)
		{
			Decompte_Combat++;
		}
		
		if(Temps_Décimer < 1)
		{
			_unit->CastSpell(_unit, spells[2].info, spells[2].instant);
			Temps_Décimer = 110;
		}
		else
		{
			Temps_Décimer--;
		}
		
		if(Temps_Croq_zombie < 1)
		{
			int RandomSpawn = RandomUInt(1);
			switch (RandomSpawn)
			{
				case 0:
				{
					Croq_zombie1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16360, 3270.129883f, -3169.949951f, 297.506012f, 5.881760f, true, false, 0, 0);
					Croq_zombie2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16360, 3307.300049f, -3183.449951f, 297.506012f, 5.742130f, true, false, 0, 0);
					Croq_zombie1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3270.129883f, -3169.949951f, 297.506012f, 16360);
					Croq_zombie2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3307.300049f, -3183.449951f, 297.506012f, 16360);
					Croq_zombie1->GetAIInterface()->MoveTo(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
					Croq_zombie2->GetAIInterface()->MoveTo(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
					Temps_Croq_zombie = 10;
					break;
				}
				
				case 1:
				{
					Croq_zombie1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16360, 3270.129883f, -3169.949951f, 297.506012f, 5.881760f, true, false, 0, 0);
					Croq_zombie2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16360, 3255.508789f, -3132.175537f, 297.422668f, 0.012555f, true, false, 0, 0);
					Croq_zombie1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3270.129883f, -3169.949951f, 297.506012f, 16360);
					Croq_zombie2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3255.508789f, -3132.175537f, 297.422668f, 16360);
					Croq_zombie1->GetAIInterface()->MoveTo(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
					Croq_zombie2->GetAIInterface()->MoveTo(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
					Temps_Croq_zombie = 10;
					break;
				}
				
				case 2:
				{
					Croq_zombie1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16360, 3307.300049f, -3183.449951f, 297.506012f, 5.742130f, true, false, 0, 0);
					Croq_zombie2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16360, 3255.508789f, -3132.175537f, 297.422668f, 0.012555f, true, false, 0, 0);
					Croq_zombie1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3307.300049f, -3183.449951f, 297.506012f, 16360);
					Croq_zombie2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3255.508789f, -3132.175537f, 297.422668f, 16360);
					Croq_zombie1->GetAIInterface()->MoveTo(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
					Croq_zombie2->GetAIInterface()->MoveTo(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
					Temps_Croq_zombie = 10;
					break;
				}
			}
		}
		else
		{
			Temps_Croq_zombie--;
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
		bool Enrage, Croq_zombie_spawn;
		int nrspells;
		uint32 Decompte_Combat,	Temps_Décimer, Temps_Croq_zombie;
		Unit * Croq_zombie1, * Croq_zombie2;
};

// Boss
#define Gothik_le_Moissonneur		16060
// Sort
#define Trait_de_l_ombre_GM			29317
#define Trait_de_l_ombre_Heroic_GM	56405
#define Moisson_d_âme				28679

class Gothik_le_MoissonneurAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Gothik_le_MoissonneurAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Gothik_le_MoissonneurAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Trait_de_l_ombre_GM);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 45.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Trait_de_l_ombre_Heroic_GM);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 45.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Moisson_d_âme);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
		
		Phase = 0;
		Lancement_Invocation = 0;
		Decompte_Teleportation = 30;
		Zone_vivant = false;
		Zone_mort_vivant = false;
		Lancement_Event = false;
		Fin_Invocation = false;
		Entre_en_Combat = false;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		
		RegisterAIUpdateEvent(1000);
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Phase = 1;
		Entre_en_Combat = true;
			
		RegisterAIUpdateEvent(1000);
		
		int RandomSpeach = RandomUInt(2);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8785);
				_unit->PlaySoundToSet(8785);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8786);
				_unit->PlaySoundToSet(8786);
				break;
				
			case 2:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8787);
				_unit->PlaySoundToSet(8787);
				break;
		}
    }

	void OnTargetDied(Unit * mTarget)
    {
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8800);
		_unit->PlaySoundToSet(8789);
	}

    void OnCombatStop(Unit * mTarget)
    {
        if(Entre_en_Combat && Fin_Invocation)
		{
			_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
			_unit->GetAIInterface()->SetAIState(STATE_IDLE);
			_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
			RemoveAIUpdateEvent();
		
			Phase = 0;
			Zone_vivant = false;
			Zone_mort_vivant = false;
			Lancement_Event = false;
			Entre_en_Combat = false;
			Lancement_Invocation = 0;
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			RegisterAIUpdateEvent(1000);
		}
    }

    void OnDied(Unit * mKiller)
    {
		_unit->RemoveAura(Berserk);
		RemoveAIUpdateEvent();
    }
	
	void AIUpdate()
	{
		switch (Phase)
		{
			case 0:
				Invocation();
				break;
			case 1:
				Combat();
				break;
		}
	}
	
	void Invocation()
	{
		if(!Lancement_Event)
		{
			for(std::set<Player*>::iterator Detection = _unit->GetInRangePlayerSetBegin(); Detection != _unit->GetInRangePlayerSetEnd(); Detection++)
			{
				if((*Detection)->GetTypeId() == TYPEID_PLAYER)
				{
					if(_unit->CalcDistance(*Detection) <= 45.0f)
					{
						Lancement_Event = true;
						Lancement_Invocation = 0;
					}
				}
			}
		}

		switch (Lancement_Invocation)
		{
			case 30:
			{
				Jeune1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2714.560059f, -3430.610107f, 268.645996f, 1.413720f, true, false, 0, 0);
				Jeune2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2692.209961f, -3428.780029f, 268.645996f, 1.483530f, true, false, 0, 0);
				Jeune3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2669.580078f, -3428.860107f, 268.645996f, 1.378810f, true, false, 0, 0);
				Jeune1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2714.560059f, -3430.610107f, 268.645996f, 16124);
				Jeune2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2692.209961f, -3428.780029f, 268.645996f, 16124);
				Jeune3 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2669.580078f, -3428.860107f, 268.645996f, 16124);

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
			
				Jeune1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune3->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				break;
			}
			case 50:
			{
				Jeune4 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2714.560059f, -3430.610107f, 268.645996f, 1.413720f, true, false, 0, 0);
				Jeune5 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2692.209961f, -3428.780029f, 268.645996f, 1.483530f, true, false, 0, 0);
				Jeune6 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2669.580078f, -3428.860107f, 268.645996f, 1.378810f, true, false, 0, 0);
				Jeune4 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2714.560059f, -3430.610107f, 268.645996f, 16124);
				Jeune5 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2692.209961f, -3428.780029f, 268.645996f, 16124);
				Jeune6 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2669.580078f, -3428.860107f, 268.645996f, 16124);

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
			
				Jeune4->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune5->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune6->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());				
				break;
			}
			
			case 70:
			{	Jeune7 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2714.560059f, -3430.610107f, 268.645996f, 1.413720f, true, false, 0, 0);
				Jeune8 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2692.209961f, -3428.780029f, 268.645996f, 1.483530f, true, false, 0, 0);
				Jeune9 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2669.580078f, -3428.860107f, 268.645996f, 1.378810f, true, false, 0, 0);
				Jeune7 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2714.560059f, -3430.610107f, 268.645996f, 16124);
				Jeune8 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2692.209961f, -3428.780029f, 268.645996f, 16124);
				Jeune9 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2669.580078f, -3428.860107f, 268.645996f, 16124);

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
			
				Jeune7->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune8->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune9->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());				
				break;
			}
			
			case 90:
			{
				Jeune10 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2714.560059f, -3430.610107f, 268.645996f, 1.413720f, true, false, 0, 0);
				Jeune11 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2692.209961f, -3428.780029f, 268.645996f, 1.483530f, true, false, 0, 0);
				Jeune12 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2669.580078f, -3428.860107f, 268.645996f, 1.378810f, true, false, 0, 0);
				Jeune10 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2714.560059f, -3430.610107f, 268.645996f, 16124);
				Jeune11 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2692.209961f, -3428.780029f, 268.645996f, 16124);
				Jeune12 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2669.580078f, -3428.860107f, 268.645996f, 16124);

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
			
				Jeune10->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune11->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune12->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());				
				break;
			}
			
			case 110:
			{
				Jeune13 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2714.560059f, -3430.610107f, 268.645996f, 1.413720f, true, false, 0, 0);
				Jeune14 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2692.209961f, -3428.780029f, 268.645996f, 1.483530f, true, false, 0, 0);
				Jeune15 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2669.580078f, -3428.860107f, 268.645996f, 1.378810f, true, false, 0, 0);
				Jeune13 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2714.560059f, -3430.610107f, 268.645996f, 16124);
				Jeune14 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2692.209961f, -3428.780029f, 268.645996f, 16124);
				Jeune15 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2669.580078f, -3428.860107f, 268.645996f, 16124);

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
			
				Jeune13->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune14->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune15->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());				
				break;
			}
			
			case 130:
			{
				Jeune16 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2714.560059f, -3430.610107f, 268.645996f, 1.413720f, true, false, 0, 0);
				Jeune17 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2692.209961f, -3428.780029f, 268.645996f, 1.483530f, true, false, 0, 0);
				Jeune18 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2669.580078f, -3428.860107f, 268.645996f, 1.378810f, true, false, 0, 0);
				Jeune16 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2714.560059f, -3430.610107f, 268.645996f, 16124);
				Jeune17 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2692.209961f, -3428.780029f, 268.645996f, 16124);
				Jeune18 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2669.580078f, -3428.860107f, 268.645996f, 16124);

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
			
				Jeune16->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune17->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune18->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());				
				break;
			}
			
			case 150:
			{
				Jeune19 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2714.560059f, -3430.610107f, 268.645996f, 1.413720f, true, false, 0, 0);
				Jeune20 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2692.209961f, -3428.780029f, 268.645996f, 1.483530f, true, false, 0, 0);
				Jeune21 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2669.580078f, -3428.860107f, 268.645996f, 1.378810f, true, false, 0, 0);
				Jeune19 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2714.560059f, -3430.610107f, 268.645996f, 16124);
				Jeune20 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2692.209961f, -3428.780029f, 268.645996f, 16124);
				Jeune21 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2669.580078f, -3428.860107f, 268.645996f, 16124);

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
			
				Jeune19->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune20->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune21->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());				
				break;
			}
			
			case 170:
			{
				Jeune22 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2714.560059f, -3430.610107f, 268.645996f, 1.413720f, true, false, 0, 0);
				Jeune23 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2692.209961f, -3428.780029f, 268.645996f, 1.483530f, true, false, 0, 0);
				Jeune24 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16124, 2669.580078f, -3428.860107f, 268.645996f, 1.378810f, true, false, 0, 0);
				Jeune22 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2714.560059f, -3430.610107f, 268.645996f, 16124);
				Jeune23 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2692.209961f, -3428.780029f, 268.645996f, 16124);
				Jeune24 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2669.580078f, -3428.860107f, 268.645996f, 16124);

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
			
				Jeune22->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune23->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Jeune24->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());				
				break;
			}
			
			case 190:
			{
				Chevalier1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16125, 2714.560059f, -3430.610107f, 268.645996f, 1.413720f, true, false, 0, 0);
				Chevalier2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16125, 2692.209961f, -3428.780029f, 268.645996f, 1.483530f, true, false, 0, 0);
				Chevalier3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16125, 2669.580078f, -3428.860107f, 268.645996f, 1.378810f, true, false, 0, 0);
				Chevalier1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2714.560059f, -3430.610107f, 268.645996f, 16125);
				Chevalier2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2692.209961f, -3428.780029f, 268.645996f, 16125);
				Chevalier3 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2669.580078f, -3428.860107f, 268.645996f, 16125);

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
			
				Chevalier1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Chevalier2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Chevalier3->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());				
				break;
			}
			
			case 210:
			{
				Chevalier4 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16125, 2714.560059f, -3430.610107f, 268.645996f, 1.413720f, true, false, 0, 0);
				Chevalier5 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16125, 2692.209961f, -3428.780029f, 268.645996f, 1.483530f, true, false, 0, 0);
				Chevalier6 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16125, 2669.580078f, -3428.860107f, 268.645996f, 1.378810f, true, false, 0, 0);
				Chevalier4 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2714.560059f, -3430.610107f, 268.645996f, 16125);
				Chevalier5 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2692.209961f, -3428.780029f, 268.645996f, 16125);
				Chevalier6 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2669.580078f, -3428.860107f, 268.645996f, 16125);

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
			
				Chevalier4->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Chevalier5->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Chevalier6->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());				
				break;
			}
			
			case 230:
			{
				Cavalier1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16126, 2714.560059f, -3430.610107f, 268.645996f, 1.413720f, true, false, 0, 0);
				Chevalier7 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16125, 2692.209961f, -3428.780029f, 268.645996f, 1.483530f, true, false, 0, 0);
				Cavalier2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16126, 2669.580078f, -3428.860107f, 268.645996f, 1.378810f, true, false, 0, 0);
				Cavalier1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2714.560059f, -3430.610107f, 268.645996f, 16126);
				Chevalier7 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2692.209961f, -3428.780029f, 268.645996f, 16125);
				Cavalier2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2669.580078f, -3428.860107f, 268.645996f, 16126);

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
			
				Cavalier1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Chevalier7->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Cavalier2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());				
				break;
			}
			
			case 240:
			{
				Cavalier3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16126, 2714.560059f, -3430.610107f, 268.645996f, 1.413720f, true, false, 0, 0);
				Cavalier4 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16126, 2669.580078f, -3428.860107f, 268.645996f, 1.378810f, true, false, 0, 0);
				Cavalier3 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2714.560059f, -3430.610107f, 268.645996f, 16126);
				Cavalier4 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2669.580078f, -3428.860107f, 268.645996f, 16126);

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
			
				Cavalier3->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Cavalier4->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());	
				break;
			}
			
			case 274:
			{
				_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
				_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
				Phase = 1;
				Decompte_Teleportation = 30;
				Fin_Invocation = true;
				Zone_vivant = true;
				Zone_mort_vivant = false;
				Decompte_Teleportation = 0;
				break;
			}
		}
		
		if(Lancement_Event)
		{
			Lancement_Invocation++;
		}
	}
	
	void Combat()
	{
		if(_unit->GetHealthPct() >= 30 && Decompte_Teleportation < 1)
		{
			if(Zone_mort_vivant)
			{
				_unit->m_invisible = true;
				_unit->SetPosition(2692.149170f, -3398.077148f, 267.684753f, 0.037733f, false);
				_unit->m_invisible = false;
				Zone_mort_vivant = false;
				Zone_vivant = true;
				Decompte_Teleportation = 30;
			}
			else if(Zone_vivant)
			{
				_unit->m_invisible = true;
				_unit->SetPosition(2700.270020f, -3322.350098f, 267.768005f, 3.525560f, true);
				_unit->m_invisible = false;
				Zone_vivant = false;
				Zone_mort_vivant = true;
				Decompte_Teleportation = 30;
			}
		}
		else if(_unit->GetHealthPct() >= 30)
		{
			Decompte_Teleportation--;
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
		bool Lancement_Event, Fin_Invocation, Zone_mort_vivant, Zone_vivant, Entre_en_Combat;
		int nrspells;
		uint32 Lancement_Invocation, Phase, Decompte_Teleportation;
		Unit * Jeune1, * Jeune2, * Jeune3, * Jeune4, * Jeune5, * Jeune6, * Jeune7, * Jeune8, * Jeune9, * Jeune10, * Jeune11, * Jeune12;
		Unit * Jeune13, * Jeune14, * Jeune15, * Jeune16, * Jeune17, * Jeune18, * Jeune19, * Jeune20, * Jeune21, * Jeune22, * Jeune23, * Jeune24;
		Unit * Chevalier1, * Chevalier2, * Chevalier3, * Chevalier4, * Chevalier5, * Chevalier6, * Chevalier7;
		Unit * Cavalier1, * Cavalier2, * Cavalier3, * Cavalier4;
};

// Boss
#define Feugen					15930
// Sort
#define Champ_statique			28135
#define Champ_statique_Heroic	54528
#define Attraction_magnétique	41959

bool Feugen_mort;
bool Stalagg_mort;
Unit * Cadavre_Feugen;
Unit * Cadavre_Stalagg;

class FeugenAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(FeugenAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    FeugenAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Champ_statique);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Champ_statique);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		Feugen_mort = false;
		Résurrection = 5;
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Feugen_mort = false;
		Résurrection = 5;
		
		RegisterAIUpdateEvent(1000);
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
		Feugen_mort = true;
		Cadavre_Feugen = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 15930);
    }
	
	void AIUpdate()
	{
		if(Stalagg_mort)
		{
			if(Résurrection < 1)
			{
				Cadavre_Stalagg->setDeathState(ALIVE);
				Cadavre_Stalagg->SetHealthPct(100);
				Stalagg_mort = false;
				Résurrection = 5;
			}
			else
			{
				Résurrection--;
			}
		}
		
		/*if()
		{
		
		}*/
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
		uint32 Résurrection;
};

// Boss
#define Grande_veuve_Faerlina				15953
// Sort
#define Salve_d_éclairs_de_poison			28796
#define Salve_d_éclairs_de_poison_Heroic	54098
#define Pluie_de_feu						39024
#define Pluie_de_feu_heroic					58936
#define Frénésie							28798				
#define Frénésie_Heroic						54100

class Grande_veuve_FaerlinaAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Grande_veuve_FaerlinaAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Grande_veuve_FaerlinaAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Salve_d_éclairs_de_poison);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 35.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Salve_d_éclairs_de_poison_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 35.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Pluie_de_feu);
			spells[1].targettype = TARGET_RANDOM_DESTINATION;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 40.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Pluie_de_feu_heroic);
			spells[1].targettype = TARGET_RANDOM_DESTINATION;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 40.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Frénésie);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = -1;
			spells[2].perctrigger = 0.0f;
			spells[2].attackstoptimer = 1000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Frénésie_Heroic);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = -1;
			spells[2].perctrigger = 0.0f;
			spells[2].attackstoptimer = 1000;
		}
		
		Temps_Frénésie = 70;
		Mort_Adorateur = 0;
		Phase = 0;
		
		Mort_Adorateur1 = false;
		Mort_Adorateur2 = false;
		Mort_Adorateur3 = false;
		Mort_Adorateur4 = false;
		Lancement_Event = false;
				
		RegisterAIUpdateEvent(1000);
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Temps_Frénésie = 70;
		Mort_Adorateur = 0;
		Phase = 1;
		
		Lancement_Event = true;
		Mort_Adorateur1 = false;
		Mort_Adorateur2 = false;
		Mort_Adorateur3 = false;
		Mort_Adorateur4 = false;

		RegisterAIUpdateEvent(1000);
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8794);
		_unit->PlaySoundToSet(8794);
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			Adorateur1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3350.260010f, -3619.110107f, 261.079987f, 4.677480f, true, false, 0, 0);
			Adorateur2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3356.709961f, -3620.050049f, 261.079987f, 4.572760f, true, false, 0, 0);
			Adorateur3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3346.330078f, -3617.489990f, 260.997223f, 4.799650f, true, false, 0, 0);
			Adorateur4 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3360.750000f, -3619.699922f, 261.079987f, 4.433140f, true, false, 0, 0);
		}
		else
		{
			Adorateur1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3350.260010f, -3619.110107f, 261.079987f, 4.677480f, true, false, 0, 0);
			Adorateur2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3356.709961f, -3620.050049f, 261.079987f, 4.572760f, true, false, 0, 0);
			Adorateur3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3346.330078f, -3617.489990f, 260.997223f, 4.799650f, true, false, 0, 0);
			Adorateur4 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3360.750000f, -3619.699922f, 261.079987f, 4.433140f, true, false, 0, 0);
			Suivant1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16505, 3342.44951f, -3618.659912f, 261.079987f, 5.183630f, true, false, 0, 0);
			Suivant1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16505, 3364.00000f, -3622.050049f, 261.079010f, 4.572760f, true, false, 0, 0);					
		}
			
		Adorateur1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3350.260010f, -3619.110107f, 261.079987f, 16506);
		Adorateur2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3356.709961f, -3620.050049f, 261.079987f, 16506);
		Adorateur3 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3346.330078f, -3617.489990f, 260.997223f, 16506);
		Adorateur4 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3360.750000f, -3619.699922f, 261.079987f, 16506);
		
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
			
		Adorateur1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
		Adorateur2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
		Adorateur3->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
		Adorateur4->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
	}
	
	void OnTargetDied(Unit * mTarget)
    {
		int RandomSpeach = RandomUInt(1);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8800);
				_unit->PlaySoundToSet(8800);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8801);
				_unit->PlaySoundToSet(8801);
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
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8798);
		_unit->PlaySoundToSet(8798);
		RemoveAIUpdateEvent();
		
		GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(3121.47f, -3791.07f, 273.915f, 194022);		


	    if(pDoor == 0)
            return;

        //Ouvre la porte
		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 0);

		TO_CREATURE(Adorateur1)->CombatStatus.OnRemoveFromWorld();
		TO_CREATURE(Adorateur2)->CombatStatus.OnRemoveFromWorld();
		TO_CREATURE(Adorateur3)->CombatStatus.OnRemoveFromWorld();
		TO_CREATURE(Adorateur4)->CombatStatus.OnRemoveFromWorld();
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
		}
	}
	
	void Intro()
	{
		for(std::set<Player*>::iterator Detection = _unit->GetInRangePlayerSetBegin(); Detection != _unit->GetInRangePlayerSetEnd(); Detection++)
		{
			if((*Detection)->GetTypeId() == TYPEID_PLAYER)
			{
				if(_unit->CalcDistance(*Detection) <= 95.0f)
				{
					_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8799);
					_unit->PlaySoundToSet(8799);
					Phase = 1;
				}
			}
		}
	}
	
	void Combat()
	{
		if(Lancement_Event)
		{
			if(Temps_Frénésie < 1)
			{
				_unit->CastSpell(_unit, spells[2].info, spells[2].instant);
					
				int RandomSpeach = RandomUInt(2);
				switch (RandomSpeach)
				{
					case 0:
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8795);
						_unit->PlaySoundToSet(8795);
						Temps_Frénésie = 70;
						break;
						
					case 1:
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8796);
						_unit->PlaySoundToSet(8796);
						Temps_Frénésie = 70;
						break;
						
					case 2:
						_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8797);
						_unit->PlaySoundToSet(8797);
						Temps_Frénésie = 70;
						break;
				}			
			}
			else
			{
				Temps_Frénésie--;
			}
				
			if ((Adorateur1 != NULL && !Adorateur1->isAlive() && !Mort_Adorateur1))
			{
				_unit->RemoveAura(Frénésie);
				Mort_Adorateur1 = true;
				Mort_Adorateur++;
			}
					
			if ((Adorateur2 != NULL && !Adorateur2->isAlive() && !Mort_Adorateur2))
			{
				_unit->RemoveAura(Frénésie);
				Mort_Adorateur2 = true;
				Mort_Adorateur++;
			}
					
			if ((Adorateur3 != NULL && !Adorateur3->isAlive() && !Mort_Adorateur3))
			{
				_unit->RemoveAura(Frénésie);
				Mort_Adorateur3 = true;
				Mort_Adorateur++;
			}
					
			if ((Adorateur4 != NULL && !Adorateur4->isAlive() && !Mort_Adorateur4))
			{
				_unit->RemoveAura(Frénésie);
				Mort_Adorateur4 = true;
				Mort_Adorateur++;
			}
			
			if (Mort_Adorateur == 4)
			{
				Mort_Adorateur = 0;
				Mort_Adorateur1 = false;
				Mort_Adorateur2 = false;
				Mort_Adorateur3 = false;
				Mort_Adorateur4 = false;
				
				if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
				{
					Adorateur1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3350.260010f, -3619.110107f, 261.079987f, 4.677480f, true, false, 0, 0);
					Adorateur2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3356.709961f, -3620.050049f, 261.079987f, 4.572760f, true, false, 0, 0);
					Adorateur3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3346.330078f, -3617.489990f, 260.997223f, 4.799650f, true, false, 0, 0);
					Adorateur4 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3360.750000f, -3619.699922f, 261.079987f, 4.433140f, true, false, 0, 0);
				}
				else
				{
					Adorateur1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3350.260010f, -3619.110107f, 261.079987f, 4.677480f, true, false, 0, 0);
					Adorateur2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3356.709961f, -3620.050049f, 261.079987f, 4.572760f, true, false, 0, 0);
					Adorateur3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3346.330078f, -3617.489990f, 260.997223f, 4.799650f, true, false, 0, 0);
					Adorateur4 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16506, 3360.750000f, -3619.699922f, 261.079987f, 4.433140f, true, false, 0, 0);
					Suivant1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16505, 3342.44951f, -3618.659912f, 261.079987f, 5.183630f, true, false, 0, 0);
					Suivant1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16505, 3364.00000f, -3622.050049f, 261.079010f, 4.572760f, true, false, 0, 0);					
				}
					
				Adorateur1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3350.260010f, -3619.110107f, 261.079987f, 16506);
				Adorateur2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3356.709961f, -3620.050049f, 261.079987f, 16506);
				Adorateur3 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3346.330078f, -3617.489990f, 260.997223f, 16506);
				Adorateur4 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3360.750000f, -3619.699922f, 261.079987f, 16506);
				
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
					
				Adorateur1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Adorateur2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Adorateur3->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
				Adorateur4->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			}
				
			float val = (float)RandomFloat(100.0f);
			SpellCast(val);
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
		bool Mort_Adorateur1, Mort_Adorateur2, Mort_Adorateur3, Mort_Adorateur4, Lancement_Event;
		int nrspells, Mort_Adorateur;
		uint32 Temps_Frénésie, Phase;
		Unit * Adorateur1, * Adorateur2, * Adorateur3, * Adorateur4, * Suivant1, * Suivant2;
};

// Boss
#define Grobbulus					15931
// Sort
#define Nuage_empoisonné			28240
#define Injection_mutante			28169
#define Projection_de_gelée			28157
#define Projection_de_gelée_Heroic	54364
#define Berserk_GS					26662
#define Explosion_mutagène			28206

class GrobbulusAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(GrobbulusAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    GrobbulusAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Nuage_empoisonné);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(Injection_mutante);
		spells[1].targettype = TARGET_RANDOM_SINGLE;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 50.0f;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Projection_de_gelée);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 35;
			spells[2].perctrigger = 20.0f;
			spells[2].attackstoptimer = 1000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Projection_de_gelée_Heroic);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 35;
			spells[2].perctrigger = 20.0f;
			spells[2].attackstoptimer = 1000;
		}
		
		spells[3].info = dbcSpell.LookupEntry(Berserk_GS);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 0.0f;
		spells[3].attackstoptimer = 1000;
		
		Decompte_Combat = 0;
		Enrage = false;
		Aura_Injection_mutante = NULL;
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Decompte_Combat = 0;
		Temps_Injection_mutante = 20;
		Enrage = false;
			
		RegisterAIUpdateEvent(1000);
    }

    void OnCombatStop(Unit * mTarget)
    {
		_unit->RemoveAura(Berserk_GS);
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
		if(!Enrage && Decompte_Combat >= 600)
		{
			_unit->CastSpell(_unit, spells[3].info, spells[3].instant);
			Enrage = true;
		}
		else if(!Enrage)
		{
			Decompte_Combat++;
		}
		
		if(Temps_Injection_mutante < 1)
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

			Temps_Injection_mutante = 35;
			_unit->CastSpell(RTarget, spells[1].info, spells[1].instant);
			Aura_Injection_mutante = RTarget;
		}
		else
		{
			Temps_Injection_mutante--;
		}
		
		if(Aura_Injection_mutante)
		{
			if(!Aura_Injection_mutante->FindAura(Injection_mutante))
			{
				_unit->CastSpell(Aura_Injection_mutante, Explosion_mutagène, true);
				_unit->GetMapMgr()->GetInterface()->SpawnCreature(16363, Aura_Injection_mutante->GetPositionX(), Aura_Injection_mutante->GetPositionY(), Aura_Injection_mutante->GetPositionZ(), Aura_Injection_mutante->GetOrientation(), true, false, 0, 0);
				Aura_Injection_mutante = NULL;
			}
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
		bool Enrage;
		int nrspells;
		uint32 Decompte_Combat, Temps_Injection_mutante;
		Unit * Aura_Injection_mutante;
};

// Boss
#define Horreb							16011
// Sort
#define Aura_nécrotique 				55593
#define Mortelle_floraison				29865
#define Mortelle_floraison_Heroic		55053
#define Malédiction_inévitable			29204
#define Malédiction_inévitable_Heroic	55052
#define Berserk_HB						26662

class HorrebAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(HorrebAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    HorrebAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Aura_nécrotique);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 45;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 1000;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Mortelle_floraison);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Mortelle_floraison_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Malédiction_inévitable);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 30;
			spells[2].perctrigger = 30.0f;
			spells[2].attackstoptimer = 1000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Malédiction_inévitable_Heroic);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 30;
			spells[2].perctrigger = 30.0f;
			spells[2].attackstoptimer = 1000;
		}
		
		spells[3].info = dbcSpell.LookupEntry(Berserk_HB);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 0.0f;
		spells[3].attackstoptimer = 1000;
		
		Phase = 0;
		Temps_Aura_nécrotique = 15;
		Temps_Invocation_de_spore = 30;
		Temps_Mortelle_floraison = 65;
		Temps_Malédiction_inévitable = 120;
		Passage_Combat = 0;
		Decompte_Combat = 0;
		Verif_nécro = false;
		Verif_Mortel = false;
		Verif_Malédic = false;
		Enrage = false;
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Phase = 0;
		Temps_Aura_nécrotique = 15;
		Temps_Invocation_de_spore = 30;
		Temps_Mortelle_floraison = 65;
		Temps_Malédiction_inévitable = 120;
		Passage_Combat = 0;
		Decompte_Combat = 0;
		Verif_nécro = false;
		Verif_Mortel = false;
		Verif_Malédic = false;
		Enrage = false;
			
		RegisterAIUpdateEvent(1000);
		
		GameObject * pdoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2909.41f, -3947.02f, 273.925f, 181496);
		
		if (pdoor && (pdoor->GetUInt32Value(GAMEOBJECT_BYTES_1) == 0))
		{
			//Ferme la porte
			pdoor->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		}
    }

    void OnCombatStop(Unit * mTarget)
    {
		_unit->RemoveAura(Berserk_HB);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
        RemoveAIUpdateEvent();
		
		GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2909.41f, -3947.02f, 273.925f, 181496);
		
		if(pDoor == 0)
			return;

        //Ouvre la porte
		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		
		GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2909.41f, -3947.02f, 273.925f, 181496);
		
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
				Préparation_Combat();
				break;
			case 1:
				Combat();
				break;
		}
	}
	
	void Préparation_Combat()
	{
		if(!Verif_nécro && Temps_Aura_nécrotique < 1)
		{
			_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
			Verif_nécro = true;
			Passage_Combat++;
		}
		else if(!Verif_nécro)
		{
			Temps_Aura_nécrotique--;
		}
		
		if(_unit->FindAura(29232))
		{
			_unit->RemoveAura(29232);
		}
		
		if(Temps_Invocation_de_spore < 1)
		{
			int RandomSpeach = RandomUInt(3);
			switch (RandomSpeach)
			{
				case 0:
				{
					Spore = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16286, 2879.759521f, -4026.776855f, 273.681183f, 6.242718f, true, false, 0, 0);
					Spore = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2879.759521f, -4026.776855f, 273.681183f, 16286);
						
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
			
					Spore->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
					Temps_Invocation_de_spore = 30;
					break;
				}
				
				case 1:
				{
				
					Spore = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16286, 2939.435791f, -4026.770996f, 273.584198f, 3.115263f, true, false, 0, 0);
					Spore = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2939.435791f, -4026.770996f, 273.584198f, 16286);
						
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
			
					Spore->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
					Temps_Invocation_de_spore = 30;
					break;
				}
				
				case 2:
				{
				
					Spore = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16286, 2939.397705f, -3968.795166f, 273.593048f, 3.180451f, true, false, 0, 0);
					Spore = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2939.397705f, -3968.795166f, 273.593048f, 16286);
						
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
			
					Spore->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
					Temps_Invocation_de_spore = 30;
					break;
				}
				
				case 3:
				{
				
					Spore = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16286, 2879.636475f, -3968.848877f, 273.633667f, 0.021580f, true, false, 0, 0);
					Spore = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2879.636475f, -3968.848877f, 273.633667f, 16286);
						
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
			
					Spore->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
					Temps_Invocation_de_spore = 30;
					break;
				}
			}
		}
		else
		{
			Temps_Invocation_de_spore--;
		}
		
		if(!Verif_Mortel && Temps_Mortelle_floraison < 1)
		{
			_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
			Verif_Mortel = true;
			Passage_Combat++;
		}
		else if(!Verif_Mortel)
		{
			Temps_Mortelle_floraison--;
		}
		
		if(!Verif_Malédic && Temps_Malédiction_inévitable < 1)
		{
			_unit->CastSpell(_unit, spells[2].info, spells[2].instant);
			Verif_Malédic = true;
			Passage_Combat++;
		}
		else if(!Verif_Malédic)
		{
			Temps_Malédiction_inévitable--;
		}

		if(Passage_Combat == 3)
		{
			Phase = 1;
		}
	}
	
	void Combat()
	{
		if(!Enrage && Decompte_Combat >= 600)
		{
			_unit->CastSpell(_unit, spells[3].info, spells[3].instant);
			Enrage = true;
		}
		else if(!Enrage)
		{
			Decompte_Combat++;
		}

		if(_unit->FindAura(29232))
		{
			_unit->RemoveAura(29232);
		}
		
		if(Temps_Invocation_de_spore < 1)
		{
			int RandomSpeach = RandomUInt(3);
			switch (RandomSpeach)
			{
				case 0:
				{
					Spore = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16286, 2879.759521f, -4026.776855f, 273.681183f, 6.242718f, true, false, 0, 0);
					Spore = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2879.759521f, -4026.776855f, 273.681183f, 16286);
						
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
			
					Spore->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
					Temps_Invocation_de_spore = 30;
					break;
				}
				
				case 1:
				{
				
					Spore = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16286, 2939.435791f, -4026.770996f, 273.584198f, 3.115263f, true, false, 0, 0);
					Spore = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2939.435791f, -4026.770996f, 273.584198f, 16286);
						
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
			
					Spore->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
					Temps_Invocation_de_spore = 30;
					break;
				}
				
				case 2:
				{
				
					Spore = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16286, 2939.397705f, -3968.795166f, 273.593048f, 3.180451f, true, false, 0, 0);
					Spore = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2939.397705f, -3968.795166f, 273.593048f, 16286);
						
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
			
					Spore->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
					Temps_Invocation_de_spore = 30;
					break;
				}
				
				case 3:
				{
				
					Spore = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16286, 2879.636475f, -3968.848877f, 273.633667f, 0.021580f, true, false, 0, 0);
					Spore = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2879.636475f, -3968.848877f, 273.633667f, 16286);
						
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
			
					Spore->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
					Temps_Invocation_de_spore = 30;
					break;
				}
			}
		}
		else
		{
			Temps_Invocation_de_spore--;
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
					
					if (spells[i].speech != NULL)
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
		bool Verif_nécro, Verif_Mortel, Verif_Malédic, Enrage;
		int nrspells, Passage_Combat;
		uint32 Decompte_Combat,	Temps_Aura_nécrotique, Temps_Invocation_de_spore, Temps_Mortelle_floraison, Temps_Malédiction_inévitable, Phase;
		Unit * Spore;
};

// Boss
#define Instructeur_Razuvious		16061
// Sort
#define Frappe_déséquilibrante		55470
#define Couteau_dentelé				55550
#define Cri_perturbant				55543

class Instructeur_RazuviousAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Instructeur_RazuviousAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Instructeur_RazuviousAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Frappe_déséquilibrante);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 35;
		spells[0].perctrigger = 15.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(Couteau_dentelé);
		spells[1].targettype = TARGET_RANDOM_SINGLE;
		spells[1].instant = false;
		spells[1].cooldown = 10;
		spells[1].perctrigger = 25.0f;
		spells[1].attackstoptimer = 1000;
		spells[1].mindist2cast = 5.0f;
		spells[1].maxdist2cast = 45.0f;
		
		spells[2].info = dbcSpell.LookupEntry(Cri_perturbant);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = 15;
		spells[2].perctrigger = 35.0f;
		spells[2].attackstoptimer = 1000;
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		RegisterAIUpdateEvent(1000);
		
		int RandomSpeach = RandomUInt(3);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8852);
				_unit->PlaySoundToSet(8852);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8786);
				_unit->PlaySoundToSet(8786);
				break;
				
			case 2:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8787);
				_unit->PlaySoundToSet(8787);
				break;
				
			case 3:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8787);
				_unit->PlaySoundToSet(8787);
				break;
		}
    }

	void OnTargetDied(Unit * mTarget)
    {
		int RandomSpeach = RandomUInt(4);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8785);
				_unit->PlaySoundToSet(8785);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8786);
				_unit->PlaySoundToSet(8786);
				break;
				
			case 2:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8787);
				_unit->PlaySoundToSet(8787);
				break;
				
			case 3:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8787);
				_unit->PlaySoundToSet(8787);
				break;
				
			case 4:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8787);
				_unit->PlaySoundToSet(8787);
				break;
		}
	}

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		_unit->RemoveAura(Berserk);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8787);
		_unit->PlaySoundToSet(8787);
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
#define Kel_Thuzad						15990
// Sort
#define Eclair_de_givre_simple			28478
#define Eclair_de_givre_Heroic_simple	55802
#define Eclair_de_givre_volée			28479
#define Eclair_de_givre_volée_Heroic	62580
#define Faire_détoner_mana				27819
#define Trait_de_givre					27808

static Coordonnée Soldat[] =
{
	{ 3759.149902f, -5074.879883f, 143.175003f, 1.203640f },
	{ 3762.959961f, -5067.399902f, 143.453003f, 0.893413f },
	{ 3772.419922f, -5076.379883f, 143.466995f, 3.606970f },
	{ 3779.699951f, -5078.180176f, 143.764008f, 4.038940f },
	{ 3770.219971f, -5065.740234f, 143.477005f, 0.630304f },
	{ 3765.709961f, -5060.799805f, 143.748001f, 1.608120f },
	{ 3776.909912f, -5066.100098f, 143.550003f, 5.130640f },
	{ 3782.659912f, -5069.529785f, 143.757004f, 5.150280f },
	{ 3773.909912f, -5059.589844f, 143.774002f, 6.257680f },
	{ 3780.260010f, -5061.580078f, 143.742996f, 5.169910f },
	{ 3721.429932f, -5052.759766f, 143.442993f, 1.457330f },
	{ 3732.149902f, -5051.589844f, 143.444000f, 1.017500f },
	{ 3741.889893f, -5047.439941f, 143.886002f, 3.075250f },
	{ 3726.229980f, -5043.410156f, 143.455994f, 6.150070f },
	{ 3718.679932f, -5042.520020f, 143.768005f, 1.614410f },
	{ 3733.060059f, -5040.979980f, 143.557007f, 1.669380f },
	{ 3741.860107f, -5038.410156f, 143.917999f, 4.410420f },
	{ 3736.189941f, -5032.810059f, 143.847000f, 5.026970f },
	{ 3723.219971f, -5035.770020f, 143.764999f, 4.701020f },
	{ 3728.760010f, -5031.759766f, 143.785995f, 3.723200f },
	{ 3683.189941f, -5062.419922f, 143.175995f, 0.559623f },
	{ 3687.739990f, -5057.779785f, 143.175995f, 1.345020f },
	{ 3674.040039f, -5067.899902f, 143.524994f, 0.005909f },
	{ 3688.340088f, -5052.009766f, 143.473007f, 2.299280f },
	{ 3681.659912f, -5052.549805f, 143.263000f, 3.343860f },
	{ 3678.840080f, -5055.529785f, 143.332993f, 3.512720f },
	{ 3685.800049f, -5045.779785f, 143.615997f, 6.253750f },
	{ 3673.479980f, -5053.350098f, 143.554993f, 1.945840f },
	{ 3670.649902f, -5061.149902f, 143.820007f, 4.266700f },
	{ 3688.018311f, -5061.541992f, 143.178223f, 0.512497f },
	{ 3742.659912f, -5157.009766f, 143.171005f, 0.773261f },
	{ 3750.310059f, -5153.779785f, 143.179993f, 5.603460f },
	{ 3739.770020f, -5163.000000f, 143.662994f, 1.095270f },
	{ 3746.649902f, -5164.560059f, 143.520004f, 1.970990f },
	{ 3748.479980f, -5169.109863f, 143.649002f, 2.591460f },
	{ 3744.560059f, -5173.520020f, 143.895996f, 1.370160f },
	{ 3758.260010f, -5156.299805f, 143.570999f, 6.192510f },
	{ 3762.620117f, -5159.149902f, 143.712997f, 4.433220f },
	{ 3760.840088f, -5162.959961f, 143.649002f, 4.280060f },
	{ 3756.580078f, -5170.060059f, 143.623001f, 3.031280f },
	{ 3705.229980f, -5163.189941f, 143.266998f, 5.692200f },
	{ 3696.949951f, -5163.370117f, 143.608002f, 0.901274f },
	{ 3710.080078f, -5168.709961f, 143.585999f, 4.675110f },
	{ 3697.030029f, -5170.220215f, 143.606003f, 0.343642f },
	{ 3692.030029f, -5170.020020f, 143.815994f, 0.932691f },
	{ 3710.320068f, -5175.319824f, 143.705002f, 4.639770f },
	{ 3694.550049f, -5177.540039f, 143.839005f, 1.549230f },
	{ 3705.830078f, -5179.120117f, 143.729996f, 3.956480f },
	{ 3712.800049f, -5179.109863f, 143.891006f, 3.855950f },
	{ 3701.669922f, -5181.859863f, 143.804001f, 1.380370f },
	{ 3676.590088f, -5144.899902f, 143.186005f, 3.575550f },
	{ 3670.649902f, -5142.629883f, 143.173996f, 4.313820f },
	{ 3665.689941f, -5136.279785f, 143.177994f, 1.176150f },
	{ 3664.870117f, -5132.330078f, 143.205002f, 3.249600f },
	{ 3662.120117f, -5144.299805f, 143.320007f, 2.256080f },
	{ 3658.979980f, -5139.490234f, 143.421997f, 6.077040f },
	{ 3651.850098f, -5137.140137f, 143.764999f, 0.799161f },
	{ 3654.689941f, -5144.009766f, 143.546997f, 2.519180f },
	{ 3666.020020f, -5149.500000f, 143.587006f, 3.359560f },
	{ 3667.959961f, -5153.120117f, 143.791000f, 4.015380f },
	{ 3659.979980f, -5100.450195f, 143.453003f, 5.168254f },
	{ 3662.800049f, -5088.189941f, 143.557999f, 4.409650f },
	{ 3658.439941f, -5090.649902f, 143.470001f, 5.528840f },
	{ 3652.810059f, -5090.450195f, 143.475998f, 1.362310f },
	{ 3651.780029f, -5095.339844f, 143.388000f, 0.981387f },
	{ 3652.629883f, -5098.970215f, 143.544998f, 2.799580f },
	{ 3652.679932f, -5083.479980f, 143.774994f, 0.482659f },
	{ 3647.189941f, -5085.490234f, 143.570999f, 1.919940f },
	{ 3645.120117f, -5097.240234f, 143.487000f, 0.765403f },
	{ 3646.360107f, -5101.200195f, 143.681000f, 2.909540f },
};

static Coordonnée Abomination[] =
{
	{ 3776.229980f, -5081.439941f, 143.779999f, 4.043730f },
	{ 3774.419922f, -5071.490234f, 143.423996f, 4.214940f },
	{ 3759.850098f, -5064.479980f, 143.636002f, 6.255410f },
	{ 3740.899902f, -5052.740234f, 143.785995f, 1.836760f },
	{ 3726.919922f, -5040.020020f, 143.535995f, 2.481570f },
	{ 3715.010010f, -5049.259766f, 143.632004f, 5.071810f },
	{ 3695.060059f, -5052.160156f, 143.548004f, 3.792400f },
	{ 3678.129883f, -5048.060059f, 143.436996f, 5.363980f },
	{ 3676.120117f, -5061.359863f, 143.492004f, 5.726840f },
	{ 3756.780029f, -5149.419922f, 143.460007f, 2.774530f },
	{ 3752.262695f, -5164.782227f, 143.409119f, 0.383768f },
	{ 3740.669922f, -5168.600098f, 143.873993f, 1.051360f },
	{ 3714.020020f, -5171.129883f, 143.776993f, 1.742510f },
	{ 3702.185303f, -5174.303711f, 143.532303f, 5.443298f },
	{ 3693.739990f, -5162.149902f, 143.748001f, 5.696990f },
	{ 3673.189941f, -5150.500000f, 143.751999f, 3.030570f },
	{ 3658.570068f, -5147.799805f, 143.494003f, 1.230440f },
	{ 3659.560059f, -5132.129883f, 143.677002f, 5.988380f },
	{ 3651.130859f, -5104.800293f, 143.798248f, 5.374194f },
	{ 3646.947021f, -5092.266113f, 143.305878f, 5.005841f },
	{ 3658.618408f, -5083.832031f, 143.778641f, 5.951464f },
};

static Coordonnée Tisseur[] =
{
	{ 3768.540039f, -5075.140137f, 143.203995f, 5.096160f },
	{ 3728.030029f, -5047.359863f, 143.306000f, 5.230460f },
	{ 3682.929932f, -5055.819824f, 143.184006f, 5.368690f },
	{ 3749.429932f, -5160.419922f, 143.283997f, 4.723090f },
	{ 3706.120117f, -5169.250000f, 143.436996f, 2.682630f },
	{ 3665.310059f, -5142.339844f, 143.220001f, 1.147180f },
	{ 3656.365234f, -5094.724121f, 143.306641f, 6.203571f },
};

static Coordonnée Gardien[] =
{
	{ 3778.371582f, -5065.141113f, 143.614639f, 3.700061f },
	{ 3731.733398f, -5032.681152f, 143.775040f, 4.485459f },
	{ 3758.592285f, -5170.157715f, 143.667297f, 2.144972f },
	{ 3700.936279f, -5183.230469f, 143.858582f, 1.314648f },
};

class Kel_ThuzadAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Kel_ThuzadAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    Kel_ThuzadAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Eclair_de_givre_simple);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;
			spells[0].speech = 8815;
			spells[0].soundid = 8815;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Eclair_de_givre_Heroic_simple);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;
			spells[0].speech = 8815;
			spells[0].soundid = 8815;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Eclair_de_givre_volée);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 35;
			spells[1].perctrigger = 18.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Eclair_de_givre_volée_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 35;
			spells[1].perctrigger = 18.0f;
			spells[1].attackstoptimer = 1000;
		}
		
		spells[2].info = dbcSpell.LookupEntry(Faire_détoner_mana);
		spells[2].targettype = TARGET_RANDOM_SINGLE;
		spells[2].instant = true;
		spells[2].cooldown = 30;
		spells[2].perctrigger = 10.0f;
		spells[2].attackstoptimer = 1000;
		spells[2].mindist2cast = 0.0f;
		spells[2].maxdist2cast = 45.0f;
		
		spells[3].info = dbcSpell.LookupEntry(Trait_de_givre);
		spells[3].targettype = TARGET_RANDOM_SINGLE;
		spells[3].instant = true;
		spells[3].cooldown = 45;
		spells[3].perctrigger = 13.0f;
		spells[3].attackstoptimer = 1000;
		spells[3].mindist2cast = 0.0f;
		spells[3].maxdist2cast = 45.0f;
		
		Phase = 0;
		Temps_Fissure = 15;
		Decompte_Event = 0;
		Temps_Invocation = 1;
		Invocation_Soldat = 0;
		Invocation_Tisseur = 0;
		Invocation_Abomination = 0;
		Lancement_event = false;
		Combat_lancer = false;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		
		RegisterAIUpdateEvent(1000);
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Combat_lancer = true;
			
		RegisterAIUpdateEvent(1000);
		
		int RandomSpeach = RandomUInt(3);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8809);
				_unit->PlaySoundToSet(8809);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8810);
				_unit->PlaySoundToSet(8810);
				break;
				
			case 2:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8811);
				_unit->PlaySoundToSet(8811);
				break;
		}
	}

	void OnCombatStop(Unit * mTarget)
    {
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
		_unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		RemoveAIUpdateEvent();

		if(Combat_lancer)
		{	
			Phase = 0;
			Temps_Fissure = 15;
			Decompte_Event = 0;
			Temps_Invocation = 1;
			Invocation_Soldat = 0;
			Invocation_Tisseur = 0;
			Invocation_Abomination = 0;
			Lancement_event = false;
			Combat_lancer = false;
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			RegisterAIUpdateEvent(1000);
		}
    }
	
	void OnTargetDied(Unit * mTarget)
	{
		int RandomSpeach = RandomUInt(3);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8817);
				_unit->PlaySoundToSet(8817);
				break;
				
			case 1:
				_unit->PlaySoundToSet(8818);
				break;
		}
	}

    void OnDied(Unit * mKiller)
    {
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8814);
		_unit->PlaySoundToSet(8814);
		RemoveAIUpdateEvent();
	}
	
	void AIUpdate()
	{
		switch (Phase)
		{
			case 0:
				Invocation();
				break;
			case 1:
				Combat();
				break;
		}
	}
	
	void Invocation()
	{
		if(!Lancement_event)
		{
			for(std::set<Player*>::iterator Detection = _unit->GetInRangePlayerSetBegin(); Detection != _unit->GetInRangePlayerSetEnd(); Detection++)
			{
				if((*Detection)->GetTypeId() == TYPEID_PLAYER)
				{
					if((*Detection)->isAlive())
					{
						if(_unit->CalcDistance(*Detection) <= 50.0f)
						{
							_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8819);
							_unit->PlaySoundToSet(8819);
							Lancement_event = true;
						}
					}
				}
			}
		}
		
		if(Lancement_event)
		{
			if(Decompte_Event < 290)
			{
				if(Temps_Invocation < 1)
				{
					if(Invocation_Soldat < 68 && Invocation_Abomination < 8 && Invocation_Tisseur < 4)
					{
						int RandomSpawn = RandomUInt(3);
						switch (RandomSpawn)
						{
							case 1:
							{
								for (int i = 0; i < 4; i++)
								{
									uint32 SpawnID = RandomUInt(71);
									Soldat1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16427, Soldat[SpawnID].x, Soldat[SpawnID].y, Soldat[SpawnID].z, Soldat[SpawnID].o, true, false, 0, 0);
									Soldat1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Soldat[SpawnID].x, Soldat[SpawnID].y, Soldat[SpawnID].z, 16427);
									
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
			
									Soldat1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
									Invocation_Soldat++;
								}
								Temps_Invocation = 10;
								break;
							}
							
							case 2:
							{
								uint32 SpawnID = RandomUInt(21);
								Abomination1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16428, Abomination[SpawnID].x, Abomination[SpawnID].y, Abomination[SpawnID].z, Abomination[SpawnID].o, true, false, 0, 0);
								Abomination1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Abomination[SpawnID].x, Abomination[SpawnID].y, Abomination[SpawnID].z, 16428);
									
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
			
								Abomination1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
								Invocation_Abomination++;
								Temps_Invocation = 10;
								break;
							}
							
							case 3:
							{
								uint32 SpawnID = RandomUInt(7);
								Tisseur1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16429, Tisseur[SpawnID].x, Tisseur[SpawnID].y, Tisseur[SpawnID].z, Tisseur[SpawnID].o, true, false, 0, 0);
								Tisseur1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Tisseur[SpawnID].x, Tisseur[SpawnID].y, Tisseur[SpawnID].z, 16429);
									
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
			
								Tisseur1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
								Invocation_Tisseur++;
								Temps_Invocation = 10;
								break;
							}
						}					
					}
					else if(Invocation_Soldat < 68 && Invocation_Abomination < 8 && Invocation_Tisseur == 4)
					{
						int RandomSpawn = RandomUInt(2);
						switch (RandomSpawn)
						{
							case 1:
							{
								for (int i = 0; i < 4; i++)
								{
									uint32 SpawnID = RandomUInt(71);
									Soldat1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16427, Soldat[SpawnID].x, Soldat[SpawnID].y, Soldat[SpawnID].z, Soldat[SpawnID].o, true, false, 0, 0);
									Soldat1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Soldat[SpawnID].x, Soldat[SpawnID].y, Soldat[SpawnID].z, 16427);
									
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
			
									Soldat1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
									Invocation_Soldat++;
								}
								Temps_Invocation = 10;
								break;
							}
							
							case 2:	
							{
								uint32 SpawnID = RandomUInt(21);
								Abomination1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16428, Abomination[SpawnID].x, Abomination[SpawnID].y, Abomination[SpawnID].z, Abomination[SpawnID].o, true, false, 0, 0);
								Abomination1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Abomination[SpawnID].x, Abomination[SpawnID].y, Abomination[SpawnID].z, 16428);
									
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
			
								Abomination1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
								Invocation_Abomination++;
								Temps_Invocation = 10;
								break;
							}
						}
					}
					else if(Invocation_Soldat < 68 && Invocation_Abomination == 8 && Invocation_Tisseur < 4)
					{
						int RandomSpawn = RandomUInt(2);
						switch (RandomSpawn)
						{
							case 1:
							{
								for (int i = 0; i < 4; i++)
								{
									uint32 SpawnID = RandomUInt(71);
									Soldat1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16427, Soldat[SpawnID].x, Soldat[SpawnID].y, Soldat[SpawnID].z, Soldat[SpawnID].o, true, false, 0, 0);
									Soldat1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Soldat[SpawnID].x, Soldat[SpawnID].y, Soldat[SpawnID].z, 16427);
									
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
			
									Soldat1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
									Invocation_Soldat++;
								}
								Temps_Invocation = 10;
								break;
							}
							
							case 2:
							{
								uint32 SpawnID = RandomUInt(7);
								Tisseur1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16429, Tisseur[SpawnID].x, Tisseur[SpawnID].y, Tisseur[SpawnID].z, Tisseur[SpawnID].o, true, false, 0, 0);
								Tisseur1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Tisseur[SpawnID].x, Tisseur[SpawnID].y, Tisseur[SpawnID].z, 16429);
									
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
			
								Tisseur1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
								Invocation_Tisseur++;
								Temps_Invocation = 10;
								break;
							}
						}
					}
					else if(Invocation_Soldat < 68 && Invocation_Abomination == 8 && Invocation_Tisseur == 4)
					{
						for (int i = 0; i < 4; i++)
						{
							uint32 SpawnID = RandomUInt(71);
							Soldat1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16427, Soldat[SpawnID].x, Soldat[SpawnID].y, Soldat[SpawnID].z, Soldat[SpawnID].o, true, false, 0, 0);
							Soldat1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Soldat[SpawnID].x, Soldat[SpawnID].y, Soldat[SpawnID].z, 16427);
									
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
			
							Soldat1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
							Invocation_Soldat++;
						}
						Temps_Invocation = 10;
					}
					else if(Invocation_Soldat == 68 && Invocation_Abomination < 8 && Invocation_Tisseur < 4)
					{
						int RandomSpawn = RandomUInt(2);
						switch (RandomSpawn)
						{
							case 1:
							{
								uint32 SpawnID = RandomUInt(21);
								Abomination1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16428, Abomination[SpawnID].x, Abomination[SpawnID].y, Abomination[SpawnID].z, Abomination[SpawnID].o, true, false, 0, 0);
								Abomination1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Abomination[SpawnID].x, Abomination[SpawnID].y, Abomination[SpawnID].z, 16428);
									
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
			
								Abomination1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
								Invocation_Abomination++;
								Temps_Invocation = 10;
								break;
							}
							
							case 2:
							{
								uint32 SpawnID = RandomUInt(7);
								Tisseur1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16429, Tisseur[SpawnID].x, Tisseur[SpawnID].y, Tisseur[SpawnID].z, Tisseur[SpawnID].o, true, false, 0, 0);
								Tisseur1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Tisseur[SpawnID].x, Tisseur[SpawnID].y, Tisseur[SpawnID].z, 16429);
									
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
			
								Tisseur1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
								Invocation_Tisseur++;
								Temps_Invocation = 10;
								break;
							}
						}
					}
					else if(Invocation_Soldat == 68 && Invocation_Abomination < 8 && Invocation_Tisseur == 4)
					{
						uint32 SpawnID = RandomUInt(21);
						Abomination1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16428, Abomination[SpawnID].x, Abomination[SpawnID].y, Abomination[SpawnID].z, Abomination[SpawnID].o, true, false, 0, 0);
						Abomination1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Abomination[SpawnID].x, Abomination[SpawnID].y, Abomination[SpawnID].z, 16428);
									
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
			
						Abomination1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
						Invocation_Abomination++;
						Temps_Invocation = 10;
					}
					else if(Invocation_Soldat == 68 && Invocation_Abomination == 8 && Invocation_Tisseur < 4)
					{
						uint32 SpawnID = RandomUInt(7);
						Tisseur1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16429, Tisseur[SpawnID].x, Tisseur[SpawnID].y, Tisseur[SpawnID].z, Tisseur[SpawnID].o, true, false, 0, 0);
						Tisseur1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Tisseur[SpawnID].x, Tisseur[SpawnID].y, Tisseur[SpawnID].z, 16429);
								
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
			
						Tisseur1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
						Invocation_Tisseur++;
						Temps_Invocation = 10;
					}
				}
				else
				{
					Temps_Invocation--;
				}
				Decompte_Event++;
			}
			else
			{
				_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
				_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
				
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
				Phase = 1;
			}
		}
	}
	
	void Combat()
	{
		if(_unit->GetHealthPct() <= 40 && !Dialogue)
		{
			switch (Temps_Dialogue)
			{
				case 2:
				{
					_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8816);
					_unit->PlaySoundToSet(8816);
					break;
				}
				
				case 3:
				{
					Roi_lich = _unit->GetMapMgr()->GetInterface()->SpawnCreature(30002, 3763.581543f, -5116.395020f, 144.375900f, 3.005702f, true, false, 0, 0);
					Roi_lich = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3763.581543f, -5116.395020f, 144.375900f, 30002);
				
					Roi_lich->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8824);
					Roi_lich->PlaySoundToSet(8824);
					break;
				}
				
				case 4:
				{
					if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
					{
						for (int i = 0; i < 2; i++)
						{
							uint32 SpawnID = RandomUInt(4);
							_unit->GetMapMgr()->GetInterface()->SpawnCreature(16441, Gardien[SpawnID].x, Gardien[SpawnID].y, Gardien[SpawnID].z, Gardien[SpawnID].o, true, false, 0, 0);
						}
					}
					else
					{
						for (int i = 0; i < 4; i++)
						{
							uint32 SpawnID = RandomUInt(4);
							_unit->GetMapMgr()->GetInterface()->SpawnCreature(16441, Gardien[SpawnID].x, Gardien[SpawnID].y, Gardien[SpawnID].z, Gardien[SpawnID].o, true, false, 0, 0);
						}
					}
					Dialogue = true;
					break;
				}
			}
			Temps_Dialogue++;
		}
		
		/*if(Temps_Fissure < 1)
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
				
			_unit->GetMapMgr()->GetInterface()->SpawnCreature(16129, RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation(), true, false, 0, 0);
			Temps_Fissure = 15;
		}
		else
		{
			Temps_Fissure--;
		}*/
	
		for(std::set<Player*>::iterator Detection_Trait_de_givre = _unit->GetInRangePlayerSetBegin(); Detection_Trait_de_givre != _unit->GetInRangePlayerSetEnd(); Detection_Trait_de_givre++)
		{
			if((*Detection_Trait_de_givre)->GetTypeId() == TYPEID_PLAYER)
			{
				if(_unit->CalcDistance(*Detection_Trait_de_givre) > 0.0f)
				{
					Aura_Trait_de_givre = (*Detection_Trait_de_givre);

					if(Aura_Trait_de_givre->FindAura(Trait_de_givre))
					{
						_unit->DealDamage(Aura_Trait_de_givre, Aura_Trait_de_givre->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * 0.26, 0, 0, 0, true);
					}
				}
			}
		}
		
		for(std::set<Player*>::iterator Detection_Detoner_Mana = _unit->GetInRangePlayerSetBegin(); Detection_Detoner_Mana != _unit->GetInRangePlayerSetEnd(); Detection_Detoner_Mana++)
		{
			if((*Detection_Detoner_Mana)->GetTypeId() == TYPEID_PLAYER)
			{
				if(_unit->CalcDistance(*Detection_Detoner_Mana) > 50.0f)
				{
					Aura_Detoner_Mana = (*Detection_Detoner_Mana);

					if(Aura_Detoner_Mana->FindAura(Faire_détoner_mana))
					{
						Aura_Detoner_Mana = Effet_Aura_Detoner_Mana;
						
						if(!Effet_Aura_Detoner_Mana->FindAura(Faire_détoner_mana))
						{
							_unit->Energize(Effet_Aura_Detoner_Mana, 0, -2000, POWER_TYPE_MANA);
							_unit->DealDamage(Effet_Aura_Detoner_Mana, Aura_Trait_de_givre->GetUInt32Value(UNIT_FIELD_POWER1) , 0, 0, 0, true);
						}
					}
				}
			}
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
		bool Lancement_event, Combat_lancer, Dialogue;
		int nrspells, Invocation_Soldat, Invocation_Tisseur, Invocation_Abomination;
		uint32 Phase, Decompte_Event, Temps_Invocation, Temps_Fissure, Temps_Dialogue;
		Unit * Aura_Trait_de_givre, * Aura_Detoner_Mana, * Effet_Aura_Detoner_Mana, * Roi_lich, * Soldat1, * Abomination1, * Tisseur1;
};

// Boss
#define Le_Recousu				16028
// Sort
#define Frappe_haineuse			41926
#define Frappe_haineuse_Heroic	59192
#define Frénésie_LR				28131
#define Berserk_LR				26662
#define Trait_de_gelée			32309

class Le_RecousuAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Le_RecousuAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    Le_RecousuAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Frappe_haineuse);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Frappe_haineuse_Heroic);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}

		spells[1].info = dbcSpell.LookupEntry(Frénésie_LR);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(Berserk_LR);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;
		
		spells[3].info = dbcSpell.LookupEntry(Trait_de_gelée);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 0.0f;
		spells[3].attackstoptimer = 1000;
		
		Decompte_Combat = 0;
		Temps_Trait = 15;
		Fren = false;
		Enrage = false;
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Decompte_Combat = 0;
		Temps_Trait = 15;
		Fren = false;
		Enrage = false;
			
		RegisterAIUpdateEvent(1000);
		
		int RandomSpeach = RandomUInt(1);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8909);
				_unit->PlaySoundToSet(8909);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8910);
				_unit->PlaySoundToSet(8910);
				break;
		}
    }

	void OnTargetDied(Unit * mTarget)
    {
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8912);
		_unit->PlaySoundToSet(8912);
	}

    void OnCombatStop(Unit * mTarget)
    {
		_unit->RemoveAura(Frénésie_LR);
		_unit->RemoveAura(Berserk_LR);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8911);
		_unit->PlaySoundToSet(8911);
		RemoveAIUpdateEvent();
    }
	
	void AIUpdate()
	{
		if(!Enrage && Decompte_Combat >= 360)
		{
			_unit->RemoveAura(Frénésie_LR);
			_unit->CastSpell(_unit, spells[2].info, spells[2].instant);
			Enrage = true;
		}
		else if(!Enrage)
		{
			Decompte_Combat++;
		}
		
		if(!Enrage)
		{
			if((_unit->GetHealthPct() <= 5) && !Fren)
			{
				_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
				Fren = true;
			}
		}
		
		if(Enrage && Temps_Trait < 1)
		{
			_unit->CastSpell(_unit, spells[3].info, spells[3].instant);
			Temps_Trait = 10;
		}
		else if(Enrage)
		{
			Temps_Trait--;
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
		bool Enrage, Fren;
		int nrspells;
		uint32 Decompte_Combat,	Temps_Trait;
};

// Boss
#define Maexxna 					15952
// Sort
#define Jet_de_toiles				29484
#define Jet_de_toiles_Heroic		54125
#define Horion_empoisonné			28741
#define Horion_empoisonné_heroic	54122
#define Poison_nécrotique			28776
#define Frénésie_MA					54123
#define Frénésie_Heroic_MA			54124

class MaexxnaAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(MaexxnaAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    MaexxnaAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Jet_de_toiles);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 40;
			spells[0].perctrigger = 35.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Jet_de_toiles_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 40;
			spells[0].perctrigger = 35.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Horion_empoisonné);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 22.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Horion_empoisonné_heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 22.0f;
			spells[1].attackstoptimer = 1000;
		}
		
		spells[2].info = dbcSpell.LookupEntry(Poison_nécrotique);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = 25;
		spells[2].perctrigger = 18.0f;
		spells[2].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[3].info = dbcSpell.LookupEntry(Frénésie_MA);
			spells[3].targettype = TARGET_SELF;
			spells[3].instant = true;
			spells[3].cooldown = -1;
			spells[3].perctrigger = 0.0f;
			spells[3].attackstoptimer = 1000;
		}
		else
		{
			spells[3].info = dbcSpell.LookupEntry(Frénésie_Heroic_MA);
			spells[3].targettype = TARGET_SELF;
			spells[3].instant = true;
			spells[3].cooldown = -1;
			spells[3].perctrigger = 0.0f;
			spells[3].attackstoptimer = 1000;
		}
		
		Enrage = false;
		Temps_Invocation = 30;
	}

	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Enrage = false;
			
		RegisterAIUpdateEvent(1000);
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
		if((_unit->GetHealthPct() <= 30) && !Enrage)
		{
			_unit->CastSpell(_unit, spells[3].info, spells[3].instant);
			Enrage = true;
		}
		
		if(Temps_Invocation < 1)
		{
			Jeune_araignée1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(17055, _unit->GetPositionX()+5, _unit->GetPositionY()+5, _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			Jeune_araignée2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(17055, _unit->GetPositionX()+4, _unit->GetPositionY()+4, _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			Jeune_araignée3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(17055, _unit->GetPositionX()+3, _unit->GetPositionY()+3, _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			Jeune_araignée4 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(17055, _unit->GetPositionX()+2, _unit->GetPositionY()+2, _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			Jeune_araignée5 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(17055, _unit->GetPositionX()+1, _unit->GetPositionY()+1, _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			Jeune_araignée6 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(17055, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			Jeune_araignée7 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(17055, _unit->GetPositionX()-1, _unit->GetPositionY()-1, _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			Jeune_araignée8 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(17055, _unit->GetPositionX()-2, _unit->GetPositionY()-2, _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			Jeune_araignée9 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(17055, _unit->GetPositionX()-3, _unit->GetPositionY()-3, _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			Jeune_araignée1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Jeune_araignée1->GetPositionX(), Jeune_araignée1->GetPositionY(), Jeune_araignée1->GetPositionZ(), 17055);
			Jeune_araignée2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Jeune_araignée2->GetPositionX(), Jeune_araignée2->GetPositionY(), Jeune_araignée2->GetPositionZ(), 17055);
			Jeune_araignée3 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Jeune_araignée3->GetPositionX(), Jeune_araignée3->GetPositionY(), Jeune_araignée3->GetPositionZ(), 17055);
			Jeune_araignée4 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Jeune_araignée4->GetPositionX(), Jeune_araignée4->GetPositionY(), Jeune_araignée4->GetPositionZ(), 17055);
			Jeune_araignée5 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Jeune_araignée5->GetPositionX(), Jeune_araignée5->GetPositionY(), Jeune_araignée5->GetPositionZ(), 17055);
			Jeune_araignée6 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Jeune_araignée6->GetPositionX(), Jeune_araignée6->GetPositionY(), Jeune_araignée6->GetPositionZ(), 17055);
			Jeune_araignée7 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Jeune_araignée7->GetPositionX(), Jeune_araignée7->GetPositionY(), Jeune_araignée7->GetPositionZ(), 17055);
			Jeune_araignée8 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Jeune_araignée8->GetPositionX(), Jeune_araignée8->GetPositionY(), Jeune_araignée8->GetPositionZ(), 17055);
			Jeune_araignée9 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(Jeune_araignée9->GetPositionX(), Jeune_araignée9->GetPositionY(), Jeune_araignée9->GetPositionZ(), 17055);
	
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
			
			Jeune_araignée1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Jeune_araignée2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Jeune_araignée3->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Jeune_araignée4->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Jeune_araignée5->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Jeune_araignée6->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Jeune_araignée7->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Jeune_araignée8->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Jeune_araignée9->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Temps_Invocation = 40;
		}
		else
		{
			Temps_Invocation--;
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
		bool Enrage;
		int nrspells;
		uint32 Temps_Invocation;
		Unit * Jeune_araignée1, * Jeune_araignée2, * Jeune_araignée3, * Jeune_araignée4, * Jeune_araignée5, * Jeune_araignée6, * Jeune_araignée7, * Jeune_araignée8, * Jeune_araignée9;
};

// Boss
#define Noth_le_Porte_peste					15954
// Sort
#define Malédiction_du_Porte_peste			29213
#define Malédiction_du_Porte_peste_Heroic	54835
#define Faiblesse							29212

class Noth_le_Porte_pesteAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Noth_le_Porte_pesteAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Noth_le_Porte_pesteAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Malédiction_du_Porte_peste);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Malédiction_du_Porte_peste_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Faiblesse);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 20;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 1000;

		Phase = 0;
		Passage_balcon = 110;
		Invocation_guerrier = 30;
		Invocation_mix = 15;
		Invocation_gardien = 30;
		Retour_terrestre = 25;
		Arriver_Balcon = false;
		Vague0 = false;
		Vague1 = false;
		Vague2 = false;
		Vague3 = false;
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Phase = 0;
		Passage_balcon = 110;
		Invocation_guerrier = 30;
		Invocation_mix = 15;
		Invocation_gardien = 30;
		Retour_terrestre = 25;
		Arriver_Balcon = false;
		Vague0 = false;
		Vague1 = false;
		Vague2 = false;
		Vague3 = false;
			
		RegisterAIUpdateEvent(1000);
		
		GameObject * pdoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2737.66f, -3489.72f, 262.095f, 181200);
		
		if (pdoor && (pdoor->GetUInt32Value(GAMEOBJECT_BYTES_1) == 0))
		{
			//Ferme la porte
			pdoor->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		}
		
		int RandomSpeach = RandomUInt(2);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8845);
				_unit->PlaySoundToSet(8845);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8846);
				_unit->PlaySoundToSet(8846);
				break;
				
			case 2:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8847);
				_unit->PlaySoundToSet(8847);
				break;
		}
    }

	void OnTargetDied(Unit * mTarget)
    {
		int RandomSpeach = RandomUInt(1);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8849);
				_unit->PlaySoundToSet(8849);
				break;
				
			case 1:
				_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8850);
				_unit->PlaySoundToSet(8850);
				break;
		}
	}

    void OnCombatStop(Unit * mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
        RemoveAIUpdateEvent();
		
		GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2737.66f, -3489.72f, 262.095f, 181200);
		
		if(pDoor == 0)
			return;

        //Ouvre la porte
		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		
		GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2737.66f, -3489.72f, 262.095f, 181200);
		
		if(pDoor == 0)
			return;

        //Ouvre la porte
		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
		
		GameObject * pDoor2 = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2684.28f, -3559.36f, 261.913f, 181201);
	    
		if(pDoor2 == 0)
            return;

        //Ouvre la seconde porte
        pDoor2->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
    }
	
	void AIUpdate()
	{
		switch (Phase)
		{
			case 0:
				Terrestre();
				break;
			case 1:
				Balcon();
				break;
		}
	}
	
	void Terrestre()
	{
		if(!Vague0 && Passage_balcon < 1)
		{
			_unit->m_invisible = true;
			_unit->SetPosition(2632.777588f, -3529.851074f, 274.037598f, 0.056349f, false);
			_unit->Root();
			_unit->GetAIInterface()->disable_melee = true;
			Arriver_Balcon = true;
			Vague0 = true;
			Phase = 1;
		}
		else if(!Vague0)
		{
			Passage_balcon--;
		}
		
		if(Vague3)
		{
			_unit->m_invisible = false;
			_unit->Unroot();
			_unit->GetAIInterface()->disable_melee = false;
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
			Vague3 = false;
		}
		
		if(Invocation_guerrier < 1)
		{
			_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8851);
			_unit->PlaySoundToSet(8851);
			
			Guerrier1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16984, 2704.945801f, -3461.603516f, 262.292590f, 4.624230f, true, false, 0, 0);
			Guerrier2 =	_unit->GetMapMgr()->GetInterface()->SpawnCreature(16984, 2663.913086f, -3463.610840f, 262.842712f, 4.993366f, true, false, 0, 0);
			Guerrier1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2704.945801f, -3461.603516f, 262.292590f, 16984);
			Guerrier2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2663.913086f, -3463.610840f, 262.842712f, 16984);
					
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
			
			Guerrier1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Guerrier2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Invocation_guerrier = 30;
		}
		else
		{
			Invocation_guerrier--;
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}
	
	void Balcon()
	{
		if(Arriver_Balcon)
		{
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			_unit->m_invisible = false;
			
			_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8851);
			_unit->PlaySoundToSet(8851);
			
			Champion1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16983, 2704.945801f, -3461.603516f, 262.292590f, 4.624230f, true, false, 0, 0);
			Champion2 =	_unit->GetMapMgr()->GetInterface()->SpawnCreature(16983, 2663.913086f, -3463.610840f, 262.842712f, 4.993366f, true, false, 0, 0);
			Champion1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2704.945801f, -3461.603516f, 262.292590f, 16983);
			Champion2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2663.913086f, -3463.610840f, 262.842712f, 16983);
			
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
			
			Champion1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Champion2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Invocation_mix = 15;
			Vague1 = true;
			Arriver_Balcon = false;
		}
		
		if(Vague1 && Invocation_mix < 1)
		{
			_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8851);
			_unit->PlaySoundToSet(8851);
			
			Champion1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16983, 2704.945801f, -3461.603516f, 262.292590f, 4.624230f, true, false, 0, 0);
			Gardien1 =	_unit->GetMapMgr()->GetInterface()->SpawnCreature(16981, 2663.913086f, -3463.610840f, 262.842712f, 4.993366f, true, false, 0, 0);
			Champion1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2704.945801f, -3461.603516f, 262.292590f, 16983);
			Gardien1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2663.913086f, -3463.610840f, 262.842712f, 16981);
			
			
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
			
			Champion1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Gardien1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Invocation_gardien = 30;
			Vague1 = false;
			Vague2 = true;
		}
		else if(Vague1)
		{
			Invocation_mix--;
		}
		
		if(Vague2 && Invocation_gardien < 1)
		{
			_unit->SendChatMessageLocalized(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, 8851);
			_unit->PlaySoundToSet(8851);
			
			Gardien1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16981, 2704.945801f, -3461.603516f, 262.292590f, 4.624230f, true, false, 0, 0);
			Gardien2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(16981, 2663.913086f, -3463.610840f, 262.842712f, 4.993366f, true, false, 0, 0);
			Gardien1 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2704.945801f, -3461.603516f, 262.292590f, 16981);
			Gardien2 = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2663.913086f, -3463.610840f, 262.842712f, 16981);
			
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
			
			Gardien1->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Gardien2->GetAIInterface()->MoveTo(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation());
			Retour_terrestre = 25;
			Vague2 = false;
			Vague3 = true;
		}
		else if(Vague2)
		{
			Invocation_gardien--;
		}
		
		if(Vague3 && Retour_terrestre < 1)
		{
			_unit->m_invisible = true;
			_unit->SetPosition(2684.787598f, -3502.381348f, 261.313904f, 0.076773f, false);
			Invocation_guerrier = 30;
			Phase = 0;
		}
		else if(Vague3)
		{
			Retour_terrestre--;
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
					
					if (spells[i].speech != NULL)
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
		bool Arriver_Balcon, Vague0, Vague1, Vague2, Vague3;
		int nrspells;
		uint32 Phase, Passage_balcon, Invocation_guerrier, Invocation_mix, Invocation_gardien, Retour_terrestre;
		Unit * Guerrier1, * Guerrier2, * Champion1, * Champion2, * Gardien1, * Gardien2; 
};

// Boss
#define Saphiron				15989
//Sort
#define	Aura_de_givre			28531
#define Enchaînement			19983
#define Coup_de_queue			55697
#define Coup_de_queue_Heroic	55696
#define Drain_de_vie			28542
#define Drain_de_vie_Heroic		55665
#define Berserk_SR				26662
#define Eclair_de_glace			28522
#define Souffle_de_givre_effet	30101
#define Saphiron_meurt			29357
#define Cours					256
#define Mode_Vol				768

static Coordonnée Changement_Position[] =
{
	{ },
    { 3520.717529f, -5237.437012f, 137.626816f, 2.759857f },
	{ 3520.717529f, -5237.437012f, 150.026825f, 2.759857f },
	{ 3520.717529f, -5237.437012f, 137.626816f, 2.759857f },
	{ 3520.717529f, -5237.437012f, 137.626816f, 2.759857f },
};

class SaphironAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(SaphironAI);
	SP_AI_Spell spells[5];
	bool m_spellcheck[5];

    SaphironAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 5;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Enchaînement);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 25;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 1000;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Coup_de_queue);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 35;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Coup_de_queue_Heroic);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 35;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Drain_de_vie);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 90;
			spells[2].perctrigger = 10.0f;
			spells[2].attackstoptimer = 1000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Drain_de_vie_Heroic);
			spells[2].targettype = TARGET_SELF;
			spells[2].instant = true;
			spells[2].cooldown = 90;
			spells[2].perctrigger = 10.0f;
			spells[2].attackstoptimer = 1000;
		}
		
		spells[3].info = dbcSpell.LookupEntry(Berserk_SR);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 0.0f;
		spells[3].attackstoptimer = 1000;
		
		spells[4].info = dbcSpell.LookupEntry(Eclair_de_glace);
		spells[4].targettype = TARGET_RANDOM_SINGLE;
		spells[4].instant = true;
		spells[4].cooldown = -1;
		spells[4].perctrigger = 0.0f;
		spells[4].attackstoptimer = 1000;
		
		Phase = 0;
		Decompte_Combat = 0;
		Changement_de_phase = 45;
		Temps_Event = 0;
		Temps_Transir = 3;
		Enrage = false;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Phase = 0;
		Decompte_Combat = 0;
		Changement_de_phase = 45;
		Temps_Event = 0;
		Temps_Transir = 3;
		Enrage = false;
		
		RegisterAIUpdateEvent(1000);
    }

    void OnCombatStop(Unit * mTarget)
    {
		_unit->RemoveAura(Berserk_SR);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		RemoveAIUpdateEvent();
	}

    void OnDied(Unit * mKiller)
    {
		_unit->CastSpell(_unit, Saphiron_meurt, true);
		RemoveAIUpdateEvent();
		
		GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(3536.9f, -5159.75f, 143.666f, 181225);

	    if(pDoor == 0)
            return;

        //Ouvre la porte
		pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
    }
	
	void AIUpdate()
	{
		if(!Enrage && Decompte_Combat >= 900)
		{
			_unit->CastSpell(_unit, spells[3].info, spells[3].instant);
			Enrage = true;
		}
		else if(!Enrage)
		{
			Decompte_Combat++;
		}
		
		switch (Phase)
		{
			case 0:
				Phase_de_combat();
				break;
			case 1:
				Phase_de_vol();
				break;
		}
	}
	
	void Phase_de_combat()
	{
		if(Temps_Transir < 1)
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
				
			_unit->GetMapMgr()->GetInterface()->SpawnCreature(1000003, RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), RTarget->GetOrientation(), true, false, 0, 0);
			Temps_Transir = 3;
		}
		else
		{
			Temps_Transir--;
		}
		
		if(Changement_de_phase < 1 && _unit->GetHealthPct() > 10)
		{
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(1, 1000, Cours));
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(2, 1000, Mode_Vol));
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(3, 1000, Mode_Vol));
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(4, 1000, Cours));
			_unit->GetAIInterface()->StopMovement(1000);
			_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
			_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			_unit->GetAIInterface()->setWaypointToMove(1);
			Changement_de_phase = 45;
			Phase = 1;
			Temps_Event = 1;
		}
		else
		{
			Changement_de_phase--;
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}
	
	void Phase_de_vol()
	{
		if (_unit->GetAIInterface()->getCurrentWaypoint() == 2 && Temps_Event > 0)
		{
			switch (Temps_Event)
			{
				case 5:
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
						
					if(RTarget->FindAura(Eclair_de_glace))
					{
						RandTarget = rand()%TargetTable.size();
						_unit->CastSpell(RTarget, spells[4].info, spells[4].instant);
						Aura_Eclair_de_glace = RTarget;
					}
					else
					{
						_unit->CastSpell(RTarget, spells[4].info, spells[4].instant);
						Aura_Eclair_de_glace = RTarget;
					}
					break;
				}
				
				case 7:
				{
					if(Aura_Eclair_de_glace)
					{
						if(Aura_Eclair_de_glace->FindAura(Eclair_de_glace))
						{
							_unit->GetMapMgr()->GetInterface()->SpawnGameObject(181247, Aura_Eclair_de_glace->GetPositionX(), Aura_Eclair_de_glace->GetPositionY(), Aura_Eclair_de_glace->GetPositionZ(), Aura_Eclair_de_glace->GetOrientation(), true, false, 0);
						}
					}
					break;
				}

				case 8:
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

					Unit * RTarget2 = TargetTable[RandTarget];

					if (!RTarget2)
						return;
					
					if(RTarget2->FindAura(Eclair_de_glace))
					{
						RandTarget = rand()%TargetTable.size();
												
						_unit->CastSpell(RTarget2, spells[4].info, spells[4].instant);
						Aura_Eclair_de_glace2 = RTarget2;
					}
					else
					{
						_unit->CastSpell(RTarget2, spells[4].info, spells[4].instant);
						Aura_Eclair_de_glace2 = RTarget2;
					}
					break;
				}
				
				case 10:
				{
					if(Aura_Eclair_de_glace2)
					{
						if(Aura_Eclair_de_glace2->FindAura(Eclair_de_glace))
						{
							_unit->GetMapMgr()->GetInterface()->SpawnGameObject(181247, Aura_Eclair_de_glace2->GetPositionX(), Aura_Eclair_de_glace2->GetPositionY(), Aura_Eclair_de_glace2->GetPositionZ(), Aura_Eclair_de_glace2->GetOrientation(), true, false, 0);
						}
					}
					break;
				}
				
				case 17:
				{
					_unit->CastSpell(_unit, Souffle_de_givre_effet, true);
					break;
				}
				
				case 21:
				{
					_unit->GetMapMgr()->GetInterface()->SpawnCreature(1000001, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
					break;
				}

				case 25:
				{
					_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
					_unit->GetAIInterface()->setWaypointToMove(3);
				}
				
				case 29:
				{
					if (_unit->GetAIInterface()->getCurrentWaypoint() == 3)
					{
						_unit->GetAIInterface()->m_moveFly = false;
						WorldPacket data(SMSG_MOVE_UNSET_HOVER, 13);
						data << _unit->GetNewGUID();
						data << uint32(0);
						_unit->SendMessageToSet(&data, false);
						_unit->GetAIInterface()->setWaypointToMove(4);
					}
				}
				
				case 30:
				{
					if (_unit->GetAIInterface()->getCurrentWaypoint() == 4)
					{
						_unit->GetAIInterface()->m_moveFly = false;
						_unit->GetAIInterface()->setWaypointToMove(4);
						_unit->GetAIInterface()->SetAIState(STATE_ATTACKING);
						Phase = 0;
						Temps_Event = 0;
					}
				}
			}
			Temps_Event++;
		}
	}
	
	void OnReachWP(uint32 iWaypointId, bool bForwards)
    {
		switch (iWaypointId)
		{
			case 1:
			{
				_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
				_unit->GetAIInterface()->setWaypointToMove(2);
				 _unit->GetMapMgr()->GetInterface()->SpawnCreature(1000002, 3520.717529f, -5237.437012f, 137.626816f, 2.759857f, true, false, 0, 0);
			}break;
			
			case 2:
			{
				_unit->GetAIInterface()->m_moveFly = true;
				WorldPacket data(SMSG_MOVE_SET_HOVER, 13);
				data << _unit->GetNewGUID();
				data << uint32(0);
				_unit->SendMessageToSet(&data, false);
			}break;
			case 3:
			case 4:
			case 5:
				break;
		}
    }
	
	inline WayPoint* CreateWaypoint(int id, uint32 waittime, uint32 flags)
    {
        WayPoint * wp = _unit->CreateWaypointStruct();
        wp->id = id;
        wp->x = Changement_Position[id].x;
        wp->y = Changement_Position[id].y;
        wp->z = Changement_Position[id].z;
        wp->o = Changement_Position[id].o;
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
		bool Enrage, FlightActions;
		int nrspells;
		uint32 Decompte_Combat, Phase, Changement_de_phase, Temps_Event, Temps_Transir;
		Unit * Aura_Eclair_de_glace, * Aura_Eclair_de_glace2;
};
	
// Boss
#define Sire_Zeliek				16063
// Sort
#define Marque_de_Zeliek		28835
#define Eclair_sacré			57376
#define Eclair_sacré_Heroic		57465
#define Berserk_SZ				26662
#define Colère_divine			28883
#define Colère_divine_Heroic	57466
#define Condamnation			57377

static Coordonnée Porte_Ouest[] =
{
	{ },
    { 2506.508545f, -2925.250732f, 241.277710f, 2.336275f },
	{ 2517.784912f, -2897.103516f, 241.276321f, 5.473155f },
};

class Sire_ZeliekAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Sire_ZeliekAI);
	SP_AI_Spell spells[5];
	bool m_spellcheck[5];

    Sire_ZeliekAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 5;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Marque_de_Zeliek);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Eclair_sacré);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 5;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 45.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Eclair_sacré_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 5;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 45.0f;
		}
		
		spells[2].info = dbcSpell.LookupEntry(Berserk_SZ);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[3].info = dbcSpell.LookupEntry(Colère_divine);
			spells[3].targettype = TARGET_RANDOM_SINGLE;
			spells[3].instant = true;
			spells[3].cooldown = 25;
			spells[3].perctrigger = 15.0f;
			spells[3].attackstoptimer = 1000;
			spells[3].mindist2cast = 0.0f;
			spells[3].maxdist2cast = 45.0f;
		}
		else
		{
			spells[3].info = dbcSpell.LookupEntry(Colère_divine);
			spells[3].targettype = TARGET_RANDOM_SINGLE;
			spells[3].instant = true;
			spells[3].cooldown = 25;
			spells[3].perctrigger = 15.0f;
			spells[3].attackstoptimer = 1000;
			spells[3].mindist2cast = 0.0f;
			spells[3].maxdist2cast = 45.0f;
		}
		
		spells[4].info = dbcSpell.LookupEntry(Condamnation);
		spells[4].targettype = TARGET_SELF;
		spells[4].instant = false;
		spells[4].cooldown = 35;
		spells[4].perctrigger = 25.0f;
		spells[4].attackstoptimer = 2000;
		
		Phase = 0;
		Temps_Marque = 24;
		Marque = 0;
		Enrage = false;
		lancement_event = true;
		Combat_lancer = false;
		Mort_Zeliek = false;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		
		RegisterAIUpdateEvent(500);
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
		
		Phase = 1;
		Temps_Marque = 24;
		Marque = 0;
		Enrage = false;
		Combat_lancer = true;
		Mort_Zeliek = false;
		RegisterAIUpdateEvent(1000);
	}

	void OnCombatStop(Unit * mTarget)
    {
		_unit->RemoveAura(Berserk_SZ);
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		RemoveAIUpdateEvent();
		
		if(Combat_lancer)
		{
			Phase = 0;
			lancement_event = true;
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			Combat_lancer = false;
			
			_unit->SetPosition(2528.79039f, -2948.580078f, 245.632996f, 5.270900f, false);
		}
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		Mort_Zeliek = true;
		
		if(Mort_Vaillefendre && Mort_Blaumeux && Mort_Korth_azz)
		{
			_unit->GetMapMgr()->GetInterface()->SpawnGameObject(181366, 2519.668213f, -2950.441895f, 245.552444f, 5.690034, true, false, 0);
		}
    }
	
	void AIUpdate()
	{
		switch (Phase)
		{
			case 0:
				Changement_position();
				break;
			case 1:
				Combat();
				break;
		}
	}
	
	void Changement_position()
	{
		if(lancement_event)
		{
			for(std::set<Player*>::iterator Detection = _unit->GetInRangePlayerSetBegin(); Detection != _unit->GetInRangePlayerSetEnd(); Detection++)
			{
				if((*Detection)->GetTypeId() == TYPEID_PLAYER)
				{
					if(_unit->CalcDistance(*Detection) <= 45.0f)
					{
						for (int i = 1; i < 4; i++)
						{
							_unit->GetAIInterface()->addWayPoint(CreateWaypoint(i, 0, Galot));
						}
		
						_unit->GetAIInterface()->StopMovement(1000);
						_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
						_unit->GetAIInterface()->setWaypointToMove(1);
						lancement_event = false;
					}
				}
			}
		}
	}
	
	void Combat()
	{
		if(!Enrage && Temps_Marque < 1)
		{
			std::vector<Unit*> TargetTable;	

			for( set<Player*>::iterator PlayerIter = _unit->GetInRangePlayerSetBegin(); PlayerIter != _unit->GetInRangePlayerSetEnd(); ++PlayerIter ) 
			{ 
				if (_unit->CalcDistance((*PlayerIter)) < 45.0f)
				{
					TargetTable.push_back(*PlayerIter);
				} 
			}
	
			if (!TargetTable.size())
				return;
				
			for(size_t i= 0 ; i<TargetTable.size(); i++)
			{
				_unit->CastSpell(TargetTable[i], spells[0].info, spells[0].instant);
				
				for (int Nombre_Marque = 0; Nombre_Marque < 100; Nombre_Marque++)
				{
					if (TargetTable[i]->FindAuraCountByHash(SPELL_HASH_MARK_OF_ZELIEK, Nombre_Marque))
					{
						switch (Nombre_Marque)
						{
						
							case 2:
								_unit->DealDamage(TargetTable[i], 500, 0, 0, 0, true);
								break;
							
							case 3:
								_unit->DealDamage(TargetTable[i], 1500, 0, 0, 0, true);
								break;
						
							case 4:
								_unit->DealDamage(TargetTable[i], 4000, 0, 0, 0, true);
								break;
								
							case 5:
								_unit->DealDamage(TargetTable[i], 12500, 0, 0, 0, true);
								break;
								
							case 6:
								_unit->DealDamage(TargetTable[i], 20000, 0, 0, 0, true);
								break;
						}
						
						if (Nombre_Marque > 6)
						{
							_unit->DealDamage(TargetTable[i], 14000 + (Nombre_Marque * 1000), 0, 0, 0, true);
						}
					}
				}
			}
			
			Marque++;
			Temps_Marque = 15;
		}
		else if(!Enrage)
		{
			Temps_Marque--;
		}
		
		if(!Enrage && Marque == 100)
		{
			Enrage = true;
			_unit->CastSpell(_unit, spells[2].info, spells[2].instant);
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}
	
	void OnReachWP(uint32 iWaypointId, bool bForwards)
    {
		switch (iWaypointId)
		{
			case 1:
			{
				_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
				_unit->GetAIInterface()->setWaypointToMove(2);
			}break;
			
			case 2:
			{
				_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
				_unit->GetAIInterface()->SetAIState(STATE_ATTACKING);
				
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
				Phase = 1;
			}break;
		}
    }
	
	inline WayPoint* CreateWaypoint(int id, uint32 waittime, uint32 flags)
    {
        WayPoint * wp = _unit->CreateWaypointStruct();
        wp->id = id;
        wp->x = Porte_Ouest[id].x;
        wp->y = Porte_Ouest[id].y;
        wp->z = Porte_Ouest[id].z;
        wp->o = Porte_Ouest[id].o;
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
		bool Enrage, lancement_event, Combat_lancer;
		int nrspells, Marque;
		uint32 Temps_Marque, Phase;
};

// Boss
#define Stalagg		15929
// Sort
#define Vague_de_puissance			54529
#define Vague_de_puissance_heroic	28134
#define Attraction_magnétique_SG	41959

class StalaggAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(StalaggAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    StalaggAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Vague_de_puissance);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 45;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Champ_statique);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		Stalagg_mort = false;
		Résurrection = 5;
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Stalagg_mort = false;
		Résurrection = 5;
		
		RegisterAIUpdateEvent(1000);
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
		_unit->RemoveAura(Berserk);
		RemoveAIUpdateEvent();
		Stalagg_mort = true;
		Cadavre_Stalagg = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 15929);
    }
	
	void AIUpdate()
	{
		if(Feugen_mort)
		{
			if(Résurrection < 1)
			{
				Cadavre_Feugen->setDeathState(ALIVE);
				Cadavre_Feugen->SetHealthPct(100);
				Feugen_mort = false;
				Résurrection = 5;
			}
			else
			{
				Résurrection--;
			}
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
		int nrspells;
		uint32 Résurrection;
};

// Boss
#define Thane_Korth_azz			16064
// Sort
#define Marque_de_Korth_azz		28832
#define Météore					28884
#define Météore_Heroic			57467
#define Berserk_TKA				26662

static Coordonnée Porte_Est[] =
{
	{ },
    { 2539.224609f, -2974.423828f, 241.306808f, 5.479501f },
	{ 2538.640869f, -3014.260010f, 241.337769f, 4.710595f },
};

class Thane_Korth_azzAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Thane_Korth_azzAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Thane_Korth_azzAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Marque_de_Korth_azz);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Météore);
			spells[1].targettype = TARGET_RANDOM_DESTINATION;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1500;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 20.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Météore_Heroic);
			spells[1].targettype = TARGET_RANDOM_DESTINATION;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 25.0f;
			spells[1].attackstoptimer = 1500;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 20.0f;
		}
		
		spells[2].info = dbcSpell.LookupEntry(Berserk_TKA);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;
		
		Phase = 0;
		Temps_Marque = 24;
		Marque = 0;
		Enrage = false;
		lancement_event = true;
		Combat_lancer = false;
		Mort_Korth_azz = false;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		
		RegisterAIUpdateEvent(500);
	}
	
	void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
		
		Phase = 1;
		Temps_Marque = 24;
		Marque = 0;
		Enrage = false;
		Combat_lancer = true;
		Mort_Korth_azz = false;		
		RegisterAIUpdateEvent(1000);
	}

	void OnCombatStop(Unit * mTarget)
    {
		_unit->RemoveAura(Berserk_TKA);
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		_unit->SetUInt32Value(UNIT_FIELD_HEALTH, _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		RemoveAIUpdateEvent();
		lancement_event = true;
		
		if(Combat_lancer)
		{
			Phase = 0;
			lancement_event = true;
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			Combat_lancer = false;
			
			_unit->SetPosition(2520.500000f, -2955.379883f, 245.634995f, 5.585050f, false);
		}
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		Mort_Korth_azz = true;
		
		if(Mort_Vaillefendre && Mort_Blaumeux && Mort_Zeliek)
		{
			_unit->GetMapMgr()->GetInterface()->SpawnGameObject(181366, 2519.668213f, -2950.441895f, 245.552444f, 5.690034, true, false, 0);
		}
    }
	
	void AIUpdate()
	{
		switch (Phase)
		{
			case 0:
				Changement_position();
				break;
			case 1:
				Combat();
				break;
		}
	}
	
	void Changement_position()
	{
		if(lancement_event)
		{
			for(std::set<Player*>::iterator Detection = _unit->GetInRangePlayerSetBegin(); Detection != _unit->GetInRangePlayerSetEnd(); Detection++)
			{
				if((*Detection)->GetTypeId() == TYPEID_PLAYER)
				{
					if(_unit->CalcDistance(*Detection) <= 45.0f)
					{
						for (int i = 1; i < 4; i++)
						{
							_unit->GetAIInterface()->addWayPoint(CreateWaypoint(i, 0, Galot));
						}
		
						_unit->GetAIInterface()->StopMovement(1000);
						_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
						_unit->GetAIInterface()->setWaypointToMove(1);
						lancement_event = false;
					}
				}
			}
		}
	}
	
	void Combat()
	{
		if(!Enrage && Temps_Marque < 1)
		{
			std::vector<Unit*> TargetTable;	

			for( set<Player*>::iterator PlayerIter = _unit->GetInRangePlayerSetBegin(); PlayerIter != _unit->GetInRangePlayerSetEnd(); ++PlayerIter ) 
			{ 
				if (_unit->CalcDistance((*PlayerIter)) < 45.0f)
				{
					TargetTable.push_back(*PlayerIter);
				} 
			}
	
			if (!TargetTable.size())
				return;
				
			for(size_t i= 0 ; i<TargetTable.size(); i++)
			{
				_unit->CastSpell(TargetTable[i], spells[0].info, spells[0].instant);
				
				for (int Nombre_Marque = 0; Nombre_Marque < 100; Nombre_Marque++)
				{
					if (TargetTable[i]->FindAuraCountByHash(SPELL_HASH_MARK_OF_KORTH_AZZ, Nombre_Marque))
					{
						switch (Nombre_Marque)
						{
						
							case 2:
								_unit->DealDamage(TargetTable[i], 500, 0, 0, 0, true);
								break;
							
							case 3:
								_unit->DealDamage(TargetTable[i], 1500, 0, 0, 0, true);
								break;
						
							case 4:
								_unit->DealDamage(TargetTable[i], 4000, 0, 0, 0, true);
								break;
								
							case 5:
								_unit->DealDamage(TargetTable[i], 12500, 0, 0, 0, true);
								break;
								
							case 6:
								_unit->DealDamage(TargetTable[i], 20000, 0, 0, 0, true);
								break;
						}
						
						if (Nombre_Marque > 6)
						{
							_unit->DealDamage(TargetTable[i], 14000 + (Nombre_Marque * 1000), 0, 0, 0, true);
						}
					}
				}
			}
			
			Marque++;
			Temps_Marque = 12;
		}
		else if(!Enrage)
		{
			Temps_Marque--;
		}
		
		if(!Enrage && Marque == 100)
		{
			Enrage = true;
			_unit->CastSpell(_unit, spells[2].info, spells[2].instant);
		}
		
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
	}
	
	void OnReachWP(uint32 iWaypointId, bool bForwards)
    {
		switch (iWaypointId)
		{
			case 1:
			{
				_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
				_unit->GetAIInterface()->setWaypointToMove(2);
			}break;
			
			case 2:
			{
				_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
				_unit->GetAIInterface()->SetAIState(STATE_ATTACKING);
				
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
				Phase = 1;
			}break;
		}
    }
	
	inline WayPoint* CreateWaypoint(int id, uint32 waittime, uint32 flags)
    {
        WayPoint * wp = _unit->CreateWaypointStruct();
        wp->id = id;
        wp->x = Porte_Est[id].x;
        wp->y = Porte_Est[id].y;
        wp->z = Porte_Est[id].z;
        wp->o = Porte_Est[id].o;
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
		bool Enrage, lancement_event, Combat_lancer;
		int nrspells, Marque;
		uint32 Temps_Marque, Phase;
};

/** Add Boss()

	Nuage de Grobbulus
	Spore
	
**/

// GameObject
#define Bloc_de_Glace		181247

class Bloc_de_GlaceAI : public GameObjectAIScript
{
public:
	Bloc_de_GlaceAI(GameObject* goinstance) : GameObjectAIScript(goinstance) 
	{
		RegisterAIUpdateEvent(500);
		_gameobject->SetUInt64Value(GAMEOBJECT_FLAGS, GAMEOBJECT_UNCLICKABLE);
	}
	static GameObjectAIScript *Create(GameObject * GO) { return new Bloc_de_GlaceAI(GO); }

	void AIUpdate()
	{
		for(std::set<Player*>::iterator Detection = _gameobject->GetInRangePlayerSetBegin(); Detection != _gameobject->GetInRangePlayerSetEnd(); Detection++)
		{
			if((*Detection)->GetTypeId() == TYPEID_PLAYER)
			{
				if(_gameobject->CalcDistance(*Detection) < 0.5f)
				{
					Aura_Eclair_de_glace = (*Detection);
					
					int32 val = 500000000;
					val += float2int32(float(val));

					Absorb *ab = new Absorb;
					ab->amt = val;
					Aura_Eclair_de_glace->Absorbs[4].push_back(ab);

					if(!Aura_Eclair_de_glace->FindAura(Eclair_de_glace))
					{
						Aura_Eclair_de_glace->Absorbs[4].clear();
						delete ab;
						_gameobject->Despawn(0,0);
					}
				}
			}
		}
	}
	protected:
		Unit * Aura_Eclair_de_glace, * Aura_Eclair_de_glace2;
};

// Mob
#define Bombe_de_givre_de_Saphiron		1000001
// Sort
#define Souffle_de_givre				28524 
#define Bombe_de_givre					64624
#define Vol_Bombe						768

static Coordonnée Explosion[] =
{
	{ },
    { 3520.919922f, -5229.200195f, 137.626007f, 4.510490f },
};

class Bombe_de_givre_de_SaphironAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Bombe_de_givre_de_SaphironAI);
	Bombe_de_givre_de_SaphironAI(Creature * pCreature) : CreatureAIScript(pCreature)
	{	
		Visuel = false;
		Position = false;
		_unit->m_flySpeed = 3.0f;
		_unit->m_walkSpeed = 3.0f;
		_unit->m_runSpeed = 3.0f;
		
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_2);
		_unit->GetAIInterface()->disable_melee = true;
		_unit->GetAIInterface()->m_canMove = false;
		_unit->m_noRespawn = true;

		RegisterAIUpdateEvent(1000);
	}
	
	void AIUpdate()
	{
		if(!Visuel)
		{
			_unit->CastSpell(_unit, Bombe_de_givre, true);
			Visuel = true;
			Position = true;
		}
		
		if(Position)
		{
			for (int i = 1; i < 2; i++)
			{
				_unit->GetAIInterface()->addWayPoint(CreateWaypoint(i, 0, Vol_Bombe));
			}
		
			_unit->GetAIInterface()->StopMovement(1000);
			_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
			_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			_unit->GetAIInterface()->setWaypointToMove(1);
			Position = false;
			Temps_Explosion = 1;
		}
		
		if (_unit->GetAIInterface()->getCurrentWaypoint() == 1 && Temps_Explosion > 0)
		{
			switch (Temps_Explosion)
			{
				case 3:
				{
					_unit->CastSpell(_unit, Souffle_de_givre, true);
					break;
				}
				
				case 5:
				{
					for(std::set<Player*>::iterator PresenceItr = _unit->GetInRangePlayerSetBegin(); PresenceItr != _unit->GetInRangePlayerSetEnd(); PresenceItr++)
					{
						if((*PresenceItr)->GetTypeId() == TYPEID_PLAYER)
						{
							if( _unit->CalcDistance((*PresenceItr)) > 0.0f )
							{
								(*PresenceItr)->RemoveAura(Eclair_de_glace);
							}
						}
					}
					_unit->Despawn(0,0);
					break;
				}
			}
			Temps_Explosion++;
		}
	}
		
	void OnReachWP(uint32 iWaypointId, bool bForwards)
	{
		switch (iWaypointId)
		{
			case 1:
				break;
		}
	}
	
	inline WayPoint* CreateWaypoint(int id, uint32 waittime, uint32 flags)
    {
        WayPoint * wp = _unit->CreateWaypointStruct();
        wp->id = id;
        wp->x = Explosion[id].x;
        wp->y = Explosion[id].y;
        wp->z = Explosion[id].z;
        wp->o = Explosion[id].o;
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
	
	protected:
		bool Visuel, Position;
		uint32 Temps_Explosion;
};

// Mob
#define Declencheur_Coup_d_aile_de_Saphiron			1000002
// Sort
#define Coup_d_aile_de_Saphiron						29328

class Declencheur_Coup_d_aile_de_SaphironAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Declencheur_Coup_d_aile_de_SaphironAI);
	Declencheur_Coup_d_aile_de_SaphironAI(Creature * pCreature) : CreatureAIScript(pCreature)
	{	
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		
		Temps_Visuel = 1;
		
		RegisterAIUpdateEvent(1000);
		_unit->Despawn(26000, 0);
	}
	
	void AIUpdate()
	{
		if(Temps_Visuel < 1)
		{
			_unit->CastSpell(_unit, Coup_d_aile_de_Saphiron, true);
			Temps_Visuel = 1;
		}
		else
		{
			Temps_Visuel--;
		}
	}
	
	protected:
		uint32 Temps_Visuel;
};

// Mob
#define Declencheur_Transir		1000003
// Sort
#define Transir					28547

class Declencheur_TransirAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Declencheur_TransirAI);
	Declencheur_TransirAI(Creature * pCreature) : CreatureAIScript(pCreature)
	{	
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_2);
		_unit->GetAIInterface()->disable_melee = true;
		_unit->GetAIInterface()->m_canMove = false;
		_unit->m_noRespawn = true;
		
		Visuel = false;
		
		RegisterAIUpdateEvent(1000);
		_unit->Despawn(10000, 0);
	}
	
	void AIUpdate()
	{
		if(!Visuel)
		{
			_unit->CastSpell(_unit, Transir, true);
			Visuel = true;
		}
	}
	
	protected:
		bool Visuel;
};

// Mob
#define Croq_zombie				16360
// Sort
#define Blessure_infectée		29306

class Croq_zombieAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Croq_zombieAI);
    Croq_zombieAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		_unit->m_noRespawn = true;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
	}

	void OnDamageTaken(Unit* mAttacker, float fAmount)
	{
		_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
		_unit->CastSpell(mAttacker, Blessure_infectée, true);
		_unit->Despawn(480000,0);
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
	}
};

// Mob
#define Nuage_de_Grobbulus	16363
// Sort
#define Poison				38462

class Nuage_de_GrobbulusAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Nuage_de_GrobbulusAI);
    Nuage_de_GrobbulusAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		Visuel = false;
		
		_unit->Root();
		_unit->m_noRespawn = true;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		
		RegisterAIUpdateEvent(1000);
	}
	
	void AIUpdate()
	{
		if(!Visuel)
		{
			_unit->CastSpell(_unit, dbcSpell.LookupEntry(Poison), true);
			_unit->Despawn(60000, 0);
			Visuel = true;
			Log.Notice("ADD","FUCK");
		}
		
		for(std::set<Player*>::iterator PresenceItr = _unit->GetInRangePlayerSetBegin(); PresenceItr != _unit->GetInRangePlayerSetEnd(); PresenceItr++)
		{
			if((*PresenceItr)->GetTypeId() == TYPEID_PLAYER)
			{
				if(_unit->CalcDistance(*PresenceItr) <= 5.0f)
				{
					_unit->DealDamage((*PresenceItr), 2000, 0, 0, 0,true);
				}
			}
		}
	}
	
	protected:
		bool Visuel;
};

// Mob
#define Roi_liche	30002

class Roi_licheAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Roi_licheAI);
    Roi_licheAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		_unit->Root();
		_unit->m_noRespawn = true;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
	}
};

// Mob
#define Spore					16286
// Sort
#define Croissance_fongique		29232

class SporeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(SporeAI);

    SporeAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {}
    
    void OnCombatStart(Unit * mTarget)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		_unit->Despawn(3000,0);
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
		_unit->CastSpell(_unit, Croissance_fongique, true);
		_unit->Despawn(3000,0);
		RemoveAIUpdateEvent();
    }
};

/** Mob (52)

	Abomination irrésistible
	Acolyte de Naxxramas
	Adorateur de Naxxramas
	Assemblage osseux
	Assemblage pestiféré
	Assistant en chirurgie
	Bâton impie
	Bête de peste
	Capitaine des chevaliers de la mort
	Cavalier de la mort
	Cavalier spectral
	Cavalier tenace
	Champion pestiféré
	Chauve-souris pesteuse
	Cheval spectral
	Chevalier de la mort
	Chevalier de la mort spectral
	Chevalier de la mort tenace
	Colosse raccommodé
	Crache-vase
	Doublure de chevalier de la mort
	Ecuyer ressuscité
	Epées impies
	Forgeron squelettique
	Gardien de la Couronne de glace
	Gardien des cryptes
	Gardien pestiféré
	Gargouille peau de pierre
	Géant raccommodé
	Gelée d'égout
	Gelée d'embaumement
	Golem recousu
	Goule infectieuse
	Guerrier pestiféré
	Guerrier touché par l'obscurité
	Hache impie
	Horreur des tombes
	Jeune araignée de Maexxna
	Jeune recrue spectrale
	Jeune recrue tenace
	Larve mutante
	Monstruosité vivante
	Nécrochevalier
	Oeil pédonculé
	Ombre de Naxxramas
	Ombre vigilante
	Rampant de l'effroi
	Saccageur des cryptes
	Sectateur de Naxxramas
	Suivant de Naxxramas
	Tisse-charogne
	Vomisseur de bile
	
**/

// Mob
#define Abomination_irrésistible	16428
// Sort
#define Blessure_mortelle_AI		28467
#define Frénésie_AI					28468

class Abomination_irrésistibleAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Abomination_irrésistibleAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Abomination_irrésistibleAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Blessure_mortelle_AI);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 15.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(Frénésie_AI);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
		
		Etat_Enrager = false;
    }
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Etat_Enrager = false;

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
		if((_unit->GetHealthPct() <= 15) && !Etat_Enrager)
		{
			_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
			Etat_Enrager = true;
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
		bool Etat_Enrager;
		int nrspells;
};

// Mob
#define Acolyte_de_Naxxramas				15981
// Sort
#define Explosion_des_arcanes				56063
#define Explosion_des_arcanes_Heroic		56067
#define Salve_de_Traits_de_l_ombre			56064
#define Salve_de_Traits_de_l_ombre_Heroic	56065

class Acolyte_de_NaxxramasAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Acolyte_de_NaxxramasAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Acolyte_de_NaxxramasAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_des_arcanes);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = 30;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 2000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_des_arcanes_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = 30;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 2000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Salve_de_Traits_de_l_ombre);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 3000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 30.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Salve_de_Traits_de_l_ombre_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 3000;
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
#define Adorateur_de_Naxxramas		16506
// Sort
#define Boule_de_feu				54095
#define Boule_de_feu_Heroic			54096
#define Etreinte_de_la_veuve		28732

class Adorateur_de_NaxxramasAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Adorateur_de_NaxxramasAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Adorateur_de_NaxxramasAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Boule_de_feu);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 2500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 45.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Boule_de_feu_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 2500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 45.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Salve_de_Traits_de_l_ombre_Heroic);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 40;
		spells[1].perctrigger = 10.0f;
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
#define Assemblage_osseux		16167
// Sort
#define Balayage_brutal			55319
#define Balayage_brutal_Heroic	55324

class Assemblage_osseuxAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Assemblage_osseuxAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Assemblage_osseuxAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Balayage_brutal);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 45;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 10.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Balayage_brutal_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 45;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 10.0f;
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
#define Assemblage_pestiféré	16982
// Sort
#define Balayage_brutal_AP		56586

class Assemblage_pestiféréAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Assemblage_pestiféréAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Assemblage_pestiféréAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Balayage_brutal_AP);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = true;
		spells[0].cooldown = 45;
		spells[0].perctrigger = 10.0f;
		spells[0].attackstoptimer = 1000;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 10.0f;
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
#define Assistant_en_chirurgie	16022
// Sort
#define Fouet_mental			28310
#define Fouet_mental_Heroic		54339

class Assistant_en_chirurgieAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Assistant_en_chirurgieAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Assistant_en_chirurgieAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Fouet_mental);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 35;
			spells[0].perctrigger = 13.0f;
			spells[0].attackstoptimer = 5000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 50.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Fouet_mental_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 35;
			spells[0].perctrigger = 13.0f;
			spells[0].attackstoptimer = 5000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 50.0f;
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
#define Bâton_impie						16215
// Sort
#define Explosion_des_arcanes_BI		28450
#define Explosion_des_arcanes_Heroic_BI	55467
#define Métamorphose					29848
#define Nova_de_givre					29849

class Bâton_impieAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Bâton_impieAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Bâton_impieAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_des_arcanes_BI);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 500;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_des_arcanes_Heroic_BI);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 500;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Métamorphose);
		spells[1].targettype = TARGET_RANDOM_SINGLE;
		spells[1].instant = true;
		spells[1].cooldown = 15;
		spells[1].perctrigger = 5.0f;
		spells[1].attackstoptimer = 1000;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 45.0f;
		
		spells[2].info = dbcSpell.LookupEntry(Métamorphose);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = 15;
		spells[2].perctrigger = 15.0f;
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
#define Bête_de_peste				16034
// Sort
#define Projection_de_peste			54780
#define Projection_de_peste_Heroic	56538

class Bête_de_pesteAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Bête_de_pesteAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Bête_de_pesteAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Projection_de_peste);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 50.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Projection_de_peste_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 50.0f;
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
#define Capitaine_des_chevaliers_de_la_mort		16145
// Sort
#define Frappe_de_peste							55255
#define Frappe_de_peste_Heroic					55321
#define Présence_impie							55222
#define Réanimation_morbide						28353

class Capitaine_des_chevaliers_de_la_mortAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Capitaine_des_chevaliers_de_la_mortAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Capitaine_des_chevaliers_de_la_mortAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Frappe_de_peste);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Frappe_de_peste_Heroic);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Présence_impie);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
		
		spells[2].info = dbcSpell.LookupEntry(Réanimation_morbide);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = false;
		spells[2].cooldown = 60;
		spells[2].perctrigger = 5.0f;
		spells[2].attackstoptimer = 1500;
		
		Presence = false;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Presence = false;
			
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
		if((_unit->GetHealthPct() <= 25) && !Presence)
		{
			_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
			Presence = true;
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
		bool Presence;
		int nrspells;
};

// Mob
#define Cavalier_de_la_mort					16163
// Sort
#define Armure_d_os							55315
#define Armure_d_os_Heroic					55336
//#define Descente_du_destrier_de_la_mort	55294
#define Strangulation						55314
#define Strangulation_Heroic				55334
#define Toucher_de_glace					55313
#define Toucher_de_glace_Heroic				55331

class Cavalier_de_la_mortAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Cavalier_de_la_mortAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Cavalier_de_la_mortAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Armure_d_os);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 120;
			spells[0].perctrigger = 5.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Armure_d_os_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 120;
			spells[0].perctrigger = 5.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{		
			spells[1].info = dbcSpell.LookupEntry(Strangulation);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 10.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 50.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Strangulation_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 10.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 50.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{		
			spells[2].info = dbcSpell.LookupEntry(Toucher_de_glace);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = true;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 15.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 20.0f;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Toucher_de_glace_Heroic);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = true;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 15.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 20.0f;
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
#define Cavalier_spectral		16150
// Sort
#define Aura_impie				55606
#define Aura_impie_Heroic		55608
#define Drain_de_vie_CP			27994
#define Drain_de_vie_Heroic_CP	55646
#define Frénésie_impie			55648
#define Frénésie_impie_Heroic	27995

class Cavalier_spectralAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Cavalier_spectralAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Cavalier_spectralAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Aura_impie);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = -1;
			spells[0].perctrigger = 0.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Aura_impie_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = -1;
			spells[0].perctrigger = 0.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Drain_de_vie_CP);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 10.0f;
			spells[1].attackstoptimer = 5000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 20.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Drain_de_vie_Heroic_CP);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 10.0f;
			spells[1].attackstoptimer = 5000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 20.0f;
		}
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Frénésie_impie);
			spells[2].targettype = TARGET_RANDOM_FRIEND;
			spells[2].instant = true;
			spells[2].cooldown = 45;
			spells[2].perctrigger = 5.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 30.0f;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Frénésie_impie_Heroic);
			spells[2].targettype = TARGET_RANDOM_FRIEND;
			spells[2].instant = true;
			spells[2].cooldown = 45;
			spells[2].perctrigger = 5.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 30.0f;
		}
		
		Aura = false;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Aura = false;
			
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
		if((_unit->GetHealthPct() <= 25) && !Aura)
		{
			_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
			Aura = true;
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
		bool Aura;
		int nrspells;
};

// Mob
#define Cavalier_tenace							16126
// Sort
#define Aura_impie								55606
#define Aura_impie_Heroic						55608
#define Invocation_d_assistants					29316
#define Salve_de_Traits_de_l_ombre_CT			27831
#define Salve_de_Traits_de_l_ombre_Heroic_CT	55638

class Cavalier_tenaceAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Cavalier_tenaceAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Cavalier_tenaceAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Aura_impie);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = -1;
			spells[0].perctrigger = 0.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Aura_impie_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = -1;
			spells[0].perctrigger = 0.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Invocation_d_assistants);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 900;
		spells[1].perctrigger = 5.0f;
		spells[1].attackstoptimer = 1000;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Salve_de_Traits_de_l_ombre_CT);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = false;
			spells[2].cooldown = 15;
			spells[2].perctrigger = 20.0f;
			spells[2].attackstoptimer = 1500;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 45.0f;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Salve_de_Traits_de_l_ombre_Heroic_CT);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = false;
			spells[2].cooldown = 15;
			spells[2].perctrigger = 20.0f;
			spells[2].attackstoptimer = 1500;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 45.0f;
		}
		
		Aura = false;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
		
		Aura = false;
		
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
		if((_unit->GetHealthPct() <= 25) && !Aura)
		{
			_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
			Aura = true;
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
		bool Aura;
		int nrspells;
};

// Mob
#define Champion_pestiféré			16983
// Sort
#define Frappe_mortelle				32736
#define Horion_de_l_ombre			30138
#define Horion_de_l_ombre_Heroic	54889

class Champion_pestiféréAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Champion_pestiféréAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Champion_pestiféréAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Frappe_mortelle);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 20.0f;
		spells[0].attackstoptimer = 1000;

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Horion_de_l_ombre);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 10.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Horion_de_l_ombre_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 10.0f;
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
#define Chauve_souris_pesteuse	16037
// Sort
#define Morsure_putride			30113

class Chauve_souris_pesteuseAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Chauve_souris_pesteuseAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Chauve_souris_pesteuseAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Morsure_putride);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 20.0f;
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
#define Cheval_spectral		16149
// Sort
#define Piétinement			27993

class Cheval_spectralAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Cheval_spectralAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Cheval_spectralAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Piétinement);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 5.0f;
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
#define Chevalier_de_la_mort	16146
// Sort
#define Hystérie				55213
#define Présence_de_sang		55212
#define Voile_mortel			55209
#define Voile_mortel_Heroic		55320

class Chevalier_de_la_mortAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Chevalier_de_la_mortAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Chevalier_de_la_mortAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Hystérie);
		spells[0].targettype = TARGET_RANDOM_FRIEND;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 5.0f;
		spells[0].attackstoptimer = 1000;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 45.0f;
		
		spells[1].info = dbcSpell.LookupEntry(Présence_de_sang);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Voile_mortel);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = true;
			spells[2].cooldown = 20;
			spells[2].perctrigger = 15.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 45.0f;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Voile_mortel_Heroic);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = true;
			spells[2].cooldown = 20;
			spells[2].perctrigger = 15.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 45.0f;
		}
		
		Presence = false;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Presence = false;
		
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
		if((_unit->GetHealthPct() <= 25) && !Presence)
		{
			_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
			Presence = true;
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
	bool Presence;
		int nrspells;
};

// Mob
#define Chevalier_de_la_mort_spectral	16148
// Sort
#define Tourbillon						56408

class Chevalier_de_la_mort_spectralAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Chevalier_de_la_mort_spectralAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Chevalier_de_la_mort_spectralAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Tourbillon);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 35;
		spells[0].perctrigger = 10.0f;
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
#define Chevalier_de_la_mort_tenace		16125
// Sort
#define Invocation_d_assistants			29316
#define Marque_de_l_ombre				27825

class Chevalier_de_la_mort_tenaceAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Chevalier_de_la_mort_tenaceAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Chevalier_de_la_mort_tenaceAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Invocation_d_assistants);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 900;
		spells[0].perctrigger = 5.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Marque_de_l_ombre);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 35;
		spells[1].perctrigger = 13.5f;
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
#define Colosse_raccommodé			30071
// Sort
#define Piétinement_violent			55821
#define Piétinement_violent_Heroic	55826
#define Rage_irrésistible			54356

class Colosse_raccommodéAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Colosse_raccommodéAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Colosse_raccommodéAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Piétinement_violent);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Piétinement_violent_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Rage_irrésistible);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
		
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
		if((_unit->GetHealthPct() <= 25) && !Rage)
		{
			_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
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
		bool Rage;
		int nrspells;
};

// Mob
#define Crache_vase			16029
// Sort
#define Vase_acide			27891
#define Vase_acide_Heroic	54331

class Crache_vaseAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Crache_vaseAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Crache_vaseAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Vase_acide);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 45.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Vase_acide_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 45.0f;
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
#define Doublure_de_chevalier_de_la_mort	16803
// Sort
#define Barrière_d_os						29061
#define Frappe_de_sang						61696
						
class Doublure_de_chevalier_de_la_mortAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Doublure_de_chevalier_de_la_mortAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Doublure_de_chevalier_de_la_mortAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Barrière_d_os);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 100;
		spells[0].perctrigger = 7.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Frappe_de_sang);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 25;
		spells[1].perctrigger = 18.0f;
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
#define Ecuyer_ressuscité	16154
// Sort
#define Perce_armure		55318

class Ecuyer_ressuscitéAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Ecuyer_ressuscitéAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Ecuyer_ressuscitéAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Perce_armure);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 20;
		spells[0].perctrigger = 10.0f;
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
#define Epées_impies		16216
// Sort
#define Enchaînement_EI		15284
#define Rosser				3391

class Epées_impiesAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Epées_impiesAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Epées_impiesAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Enchaînement_EI);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 20;
		spells[0].perctrigger = 20.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Rosser);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 55;
		spells[1].perctrigger = 10.0f;
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
#define Forgeron_squelettique	16193
// Sort
#define Désarmement				6713
#define Ecraser_armure			33661

class Forgeron_squelettiqueAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Forgeron_squelettiqueAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Forgeron_squelettiqueAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Désarmement);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 25;
		spells[0].perctrigger = 25.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Ecraser_armure);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 15;
		spells[1].perctrigger = 10.0f;
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
#define Gardien_de_la_Couronne_de_glace		16441
// Sort
#define Drain_sanglant						28470

class Gardien_de_la_Couronne_de_glaceAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Gardien_de_la_Couronne_de_glaceAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Gardien_de_la_Couronne_de_glaceAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Boule_de_feu);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = false;
		spells[0].cooldown = 25;
		spells[0].perctrigger = 13.0f;
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
#define Gardien_des_cryptes		16573
// Sort
#define Crachat_acide			28969
#define Crachat_acide_Heroic	56098
#define Enchaînement_GDC		40504
#define Frénésie_GDC			8269

class Gardien_des_cryptesAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Gardien_des_cryptesAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Gardien_des_cryptesAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Crachat_acide);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Crachat_acide_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Enchaînement_GDC);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 15;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 1000;
		
		spells[2].info = dbcSpell.LookupEntry(Frénésie_GDC);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = 180;
		spells[2].perctrigger = 5.0f;
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
#define Gardien_pestiféré				16981
// Sort
#define Explosion_des_arcanes_CP		54890
#define Explosion_des_arcanes_Heroic_CP	54891
#define Transfert						29208

class Gardien_pestiféréAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Gardien_pestiféréAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Gardien_pestiféréAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_des_arcanes_CP);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1500;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_des_arcanes_Heroic_CP);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1500;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Transfert);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 90;
		spells[1].perctrigger = 5.0f;
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
#define Gargouille_peau_de_pierre	16168
// Sort
#define Peau_de_pierre				28995	
#define Peau_de_pierre_Heroic		54722
#define Salve_d_acide				29325
#define Salve_d_acide_Heroic		54714

class Gargouille_peau_de_pierreAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Gargouille_peau_de_pierreAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Gargouille_peau_de_pierreAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Peau_de_pierre);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = -1;
			spells[0].perctrigger = 0.0f;
			spells[0].attackstoptimer = 7000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Peau_de_pierre_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = -1;
			spells[0].perctrigger = 0.0f;
			spells[0].attackstoptimer = 7000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Salve_d_acide);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 17.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 50.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Salve_d_acide_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 17.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 50.0f;
		}
		
		Peau = false;
	}
    
    void OnCombatStart(Unit * mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Peau = false;
			
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
		if((_unit->GetHealthPct() <= 15) && !Peau)
		{
			_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
			Peau = true;
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
		bool Peau;
		int nrspells;
};

// Mob
#define Géant_raccommodé	16025
// Sort
#define Rage_irrésistible	54356
#define Repousser			28405

class Géant_raccommodéAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Géant_raccommodéAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Géant_raccommodéAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Rage_irrésistible);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Repousser);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 25;
		spells[1].perctrigger = 10.0f;
		spells[1].attackstoptimer = 1000;
		
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
		if((_unit->GetHealthPct() <= 22) && !Rage)
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
		bool Rage;
		int nrspells;
};

// Mob
#define Gelée_d_égout		16375
// Sort
#define Nuée_maléfique		28156

class Gelée_d_égoutAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Gelée_d_égoutAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Gelée_d_égoutAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Nuée_maléfique);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
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
		_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
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
#define Gelée_d_embaumement		16024
// Sort
#define Nuage_d_embaumement		28322

class Gelée_d_embaumementAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Gelée_d_embaumementAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Gelée_d_embaumementAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Nuage_d_embaumement);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
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
		_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
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
#define Golem_recousu			16017
// Sort
#define Choc_martial			27758
#define Choc_martial_Heroic		56427
#define Enchaînement_GR			27794
#define Exécution				7160
#define Exécution_Heroic		56426
#define Nuée_maléfique_GR		27793

class Golem_recousuAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Golem_recousuAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Golem_recousuAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Choc_martial);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Choc_martial_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Enchaînement_GR);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 15;
		spells[1].perctrigger = 18.0f;
		spells[1].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Exécution);
			spells[2].targettype = TARGET_ATTACKING;
			spells[2].instant = true;
			spells[2].cooldown = 45;
			spells[2].perctrigger = 5.0f;
			spells[2].attackstoptimer = 1000;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Exécution_Heroic);
			spells[2].targettype = TARGET_ATTACKING;
			spells[2].instant = true;
			spells[2].cooldown = 45;
			spells[2].perctrigger = 5.0f;
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
#define Goule_infectieuse			16244
// Sort
#define Frénésie_GI					54701
#define Pourfendre					54703
#define Pourfendre_Heroic			54708
#define Putréfaction_de_la_chair	29915

class Goule_infectieuseAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Goule_infectieuseAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Goule_infectieuseAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		
		spells[0].info = dbcSpell.LookupEntry(Frénésie_GI);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 120;
		spells[0].perctrigger = 5.0f;
		spells[0].attackstoptimer = 1000;
	
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Pourfendre);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 2500;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Pourfendre_Heroic);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 2500;
		}
		
		spells[2].info = dbcSpell.LookupEntry(Putréfaction_de_la_chair);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = 15;
		spells[2].perctrigger = 10.0f;
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
#define Guerrier_pestiféré	16984
// Sort
#define Enchaînement_GP		15496

class Guerrier_pestiféréAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Guerrier_pestiféréAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Guerrier_pestiféréAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Enchaînement_GP);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 13.8f;
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
#define Guerrier_touché_par_l_obscurité		16156
// Sort
#define Tourbillon_GTPO						55266

class Guerrier_touché_par_l_obscuritéAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Guerrier_touché_par_l_obscuritéAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Guerrier_touché_par_l_obscuritéAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Tourbillon_GTPO);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 35;
		spells[0].perctrigger = 10.0f;
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
#define Hache_impie			16194
// Sort
#define	Frappe_mortelle_HI	16856
#define Tourbillon_HI		41057

class Hache_impieAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Hache_impieAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Hache_impieAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Frappe_mortelle_HI);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 20.0f;
		spells[0].attackstoptimer = 1000;
			
		spells[1].info = dbcSpell.LookupEntry(Tourbillon_HI);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 40;
		spells[1].perctrigger = 10.0f;
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
#define Horreur_des_tombes						15979
// Sort
#define Essaim_de_scarabées_des_cryptes			54313
#define Essaim_de_scarabées_des_cryptes_Heroic	54317
#define Scarabées_des_cryptes					54311

class Horreur_des_tombesAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Horreur_des_tombesAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Horreur_des_tombesAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Essaim_de_scarabées_des_cryptes);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = 45;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 3000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Essaim_de_scarabées_des_cryptes_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = 45;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 3000;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Scarabées_des_cryptes);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 55;
		spells[1].perctrigger = 10.0f;
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
#define Jeune_araignée_de_Maexxna		17055
// Sort
#define Poison_nécrotique_JAM			54121
#define Poison_nécrotique_Heroic_JAM	28776

class Jeune_araignée_de_MaexxnaAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Jeune_araignée_de_MaexxnaAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Jeune_araignée_de_MaexxnaAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Poison_nécrotique_JAM);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Poison_nécrotique_Heroic_JAM);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 15.0f;
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
#define Jeune_recrue_spectrale			16127
// Sort
#define Explosion_des_arcanes_JRP		27989
#define Explosion_des_arcanes_Heroic_JRP	56407

class Jeune_recrue_spectraleAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Jeune_recrue_spectraleAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Jeune_recrue_spectraleAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_des_arcanes);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 35;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_des_arcanes_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 35;
			spells[0].perctrigger = 10.0f;
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
#define Jeune_recrue_tenace		16124
// Sort
#define Peste_mortelle			55604
#define Peste_mortelle_Heroic	55645

class Jeune_recrue_tenaceAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Jeune_recrue_tenaceAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Jeune_recrue_tenaceAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Peste_mortelle);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Peste_mortelle_Heroic);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 10.0f;
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
#define Larve_mutante				16297
// Sort
#define Explosion_de_gelée			30109
#define Explosion_de_gelée_Heroic	54769

class Larve_mutanteAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Larve_mutanteAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Larve_mutanteAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_de_gelée_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_de_gelée);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 25;
			spells[0].perctrigger = 15.0f;
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
#define Monstruosité_vivante		16021
// Sort
#define Chaîne_d_éclairs			28293
#define Chaîne_d_éclairs_Heroic		54334
#define Totem_de_foudre				28294

class Monstruosité_vivanteAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Monstruosité_vivanteAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Monstruosité_vivanteAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Chaîne_d_éclairs);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 45.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Chaîne_d_éclairs_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 45.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Totem_de_foudre);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = false;
		spells[1].cooldown = 90;
		spells[1].perctrigger = 10.0f;
		spells[1].attackstoptimer = 500;
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
#define Nécrochevalier				16165
// Sort
#define Cône_de_froid				30095
#define Choc_de_flammes				30091
#define Explosion_des_arcanes_NR	15453
#define Nova_de_givre_NR			30094
#define Transfert_NR				28391
#define Vague_explosive				30092

class NécrochevalierAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(NécrochevalierAI);
	SP_AI_Spell spells[6];
	bool m_spellcheck[6];

    NécrochevalierAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 6;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Cône_de_froid);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 20;
		spells[0].perctrigger = 20.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Choc_de_flammes);
		spells[1].targettype = TARGET_RANDOM_DESTINATION;
		spells[1].instant = false;
		spells[1].cooldown = 35;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 2000;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 30.0f;
		
		spells[2].info = dbcSpell.LookupEntry(Explosion_des_arcanes_NR);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = false;
		spells[2].cooldown = 15;
		spells[2].perctrigger = 19.0f;
		spells[2].attackstoptimer = 1500;
		
		spells[3].info = dbcSpell.LookupEntry(Nova_de_givre_NR);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = 22;
		spells[3].perctrigger = 18.0f;
		spells[3].attackstoptimer = 1000;
		
		spells[4].info = dbcSpell.LookupEntry(Transfert_NR);
		spells[4].targettype = TARGET_SELF;
		spells[4].instant = true;
		spells[4].cooldown = 240;
		spells[4].perctrigger = 5.0f;
		spells[4].attackstoptimer = 1000;
		
		spells[5].info = dbcSpell.LookupEntry(Vague_explosive);
		spells[5].targettype = TARGET_SELF;
		spells[5].instant = true;
		spells[5].cooldown = 25;
		spells[5].perctrigger = 17.0f;
		spells[5].attackstoptimer = 1000;
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
#define Oeil_pédonculé			16236
// Sort
#define Fouet_mental_OP			29407
#define Fouet_mental_Heroic_OP	54805

class Oeil_pédonculéAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Oeil_pédonculéAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Oeil_pédonculéAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		_unit->Root();
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Fouet_mental_OP);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 6000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 35.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Fouet_mental_Heroic_OP);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 6000;
			spells[0].mindist2cast = 0.0f;
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
#define Ombre_de_Naxxramas						16164
// Sort
#define Salve_de_Traits_de_l_ombre_ODN			28407
#define Salve_de_Traits_de_l_ombre_Heroic_ODN	55323
#define Portail_des_ombres						28383

class Ombre_de_NaxxramasAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Ombre_de_NaxxramasAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Ombre_de_NaxxramasAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Salve_de_Traits_de_l_ombre_ODN);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Salve_de_Traits_de_l_ombre_Heroic_ODN);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Portail_des_ombres);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 90;
		spells[1].perctrigger = 5.0f;
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
#define Ombre_vigilante							30085
// Sort
#define Salve_de_Traits_de_l_ombre_OV			55850
#define Salve_de_Traits_de_l_ombre_Heroic_OV	55851

class Ombre_vigilanteAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Ombre_vigilanteAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Ombre_vigilanteAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Salve_de_Traits_de_l_ombre_OV);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Salve_de_Traits_de_l_ombre_Heroic_OV);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1000;
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
#define Rampant_de_l_effroi			15974
// Sort
#define Voile_de_l_ombre			53803
#define Voile_de_l_ombre_Heroic		28440

class Rampant_de_l_effroiAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Rampant_de_l_effroiAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Rampant_de_l_effroiAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Voile_de_l_ombre);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 20.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Voile_de_l_ombre_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 10.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 20.0f;
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
#define Saccageur_des_cryptes	15978
// Sort
#define Enchaînement_SDC		40504
#define Frénésie_SDC			56625	

class Saccageur_des_cryptesAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Saccageur_des_cryptesAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Saccageur_des_cryptesAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Enchaînement_SDC);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 15.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Frénésie_SDC);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 240;
		spells[1].perctrigger = 5.0f;
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
#define Sectateur_de_Naxxramas		15980
// Sort
#define Explosion_d_ombre			53850
#define Explosion_d_ombre_Heroic	53851

class Sectateur_de_NaxxramasAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Sectateur_de_NaxxramasAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Sectateur_de_NaxxramasAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_d_ombre);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Explosion_d_ombre_Heroic);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
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
#define	Suivant_de_Naxxramas	16505
// Sort
#define Silence					54093

class Suivant_de_NaxxramasAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Suivant_de_NaxxramasAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Suivant_de_NaxxramasAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		spells[0].info = dbcSpell.LookupEntry(Silence);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 45;
		spells[0].perctrigger = 10.0f;
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
#define Tisse_charogne			15975
// Sort
#define	Jet_de_poison			30043
#define	Jet_de_poison_Heroic	56032
#define Toile_d_araignée		28434

class Tisse_charogneAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Tisse_charogneAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Tisse_charogneAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Jet_de_poison);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 17.8f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Jet_de_poison_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 17.8f;
			spells[0].attackstoptimer = 1000;
		}

		spells[1].info = dbcSpell.LookupEntry(Toile_d_araignée);
		spells[1].targettype = TARGET_RANDOM_SINGLE;
		spells[1].instant = true;
		spells[1].cooldown = 15;
		spells[1].perctrigger = 10.0f;
		spells[1].attackstoptimer = 1000;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 45.0f;
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

//Mob
#define Vomisseur_de_bile		16018
// Sort
#define	Vomi_bilieux			27807
#define	Vomi_bilieux_Heroic		54326

class Vomisseur_de_bileAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Vomisseur_de_bileAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Vomisseur_de_bileAI(Creature * pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
			spells[i].speech = 0;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Vomi_bilieux);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 14.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 20.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Vomi_bilieux_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 14.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 20.0f;
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

void Naxxramas(ScriptMgr * mgr)
{
	// Boss
	mgr->register_creature_script(Anub_Rekhan,				 				&Anub_RekhanAI::Create);
	mgr->register_creature_script(Baron_Vaillefendre,		 				&Baron_VaillefendreAI::Create);
	mgr->register_creature_script(Dame_Blaumeux,			 				&Dame_BlaumeuxAI::Create);
	mgr->register_creature_script(Gluth,					 				&GluthAI::Create);
	mgr->register_creature_script(Gothik_le_Moissonneur,	 				&Gothik_le_MoissonneurAI::Create);
	mgr->register_creature_script(Feugen,					 				&FeugenAI::Create);
	mgr->register_creature_script(Grande_veuve_Faerlina,	 				&Grande_veuve_FaerlinaAI::Create);
	mgr->register_creature_script(Grobbulus,				 				&GrobbulusAI::Create);
	mgr->register_creature_script(Horreb,					 				&HorrebAI::Create);
	mgr->register_creature_script(Instructeur_Razuvious,	 				&Instructeur_RazuviousAI::Create);
	mgr->register_creature_script(Kel_Thuzad,				 				&Kel_ThuzadAI::Create);
	mgr->register_creature_script(Le_Recousu,				 				&Le_RecousuAI::Create);
	mgr->register_creature_script(Maexxna,					 				&MaexxnaAI::Create);
	mgr->register_creature_script(Noth_le_Porte_peste,		 				&Noth_le_Porte_pesteAI::Create);
	mgr->register_creature_script(Saphiron,					 				&SaphironAI::Create);
	mgr->register_creature_script(Sire_Zeliek,				 				&Sire_ZeliekAI::Create);
	mgr->register_creature_script(Stalagg,					 				&StalaggAI::Create);
	mgr->register_creature_script(Thane_Korth_azz,			 				&Thane_Korth_azzAI::Create);
	// Add Boss
	mgr->register_gameobject_script(Bloc_de_Glace,			 				&Bloc_de_GlaceAI::Create);
	mgr->register_creature_script(Bombe_de_givre_de_Saphiron, 				&Bombe_de_givre_de_SaphironAI::Create);
	mgr->register_creature_script(Declencheur_Coup_d_aile_de_Saphiron,	 	&Declencheur_Coup_d_aile_de_SaphironAI::Create);
	mgr->register_creature_script(Declencheur_Transir,				 		&Declencheur_TransirAI::Create);
	mgr->register_creature_script(Croq_zombie,						 		&Croq_zombieAI::Create);
	mgr->register_creature_script(Nuage_de_Grobbulus, 						&Nuage_de_GrobbulusAI::Create);
	mgr->register_creature_script(Roi_liche,		 						&Roi_licheAI::Create);
	mgr->register_creature_script(Spore,				 					&SporeAI::Create);
	// Mobs
	mgr->register_creature_script(Abomination_irrésistible, 				&Abomination_irrésistibleAI::Create);
	mgr->register_creature_script(Acolyte_de_Naxxramas, 					&Acolyte_de_NaxxramasAI::Create);
	mgr->register_creature_script(Adorateur_de_Naxxramas, 					&Adorateur_de_NaxxramasAI::Create);
	mgr->register_creature_script(Assemblage_osseux, 						&Assemblage_osseuxAI::Create);
	mgr->register_creature_script(Assemblage_pestiféré, 					&Assemblage_pestiféréAI::Create);
	mgr->register_creature_script(Assistant_en_chirurgie, 					&Assistant_en_chirurgieAI::Create);
	mgr->register_creature_script(Bâton_impie, 								&Bâton_impieAI::Create);
	mgr->register_creature_script(Bête_de_peste, 							&Bête_de_pesteAI::Create);
	mgr->register_creature_script(Capitaine_des_chevaliers_de_la_mort, 		&Capitaine_des_chevaliers_de_la_mortAI::Create);
	mgr->register_creature_script(Cavalier_de_la_mort, 						&Cavalier_de_la_mortAI::Create);
	mgr->register_creature_script(Cavalier_spectral, 						&Cavalier_spectralAI::Create);
	mgr->register_creature_script(Cavalier_tenace, 							&Cavalier_tenaceAI::Create);
	mgr->register_creature_script(Champion_pestiféré, 						&Champion_pestiféréAI::Create);
	mgr->register_creature_script(Chauve_souris_pesteuse, 					&Chauve_souris_pesteuseAI::Create);
	mgr->register_creature_script(Cheval_spectral, 							&Cheval_spectralAI::Create);
	mgr->register_creature_script(Chevalier_de_la_mort, 					&Chevalier_de_la_mortAI::Create);
	mgr->register_creature_script(Chevalier_de_la_mort_spectral, 			&Chevalier_de_la_mort_spectralAI::Create);
	mgr->register_creature_script(Chevalier_de_la_mort_tenace, 				&Chevalier_de_la_mort_tenaceAI::Create);
	mgr->register_creature_script(Colosse_raccommodé, 						&Colosse_raccommodéAI::Create);
	mgr->register_creature_script(Crache_vase, 								&Crache_vaseAI::Create);
	mgr->register_creature_script(Doublure_de_chevalier_de_la_mort, 		&Doublure_de_chevalier_de_la_mortAI::Create);
	mgr->register_creature_script(Ecuyer_ressuscité, 						&Ecuyer_ressuscitéAI::Create);
	mgr->register_creature_script(Epées_impies, 							&Epées_impiesAI::Create);
	mgr->register_creature_script(Forgeron_squelettique, 					&Forgeron_squelettiqueAI::Create);
	mgr->register_creature_script(Gardien_de_la_Couronne_de_glace, 			&Gardien_de_la_Couronne_de_glaceAI::Create);
	mgr->register_creature_script(Gardien_des_cryptes, 						&Gardien_des_cryptesAI::Create);
	mgr->register_creature_script(Gardien_pestiféré, 						&Gardien_pestiféréAI::Create);
	mgr->register_creature_script(Gargouille_peau_de_pierre, 				&Gargouille_peau_de_pierreAI::Create);
	mgr->register_creature_script(Géant_raccommodé, 						&Géant_raccommodéAI::Create);
	mgr->register_creature_script(Gelée_d_égout, 							&Gelée_d_égoutAI::Create);
	mgr->register_creature_script(Gelée_d_embaumement,						&Gelée_d_embaumementAI::Create);
	mgr->register_creature_script(Golem_recousu, 							&Golem_recousuAI::Create);
	mgr->register_creature_script(Goule_infectieuse, 						&Goule_infectieuseAI::Create);
	mgr->register_creature_script(Guerrier_pestiféré, 						&Guerrier_pestiféréAI::Create);
	mgr->register_creature_script(Guerrier_touché_par_l_obscurité, 			&Guerrier_touché_par_l_obscuritéAI::Create);
	mgr->register_creature_script(Hache_impie, 								&Hache_impieAI::Create);
	mgr->register_creature_script(Horreur_des_tombes, 						&Horreur_des_tombesAI::Create);
	mgr->register_creature_script(Jeune_araignée_de_Maexxna, 				&Jeune_araignée_de_MaexxnaAI::Create);
	mgr->register_creature_script(Jeune_recrue_spectrale, 					&Jeune_recrue_spectraleAI::Create);
	mgr->register_creature_script(Jeune_recrue_tenace, 						&Jeune_recrue_tenaceAI::Create);
	mgr->register_creature_script(Larve_mutante, 							&Larve_mutanteAI::Create);
	mgr->register_creature_script(Monstruosité_vivante, 					&Monstruosité_vivanteAI::Create);
	mgr->register_creature_script(Nécrochevalier, 							&NécrochevalierAI::Create);
	mgr->register_creature_script(Oeil_pédonculé, 							&Oeil_pédonculéAI::Create);
	mgr->register_creature_script(Ombre_de_Naxxramas, 						&Ombre_de_NaxxramasAI::Create);
	mgr->register_creature_script(Ombre_vigilante, 							&Ombre_vigilanteAI::Create);
	mgr->register_creature_script(Rampant_de_l_effroi, 						&Rampant_de_l_effroiAI::Create);
	mgr->register_creature_script(Saccageur_des_cryptes, 					&Saccageur_des_cryptesAI::Create);
	mgr->register_creature_script(Sectateur_de_Naxxramas, 					&Sectateur_de_NaxxramasAI::Create);
	mgr->register_creature_script(Suivant_de_Naxxramas, 					&Suivant_de_NaxxramasAI::Create);
	mgr->register_creature_script(Tisse_charogne, 							&Tisse_charogneAI::Create);
	mgr->register_creature_script(Vomisseur_de_bile, 						&Vomisseur_de_bileAI::Create);
}