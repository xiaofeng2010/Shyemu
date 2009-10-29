#include "StdAfx.h"
#include "Setup.h"

/** Gossip (2)

**/

struct Coordonnée
{
    float x;
    float y;
    float z;
    float o;
};

static Coordonnée Sjonnir[] = 
{
	{  },
	{ 1059.721191f, 480.520538f, 207.723892f, 2.566766f },
	{ 1049.576660f, 514.748047f, 207.734283f, 1.859903f },
	{ 1048.814087f, 562.703613f, 207.413788f, 1.572447f },
	{ 1048.608521f, 635.325928f, 207.719559f, 1.576374f },
	{ 1049.187988f, 659.849060f, 201.671661f, 1.438935f },
	{ 1103.240234f, 666.519897f, 202.871002f, 6.265206f },
	{ 1122.709961f, 667.350464f, 196.235107f, 6.183521f },
	{ 1127.323730f, 644.125427f, 196.235107f, 5.478230f },
	{ 1154.118408f, 632.638916f, 196.235107f, 5.933751f },
	{ 1179.958496f, 641.113220f, 196.236359f, 0.358209f },
	{ 1188.749634f, 667.176453f, 196.236359f, 6.276154f },
	{ 1201.824219f, 667.187744f, 196.241058f, 0.005564f },
	{ 1229.495117f, 667.036438f, 189.607986f, 6.246272f },
	{ 1256.142578f, 666.936768f, 189.608154f, -0.004620f },
	{ 1308.129883f, 666.817749f, 189.608154f, 2.884834f }
};

#define Brann_Barbe_de_bronze	28070
#define Marche_Event			0
 
class SCRIPT_DECL Brann_Barbe_de_bronzeGossip : public GossipScript
{
public:
    void GossipHello(ObjectPointer pObject, PlayerPointer plr, bool AutoSend)
    {
        GossipMenu *Menu;
		CreaturePointer Brann = NULLCREATURE;
		Brann = (pObject->GetTypeId()==TYPEID_UNIT)?TO_CREATURE(pObject):NULLCREATURE;

		if (Brann == NULL)
			return;

		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 229901, plr);
		Menu->AddItem( 0, "Vers La Forge des volontés", 1);
		 
		if(AutoSend)
			Menu->SendTo(plr);
    }
 
	void GossipSelectOption(ObjectPointer pObject, PlayerPointer plr, uint32 Id, uint32 IntId, const char * EnteredCode)
    {
		CreaturePointer Brann = NULLCREATURE;
		Brann = (pObject->GetTypeId()==TYPEID_UNIT)?TO_CREATURE(pObject):NULLCREATURE;
		
		if (Brann == NULL)
			return;

		switch (IntId)
		{
		case 0:
			GossipHello(pObject, plr, true);
			break;
		case 1:
			Brann->SetUInt32Value(UNIT_NPC_FLAGS, 0);

			Brann->GetAIInterface()->StopMovement(0);
			Brann->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
			Brann->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			Brann->GetAIInterface()->setWaypointToMove(1);
			break;
		}
	}
 
    void Destroy()
    {
        delete this;
    }
};

class Brann_Barbe_de_bronzeAI : public CreatureAIScript
{
public:
	friend class Brann_Barbe_de_bronzeGossip;

    ADD_CREATURE_FACTORY_FUNCTION(Brann_Barbe_de_bronzeAI);
    Brann_Barbe_de_bronzeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		for (int i = 1; i < 16; i++)
		{
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(i, 0, Marche_Event));
		}

		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_9);
		_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);

		EventChapter = 0;
		EventTimer = 0;
	}
    
	void AIUpdate()
	{
		switch (EventChapter)
		{
		case 0:
			Event_Sjonnir();
			break;
		}
	}

	void Event_Sjonnir()
	{
		if (_unit->GetAIInterface()->getCurrentWaypoint() == 12 && EventTimer > 0)
		{
			GameObjectPointer Porte = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(1206.56f, 666.977f, 197.738f, 191296);
		
			switch (EventTimer)
			{
				case 2:
				{
					_unit->Emote(EMOTE_ONESHOT_USESTANDING);
					break;
				}
		
				case 6:
				{
					Porte->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
					break;
				}
				
				case 8:
				{
					_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
					_unit->GetAIInterface()->setWaypointToMove(13);
					EventTimer = 1;
					break;
				}
			}

			EventTimer++;
		}

		if(_unit->GetAIInterface()->getCurrentWaypoint() == 14 && EventTimer > 0)
		{
			EventTimer++;
			switch (EventTimer)
			{
				case 10:
				{
					_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
					_unit->GetAIInterface()->setWaypointToMove(15);
					EventTimer = 1;
					break;
				}
			}
		}

		if(_unit->GetAIInterface()->getCurrentWaypoint() == 15 && EventTimer > 0)
		{
			EventTimer++;
			switch (EventTimer)
			{
				case 2:
				{
					_unit->SetFacing(3.057555f);
					_unit->SetUInt32Value(UNIT_NPC_FLAGS, 2);
					EventTimer = 0;
					break;
				}
			}
		}
	}

    void OnReachWP(uint32 iWaypointId, bool bForwards)
    {
		switch (iWaypointId)
		{
			case 12:
			case 14:
			case 15:
			case 16:
				RegisterAIUpdateEvent(1000);
				EventTimer = 1;
				break;
			default:
			{
				_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
				_unit->GetAIInterface()->setWaypointToMove(iWaypointId+1);
			}
		}
    }

    inline WayPoint* CreateWaypoint(int id, uint32 waittime, uint32 flags)
    {
        WayPoint * wp = _unit->CreateWaypointStruct();
        wp->id = id;
        wp->x = Sjonnir[id].x;
        wp->y = Sjonnir[id].y;
        wp->z = Sjonnir[id].z;
        wp->o = Sjonnir[id].o;
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
		uint32 EventChapter;
		uint32 EventTimer;
		CreaturePointer Sjonnir_Sculptefer;
};

/** Boss (3)

	Damoiselle de peine
	Krystallus
	Sjonnir le Sculptefer

**/
// Mob
#define Damoiselle_de_peine					27975
// Sort
#define Chagrin_de_la_séparation_Heroic		59723
#define Horion_de_chagrin					50760
#define Horion_de_chagrin_Heroic			59726
#define Pilier_de_malheur_Heroic			59727
#define Tempête_de_peine					50752
#define Tempête_de_peine_Heroic				59772

class Damoiselle_de_peineAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Damoiselle_de_peineAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    Damoiselle_de_peineAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode == MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Chagrin_de_la_séparation_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 2000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
			spells[0].speech = "Tellement de temps perdu... que vous ne retrouverez jamais!";
			spells[0].soundid = 13492;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Horion_de_chagrin);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 4000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Horion_de_chagrin_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 4000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode == MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Pilier_de_malheur_Heroic);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = false;
			spells[2].cooldown = 15;
			spells[2].perctrigger = 30.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 50.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[3].info = dbcSpell.LookupEntry(Tempête_de_peine);
			spells[3].targettype = TARGET_ATTACKING;
			spells[3].instant = true;
			spells[3].cooldown = 15;
			spells[3].perctrigger = 45.0f;
			spells[3].attackstoptimer = 1000;
		}
		else
		{
			spells[3].info = dbcSpell.LookupEntry(Tempête_de_peine);
			spells[3].targettype = TARGET_ATTACKING;
			spells[3].instant = true;
			spells[3].cooldown = 15;
			spells[3].perctrigger = 45.0f;
			spells[3].attackstoptimer = 1000;
		}
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;

		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Vous n'auriez pas du venir... vous allez mourir!");
		_unit->PlaySoundToSet(13487);
    }

	void OnTargetDied(UnitPointer mTarget)
    {
		int RandomSpeach = RandomUInt(4);
		switch (RandomSpeach)
		{
			case 0:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Pourquoi ça doit finir comme ça?");
				_unit->PlaySoundToSet(13488);
				break;
				
			case 1:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Vous l'avez bien mérité!");
				_unit->PlaySoundToSet(13489);
				break;

			case 2:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Mon fardeau deviens si lourd.");
				_unit->PlaySoundToSet(13490);
				break;
				
			case 3:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "C'est de votre faute!");
				_unit->PlaySoundToSet(13491);
				break;
		}
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
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Puissiez vous tous pourrir! Jamais... je n'est voulue... ça.");
		_unit->PlaySoundToSet(13493);
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

// Boss
#define Krystallus					27977
// Sort
#define Lancer_de_rocher			50843
#define Lancer_de_rocher_Heroic 	59742
#define Piétinement					50868
#define Piétinement_Heroic			59744
#define Pointe_terrestre			59750

class KrystallusAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(KrystallusAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    KrystallusAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Lancer_de_rocher);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 35.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 50.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Lancer_de_rocher_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 35.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 50.0f;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Piétinement);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Piétinement_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode == MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Pointe_terrestre);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 100.0f;
		}
    }
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;

		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Ecraser...");
		_unit->PlaySoundToSet(14176);
    }

	void OnTargetDied(UnitPointer mTarget)
    {
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Ha...ha...ha...ha... ");
		_unit->PlaySoundToSet(14177);
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
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Uuuuhhhhhhhhhh....... ");
		_unit->PlaySoundToSet(14179);
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

// Boss
#define Sjonnir_le_Sculptefer		27978
// Sort
#define Anneau_de_foudre			51849
#define Anneau_de_foudre_Heroic		59861
#define Bouclier_de_foudre			50831
#define Bouclier_de_foudre_Heroic	59845
#define Chaîne_d_éclairs			50830
#define Chaîne_d_éclairs_heroic		59844

class Sjonnir_le_SculpteferAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Sjonnir_le_SculpteferAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    Sjonnir_le_SculpteferAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Anneau_de_foudre);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = 45;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 10000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Anneau_de_foudre_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = 45;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 10000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Bouclier_de_foudre);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 240;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Bouclier_de_foudre_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 240;
			spells[1].perctrigger = 15.0f;
			spells[1].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[2].info = dbcSpell.LookupEntry(Chaîne_d_éclairs);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = true;
			spells[2].cooldown = 15;
			spells[2].perctrigger = 35.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 30.0f;
		}
		else
		{
			spells[2].info = dbcSpell.LookupEntry(Chaîne_d_éclairs_heroic);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = true;
			spells[2].cooldown = 15;
			spells[2].perctrigger = 35.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 30.0f;
		}
		
		Cooldown_Limon = 5;
		Cooldown_Trogg = 15;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Cooldown_Limon = 5;
		Cooldown_Trogg = 15;

		Nain1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(27982, 1284.619385f, 645.040222f, 189.607819f, 1.705882f, true, false, 0, 0);
		Nain1->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(1284.619385f, 645.040222f, 189.607819f, 27982);
		Nain1->GetAIInterface()->MoveTo(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
				
		Nain2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(27982, 1283.328369f, 688.416748f, 189.607819f, 4.345609f, true, false, 0, 0);
		Nain2->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(1283.328369f, 688.416748f, 189.607819f, 27982);
		Nain2->GetAIInterface()->MoveTo(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
		
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Des enveloppes frêles et vulnérables. Des vies fragiles et brève. Vous n'échapperez pas à la malédiction de la chair!");
		_unit->PlaySoundToSet(14180);
    }

	void OnTargetDied(UnitPointer mTarget)
    {
		int RandomSpeach = RandomUInt(3);
		switch (RandomSpeach)
		{
			case 0:
				_unit->PlaySoundToSet(14181);
				break;
				
			case 1:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "La chair ne vaut rien face au fer!");
				_unit->PlaySoundToSet(14182);
				break;

			case 2:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Les armées du fer vont étrangler le monde!");
				_unit->PlaySoundToSet(14183);
				break;
		}
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
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Loken ne connaitra pas le repos, tant que la forge ne sera pas reprise. Vous ni changerez rien!");
		_unit->PlaySoundToSet(14184);
		RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		if(_unit->GetHealthPct() <= 35)
		{
			if (Cooldown_Limon < 1)
			{
				int RandomSpawn = RandomUInt(2);
				switch (RandomSpawn)
				{
					case 1:
					{
						Limon1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(27981, 1292.266846f, 718.395813f, 196.552658f, 4.637781f, true, false, 0, 0);
						Limon1->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(1292.266846f, 718.395813f, 196.552658f, 27981);
						Limon1->GetAIInterface()->MoveTo(1293.996094f, 667.162354f, 189.607881f, 4.577306f);
						
						Limon2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(27981, 1295.038940f, 718.445679f, 196.552658f, 4.761088f, true, false, 0, 0);
						Limon2->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(1295.038940f, 718.445679f, 196.552658f, 27981);
						Limon2->GetAIInterface()->MoveTo(1293.996094f, 667.162354f, 189.607881f, 4.577306f);
					
						Cooldown_Limon = 5;
						break;
					}
				
					case 2:
					{
						Limon1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(27981, 1292.877563f, 615.450439f, 196.552826f, 1.4119220f, true, false, 0, 0);
						Limon1->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(1292.877563f, 615.450439f, 196.552826f, 27981);
						Limon1->GetAIInterface()->MoveTo(1293.894775f, 666.817749f, 189.607758f, 1.587293f);
					
						Limon2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(27981, 1294.611572f, 615.466858f, 196.552826f, 1.552735f, true, false, 0, 0);
						Limon2->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(1294.611572f, 615.466858f, 196.552826f, 27981);
						Limon2->GetAIInterface()->MoveTo(1293.894775f, 666.817749f, 189.607758f, 1.587293f);
				
						Cooldown_Limon = 5;
						break;
					}
				}
			}	
			else if(Cooldown_Trogg < 1)
			{
				int RandomSpawn = RandomUInt(2);
				switch (RandomSpawn)
				{
					case 1:
					{
						Trogg = _unit->GetMapMgr()->GetInterface()->SpawnCreature(27979, 1294.740723f, 691.246948f, 189.833557f, 4.694327f, true, false, 0, 0);
						Trogg->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(1294.740723f, 691.246948f, 189.833557f, 27979);
						Trogg->GetAIInterface()->MoveTo(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
					
						Cooldown_Trogg = 15;
						break;
					}
				
					case 2:
					{
						Trogg = _unit->GetMapMgr()->GetInterface()->SpawnCreature(27979, 1294.802002f, 642.709534f, 189.823257f, 1.533885f, true, false, 0, 0);
						Trogg->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(1294.802002f, 642.709534f, 189.823257f, 27979);
						Trogg->GetAIInterface()->MoveTo(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
					
						Cooldown_Trogg = 15;
						break;
					}
				}
			}
			else
			{
				Cooldown_Limon--;
				Cooldown_Trogg--;
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
		uint32 Cooldown_Limon, Cooldown_Trogg;
		UnitPointer Nain1, Nain2, Limon1, Limon2, Trogg;
};

/** Mob (16)

	Assemblage de foudre
	Assemblage déchaîné
	Assemblage tenace
	Contrôleur sombre-rune
	Elémentaliste sombre-rune
	Géant sombre-rune
	Guerrier sombre-rune
	Mande-foudre sombre-rune
	Nain de fer forgé
	Ouvrier sombre-rune
	Protecteur golem de fer
	Protecteur sombre-rune
	Sculpteur sombre-rune
	Théurge sombre-rune
	Trogg de fer forgé
	Vase de fer

**/

// Mob
#define Assemblage_de_foudre			27972
// Sort 
#define Chaîne_d_éclairs_ADF			61528
#define Surcharge_électrique			52341	
#define Surcharge_électrique_Heroic		59038

class Assemblage_de_foudreAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Assemblage_de_foudreAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Assemblage_de_foudreAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Chaîne_d_éclairs_ADF);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 1500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Surcharge_électrique);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1500;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Surcharge_électrique_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = false;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 20.0f;
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
#define Assemblage_déchaîné					27970
// Sort
#define Convulsion_toute_puissante			51819
#define Convulsion_toute_puissante_Heroic	61514
#define Frappe_en_arc_de_cercle				28168

class Assemblage_déchaînéAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Assemblage_déchaînéAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Assemblage_déchaînéAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Convulsion_toute_puissante);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = -1;
			spells[0].perctrigger = 0.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Convulsion_toute_puissante_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = -1;
			spells[0].perctrigger = 0.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Frappe_en_arc_de_cercle);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 15;
		spells[1].perctrigger = 39.0f;
		spells[1].attackstoptimer = 1000;
		
		Convulsion = false;
	}
    
    void OnCombatStart(UnitPointer mTarget)
    {
		for (int i = 0; i < nrspells; i++)
			spells[i].casttime = 0;
			
		Convulsion = false;
			
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
		if((_unit->GetHealthPct() <= 25) && !Convulsion)
		{
			_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
			Convulsion = true;
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
		bool Convulsion;
		int nrspells;
};

// Mob
#define Assemblage_tenace			27971
// Sort
#define Court_circuit				51832
#define Court_circuit_Heroic		61513
#define Frappe_continuelle			51491
#define Frappe_continuelle_Heroic	59039

class Assemblage_tenaceAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Assemblage_tenaceAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Assemblage_tenaceAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Court_circuit);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 3000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Court_circuit_Heroic);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 25.0f;
			spells[0].attackstoptimer = 3000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Frappe_continuelle);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Frappe_continuelle_Heroic);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 1000;
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
#define Contrôleur_sombre_rune		27966
// Sort
#define Croissance_cristalline		51805
#define Invocation_d_un_éclaté		51507

class Contrôleur_sombre_runeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Contrôleur_sombre_runeAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Contrôleur_sombre_runeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Croissance_cristalline);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = false;
		spells[0].cooldown = 35;
		spells[0].perctrigger = 15.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Invocation_d_un_éclaté);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = 90;
		spells[1].perctrigger = 22.0f;
		spells[1].attackstoptimer = 2000;
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
#define Elémentaliste_sombre_rune			27962
// Sort
#define Bouclier_de_foudre_ESR				51776
#define Bouclier_de_foudre_Heroic_ESR		59025
#define Eclair								53314
#define Eclair_Heroic						59024
#define Hâte_des_arcanes					32693
#define Invocation_d_un_élémentaire_d_air	51475

class Elémentaliste_sombre_runeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Elémentaliste_sombre_runeAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    Elémentaliste_sombre_runeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Bouclier_de_foudre_ESR);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Bouclier_de_foudre_Heroic_ESR);
			spells[0].targettype = TARGET_SELF;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 20.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Eclair);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 15;
			spells[1].perctrigger = 35.0f;
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
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 40.0f;
		}
		
		spells[2].info = dbcSpell.LookupEntry(Hâte_des_arcanes);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = 20;
		spells[2].perctrigger = 10.0f;
		spells[2].attackstoptimer = 1000;
		
		spells[3].info = dbcSpell.LookupEntry(Invocation_d_un_élémentaire_d_air);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = false;
		spells[3].cooldown = 120;
		spells[3].perctrigger = 10.0f;
		spells[3].attackstoptimer = 1500;
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
#define Géant_sombre_rune		27969
// Sort
#define Piétinement_GSR			51493
#define Piétinement_Heroic_GSR	59026
#define Poing_de_fer			51494

class Géant_sombre_runeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Géant_sombre_runeAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Géant_sombre_runeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Piétinement);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 1000;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Piétinement_Heroic);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 30.0f;
			spells[0].attackstoptimer = 1000;
		}
		
		spells[1].info = dbcSpell.LookupEntry(Poing_de_fer);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = false;
		spells[1].cooldown = 40;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 2000;
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
#define Guerrier_sombre_rune	27960
// Sort
#define Enchaînement			42724
#define Frappe_héroïque			53395
#define Frappe_héroïque_heroic	59035

class Guerrier_sombre_runeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Guerrier_sombre_runeAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Guerrier_sombre_runeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
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
		spells[0].perctrigger = 20.0f;
		spells[0].attackstoptimer = 1000;
			
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Frappe_héroïque);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 10;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Frappe_héroïque_heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 10;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 1000;
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
#define Mande_foudre_sombre_rune	27984
// Sort
#define Eclair_MFSR					59863
#define Mot_de_l_ombre_Douleur		59864

class Mande_foudre_sombre_runeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Mande_foudre_sombre_runeAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Mande_foudre_sombre_runeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Eclair_MFSR);
		spells[0].targettype = TARGET_RANDOM_SINGLE;
		spells[0].instant = false;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 45.0f;
		spells[0].attackstoptimer = 3000;
		spells[0].mindist2cast = 0.0f;
		spells[0].maxdist2cast = 40.0f;
		
		spells[1].info = dbcSpell.LookupEntry(Mot_de_l_ombre_Douleur);
		spells[1].targettype = TARGET_RANDOM_SINGLE;
		spells[1].instant = true;
		spells[1].cooldown = 20;
		spells[1].perctrigger = 25.0f;
		spells[1].attackstoptimer = 1000;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 30.0f;
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
#define Nain_de_fer_forgé		27982
// Sort
#define Longe_éclair			50895
#define Longe_éclair_Heroic		59851

class Nain_de_fer_forgéAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Nain_de_fer_forgéAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Nain_de_fer_forgéAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Longe_éclair);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 40.0f;
			spells[0].attackstoptimer = 5000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 10.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Longe_éclair_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 10;
			spells[0].perctrigger = 40.0f;
			spells[0].attackstoptimer = 5000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 10.0f;
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
#define Ouvrier_sombre_rune		27961
// Sort
#define Colère_maussade			51499
#define Perce_armure			46202

class Ouvrier_sombre_runeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Ouvrier_sombre_runeAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Ouvrier_sombre_runeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Colère_maussade);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = 35;
		spells[0].perctrigger = 18.0f;
		spells[0].attackstoptimer = 1000;
		
		spells[1].info = dbcSpell.LookupEntry(Perce_armure);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = 10;
		spells[1].perctrigger = 35.0f;
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
#define Protecteur_golem_de_fer		27985
// Sort
#define Ecraser_armure				33661
#define Onde_de_choc				12734
#define Onde_de_choc_Heroic			59865

class Protecteur_golem_de_ferAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Protecteur_golem_de_ferAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Protecteur_golem_de_ferAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Ecraser_armure);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 38.0f;
		spells[0].attackstoptimer = 1000;
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Onde_de_choc);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1000;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Onde_de_choc_Heroic);
			spells[1].targettype = TARGET_SELF;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 20.0f;
			spells[1].attackstoptimer = 1000;
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

// MoB
#define Protecteur_sombre_rune		27983
// Sort
#define Enchaînement				42724

class Protecteur_sombre_runeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Protecteur_sombre_runeAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Protecteur_sombre_runeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(Enchaînement);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 15;
		spells[0].perctrigger = 35.0f;
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
#define Sculpteur_sombre_rune		27965
// Sort
#define Rayon_ciselant				51496
#define Rayon_ciselant_Heroic		59034

class Sculpteur_sombre_runeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Sculpteur_sombre_runeAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    Sculpteur_sombre_runeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Rayon_ciselant);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 38.0f;
			spells[0].attackstoptimer = 1500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Rayon_ciselant_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 38.0f;
			spells[0].attackstoptimer = 1500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;
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
#define Théurge_sombre_rune			27963
// Sort
#define Eclair_TSR					15801
#define Eclair_Heroic_TSR			35010
#define Fourche_d_éclairs			53167
#define Fourche_d_éclairs_Heroic	59152
#define Puissance_de_fer			51484

class Théurge_sombre_runeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Théurge_sombre_runeAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    Théurge_sombre_runeAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Eclair_TSR);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 55.0f;
			spells[0].attackstoptimer = 3000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Eclair_Heroic_TSR);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 55.0f;
			spells[0].attackstoptimer = 3000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;
		}
		
		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[1].info = dbcSpell.LookupEntry(Fourche_d_éclairs);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 30.0f;
		}
		else
		{
			spells[1].info = dbcSpell.LookupEntry(Fourche_d_éclairs_Heroic);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = false;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 35.0f;
			spells[1].attackstoptimer = 2000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 30.0f;
		}
		
		spells[2].info = dbcSpell.LookupEntry(Puissance_de_fer);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = 55;
		spells[2].perctrigger = 20.0f;
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
#define Trogg_de_fer_forgé			27979
// Sort
#define Horion_de_foudre			50900
#define Horion_de_foudre_Heroic		50900

class Trogg_de_fer_forgéAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Trogg_de_fer_forgéAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Trogg_de_fer_forgéAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Horion_de_foudre);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 40.0f;
			spells[0].attackstoptimer = 2500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 10.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Horion_de_foudre_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 40.0f;
			spells[0].attackstoptimer = 2500;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 10.0f;
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
		_unit->Despawn(0,0);
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
#define Vase_de_fer				28165
// Sort
#define Salve_toxique			50838
#define Salve_toxique_Heroic	59853

class Vase_de_ferAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(Vase_de_ferAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    Vase_de_ferAI(CreaturePointer pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		{
			spells[0].info = dbcSpell.LookupEntry(Salve_toxique);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 35.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 30.0f;
		}
		else
		{
			spells[0].info = dbcSpell.LookupEntry(Salve_toxique_Heroic);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 35.0f;
			spells[0].attackstoptimer = 1000;
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


void Ulduar_Les_salles_de_pierre(ScriptMgr * mgr)
{
	// Gossip
	GossipScript * BBDB = (GossipScript*) new Brann_Barbe_de_bronzeGossip();
	mgr->register_gossip_script(Brann_Barbe_de_bronze, BBDB);
	mgr->register_creature_script(Brann_Barbe_de_bronze, &Brann_Barbe_de_bronzeAI::Create);
	// Boss
	mgr->register_creature_script(Damoiselle_de_peine,			&Damoiselle_de_peineAI::Create);
	mgr->register_creature_script(Krystallus,					&KrystallusAI::Create);
	mgr->register_creature_script(Sjonnir_le_Sculptefer,		&Sjonnir_le_SculpteferAI::Create);
	// Mob
	mgr->register_creature_script(Assemblage_de_foudre,			&Assemblage_de_foudreAI::Create);
	mgr->register_creature_script(Assemblage_déchaîné,			&Assemblage_déchaînéAI::Create);
	mgr->register_creature_script(Assemblage_tenace,			&Assemblage_tenaceAI::Create);
	mgr->register_creature_script(Contrôleur_sombre_rune,		&Contrôleur_sombre_runeAI::Create);
	mgr->register_creature_script(Elémentaliste_sombre_rune,	&Elémentaliste_sombre_runeAI::Create);
	mgr->register_creature_script(Géant_sombre_rune,			&Géant_sombre_runeAI::Create);
	mgr->register_creature_script(Guerrier_sombre_rune,			&Guerrier_sombre_runeAI::Create);
	mgr->register_creature_script(Mande_foudre_sombre_rune,		&Mande_foudre_sombre_runeAI::Create);
	mgr->register_creature_script(Nain_de_fer_forgé,			&Nain_de_fer_forgéAI::Create);
	mgr->register_creature_script(Ouvrier_sombre_rune,			&Ouvrier_sombre_runeAI::Create);
	mgr->register_creature_script(Protecteur_golem_de_fer,		&Protecteur_golem_de_ferAI::Create);
	mgr->register_creature_script(Protecteur_sombre_rune,		&Protecteur_sombre_runeAI::Create);
	mgr->register_creature_script(Sculpteur_sombre_rune,		&Sculpteur_sombre_runeAI::Create);
	mgr->register_creature_script(Théurge_sombre_rune,			&Théurge_sombre_runeAI::Create);
	mgr->register_creature_script(Trogg_de_fer_forgé,			&Trogg_de_fer_forgéAI::Create);
	mgr->register_creature_script(Vase_de_fer,					&Vase_de_ferAI::Create);

}