/*
 * EternalCore MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008-2009 <http://www.shyemu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StdAfx.h"


static float AttackToRageConversionTable[PLAYER_LEVEL_CAP + 1]=
{
	0.0f,
	0.499999998893f,
	0.34874214056f,
	0.267397170992f,
	0.216594535676f,
	0.181852997475f,
	0.156596678244f,
	0.137408407814f,
	0.12233646474f,
	0.110185074062f,
	0.100180723915f,
	0.0918008940243f,
	0.084679891259f,
	0.0785541194583f,
	0.0732287738371f,
	0.0685567746212f,
	0.0644249954237f,
	0.0607450001819f,
	0.0574466557344f,
	0.0544736297718f,
	0.0517801553458f,
	0.0493286648502f,
	0.0470880325642f,
	0.0450322506478f,
	0.0431394187932f,
	0.0413909641335f,
	0.0397710324301f,
	0.0382660082118f,
	0.0368641330875f,
	0.035555199573f,
	0.0343303035574f,
	0.0331816427126f,
	0.0321023511953f,
	0.0310863632415f,
	0.0301282999279f,
	0.0292233746364f,
	0.0283673137143f,
	0.0275562895548f,
	0.0267868638875f,
	0.0260559395055f,
	0.0253607190016f,
	0.0246986693537f,
	0.0240674914139f,
	0.0234650935281f,
	0.0228895686471f,
	0.0223391744027f,
	0.0218123157088f,
	0.0213075295236f,
	0.0208234714647f,
	0.02035890402f,
	0.019912686137f,
	0.0194837640053f,
	0.0190711628769f,
	0.0186739797893f,
	0.0182913770778f,
	0.0179225765793f,
	0.0175668544424f,
	0.0172235364711f,
	0.0168919939405f,
	0.0165716398271f,
	0.0162619254091f,
	0.0159623371939f,
	0.0156723941359f,
	0.0153916451144f,
	0.0151196666436f,
	0.0148560607885f,
	0.0146004532678f,
	0.0143524917226f,
	0.0141118441351f,
	0.0138781973828f,
	0.0136512559131f,
#if PLAYER_LEVEL_CAP==80
	0.0136512559131f,
	0.0136512559131f,
	0.0136512559131f,
	0.0136512559131f,
	0.0136512559131f,
	0.0136512559131f,
	0.0136512559131f,
	0.0136512559131f,
	0.0136512559131f,
	0.0136512559131f,
#endif
};

Unit::Unit()
{
	int i;

	m_attackTimer = 0;
	m_attackTimer_1 = 0;
	m_dualWield = false;

	m_ignoreArmorPctMaceSpec = 0;
	m_ignoreArmorPct = 0;
	m_fearmodifiers = 0;
	m_state = 0;
	m_special_state = 0;
	m_deathState = ALIVE;
	m_currentSpell = NULL;
	m_meleespell = 0;
	m_addDmgOnce = 0;
	m_TotemSlots[0] = NULL;
	m_TotemSlots[1] = NULL;
	m_TotemSlots[2] = NULL;
	m_TotemSlots[3] = NULL;
	m_ObjectSlots[0] = 0;
	m_ObjectSlots[1] = 0;
	m_ObjectSlots[2] = 0;
	m_ObjectSlots[3] = 0;
	m_silenced = 0;
	disarmed   = false;

	//DK:modifiers
	PctRegenModifier = 0;
	for( i = 0; i < 4; i++ )
	{
		PctPowerRegenModifier[i] = 1;
	}
	m_speedModifier = 0;
	m_slowdown = 0;
	m_mountedspeedModifier=0;
	m_maxSpeed = 0;
	for( i = 0; i < 32 ; i++ )
	{
		MechanicsDispels[i] = 0;
		MechanicsResistancesPCT[i] = 0;
		ModDamageTakenByMechPCT[i] = 0;
	}

	//SM
	SM_FDamageBonus = 0;
	SM_PDamageBonus = 0;

	SM_FDur = 0;
	SM_PDur = 0;

	SM_FThreat = 0;
	SM_PThreat = 0;

	SM_FEffect1_Bonus = 0;
	SM_PEffect1_Bonus = 0;

	SM_FCharges = 0;
	SM_PCharges = 0;

	SM_FRange = 0;
	SM_PRange = 0;

	SM_FRadius = 0;
	SM_PRadius = 0;
		
	SM_CriticalChance = 0;

	SM_FMiscEffect = 0;
	SM_PMiscEffect = 0;
		
	SM_PNonInterrupt = 0;

	SM_FCastTime = 0;
	SM_PCastTime = 0;
		
	SM_FCooldownTime = 0;
	SM_PCooldownTime = 0;
		
	SM_FEffect2_Bonus = 0;
	SM_PEffect2_Bonus = 0;

	SM_FCost = 0;
	SM_PCost = 0;
		
	SM_PCriticalDamage = 0;

	SM_FHitchance = 0;

	SM_FAdditionalTargets = 0;

	SM_FChanceOfSuccess = 0;

	SM_FAmptitude = 0;
	SM_PAmptitude = 0;

	SM_PJumpReduce = 0;

	SM_FGlobalCooldown = 0;
	SM_PGlobalCooldown = 0;

	SM_FDOT = 0;
	SM_PDOT = 0;
		
	SM_FEffect3_Bonus = 0;
	SM_PEffect3_Bonus = 0;

	SM_FPenalty = 0;
	SM_PPenalty = 0;

	SM_FEffectBonus = 0;
	SM_PEffectBonus = 0;	
		
	SM_FRezist_dispell = 0;
	SM_PRezist_dispell = 0;

	m_pacified = 0;
	m_interruptRegen = 0;
	m_resistChance = 0;
	m_powerRegenPCT = 0;
	RAPvModifier=0;
	APvModifier=0;
	stalkedby=0;

	m_extraattacks = 0;
	m_stunned = 0;
	m_manashieldamt=0;
	m_rooted = 0;
	m_triggerSpell = 0;
	m_triggerDamage = 0;
	m_canMove = 0;
	m_noInterrupt = 0;
	m_modlanguage = -1;
	m_magnetcaster = 0;

	m_CombatResult_Dodge = 0;
	m_CombatResult_Parry = 0;

	critterPet = NULL;
	summonPet = NULL;

	m_useAI = false;
	for(i=0;i<10;i++)
	{
		dispels[i]=0;
		CreatureAttackPowerMod[i] = 0;
		CreatureRangedAttackPowerMod[i] = 0;
	}
	//REMIND:Update these if you make any changes
	CreatureAttackPowerMod[UNIT_TYPE_MISC] = 0;
	CreatureRangedAttackPowerMod[UNIT_TYPE_MISC] = 0;
	CreatureAttackPowerMod[11] = 0;
	CreatureRangedAttackPowerMod[11] = 0;

	m_invisibility = 0;
	m_invisible = false;
	m_invisFlag = INVIS_FLAG_NORMAL;
	m_mageInvisibility = false;

	for(i = 0; i < INVIS_FLAG_TOTAL; i++)
	{
		m_invisDetect[i] = 0;
	}

	m_stealthLevel = 0;
	m_stealthDetectBonus = 0;
	m_stealth = 0;
	m_can_stealth = true;

	for(i=0;i<5;i++)
		BaseStats[i]=0;

	m_H_regenTimer = 2000;
	m_P_regenTimer = 2000;

	//	if(GetTypeId() == TYPEID_PLAYER) //only player for now
	//		CalculateActualArmor();

	m_aiInterface = new AIInterface();
	m_aiInterface->Init(this, AITYPE_AGRO, MOVEMENTTYPE_NONE);

	m_emoteState = 0;
	m_oldEmote = 0;

	BaseDamage[0]=0;
	BaseOffhandDamage[0]=0;
	BaseRangedDamage[0]=0;
	BaseDamage[1]=0;
	BaseOffhandDamage[1]=0;
	BaseRangedDamage[1]=0;

	m_CombatUpdateTimer = 0;
	for(i=0;i<7;i++)
	{
		SchoolImmunityList[i] = 0;
		BaseResistance[i] = 0;
		HealDoneMod[i] = 0;
		HealDonePctMod[i] = 0;
		HealTakenMod[i] = 0;
		HealTakenPctMod[i] = 0;
		DamageTakenMod[i] = 0;
		DamageDoneModPCT[i]= 0;
		SchoolCastPrevent[i]=0;
		DamageTakenPctMod[i] = 0;
		SpellCritChanceSchool[i] = 0;
		PowerCostMod[i] = 0;
		PowerCostPctMod[i] = 0; // armor penetration & spell penetration
		AttackerCritChanceMod[i]=0;
		CritMeleeDamageTakenPctMod[i]=0;
		CritRangedDamageTakenPctMod[i]=0;
		m_generatedThreatModifyer[i] = 0;
		DoTPctIncrease[i] = 0;
	}
	DamageTakenPctModOnHP35 = 1;
	RangedDamageTaken = 0;
	AOEDmgMod = 1.0f;

	for(i = 0; i < 5; i++)
	{
		m_detectRangeGUID[i] = 0;
		m_detectRangeMOD[i] = 0;
	}

	trackStealth = false;

	m_threatModifyer = 0;
	memset(m_auras, 0, (MAX_TOTAL_AURAS_END)*sizeof(Aura*));

	// diminishing return stuff
	memset( m_diminishAuraCount, 0, DIMINISHING_GROUP_COUNT );
	memset( m_diminishCount, 0, DIMINISHING_GROUP_COUNT * 2 );
	memset( m_diminishTimer, 0, DIMINISHING_GROUP_COUNT * 2 );
	memset( m_auraStackCount, 0, MAX_NEGATIVE_VISUAL_AURAS_END );
	memset( m_auravisuals, 0, MAX_NEGATIVE_VISUAL_AURAS_END * sizeof(uint32 ));

	m_diminishActive = false;
	dynObj = 0;
	pLastSpell = 0;
	m_flyspeedModifier = 0;
	bInvincible = false;
	m_redirectSpellPackets = 0;
	can_parry = false;
	bProcInUse = false;
	spellcritperc = 0;

	polySpell = 0;
	RangedDamageTaken = 0;
	m_procCounter = 0;
	m_damgeShieldsInUse = false;
//	fearSpell = 0;
	m_extraAttackCounter = false;
	CombatStatus.SetUnit(this);
	m_temp_summon=false;
	m_chargeSpellsInUse=false;
//	m_spellsbusy=false;
	m_interruptedRegenTime = 0;
	m_hasVampiricEmbrace = m_hasVampiricTouch = 0;
	m_hitfrommeleespell	 = 0;
	m_damageSplitTarget = NULL;
	m_extrastriketarget = 0;
	m_extrastriketargetc = 0;
	trigger_on_stun = 0;
	trigger_on_stun_chance = 100;
	trigger_on_stun_victim = 0;
	trigger_on_stun_chance_victim = 100;
	trigger_on_chill = 0;
	trigger_on_chill_chance = 100;
	trigger_on_chill_victim = 0;
	trigger_on_chill_chance_victim = 100;
	m_soulSiphon.amt = 0;
	m_soulSiphon.max = 0;
	ModelHalfSize = 1.0f; //worst case unit size. (Should be overwritten)

	m_blockfromspell		= 0;
	m_dodgefromspell		= 0;
	m_parryfromspell		= 0;
	m_BlockModPct			= 0;

	m_damageShields.clear();
	m_reflectSpellSchool.clear();
	m_procSpells.clear();
	m_chargeSpells.clear();
	m_chargeSpellRemoveQueue.clear();
	tmpAura.clear();
	m_extraStrikeTargets.clear();
	for (i=0; i<7; i++) {
		Absorbs[i].clear();
	}

	asc_frozen = 0;
	asc_enraged = 0;
	asc_seal = 0;
}

Unit::~Unit()
{
	//start to remove badptrs, if you delete from the heap null the ptr's damn!
	RemoveAllAuras();

	if( SM_CriticalChance != NULL ) {
		delete [] SM_CriticalChance;
		SM_CriticalChance = NULL;
	}

	if( SM_FDur != NULL ) {
		delete [] SM_FDur;
		SM_FDur = NULL;
	}

	if( SM_PDur != NULL ) {
		delete [] SM_PDur;
		SM_PDur = NULL;
	}

	if( SM_FRadius != NULL ) {
		delete [] SM_FRadius;
		SM_FRadius = NULL;
	}

	if( SM_FRange != NULL ) {
		delete [] SM_FRange;
		SM_FRange = NULL;
	}

	if( SM_PCastTime != NULL ) {
		delete [] SM_PCastTime;
		SM_PCastTime = NULL;
	}

	if(SM_FCastTime != NULL ) {
		delete [] SM_FCastTime;
		SM_FCastTime = NULL;
	}

	if(SM_PCriticalDamage != NULL ) {
		delete [] SM_PCriticalDamage;
		SM_PCriticalDamage = NULL;
	}

	if(SM_FDOT != NULL ) {
		delete [] SM_FDOT;
		SM_FDOT = NULL;
	}

	if(SM_PDOT != NULL ) {
		delete [] SM_PDOT;
		SM_PDOT = NULL;
	}

	if(SM_FEffect1_Bonus != NULL) {
		delete [] SM_FEffect1_Bonus ;
		SM_FEffect1_Bonus = NULL;
	}

	if(SM_PEffect1_Bonus != NULL) {
		delete [] SM_PEffect1_Bonus ;
		SM_PEffect1_Bonus = NULL;
	}

	if(SM_FEffect2_Bonus != NULL) {
		delete [] SM_FEffect2_Bonus ;
		SM_FEffect2_Bonus = NULL;
	}

	if(SM_PEffect2_Bonus != NULL) {
		delete [] SM_PEffect2_Bonus ;
		SM_PEffect2_Bonus = NULL;
	}

	if(SM_FEffect3_Bonus != NULL) {
		delete [] SM_FEffect3_Bonus ;
		SM_FEffect3_Bonus = NULL;
	}

	if(SM_PEffect3_Bonus != NULL) {
		delete [] SM_PEffect3_Bonus ;
		SM_PEffect3_Bonus = NULL;
	}

	if(SM_PEffectBonus != NULL ) {
		delete [] SM_PEffectBonus;
		SM_PEffectBonus = NULL;
	}

    if(SM_FEffectBonus != NULL ) {
		delete [] SM_FEffectBonus;
		SM_FEffectBonus = NULL;
	}

	if(SM_FDamageBonus != NULL ) {
		delete [] SM_FDamageBonus;
		SM_FDamageBonus = NULL;
	}

	if(SM_PDamageBonus != NULL ) {
		delete [] SM_PDamageBonus;
		SM_PDamageBonus = NULL;
	}

	if(SM_PMiscEffect != NULL ) {
		delete [] SM_PMiscEffect;
		SM_PMiscEffect = NULL;
	}

	if(SM_FMiscEffect != NULL ) {
		delete [] SM_FMiscEffect;
		SM_FMiscEffect = NULL;
	}

	if(SM_FHitchance != NULL ) {
		delete [] SM_FHitchance;
		SM_FHitchance = NULL;
	}

	if(SM_PRange != NULL ) {
		delete [] SM_PRange;
		SM_PRange = NULL;
	}

	if(SM_PRadius != NULL ) {
		delete [] SM_PRadius;
		SM_PRadius = NULL;
	}

	if(SM_PCost != NULL ) {
		delete [] SM_PCost;
		SM_PCost = NULL;
	}

	if(SM_FCost != NULL ) {
		delete [] SM_FCost;
		SM_FCost = NULL;
	}

	if(SM_FAdditionalTargets != NULL ) {
		delete [] SM_FAdditionalTargets;
		SM_FAdditionalTargets = NULL;
	}

	if(SM_PJumpReduce != NULL ) {
		delete [] SM_PJumpReduce;
		SM_PJumpReduce = NULL;
	}

	if(SM_FGlobalCooldown != NULL ) {
		delete [] SM_FGlobalCooldown;
		SM_FGlobalCooldown = NULL;
	}

	if(SM_PGlobalCooldown != NULL ) {
		delete [] SM_PGlobalCooldown;
		SM_PGlobalCooldown = NULL;
	}

	if(SM_PNonInterrupt != NULL ) {
		delete [] SM_PNonInterrupt;
		SM_PNonInterrupt = NULL;
	}

	if(SM_FPenalty != NULL ) {
		delete [] SM_FPenalty;
		SM_FPenalty = NULL;
	}

	if(SM_PPenalty != NULL ) {
		delete [] SM_PPenalty;
		SM_PPenalty = NULL;
	}

	if(SM_FCooldownTime != NULL ) {
		delete [] SM_FCooldownTime;
		SM_FCooldownTime = NULL;
	}

	if(SM_PCooldownTime != NULL ) {
		delete [] SM_PCooldownTime;
		SM_PCooldownTime = NULL;
	}

	if(SM_FChanceOfSuccess != NULL ) {
		delete [] SM_FChanceOfSuccess;
		SM_FChanceOfSuccess = NULL;
	}

	if(SM_FAmptitude != NULL ) {
		delete [] SM_FAmptitude;
		SM_FAmptitude = NULL;
	}

	if(SM_PAmptitude != NULL ) {
		delete [] SM_PAmptitude;
		SM_PAmptitude = NULL;
	}

	if(SM_FRezist_dispell != NULL ) {
		delete [] SM_FRezist_dispell;
		SM_FRezist_dispell = NULL;
	}

	if(SM_PRezist_dispell != NULL ) {
		delete [] SM_PRezist_dispell;
		SM_PRezist_dispell = NULL;
	}

	if(SM_FCharges != NULL ) {
		delete [] SM_FCharges;
		SM_FCharges = NULL;
	}

	if(SM_PCharges != NULL ) {
		delete [] SM_PCharges;
		SM_PCharges = NULL;
	}

	if(SM_FThreat != NULL ) {
		delete [] SM_FThreat;
		SM_FThreat = NULL;
	}

	if(SM_PThreat != NULL ) {
		delete [] SM_PThreat;
		SM_PThreat = NULL;
	}

	delete m_aiInterface;
	m_aiInterface = NULL;


	if( m_currentSpell ) 
	{
		m_currentSpell->cancel();
		m_currentSpell = NULL;
	}

	if( m_damageSplitTarget ) 
	{
		delete m_damageSplitTarget;
		m_damageSplitTarget = NULL;
	}
	
	// reflects not created by auras need to be deleted manually
	for( std::list<struct ReflectSpellSchool*>::iterator i = m_reflectSpellSchool.begin(); i != m_reflectSpellSchool.end(); i++ )
		delete *i;
	m_reflectSpellSchool.clear();
}

void Unit::Update( uint32 p_time )
{
	_UpdateSpells( p_time );

	if(!IsDead())
	{
		//-----------------------POWER & HP REGENERATION-----------------
		/* Please don't do temp fixes. Better report to me. Thx. Shady */
        if( p_time >= m_H_regenTimer )
		    RegenerateHealth();
	    else
		    m_H_regenTimer -= static_cast<uint16>( p_time );

		if( p_time >= m_P_regenTimer )
		{
			RegeneratePower( false );
			m_interruptedRegenTime=0;
		}
		else
		{
			m_P_regenTimer -= static_cast<uint16>( p_time );
			if (m_interruptedRegenTime)
			{
				if(p_time>=m_interruptedRegenTime)
					RegeneratePower( true );
				else
					m_interruptedRegenTime -= p_time;
			}
		}


		if(m_aiInterface != NULL && m_useAI)
			m_aiInterface->Update(p_time);

		if(m_diminishActive)
		{
			uint32 count = 0;
			for(uint32 x = 0; x < DIMINISHING_GROUP_COUNT; ++x)
			{
				// diminishing return stuff
				if(m_diminishTimer[x] && !m_diminishAuraCount[x])
				{
					if(p_time >= m_diminishTimer[x])
					{
						// resetting after 15 sec
						m_diminishTimer[x] = 0;
						m_diminishCount[x] = 0;
					}
					else
					{
						// reducing, still.
						m_diminishTimer[x] -= static_cast<uint16>( p_time );
						++count;
					}
				}
			}
			if(!count)
				m_diminishActive = false;
		}

/*		//if health changed since last time. Would be perfect if it would work for creatures too :)
		if(m_updateMask.GetBit(UNIT_FIELD_HEALTH))
			EventHealthChangeSinceLastUpdate();*/
	}
}

bool Unit::canReachWithAttack(Unit *pVictim)
{
	if( GetMapId() != pVictim->GetMapId() )
		return false;

//	float targetreach = pVictim->GetFloatValue(UNIT_FIELD_COMBATREACH);
	float selfreach;
	if( IsPlayer() )
		selfreach = 5.0f; // minimum melee range, UNIT_FIELD_COMBATREACH is too small and used eg. in melee spells
	else
		selfreach = m_floatValues[UNIT_FIELD_COMBATREACH];

	float targetradius;
//	targetradius = pVictim->m_floatValues[UNIT_FIELD_BOUNDINGRADIUS]; //this is plain wrong. Represents i have no idea what :)
	targetradius = pVictim->GetModelHalfSize();
	float selfradius;;
//	selfradius = m_floatValues[UNIT_FIELD_BOUNDINGRADIUS];
	selfradius = GetModelHalfSize();
//	float targetscale = pVictim->m_floatValues[OBJECT_FIELD_SCALE_X];
//	float selfscale = m_floatValues[OBJECT_FIELD_SCALE_X];

	//float distance = sqrt(GetDistanceSq(pVictim));
	float delta_x = pVictim->GetPositionX() - GetPositionX();
	float delta_y = pVictim->GetPositionY() - GetPositionY();
	float distance = sqrt(delta_x*delta_x + delta_y*delta_y);


//	float attackreach = (((targetradius*targetscale) + selfreach) + (((selfradius*selfradius)*selfscale)+1.50f));
	float attackreach = targetradius + selfreach + selfradius;

	//formula adjustment for player side.
	if( IsPlayer() )
	{
/*
		if( attackreach <= 8 && attackreach >= 5 && targetradius >= 1.80f)
			attackreach = 11; //giant type units

		if( attackreach > 11)
			attackreach = 11; //distance limited to max 11 yards attack range //max attack distance

		if( attackreach < 5 )
			attackreach = 5; //normal units with too small reach.

		//range can not be less than 5 yards - this is normal combat range, SCALE IS NOT SIZE
*/
		// latency compensation!!
		// figure out how much extra distance we need to allow for based on our movespeed and latency.
		if( pVictim->IsPlayer() && static_cast< Player* >( pVictim )->m_isMoving )
		{
			// this only applies to PvP.
			uint32 lat = static_cast< Player* >( pVictim )->GetSession() ? static_cast< Player* >( pVictim )->GetSession()->GetLatency() : 0;

			// if we're over 500 get fucked anyway.. your gonna lag! and this stops cheaters too
			lat = ( lat > 500 ) ? 500 : lat;

			// calculate the added distance
			attackreach += ( m_runSpeed * 0.001f ) * float( lat );
		}

		if( static_cast< Player* >( this )->m_isMoving )
		{
			// this only applies to PvP.
			uint32 lat = static_cast< Player* >( this )->GetSession() ? static_cast< Player* >( this )->GetSession()->GetLatency() : 0;

			// if we're over 500 get fucked anyway.. your gonna lag! and this stops cheaters too
			lat = ( lat > 500) ? 500 : lat;

			// calculate the added distance
			attackreach += ( m_runSpeed * 0.001f ) * float( lat );
		}
	}
	return ( distance <= attackreach );
}

void Unit::GiveGroupXP(Unit *pVictim, Player *PlayerInGroup)
{
	if(!PlayerInGroup)
		return;
	if(!pVictim)
		return;
	if(!PlayerInGroup->InGroup())
		return;
	Group *pGroup = PlayerInGroup->GetGroup();
	uint32 xp;
	if(!pGroup)
		return;

	//Get Highest Level Player, Calc Xp and give it to each group member
	Player *pHighLvlPlayer = NULL;
	Player *pGroupGuy = NULL;
	  int active_player_count=0;
	Player *active_player_list[MAX_GROUP_SIZE_RAID];//since group is small we can afford to do this ratehr then recheck again the whole active player set
	int total_level=0;
	float xp_mod = 1.0f;

/*	if(pGroup->GetGroupType() == GROUP_TYPE_RAID)
	{   //needs to change
		//Calc XP
		xp = CalculateXpToGive(pVictim, PlayerInGroup);
		xp /= pGroup->MemberCount();

		GroupMembersSet::iterator itr;
		for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++)
		{
			for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
			{
				if((*itr)->getLevel() < sWorld.LevelCap)
					(*itr)->GiveXP(xp, pVictim->GetGUID(), true);
			}
		}
	}
	else if(pGroup->GetGroupType() == GROUP_TYPE_PARTY) */
	//change on 2007 04 22 by Zack
	//we only take into count players that are near us, on same map
	GroupMembersSet::iterator itr;
	pGroup->Lock();
	for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++) {
		for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
		{
			pGroupGuy = (*itr)->m_loggedInPlayer;
			if( pGroupGuy &&
				pGroupGuy->isAlive() &&
//				PlayerInGroup->GetInstanceID()==pGroupGuy->GetInstanceID() &&
				pVictim->GetMapMgr() == pGroupGuy->GetMapMgr() &&
				pGroupGuy->GetDistanceSq(pVictim)<100*100
				)
			{
				active_player_list[active_player_count]=pGroupGuy;
				active_player_count++;
				total_level += pGroupGuy->getLevel();
				if(pHighLvlPlayer)
				{
					if(pGroupGuy->getLevel() > pHighLvlPlayer->getLevel())
						pHighLvlPlayer = pGroupGuy;
				}
				else
					pHighLvlPlayer = pGroupGuy;
			}
		}
	}
	pGroup->Unlock();
	if(active_player_count<1) //killer is always close to the victim. This should never execute
	{
		if(PlayerInGroup == 0)
		{
			PlayerInfo * pleaderinfo = pGroup->GetLeader();
			if(!pleaderinfo->m_loggedInPlayer)
				return;

			PlayerInGroup = pleaderinfo->m_loggedInPlayer;
		}

		xp = CalculateXpToGive(pVictim, PlayerInGroup);
		PlayerInGroup->GiveXP(xp, pVictim->GetGUID(), true);
	}
	else
	{
		if( pGroup->GetGroupType() == GROUP_TYPE_PARTY)
		{
			if(active_player_count==3)
				xp_mod=1.1666f;
			else if(active_player_count==4)
				xp_mod=1.3f;
			else if(active_player_count==5)
				xp_mod=1.4f;
			else xp_mod=1;//in case we have only 2 members ;)
		}
		else if(pGroup->GetGroupType() == GROUP_TYPE_RAID)
			xp_mod=0.5f;

		if(pHighLvlPlayer == 0)
		{
			PlayerInfo * pleaderinfo = pGroup->GetLeader();
			if(!pleaderinfo->m_loggedInPlayer)
				return;

			pHighLvlPlayer = pleaderinfo->m_loggedInPlayer;
		}

		xp = CalculateXpToGive(pVictim, pHighLvlPlayer);
		//I'm not sure about this formula is correct or not. Maybe some brackets are wrong placed ?
		for(int i=0;i<active_player_count;i++)
		{
			Player * plr = active_player_list[i];
			plr->GiveXP( float2int32( ( ( xp * plr->getLevel() ) / total_level ) * xp_mod ), pVictim->GetGUID(), true );

			active_player_list[i]->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_LASTKILLWITHHONOR);
			if(!sEventMgr.HasEvent(active_player_list[i],EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE))
			{
				sEventMgr.AddEvent((Unit*)active_player_list[i],&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_LASTKILLWITHHONOR,EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE,20000,1,0);
			}
			else
			{
				sEventMgr.ModifyEventTimeLeft(active_player_list[i],EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE,20000);
			}

			if ( plr->GetSummon() && plr->GetSummon()->CanGainXP() )
			{
				uint32 pet_xp = (uint32)(CalculateXpToGive( pVictim, plr->GetSummon() ) * xp_mod); // vojta: this isn't blizzlike probably but i have no idea, feel free to correct it
				if ( pet_xp > 0 )
					plr->GetSummon()->GiveXP( pet_xp );
			}
		}
	}
		/* old code start before 2007 04 22
		GroupMembersSet::iterator itr;
		for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++)
		{
			for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
			{
				pGroupGuy = (*itr);
				if(pGroupGuy)
				{
					if(pHighLvlPlayer)
					{
						if(pGroupGuy->getLevel() > pHighLvlPlayer->getLevel())
						{
							pHighLvlPlayer = pGroupGuy;
						}
					}
					else
						pHighLvlPlayer = pGroupGuy;
				}
			}
		}

		//Calc XP
		xp = CalculateXpToGive(pVictim, pHighLvlPlayer);
		uint32 giveXP = 0;

		for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++)
		{
			for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
			{
				pGroupGuy = (*itr);
				giveXP = xp * pGroupGuy->getLevel() / (pHighLvlPlayer->getLevel() + pGroupGuy->getLevel());
				if(pGroupGuy->getLevel() < sWorld.LevelCap)
					pGroupGuy->GiveXP(giveXP, pVictim->GetGUID(), true);
			}
		}
	}*/
}

uint32 Unit::HandleProc( uint32 flag, Unit* victim, SpellEntry* CastingSpell, uint32 dmg, uint32 abs )
{
	uint32 resisted_dmg = 0;
	++m_procCounter;
	bool can_delete = !bProcInUse; //if this is a nested proc then we should have this set to TRUE by the father proc
	bProcInUse = true; //locking the proc list

	/* hmm what's a reasonable value here */
	if( m_procCounter > 40 )
	{
		/* something has proceed over 10 times in a loop :/ dump the spellids to the crashlog, as the crashdump will most likely be useless. */
		// BURLEX FIX ME!
		//OutputCrashLogLine("HandleProc %u SpellId %u (%s) %u", flag, spellId, sSpellStore.LookupString(sSpellStore.LookupEntry(spellId)->Name), m_procCounter);
		return 0;
	}
#if 0
	//will be used only on new system
	ProcCondSharedDataStruct sharedprocdata;
	sharedprocdata.owner = this;
	sharedprocdata.ProcFlags = flag;
	sharedprocdata.CastingSpell = CastingSpell;
	sharedprocdata.Fulldmg = dmg;
	sharedprocdata.Absdmg = abs;
	sharedprocdata.victim = victim;
#endif

	std::list< uint32 > remove;
	std::list< struct ProcTriggerSpell >::iterator itr,itr2;
	for( itr = m_procSpells.begin(); itr != m_procSpells.end(); )  // Proc Trigger Spells for Victim
	{
		itr2 = itr;
		++itr;
		
		if( itr2->deleted )
		{
			if( can_delete )
				m_procSpells.erase( itr2 );
			continue;
		}
		//flags can be mixed, we test them in mixed way. Maybe we should handle each one ?
		if( !( itr2->procFlags & flag ) )
			continue;
		
		if( CastingSpell != NULL )
		{
			if(	CastingSpell->Id == itr2->spellId )
				continue;
		}

		uint32 spellId = itr2->spellId;
		
		if( !spellId )
			continue; //there are procs without spells ?

		//lookupentry returns first spell for wrong ids to avoid crash, there is no need for NULL check
		SpellEntry* spe  = dbcSpell.LookupEntry( spellId );

		uint32 origId = itr2->origId;
		SpellEntry* ospinfo = dbcSpell.LookupEntry( origId );//no need to check if exists or not since we were not able to register this trigger if it would not exist :P

		/*if( itr2->procFlags & PROC_ON_CAST_SPECIFIC_SPELL || itr2->procFlags & PROC_ON_CAST_SPELL) {
			if( CastingSpell == NULL )
				continue;

			if (itr2->groupRelation) {
				if (!(itr2->groupRelation & CastingSpell->SpellGroupType))
					continue;
			}
		}*/

		//this requires some specific spell check,not yet implemented
		//this sucks and should be rewrote
		if( itr2->procFlags & PROC_ON_CAST_SPECIFIC_SPELL )
		{
			if( CastingSpell == NULL )
				continue;

			//this is wrong, dummy is too common to be based on this, we should use spellgroup or something
			if( spe->spellIconID != CastingSpell->spellIconID )
			{
				if( !ospinfo->School )
					continue;
				if( ospinfo->School != CastingSpell->School )
					continue;
				if( CastingSpell->EffectImplicitTargetA[0] == 1 ||
					CastingSpell->EffectImplicitTargetA[1] == 1 ||
					CastingSpell->EffectImplicitTargetA[2] == 1 ) //Prevents school based procs affecting caster when self buffing
					continue;
			}
			else
				if( spe->spellIconID == 1 )
					continue;
		}

#if 0
		if( itr2->spellId < MAX_SPELL_ID_FROMDBC && G_ProcCondHandlers[ itr2->spellId ] )
		{
			sharedprocdata.cur_itr = itr2;
			ProcCondHandlerRes res = (*G_ProcCondHandlers[ itr2->spellId ])( &sharedprocdata );
			if( res == PROCCOND_BREAK_EXECUTION )
				continue;
			else if( res == PROCCOND_FATAL_EXIT )
			{
				//this is panic situation and should not happen !
				bProcInUse = false;
				return;
			}
		}
#endif

		uint32 proc_Chance = itr2->procChance;

		// feral = no procs (need a better way to do this)
		/*if( this->IsPlayer() && static_cast<Player*>(this)->GetShapeShift() )
		{
			if( spe->NameHash == SPELL_HASH_LIGHTNING_SPEED ) // mongoose
				continue;
			else if( spe->NameHash == SPELL_HASH_HOLY_STRENGTH ) //crusader
				continue;
		}*/

		//Custom procchance modifications based on equipped weapon speed.
		if( this->IsPlayer() && (
			spe->NameHash == SPELL_HASH_MAGTHERIDON_MELEE_TRINKET ||
			spe->NameHash == SPELL_HASH_ROMULO_S_POISON ||
			spe->NameHash == SPELL_HASH_BLACK_TEMPLE_MELEE_TRINKET ||
			spe->NameHash == SPELL_HASH_FROSTBRAND_ATTACK || spellId == 16870 ) )
		{
			float ppm = 1.0f;
			switch( spe->NameHash )
			{
				case SPELL_HASH_MAGTHERIDON_MELEE_TRINKET:
					ppm = 1.5f;
					break; // dragonspine trophy
				case SPELL_HASH_ROMULO_S_POISON:
					ppm = 1.5f;
					break; // romulo's
				case SPELL_HASH_BLACK_TEMPLE_MELEE_TRINKET:
					ppm = 1.0f;
					break; // madness of the betrayer
				case SPELL_HASH_FROSTBRAND_ATTACK:
					ppm = 9.0f;
					break; // Frostbrand Weapon
			}
			switch( spellId )
			{
				case 16870:
					ppm = 2.0f;
					break; //druid: clearcasting
			}

			Item * mh = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
			Item * of = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );

			if( mh != NULL && of != NULL )
			{
				float mhs = float( mh->GetProto()->Delay );
				float ohs = float( of->GetProto()->Delay );
				proc_Chance = FL2UINT( ( mhs + ohs ) * 0.001f * ppm / 0.6f );
			}
			else if( mh != NULL )
			{
				float mhs = float( mh->GetProto()->Delay );
				proc_Chance = float2int32( mhs * 0.001f * ppm / 0.6f );
			}
			else
				proc_Chance = 0;

			if( static_cast< Player* >( this )->IsInFeralForm() )
			{
				if( static_cast< Player* >( this )->GetShapeShift() == FORM_CAT )
				{
					proc_Chance = FL2UINT( ppm / 0.6f );
				}
				else if( static_cast< Player* >( this )->GetShapeShift() == FORM_BEAR || static_cast< Player* >( this )->GetShapeShift() == FORM_DIREBEAR )
				{
					proc_Chance = FL2UINT( ppm / 0.24f );
				}
			}
		}

		
		SM_FIValue( SM_FChanceOfSuccess, (int32*)&proc_Chance, ospinfo->SpellGroupType );
		if( !Rand( proc_Chance ) )
			continue;
		//check if we can trigger due to time limitation
		if( ospinfo->proc_interval )
		{
			uint32 now_in_ms=getMSTime();
			if( itr2->LastTrigger + ospinfo->proc_interval > now_in_ms )
				continue; //we can't trigger it yet.
			itr2->LastTrigger = now_in_ms; // consider it triggered
		}

		//since we did not allow to remove auras like these with interrupt flag we have to remove them manually.
		if( itr2->procFlags & PROC_REMOVEONUSE )
			RemoveAura( origId );

		int dmg_overwrite = 0;

		//these are player talents. Fuckem they pull the emu speed down
		if( IsPlayer() )
		{
			if( spe->ProcOnNameHash[0] != 0 )
			{
				if( CastingSpell == NULL )
					continue;

				if( CastingSpell->NameHash != spe->ProcOnNameHash[0] &&
					CastingSpell->NameHash != spe->ProcOnNameHash[1] &&
					CastingSpell->NameHash != spe->ProcOnNameHash[2] )
					continue;
			}

			uint32 talentlevel = 0;
			switch( origId )
			{
				//mace specialization
				case 12284:	{talentlevel = 1;}break;
				case 12701:	{talentlevel = 2;}break;
				case 12702:	{talentlevel = 3;}break;
				case 12703:	{talentlevel = 4;}break;
				case 12704:	{talentlevel = 5;}break;

				//Unbridled Wrath
				case 12999:	{talentlevel = 1;}break;
				case 13000:	{talentlevel = 2;}break;
				case 13001:	{talentlevel = 3;}break;
				case 13002:	{talentlevel = 4;}break;
			}

			switch( spellId )
			{
				 // Missile Barrage by Malacka
			   case 44404:
               case 54486:
               case 54488:
               case 54489:
               case 54490:
			   {
				   Log.Notice("Missile", "barrage");
					   if (CastingSpell == NULL)
						   continue;
					   /*if (CastingSpell->NameHash != SPELL_HASH_ARCANE_BLAST &&
						   CastingSpell->NameHash != SPELL_HASH_FIREBALL && 
                           CastingSpell->NameHash != SPELL_HASH_FROSTBOLT && 
		                   CastingSpell->NameHash != SPELL_HASH_ARCANE_BARRAGE &&
                           CastingSpell->NameHash != SPELL_HASH_FROSTFIRE_BOLT)
						   continue;*/
			    }break;
				case 32747: //Deadly Throw Interrupt (rogue arena gloves set)
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_DEADLY_THROW )
							continue;
					}break;
				case 16959://Druid - Primal Fury Proc
					{
						if( !IsPlayer() )
							continue;
						Player * p = static_cast< Player * >( this );
						if( p->GetShapeShift() != FORM_BEAR && p->GetShapeShift() != FORM_DIREBEAR )
							continue;
					}break;
				case 16953: //Druid - Blood Frenzy Proc
					{
						if( !IsPlayer() || !CastingSpell )
							continue;
						Player * p = static_cast< Player * >( this );
						if( p->GetShapeShift() != FORM_CAT || (
							CastingSpell->NameHash != SPELL_HASH_CLAW &&
							CastingSpell->NameHash != SPELL_HASH_RAKE &&
							CastingSpell->NameHash != SPELL_HASH_RAVAGE &&
							CastingSpell->NameHash != SPELL_HASH_SHRED ) )
							continue;
					}break;
				case 14189: //Seal Fate
				{
					if( !this->IsPlayer() ||
						!CastingSpell ||
						CastingSpell->Id == 14189 ||
						CastingSpell->Id == 16953 ||
						CastingSpell->Id == 16959)
						continue;
					if( CastingSpell->Effect[0] != 80 &&
						CastingSpell->Effect[1] != 80 &&
						CastingSpell->Effect[2] != 80 &&
						CastingSpell->NameHash != SPELL_HASH_MANGLE___CAT )
						continue;
				}break;
				case 17106: //druid intensity
				{
					if( CastingSpell == NULL )
						continue;
					if( CastingSpell->Id != 5229 )//enrage
						continue;
				}break;
				case 31616: //Nature's Guardian
				{
					//yep, another special case: Nature's grace
					if( GetHealthPct() > 30 )
						continue;
				}break;
				case 37309: //Bloodlust
				{
					if( !this->IsPlayer() )
						continue;
					if( static_cast< Player* >( this )->GetShapeShift() != FORM_BEAR ||
						static_cast< Player* >( this )->GetShapeShift() != FORM_DIREBEAR )
						continue;
				}break;
				case 37310://Bloodlust
				{
					if( !this->IsPlayer() || static_cast< Player* >( this )->GetShapeShift() != FORM_CAT )
						continue;
				}break;
                case 34754: //holy concentration
                {

					if( CastingSpell == NULL )
						continue;
					if( CastingSpell->NameHash != SPELL_HASH_FLASH_HEAL &&
						CastingSpell->NameHash != SPELL_HASH_BINDING_HEAL &&
						CastingSpell->NameHash != SPELL_HASH_GREATER_HEAL )
						continue;
				}break;
				case 16459:
				{
					//sword specialization
					if( static_cast< Player* >( this )->GetItemInterface())
					{
						Item* itMH = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
						Item* itOH = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
						uint32 reqskillMH = 0;
						uint32 reqskillOH = 0;

						if( itMH != NULL && itMH->GetProto() ) 
							reqskillMH = GetSkillByProto( itMH->GetProto()->Class, itMH->GetProto()->SubClass );

						if( itOH != NULL && itOH->GetProto() )
							reqskillOH = GetSkillByProto( itOH->GetProto()->Class, itOH->GetProto()->SubClass );

						if( reqskillMH != SKILL_SWORDS && reqskillMH != SKILL_2H_SWORDS && reqskillOH != SKILL_SWORDS && reqskillOH != SKILL_2H_SWORDS )
							continue;
					}
					else
						continue; //no weapon no joy
				}break;
				case 12721:
				{
					//deep wound requires a melee weapon
					Item* it;
					if( static_cast< Player* >( this )->GetItemInterface())
					{
						it = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
						if( it != NULL && it->GetProto() )
						{
							//class 2 means weapons ;)
							if( it->GetProto()->Class != 2 )
								continue;
						}
						else continue; //no weapon no joy
					}
					else continue; //no weapon no joy
				}break;
				//Warrior - Sword and Board
				case 50227:
				{
					if( CastingSpell == NULL )
						continue;

					if( CastingSpell->NameHash != SPELL_HASH_DEVASTATE && CastingSpell->NameHash != SPELL_HASH_REVENGE )
						continue;
				}break;
				//Warrior - Safeguard
				case 46946:
				case 46947:
				{
					if( CastingSpell == NULL )
						continue;

					if( CastingSpell->NameHash != SPELL_HASH_INTERVENE )
						continue;
				}break;
				//Warrior - Taste for Blood
				case 60503:
				{
					if( CastingSpell == NULL )
						continue;

					if( CastingSpell->NameHash != SPELL_HASH_REND )
						continue;
				}break;
				//Warrior - Blood Frenzy
				case 30069:
				case 30070:
				{
					if( CastingSpell == NULL )
						continue;

					if( CastingSpell->NameHash != SPELL_HASH_REND &&
						CastingSpell->NameHash != SPELL_HASH_DEEP_WOUND )
						continue;
				}break;
				//Warrior - Unbridled Wrath
				case 12964:
				{
					//let's recalc chance to cast since we have a full 100 all time on this one
					Item* it;
					if( static_cast< Player* >( this )->GetItemInterface() )
					{
						it = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
						if( !( it != NULL && it->GetProto() ) )
							continue; //no weapon no joy
					}
					else
						continue; //no weapon no joy
					//float chance=float(it->GetProto()->Delay)*float(talentlevel)/600.0f;
					float chance = float( it->GetProto()->Delay ) * float(talentlevel ) / 300.0f; //zack this had a very low proc rate. Kinda like a wasted talent
					uint32 myroll = RandomUInt( 100 );
					if( myroll > chance )
						continue;
				}break;
				//Warrior - Gag Order
				case 18498:
				{
					if( CastingSpell == NULL )
						continue;

					if( CastingSpell->NameHash != SPELL_HASH_SHIELD_BASH &&
						CastingSpell->NameHash != SPELL_HASH_HEROIC_THROW )
						continue;
				}break;
				//Warrior - Bloodsurge
				case 46916:
				{
					if( CastingSpell == NULL )
						continue;

					if( CastingSpell->NameHash != SPELL_HASH_HEROIC_STRIKE &&
						CastingSpell->Id != 23881 &&
						CastingSpell->NameHash != SPELL_HASH_WHIRLWIND )
						continue;
				}break;
////////////////////////////////////////////////////////////////////////////
				// Mage ignite talent only for fire dmg
				case 12654:
				{
					if( CastingSpell == NULL )
						continue;
					if( CastingSpell->School != SCHOOL_FIRE )
						continue;
					SpellEntry* spellInfo = dbcSpell.LookupEntry( spellId ); //we already modified this spell on server loading so it must exist
					SpellDuration* sd = dbcSpellDuration.LookupEntryForced( spellInfo->DurationIndex );
					uint32 tickcount = GetDuration( sd ) / spellInfo->EffectAmplitude[0] ;
					dmg_overwrite = ospinfo->EffectBasePoints[0] * dmg / (100  * tickcount );
				}break;
				//druid - Primal Fury
				case 37116:
				case 37117:
				{
					if (!this->IsPlayer())
						continue;
					Player* mPlayer = (Player*)this;
					if (!mPlayer->IsInFeralForm() ||
						(mPlayer->GetShapeShift() != FORM_CAT &&
						mPlayer->GetShapeShift() != FORM_BEAR &&
						mPlayer->GetShapeShift() != FORM_DIREBEAR))
						continue;
				}break;
				//rogue - blade twisting
				case 31125:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if( CastingSpell->NameHash != SPELL_HASH_BACKSTAB && //backstab
							CastingSpell->NameHash != SPELL_HASH_SINISTER_STRIKE && //sinister strike
							CastingSpell->NameHash != SPELL_HASH_SHIV && //shiv
							CastingSpell->NameHash != SPELL_HASH_GOUGE ) //gouge
							continue;
					}break;

				//rogue - Deadly Brew
				case 51625:
				case 51626:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_WOUND_POISON &&
							CastingSpell->NameHash != SPELL_HASH_CRIPPLING_POISON )//It's SPELL_HASH_CRIPPLING_POISON, no mind numbling poison
							continue;
						CastSpell(victim, 44289, true);
					}break; 
				//priest - Grace
				case 47930:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_PENANCE &&
							CastingSpell->NameHash != SPELL_HASH_FLASH_HEAL &&
							CastingSpell->NameHash != SPELL_HASH_GREATER_HEAL )
							continue;
					}break;
				//warlock - Improved Shadow Bolt
				case 17794:
				case 17798:
				case 17797:
				case 17799:
				case 17800:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if( CastingSpell->NameHash!=SPELL_HASH_SHADOW_BOLT)//shadow bolt
							continue;
					}break;
				// warlock - Seed of Corruption
				case 27285:
					{
						bool can_proc_now = false;
						//if we proced on spell tick
						if( flag & PROC_ON_SPELL_HIT_VICTIM )
						{
							if( !CastingSpell )
								continue;
							//only trigger effect for specified spells
							if( CastingSpell->NameHash != SPELL_HASH_SEED_OF_CORRUPTION )
								continue;
							//this spell builds up in time
							(*itr2).procCharges += dmg;
							if( (int32)(*itr2).procCharges >= ospinfo->EffectBasePoints[ 1 ] && //if charge built up
								dmg < (int32)this->GetUInt32Value( UNIT_FIELD_HEALTH ) ) //if this is not a killer blow
								can_proc_now = true;
						}
						else can_proc_now = true; //target died
						if( can_proc_now == false )
							continue;
						Unit *new_caster = victim;
						if( new_caster && new_caster->isAlive() )
						{
							SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId ); //we already modified this spell on server loading so it must exist
							Spell *spell = SpellPool.PooledNew();
							if (!spell)
								return 0;
							spell->Init( new_caster, spellInfo ,true, NULL );
							SpellCastTargets targets;
							targets.m_destX = GetPositionX();
							targets.m_destY = GetPositionY();
							targets.m_destZ = GetPositionZ();
							spell->prepare(&targets);
						}
						(*itr2).deleted = true;
						continue;
					}break;
				// warlock - Improved Drain Soul
				case 18371:
					{
						if( !CastingSpell )
							continue;
						//only trigger effect for specified spells
						if( CastingSpell->NameHash != SPELL_HASH_DRAIN_SOUL )
							continue;
						//null check was made before like 2 times already :P
						dmg_overwrite = ( ospinfo->EffectBasePoints[2] + 1 ) * GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) / 100;
					}break;
				// warlock - Unstable Affliction
				case 31117:
					{
						//null check was made before like 2 times already :P
						dmg_overwrite = ( ospinfo->EffectBasePoints[0] + 1 ) * 9;
					}break;
				//warlock soul link
				case 25228:
					{
						//we need a pet for this, else we do not trigger it at all
						if( IsPlayer() )
							continue;
						Unit* new_caster;
						if( static_cast< Player* >( this )->GetSummon() )
							new_caster = static_cast< Player* >( this )->GetSummon();
						else if( GetUInt64Value( UNIT_FIELD_CHARM ) )
							new_caster = GetMapMgr()->GetUnit( GetUInt64Value( UNIT_FIELD_CHARM ) );
						else
							new_caster = NULL;
						if( new_caster != NULL && new_caster->isAlive() )
						{
							SpellEntry* spellInfo = dbcSpell.LookupEntry( 25228 ); //we already modified this spell on server loading so it must exist
							Spell* spell = SpellPool.PooledNew();
							if (!spell)
								return 0;
							spell->Init( new_caster, spellInfo, true, NULL );
							spell->forced_basepoints[0] = dmg;
							SpellCastTargets targets;
							targets.m_unitTarget = GetGUID();
							spell->prepare( &targets );
						}
						continue;
					}break;
				//warlock - Nighfall
				case 17941:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if( CastingSpell->NameHash != SPELL_HASH_CORRUPTION && //Corruption
							CastingSpell->NameHash != SPELL_HASH_DRAIN_LIFE )//Drain Life
							continue;
					}break;
				//warlock - Shadow Embrace
				case 32386:
				case 32388:
				case 32389:
				case 32390:
				case 32391:
					{
						if( CastingSpell == NULL )
							continue;
						else
						{
							if( CastingSpell->NameHash != SPELL_HASH_FIRE_SHIELD_II && // Corruption
								CastingSpell->NameHash != SPELL_HASH_CURSE_OF_AGONY && //CoA
								CastingSpell->NameHash != SPELL_HASH_SIPHON_LIFE && //Siphon Life
								CastingSpell->NameHash != SPELL_HASH_SEED_OF_CORRUPTION ) //SoC
								continue;
						}
					}break;
				//warlock - Aftermath
				case 18118:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						skilllinespell* skillability = objmgr.GetSpellSkill(CastingSpell->Id);
						if( !skillability )
							continue;
						if( skillability->skilline != SKILL_DESTRUCTION )
							continue;
					}break;
				//warlock - Nether Protection
				case 30300:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;
						if( CastingSpell->School!=SCHOOL_FIRE &&
							CastingSpell->School!=SCHOOL_SHADOW)
							continue;
					}break;
				//warlock - Soul Leech - this whole spell should get rewritten. Uses bad formulas, bad trigger method, spell is rewritten ...
				case 30294:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						uint32 amount;
						switch( CastingSpell->NameHash )
						{
							case SPELL_HASH_SHADOW_BOLT: //Shadow Bolt
							case SPELL_HASH_SOUL_FIRE: //Soul Fire
							case SPELL_HASH_INCINERATE: //Incinerate
							case SPELL_HASH_SEARING_PAIN: //Searing Pain
							case SPELL_HASH_CONFLAGRATE: //Conflagrate
							case SPELL_HASH_CHAOS_BOLT: //Chaos Bolt
							{
								amount = CastingSpell->EffectBasePoints[0]+1;
							}break;
							case SPELL_HASH_SHADOWBURN: //Shadowburn
							{
								amount = CastingSpell->EffectBasePoints[1]+1;
							}break;
							default:
								amount=0;
						}
						if(!amount)
							continue;
						SpellEntry *spellInfo = dbcSpell.LookupEntry(spellId );
						if(!spellInfo)
							continue;
						Spell *spell = SpellPool.PooledNew();
						if (!spell)
							return 0;
						spell->Init(this, spellInfo ,true, NULL);
						spell->SetUnitTarget(this);
						spell->Heal(amount*(ospinfo->EffectBasePoints[0]+1)/100);
						SpellPool.PooledDelete(spell);
						spell = NULL;
						continue;
					}break;
				//warlock - pyroclasm
				case 18093:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if( CastingSpell->NameHash != SPELL_HASH_RAIN_OF_FIRE && //Rain of Fire
							CastingSpell->NameHash != SPELL_HASH_HELLFIRE_EFFECT && //Hellfire
							CastingSpell->NameHash != SPELL_HASH_SOUL_FIRE ) //Soul Fire
							continue;
					}break;
				case 54274:
				case 54276:
				case 54277:
				{
					if( CastingSpell == NULL )
						continue;

					if( CastingSpell->NameHash != SPELL_HASH_CONFLAGRATE )
						continue;
				}break;
				//Mage - Missile Barrage
				case 44401:
					{
						if( CastingSpell == NULL )
							continue;

						if( CastingSpell->NameHash != SPELL_HASH_ARCANE_BLAST &&
							CastingSpell->NameHash != SPELL_HASH_ARCANE_BARRAGE &&
							CastingSpell->NameHash != SPELL_HASH_FIREBALL &&
							CastingSpell->NameHash != SPELL_HASH_FROSTBOLT && 
							CastingSpell->NameHash != SPELL_HASH_FROSTFIRE_BOLT )
							continue;
					}break;
				//mage - Improved Scorch
				case 22959:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if( CastingSpell->NameHash != SPELL_HASH_SCORCH ) //Scorch
							continue;
					}break;
				//mage - Combustion
				case 28682:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING)
							|| CastingSpell->School != SCHOOL_FIRE )
							continue;
						if( flag & PROC_ON_SPELL_CRIT_HIT )
						{
							itr2->procCharges++;
							if( itr2->procCharges >= 3 ) //whatch that number cause it depends on original stack count !
							{
								RemoveAllAuraByNameHash( SPELL_HASH_COMBUSTION );
								continue;
							}
						}
					}break;
				//mage - Winter's Chill
				case 12579:
					// Winter's Chill shouldn't proc on self
					if (victim == this || CastingSpell->School != SCHOOL_FROST)
						continue;
					break;
				//item - Thunderfury
				case 21992:
					if (victim == this)
						continue;
				break;
				//warrior - Intimidating Shout
				case 5246:
					if (victim == this)
						continue;
				break;

				//priest - Borrowed time
				case 59887:
				case 59888:
				case 59889:
				case 59890:
				case 59891:
					{
						if( CastingSpell == NULL ) 
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_POWER_WORD__SHIELD)  
							continue;						
					}break;

				//priest - prayer of mending
				case 41637: //the heal spell
					{
						//victim got a hit in the face so we jump on next injured target
						//find aura on self and get it's value
						Aura *pa = this->FindAura( origId );
						if( !pa || !this->GetMapMgr() )
							return 0; //omg we have this proc on us and on second check we don't ? Return instead of continue since this seems to be a corrupted object

						//check if we jumped proctimes
						if( pa->GetModAmount( 0 ) == 1 )
							break;

						//we use same caster as firts caster to be able to get heal bonuses !
						Unit *oricaster = this->GetMapMgr()->GetUnit( pa->GetCasterGUID() );
						if( !oricaster || !oricaster->IsPlayer() )
							break;

						//the nasty part : get a new target ^^
						Player *p_caster = (Player*)oricaster;
						Player *First_new_target,*Next_new_target,*First_whatever;
						First_new_target = Next_new_target = First_whatever = NULL;
						bool passed_prev_target = false;
						GroupMembersSet::iterator itr;
						SubGroup * pGroup = p_caster->GetGroup() ?
							p_caster->GetGroup()->GetSubGroup(p_caster->GetSubGroup()) : 0;

						if(pGroup)
						{
							p_caster->GetGroup()->Lock();

							float range=GetMaxRange(dbcSpellRange.LookupEntry(ospinfo->rangeIndex));
							range*=range;

							for(itr = pGroup->GetGroupMembersBegin();itr != pGroup->GetGroupMembersEnd(); ++itr)
							{
								if(!(*itr)->m_loggedInPlayer || !(*itr)->m_loggedInPlayer->isAlive() )
									continue;

								//we cannot retarget self
								if( (*itr)->m_loggedInPlayer == this )
								{
									passed_prev_target = true;
									continue;
								}

								if( IsInrange(p_caster,(*itr)->m_loggedInPlayer, range) )
								{

									if( !First_whatever )
										First_whatever = (*itr)->m_loggedInPlayer;

									//we target stuff that has no full health. No idea if we must fill target list or not :(
									if( First_whatever && (*itr)->m_loggedInPlayer->GetUInt32Value( UNIT_FIELD_HEALTH ) == (*itr)->m_loggedInPlayer->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) )
										continue;

									//first targatable player in group (like make circular buffer from normal list)
									if( !First_new_target )
										First_new_target = (*itr)->m_loggedInPlayer;

									if( passed_prev_target )
									{
										Next_new_target = (*itr)->m_loggedInPlayer;
										break;
									}
								}
							}
							p_caster->GetGroup()->Unlock();
						}
						if( First_new_target && !Next_new_target )
							Next_new_target = First_new_target; //we passed end of the list and it is time to restart it

						if( !Next_new_target )
							Next_new_target = First_whatever; //we passed end of the list and it is time to restart it

						if( Next_new_target )
						{
							Spell *spell = SpellPool.PooledNew();
							if (!spell)
								return 0;
							spell->Init(p_caster, ospinfo ,true, NULL);
							spell->forced_basepoints[0] = pa->GetModAmount( 0 ) - 1 ;
							SpellCastTargets targets( Next_new_target->GetGUID() ); //no target so spelltargeting will get an injured party member
							spell->prepare( &targets );
						}
					}break;
				//priest - Misery
				case 33200:
				case 33199:
				case 33198:
				case 33197:
				case 33196:
					{
						if( CastingSpell == NULL )
							continue;
						else
						{
							if( CastingSpell->NameHash != SPELL_HASH_MIND_FLAY && // Mind Flay
								CastingSpell->NameHash != SPELL_HASH_SHADOW_WORD__PAIN && //SW:P
								CastingSpell->NameHash != SPELL_HASH_VAMPIRIC_TOUCH ) //SoC
								continue;
						}
					}break;
				//priest - Shadow Weaving
				case 15258:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						if( CastingSpell->School != SCHOOL_SHADOW || !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) ) //we need damaging spells for this, so we suppose all shadow spells cast on target are dmging spells = Wrong
							continue;
					}break;
				//priest - Inspiration
				case 15363:
				case 14893:
				case 15357:
				case 15359:
					{
						if( !CastingSpell || !( CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ) )
							continue;
					}
					break;
				//priest - Blessed Recovery
                case 27813:
                case 27817:
                case 27818:
                    {
                        if(!IsPlayer() || !dmg)
                            continue;
                        SpellEntry *parentproc= dbcSpell.LookupEntry(origId);
                        SpellEntry *spellInfo = dbcSpell.LookupEntry(spellId);
						if (!parentproc || !spellInfo)
							continue;
						int32 val = parentproc->EffectBasePoints[0] + 1;
                        Spell *spell = SpellPool.PooledNew();
						if (!spell)
							return 0;
						spell->Init(this, spellInfo ,true, NULL);
                        spell->forced_basepoints[0] = (val*dmg)/300; //per tick
                        SpellCastTargets targets;
                        targets.m_unitTarget = GetGUID();
                        spell->prepare(&targets);
                        continue;
                    }break;


				//Shaman - Healing Way
				case 29203:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if( CastingSpell->NameHash != SPELL_HASH_HEALING_WAVE ) //healing wave
							continue;
					}break;
				//Shaman - Elemental Devastation
				case 29177:
				case 29178:
				case 30165:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if( !(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING)) //healing wave
							continue;
					}break;
				//Shaman - Ancestral Fortitude
				case 16177:
				case 16236:
				case 16237:
				//Shaman - Earthliving Weapon
				case 51940:
				case 51989:
				case 52004:
				case 52005:
				case 52007:
				case 52008:
					{
						if( CastingSpell == NULL )
							continue;
						if( !(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING) ) //healing spell
							continue;
					}break;
				//Toute puissance:
				case 35541:
				case 35550:
				case 35551:
				case 35552:
				case 35553:
					{
						CastSpell( this, spe->EffectTriggerSpell[0], true);
					}break;
				//Shaman - Tidal Waves
				case 51562:
				case 51563:
				case 51564:
				case 51565:
				case 51566:
					{
						if( CastingSpell == NULL )
							continue;
						if( !(CastingSpell->NameHash == SPELL_HASH_CHAIN_HEAL || CastingSpell->NameHash == SPELL_HASH_RIPTIDE) )
							continue;
					}break;
				// Resilient
				case 46089:
				case 43839:
				case 43848:
				case 43849:
					{
						if( CastingSpell == NULL )
							continue;
						if(	(origId==46097 || origId==43860 || origId==43861 || origId==43862)&&
							(CastingSpell->NameHash == SPELL_HASH_EARTH_SHOCK ||
							CastingSpell->NameHash == SPELL_HASH_FROST_SHOCK ||
							CastingSpell->NameHash == SPELL_HASH_FLAME_SHOCK))
							break;
						if(	(origId==43859 || origId==43858 || origId==43857 || origId==46096)&&
							CastingSpell->NameHash == SPELL_HASH_STORMSTRIKE)
							break;
					}continue;
				// Totem of the Third Wind
				case 42371:
				case 34132:
				case 46099:
				case 43729:
					{
						if( CastingSpell == NULL )
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_LESSER_HEALING_WAVE)
							continue;
					}break;
				//Stonebreaker's Totem
				case 43749:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_EARTH_SHOCK && CastingSpell->NameHash != SPELL_HASH_FROST_SHOCK && CastingSpell->NameHash != SPELL_HASH_FLAME_SHOCK )
							continue;
					}break;
				// Librams of Justice
				case 34135:
				case 42369:
				case 43727:
				case 46093:
					{
						if( CastingSpell == NULL )
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_FLASH_OF_LIGHT)
							continue;
					}break;
				//Libram of Divine Judgement
				case 43747:
					{
						if( CastingSpell == NULL )
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_COMMAND && CastingSpell->NameHash != SPELL_HASH_JUDGEMENT)
							continue;
					}break;
				// Flametongue Totem
				/*case 25555:
				case 16389:
				case 10523:
				case 8248:
				case 8253:*/
				// Shaman - Flametongue Weapon
				case 8026:
				case 8028:
				case 8029:
				case 10445:
				case 16343:
				case 16344:
				case 25488:
				case 58786:
				case 58787:
				case 58788:
				{
					spellId = 10444;	// Flametongue Weapon proc
					Item * mh = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );

					if( mh != NULL)
					{
						float mhs = float( mh->GetProto()->Delay );
						dmg_overwrite = FL2UINT( mhs * 0.001f * (spe->EffectBasePoints[0] + 1)/88 );
					}
					else
						continue;
				}break;
				
				// Shaman - Clearcasting
				case 16246:
				{
					if(origId == 39805)
						continue; // Lightning Overload Proc is already free
					if(CastingSpell->NameHash!=SPELL_HASH_LIGHTNING_BOLT && CastingSpell->NameHash!=SPELL_HASH_CHAIN_LIGHTNING && CastingSpell->NameHash!=SPELL_HASH_EARTH_SHOCK && CastingSpell->NameHash!=SPELL_HASH_FLAME_SHOCK && CastingSpell->NameHash!=SPELL_HASH_FROST_SHOCK)
						continue;
				}break;
				// Shaman - windfury weapon
				case 25504:
				{
					if(!IsPlayer())	continue;
					Item * mh = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
					if(!mh) continue;
					uint32 apBonus = 46; // use rank 1 bonus as default
					EnchantmentInstance * ei = mh->GetEnchantment(1);
					if(!ei)	continue;
					EnchantEntry * e = ei->Enchantment;
					if(!e) continue;
					switch(e->Id)
					{
						case 284: apBonus = 119; break;
						case 525: apBonus = 249; break;
						case 1669: apBonus = 333; break;
						case 2636: apBonus = 445; break;
						case 3785: apBonus = 835; break;
						case 3786: apBonus = 1090; break;
						case 3787: apBonus = 1250; break;
					}	
					float mhs = float( mh->GetProto()->Delay );
					// Calculate extra AP bonus damage
					uint32 extra_dmg=float2int32(mhs * apBonus / 14000.0f);
					Strike( victim, MELEE, spe, extra_dmg, 0, 0, false, false );
					Strike( victim, MELEE, spe, extra_dmg, 0, 0, false, false );
					spellId = 33010; // WF animation
				}break;
				//rogue - Ruthlessness
				case 14157:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//we need a finishing move for this
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE) || victim==this)
							continue;
					//should fix issue with combo points
					if(IsPlayer())
						{
							static_cast<Player*>(this)->m_spellcomboPoints++;
							static_cast<Player*>(this)->UpdateComboPoints();
						}
					}break;
				//rogue - Relentless Strikes
				case 14181:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						int32 proc_Chance;
						//chance is based actually on combopoint count and not 100% always
						if( CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE && IsPlayer())
							proc_Chance = static_cast< Player* >( this )->m_comboPoints*ospinfo->EffectBasePoints[1];
						else continue;
						if(!Rand(proc_Chance))
							continue;
					}break;
				//rogue - Find Weakness
				case 31234:
				case 31235:
				case 31236:
				case 31237:
				case 31238:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE))
							continue;
					}break;
				//rogue - Initiative
				case 13977:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//we need a Ambush, Garrote, or Cheap Shot
						if( CastingSpell == NULL )
							continue;

						if( CastingSpell->NameHash != SPELL_HASH_CHEAP_SHOT && //Cheap Shot
							CastingSpell->NameHash != SPELL_HASH_AMBUSH && //Ambush
							CastingSpell->NameHash != SPELL_HASH_GARROTE )  //Garrote
							continue;
					}break;
				//Priest - Shadowguard
				case 28377:
				case 28378:
				case 28379:
				case 28380:
				case 28381:
				case 28382:
				case 28385:
					{
						if( CastingSpell && ( this == victim || !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) ) ) //no self casts allowed or beneficial spells
							continue;//we can proc on ranged weapons too
					}break;
				//Priest - blackout
				case 15269:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						if( CastingSpell->School != SCHOOL_SHADOW || !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
							continue;
					}break;
				//warrior - improved berserker rage
				case 23690:
				case 23691:
					{
						if( !CastingSpell || CastingSpell->NameHash != SPELL_HASH_BERSERKER_RAGE )
							continue;
					}break;
				//mage - Arcane Concentration
				case 12536:
					{
						//requires damageing spell
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
							continue;
					}break;
				//mage - Improved Blizzard
				case 12484:
				case 12485:
				case 12486:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_BLIZZARD || victim == this ) //Blizzard
							continue;
					}break;
				//mage - Master of Elements
				case 29077:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->School!=SCHOOL_FIRE && CastingSpell->School!=SCHOOL_FROST) //fire and frost critical's
							continue;
						dmg_overwrite = CastingSpell->manaCost * ( ospinfo->EffectBasePoints[0] + 1 ) / 100;
					}break;
				//Hunter - The Beast Within
				case 34471:
					{
						if( CastingSpell == NULL )
							continue;

						if( CastingSpell->Id != 19574 )
							continue;
					}
				//Hunter - Thrill of the Hunt
				case 34720:
					{
						if( CastingSpell == NULL )
							continue;
						dmg_overwrite = CastingSpell->manaCost * 40 / 100;
					}break;
				//priest - Reflective Shield
				case 33619:
					{
						if (  !abs )
							continue;

						//requires Power Word: Shield active
						int power_word_id = HasAurasWithNameHash( SPELL_HASH_POWER_WORD__SHIELD );
						if( !power_word_id )
							power_word_id = 17;
						//make a direct strike then exit rest of handler
						int tdmg = abs * ( ospinfo->EffectBasePoints[0] + 1 ) / 100;
						//somehow we should make this not caused any threat (to be done)
						SpellNonMeleeDamageLog( victim, power_word_id, tdmg, false, true );
						continue;
					}break;
				//rogue - improved sprint
				case 30918:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_SPRINT || victim != this ) //sprint
							continue;
					}break;
				//rogue - combat potency
				case 35542:
				case 35545:
				case 35546:
				case 35547:
				case 35548:
					{
						if( !IsPlayer() || !dmg )
							continue;
						//this needs offhand weapon
						Item* it = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
						if( it == NULL || it->GetProto()->InventoryType != INVTYPE_WEAPON )
							continue;
					}break;
				//paladin - Improved Lay on Hands
				case 20233:
				case 20236:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_LAY_ON_HANDS )
							continue;
					}break;
				//paladin - Infusion of Light
				case 53672:
				case 54149:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_HOLY_SHOCK )
							continue;
					}break;
				//paladin - Sacred Cleansing
				case 53659:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_CLEANSE )
							continue;
					}break;
				//paladin - Judgements of the Pure
				case 53655:
				case 53656:
				case 53657:
				case 54152:
				case 54153:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->Id != 53408 &&
							CastingSpell->Id != 53407 &&
							CastingSpell->Id != 20271 )
							continue;
					}break;
				case 21183: //Paladin - Heart of the Crusader
				case 54498:
				case 54499:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->Id != 53408 &&
							CastingSpell->Id != 53407 &&
							CastingSpell->Id != 20271 )
							continue;
					}break;
				case 54203: //Paladin - Sheath of Light 
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_FLASH_OF_LIGHT &&
							CastingSpell->NameHash != SPELL_HASH_HOLY_LIGHT )
							continue;
						SpellEntry* spellInfo = dbcSpell.LookupEntry( 54203 ); 
						SpellDuration* sd = dbcSpellDuration.LookupEntryForced( spellInfo->DurationIndex );
						uint32 tickcount = GetDuration( sd ) / spellInfo->EffectAmplitude[0] ;
						dmg_overwrite = ospinfo->EffectBasePoints[0] * dmg / (100  * tickcount );
					}break;
				case 59578: //Paladin - Art of War
				case 53489:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->Id != 53408 &&
							CastingSpell->Id != 53407 &&
							CastingSpell->Id != 20271 &&
							CastingSpell->NameHash != SPELL_HASH_DIVINE_STORM &&
							CastingSpell->NameHash != SPELL_HASH_CRUSADER_STRIKE )
							continue;
					}break;
				//paladin - Spiritual Attunement
				case 31786:
					{
						if( CastingSpell == NULL )
							continue;
						//trigger only on heal spell cast by NOT us
						if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ) || this == victim )
							continue;
						//this is not counting the bonus effects on heal
						dmg_overwrite = (CastingSpell->EffectBasePoints[IsHealingSpell(CastingSpell)-1] + 1) * (ospinfo->EffectBasePoints[0] + 1 ) / 100;
					}break;
				//paladin - Light's Grace
				case 31834:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						if( CastingSpell->NameHash != SPELL_HASH_HOLY_LIGHT )
							continue;
					}break;
				//paladin - Eye for an Eye
				case 25997:
					{
						if( victim == this )
							continue; //not self-cast crits
						//requires damaging spell
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;

						//this should contain the same values as the fixed ones
						dmg_overwrite = ( dmg *  (ospinfo->EffectBasePoints[0] + 1 )) / 100 ; //only half dmg

						int32 half_health = this->GetUInt32Value(UNIT_FIELD_HEALTH) >> 1;
						if( dmg_overwrite > half_health )
							dmg_overwrite = half_health ;
					}break;
				//paladin - Blessed Life
				case 31828:
					{
						//we should test is damage is from environment or not :S
						resisted_dmg = dmg/2;
						continue; //there is no visual for this ?
					}break;
				//paladin - Judgements of the Wise
				case 54180:
					{
						if( CastingSpell == NULL )
							continue;
						if(	CastingSpell->Id != 53408 && CastingSpell->Id != 53407 && CastingSpell->Id != 20271 )
							continue;
						if( !IsPlayer() )
							continue;
						Player* c = static_cast< Player* >( this );
						if( !c->LastSeal )
							continue;
						SpellEntry *spellInfo = dbcSpell.LookupEntry( c->LastSeal );
						if( !spellInfo )
							continue;
					}break;
				case 54172: //Paladin - Divine Storm heal effect
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_DIVINE_STORM )
							continue;
					}break;
				//Energized
				case 43751:
					{
						if( CastingSpell == NULL )
							continue;
						if(	CastingSpell->NameHash != SPELL_HASH_LIGHTNING_BOLT )
							continue;
					}break;
				//Spell Haste Trinket
				//http://www.wowhead.com/?item=28190 scarab of the infinite circle
				case 33370:
					{
						if( CastingSpell == NULL )
							continue;
						if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
							continue;
					}break;
				case 60487: // Extract of Necromantic Power
					{
						if( CastingSpell == NULL )
							continue;
						if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
							continue;
					}break;
				case 33953: // The Egg of Mortal essence
					{
						if (!CastingSpell )
							continue;
						if( !(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING) )
							continue;
					}break;
				case 60529: // Forethough Talisman
					{
						if (!CastingSpell )
							continue;
						if( !(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING) )
							continue;
					}break;
				case 53390: //Tidal Waves
				{
					if (!CastingSpell )
						continue;
					if( CastingSpell->NameHash != SPELL_HASH_CHAIN_HEAL &&
						CastingSpell->NameHash != SPELL_HASH_RIPTIDE )
						continue;
				}break;
				//Earthliving
				case 51945:
				case 51990:
				case 51997:
				case 51998:
				case 51999:
				case 52000:
					{
						if (!CastingSpell )
							continue;
						if( !(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING) )
							continue;
					}break;
				//shaman - Lightning Overload
				case 39805:
					{
						if( CastingSpell == NULL )
							continue;//this should not occur unless we made a fuckup somewhere
						//trigger on lightning and chain lightning. Spell should be identical , well maybe next time :P
						if(	CastingSpell->NameHash == SPELL_HASH_LIGHTNING_BOLT || CastingSpell->NameHash == SPELL_HASH_CHAIN_LIGHTNING )
						{
							CastSpell(this, 39805, true);
							spellId = CastingSpell->Id;
							origId = 39805;
						}
						else continue;
					}break;
				//item - Band of the Eternal Sage
				case 35084:
					{
						if( CastingSpell == NULL )
							continue;
						if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) ) //requires offensive spell. ! might not cover all spells
							continue;
					}break;
					//druid - Earth and Moon
                  case 60431:
                  case 60432:
                  case 60433:
                      {
                          if ( CastingSpell == NULL)
                                   continue;
                          if ( CastingSpell->NameHash != SPELL_HASH_WRATH &&
                               CastingSpell->NameHash != SPELL_HASH_STARFIRE )
                                   continue;
                      }break;
				// druid - Celestial Focus
				case 16922:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_STARFIRE )
							continue;
					}break;
				case 37565: //setbonus
					{
						if (!CastingSpell || CastingSpell->NameHash != SPELL_HASH_FLASH_HEAL)
							continue;
					}break;
				//SETBONUSES
				case 37379:
					{
						if (!CastingSpell || CastingSpell->School != SCHOOL_SHADOW || !(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;
					}break;
				case 37378:
					{
						if (!CastingSpell || CastingSpell->School != SCHOOL_FIRE || !(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;
					}break;
				case 45062: // Vial of the Sunwell
				case 39950:	// Wave Trance
					{
						if (!CastingSpell ||  !(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))
							continue;
					}break;
				case 37234:
				case 37214:
				case 37601:
					{
						if (!CastingSpell ||  !(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;
					}break;
				case 37237:
					{
						if (!CastingSpell || CastingSpell->NameHash != SPELL_HASH_LIGHTNING_BOLT)
							continue;
					}break;
				//Tier 7 Warlock setbonus
				case 61082:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_LIFE_TAP )
							continue;
					}break;
				case 37193:
					{
						if (!CastingSpell || CastingSpell->NameHash != SPELL_HASH_HOLY_SHIELD)
							continue;
					}break;
				case 37196:
				case 43838:
					{
						if (!CastingSpell)
							continue;
							//CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_THE_CRUSADER &&
						if (CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_JUSTICE &&
							CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_LIGHT &&
							CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_WISDOM &&
							CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_RIGHTEOUSNESS &&
							CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_BLOOD &&
							CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_VENGEANCE &&
							CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_COMMAND)
							continue;
					}break;
				case 43837:
					{
						if (!CastingSpell || (CastingSpell->NameHash != SPELL_HASH_FLASH_OF_LIGHT && CastingSpell->NameHash != SPELL_HASH_HOLY_LIGHT))
							continue;
					}break;
				case 37529:
					{
						if (!CastingSpell || CastingSpell->NameHash != SPELL_HASH_OVERPOWER)
							continue;
					}break;
				case 37517:
					{
						if (!CastingSpell || CastingSpell->Id == 37517 || CastingSpell->NameHash != SPELL_HASH_REVENGE)
							continue;
					}break;
				case 38333: // Ribbon of Sacrifice
					{
						if( !CastingSpell || !( CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ) )
							continue;
					}
				//SETBONUSES END
					//http://www.wowhead.com/?item=32493 Ashtongue Talisman of Shadows
				case 40480:
					{
						if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_CORRUPTION )
							continue;
					}break;

					//http://www.wowhead.com/?item=32496  Memento of Tyrande
				case 37656: //don't say damaging spell but EACH time spell is cast there is a chance (so can be healing spell)
					{
						if( CastingSpell == NULL )
							continue;
					}break;
				//http://www.wowhead.com/?item=32488 Ashtongue Talisman of Insight
				case 40483:
					{
						if( CastingSpell == NULL )
							continue;
						if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
							continue;
					}break;

					//http://www.wowhead.com/?item=32487 Ashtongue Talisman of Swiftness
				case 40487:
					{
						if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_STEADY_SHOT)
							continue;
					}break;

					//http://www.wowhead.com/?item=32485 Ashtongue Talisman of Valor
				case 40459:
					{
						if( CastingSpell == NULL || (CastingSpell->NameHash != SPELL_HASH_MORTAL_STRIKE && CastingSpell->NameHash != SPELL_HASH_BLOODTHIRST && CastingSpell->NameHash != SPELL_HASH_SHIELD_SLAM))
							continue;
					}break;
				case 28804://Epiphany :Each spell you cast can trigger an Epiphany, increasing your mana regeneration by 24 for 30 sec.
					{
						if (!CastingSpell)
							continue;
					}break;
				//SETBONUSES END
				//item - Band of the Eternal Restorer
				case 35087:
					{
						if( CastingSpell == NULL )
							continue;
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING)) //requires healing spell.
							continue;
					}break;

					//http://www.wowhead.com/?item=32486 Ashtongue Talisman of Equilibrium
				case 40452: //Mangle has a 40% chance to grant 140 Strength for 8 sec
					{
						if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_MANGLE___BEAR || CastingSpell->NameHash != SPELL_HASH_MANGLE___CAT)
							continue;
					}break;
				case 40445: //Starfire has a 25% chance to grant up to 150 spell damage for 8 sec
					{
						if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_STARFIRE)
							continue;
					}break;
				case 40446: //Rejuvenation has a 25% chance to grant up to 210 healing for 8 sec
					{
						if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_REJUVENATION)
							continue;
					}break;

					//http://www.wowhead.com/?item=32490 Ashtongue Talisman of Acumen
				case 40441: //Each time your Shadow Word: Pain deals damage, it has a 10% chance to grant you 220 spell damage for 10 sec
					{
						if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_SHADOW_WORD__PAIN)
							continue;
					}break;

					//http://www.wowhead.com/?item=32490 Ashtongue Talisman of Acumen
				case 40440: //Each time your Renew heals, it has a 10% chance to grant you 220 healing for 5 sec
					{
						if( CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_RENEW)
							continue;
					}break;

					//http://www.wowhead.com/?item=32492 Ashtongue Talisman of Lethality
				case 40461:
					{
						if( CastingSpell == NULL )
							continue;
						//we need a finishing move for this
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE) || victim==this)
							continue;
					}break;
				case 37445: //using a mana gem grants you 225 spell damage for 15 sec
					{
						if (!CastingSpell || CastingSpell->NameHash != SPELL_HASH_REPLENISH_MANA)
							continue;
					}break;
				case 16886: // druid - Nature's Grace
					{
						// Remove aura if it exists so it gets reapplied
						if (HasAura(16886))
							RemoveAura(16886);
					}break;
				/*case 38395:
					{
						if( CastingSpell == NULL )
							continue;
						if( CastingSpell->NameHash != SPELL_HASH_IMMOLATE &&
							CastingSpell->NameHash != SPELL_HASH_CORRUPTION)
							continue;
					}break;*/
			}
		}
		else
		{
			switch( spellId )
			{
				case 14189: //Seal Fate
				case 16953: //Blood Frenzy
				case 16959: //Primal Fury
				{
					if( !CastingSpell ||
						CastingSpell->Id == 14189 ||
						CastingSpell->Id == 16953 ||
						CastingSpell->Id == 16959 )
						continue;
				}break;

			}
		}

		if( spellId == 17364 || spellId == 32175 || spellId == 32176 ) //Stormstrike
			continue;
		if( spellId==22858 && isInBack(victim) ) //retatliation needs target to be not in front. Can be cast by creatures too
			continue;

		SpellCastTargets targets;
		if( itr2->procFlags & PROC_TARGET_SELF )
			targets.m_unitTarget = GetGUID();
		else
			targets.m_unitTarget = victim->GetGUID();

		SpellEntry *spellInfo = dbcSpell.LookupEntry(spellId );
		Spell *spell = SpellPool.PooledNew();
		if (!spell)
			return 0;

		spell->Init(this, spellInfo ,true, NULL);
		spell->forced_basepoints[0] = dmg_overwrite;
		spell->ProcedOnSpell = CastingSpell;
		//Spell *spell = new Spell(this,spellInfo,false,0,true,false);
		if( spellId == 974 || spellId == 32593 || spellId == 32594 || spellId == 49283 || spellId == 49284 ) // Earth Shield handler
		{
			spell->pSpellId=itr2->spellId;
			spell->SpellEffectDummy(0);
			SpellPool.PooledDelete(spell);
			spell = NULL;
			continue;
		}
		spell->pSpellId=origId;
		spell->prepare(&targets);

		if (origId == 39805)
		{
			// Remove lightning overload aura after procing
			RemoveAura(39805);
		}
	}

	m_chargeSpellsInUse = true;
	std::map<uint32, struct SpellCharge>::iterator iter, iter2;
	iter = m_chargeSpells.begin();

	while( iter != m_chargeSpells.end() )
	{
		iter2 = iter++;

		if(iter2->second.count)
		{
			if( (iter2->second.ProcFlag & flag) )
			{
				//Fixes for spells that don't lose charges when dmg is absorbed
				if( iter2->second.ProcFlag==680 && dmg==0 ) 
					continue;

				if( CastingSpell )
				{
					SpellCastTime *sd = dbcSpellCastTime.LookupEntry(CastingSpell->CastingTimeIndex);
					if( !sd ) 
						continue; // this shouldn't happen though :P

					//if we did not proc these then we should not remove them
					if( CastingSpell->Id == iter2->second.spellId )
						continue;

					switch( iter2->second.spellId )
					{
					case 43339: // Shaman - Shamanist Focus
						{
							if( CastingSpell->NameHash != SPELL_HASH_EARTH_SHOCK &&
								CastingSpell->NameHash != SPELL_HASH_FLAME_SHOCK &&
								CastingSpell->NameHash != SPELL_HASH_FROST_SHOCK )
								continue;
						}break;
					case 12043: // Mage - Presence of Mind
						{
							//if(!sd->CastTime||sd->CastTime>10000) continue;
							if( sd->CastTime == 0 )
								continue;
						}break;
					case 17116: // Shaman - Nature's Swiftness
					case 16188:	// Druid - Nature's Swiftness
						{
							//if( CastingSpell->School!=SCHOOL_NATURE||(!sd->CastTime||sd->CastTime>10000)) continue;
							if( CastingSpell->School!=SCHOOL_NATURE || sd->CastTime==0 ) 
								continue;
						}break;
					case 16166:
						{
							if( !( CastingSpell->School == SCHOOL_FIRE || CastingSpell->School == SCHOOL_FROST || CastingSpell->School == SCHOOL_NATURE ) )
								continue;
						}break;
					case 14177: // Cold blood will get removed on offensive spell
						{
							if( CastingSpell == NULL || CastingSpell->Id == 36554 || victim==this || isFriendly(this, victim) )
								continue;
						}break;
					case 46916: // Bloodsurge - Slam! effect should dissapear after casting Slam only
						{
							if( CastingSpell->NameHash != SPELL_HASH_SLAM )
								continue;
						}break;
					case 60503: // Taste for Blood should dissapear after casting Overpower
						{
							if( CastingSpell->NameHash != SPELL_HASH_OVERPOWER )
								continue;
						}break;
					case 23694: // Imp. Hamstring
						{
							if( CastingSpell->NameHash != SPELL_HASH_IMPROVED_HAMSTRING )
								continue;
						}break;
					case 65156: // Juggernaut
						{
							if( CastingSpell->NameHash != SPELL_HASH_MORTAL_STRIKE &&
								CastingSpell->NameHash != SPELL_HASH_SLAM )
								continue;
						}break;
					case 20216:
						{
							if( CastingSpell->NameHash != SPELL_HASH_FLASH_OF_LIGHT && CastingSpell->NameHash != SPELL_HASH_HOLY_LIGHT && CastingSpell->NameHash != SPELL_HASH_HOLY_SHOCK )
								continue;
						}break;
					}
				}
				if( iter2->second.lastproc != 0 )
				{
					if( iter2->second.procdiff > 3000 )
					{
						//--(iter2->second.count);
						RemoveAura(iter2->second.spellId);
					}
				}
				else
				{
					//--(iter2->second.count);		// done in Aura::Remove
					this->RemoveAura(iter2->second.spellId);
				}
			}
		}
		if( !iter2->second.count )
		{
			m_chargeSpells.erase(iter2);
		}
	}

	for( ;!m_chargeSpellRemoveQueue.empty(); )
	{
		iter = m_chargeSpells.find( m_chargeSpellRemoveQueue.front() );
		if( iter != m_chargeSpells.end() )
		{
			if( iter->second.count > 1 )
				--iter->second.count;
			else
				m_chargeSpells.erase(iter);
		}
		m_chargeSpellRemoveQueue.pop_front();
	}

	m_chargeSpellsInUse = false;
	if( can_delete ) //are we the upper level of nested procs ? If yes then we can remove the lock
		bProcInUse = false;

	return resisted_dmg;
}

//damage shield is a triggered spell by owner to atacker
void Unit::HandleProcDmgShield(uint32 flag, Unit* attacker)
{
	//make sure we do not loop dmg procs
	if(this==attacker || !attacker)
		return;
	if(m_damgeShieldsInUse)
		return;
	m_damgeShieldsInUse = true;
	//charges are already removed in handleproc
	WorldPacket data(24);
	std::list<DamageProc>::iterator i;
	std::list<DamageProc>::iterator i2;
	for(i = m_damageShields.begin();i != m_damageShields.end();)     // Deal Damage to Attacker
	{
		i2 = i++; //we should not proc on proc.. not get here again.. not needed.Better safe then sorry.
		if(	(flag & (*i2).m_flags) )
		{
			if(PROC_MISC & (*i2).m_flags)
			{
				data.Initialize(SMSG_SPELLDAMAGESHIELD);
				data << this->GetGUID();
				data << attacker->GetGUID();
				data << (*i2).m_spellId;
				data << (*i2).m_damage;
				data << ( 1 << (*i2).m_school );
				SendMessageToSet(&data,true);
				this->DealDamage(attacker,(*i2).m_damage,0,0,(*i2).m_spellId);
			}
			else
			{
				SpellEntry	*ability=dbcSpell.LookupEntry((*i2).m_spellId);
				this->Strike( attacker, RANGED, ability, 0, 0, (*i2).m_damage, true, true );//can dmg shields miss at all ?
			}
		}
	}
	m_damgeShieldsInUse = false;
}

/*
void Unit::HandleProcSpellOnSpell(Unit* Victim,uint32 damage,bool critical)
{
}
*/
bool Unit::IsCasting()
{
	return (m_currentSpell != NULL);
}

bool Unit::IsInInstance()
{
	MapInfo *pMapinfo = WorldMapInfoStorage.LookupEntry(this->GetMapId());
	if(pMapinfo)
		return (pMapinfo->type != INSTANCE_NULL);

	return false;
}

void Unit::RegenerateHealth()
{
	m_H_regenTimer = 2000;//set next regen time

	if(!isAlive())
		return;

	// player regen
	if(this->IsPlayer())
	{
		// These only NOT in combat
		if(!CombatStatus.IsInCombat())
		{
			static_cast< Player* >( this )->RegenerateHealth(false);
		}
		else
			static_cast< Player* >( this )->RegenerateHealth(true);
	}
	else
	{
		// Only regen health out of combat
		if(!CombatStatus.IsInCombat())
			static_cast<Creature*>(this)->RegenerateHealth();
	}
}

void Unit::RegeneratePower(bool isinterrupted)
{
	// This is only 2000 IF the power is not rage
	if (isinterrupted)
		m_interruptedRegenTime = 2000;
	else
		m_P_regenTimer = 2000;//set next regen time

	if(!isAlive())
		return;

	//druids regen every tick, which is every 100ms, at one energy, as of 3.0.2
	//I don't know how mana has changed exactly, but it has, will research it - optical
	if (IsPlayer() && GetPowerType() == POWER_TYPE_ENERGY)
	{
		static_cast< Player* >( this )->RegenerateEnergy();
		// druids regen mana when shapeshifted
		if(getClass() == DRUID)
		{
			static_cast< Player* >( this )->RegenerateMana(isinterrupted);
		}
		return;
	}

	// player regen
	if(this->IsPlayer())
	{
		uint32 powertype = GetPowerType();
		switch(powertype)
		{
		case POWER_TYPE_MANA:
			static_cast< Player* >( this )->RegenerateMana(isinterrupted);
			break;

		case POWER_TYPE_RAGE:
			{
				// These only NOT in combat
				if(!CombatStatus.IsInCombat())
				{
					m_P_regenTimer = 3000;
					if (static_cast< Player* >( this )->HasAura(12296))
					{
						static_cast< Player* >( this )->LooseRage(20);
					}
					else
						static_cast< Player* >( this )->LooseRage(30);
				}
				else
				{
					if (static_cast< Player* >( this )->HasAura(12296))
					{
						m_P_regenTimer = 3000;
						static_cast< Player* >( this )->LooseRage(-10);
					}
				}

			}break;

		case POWER_TYPE_RUNIC_POWER:
			{
				if(!CombatStatus.IsInCombat())
				{
					uint32 cur = GetUInt32Value(UNIT_FIELD_POWER7);
					SetPower(POWER_TYPE_RUNIC_POWER, cur - 20);
				}
			}break;
		}

		/*

		There is a problem here for druids.
		Druids when shapeshifted into bear have 2 power with different regen timers
		a) Mana (which regenerates while shapeshifted
		b) Rage

		Mana has a regen timer of 2 seconds
		Rage has a regen timer of 3 seconds

		I think the only viable way of fixing this is to have 2 different timers
		to check each individual power.

		Atm, mana is being regen at 3 seconds while shapeshifted...

		*/


		// druids regen mana when shapeshifted
		if(getClass() == DRUID && powertype != POWER_TYPE_MANA)
			static_cast< Player* >( this )->RegenerateMana(isinterrupted);
	}
	else
	{
		uint32 powertype = GetPowerType();
		switch(powertype)
		{
		case POWER_TYPE_MANA:
			static_cast<Creature*>(this)->RegenerateMana();
			break;
		case POWER_TYPE_FOCUS:
			static_cast<Creature*>(this)->RegenerateFocus();
			m_P_regenTimer = 4000;
			break;
		}
	}
}

double Unit::GetResistanceReducion(Unit* pVictim, uint32 school, float armorReducePct)
{
	double reduction = 0.0;
	float resistance = (float) pVictim->GetResistance(school);
	if(school == 0) // physical
	{
		if(this->IsPlayer()) // apply armor penetration
			resistance -= resistance * (armorReducePct + static_cast<Player*>(this)->CalcRating( PLAYER_RATING_MODIFIER_ARMOR_PENETRATION_RATING )) / 100.0f;
		if(getLevel() < 60) reduction = double(resistance) / double(resistance+400+(85*getLevel()));
		else if(getLevel() > 59 && getLevel() < 80) reduction = double(resistance) / double(resistance-22167.5+(467.5*getLevel()));
		else reduction = double(resistance) / double(resistance+15232.5);
	} else { // non-physical
		double RResist = resistance + float((pVictim->getLevel() > getLevel()) ? (pVictim->getLevel() - this->getLevel()) * 5 : 0) - PowerCostPctMod[school]; 
		reduction = RResist / (double)(getLevel() * 5) * 0.75f;
	}
	if(reduction > 0.75) reduction = 0.75;
	else if(reduction < 0) reduction = 0;

	return reduction;
}

void Unit::CalculateResistanceReduction(Unit *pVictim,dealdamage * dmg, SpellEntry* ability, float ArmorPctReduce)
{
	/*float AverageResistance = 0.0f;
	float ArmorReduce;

	
	if((*dmg).school_type == 0)//physical
	{
		if(this->IsPlayer())
			ArmorReduce = PowerCostPctMod[0]+ ((float)pVictim->GetResistance(0) * (ArmorPctReduce + static_cast<Player*>(this)->CalcRating( PLAYER_RATING_MODIFIER_ARMOR_PENETRATION_RATING )) / 100.0f);
		else
			ArmorReduce = 0.0f;

		if(ArmorReduce >= pVictim->GetResistance(0))		// fully penetrated :O
			return;

//		double Reduction = double(pVictim->GetResistance(0)) / double(pVictim->GetResistance(0)+400+(85*getLevel()));
		//dmg reduction formula from xinef
		double Reduction = 0;
		if(getLevel() < 60) Reduction = double(pVictim->GetResistance(0) - ArmorReduce) / double(pVictim->GetResistance(0)+400+(85*getLevel()));
		else if(getLevel() > 59 && getLevel() < PLAYER_LEVEL_CAP) Reduction = double(pVictim->GetResistance(0) - ArmorReduce) / double(pVictim->GetResistance(0)-22167.5+(467.5*getLevel()));
		//
		else Reduction = double(pVictim->GetResistance(0) - ArmorReduce) / double(pVictim->GetResistance(0)+10557.5);
		if(Reduction > 0.75f) Reduction = 0.75f;
		else if(Reduction < 0) Reduction = 0;
		if(Reduction) dmg[0].full_damage = (uint32)(dmg[0].full_damage*(1-Reduction));	  // no multiply by 0
	}
	else
	{
		// applying resistance to other type of damage
		int32 RResist = float2int32( float(pVictim->GetResistance( (*dmg).school_type ) + ((pVictim->getLevel() > getLevel()) ? (pVictim->getLevel() - this->getLevel()) * 5 : 0)) - PowerCostPctMod[(*dmg).school_type] );
		if (RResist<0)
			RResist = 0;
		Log.Notice("school", "RResist = %u", RResist);
		AverageResistance = (float)(RResist) / (float)(getLevel() * 5) * 0.75f;
		  if(AverageResistance > 0.75f)
			AverageResistance = 0.75f;
		Log.Notice("school", "AverageResistance = %f", AverageResistance);
		  // NOT WOWWIKILIKE but i think it's actually to add some fullresist chance from resistances
		  if (!ability || !(ability->Attributes & ATTRIBUTES_IGNORE_INVULNERABILITY))
		  {
			  float Resistchance=(float)pVictim->GetResistance( (*dmg).school_type)/(float)pVictim->getLevel();
			  Resistchance*=Resistchance;
			  if(Rand(Resistchance))
				  AverageResistance=1.0f;
		  }

		if(AverageResistance>0)
			(*dmg).resisted_damage = (uint32)(((*dmg).full_damage)*AverageResistance);
		else
			(*dmg).resisted_damage=0;
	}*/
	if(dmg->school_type && ability && Spell::IsBinary(ability))	// damage isn't reduced for binary spells
	{
		(*dmg).resisted_damage = 0;
		return;
	}

	double reduction = GetResistanceReducion(pVictim, dmg->school_type, ArmorPctReduce);

	// only for physical or non binary spells
	if(reduction>0)
		(*dmg).resisted_damage = (uint32)(((*dmg).full_damage)*reduction);
	else 
		(*dmg).resisted_damage = 0; 
}

uint32 Unit::GetSpellDidHitResult( Unit* pVictim, uint32 weapon_damage_type, SpellEntry* ability )
{
	Item * it = NULL;
	float hitchance          = 0.0f;
	float dodge				 = 0.0f;
	float parry				 = 0.0f;
	float block				 = 0.0f;

	float hitmodifier		 = 0;
	int32 self_skill;
	int32 victim_skill;
	uint32 SubClassSkill	 = SKILL_UNARMED;

	bool backAttack			 = !pVictim->isInFront( this ); // isInBack is bugged!
	uint32 vskill            = 0;

	//==========================================================================================
	//==============================Victim Skill Base Calculation===============================
	//==========================================================================================
	if( pVictim->IsPlayer() )
	{
		vskill = static_cast< Player* >( pVictim )->_GetSkillLineCurrent( SKILL_DEFENSE );
		if( weapon_damage_type != RANGED && !backAttack )
		{
			//--------------------------------block chance----------------------------------------------
			block = pVictim->GetFloatValue(PLAYER_BLOCK_PERCENTAGE); //shield check already done in Update chances
			//--------------------------------dodge chance----------------------------------------------
			if( pVictim->m_stunned <= 0 )
			{
				dodge = pVictim->GetFloatValue( PLAYER_DODGE_PERCENTAGE );
			}
			//--------------------------------parry chance----------------------------------------------
			if( pVictim->can_parry && !pVictim->disarmed )
			{
				if( static_cast< Player* >( pVictim )->HasSpell( 3127 ) || static_cast< Player* >( pVictim )->HasSpell( 18848 ) )
				{
					parry = pVictim->GetFloatValue( PLAYER_PARRY_PERCENTAGE );
				}
			}
		}
		victim_skill = float2int32( vskill + static_cast< Player* >( pVictim )->CalcRating( PLAYER_RATING_MODIFIER_DEFENCE ) );
	}
	//--------------------------------mob defensive chances-------------------------------------
	else
	{
		if( weapon_damage_type != RANGED && !backAttack )
			dodge = pVictim->GetUInt32Value(UNIT_FIELD_STAT1) / 14.5f; // what is this value?
		victim_skill = pVictim->getLevel() * 5;
		if(pVictim->m_objectTypeId == TYPEID_UNIT)
		{
			Creature * c = (Creature*)(pVictim);
			if( c->GetCreatureInfo() && c->GetCreatureInfo()->Rank == ELITE_WORLDBOSS )
			{
				victim_skill = std::max(victim_skill,((int32)this->getLevel()+3)*5); //used max to avoid situation when lowlvl hits boss.
			}
		}
	}
	//==========================================================================================
	//==============================Attacker Skill Base Calculation=============================
	//==========================================================================================
	if(this->IsPlayer())
	{
		self_skill = 0;
		Player* pr = static_cast< Player* >( this );
		hitmodifier = pr->GetHitFromMeleeSpell();

		switch( weapon_damage_type )
		{
		case MELEE:   // melee main hand weapon
			it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
			hitmodifier += pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL ) );
			break;
		case OFFHAND: // melee offhand weapon (dualwield)
			it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
			hitmodifier += pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_OFF_HAND_SKILL ) );
			break;
		case RANGED:  // ranged weapon
			it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_RANGED );
			hitmodifier += pr->CalcRating( PLAYER_RATING_MODIFIER_RANGED_HIT );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_RANGED_SKILL ) );
			break;
		}

		// erm. some spells don't use ranged weapon skill but are still a ranged spell and use melee stats instead
		// i.e. hammer of wrath
		if( ability && ability->NameHash == SPELL_HASH_HAMMER_OF_WRATH )
		{
			it = pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
			hitmodifier += pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL ) );
		}
		if(it && it->GetProto())
			SubClassSkill = GetSkillByProto(it->GetProto()->Class,it->GetProto()->SubClass);
		else
			SubClassSkill = SKILL_UNARMED;

		if(SubClassSkill==SKILL_FIST_WEAPONS)
			SubClassSkill = SKILL_UNARMED;

		//chances in feral form don't depend on weapon skill
		if(static_cast< Player* >( this )->IsInFeralForm())
		{
			uint8 form = static_cast< Player* >( this )->GetShapeShift();
			if(form == FORM_CAT || form == FORM_BEAR || form == FORM_DIREBEAR)
			{
				SubClassSkill = SKILL_FERAL_COMBAT;
				// Adjust skill for Level * 5 for Feral Combat
				self_skill += pr->getLevel() * 5;
			}
		}


		self_skill += pr->_GetSkillLineCurrent(SubClassSkill);
	}
	else
	{
		self_skill = this->getLevel() * 5;
		if(m_objectTypeId == TYPEID_UNIT)
		{
			Creature * c = (Creature*)(this);
			if( c->GetCreatureInfo()&&c->GetCreatureInfo()->Rank == ELITE_WORLDBOSS )
				self_skill = std::max(self_skill,((int32)pVictim->getLevel()+3)*5);//used max to avoid situation when lowlvl hits boss.
		}
	}
	//==========================================================================================
	//==============================Special Chances Base Calculation============================
	//==========================================================================================
	//<THE SHIT> to avoid Linux bug.
	float diffVcapped = (float)self_skill;
	if(int32(pVictim->getLevel()*5)>victim_skill)
		diffVcapped -=(float)victim_skill;
	else
		diffVcapped -=(float)(pVictim->getLevel()*5);

	float diffAcapped = (float)victim_skill;
	if(int32(this->getLevel()*5)>self_skill)
		diffAcapped -=(float)self_skill;
	else
		diffAcapped -=(float)( getLevel() * 5 );
	//<SHIT END>

	//--------------------------------by victim state-------------------------------------------
	if(pVictim->IsPlayer()&&pVictim->GetStandState()) //every not standing state is >0
	{
		hitchance = 100.0f;
	}

	//--------------------------------by damage type and by weapon type-------------------------
	if( weapon_damage_type == RANGED )
	{
		dodge=0.0f;
		parry=0.0f;
	}

	//--------------------------------by skill difference---------------------------------------
	float vsk = (float)self_skill - (float)victim_skill;
	dodge = std::max( 0.0f, dodge - vsk * 0.04f );
	if( parry )
		parry = std::max( 0.0f, parry - vsk * 0.04f );
	if( block )
		block = std::max( 0.0f, block - vsk * 0.04f );

	if( vsk > 0 )
		hitchance = std::max( hitchance, 95.0f + vsk * 0.02f + hitmodifier );
	else
	{
		if( pVictim->IsPlayer() )
			hitchance = std::max( hitchance, 95.0f + vsk * 0.1f + hitmodifier ); //wowwiki multiplier - 0.04 but i think 0.1 more balanced
		else
			hitchance = std::max( hitchance, 100.0f + vsk * 0.6f + hitmodifier ); //not wowwiki but more balanced
	}

	if( ability && ability->SpellGroupType )
	{
		SM_FFValue( SM_FHitchance, &hitchance, ability->SpellGroupType );
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
		float spell_flat_modifers=0;
		SM_FFValue(SM_FHitchance,&spell_flat_modifers,ability->SpellGroupType);
		if(spell_flat_modifers!=0 )
			printf("!!!!!spell resist mod flat %f,  spell resist bonus %f, spell group %u\n",spell_flat_modifers,hitchance,ability->SpellGroupType);
#endif
	}

	if( ability && ability->Attributes & ATTRIBUTES_CANT_BE_DPB )
	{
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
	}

	//==========================================================================================
	//==============================One Roll Processing=========================================
	//==========================================================================================
	//--------------------------------cumulative chances generation----------------------------
	float chances[4];
	chances[0]=std::max(0.0f,100.0f-hitchance);
	chances[1]=chances[0]+dodge;
	chances[2]=chances[1]+parry;
	chances[3]=chances[2]+block;


	//--------------------------------roll------------------------------------------------------
	float Roll = RandomFloat(100.0f);
	uint32 r = 0;
	while (r<4&&Roll>chances[r])
	{

		r++;
	}

	uint32 roll_results[5] = { SPELL_DID_HIT_MISS,SPELL_DID_HIT_DODGE,SPELL_DID_HIT_DEFLECT,SPELL_DID_HIT_BLOCK,SPELL_DID_HIT_SUCCESS };
	return roll_results[r];
}

void Unit::Strike( Unit* pVictim, uint32 weapon_damage_type, SpellEntry* ability, int32 add_damage, int32 pct_dmg_mod, uint32 exclusive_damage, bool disable_proc, bool skip_hit_check )
{
//==========================================================================================
//==============================Unacceptable Cases Processing===============================
//==========================================================================================
	if( !pVictim || !pVictim->isAlive() || !isAlive()  || IsStunned() || IsPacified() || IsFeared() )
		return;

	if(!isInFront(pVictim))
	{
		if(IsPlayer())
		{
			static_cast< Player* >( this )->GetSession()->OutPacket(SMSG_ATTACKSWING_BADFACING);
			return;
		}
	}

//==========================================================================================
//==============================Variables Initialization====================================
//==========================================================================================
	dealdamage dmg			  = {0,0,0};

	Item * it = NULL;

	float hitchance          = 0.0f;
	float dodge				 = 0.0f;
	float parry				 = 0.0f;
	float glanc              = 0.0f;
	float block				 = 0.0f;
	float crit				 = 0.0f;
	float crush              = 0.0f;

	uint32 targetEvent		 = 0;
	uint32 hit_status		 = 0;

	uint32 blocked_damage	 = 0;
	int32  realdamage		 = 0;

	uint32 vstate			 = 1;
	uint32 aproc			 = 0;
	uint32 vproc			 = 0;

	float hitmodifier		 = 0;
	float ArmorPctReduce	 = m_ignoreArmorPct;
	int32 self_skill;
	int32 victim_skill;
	uint32 SubClassSkill	 = SKILL_UNARMED;

	bool backAttack			 = !pVictim->isInFront( this );
	uint32 vskill            = 0;
	bool disable_dR			 = false;

	if(ability)
		dmg.school_type = ability->School;
	else
	{
		if (GetTypeId() == TYPEID_UNIT)
			dmg.school_type = static_cast< Creature* >( this )->BaseAttackType;
		else
			dmg.school_type = SCHOOL_NORMAL;
	}

//==========================================================================================
//==============================Victim Skill Base Calculation===============================
//==========================================================================================
	if(pVictim->IsPlayer())
	{
		Player* plr = static_cast< Player* >( pVictim );
		vskill = plr->_GetSkillLineCurrent( SKILL_DEFENSE );

		if( !backAttack )
		{
			// not an attack from behind so we may dodge/parry/block

			//uint32 pClass = plr->getClass();
			//uint32 pLevel = (getLevel() > PLAYER_LEVEL_CAP) ? PLAYER_LEVEL_CAP : getLevel();

			if ( weapon_damage_type != RANGED )
			{
				// cannot dodge/parry ranged attacks

				if(pVictim->m_stunned<=0)
				{
					// can dodge as long as we're not stunned
					dodge = plr->GetDodgeChance();
				}

				if(pVictim->can_parry && !disarmed)
				{
					// can parry as long as we're not disarmed
					parry = plr->GetParryChance();
				}
			}
			// can block ranged attacks

			// Is an offhand equipped and is it a shield?
			Item* it = plr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
			if( it != NULL && it->GetProto()->InventoryType == INVTYPE_SHIELD )
			{
				block = plr->GetBlockChance();
			}
		}
		victim_skill = float2int32( vskill + floorf( plr->CalcRating( PLAYER_RATING_MODIFIER_DEFENCE ) ) );
	}
//--------------------------------mob defensive chances-------------------------------------
	else
	{
		// not a player, must be a creature
		Creature* c = static_cast< Creature* >( pVictim );

		// mobs can dodge attacks from behind
		if ( weapon_damage_type != RANGED && pVictim->m_stunned <= 0 )
		{
			dodge = pVictim->GetUInt32Value( UNIT_FIELD_AGILITY ) / 14.5f;
			dodge += pVictim->GetDodgeFromSpell();
		}

		if ( !backAttack )
		{
			// can parry attacks from the front
			// TODO different bosses have different parry rates (db patch?)
			if ( !disarmed ) // TODO this is wrong
			{
				parry = c->GetBaseParry();
				parry += pVictim->GetParryFromSpell();
			}

			// TODO add shield check/block chance here
			// how do we check what the creature has equipped?
		}

		victim_skill = pVictim->getLevel() * 5;
		if ( pVictim->m_objectTypeId == TYPEID_UNIT )
		{
			if ( c != NULL && c->GetCreatureInfo() && c->GetCreatureInfo()->Rank == ELITE_WORLDBOSS )
			{
				victim_skill = std::max( victim_skill, ( (int32)getLevel() + 3 ) * 5 ); //used max to avoid situation when lowlvl hits boss.
			}
		}
	}
//==========================================================================================
//==============================Attacker Skill Base Calculation=============================
//==========================================================================================
	if( this->IsPlayer() )
	{
		self_skill = 0;
		Player* pr = static_cast< Player* >( this );
		hitmodifier = pr->GetHitFromMeleeSpell();

		switch( weapon_damage_type )
		{
		case MELEE:   // melee main hand weapon
			it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL ) );
			if (it && it->GetProto())
			{
				dmg.school_type = it->GetProto()->Damage[0].Type;
				if( it->GetProto()->SubClass == ITEM_SUBCLASS_WEAPON_MACE )
					ArmorPctReduce += m_ignoreArmorPctMaceSpec;
			}
			break;
		case OFFHAND: // melee offhand weapon (dualwield)
			it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_OFF_HAND_SKILL ) );
			hit_status |= HITSTATUS_DUALWIELD;//animation
			if (it && it->GetProto())
			{
				dmg.school_type = it->GetProto()->Damage[0].Type;
				if( it->GetProto()->SubClass == ITEM_SUBCLASS_WEAPON_MACE )
					ArmorPctReduce += m_ignoreArmorPctMaceSpec;
			}
			break;
		case RANGED:  // ranged weapon
			it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_RANGED );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_RANGED_SKILL ) );
			if (it && it->GetProto())
				dmg.school_type = it->GetProto()->Damage[0].Type;
			break;
		}

		if(it && it->GetProto())
		{
			SubClassSkill = GetSkillByProto(it->GetProto()->Class,it->GetProto()->SubClass);
			if(SubClassSkill==SKILL_FIST_WEAPONS)
				SubClassSkill = SKILL_UNARMED;
		}
		else
			SubClassSkill = SKILL_UNARMED;


		//chances in feral form don't depend on weapon skill
		if(pr->IsInFeralForm())
		{
			uint8 form = pr->GetShapeShift();
			if(form == FORM_CAT || form == FORM_BEAR || form == FORM_DIREBEAR)
			{
				SubClassSkill = SKILL_FERAL_COMBAT;
				self_skill += pr->getLevel() * 5;
			}
		}

		self_skill += pr->_GetSkillLineCurrent(SubClassSkill);
		crit = GetFloatValue(PLAYER_CRIT_PERCENTAGE);
	}
	else
	{
		self_skill = this->getLevel() * 5;
		if(m_objectTypeId == TYPEID_UNIT)
		{
			Creature * c = (Creature*)(this);
			if(c&&c->GetCreatureInfo()&&c->GetCreatureInfo()->Rank == ELITE_WORLDBOSS)
				self_skill = std::max(self_skill,((int32)pVictim->getLevel()+3)*5);//used max to avoid situation when lowlvl hits boss.
		}
		crit = 5.0f; //will be modified later
	}
//==========================================================================================
//==============================Special Chances Base Calculation============================
//==========================================================================================

//--------------------------------crushing blow chance--------------------------------------
	//http://www.wowwiki.com/Crushing_blow
	if (pVictim->IsPlayer() && !this->IsPlayer() && !ability && !dmg.school_type)
	{
		int32 baseDefense = static_cast<Player*>(pVictim)->_GetSkillLineCurrent(SKILL_DEFENSE, false);
		int32 skillDiff = self_skill - baseDefense;
		if ( skillDiff >= 15)
			crush = -15.0f + 2.0f * skillDiff;
		else
			crush = 0.0f;
	}
//--------------------------------glancing blow chance--------------------------------------
	//http://www.wowwiki.com/Glancing_blow
	// did my own quick research here, seems base glancing against equal level mob is about 5%
	// and goes up 5% each level. Need to check this further.
	float diffAcapped = victim_skill - std::min((float)self_skill, getLevel() * 5.0f);

	if (this->IsPlayer() && !pVictim->IsPlayer() && !ability)
	{
		glanc = 5.0f + diffAcapped;
		if(glanc<0)
			glanc = 0.0f;
	}
//==========================================================================================
//==============================Advanced Chances Modifications==============================
//==========================================================================================
//--------------------------------by talents------------------------------------------------
	if(pVictim->IsPlayer())
	{
		if( weapon_damage_type != RANGED )
		{
			crit += static_cast< Player* >(pVictim)->res_M_crit_get();
			hitmodifier += static_cast< Player* >(pVictim)->m_resist_hit[ MOD_MELEE ];
		}
		else
		{
			crit += static_cast< Player* >(pVictim)->res_R_crit_get(); //this could be ability but in that case we overwrite the value
			hitmodifier += static_cast< Player* >(pVictim)->m_resist_hit[ MOD_RANGED ];
		}
	}
	crit += (float)(pVictim->AttackerCritChanceMod[0]);
//--------------------------------by skill difference---------------------------------------

	float vsk = (float)(self_skill - victim_skill);
	dodge = std::max( 0.0f, dodge - vsk * 0.04f );
	if( parry )
		parry = std::max( 0.0f, parry - vsk * 0.04f );
	if( block )
		block = std::max( 0.0f, block - vsk * 0.04f );

	crit += pVictim->IsPlayer() ? vsk * 0.04f : min( vsk * 0.2f, 0.0f );

	// http://www.wowwiki.com/Miss
	float misschance;
	float ask = -vsk;
	if (pVictim->IsPlayer())
	{
		if (ask > 0)
			misschance = ask * 0.04f;
		else
			misschance = ask * 0.02f;
	}
	else
	{
		if (ask <= 10)
			misschance = ask * 0.1f;
		else
			misschance = 2 + (ask - 10) * 0.4f;
	}
	hitchance = 100.0f - misschance; // base miss chances are worked out further down

	if(ability && ability->SpellGroupType)
	{
		SM_FFValue(SM_CriticalChance,&crit,ability->SpellGroupType);
		SM_FFValue(SM_FHitchance,&hitchance,ability->SpellGroupType);
	}
//--------------------------------by ratings------------------------------------------------
	crit -= pVictim->IsPlayer() ? static_cast< Player* >(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE ) : 0.0f;
	if(crit<0) crit=0.0f;
	if (this->IsPlayer())
	{
		Player* plr = static_cast< Player* >(this);
		hitmodifier += (weapon_damage_type == RANGED) ? plr->CalcRating( PLAYER_RATING_MODIFIER_RANGED_HIT ) : plr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT );

		float expertise_bonus = plr->CalcRating( PLAYER_RATING_MODIFIER_EXPERTISE );
		if( weapon_damage_type == MELEE )
			expertise_bonus += plr->GetUInt32Value( PLAYER_EXPERTISE );
		else if( weapon_damage_type == OFFHAND )
			expertise_bonus += plr->GetUInt32Value( PLAYER_OFFHAND_EXPERTISE );

		dodge -= expertise_bonus;
		if( dodge < 0 ) 
			dodge = 0.0f;

		parry -= expertise_bonus;
		if( parry < 0 ) 
			parry = 0.0f;
	}
//--------------------------------by aura mods-------------------------
	//Aura 248 SPELL_AURA_MOD_COMBAT_RESULT_CHANCE
	dodge += m_CombatResult_Dodge;
	if( dodge < 0 ) 
		dodge = 0.0f;

	//parry += m_CombatResult_Parry;
	//if( parry < 0 ) 
		//parry = 0.0f;

//--------------------------------by damage type and by weapon type-------------------------
	if( weapon_damage_type == RANGED )
	{
		dodge=0.0f;
		parry=0.0f;
		glanc=0.0f;
	}

	if ( this->IsPlayer() )
	{
		it = static_cast< Player* >( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
		if ( !ability && it != NULL
		 && (it->GetProto()->InventoryType == INVTYPE_WEAPON || it->GetProto()->InventoryType == INVTYPE_WEAPONOFFHAND))
		{
			// offhand weapon can either be a 1 hander weapon or an offhander weapon
			hitmodifier -= 24.0f; //dualwield miss chance
		}
		else
		{
			hitmodifier -= 5.0f; // base miss chance
		}
	}
	else
	{
		// mobs base hit chance
		hitmodifier -= 5.0f;
	}

	hitchance += hitmodifier;

	//Hackfix for Surprise Attacks
	if(  this->IsPlayer() && ability && static_cast< Player* >( this )->m_finishingmovesdodge && ability->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE)
			dodge = 0.0f;

	if( skip_hit_check )
	{
		hitchance = 100.0f;
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
	}

	if( ability != NULL && ability->Attributes & ATTRIBUTES_CANT_BE_DPB )
	{
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
	}

//--------------------------------by victim state-------------------------------------------
	if(pVictim->IsPlayer()&&pVictim->GetStandState()) //every not standing state is >0
	{
		hitchance = 100.0f;
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
		crush = 0.0f;
		crit = 100.0f;
	}
	if(backAttack)
	{
		if(pVictim->IsPlayer())
		{
			//However mobs can dodge attacks from behind
			dodge = 0.0f;
		}
		parry = 0.0f;
		block = 0.0f;
	}
//==========================================================================================
//==============================One Roll Processing=========================================
//==========================================================================================
	//--------------------------------cumulative chances generation----------------------------
	float chances[7];
	chances[0]=std::max(0.0f,100.0f-hitchance);
	chances[1]=chances[0]+dodge;
	chances[2]=chances[1]+parry;
	chances[3]=chances[2]+glanc;
	chances[4]=chances[3]+block;
	chances[5]=chances[4]+crit;
	chances[6]=chances[5]+crush;

	//printf("%s:-\n", IsPlayer() ? "Player" : "Mob");
	//printf(" miss: %.2f\n", chances[0]);
	//printf("dodge: %.2f\n", dodge);
	//printf("parry: %.2f\n", parry);
	//printf("glanc: %.2f\n", glanc);
	//printf("block: %.2f\n", block);
	//printf(" crit: %.2f\n", crit);
	//printf("crush: %.2f\n", crush);

//--------------------------------roll------------------------------------------------------
	float Roll = RandomFloat(100.0f);
	uint32 r = 0;
	while (r<7&&Roll>chances[r])
	{
		r++;
	}
//--------------------------------postroll processing---------------------------------------
	uint32 abs = 0;
	
	switch(r)
	{
//--------------------------------miss------------------------------------------------------
	case 0:
		hit_status |= HITSTATUS_MISS;
		// dirty ai agro fix
		if(pVictim->GetTypeId() == TYPEID_UNIT && pVictim->GetAIInterface()->GetNextTarget() == NULL)
			pVictim->GetAIInterface()->AttackReaction(this, 1, 0);
		break;
//--------------------------------dodge-----------------------------------------------------
	case 1:
		// dirty ai agro fix
		if(pVictim->GetTypeId() == TYPEID_UNIT && pVictim->GetAIInterface()->GetNextTarget() == NULL)
			pVictim->GetAIInterface()->AttackReaction(this, 1, 0);

		CALL_SCRIPT_EVENT(pVictim, OnTargetDodged)(this);
		CALL_SCRIPT_EVENT(this, OnDodged)(this);
		targetEvent = 1;
		vstate = DODGE;
		vproc |= PROC_ON_DODGE_VICTIM;
		pVictim->Emote(EMOTE_ONESHOT_PARRYUNARMED);			// Animation
		if( this->IsPlayer() && this->getClass() == WARRIOR)
		{
			//almighty warrior overpower
			/*if( this->IsPlayer() && static_cast< Player* >( this )->getClass() == WARRIOR )
			{
				static_cast< Player* >( this )->AddComboPoints( pVictim->GetGUID(), 1 );
				static_cast< Player* >( this )->UpdateComboPoints();
				if( !sEventMgr.HasEvent( static_cast< Player* >( this ), EVENT_COMBO_POINT_CLEAR_FOR_TARGET ) )
					sEventMgr.AddEvent( static_cast< Player* >( this ), &Player::NullComboPoints, (uint32)EVENT_COMBO_POINT_CLEAR_FOR_TARGET, (uint32)5000, (uint32)1, (uint32)0 );
				else
					sEventMgr.ModifyEventTimeLeft( static_cast< Player* >( this ), EVENT_COMBO_POINT_CLEAR_FOR_TARGET, 5000 ,0 );
			}
			pVictim->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_DODGE_BLOCK);	//SB@L: Enables spells requiring dodge
			if(!sEventMgr.HasEvent(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE))
				sEventMgr.AddEvent(pVictim,&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_DODGE_BLOCK,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000,1,0);
			else sEventMgr.ModifyEventTimeLeft(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000,0);*/
			static_cast< Player* >( this )->AddComboPoints( pVictim->GetGUID(), 1 );
			static_cast< Player* >( this )->UpdateComboPoints();
			if( !sEventMgr.HasEvent( static_cast< Player* >( this ), EVENT_COMBO_POINT_CLEAR_FOR_TARGET ) )
				sEventMgr.AddEvent( static_cast< Player* >( this ), &Player::NullComboPoints, (uint32)EVENT_COMBO_POINT_CLEAR_FOR_TARGET, (uint32)5000, (uint32)1, (uint32)0 );
			else
				sEventMgr.ModifyEventTimeLeft( static_cast< Player* >( this ), EVENT_COMBO_POINT_CLEAR_FOR_TARGET, 5000 ,0 );
		}
		if(this->IsPlayer() && this->getClass() == DEATHKNIGHT)
			CastSpell(GetGUID(), 56817, true);
		pVictim->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_DODGE_BLOCK);
		if(!sEventMgr.HasEvent(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE))
			sEventMgr.AddEvent(pVictim,&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_DODGE_BLOCK,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000,1,0);
		else sEventMgr.ModifyEventTimeLeft(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000,0);
		break;
//--------------------------------parry-----------------------------------------------------
	case 2:
		// dirty ai agro fix
		if(pVictim->GetTypeId() == TYPEID_UNIT && pVictim->GetAIInterface()->GetNextTarget() == NULL)
			pVictim->GetAIInterface()->AttackReaction(this, 1, 0);

		CALL_SCRIPT_EVENT(pVictim, OnTargetParried)(this);
		CALL_SCRIPT_EVENT(this, OnParried)(this);
		targetEvent = 3;
		vstate = PARRY;
		pVictim->Emote(EMOTE_ONESHOT_PARRYUNARMED);			// Animation
		if(pVictim->IsPlayer())
		{
			pVictim->SetFlag( UNIT_FIELD_AURASTATE,AURASTATE_FLAG_PARRY );	//SB@L: Enables spells requiring parry
			if(!sEventMgr.HasEvent( pVictim, EVENT_PARRY_FLAG_EXPIRE ) )
				sEventMgr.AddEvent( pVictim, &Unit::EventAurastateExpire, (uint32)AURASTATE_FLAG_PARRY,EVENT_PARRY_FLAG_EXPIRE, 5000, 1, 0 );
			else
				sEventMgr.ModifyEventTimeLeft( pVictim, EVENT_PARRY_FLAG_EXPIRE, 5000 );
			if( static_cast< Player* >( pVictim )->getClass() == 1 || static_cast< Player* >( pVictim )->getClass() == 4 )//warriors for 'revenge' and rogues for 'riposte'
			{
				pVictim->SetFlag( UNIT_FIELD_AURASTATE,AURASTATE_FLAG_DODGE_BLOCK );	//SB@L: Enables spells requiring dodge
				if(!sEventMgr.HasEvent( pVictim, EVENT_DODGE_BLOCK_FLAG_EXPIRE ) )
					sEventMgr.AddEvent( pVictim, &Unit::EventAurastateExpire, (uint32)AURASTATE_FLAG_DODGE_BLOCK, EVENT_DODGE_BLOCK_FLAG_EXPIRE, 5000, 1, 0 );
				else
					sEventMgr.ModifyEventTimeLeft( pVictim, EVENT_DODGE_BLOCK_FLAG_EXPIRE, 5000 );
			}
		}
		break;
//--------------------------------not miss,dodge or parry-----------------------------------
	default:
		hit_status |= HITSTATUS_HITANIMATION;//hit animation on victim
		if( pVictim->SchoolImmunityList[0] )
			vstate = IMMUNE;
		else
		{
//--------------------------------state proc initialization---------------------------------
			vproc |= PROC_ON_ANY_DAMAGE_VICTIM;
			if( weapon_damage_type != RANGED )
			{
				aproc |= PROC_ON_MELEE_ATTACK;
				vproc |= PROC_ON_MELEE_ATTACK_VICTIM;
			}
			else
			{
				aproc |= PROC_ON_RANGED_ATTACK;
				vproc |= PROC_ON_RANGED_ATTACK_VICTIM;
				if(ability && ability->Id==3018 && IsPlayer() && getClass()==HUNTER)
					aproc |= PROC_ON_AUTO_SHOT_HIT;
			}
//--------------------------------base damage calculation-----------------------------------
			if(exclusive_damage)
				dmg.full_damage = exclusive_damage;
			else
			{
				if( weapon_damage_type == MELEE && ability )
					dmg.full_damage = CalculateDamage( this, pVictim, MELEE, ability->SpellGroupType, ability );
				else
					dmg.full_damage = CalculateDamage( this, pVictim, weapon_damage_type, 0, ability );
			}

			if( pct_dmg_mod > 0 )
				dmg.full_damage = float2int32( dmg.full_damage *  ( float( pct_dmg_mod) / 100.0f ) );

			dmg.full_damage += add_damage;

			if(ability && ability->SpellGroupType)
			{
				SM_FIValue( ((Unit*)this)->SM_FDamageBonus, &dmg.full_damage, ability->SpellGroupType );
				SM_PIValue( ((Unit*)this)->SM_PDamageBonus, &dmg.full_damage, ability->SpellGroupType );
			} 
			else 
			{
//				SM_FIValue(((Unit*)this)->SM_FMiscEffect,&dmg.full_damage,(uint64)1<<63);
//				SM_PIValue(((Unit*)this)->SM_PMiscEffect,&dmg.full_damage,(uint64)1<<63);
			}

			dmg.full_damage += pVictim->DamageTakenMod[dmg.school_type];
			if( weapon_damage_type == RANGED )
			{
				dmg.full_damage += pVictim->RangedDamageTaken;
			}

			if( ability && ability->MechanicsType == MECHANIC_BLEEDING )
				disable_dR = true;


			dmg.full_damage += float2int32( dmg.full_damage * pVictim->DamageTakenPctMod[ dmg.school_type ] );
			dmg.full_damage += float2int32( dmg.full_damage * DamageDoneModPCT[dmg.school_type] );

			if( dmg.school_type != SCHOOL_NORMAL )
				dmg.full_damage += float2int32( dmg.full_damage * (GetDamageDonePctMod( dmg.school_type ) - 1) );

			if( ability != NULL && ability->NameHash == SPELL_HASH_SHRED )
				dmg.full_damage += float2int32( dmg.full_damage *  pVictim->ModDamageTakenByMechPCT[MECHANIC_BLEEDING] );
			if( ability != NULL && ability->NameHash == SPELL_HASH_MAUL)
				dmg.full_damage += float2int32( dmg.full_damage *  pVictim->ModDamageTakenByMechPCT[MECHANIC_BLEEDING] );

			//pet happiness state dmg modifier
			if( IsPet() && !static_cast<Pet*>(this)->IsSummon() )
				dmg.full_damage = ( dmg.full_damage <= 0 ) ? 0 : float2int32( dmg.full_damage * static_cast< Pet* >( this )->GetHappinessDmgMod() );

			if(dmg.full_damage < 0)
				dmg.full_damage = 0;
//--------------------------------check for special hits------------------------------------
			switch(r)
			{
//--------------------------------glancing blow---------------------------------------------
			case 3:
				{
					float low_dmg_mod = 1.5f - (0.05f * diffAcapped);
					if(this->getClass() == MAGE || this->getClass() == PRIEST || this->getClass() == WARLOCK) //casters = additional penalty.
					{
						low_dmg_mod -= 0.7f;
					}
					if(low_dmg_mod<0.01)
						low_dmg_mod = 0.01f;
					if(low_dmg_mod>0.91)
						low_dmg_mod = 0.91f;
					float high_dmg_mod = 1.2f - (0.03f * diffAcapped);
					if(this->getClass() == MAGE || this->getClass() == PRIEST || this->getClass() == WARLOCK) //casters = additional penalty.
					{
						high_dmg_mod -= 0.3f;
					}
					if(high_dmg_mod>0.99)
						high_dmg_mod = 0.99f;
					if(high_dmg_mod<0.2)
						high_dmg_mod = 0.2f;

					float damage_reduction = (high_dmg_mod + low_dmg_mod) / 2.0f;
					if(damage_reduction > 0)
					{
							dmg.full_damage = float2int32(damage_reduction * float(dmg.full_damage));
					}
					hit_status |= HITSTATUS_GLANCING;
				}
				break;
//--------------------------------block-----------------------------------------------------
			case 4:
				{
					Item* shield = static_cast< Player* >( pVictim )->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
					if( shield != NULL )
					{
						targetEvent = 2;
						pVictim->Emote(EMOTE_ONESHOT_PARRYSHIELD);// Animation

						if( shield->GetProto()->InventoryType == INVTYPE_SHIELD )
						{
							float block_multiplier = ( 100.0f + float( static_cast< Player* >( pVictim )->m_modblockabsorbvalue ) ) / 100.0f;
							if( block_multiplier < 1.0f )block_multiplier = 1.0f;

							blocked_damage = float2int32( (float( shield->GetProto()->Block ) + ( float( static_cast< Player* >( pVictim )->m_modblockvaluefromspells + pVictim->GetUInt32Value( PLAYER_RATING_MODIFIER_BLOCK ) )) + ( ( float( pVictim->GetUInt32Value( UNIT_FIELD_STAT0 ) ) / 20.0f ) - 1.0f ) ) * block_multiplier);
							if( Rand( m_BlockModPct ) )
								blocked_damage *= 2;
						}
						else
						{
							blocked_damage = 0;
						}

						if(dmg.full_damage <= (int32)blocked_damage)
							vstate = BLOCK;
						if( blocked_damage )
						{
							CALL_SCRIPT_EVENT(pVictim, OnTargetBlocked)(this, blocked_damage);
							CALL_SCRIPT_EVENT(this, OnBlocked)(pVictim, blocked_damage);
							vproc |= PROC_ON_BLOCK_VICTIM;
						}
						if( pVictim->IsPlayer() )//not necessary now but we'll have blocking mobs in future
						{
							pVictim->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_DODGE_BLOCK);	//SB@L: Enables spells requiring dodge
							if(!sEventMgr.HasEvent(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE))
								sEventMgr.AddEvent(pVictim,&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_DODGE_BLOCK,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000,1,0);
							else
								sEventMgr.ModifyEventTimeLeft(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000);
						}
					}
				}
				break;
//--------------------------------critical hit----------------------------------------------
			case 5:
				{
					hit_status |= HITSTATUS_CRICTICAL;
					int32 dmgbonus = dmg.full_damage;
					//sLog.outString( "DEBUG: Critical Strike! Full_damage: %u" , dmg.full_damage );
					if(ability && ability->SpellGroupType)
					{
						int32 dmg_bonus_pct = 100;
						SM_FIValue(SM_PCriticalDamage,&dmg_bonus_pct,ability->SpellGroupType);
						dmgbonus = float2int32( float(dmgbonus) * (float(dmg_bonus_pct)/100.0f) );
					}

					//sLog.outString( "DEBUG: After CritMeleeDamageTakenPctMod: %u" , dmg.full_damage );
					if(IsPlayer())
					{
						if( weapon_damage_type != RANGED )
						{
							float critextra=float(static_cast< Player* >( this )->m_modphyscritdmgPCT);
							dmg.full_damage += int32((float(dmg.full_damage)*critextra/100.0f));
						}
						if(!pVictim->IsPlayer())
							dmg.full_damage += float2int32(dmg.full_damage*static_cast< Player* >( this )->IncreaseCricticalByTypePCT[((Creature*)pVictim)->GetCreatureInfo() ? ((Creature*)pVictim)->GetCreatureInfo()->Type : 0]);
					//sLog.outString( "DEBUG: After IncreaseCricticalByTypePCT: %u" , dmg.full_damage );
					}

					dmg.full_damage += dmgbonus;

					if( weapon_damage_type == RANGED )
						dmg.full_damage = dmg.full_damage - float2int32(dmg.full_damage * CritRangedDamageTakenPctMod[dmg.school_type]);
					else
						dmg.full_damage = dmg.full_damage - float2int32(dmg.full_damage * CritMeleeDamageTakenPctMod[dmg.school_type]);

					if(pVictim->IsPlayer())
					{
						//Resilience is a special new rating which was created to reduce the effects of critical hits against your character.
						float dmg_reduction_pct = 2.0f * static_cast< Player* >(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE ) / 100.0f;
						if( dmg_reduction_pct > 1.0f )
							dmg_reduction_pct = 1.0f; //we cannot resist more then he is criticalling us, there is no point of the critical then :P
						dmg.full_damage = float2int32( dmg.full_damage - dmg.full_damage*dmg_reduction_pct );
						//sLog.outString( "DEBUG: After Resilience check: %u" , dmg.full_damage );
					}

					if (pVictim->GetTypeId() == TYPEID_UNIT && static_cast<Creature*>(pVictim)->GetCreatureInfo() && static_cast<Creature*>(pVictim)->GetCreatureInfo()->Rank != ELITE_WORLDBOSS)
						pVictim->Emote( EMOTE_ONESHOT_WOUNDCRITICAL );

					vproc |= PROC_ON_CRIT_HIT_VICTIM;
					aproc |= PROC_ON_CRIT_ATTACK;

					if( weapon_damage_type == RANGED )
					{
						vproc |= PROC_ON_RANGED_CRIT_ATTACK_VICTIM;
						aproc |= PROC_ON_RANGED_CRIT_ATTACK;
					}

					if( IsPlayer() )
					{
						this->SetFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_CRITICAL );
						if( !sEventMgr.HasEvent( this, EVENT_CRIT_FLAG_EXPIRE ) )
							sEventMgr.AddEvent( ( Unit* )this, &Unit::EventAurastateExpire, uint32( AURASTATE_FLAG_CRITICAL ) , EVENT_CRIT_FLAG_EXPIRE, 5000, 1, 0 );
						else sEventMgr.ModifyEventTimeLeft( this, EVENT_CRIT_FLAG_EXPIRE, 5000 );
					}

					CALL_SCRIPT_EVENT(pVictim, OnTargetCritHit)(this, float(dmg.full_damage));
					CALL_SCRIPT_EVENT(this, OnCritHit)(pVictim, float(dmg.full_damage));
				}
				break;
//--------------------------------crushing blow---------------------------------------------
			case 6:
				hit_status |= HITSTATUS_CRUSHINGBLOW;
				dmg.full_damage = (dmg.full_damage * 3) >> 1;
				break;
//--------------------------------regular hit-----------------------------------------------
			default:
				break;
			}
//==========================================================================================
//==============================Post Roll Damage Processing=================================
//==========================================================================================
//--------------------------absorption------------------------------------------------------
			uint32 dm = dmg.full_damage;
			abs = pVictim->AbsorbDamage(dmg.school_type,(uint32*)&dm);

			if(dmg.full_damage > (int32)blocked_damage)
			{
				uint32 sh = pVictim->ManaShieldAbsorb(dmg.full_damage);
//--------------------------armor reducing--------------------------------------------------
				if(sh)
				{
					dmg.full_damage -= sh;
					if(dmg.full_damage && !disable_dR)
						CalculateResistanceReduction(pVictim,&dmg, ability, ArmorPctReduce);
					dmg.full_damage += sh;
					abs+=sh;
				}
				else if(!disable_dR)
					CalculateResistanceReduction(pVictim,&dmg, ability, ArmorPctReduce);
			}

			if(abs)
				vproc |= PROC_ON_ABSORB;

			if (dmg.school_type == SCHOOL_NORMAL)
			{
				abs+=dmg.resisted_damage;
				dmg.resisted_damage=0;
			}

			realdamage = dmg.full_damage-abs-dmg.resisted_damage-blocked_damage;
			if(realdamage < 0)
			{
				realdamage = 0;
				vstate = IMMUNE;
				if( !(hit_status & HITSTATUS_BLOCK) )
					hit_status |= HITSTATUS_ABSORBED;
				else
					hit_status |= HITSTATUS_BLOCK;
			}
		}
		break;
	}

//==========================================================================================
//==============================Post Roll Special Cases Processing==========================
//==========================================================================================
//------------------------------- Special Effects Processing
	// Paladin: Blessing of Sacrifice, and Warlock: Soul Link
	if( pVictim->m_damageSplitTarget )
	{
		dmg.full_damage = pVictim->DoDamageSplitTarget(dmg.full_damage, dmg.school_type, true);
		realdamage = dmg.full_damage;
	}

	//--------------------------special states processing---------------------------------------
	if(pVictim->GetTypeId() == TYPEID_UNIT)
	{
		if(pVictim->GetAIInterface() && (pVictim->GetAIInterface()->getAIState()== STATE_EVADE ||
										(pVictim->GetAIInterface()->GetIsSoulLinked() && pVictim->GetAIInterface()->getSoullinkedWith() != this)))
		{
			vstate = EVADE;
			realdamage = 0;
			dmg.full_damage = 0;
			dmg.resisted_damage = 0;
		}
	}
	if(pVictim->GetTypeId() == TYPEID_PLAYER && static_cast< Player* >(pVictim)->GodModeCheat == true)
	{
		dmg.resisted_damage = dmg.full_damage; //godmode
	}
//--------------------------dirty fixes-----------------------------------------------------
	//vstate=1-wound,2-dodge,3-parry,4-interrupt,5-block,6-evade,7-immune,8-deflect
	// the above code was remade it for reasons : damage shield needs moslty same flags as handleproc + dual wield should proc too ?
	if (ability && ability->noproc)
	{
		disable_proc = true;
	}
	if( !disable_proc )//offhand should proc too!
	{
		uint32 resisted_dmg;

		//damage shield must come before handleproc to not loose 1 charge : spell gets removed before last charge
		if( (realdamage > 0 || vproc & PROC_ON_BLOCK_VICTIM) && weapon_damage_type != OFFHAND )
		{
			pVictim->HandleProcDmgShield(vproc,this);
			HandleProcDmgShield(aproc,pVictim);
		}

		this->HandleProc( aproc, pVictim, ability, realdamage, abs ); //maybe using dmg.resisted_damage is better sometimes but then if using godmode dmg is resisted instead of absorbed....bad
		m_procCounter = 0;

		resisted_dmg = pVictim->HandleProc( vproc, this, ability, realdamage, abs );
		pVictim->m_procCounter = 0;

		if (resisted_dmg) 
		{
			dmg.resisted_damage+= resisted_dmg;
			dmg.full_damage-= resisted_dmg;
			realdamage-= resisted_dmg;
		}
	}
//--------------------------spells triggering-----------------------------------------------
	if(realdamage > 0 && ability == 0)
	{
		if( IsPlayer() && static_cast< Player* >( this )->m_onStrikeSpells.size() )
		{
			SpellCastTargets targets;
			targets.m_unitTarget = pVictim->GetGUID();
			targets.m_targetMask = 0x2;
			Spell* cspell;

			// Loop on hit spells, and strike with those.
			for( map< SpellEntry*, pair< uint32, uint32 > >::iterator itr = static_cast< Player* >( this )->m_onStrikeSpells.begin();
				itr != static_cast< Player* >( this )->m_onStrikeSpells.end(); ++itr )
			{
				if( itr->second.first )
				{
					// We have a *periodic* delayed spell.
					uint32 t = getMSTime();
					if( t > itr->second.second )  // Time expired
					{
						// Set new time
						itr->second.second = t + itr->second.first;
					}

					// Cast.
					cspell = SpellPool.PooledNew();
					if (!cspell)
						return;
					cspell->Init(this, itr->first, true, NULL);
					cspell->prepare(&targets);
				}
				else
				{
					cspell = SpellPool.PooledNew();
					if (!cspell)
						return;
					cspell->Init(this, itr->first, true, NULL);
					cspell->prepare(&targets);
				}
			}
		}

		if( IsPlayer() && static_cast< Player* >( this )->m_onStrikeSpellDmg.size() )
		{
			map< uint32, OnHitSpell >::iterator it2 = static_cast< Player* >( this )->m_onStrikeSpellDmg.begin();
			map< uint32, OnHitSpell >::iterator itr;
			uint32 min_dmg, max_dmg, range, dmg;
			for(; it2 != static_cast< Player* >( this )->m_onStrikeSpellDmg.end(); )
			{
				itr = it2;
				++it2;

				min_dmg = itr->second.mindmg;
				max_dmg = itr->second.maxdmg;
				range = min_dmg - max_dmg;
				dmg = min_dmg;
				if(range) range += RandomUInt(range);

				SpellNonMeleeDamageLog(pVictim, itr->second.spellid, dmg, true);
			}
		}

		//ugly hack for shadowfiend restoring mana
		if( GetUInt64Value(UNIT_FIELD_SUMMONEDBY) != 0 && GetUInt32Value(OBJECT_FIELD_ENTRY) == 19668 )
		{
			Player* owner = GetMapMgr()->GetPlayer((uint32)GetUInt64Value(UNIT_FIELD_SUMMONEDBY));
			if ( owner != NULL )
				this->Energize(owner, 34433, uint32(2.5f*realdamage + 0.5f), POWER_TYPE_MANA );
		}
	}

//==========================================================================================
//==============================Data Sending================================================
//==========================================================================================
	if( !ability )
	{
		if( dmg.full_damage > 0 )
		{
			if( dmg.full_damage == (int32)abs )
				hit_status |= HITSTATUS_ABSORBED;
			else if (dmg.full_damage <= (int32)dmg.resisted_damage)
			{
				hit_status |= HITSTATUS_RESIST;
				vproc |= PROC_ON_ABSORB;
				dmg.resisted_damage = dmg.full_damage;
			}
		}

		if( dmg.full_damage < 0 )
			dmg.full_damage = 0;

		if( realdamage < 0 )
			realdamage = 0;

		SendAttackerStateUpdate(this, pVictim, &dmg, realdamage, abs, blocked_damage, hit_status, vstate);
	}
	else
	{
		if( realdamage > 0 )//FIX ME: add log for miss,block etc for ability and ranged
		{
			// here we send "dmg.resisted_damage" for "AbsorbedDamage", "0" for "ResistedDamage", and "false" for "PhysicalDamage" even though "School" is "SCHOOL_NORMAL"   o_O
			SendSpellNonMeleeDamageLog( this, pVictim, ability->Id, realdamage, static_cast<uint8>( dmg.school_type ), dmg.resisted_damage, 0, false, blocked_damage, ( ( hit_status & HITSTATUS_CRICTICAL ) != 0 ), true );
		}
		//FIX ME: add log for miss,block etc for ability and ranged
		//example how it works
		//SendSpellLog(this,pVictim,ability->Id,SPELL_LOG_MISS);
	}

	if(ability && realdamage==0)
	{
		SendSpellLog(this,pVictim,ability->Id,SPELL_LOG_RESIST);
	}
//==========================================================================================
//==============================Damage Dealing==============================================
//==========================================================================================

	if(HasAura(48266))
	{
		realdamage *= 1.15;
		if(HasAura(50365))		// Pr�sence de sang am�lior�e rang 1
		{
			uint32 heal = realdamage*0.09;
			Heal( this, 48266, heal);
		}
		else if(HasAura(50371))	// Pr�sence de sang am�lior�e rang 2
		{
			uint32 heal = realdamage*0.14;
			Heal( this, 48266, heal);
		}
		else
		{
			uint32 heal = realdamage*0.04;
			Heal( this, 48266, heal);
		}
	}

	if(HasAura(48263) || HasAura(48265))
	{
		if(HasAura(50365))		// Pr�sence de sang am�lior�e rang 1
		{
			uint32 heal = realdamage*0.02;
			Heal( this, 48266, heal);
		}
		else if(HasAura(50371))	// Pr�sence de sang am�lior�e rang 2
		{
			uint32 heal = realdamage*0.04;
			Heal( this, 48266, heal);
		}
	}

	if(this->IsPlayer() && ability)
		static_cast< Player* >( this )->m_casted_amount[dmg.school_type]=(uint32)(realdamage+abs);

	// invincible people don't take damage
	if( pVictim->bInvincible == false ){		
		if(realdamage){
			DealDamage(pVictim, realdamage, 0, targetEvent, 0);
			//pVictim->HandleProcDmgShield(PROC_ON_MELEE_ATTACK_VICTIM,this);
			//		HandleProcDmgShield(PROC_ON_MELEE_ATTACK_VICTIM,pVictim);
			
			if(pVictim->GetCurrentSpell())
				pVictim->GetCurrentSpell()->AddTime(0);
		}else{
			// have to set attack target here otherwise it wont be set
			// because dealdamage is not called.
			//setAttackTarget(pVictim);
			this->CombatStatus.OnDamageDealt( pVictim );
		}
	}
//==========================================================================================
//==============================Post Damage Dealing Processing==============================
//==========================================================================================
//--------------------------durability processing-------------------------------------------
	if(pVictim->IsPlayer())
	{
		static_cast< Player* >( pVictim )->GetItemInterface()->ReduceItemDurability();
		if( !this->IsPlayer() )
		{
			Player *pr = static_cast< Player* >( pVictim );
			if( Rand( pr->GetSkillUpChance( SKILL_DEFENSE ) * sWorld.getRate( RATE_SKILLCHANCE ) ) )
			{
				pr->_AdvanceSkillLine( SKILL_DEFENSE, float2int32( 1.0f * sWorld.getRate(RATE_SKILLRATE)));
				pr->UpdateChances();
			}
		}
		else
		{
			 static_cast< Player* >( this )->GetItemInterface()->ReduceItemDurability();
		}
	}
	else
	{
		if(this->IsPlayer())//not pvp
		{
			static_cast< Player* >( this )->GetItemInterface()->ReduceItemDurability();
			Player* pr = static_cast< Player* >( this );
			if( Rand( pr->GetSkillUpChance( SubClassSkill) * sWorld.getRate( RATE_SKILLCHANCE ) ) )
			{
				pr->_AdvanceSkillLine( SubClassSkill, float2int32( 1.0f * sWorld.getRate(RATE_SKILLRATE)));
				//pr->UpdateChances();
			}
		}
	}
	//--------------------------rage processing-------------------------------------------------
	//http://www.wowwiki.com/Formulas:Rage_generation

	if( dmg.full_damage && IsPlayer() && GetPowerType() == POWER_TYPE_RAGE && !ability)
	{
		float val;
		uint32 level = getLevel();
		float conv;
		if( level <= PLAYER_LEVEL_CAP )
			conv = AttackToRageConversionTable[ level ];
		else
			conv = 3.75f / (0.0091107836f * level * level + 3.225598133f * level + 4.2652911f);

		// Hit Factor
		float f = ( weapon_damage_type == OFFHAND ) ? 1.75f : 3.5f;

		if( hit_status & HITSTATUS_CRICTICAL )
			f *= 2.0f;

		float s = 1.0f;

		// Weapon speed (normal)
		Item* weapon = ( static_cast< Player* >( this )->GetItemInterface())->GetInventoryItem( INVENTORY_SLOT_NOT_SET, ( weapon_damage_type == OFFHAND ? EQUIPMENT_SLOT_OFFHAND : EQUIPMENT_SLOT_MAINHAND ) );
		if( weapon == NULL )
		{
			if( weapon_damage_type == OFFHAND )
				s = GetUInt32Value( UNIT_FIELD_BASEATTACKTIME+1 ) / 1000.0f;
			else
				s = GetUInt32Value( UNIT_FIELD_BASEATTACKTIME ) / 1000.0f;
		}
		else
		{
			uint32 entry = weapon->GetEntry();
			ItemPrototype* pProto = ItemPrototypeStorage.LookupEntry( entry );
			if( pProto != NULL )
			{
				s = pProto->Delay / 1000.0f;
			}
		}

		val = conv * dmg.full_damage + f * s / 2.0f;
		val *= ( 1 + ( static_cast< Player* >( this )->rageFromDamageDealt / 100.0f ) );
		float ragerate = sWorld.getRate(RATE_POWER2);
		val *= 10 * ragerate;

		//float r = ( 7.5f * dmg.full_damage / c + f * s ) / 2.0f;
		//float p = ( 1 + ( static_cast< Player* >( this )->rageFromDamageDealt / 100.0f ) );
		//sLog.outDebug( "Rd(%i) d(%i) c(%f) f(%f) s(%f) p(%f) r(%f) rage = %f", realdamage, dmg.full_damage, c, f, s, p, r, val );

		ModUnsigned32Value( UNIT_FIELD_POWER2, (int32)val );
		if( GetUInt32Value( UNIT_FIELD_POWER2 ) > 1000 )
			ModUnsigned32Value( UNIT_FIELD_POWER2, 1000 - GetUInt32Value( UNIT_FIELD_POWER2 ) );

	}

	RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_START_ATTACK);
//--------------------------extra strikes processing----------------------------------------
	if(!m_extraAttackCounter)
	{
		int32 extra_attacks = m_extraattacks;
		m_extraAttackCounter = true;
		m_extraattacks = 0;

		while(extra_attacks > 0)
		{
			extra_attacks--;
			Strike( pVictim, weapon_damage_type, NULL, 0, 0, 0, false, false);
		}

		m_extraAttackCounter = false;
	}

	if(m_extrastriketargetc > 0 && m_extrastriketarget == 0)
	{
		m_extrastriketarget = 1;

		for(std::list<ExtraStrike*>::iterator itx = m_extraStrikeTargets.begin();itx != m_extraStrikeTargets.end(); itx++)
		{
			ExtraStrike *ex = *itx;

			if (ex->deleted) continue;

			for(set<Object*>::iterator itr = m_objectsInRange.begin(); itr != m_objectsInRange.end(); ++itr)
			{
				if (!(*itr) || (*itr) == pVictim || !(*itr)->IsUnit())
					continue;

				if(CalcDistance(*itr) < 5.0f && isAttackable(this, (*itr)) && (*itr)->isInFront(this) && !((Unit*)(*itr))->IsPacified())
				{
					// Sweeping Strikes hits cannot be dodged, missed or parried (from wowhead)
					bool skip_hit_check = ex->spell_info->Id == 12328 ? true : false;
					//zack : should we use the spell id the registered this extra strike when striking ? It would solve a few proc on proc problems if so ;)
//					Strike( static_cast< Unit* >( *itr ), weapon_damage_type, ability, add_damage, pct_dmg_mod, exclusive_damage, false, skip_hit_check );
					Strike( static_cast< Unit* >( *itr ), weapon_damage_type, ex->spell_info, add_damage, pct_dmg_mod, exclusive_damage, false, skip_hit_check );
					break;
				}
			}

			// Sweeping Strikes charges are used up regardless whether there is a secondary target in range or not. (from wowhead)
			if (ex->charges > 0)
			{
				ex->charges--;
				if (ex->charges <= 0)
				{
					ex->deleted = true;
					m_extrastriketargetc--;
				}
			}
		}

		m_extrastriketarget = 0;
	}
}

void Unit::smsg_AttackStop(Unit* pVictim)
{
	if(!pVictim)
		return;

	WorldPacket data(SMSG_ATTACKSTOP, 24);
	if(m_objectTypeId==TYPEID_PLAYER)
	{
		data << pVictim->GetNewGUID();
		data << uint8(0);
		data << uint32(0);
		static_cast< Player* >( this )->GetSession()->SendPacket( &data );
		data.clear();
	}

	data << GetNewGUID();
	data << pVictim->GetNewGUID();
	data << uint32(0);
	SendMessageToSet(&data, true );
	// stop swinging, reset pvp timeout

	if( pVictim->IsPlayer() )
	{
		pVictim->CombatStatusHandler_ResetPvPTimeout();
		CombatStatusHandler_ResetPvPTimeout();
	}
	else
	{
		if( !IsPlayer() || getClass() == ROGUE )
		{
		m_cTimer = getMSTime() + 8000;
		sEventMgr.RemoveEvents( this, EVENT_COMBAT_TIMER );
			sEventMgr.AddEvent( this, &Unit::EventUpdateFlag, EVENT_COMBAT_TIMER, 8000, 1, 0 );
			if( pVictim->IsUnit() ) // there could be damage coming from objects/enviromental
				sEventMgr.AddEvent( pVictim, &Unit::EventUpdateFlag, EVENT_COMBAT_TIMER, 8000, 1, 0 );		}
		else
		{
		}
	}
}

void Unit::smsg_AttackStop(uint64 victimGuid)
{
	WorldPacket data(20);
	data.Initialize( SMSG_ATTACKSTOP );
	data << GetNewGUID();
	FastGUIDPack(data, victimGuid);
	data << uint32( 0 );
	SendMessageToSet(&data, IsPlayer());
}

void Unit::smsg_AttackStart(Unit* pVictim)
{
    // Prevent user from ignoring attack speed and stopping and start combat really really fast
    /*if(!isAttackReady())
        setAttackTimer(uint32(0));
    else if(!canReachWithAttack(pVictim))
    {
        setAttackTimer(uint32(500));
        //pThis->GetSession()->OutPacket(SMSG_ATTACKSWING_NOTINRANGE);
    }
    else if(!isInFront(pVictim))
    {
        setAttackTimer(uint32(500));
        //pThis->GetSession()->OutPacket(SMSG_ATTACKSWING_NOTINRANGE);
    }*/

    // Send out ATTACKSTART
    WorldPacket data(SMSG_ATTACKSTART, 16);
    data << GetGUID();
    data << pVictim->GetGUID();
//    SendMessageToSet(&data, true);
    SendMessageToSet(&data, false);
    sLog.outDebug( "WORLD: Sent SMSG_ATTACKSTART" );

    // FLAGS changed so other players see attack animation
    //    addUnitFlag(UNIT_FLAG_COMBAT);
    //    setUpdateMaskBit(UNIT_FIELD_FLAGS );
    if(GetTypeId() == TYPEID_PLAYER)
    {
        Player* pThis = static_cast< Player* >( this );
        if( pThis->cannibalize)
        {
            sEventMgr.RemoveEvents(pThis, EVENT_CANNIBALIZE);
            pThis->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
            pThis->cannibalize = false;
        }
    }
}

uint8 Unit::FindVisualSlot(uint32 SpellId,bool IsPos)
{
	uint32 from,to;
	uint8 visualslot = 0xFF;
	if( IsPos )
	{
		from = 0;
		to = MAX_POSITIVE_VISUAL_AURAS_END;
	}
	else
	{
		from = MAX_NEGATIVE_VISUAL_AURAS_START;
		to = MAX_NEGATIVE_VISUAL_AURAS_END;
	}
	//check for already visual same aura
	for(uint32 i=from;i<to;i++)
		if( m_auravisuals[i] == SpellId )
		{
			visualslot = static_cast<uint8>( i );
			break;
		}
	if( visualslot == 0xFF )
		for(uint32 i=from;i<to;i++)
			if( m_auravisuals[i] == 0 )
			{
				visualslot = static_cast<uint8>( i );
				break;
			}
	return visualslot;
}

void Unit::AddAura(Aura * aur)
{
	if ( !aur )
		return;

    if( !isAlive() && !( aur->GetSpellProto()->AttributesExC & CAN_PERSIST_AND_CASTED_WHILE_DEAD ) )
        return;

	if(m_mapId!=530 && (m_mapId!=571 || (IsPlayer() && !((Player*)this)->HasSpellwithNameHash(SPELL_HASH_COLD_WEATHER_FLYING))))
	// can't use flying auras in non-outlands or non-northrend (northrend requires cold weather flying)
	{
		for( uint32 i = 0; i < 3; ++i )
		{
			if( aur->GetSpellProto()->EffectApplyAuraName[i] == 208 || aur->GetSpellProto()->EffectApplyAuraName[i] == 207 )
			{
				// Pretty sure this gets removed somewhere in the aura pool..
				// Watch:
				/*
				PooledDelete(T* dumped) calls dumped->Virtual_Destructor(); 
				which calls Aura::Virtual_Destructor() which then calls
				sEventMgr.RemoveEvents( this ); this refers to the Aura pointer which we've named aur.
				Cheers!
				*/
				//sEventMgr.RemoveEvents(aur);
				AuraPool.PooledDelete(aur);
				return;
			}
		}
	}

	if( aur->GetSpellProto()->School && SchoolImmunityList[aur->GetSpellProto()->School] )
	{
		AuraPool.PooledDelete(aur);
		return;
	}

	uint16 AuraSlot = 0xFFFF;
	//all this code block is to try to find a valid slot for our new aura.
	if( !aur->IsPassive() )
	{
		uint32 AlreadyApplied = 0, CheckLimit, StartCheck;
		if( aur->IsPositive() )
		{
			StartCheck = MAX_POSITIVE_AURAS_EXTEDED_START; //also check talents to make sure they will not stack. Maybe not required ?
			CheckLimit = MAX_POSITIVE_AURAS_EXTEDED_END;
		}
		else
		{
			StartCheck = MAX_NEGATIVE_AURAS_EXTEDED_START;
			CheckLimit = MAX_NEGATIVE_AURAS_EXTEDED_END;
		}
		// Nasty check for Blood Fury debuff (spell system based on namehashes is bs anyways)
		if( aur->GetSpellProto()->always_apply == false )
		{
			//uint32 aurName = aur->GetSpellProto()->Name;
			//uint32 aurRank = aur->GetSpellProto()->Rank;
			uint32 maxStack = aur->GetSpellProto()->maxstack;
			if( aur->GetSpellProto()->procCharges > 0 )
			{
				int charges = aur->GetSpellProto()->procCharges;
				Unit* ucaster = aur->GetUnitCaster();
				if( aur->GetSpellProto()->SpellGroupType && ucaster != NULL )
				{
					SM_FIValue( ucaster->SM_FCharges, &charges, aur->GetSpellProto()->SpellGroupType );
					SM_PIValue( ucaster->SM_PCharges, &charges, aur->GetSpellProto()->SpellGroupType );
				}
				maxStack=charges;
			}
			if( IsPlayer() && static_cast< Player* >( this )->AuraStackCheat )
				maxStack = 999;

			SpellEntry * info = aur->GetSpellProto();
			//uint32 flag3 = aur->GetSpellProto()->Flags3;

			AuraCheckResponse acr;
			WorldPacket data( 21 );
			bool deleteAur = false;

			//check if we already have this aura by this caster -> update duration
			for( uint32 x = StartCheck; x < CheckLimit; x++ )
			{
				if( m_auras[x] )
				{
					if( m_auras[x]->GetSpellId() == aur->GetSpellId() )
					{
						if( !aur->IsPositive()
							&& m_auras[x]->m_casterGuid != aur->m_casterGuid
							&& ( m_auras[x]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_MAXSTACK_FOR_DEBUFF) == 0
							)
						{
							continue;
						}
						AlreadyApplied++;
						//update duration,the same aura (update the whole stack whenever we cast a new one)
						m_auras[x]->SetDuration(aur->GetDuration());
						sEventMgr.ModifyEventTimeLeft(m_auras[x], EVENT_AURA_REMOVE, aur->GetDuration());

						if(maxStack <= AlreadyApplied)
						{
							ModVisualAuraStackCount(m_auras[x], 0);
							if (AlreadyApplied == 1)
								m_auras[x]->UpdateModifiers();
							deleteAur = true;
							break;
						}
					}
					else if( ( aur->pSpellId != m_auras[x]->GetSpellProto()->Id ) ) // if this is a proc spell then it should not remove it's mother : test with combustion later
					{
						// Check for auras by specific type.
						if(info->BGR_one_buff_on_target > 0 && m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & info->BGR_one_buff_on_target && maxStack == 0)
						{
							deleteAur = HasAurasOfBuffType(info->BGR_one_buff_on_target, aur->m_casterGuid,0);
						}
						// Check for auras with the same name and a different rank.
						else
						{
							acr = AuraCheck(info->NameHash, info->RankNumber, m_auras[x],aur->GetCaster());
							if(acr.Error == AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT)
							{
								deleteAur = true;
							}
							else if(acr.Error == AURA_CHECK_RESULT_LOWER_BUFF_PRESENT)
							{
								// remove the lower aura
								m_auras[x]->Remove();

								// no more checks on bad ptr
								continue;
							}
						}
					}
				}
				else if( AuraSlot == 0xFFFF )
				{
					AuraSlot = static_cast<uint16>( x );
				}
			}

			if(deleteAur)
			{
				sEventMgr.RemoveEvents( aur );
				AuraPool.PooledDelete( aur );
				return;
			}
		}
		else
		{
			//these auras stack to infinite and with anything. Don't ask me why there is no better solution for them :P
			for( uint32 x = StartCheck; x < CheckLimit; x++ )
				if( !m_auras[x] )
				{
					AuraSlot = static_cast<uint16>( x );
					break;
				}
		}
	}
	else
	{
		//talents just get applied always. Maybe we should check stack for these as well?
		for(uint32 x=MAX_PASSIVE_AURAS_START;x<MAX_PASSIVE_AURAS_END;x++)
			if( !m_auras[x] )
			{
				AuraSlot = static_cast<uint16>( x );
				break;
			}
//			else if( m_auras[x]->GetID()==aur->GetID() ) printf("OMG stacking talents ?\n");
	}


	//check if we can store this aura in some empty slot
	if( AuraSlot == 0xFFFF )
	{
		sLog.outError("Aura error in active aura. ");
		sEventMgr.RemoveEvents( aur );
		AuraPool.PooledDelete( aur );
/*
		if ( aur != NULL ) 
			{
				delete [] aur;
				aur = NULL;
			}
	*/	return;
	}

	Unit* target = aur->GetTarget();
	if (target != NULL)
	{
		//send the aura log
		WorldPacket data(SMSG_AURACASTLOG, 28);

		data << aur->m_casterGuid;
		data << aur->GetTarget()->GetGUID();
		data << aur->m_spellProto->Id;
		data << uint64(0);

		target->SendMessageToSet(&data, true);
	}

	//Zack : if all mods were resisted it means we did not apply anything and we do not need to delete this spell either
	if( aur->TargetWasImuneToMods() )
	{
		//TODO : notify client that we are immune to this spell
		sEventMgr.RemoveEvents( aur );
		AuraPool.PooledDelete( aur );
		return;
	}

	uint8 visualslot=0xFF;
	//search for a visual slot
	if( !aur->IsPassive() || (aur->m_spellProto->AttributesEx & 1024))
		visualslot = FindVisualSlot( aur->GetSpellId(), aur->IsPositive() );
	aur->m_visualSlot = visualslot;
	ModVisualAuraStackCount(aur, 1);

	// Zack : No idea how a new aura can already have a slot. Leaving it for compatibility
	if( aur->m_auraSlot != 0xffff )
		m_auras[ aur->m_auraSlot ] = NULL;

	aur->m_auraSlot = AuraSlot;

	m_auras[ AuraSlot ] = aur;
	aur->ApplyModifiers(true);

	// We add 500ms here to allow for the last tick in DoT spells. This is a dirty hack, but at least it doesn't crash like my other method.
	// - Burlex
	if(aur->GetDuration() > 0)
	{
		sEventMgr.AddEvent(aur, &Aura::Remove, EVENT_AURA_REMOVE, aur->GetDuration() + 500, 1,
			EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT | EVENT_FLAG_DELETES_OBJECT);
	}

	//have to hate these relocate events. They run in a separate thread :P
	aur->RelocateEvents();

	// Reaction from enemy AI
	if(!aur->IsPositive() && aur->IsCombatStateAffecting())	  // Creature
	{
		Unit * pCaster = aur->GetUnitCaster();
		if( pCaster && pCaster->isAlive() && this->isAlive() )
		{
			pCaster->CombatStatus.OnDamageDealt( this );

			if(m_objectTypeId == TYPEID_UNIT)
				m_aiInterface->AttackReaction(pCaster, 1, aur->GetSpellId());
		}
		/*if(isAlive() && CanAgroHash(aur->m_spellProto->NameHash)) //no threat for hunter's mark
		{
			Unit * pCaster = aur->GetUnitCaster();
			if(!pCaster) return;

			addAttacker(pCaster);

			GetAIInterface()->AttackReaction(pCaster, 1, aur->GetSpellId());
		}*/
	}

	if (aur->GetSpellProto()->AuraInterruptFlags & AURA_INTERRUPT_ON_INVINCIBLE)
	{
		Unit * pCaster = aur->GetUnitCaster();
		if(pCaster)
		{
			pCaster->RemoveStealth();
			pCaster->RemoveInvisibility();
			pCaster->RemoveAllAuraByNameHash(SPELL_HASH_ICE_BLOCK);
			pCaster->RemoveAllAuraByNameHash(SPELL_HASH_DIVINE_SHIELD);
			pCaster->RemoveAllAuraByNameHash(SPELL_HASH_BLESSING_OF_PROTECTION);
		}
	}
    
	uint32 flag = 0;
	if( aur->GetSpellProto()->MechanicsType == MECHANIC_ENRAGED && !asc_enraged++ )
        flag |= AURASTATE_FLAG_ENRAGED;
	if( aur->GetSpellProto()->BGR_one_buff_on_target & SPELL_TYPE_SEAL && !asc_seal++ )
		flag |= AURASTATE_FLAG_JUDGEMENT;

	SetFlag( UNIT_FIELD_AURASTATE, flag );
}

bool Unit::RemoveAura(Aura *aur)
{
	if ( aur == NULL ) 
		return false;

	aur->Remove();
	return true;
}

bool Unit::RemoveAura(uint32 spellId)
{//this can be speed up, if we know passive \pos neg
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId )
		{
			m_auras[x]->Remove();
			return true;  // sky: yes, only one, see bug charges/auras queues
		}
	return false;
}

bool Unit::RemoveAuraFirst(uint32 spellId) // cebernic: just remove and return true
{
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId )
		{
			m_auras[x]->Remove();
			return true;
		}
	return false;
}

bool Unit::RemoveAuras(uint32 * SpellIds)
{
	if(!SpellIds || *SpellIds == 0)
		return false;

	uint32 x,y;
	bool res = false;
	for(x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		if(m_auras[x])
		{
			for(y=0;SpellIds[y] != 0;y++)
			{
				if( m_auras[x] && m_auras[x]->GetSpellId()==SpellIds[y] )
				{
					m_auras[x]->Remove();
					res = true;
				}
			}
		}
	}
	return res;
}

bool Unit::RemoveAurasByHeal()
{
	bool res = false;
	for( uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++ )
	{
		if ( m_auras[x] )
		{
			switch( m_auras[x]->GetSpellId() )
			{
				// remove after heal
				case 35321:
				case 38363:
				case 39215:
				{
					m_auras[x]->Remove();
					res = true;
				} break;
				// remove when healed to 100%
				case 31956:
				case 38801:
				case 43093:
				{
					if ( GetUInt32Value( UNIT_FIELD_HEALTH ) == GetUInt32Value( UNIT_FIELD_MAXHEALTH ) )
					{
						m_auras[x]->Remove();
						res = true;
					}
				} break;
				// remove at p% health
				case 38772:
				{
					uint32 p = m_auras[x]->GetSpellProto()->EffectBasePoints[1];
					if ( GetUInt32Value( UNIT_FIELD_MAXHEALTH ) * p <= GetUInt32Value( UNIT_FIELD_HEALTH ) * 100 )
					{
						m_auras[x]->Remove();
						res = true;
					}
				} break;
			}
		}
	}

	return res;
}

bool Unit::RemoveAura(uint32 spellId, uint64 guid)
{
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId()==spellId && m_auras[x]->m_casterGuid == guid)
			{
				m_auras[x]->Remove();
				return true;
			}
		}
	}
	return false;
}

bool Unit::RemoveAuraFirst(uint32 spellId, uint64 guid)
{
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId()==spellId && m_auras[x]->m_casterGuid == guid)
			{
				m_auras[x]->Remove();
				return true;
			}
		}
	}
	return false;
}

bool Unit::RemoveAuraByNameHash(uint32 namehash)
{
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				return true;
			}
		}
	}
	return false;
}

bool Unit::RemoveAllAuras(uint32 spellId, uint64 guid)
{
	bool res = false;
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId()==spellId)
			{
				if (!guid || m_auras[x]->m_casterGuid == guid)
				{
					m_auras[x]->Remove();
					res = true;
				}
			}
		}
	}
	return res;
}

uint32 Unit::RemoveAllAuraByNameHash(uint32 namehash)
{
	uint32 res = 0;
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				res++;
			}
		}
	}
	return res;
}

uint32 Unit::RemoveAllAuraById(uint32 Id)
{
	uint32 res = 0;
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId()==Id)
			{
				m_auras[x]->Remove();
				res++;
			}
		}
	}
	return res;
}

void Unit::RemoveNegativeAuras()
{
	for(uint32 x=MAX_NEGATIVE_AURAS_EXTEDED_START;x<MAX_REMOVABLE_AURAS_END;x++)
	{
		if(m_auras[x])
		{
            if(m_auras[x]->GetSpellProto()->AttributesExC & CAN_PERSIST_AND_CASTED_WHILE_DEAD)
                continue;
            else
			    m_auras[x]->Remove();
		}
	}
}

void Unit::RemoveAllAuras()
{
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
		if(m_auras[x])
			m_auras[x]->Remove();
}

//ex:to remove morph spells
void Unit::RemoveAllAuraType( uint32 auratype )
{
    for( uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++ )
		if( m_auras[x] && m_auras[x]->HasModType( auratype ) )
			m_auras[x]->Remove();//remove all morph auras containing to this spell (like wolf morph also gives speed)
}


//ex:to remove morph spells
void Unit::RemoveAllAuraFromSelfType2(uint32 auratype, uint32 butskip_hash)
{
    for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
		if(m_auras[x])
		{
			SpellEntry *proto=m_auras[x]->GetSpellProto();
			if( proto->BGR_one_buff_from_caster_on_self == auratype
				&& proto->NameHash != butskip_hash
				&& m_auras[x]->GetCaster() == this
				)
				RemoveAura(m_auras[x]->GetSpellId());//remove all morph auras containing to this spell (like wolf morph also gives speed)
		}
}

bool Unit::SetAurDuration(uint32 spellId,Unit* caster,uint32 duration)
{
	sLog.outString("setAurDuration2");
	Aura*aur=FindAura(spellId,caster->GetGUID());
	if(!aur)
		return false;
	aur->SetDuration(duration);
	sEventMgr.ModifyEventTimeLeft(aur, EVENT_AURA_REMOVE, duration);

/*	if(this->IsPlayer())
	{
		WorldPacket data(5);
		data.SetOpcode(SMSG_UPDATE_AURA_DURATION_OBSOLETE);
		data << (uint8)(aur)->m_visualSlot << duration; // cebernic: GetAuraSlot replaced due to Zack's patch...*sigh*..
		static_cast< Player* >( this )->GetSession()->SendPacket( &data );
	}

	WorldPacket data(SMSG_SET_EXTRA_AURA_INFO_OBSOLETE,21);
	data << GetNewGUID() << aur->m_visualSlot << uint32(spellId) << uint32(duration) << uint32(duration);
	SendMessageToSet(&data,false);*/

	return true;
}

bool Unit::SetAurDuration(uint32 spellId,uint32 duration)
{
	Aura*aur=FindAura(spellId);

	if(!aur)
		return false;


	sLog.outString("setAurDuration2");
	aur->SetDuration(duration);
	sEventMgr.ModifyEventTimeLeft(aur, EVENT_AURA_REMOVE, duration);

/*	if(this->IsPlayer())
	{
		WorldPacket data(5);
		data.SetOpcode(SMSG_UPDATE_AURA_DURATION_OBSOLETE);
		data << (uint8)(aur)->m_visualSlot << duration;
		static_cast< Player* >( this )->GetSession()->SendPacket( &data );
	}
	WorldPacket data(SMSG_SET_EXTRA_AURA_INFO_OBSOLETE,21);
	data << GetNewGUID() << aur->m_visualSlot << uint32(spellId) << uint32(duration) << uint32(duration);
	SendMessageToSet(&data,false);*/


	return true;
}


Aura* Unit::FindAuraByNameHash(uint32 namehash)
{
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
		if( m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash )
				return m_auras[x];
	return NULL;
}

Aura* Unit::FindAura(uint32 spellId)
{
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
		if(m_auras[x])
			if(m_auras[x]->GetSpellId()==spellId)
				return m_auras[x];
	return NULL;
}

Aura* Unit::FindAura(uint32 spellId, uint64 guid)
{
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
		if(m_auras[x])
			if(m_auras[x]->GetSpellId() == spellId && m_auras[x]->m_casterGuid == guid)
				return m_auras[x];
	return NULL;
}

void Unit::_UpdateSpells( uint32 time )
{
	/* to avoid deleting the current spell */
	if(m_currentSpell != NULL)
	{
//		m_spellsbusy=true;
		m_currentSpell->update(time);
//		m_spellsbusy=false;
	}
}

void Unit::castSpell( Spell * pSpell )
{
	// check if we have a spell already casting etc
	if(m_currentSpell && pSpell != m_currentSpell)
	{
/*
		//removed by zack : Spell system does not really handle well parallel casting. We are forced to cancel previous cast
		//eventually make creatures be able to cast secondary spell that is tracked or figure out where is this deleted
		if(m_spellsbusy)
		{
			// shouldn't really happen. but due to spell system bugs there are some cases where this can happen.
			sEventMgr.AddEvent(this,&Unit::CancelSpell,m_currentSpell,EVENT_UNIT_DELAYED_SPELL_CANCEL,1,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}
		else*/
		m_currentSpell->cancel();
	}

	m_currentSpell = pSpell;
	pLastSpell = pSpell->GetProto();
}

int32 Unit::GetSpellDmgBonus(Unit *pVictim, SpellEntry *spellInfo,int32 base_dmg, bool isdot)
{
	int32 plus_damage = 0;
	Unit* caster = this;
	uint32 school = spellInfo->School;

	if( spellInfo->c_is_flags & SPELL_FLAG_IS_NOT_USING_DMG_BONUS )
		return 0;

	if( caster->IsPlayer() )
	{
		switch( static_cast<Player*>(this)->getClass() )
		{
			case ROGUE:
			case WARRIOR:
			case DEATHKNIGHT:
			case HUNTER:
				return 0;
			default: break;
		}
	}

//------------------------------by school---------------------------------------------------
	plus_damage += caster->GetDamageDoneMod(school);
	plus_damage += pVictim->DamageTakenMod[school];
//------------------------------by victim type----------------------------------------------
	if(((Creature*)pVictim)->GetCreatureInfo() && caster->IsPlayer()&& !pVictim->IsPlayer())
		plus_damage += static_cast< Player* >(caster)->IncreaseDamageByType[((Creature*)pVictim)->GetCreatureInfo()->Type];
//==========================================================================================
//==============================+Spell Damage Bonus Modifications===========================
//==========================================================================================
//------------------------------by cast duration--------------------------------------------
	float dmgdoneaffectperc = 1.0f;
	if( spellInfo->Dspell_coef_override >= 0 && !isdot )
		plus_damage = float2int32( float( plus_damage ) * spellInfo->Dspell_coef_override );
	else if( spellInfo->OTspell_coef_override >= 0 && isdot )
		plus_damage = float2int32( float( plus_damage ) * spellInfo->OTspell_coef_override );
	else
	{
		//Bonus to DD part
		if( spellInfo->fixed_dddhcoef >= 0 && !isdot )
			plus_damage = float2int32( float( plus_damage ) * spellInfo->fixed_dddhcoef );
		//Bonus to DoT part
		else if( spellInfo->fixed_hotdotcoef >= 0 && isdot )
		{
			plus_damage = float2int32( float( plus_damage ) * spellInfo->fixed_hotdotcoef );
			if( caster->IsPlayer() )
			{
				int durmod = 0;
				SM_FIValue(caster->SM_FDur, &durmod, spellInfo->SpellGroupType);
				plus_damage += float2int32( float( plus_damage * durmod ) / 15000.0f );
			}
		}
		//In case we dont fit in previous cases do old thing
		else
		{
			plus_damage = float2int32( float( plus_damage ) * spellInfo->casttime_coef );
			float td = float( GetDuration( dbcSpellDuration.LookupEntry( spellInfo->DurationIndex ) ));
			if( spellInfo->NameHash == SPELL_HASH_MOONFIRE || spellInfo->NameHash == SPELL_HASH_IMMOLATE || spellInfo->NameHash == SPELL_HASH_ICE_LANCE || spellInfo->NameHash == SPELL_HASH_PYROBLAST )
				plus_damage = float2int32( float( plus_damage ) * float( 1.0f - ( ( td / 15000.0f ) / ( ( td / 15000.0f ) + dmgdoneaffectperc ) ) ) );
		}
	}

	//------------------------------by downranking----------------------------------------------
	//DOT-DD (Moonfire-Immolate-IceLance-Pyroblast)(Hack Fix)

	if(spellInfo->baseLevel > 0 && spellInfo->maxLevel > 0)
	{
		float downrank1 = 1.0f;
		if(spellInfo->baseLevel < 20)
		    downrank1 = 1.0f - (20.0f - float (spellInfo->baseLevel) ) * 0.0375f;
		float downrank2 = ( float(spellInfo->maxLevel + 5.0f) / float(static_cast< Player* >(caster)->getLevel()) );
		if(downrank2 >= 1 || downrank2 < 0)
		        downrank2 = 1.0f;
		dmgdoneaffectperc *= downrank1 * downrank2;
	}
//==========================================================================================
//==============================Bonus Adding To Main Damage=================================
//==========================================================================================
	int32 bonus_damage = float2int32(plus_damage * dmgdoneaffectperc);

	/*if( isdot )
		bonus_damage += float2int32(bonus_damage * (pVictim->DoTPctIncrease[spellInfo->School] / 100.0f));
	else if( (spellInfo->c_is_flags & SPELL_FLAG_IS_DAMAGING) && (spellInfo->spell_coef_flags & SPELL_FLAG_AOE_SPELL) )
		bonus_damage *= (int32)pVictim->AOEDmgMod;*/

	if( ( pVictim->HasAuraWithMechanics(MECHANIC_ENSNARED) || pVictim->HasAuraWithMechanics(MECHANIC_DAZED) ) && caster->IsPlayer() )
			bonus_damage += static_cast< Player* >(caster)->m_IncreaseDmgSnaredSlowed;

	if(spellInfo->SpellGroupType)
	{
		SM_FIValue(caster->SM_FPenalty, &bonus_damage, spellInfo->SpellGroupType);
		SM_FIValue(caster->SM_FDamageBonus, &bonus_damage, spellInfo->SpellGroupType);

		int dmg_bonus_pct=0;
		SM_FIValue(caster->SM_PPenalty, &dmg_bonus_pct, spellInfo->SpellGroupType);
		SM_FIValue(caster->SM_PDamageBonus,&dmg_bonus_pct,spellInfo->SpellGroupType);

		bonus_damage += (base_dmg+bonus_damage)*dmg_bonus_pct/100;
	}
//------------------------------by school----------------------------------------------
	float summaryPCTmod = caster->GetDamageDonePctMod(school)-1; //value is initialized with 1
	summaryPCTmod += pVictim->DamageTakenPctMod[school];
	summaryPCTmod += caster->DamageDoneModPCT[school];	// BURLEX FIX ME
	summaryPCTmod += pVictim->ModDamageTakenByMechPCT[spellInfo->MechanicsType];

	//Seals of Blood and Martyr
	if( caster->IsPlayer() )
	{
		if( spellInfo->Id == 31893 || spellInfo->Id == 53719 )
		{
			int32 selfdamage = float2int32((( bonus_damage * summaryPCTmod) + bonus_damage ) * 0.1f);
			if( caster->GetUInt32Value(UNIT_FIELD_HEALTH) - selfdamage < 0 )
				caster->SetUInt32Value(UNIT_FIELD_HEALTH, 1);
			else
				caster->ModUnsigned32Value(UNIT_FIELD_HEALTH, -selfdamage);
		}
		else if( spellInfo->Id == 31898 || spellInfo->Id == 53726 )
		{
			int32 selfdamage = float2int32((( bonus_damage * summaryPCTmod) + bonus_damage ) * 0.33f);
			if( caster->GetUInt32Value(UNIT_FIELD_HEALTH) - selfdamage < 0 )
				caster->SetUInt32Value(UNIT_FIELD_HEALTH, 1);
			else
				caster->ModUnsigned32Value(UNIT_FIELD_HEALTH, -selfdamage);
		}
	}
	int32 res = (int32)((base_dmg+bonus_damage)*summaryPCTmod + bonus_damage);
	if( res < 0 )
		res = 0;
	return res;
}

void Unit::InterruptSpell()
{
	if(m_currentSpell)
	{
/*		//ok wtf is this
		//m_currentSpell->SendInterrupted(SPELL_FAILED_INTERRUPTED);
		//m_currentSpell->cancel();
		if(m_spellsbusy)
		{
			// shouldn't really happen. but due to spell system bugs there are some cases where this can happen.
			sEventMgr.AddEvent(this,&Unit::CancelSpell,m_currentSpell,EVENT_UNIT_DELAYED_SPELL_CANCEL,1,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			m_currentSpell=NULL;
		}
		else*/
			m_currentSpell->cancel();
	}
}

void Unit::DeMorph()
{
	// hope it solves it :)
	uint32 displayid = this->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID);
	this->SetUInt32Value(UNIT_FIELD_DISPLAYID, displayid);
	EventModelChange();
}

void Unit::Emote(EmoteType emote)
{
	if(emote == 0)
		return;

	WorldPacket data(SMSG_EMOTE, 12);
	data << uint32(emote);
	data << this->GetGUID();
	SendMessageToSet (&data, true);
}

void Unit::SendChatMessageToPlayer(uint8 type, uint32 lang, const char *msg, Player *plr)
{
	size_t UnitNameLength = 0, MessageLength = 0;
	CreatureInfo *ci = (m_objectTypeId == TYPEID_UNIT) ? ((Creature*)this)->GetCreatureInfo() : NULL;

	if(ci == NULL || plr == NULL)
		return;

	UnitNameLength = strlen((char*)ci->Name) + 1;
	MessageLength = strlen((char*)msg) + 1;

	WorldPacket data(SMSG_MESSAGECHAT, 35 + UnitNameLength + MessageLength);
	data << type;
	data << lang;
	data << GetGUID();
	data << uint32(0);			// new in 2.1.0
	data << uint32(UnitNameLength);
	data << ci->Name;
	data << uint64(0);
	data << uint32(MessageLength);
	data << msg;
	data << uint8(0x00);
	plr->GetSession()->SendPacket(&data);
}

void Unit::SendChatMessageAlternateEntry(uint32 entry, uint8 type, uint32 lang, const char * msg)
{
	size_t UnitNameLength = 0, MessageLength = 0;
	CreatureInfo *ci;

	ci = CreatureNameStorage.LookupEntry(entry);
	if(!ci)
		return;

	UnitNameLength = strlen((char*)ci->Name) + 1;
	MessageLength = strlen((char*)msg) + 1;

	WorldPacket data(SMSG_MESSAGECHAT, 35 + UnitNameLength + MessageLength);
	data << type;
	data << lang;
	data << GetGUID();
	data << uint32(0);			// new in 2.1.0
	data << uint32(UnitNameLength);
	data << ci->Name;
	data << uint64(0);
	data << uint32(MessageLength);
	data << msg;
	data << uint8(0x00);
	SendMessageToSet(&data, true);
}

void Unit::SendChatMessageLocalized(uint8 type, uint32 lang, uint32 IdLocalized)
{
	size_t UnitNameLength = 0, MessageLength = 0;
	CreatureInfo *ci = (m_objectTypeId == TYPEID_UNIT) ? ((Creature*)this)->GetCreatureInfo() : NULL;

	if(ci == NULL)
		return;

	UnitNameLength = strlen((char*)ci->Name) + 1;
	
	if(!IsInWorld())
		return;

	std::set<Player*>::iterator itr = m_inRangePlayers.begin();
	std::set<Player*>::iterator it_end = m_inRangePlayers.end();
		
	for(; itr != it_end; ++itr)
	{
		if((*itr) && (*itr)->GetSession())
		{
			MessageLength = strlen((char*)(*itr)->GetSession()->LocalizedInstanceSrv(IdLocalized)) + 1;

			WorldPacket data(SMSG_MESSAGECHAT, 35 + UnitNameLength + MessageLength);
			data << type;
			data << lang;
			data << GetGUID();
			data << uint32(0);			// new in 2.1.0
			data << uint32(UnitNameLength);
			data << ci->Name;
			data << uint64(0);
			data << uint32(MessageLength);
			data << (*itr)->GetSession()->LocalizedInstanceSrv(IdLocalized);
			data << uint8(0x00);

			(*itr)->GetSession()->SendPacket(&data);
		}
	}
}

void Unit::SendChatMessage(uint8 type, uint32 lang, const char *msg, ...)
{
	size_t UnitNameLength = 0, MessageLength = 0;
	CreatureInfo *ci = (m_objectTypeId == TYPEID_UNIT) ? ((Creature*)this)->GetCreatureInfo() : NULL;

	if(ci == NULL)
		return;

	UnitNameLength = strlen((char*)ci->Name) + 1;
	MessageLength = strlen((char*)msg) + 1;

	WorldPacket data(SMSG_MESSAGECHAT, 35 + UnitNameLength + MessageLength);
	data << type;
	data << lang;
	data << GetGUID();
	data << uint32(0);			// new in 2.1.0
	data << uint32(UnitNameLength);
	data << ci->Name;
	data << uint64(0);
	data << uint32(MessageLength);
	data << msg;
	data << uint8(0x00);
	SendMessageToSet(&data, true);
}

void Unit::WipeHateList()
{
	GetAIInterface()->WipeHateList();
}
void Unit::ClearHateList()
{
	GetAIInterface()->ClearHateList();
}

void Unit::WipeTargetList()
{
	GetAIInterface()->WipeTargetList();
}

void Unit::AddInRangeObject(Object* pObj)
{
	if((pObj->GetTypeId() == TYPEID_UNIT) || (pObj->GetTypeId() == TYPEID_PLAYER))
	{
		if( isHostile( this, (Unit*)pObj ) )
			m_oppFactsInRange.insert(pObj);

		if ( isFriendly( this, (Unit*)pObj ) )
			m_sameFactsInRange.insert(pObj);
    }

	Object::AddInRangeObject(pObj);
}//427

void Unit::OnRemoveInRangeObject(Object* pObj)
{
	AquireInrangeLock();
	m_oppFactsInRange.erase(pObj);
	m_sameFactsInRange.erase(pObj);
	ReleaseInrangeLock();

	if(pObj->GetTypeId() == TYPEID_UNIT || pObj->GetTypeId() == TYPEID_PLAYER)
	{
		/*if(m_useAI)*/

		Unit *pUnit = static_cast<Unit*>(pObj);
		GetAIInterface()->CheckTarget(pUnit);

		if(GetUInt64Value(UNIT_FIELD_CHARM) == pObj->GetGUID())
			if(m_currentSpell)
				m_currentSpell->cancel();

        Object::OnRemoveInRangeObject(pObj);
        if(critterPet == pObj)
		{
			critterPet->SafeDelete();
			critterPet = 0;
		}
	}
    else
    {
        Object::OnRemoveInRangeObject(pObj);
    }
}

void Unit::ClearInRangeSet()
{
	Object::ClearInRangeSet();
}

//Events
void Unit::EventAddEmote(EmoteType emote, uint32 time)
{
	m_oldEmote = GetUInt32Value(UNIT_NPC_EMOTESTATE);
	SetUInt32Value(UNIT_NPC_EMOTESTATE,emote);
	sEventMgr.AddEvent(this, &Creature::EmoteExpire, EVENT_UNIT_EMOTE, time, 1,0);
}

void Unit::EmoteExpire()
{
	SetUInt32Value(UNIT_NPC_EMOTESTATE, m_oldEmote);
	sEventMgr.RemoveEvents(this, EVENT_UNIT_EMOTE);
}


uint32 Unit::GetResistance(uint32 type)
{
	return GetUInt32Value(UNIT_FIELD_RESISTANCES+type);
}

void Unit::MoveToWaypoint(uint32 wp_id)
{
	if(this->m_useAI && this->GetAIInterface() != NULL)
	{
		AIInterface *ai = GetAIInterface();
		WayPoint *wp = ai->getWayPoint(wp_id);
		if(!wp)
		{
			sLog.outString("WARNING: Invalid WP specified in MoveToWaypoint.");
			return;
		}

		ai->m_currentWaypoint = wp_id;
		if(wp->flags!=0)
			ai->m_moveRun = true;
		ai->MoveTo(wp->x, wp->y, wp->z, 0);
	}
}

int32 Unit::GetDamageDoneMod(uint32 school)
{
	if (school < SCHOOL_COUNT)
	{
		if( this->IsPlayer() )
		   return (int32)GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS + school ) - (int32)GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_NEG + school );
		else
		   return static_cast< Creature* >( this )->ModDamageDone[school];
	}
	else
		sLog.outDebug("[NOTICE] You have bad DB, spell school = %u\n",school);
	return 0;
}

float Unit::GetDamageDonePctMod(uint32 school)
{
	if (school < SCHOOL_COUNT)
	{
	    if(this->IsPlayer())
		   return m_floatValues[PLAYER_FIELD_MOD_DAMAGE_DONE_PCT+school];
		else
		   return ((Creature*)this)->ModDamageDonePct[school];
	}
	else
		sLog.outDebug("[NOTICE] You have bad DB, spell school = %u\n",school);
	return 0;
}

void Unit::CalcDamage()
{
	if( IsPlayer() )
		static_cast< Player* >( this )->CalcDamage();
	else
	{
		if( IsPet() )
			static_cast< Pet * >(this)->UpdateAP();
		float r;
		float delta;
		float mult;

		float ap_bonus = float(GetAP())/14000.0f;

		float bonus = ap_bonus * ( GetUInt32Value(UNIT_FIELD_BASEATTACKTIME) + static_cast< Creature* >( this )->m_speedFromHaste );

		delta = float(((Creature*)this)->ModDamageDone[0]);
		mult = float(((Creature*)this)->ModDamageDonePct[0]);
		r = ( BaseDamage[0] + bonus ) * mult + delta;
		// give some diversity to pet damage instead of having a 77-78 damage range (as an example)
		SetFloatValue(UNIT_FIELD_MINDAMAGE,r > 0 ? ( IsPet() ? r * 0.9f : r ) : 0 );
		r = ( BaseDamage[1] + bonus ) * mult + delta;
		SetFloatValue(UNIT_FIELD_MAXDAMAGE, r > 0 ? ( IsPet() ? r * 1.1f : r ) : 0 );

	//	SetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE,BaseRangedDamage[0]*mult+delta);
	//	SetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE,BaseRangedDamage[1]*mult+delta);

	}
}

//returns absorbed dmg
uint32 Unit::ManaShieldAbsorb(uint32 dmg)
{
	if(!m_manashieldamt)
		return 0;
	//mana shield group->16. the only

	uint32 mana = GetUInt32Value(UNIT_FIELD_POWER1);
	int32 effectbonus = SM_PEffectBonus ? SM_PEffectBonus[16] : 0;

	int32 potential = (mana*50)/((100+effectbonus));
	if(potential>m_manashieldamt)
		potential = m_manashieldamt;

	if((int32)dmg<potential)
		potential = dmg;

	uint32 cost = (potential*(100+effectbonus))/50;

	SetUInt32Value(UNIT_FIELD_POWER1,mana-cost);
	m_manashieldamt -= potential;
	if(!m_manashieldamt)
		RemoveAura(m_manaShieldId);
	return potential;
}

// grep: Remove any AA spells that aren't owned by this player.
//		 Otherwise, if he logs out and in and joins another group,
//		 he'll apply it to them.
/*
void Unit::RemoveAllAreaAuras()
{
	AuraList::iterator itr,it1;
	for(itr = m_auras.begin();itr!=m_auras.end();)
	{
		it1 = itr++;
		if(((*it1)->m_spellProto->Effect[0] == SPELL_EFFECT_APPLY_AREA_AURA ||
			(*it1)->m_spellProto->Effect[1] == SPELL_EFFECT_APPLY_AREA_AURA ||
			(*it1)->m_spellProto->Effect[2] == SPELL_EFFECT_APPLY_AREA_AURA) && (*it1)->GetCaster() != this)
		{
			(*it1)->Remove();
			m_auras.erase(it1);
		}
	}
}
*/
uint32 Unit::AbsorbDamage( uint32 School, uint32* dmg )
{
	if( dmg == NULL )
		return 0;

	if( School > 6 )
		return 0;

	SchoolAbsorb::iterator i, j;
	uint32 abs = 0;
	for( i = Absorbs[School].begin(); i != Absorbs[School].end(); )
	{
		if(IsPlayer()){
			SpellEntry *aSpell = dbcSpell.LookupEntry((*i)->spellid);
			//Cheat death
			if( aSpell != NULL && aSpell->SpellFamilyName == 8 && aSpell->spellIconID == 2109 )
			{
				++i;
				SpellEntry *dSpell = dbcSpell.LookupEntry(31231);
				//checking for 1 min cooldown
				if(!(static_cast< Player* >( this )->Cooldown_CanCast(dSpell)))
					continue;

				uint32 ch=this->GetUInt32Value(UNIT_FIELD_HEALTH);
				uint32 mh=this->GetUInt32Value(UNIT_FIELD_MAXHEALTH);

				//check for proc chance
				if (RandomFloat(100.0f)>float(aSpell->procChance))
					continue;
				if((*dmg) >= ch)
				{
					/*
						looks like the following lines are not so good, we check and cast on spell id 31231_
						and adding the cooldown to it, but it looks like this spell is useless(all it's doing is_
						casting 45182, so we can do all this stuff on 45182 at first place), BUT_
						as long as proceeding cheat death is not so height (how many rogue at the same time_
						gonna get to this point?) so it's better to use it because we wont lose anything!!
					*/
					static_cast< Player* >( this )->CastSpell(this->GetGUID(), dSpell, true);
					// set dummy effect,
					// this spell is used to procced the post effect of cheat death later.
					// Move next line to SPELL::SpellEffectDummy ?!! well it's better in case of dbc changing!!
					static_cast< Player* >( this )->CastSpell(this->GetGUID(), 45182, true);
					//Better to add custom cooldown procedure then fucking with entry, or not!!
					dSpell->RecoveryTime = 60000;
					static_cast< Player* >( this )->Cooldown_Add(dSpell, NULL);
					uint32 realdamage;
					//calc abs and applying it
					realdamage = this->GetHealthPct() > 10 ? ch - (mh / 10) : 0;
					abs += (*dmg) - realdamage;
					(*dmg) = realdamage;
				}

				if(!*dmg)
					break;

				continue;
			}//end of cheat death
		}
		if( (int32)(*dmg) >= (*i)->amt)//remove this absorb
		{
			(*dmg) -= (*i)->amt;
			abs += (*i)->amt;
			j = i++;

			if( i != Absorbs[School].end() )
			{
				while( (*i)->spellid == (*j)->spellid )
				{
					++i;
					if( i == Absorbs[School].end() )
						break;
				}
			}

			this->RemoveAura((*j)->spellid); //,(*j)->caster);
			if(!*dmg)//absorbed all dmg
				break;
		}
		else //absorb full dmg
		{
			abs += *dmg;
			(*i)->amt -= *dmg;
			*dmg=0;
			break;
		}
	}

	if(IsPlayer() && ((Player*)this)->GodModeCheat)
	{
		abs += *dmg;
		*dmg = 0;
	}

	return abs;
}

bool Unit::setDetectRangeMod(uint64 guid, int32 amount)
{
	int next_free_slot = -1;
	for(int i = 0; i < 5; i++)
	{
		if(m_detectRangeGUID[i] == 0 && next_free_slot == -1)
		{
			next_free_slot = i;
		}
		if(m_detectRangeGUID[i] == guid)
		{
			m_detectRangeMOD[i] = amount;
			return true;
		}
	}
	if(next_free_slot != -1)
	{
		m_detectRangeGUID[next_free_slot] = guid;
		m_detectRangeMOD[next_free_slot] = amount;
		return true;
	}
	return false;
}

void Unit::unsetDetectRangeMod(uint64 guid)
{
	for(int i = 0; i < 5; i++)
	{
		if(m_detectRangeGUID[i] == guid)
		{
			m_detectRangeGUID[i] = 0;
			m_detectRangeMOD[i] = 0;
		}
	}
}

int32 Unit::getDetectRangeMod(uint64 guid)
{
	for(int i = 0; i < 5; i++)
	{
		if(m_detectRangeGUID[i] == guid)
		{
			return m_detectRangeMOD[i];
		}
	}
	return 0;
}

void Unit::SetStandState(uint8 standstate)
{
	//only take actions if standstate did change.
	StandState bef = GetStandState();
	if( bef == standstate )
		return;

	SetByte( UNIT_FIELD_BYTES_1, 0, standstate );
	if( standstate == STANDSTATE_STAND )//standup
		RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_STAND_UP);

	if( m_objectTypeId == TYPEID_PLAYER )
		static_cast< Player* >( this )->GetSession()->OutPacket( SMSG_STANDSTATE_UPDATE, 1, &standstate );
}

void Unit::RemoveAurasByInterruptFlag(uint32 flag)
{
	Aura * a;
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		a = m_auras[x];
		if(a == NULL)
			continue;

		//some spells do not get removed all the time only at specific intervals
		if((a->m_spellProto->AuraInterruptFlags & flag) && !(a->m_spellProto->procFlags & PROC_REMOVEONUSE))
		{
			a->Remove();
			m_auras[x] = NULL;
		}
	}
}

bool Unit::HasAuraVisual(uint32 visualid)
{
	//passive auras do not have visual (at least when code was written)
	for(uint32 x=MAX_REMOVABLE_AURAS_START;x<MAX_REMOVABLE_AURAS_END;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->SpellVisual==visualid)
			return true;
	return false;
}

bool Unit::HasAura(uint32 spellid)
{
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()== spellid)
		{
			return true;
		}

		return false;
}
uint16 Unit::GetAuraStackCount(uint32 spellid)
{
	uint16 count = 0;
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()== spellid)
			count++;
	return count;
}

void Unit::DropAurasOnDeath()
{
	for(uint32 x=MAX_REMOVABLE_AURAS_START;x<MAX_REMOVABLE_AURAS_END;x++)
        if(m_auras[x])
        {
            if(m_auras[x] && m_auras[x]->GetSpellProto()->AttributesExC & CAN_PERSIST_AND_CASTED_WHILE_DEAD)
                continue;
            else
		        m_auras[x]->Remove();
        }
}

void Unit::UpdateSpeed()
{
	if(GetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID) == 0)
	{
		if(IsPlayer())
			m_runSpeed = m_base_runSpeed*(1.0f + ((float)m_speedModifier)/100.0f);
		else
			m_runSpeed = m_base_runSpeed*(1.0f + ((float)m_speedModifier)/100.0f);
	}
	else
	{
		if(IsPlayer())
		{
			m_runSpeed = m_base_runSpeed*(1.0f + ((float)m_mountedspeedModifier)/100.0f);
			m_runSpeed += (m_speedModifier<0) ? (m_base_runSpeed*((float)m_speedModifier)/100.0f) : 0;
		}
		else
		{
			m_runSpeed = m_base_runSpeed*(1.0f + ((float)m_mountedspeedModifier)/100.0f);
			m_runSpeed += (m_speedModifier<0) ? (m_base_runSpeed*((float)m_speedModifier)/100.0f) : 0;
		}
	}



	m_flySpeed = PLAYER_NORMAL_FLIGHT_SPEED*(1.0f + ((float)m_flyspeedModifier)/100.0f);

	// Limit speed due to effects such as http://www.wowhead.com/?spell=31896 [Judgement of Justice]
	if( m_maxSpeed && m_runSpeed > m_maxSpeed )
	{
		m_runSpeed = m_maxSpeed;
	}

	if(IsPlayer())
	{
		if(((Player*)this)->m_changingMaps)
			static_cast< Player* >( this )->resend_speed = true;
		else
		{
			static_cast< Player* >( this )->SetPlayerSpeed(RUN, m_runSpeed);
			static_cast< Player* >( this )->SetPlayerSpeed(FLY, m_flySpeed);
		}
	}
}

bool Unit::HasBuff(uint32 spellid) // cebernic:it does not check passive auras & must be visible auras
{
	for(uint32 x=MAX_POSITIVE_AURAS_EXTEDED_START;x<MAX_POSITIVE_AURAS_EXTEDED_END;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellid)
			return true;

	return false;
}

bool Unit::HasBuff(uint32 spellid,uint64 guid)
{
	for(uint32 x=MAX_POSITIVE_AURAS_EXTEDED_START;x<MAX_POSITIVE_AURAS_EXTEDED_END;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellid && m_auras[x]->m_casterGuid==guid)
			return true;

	return false;
}

bool Unit::HasVisialPosAurasOfNameHashWithCaster(uint32 namehash, Unit * caster)
{
	for(uint32 i = MAX_POSITIVE_AURAS_EXTEDED_START; i < MAX_POSITIVE_AURAS_EXTEDED_END; ++i)
		if( m_auras[i] && m_auras[i]->GetSpellProto()->NameHash == namehash && m_auras[i]->GetCasterGUID() == caster->GetGUID() )
			return true;

	return false;
}

void Unit::EventSummonPetExpire()
{
	if(summonPet)
	{
		if(summonPet->GetEntry() == 7915)//Goblin Bomb
		{
			SpellEntry *spInfo = dbcSpell.LookupEntry(13259);
			if(!spInfo)
				return;

			Spell * sp = SpellPool.PooledNew();
			if (!sp)
				return;
			sp->Init(summonPet,spInfo,true,NULL);
			SpellCastTargets tgt;
			tgt.m_unitTarget=summonPet->GetGUID();
			sp->prepare(&tgt);
		}
		else
		{
			summonPet->RemoveFromWorld(false, true);
			delete summonPet;
			summonPet = NULL;
		}
	}
	sEventMgr.RemoveEvents(this, EVENT_SUMMON_PET_EXPIRE);
}

uint8 Unit::CastSpell(Unit* Target, SpellEntry* Sp, bool triggered)
{
	if( Sp == NULL )
		return SPELL_FAILED_UNKNOWN;

	Spell *newSpell = SpellPool.PooledNew();
	if (!newSpell)
		return SPELL_FAILED_UNKNOWN;
	newSpell->Init(this, Sp, triggered, 0);
	SpellCastTargets targets(0);
	if(Target)
	{
		targets.m_targetMask |= TARGET_FLAG_UNIT;
		targets.m_unitTarget = Target->GetGUID();
	}
	else
	{
		newSpell->GenerateTargets(&targets);
	}
	return newSpell->prepare(&targets);
}

uint8 Unit::CastTrainerSpell(Unit* Target, SpellEntry* Sp, bool triggered)
{
	if( Sp == NULL )
		return SPELL_FAILED_UNKNOWN;

	Spell *newSpell = SpellPool.PooledNew();
	if (!newSpell)
		return SPELL_FAILED_UNKNOWN;
	newSpell->Init(Target, Sp, triggered, 0);
	SpellCastTargets targets(0);
	if(Target)
	{
		targets.m_targetMask |= TARGET_FLAG_UNIT;
		targets.m_unitTarget = Target->GetGUID();
	}
	else
	{
		newSpell->GenerateTargets(&targets);
	}
	return newSpell->prepare(&targets);
}

uint8 Unit::CastSpell(Unit* Target, uint32 SpellID, bool triggered)
{
	SpellEntry * ent = dbcSpell.LookupEntry(SpellID);
	if(ent == 0) return SPELL_FAILED_UNKNOWN;

	return CastSpell(Target, ent, triggered);
}

uint8 Unit::CastSpell(uint64 targetGuid, SpellEntry* Sp, bool triggered)
{
	if( Sp == NULL )
		return SPELL_FAILED_UNKNOWN;

	SpellCastTargets targets(targetGuid);
	Spell *newSpell = SpellPool.PooledNew();
	if (!newSpell)
		return 0;
	newSpell->Init(this, Sp, triggered, 0);
	return newSpell->prepare(&targets);
}

uint8 Unit::CastSpell(uint64 targetGuid, uint32 SpellID, bool triggered)
{
	SpellEntry * ent = dbcSpell.LookupEntry(SpellID);
	if(ent == 0) return SPELL_FAILED_UNKNOWN;

	return CastSpell(targetGuid, ent, triggered);
}
void Unit::CastSpellAoF(float x,float y,float z,SpellEntry* Sp, bool triggered)
{
	if( Sp == NULL )
		return;

	SpellCastTargets targets;
	targets.m_destX = x;
	targets.m_destY = y;
	targets.m_destZ = z;
	targets.m_targetMask=TARGET_FLAG_DEST_LOCATION;
	Spell *newSpell = SpellPool.PooledNew();
	if (!newSpell)
		return;
	newSpell->Init(this, Sp, triggered, 0);
	newSpell->prepare(&targets);
}

void Unit::PlaySpellVisual(uint64 target, uint32 spellVisual)
{
	WorldPacket data(SMSG_PLAY_SPELL_VISUAL, 12);
	data << target << spellVisual;
	SendMessageToSet(&data, true);
}

void Unit::Root()
{
	this->m_special_state |= UNIT_STATE_ROOT;

	if(m_objectTypeId == TYPEID_PLAYER)
	{
		static_cast< Player* >( this )->SetMovement(MOVE_ROOT, 1);
	}
	else
	{
		m_aiInterface->m_canMove = false;
		m_aiInterface->StopMovement(1);
	}
}

void Unit::Unroot()
{
	this->m_special_state &= ~UNIT_STATE_ROOT;

	if(m_objectTypeId == TYPEID_PLAYER)
	{
		static_cast< Player* >( this )->SetMovement(MOVE_UNROOT, 5);
	}
	else
	{
		m_aiInterface->m_canMove = true;
	}
}

void Unit::RemoveAurasByBuffType(uint32 buff_type, const uint64 &guid, uint32 skip)
{
	uint64 sguid = buff_type >= SPELL_TYPE_BLESSING ? guid : 0;

	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		if(	m_auras[x] //have aura
			&& (m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & buff_type) // aura is in same group
			&& m_auras[x]->GetSpellId() != skip // make sure to not do self removes in case aura will stack
			&& (!sguid || (sguid && m_auras[x]->m_casterGuid == sguid)) // we either remove everything or just buffs from us
			)
				m_auras[x]->Remove();
	}
}

void Unit::RemoveAurasByBuffIndexType(uint32 buff_index_type, const uint64 &guid)
{
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->BGR_one_buff_from_caster_on_1target == buff_index_type)
			if(!guid || (guid && m_auras[x]->m_casterGuid == guid))
				m_auras[x]->Remove();
	}
}

bool Unit::HasAurasOfBuffType(uint32 buff_type, const uint64 &guid,uint32 skip)
{
	uint64 sguid = (buff_type == SPELL_TYPE_BLESSING || buff_type == SPELL_TYPE_WARRIOR_SHOUT) ? guid : 0;

	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & buff_type && m_auras[x]->GetSpellId()!=skip)
			if(!sguid || (m_auras[x]->m_casterGuid == sguid))
				return true;
	}

	return false;
}

uint32 Unit::FindAuraCountByHash(uint32 HashName, uint32 maxcount)
{
	uint32 count = 0;

	for( uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x )
	{
		if( m_auras[x] && ( m_auras[x]->GetSpellProto()->NameHash == HashName ) )
		{
			count++;
			if( count == maxcount )
				break;
		}
	}

	return count;
}

AuraCheckResponse Unit::AuraCheck(SpellEntry *proto, Object *caster)
{
	AuraCheckResponse resp;

	// no error for now
	resp.Error = AURA_CHECK_RESULT_NONE;
	resp.Misc  = 0;
	
	uint32 name_hash = proto->NameHash;
	uint32 rank = proto->RankNumber;

	// look for spells with same namehash
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		//if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash && m_auras[x]->GetCaster()==caster)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
		{
			// we've got an aura with the same name as the one we're trying to apply
			resp.Misc = m_auras[x]->GetSpellProto()->Id;

			// compare the rank to our applying spell
			if( m_auras[x]->GetSpellProto()->RankNumber > rank )
			{
				if(	proto->Effect[0] == SPELL_EFFECT_TRIGGER_SPELL ||
					proto->Effect[1] == SPELL_EFFECT_TRIGGER_SPELL ||
					proto->Effect[2] == SPELL_EFFECT_TRIGGER_SPELL )
				{
					resp.Error = AURA_CHECK_RESULT_LOWER_BUFF_PRESENT;
				}
				else
					resp.Error = AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT;
			}
			else
				resp.Error = AURA_CHECK_RESULT_LOWER_BUFF_PRESENT;

			// we found something, save some loops and exit
			break;
		}
	}
	sLog.outDebug( "resp = %i", resp.Error );
	// return it back to our caller
	return resp;
}


AuraCheckResponse Unit::AuraCheck(uint32 name_hash, uint32 rank, Aura* aur, Object *caster)
{
	AuraCheckResponse resp;

	// no error for now
	resp.Error = AURA_CHECK_RESULT_NONE;
	resp.Misc  = 0;

	// look for spells with same namehash
//	if(aur->GetSpellProto()->NameHash == name_hash && aur->GetCaster()==caster)
	if(aur->GetSpellProto()->NameHash == name_hash)
	{
		// we've got an aura with the same name as the one we're trying to apply
		resp.Misc = aur->GetSpellProto()->Id;

		// compare the rank to our applying spell
		if(aur->GetSpellProto()->RankNumber > rank)
			resp.Error = AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT;
		else
			resp.Error = AURA_CHECK_RESULT_LOWER_BUFF_PRESENT;
	}

	// return it back to our caller
	return resp;
}

void Unit::OnPushToWorld()
{
	//Zack : we already relocated events on aura add ?
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
	{
		if(m_auras[x] != 0)
			m_auras[x]->RelocateEvents();
	}
}

//! Remove Unit from world
void Unit::RemoveFromWorld(bool free_guid)
{
	CombatStatus.OnRemoveFromWorld();
	if(critterPet != 0)
	{
		critterPet->RemoveFromWorld(false, true);
		//removed by Zack. Multiple deletes would lead to crash.
//		delete critterPet;
		critterPet = 0;
	}

	if(dynObj != 0)
		dynObj->Remove();

	for(uint32 i = 0; i < 4; ++i)
	{
		if(m_ObjectSlots[i] != 0)
		{
			GameObject * obj = m_mapMgr->GetGameObject(m_ObjectSlots[i]);
			if(obj)
				obj->ExpireAndDelete();

			m_ObjectSlots[i] = 0;
		}
	}

	Object::RemoveFromWorld(free_guid);

	//zack: should relocate new events to new eventmanager and not to -1
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
		if(m_auras[x] != 0)
		{
			if( m_auras[x]->m_deleted )
			{
				m_auras[x] = NULL;
				continue;
			}
			m_auras[x]->RelocateEvents();
		}

	m_aiInterface->WipeReferences();
}

void Unit::RemoveAurasByInterruptFlagButSkip(uint32 flag, uint32 skip)
{
	Aura * a;
	for(uint32 x=MAX_TOTAL_AURAS_START;x<MAX_TOTAL_AURAS_END;x++)
	{
		a = m_auras[x];
		if(a == 0)
			continue;

		//some spells do not get removed all the time only at specific intervals
		if((a->m_spellProto->AuraInterruptFlags & flag) && (a->m_spellProto->Id != skip) && a->m_spellProto->proc_interval==0)
		{
			//the black sheep's of society
			if(a->m_spellProto->AuraInterruptFlags & AURA_INTERRUPT_ON_CAST_SPELL)
			{
				switch(a->GetSpellProto()->NameHash)
				{
				case SPELL_HASH_BORROWED_TIME:
					{
						continue;
					}break;
				case SPELL_HASH_FEL_ARMOR:
				case SPELL_HASH_DEMON_ARMOR:
				case SPELL_HASH_DEMON_SKIN:
					{
						SpellEntry *spi = dbcSpell.LookupEntry( skip );
						if( spi && spi->Id != 28176
								&& spi->Id != 28189
								&& spi->Id != 47892
								&& spi->Id != 47893
								&& spi->Id != 706
								&& spi->Id != 1086
								&& spi->Id != 11733
								&& spi->Id != 11734
								&& spi->Id != 11735
								&& spi->Id != 27260
								&& spi->Id != 47793
								&& spi->Id != 47889
								&& spi->Id != 687
								&& spi->Id != 696)
							continue;
					}break;
				}
				switch(a->GetSpellProto()->Id)
				{
					case 34936:
					{
						SpellEntry *spi = dbcSpell.LookupEntry( skip );
						if( spi && spi->Id != 686
								&& spi->Id != 695
								&& spi->Id != 705
								&& spi->Id != 1088
								&& spi->Id != 1106
								&& spi->Id != 7641
								&& spi->Id != 11659
								&& spi->Id != 11660
								&& spi->Id != 11661
								&& spi->Id != 25307
								&& spi->Id != 27209
								&& spi->Id != 47808
								&& spi->Id != 47809
								&& spi->Id != 29722
								&& spi->Id != 32231
								&& spi->Id != 47837
								&& spi->Id != 47838)
								continue;
					}break;
					//priest - surge of light
					case 33151:
						{
							//our luck. it got triggered on smite..we do not remove it just yet
							if( m_currentSpell && m_currentSpell->GetProto()->NameHash == SPELL_HASH_FLASH_HEAL )
								continue;

							//this spell gets removed only when casting smite
						    SpellEntry *spi = dbcSpell.LookupEntry( skip );
							if( spi && spi->NameHash != SPELL_HASH_FLASH_HEAL && spi->NameHash != SPELL_HASH_SMITE )
								continue;
						}break;
					/*case 34936:	// Backlash
						{
							if( m_currentSpell && m_currentSpell->GetProto()->NameHash == SPELL_HASH_SHADOW_BOLT )
								continue;
							if( m_currentSpell && m_currentSpell->GetProto()->NameHash == SPELL_HASH_INCINERATE )
								continue;
							SpellEntry *spi = dbcSpell.LookupEntry( skip );
							if( spi && spi->NameHash != SPELL_HASH_SHADOW_BOLT && spi->NameHash != SPELL_HASH_INCINERATE )
								continue;
						}break;*/
					case 59578: // Art of War
					case 53489:
						{
							SpellEntry *spi = dbcSpell.LookupEntry( skip );
							if( spi && spi->Id != 19750
									&& spi->Id != 19939
									&& spi->Id != 19940
									&& spi->Id != 19941
									&& spi->Id != 19942
									&& spi->Id != 19943
									&& spi->Id != 27137
									&& spi->Id != 48784
									&& spi->Id != 48785
									&& spi->Id != 879
									&& spi->Id != 5614
									&& spi->Id != 5615
									&& spi->Id != 10312
									&& spi->Id != 10313
									&& spi->Id != 10314
									&& spi->Id != 27138
									&& spi->Id != 48800
									&& spi->Id != 48801)
								continue;
						}break;
					case 17941: //Shadow Trance
						{
							if( m_currentSpell && m_currentSpell->GetProto()->NameHash == SPELL_HASH_SHADOW_BOLT)
								continue;
							SpellEntry *spi = dbcSpell.LookupEntry( skip );
							if( spi && spi->NameHash != SPELL_HASH_SHADOW_BOLT )
								continue;
						}break;
					case 16166: // [Shaman] Elemental Mastery
						{
						    SpellEntry *spi = dbcSpell.LookupEntry( skip );
							if (spi && !(spi->School==SCHOOL_FIRE||spi->School==SCHOOL_FROST||spi->School==SCHOOL_NATURE))
								continue;
						}break;
				}
			}
			a->Remove();
		}
	}
}

int Unit::GetAuraSpellIDWithNameHash(uint32 name_hash)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
			return m_auras[x]->m_spellProto->Id;
	}

	return 0;
}

int Unit::HasAurasWithNameHash(uint32 name_hash)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
			return m_auras[x]->m_spellProto->Id;
	}

	return 0;
}

bool Unit::HasAuraWithMechanics(uint32 mechanic)
{
	for( uint32 x = MAX_NEGATIVE_AURAS_EXTEDED_START; x < MAX_NEGATIVE_AURAS_EXTEDED_END; ++x )
	{
		if( m_auras[x] && m_auras[x]->m_spellProto )
			if( Spell::GetMechanic(m_auras[x]->m_spellProto) == mechanic )
				return true;
	}

	return false;
}

/*
bool Unit::HasNegativeAuraWithNameHash(uint32 name_hash)
{
	for(uint32 x = MAX_POSITIVE_AURAS; x < MAX_AURAS + MAX_PASSIVE_AURAS; ++x)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
			return true;
	}

	return false;
}

bool Unit::HasNegativeAura(uint32 spell_id)
{
	for(uint32 x = MAX_POSITIVE_AURAS; x < MAX_AURAS + MAX_PASSIVE_AURAS; ++x)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->Id == spell_id)
			return true;
	}

	return false;
}

uint32 Unit::CountNegativeAura(uint32 spell_id)
{
	uint32 ret=0;
	for(uint32 x = MAX_POSITIVE_AURAS; x < MAX_AURAS + MAX_PASSIVE_AURAS; ++x)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->Id == spell_id)
			ret++;
	}

	return ret;
}*/

bool Unit::IsPoisoned()
{
	for(uint32 x = MAX_NEGATIVE_AURAS_EXTEDED_START; x < MAX_NEGATIVE_AURAS_EXTEDED_END; ++x)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_POISON)
			return true;

	return false;
}

uint32 Unit::ModVisualAuraStackCount(Aura *aur, int32 count)
{
	if( !aur )
		return 0;

	uint8 slot = aur->m_visualSlot;
	if( slot >= MAX_NEGATIVE_VISUAL_AURAS_END)
		return 0;

	if(count < 0 && m_auraStackCount[slot] <= -count )
	{
		m_auraStackCount[slot] = 0;
		m_auravisuals[slot] = 0;
		WorldPacket data(SMSG_AURA_UPDATE, 20);
		FastGUIDPack(data, GetGUID());
		data << uint8(slot);
		data << uint32(0);
		SendMessageToSet(&data, true);
 	}
 	else {
 		m_auraStackCount[slot] += static_cast<uint8>( count );
		m_auravisuals[slot] = aur->GetSpellId();
		uint16 flags;
		if( aur->IsPositive() )
		{
//			flags = 0x0000;
			flags = 0x1D39;
//			if( stack != 0 )
//				flags = 0x1D3B;
		}
		else
//			flags = 0x8000;
			flags = 0x1DA1;
		WorldPacket data(SMSG_AURA_UPDATE, 20);
		FastGUIDPack(data, GetGUID());
		data << uint8(slot);
		data << uint32(aur->GetSpellId());
		data << uint16(flags);
		data << uint8(m_auraStackCount[slot]);
		if( flags & 0x0000 || !aur->IsPositive() )
//			FastGUIDPack(data, aur->m_casterGuid);
			data << uint8(0);
		data << uint32(aur->GetDuration()) << uint32(aur->GetTimeLeft());
		SendMessageToSet(&data, true);
	}

 	return m_auraStackCount[slot];
}

void Unit::RemoveAurasOfSchool(uint32 School, bool Positive, bool Immune)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
		if( m_auras[x]
			&& m_auras[x]->GetSpellProto()->School == School
			&& (!m_auras[x]->IsPositive() || Positive)
			&& (!Immune && m_auras[x]->GetSpellProto()->Attributes & ATTRIBUTES_IGNORE_INVULNERABILITY)
			)
			m_auras[x]->Remove();
}

void Unit::EnableFlight()
{
	if(m_objectTypeId != TYPEID_PLAYER || ((Player*)this)->m_changingMaps)
	{
		WorldPacket data(SMSG_MOVE_SET_CAN_FLY, 13);
		data << GetNewGUID();
		data << uint32(2);
		SendMessageToSet(&data, true);

		if( IsPlayer() )
		{
			static_cast< Player* >( this )->m_setflycheat = true;
		}
	}
	else
	{
		WorldPacket * data = new WorldPacket(SMSG_MOVE_SET_CAN_FLY, 13);
		*data << GetNewGUID();
		*data << uint32(2);
		SendMessageToSet(data, false);
		static_cast< Player* >( this )->z_axisposition = 0.0f;
		static_cast< Player* >( this )->delayedPackets.add( data );
		static_cast< Player* >( this )->m_setflycheat = true;
	}
}

void Unit::DisableFlight()
{
	if(m_objectTypeId != TYPEID_PLAYER || ((Player*)this)->m_changingMaps)
	{
		WorldPacket data(SMSG_MOVE_UNSET_CAN_FLY, 13);
		data << GetNewGUID();
		data << uint32(5);
		SendMessageToSet(&data, true);

		if( IsPlayer() )
			static_cast< Player* >( this )->m_setflycheat = false;
	}
	else
	{
		WorldPacket * data = new WorldPacket( SMSG_MOVE_UNSET_CAN_FLY, 13 );
		*data << GetNewGUID();
		*data << uint32(5);
		SendMessageToSet(data, false);
		static_cast< Player* >( this )->z_axisposition = 0.0f;
		static_cast< Player* >( this )->delayedPackets.add( data );
		static_cast< Player* >( this )->m_setflycheat = false;
	}
}

bool Unit::IsDazed()
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ENSNARED)
			return true;
			for(uint32 y=0;y<3;y++)
			if(m_auras[x]->GetSpellProto()->EffectMechanic[y]==MECHANIC_ENSNARED)
				return true;
		}
	}

	return false;

}

void Unit::UpdateVisibility()
{
	ByteBuffer buf(3000);
	InRangeSet::iterator itr, it3;
	uint32 count;
	bool can_see;
	bool is_visible;
	Player *pl;
	Object * pObj;
	Player * plr;

	if( m_objectTypeId == TYPEID_PLAYER )
	{
		plr = static_cast< Player* >( this );
		for( Object::InRangeSet::iterator itr = m_objectsInRange.begin(); itr != m_objectsInRange.end();)
		{
			pObj = (*itr);
			++itr;

			can_see = plr->CanSee(pObj);
			is_visible = plr->GetVisibility(pObj, &it3);
			if(can_see)
			{
				if(!is_visible)
				{
					buf.clear();
					count = pObj->BuildCreateUpdateBlockForPlayer( &buf, plr );
					plr->PushCreationData(&buf, count);
					plr->AddVisibleObject(pObj);
				}
			}
			else
			{
				if(is_visible)
				{
					pObj->DestroyForPlayer(plr);
					plr->RemoveVisibleObject(it3);
				}
			}

			if( pObj->GetTypeId() == TYPEID_PLAYER )
			{
				pl = static_cast< Player* >( pObj );
				can_see = pl->CanSee( plr );
				is_visible = pl->GetVisibility( plr, &it3 );
				if( can_see )
				{
					if(!is_visible)
					{
						buf.clear();
						count = plr->BuildCreateUpdateBlockForPlayer( &buf, pl );
						pl->PushCreationData(&buf, count);
						pl->AddVisibleObject(plr);
					}
				}
				else
				{
					if(is_visible)
					{
						plr->DestroyForPlayer(pl);
						pl->RemoveVisibleObject(it3);
					}
				}
			}
		}
	}
	else			// For units we can save a lot of work
	{
		for(set<Player*>::iterator it2 = GetInRangePlayerSetBegin(); it2 != GetInRangePlayerSetEnd(); ++it2)
		{
			can_see = (*it2)->CanSee(this);
			is_visible = (*it2)->GetVisibility(this, &itr);
			if(!can_see)
			{
				if(is_visible)
				{
					DestroyForPlayer(*it2);
					(*it2)->RemoveVisibleObject(itr);
				}
			}
			else
			{
				if(!is_visible)
				{
					buf.clear();
					count = BuildCreateUpdateBlockForPlayer(&buf, *it2);
					(*it2)->PushCreationData(&buf, count);
					(*it2)->AddVisibleObject(this);
				}
			}
		}
	}
}

void Unit::RemoveSoloAura(uint32 type)
{
	switch(type)
	{
		case 1:// Polymorph
		{
			if(!polySpell) return;
			if(HasAura(polySpell))
				RemoveAura(polySpell);
		}break;
/*		case 2:// Sap
		{
			if(!sapSpell) return;
			if(HasActiveAura(sapSpell))
				RemoveAura(sapSpell);
		}break;
		case 3:// Fear (Warlock)
		{
			if(!fearSpell) return;
			if(HasActiveAura(fearSpell))
				RemoveAura(fearSpell);
		}break;*/
		default:
			{
			sLog.outDebug("Warning: we are trying to remove a soloauratype that has no handle");
			}break;
	}
}

void Unit::EventHealthChangeSinceLastUpdate()
{
	int pct = GetHealthPct();
	if( pct < 35 )
	{
		uint32 toset = AURASTATE_FLAG_HEALTH35;
		if( pct < 20 )
			toset |= AURASTATE_FLAG_HEALTH20;
		else
			RemoveFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_HEALTH20 );
		SetFlag( UNIT_FIELD_AURASTATE, toset );
	}
	else
		RemoveFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_HEALTH35 | AURASTATE_FLAG_HEALTH20 );

	if( pct < 75 )
		RemoveFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_HEALTH75 );
	else
		SetFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_HEALTH75 );
}

int32 Unit::GetAP()
{
    int32 baseap = GetUInt32Value(UNIT_FIELD_ATTACK_POWER) + GetUInt32Value(UNIT_FIELD_ATTACK_POWER_MODS);
    float totalap = float(baseap)*(GetFloatValue(UNIT_FIELD_ATTACK_POWER_MULTIPLIER)+1);
	if(totalap>=0)
		return float2int32(totalap);
	return	0;
}

int32 Unit::GetRAP()
{
    int32 baseap = GetUInt32Value(UNIT_FIELD_RANGED_ATTACK_POWER) + GetUInt32Value(UNIT_FIELD_RANGED_ATTACK_POWER_MODS);
    float totalap = float(baseap)*(GetFloatValue(UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER)+1);
	if(totalap>=0)
		return float2int32(totalap);
	return	0;
}

bool Unit::GetSpeedDecrease()
{
	int32 before=m_speedModifier;
	m_speedModifier -= m_slowdown;
	m_slowdown = 0;
	map< uint32, int32 >::iterator itr = speedReductionMap.begin();
	for(; itr != speedReductionMap.end(); ++itr)
		m_slowdown = (int32)min( m_slowdown, itr->second );

	if(m_slowdown<-100)
		m_slowdown = 100; //do not walk backwards !

	m_speedModifier += m_slowdown;
	//save bandwidth :P
	if(m_speedModifier!=before)
		return true;
	return false;
}

void Unit::EventCastSpell(Unit * Target, SpellEntry * Sp)
{
	Spell * pSpell = SpellPool.PooledNew();
	if (!pSpell)
		return;
	pSpell->Init(Target, Sp, true, NULL);
	SpellCastTargets targets(Target->GetGUID());
	pSpell->prepare(&targets);
}

void Unit::SetFacing(float newo)
{
	SetOrientation(newo);
	/*WorldPacket data(40);
	data.SetOpcode(MSG_MOVE_SET_FACING);
	data << GetNewGUID();
	data << (uint32)0; //flags
	data << (uint32)0; //time
	data << GetPositionX() << GetPositionY() << GetPositionZ() << newo;
	data << (uint32)0; //unk
	SendMessageToSet( &data, false );*/

	/*WorldPacket data(SMSG_MONSTER_MOVE, 60);
	data << GetNewGUID();
	data << uint8(0);
	data << m_position << getMSTime();
	data << uint8(4) << newo;
	data << uint32(0x00000000);		// flags
	data << uint32(0);				// time
	data << m_position;				// position
	SendMessageToSet(&data, true);*/

	m_aiInterface->SendMoveToPacket(m_position.x,m_position.y,m_position.z,m_position.o,1,0x1000); // MoveFlags = 0x1000 (run)
}

//guardians are temporary spawn that will inherit master faction and will follow them. Apart from that they have their own mind
Unit* Unit::create_guardian(uint32 guardian_entry,uint32 duration,float angle, uint32 lvl, GameObject * obj, LocationVector * Vec)
{
	CreatureProto * proto = CreatureProtoStorage.LookupEntry(guardian_entry);
	CreatureInfo * info = CreatureNameStorage.LookupEntry(guardian_entry);
	float m_fallowAngle = angle;
	float x = 3 * ( cosf( m_fallowAngle + GetOrientation() ) );
	float y = 3 * ( sinf( m_fallowAngle + GetOrientation() ) );
	float z = 0;

	if(!proto || !info)
	{
		sLog.outDetail("Warning : Missing summon creature template %u !",guardian_entry);
		return NULL;
	}

	Creature* p = GetMapMgr()->CreateCreature(guardian_entry);
	p->SetInstanceID(GetMapMgr()->GetInstanceID());

	if( Vec )
	{
		x += Vec->x;
		y += Vec->y;
		z += Vec->z;
		p->Load(proto, x, y, z);
	}
	//Summoned by a GameObject?
	else if ( !obj )
	{
		x += GetPositionX();
		y += GetPositionY();
		z += GetPositionZ();
		p->Load(proto, x, y, z);
	}
	else //if so, we should appear on it's location ;)
	{
		x += obj->GetPositionX();
		y += obj->GetPositionY();
		z += obj->GetPositionZ();
		p->Load(proto, x, y, z);
	}

	if ( lvl != 0 )
	{
		/* MANA */
		p->SetPowerType(POWER_TYPE_MANA);
		p->SetUInt32Value(UNIT_FIELD_MAXPOWER1,p->GetUInt32Value(UNIT_FIELD_MAXPOWER1)+28+10*lvl);
		p->SetUInt32Value(UNIT_FIELD_POWER1,p->GetUInt32Value(UNIT_FIELD_POWER1)+28+10*lvl);
		/* HEALTH */
		p->SetUInt32Value(UNIT_FIELD_MAXHEALTH,p->GetUInt32Value(UNIT_FIELD_MAXHEALTH)+28+30*lvl);
		p->SetUInt32Value(UNIT_FIELD_HEALTH,p->GetUInt32Value(UNIT_FIELD_HEALTH)+28+30*lvl);
		/* LEVEL */
		p->SetUInt32Value(UNIT_FIELD_LEVEL, lvl);
	}

	p->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, GetGUID());
    p->SetUInt64Value(UNIT_FIELD_CREATEDBY, GetGUID());
    p->SetZoneId(GetZoneId());
	p->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE,GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
	p->_setFaction();

	p->GetAIInterface()->Init(p,AITYPE_PET,MOVEMENTTYPE_NONE,this);
	p->GetAIInterface()->SetUnitToFollow(this);
	p->GetAIInterface()->SetUnitToFollowAngle(m_fallowAngle);
	p->GetAIInterface()->SetFollowDistance(3.0f);
	p->m_noRespawn = true;

	p->PushToWorld(GetMapMgr());

	/*if(p->GetEntry() == 31216)
	{
		CastSpell(p, 45204, true); 
	}*/

	sEventMgr.AddEvent(p, &Creature::SummonExpire, EVENT_SUMMON_EXPIRE, duration, 1,0);

	return p;//lol, will compiler make the pointer conversion ?

}

float Unit::get_chance_to_daze(Unit *target)
{
//	if(GetTypeId()!=TYPEID_UNIT)
//		return 0.0f;
	float attack_skill = float( getLevel() ) * 5.0f;
	float defense_skill;
	if( target->IsPlayer() )
		defense_skill = float( static_cast< Player* >( target )->_GetSkillLineCurrent( SKILL_DEFENSE, false ) );
	else defense_skill = float( target->getLevel() * 5 );
	if( !defense_skill )
		defense_skill = 1;
	float chance_to_daze = attack_skill * 20 / defense_skill;//if level is equal then we get a 20% chance to daze
	chance_to_daze = chance_to_daze * std::min(target->getLevel() / 30.0f, 1.0f );//for targets below level 30 the chance decreases
	if( chance_to_daze > 40 )
		return 40.0f;
	else
		return chance_to_daze;
}

void CombatStatusHandler::ClearMyHealers()
{
	// this is where we check all our healers
	HealedSet::iterator i;
	Player * pt;
	for(i = m_healers.begin(); i != m_healers.end(); ++i)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*i);
		if(pt != NULL)
			pt->CombatStatus.RemoveHealed(m_Unit);
	}

	m_healers.clear();
}

void CombatStatusHandler::WeHealed(Unit * pHealTarget)
{
	if(pHealTarget->GetTypeId() != TYPEID_PLAYER || m_Unit->GetTypeId() != TYPEID_PLAYER || pHealTarget == m_Unit)
		return;

	if(pHealTarget->CombatStatus.IsInCombat())
	{
		m_healed.insert(pHealTarget->GetLowGUID());
		pHealTarget->CombatStatus.m_healers.insert(m_Unit->GetLowGUID());
	}

	UpdateFlag();
}

void CombatStatusHandler::RemoveHealed(Unit * pHealTarget)
{
	m_healed.erase(pHealTarget->GetLowGUID());
	UpdateFlag();
}

void CombatStatusHandler::UpdateFlag()
{
	bool n_status = InternalIsInCombat();
	if(n_status != m_lastStatus)
	{
		m_lastStatus = n_status;
		if(n_status)
		{
			//printf(I64FMT" is now in combat.\n", m_Unit->GetGUID());
			m_Unit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
			if(!m_Unit->hasStateFlag(UF_ATTACKING)) m_Unit->addStateFlag(UF_ATTACKING);
		}
		else
		{
			//printf(I64FMT" is no longer in combat.\n", m_Unit->GetGUID());
			m_Unit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
			if(m_Unit->hasStateFlag(UF_ATTACKING)) m_Unit->clearStateFlag(UF_ATTACKING);

			// remove any of our healers from combat too, if they are able to be.
			ClearMyHealers();
		}
	}
}

bool CombatStatusHandler::InternalIsInCombat()
{
	if(m_Unit->IsPlayer() && m_Unit->GetMapMgr() && m_Unit->GetMapMgr()->IsCombatInProgress())
		return true;

	if(m_healed.size() > 0)
		return true;

	if(m_attackTargets.size() > 0)
		return true;

	if(m_attackers.size() > 0)
		return true;

	return false;
}

void CombatStatusHandler::AddAttackTarget(const uint64& guid)
{
	if(guid == m_Unit->GetGUID())
		return;

	m_attackTargets.insert(guid);
	//printf("Adding attack target "I64FMT" to "I64FMT"\n", guid, m_Unit->GetGUID());
	if(m_Unit->GetTypeId() == TYPEID_PLAYER &&
		m_primaryAttackTarget != guid)			// players can only have one attack target.
	{
		if(m_primaryAttackTarget)
			ClearPrimaryAttackTarget();

		m_primaryAttackTarget = guid;
	}

	UpdateFlag();
}

void CombatStatusHandler::ClearPrimaryAttackTarget()
{
	//printf("ClearPrimaryAttackTarget for "I64FMT"\n", m_Unit->GetGUID());
	if(m_primaryAttackTarget != 0)
	{
		Unit * pt = m_Unit->GetMapMgr()->GetUnit(m_primaryAttackTarget);
		if(pt != NULL)
		{
			// remove from their attacker set. (if we have no longer got any DoT's, etc)
			if(!IsAttacking(pt))
			{
				pt->CombatStatus.RemoveAttacker(m_Unit, m_Unit->GetGUID());
				m_attackTargets.erase(m_primaryAttackTarget);
			}

			m_primaryAttackTarget = 0;
		}
		else
		{
			m_attackTargets.erase(m_primaryAttackTarget);
			m_primaryAttackTarget = 0;
		}
	}

	UpdateFlag();
}

bool CombatStatusHandler::IsAttacking(Unit * pTarget)
{
	// check the target for any of our DoT's.
	for(uint32 i = MAX_NEGATIVE_AURAS_EXTEDED_START; i < MAX_NEGATIVE_AURAS_EXTEDED_END; ++i)
		if(pTarget->m_auras[i] != NULL)
			if(m_Unit->GetGUID() == pTarget->m_auras[i]->m_casterGuid && pTarget->m_auras[i]->IsCombatStateAffecting())
				return true;

	// place any additional checks here
	return false;
}

void CombatStatusHandler::RemoveAttackTarget(Unit * pTarget)
{
	// called on aura remove, etc.
	AttackerMap::iterator itr = m_attackTargets.find(pTarget->GetGUID());
	if(itr == m_attackTargets.end())
		return;

	if(!IsAttacking(pTarget))
	{
		//printf("Removing attack target "I64FMT" on "I64FMT"\n", pTarget->GetGUID(), m_Unit->GetGUID());
		m_attackTargets.erase(itr);
		if(m_primaryAttackTarget == pTarget->GetGUID())
			m_primaryAttackTarget = 0;

		UpdateFlag();
	}
	/*else
		printf("Cannot remove attack target "I64FMT" from "I64FMT"\n", pTarget->GetGUID(), m_Unit->GetGUID());*/
}

void CombatStatusHandler::RemoveAttacker(Unit * pAttacker, const uint64& guid)
{
	AttackerMap::iterator itr = m_attackers.find(guid);
	if(itr == m_attackers.end())
		return;

	if( (!pAttacker) || (!pAttacker->CombatStatus.IsAttacking(m_Unit)) )
	{
		//printf("Removing attacker "I64FMT" from "I64FMT"\n", guid, m_Unit->GetGUID());
		m_attackers.erase(itr);
		UpdateFlag();
	}
	/*else
	{
		printf("Cannot remove attacker "I64FMT" from "I64FMT"\n", guid, m_Unit->GetGUID());
	}*/
}

void CombatStatusHandler::OnDamageDealt( Unit * pTarget )
{
	// we added an aura, or dealt some damage to a target. they need to have us as an attacker, and they need to be our attack target if not.
	//printf("OnDamageDealt to "I64FMT" from "I64FMT"\n", pTarget->GetGUID(), m_Unit->GetGUID());
	if( pTarget == m_Unit )
		return;

	//no need to be in combat if dead
	if( !pTarget->isAlive() || !m_Unit->isAlive() )
		return;

	AttackerMap::iterator itr = m_attackTargets.find( pTarget->GetGUID() );
	if( itr == m_attackTargets.end() )
		AddAttackTarget(pTarget->GetGUID());

	itr = pTarget->CombatStatus.m_attackers.find( m_Unit->GetGUID() );
	if( itr == pTarget->CombatStatus.m_attackers.end() )
		pTarget->CombatStatus.AddAttacker( m_Unit->GetGUID() );

	// update the timeout
	m_Unit->CombatStatusHandler_ResetPvPTimeout();
}

void CombatStatusHandler::AddAttacker(const uint64& guid)
{
	m_attackers.insert(guid);
	UpdateFlag();
}

void CombatStatusHandler::ClearAttackers()
{
	// this is a FORCED function, only use when the reference will be destroyed.
	AttackerMap::iterator itr = m_attackTargets.begin();
	Unit * pt;
	for(; itr != m_attackTargets.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetUnit(*itr);
		if(pt)
		{
			pt->CombatStatus.m_attackers.erase(m_Unit->GetGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	for(itr = m_attackers.begin(); itr != m_attackers.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetUnit(*itr);
		if(pt)
		{
			pt->CombatStatus.m_attackTargets.erase(m_Unit->GetGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	m_attackers.clear();
	m_attackTargets.clear();
	m_primaryAttackTarget = 0;
	UpdateFlag();
}

void CombatStatusHandler::ClearHealers()
{

	if( m_Unit->GetMapMgr() == NULL )
		return; //wierd crash bug

	HealedSet::iterator itr = m_healed.begin();
	Player * pt;
	for(; itr != m_healed.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*itr);
		if(pt)
		{
			pt->CombatStatus.m_healers.erase(m_Unit->GetLowGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	for(itr = m_healers.begin(); itr != m_healers.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*itr);
		if(pt)
		{
			pt->CombatStatus.m_healed.erase(m_Unit->GetLowGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	m_healed.clear();
	m_healers.clear();
	UpdateFlag();
}

void CombatStatusHandler::OnRemoveFromWorld()
{
	ClearAttackers();
	ClearHealers();
}

bool CombatStatusHandler::IsInCombat()
{
	// If the unit doesn't exist - OR - the unit exists but is not in world
	if( !m_Unit || ( m_Unit && !m_Unit->IsInWorld() ) )
		return false;

	switch (m_Unit->GetTypeId())
	{
		case TYPEID_UNIT:
		{
			if (m_Unit->IsPet() && ((Pet*)m_Unit)->GetPetAction() == PET_ACTION_ATTACK)
				return true;
			else if (m_Unit->IsPet())
				return m_lastStatus;
			else
				return m_Unit->GetAIInterface()->getAITargetsCount()==0? false:true;
		} break;
		case TYPEID_PLAYER:
		{
			if (((Player*)m_Unit)->GetSummon() != NULL && ((Player*)m_Unit)->GetSummon()->GetPetOwner() == m_Unit && ((Player*)m_Unit)->GetSummon()->CombatStatus.IsInCombat())
				return true;

			return m_lastStatus;
		} break;
		default: return false;
	}
}

void Unit::CombatStatusHandler_ResetPvPTimeout()
{
	if(!IsPlayer())
		return;

	m_lock.Acquire();
	EventMap::iterator itr = m_events.find(EVENT_ATTACK_TIMEOUT);
	if(itr != m_events.end())
	{
		for(; itr != m_events.upper_bound(EVENT_ATTACK_TIMEOUT); ++itr)
		{
			if(!itr->second->deleted)
			{
				itr->second->currTime = 5000;
				m_lock.Release();
				return;
			}
		}
	}
	// TESTING GROUND TESTING
	//this->SendChatMessage( CHAT_MSG_MONSTER_SAY , LANG_UNIVERSAL , "Eye of C'thun AI Initialized" );
	//this->SendChatMessage(
	//	this->Emote( EMOTE_ONESHOT_SPELLCAST );
	// yay for recursive mutexes
	sEventMgr.AddEvent(this, &Unit::CombatStatusHandler_UpdatePvPTimeout, EVENT_ATTACK_TIMEOUT, 5000, 1, 0);
	m_lock.Release();
}

void Unit::CombatStatusHandler_UpdatePvPTimeout()
{
	CombatStatus.TryToClearAttackTargets();
}

void Unit::Heal(Unit *target, uint32 SpellId, uint32 amount)
{
	if(!target || !SpellId || !amount)
		return;

	uint32 ch=target->GetUInt32Value(UNIT_FIELD_HEALTH);
	uint32 mh=target->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
	if(mh!=ch)
	{
		ch += amount;
		uint32 overheal = 0;

		if(ch > mh)
		{
			target->SetUInt32Value(UNIT_FIELD_HEALTH, mh);
			overheal = amount - mh;
			amount += (mh - ch);
		}
		else
			target->SetUInt32Value(UNIT_FIELD_HEALTH, ch);

		WorldPacket data(SMSG_SPELLHEALLOG, 29);
		data << target->GetNewGUID();
		data << this->GetNewGUID();
		data << uint32(SpellId);
		data << uint32(amount);							// amt healed
		data << uint32(overheal);						// Amount Overhealed
		data << uint8(0);								// critical message
		this->SendMessageToSet(&data, true);

		target->RemoveAurasByHeal();
	}
}

void Unit::Energize( Unit* target, uint32 SpellId, uint32 amount, uint32 type )
{	
	//Static energize
	if( !target || !SpellId || !amount )
		return;

	uint32 cur = target->GetUInt32Value( UNIT_FIELD_POWER1 + type );
	uint32 max = target->GetUInt32Value( UNIT_FIELD_MAXPOWER1 + type );

	//if( max == cur ) // can we show null power gains in client? eg. zero happiness gain should be show...
		//return;

	if( cur + amount > max )
		amount = max - cur;

	target->SetUInt32Value( UNIT_FIELD_POWER1 + type, cur + amount );

	WorldPacket datamr( SMSG_SPELLENERGIZELOG, 30 );
	datamr << target->GetNewGUID();
	datamr << this->GetNewGUID();
	datamr << SpellId;
	datamr << type;
	datamr << amount;
	this->SendMessageToSet( &datamr, true );
}
/*
void Unit::Energize( Unit* target, uint32 SpellId, uint32 amount, uint32 type )
{	
	//Static energize
	if( !target || !SpellId || !amount )
		return;

	uint32 cur = target->GetUInt32Value( UNIT_FIELD_POWER1 + type );
	uint32 max = target->GetUInt32Value( UNIT_FIELD_MAXPOWER1 + type );

	if(max != cur)
	{
		amount += GetSpellDmgBonus( target, dbcSpell.LookupEntry(SpellId), amount, false );
		if( !amount )
			return;

		cur += amount;
		if( cur > max )
		{
			target->SetUInt32Value( UNIT_FIELD_POWER1 + type, max );
			amount = max - cur;
		}
		else 
			target->SetUInt32Value( UNIT_FIELD_POWER1 + type, cur );

		WorldPacket datamr( SMSG_SPELLENERGIZELOG, 30 );
		datamr << target->GetNewGUID();
		datamr << this->GetNewGUID();
		datamr << SpellId;
		datamr << type;
		datamr << amount;

		this->SendMessageToSet( &datamr, true );
		target->SendPowerUpdate( false );
	}
}
*/
void Unit::InheritSMMods(Unit *inherit_from)
{
	if(inherit_from == NULL)
		return;

	if(inherit_from->SM_CriticalChance)
	{
		if(SM_CriticalChance==0)
			SM_CriticalChance = new int32[SPELL_GROUPS];
		memcpy(SM_CriticalChance,inherit_from->SM_CriticalChance,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FDur)
	{
		if(SM_FDur==0)
			SM_FDur = new int32[SPELL_GROUPS];
		memcpy(SM_FDur,inherit_from->SM_FDur,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PDur)
	{
		if(SM_PDur==0)
			SM_PDur = new int32[SPELL_GROUPS];
		memcpy(SM_PDur,inherit_from->SM_PDur,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PRadius)
	{
		if(SM_PRadius==0)
			SM_PRadius = new int32[SPELL_GROUPS];
		memcpy(SM_PRadius,inherit_from->SM_PRadius,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FRadius)
	{
		if(SM_FRadius==0)
			SM_FRadius = new int32[SPELL_GROUPS];
		memcpy(SM_FRadius,inherit_from->SM_FRadius,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FRange)
	{
		if(SM_FRange==0)
			SM_FRange = new int32[SPELL_GROUPS];
		memcpy(SM_FRange,inherit_from->SM_FRange,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCastTime)
	{
		if(SM_PCastTime==0)
			SM_PCastTime = new int32[SPELL_GROUPS];
		memcpy(SM_PCastTime,inherit_from->SM_PCastTime,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FCastTime)
	{
		if(SM_FCastTime==0)
			SM_FCastTime = new int32[SPELL_GROUPS];
		memcpy(SM_FCastTime,inherit_from->SM_FCastTime,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCriticalDamage)
	{
		if(SM_PCriticalDamage==0)
			SM_PCriticalDamage = new int32[SPELL_GROUPS];
		memcpy(SM_PCriticalDamage,inherit_from->SM_PCriticalDamage,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FDOT)
	{
		if(SM_FDOT==0)
			SM_FDOT = new int32[SPELL_GROUPS];
		memcpy(SM_FDOT,inherit_from->SM_FDOT,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PDOT)
	{
		if(SM_PDOT==0)
			SM_PDOT = new int32[SPELL_GROUPS];
		memcpy(SM_PDOT,inherit_from->SM_PDOT,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FEffect1_Bonus)
	{
		if(SM_FEffect1_Bonus==0)
			SM_FEffect1_Bonus = new int32[SPELL_GROUPS];
		memcpy(SM_FEffect1_Bonus,inherit_from->SM_FEffect1_Bonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PEffect1_Bonus)
	{
		if(SM_PEffect1_Bonus==0)
			SM_PEffect1_Bonus = new int32[SPELL_GROUPS];
		memcpy(SM_PEffect1_Bonus,inherit_from->SM_PEffect1_Bonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FEffect2_Bonus)
	{
		if(SM_FEffect2_Bonus==0)
			SM_FEffect2_Bonus = new int32[SPELL_GROUPS];
		memcpy(SM_FEffect2_Bonus,inherit_from->SM_FEffect2_Bonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PEffect2_Bonus)
	{
		if(SM_PEffect2_Bonus==0)
			SM_PEffect2_Bonus = new int32[SPELL_GROUPS];
		memcpy(SM_PEffect2_Bonus,inherit_from->SM_PEffect2_Bonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FEffect3_Bonus)
	{
		if(SM_FEffect3_Bonus==0)
			SM_FEffect3_Bonus = new int32[SPELL_GROUPS];
		memcpy(SM_FEffect3_Bonus,inherit_from->SM_FEffect3_Bonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PEffect3_Bonus)
	{
		if(SM_PEffect3_Bonus==0)
			SM_PEffect3_Bonus = new int32[SPELL_GROUPS];
		memcpy(SM_PEffect3_Bonus,inherit_from->SM_PEffect3_Bonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FEffectBonus)
	{
		if(SM_FEffectBonus==0)
			SM_FEffectBonus = new int32[SPELL_GROUPS];
		memcpy(SM_FEffectBonus,inherit_from->SM_FEffectBonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PEffectBonus)
	{
		if(SM_PEffectBonus==0)
			SM_PEffectBonus = new int32[SPELL_GROUPS];
		memcpy(SM_PEffectBonus,inherit_from->SM_PEffectBonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FDamageBonus)
	{
		if(SM_FDamageBonus==0)
			SM_FDamageBonus = new int32[SPELL_GROUPS];
		memcpy(SM_FDamageBonus,inherit_from->SM_FDamageBonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PDamageBonus)
	{
		if(SM_PDamageBonus==0)
			SM_PDamageBonus = new int32[SPELL_GROUPS];
		memcpy(SM_PDamageBonus,inherit_from->SM_PDamageBonus,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PMiscEffect)
	{
		if(SM_PMiscEffect==0)
			SM_PMiscEffect = new int32[SPELL_GROUPS];
		memcpy(SM_PMiscEffect,inherit_from->SM_PMiscEffect,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FMiscEffect)
	{
		if(SM_FMiscEffect==0)
			SM_FMiscEffect = new int32[SPELL_GROUPS];
		memcpy(SM_FMiscEffect,inherit_from->SM_FMiscEffect,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FHitchance)
	{
		if(SM_FHitchance==0)
			SM_FHitchance = new int32[SPELL_GROUPS];
		memcpy(SM_FHitchance,inherit_from->SM_FHitchance,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PRange)
	{
		if(SM_PRange==0)
			SM_PRange = new int32[SPELL_GROUPS];
		memcpy(SM_PRange,inherit_from->SM_PRange,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PRadius)
	{
		if(SM_PRadius==0)
			SM_PRadius = new int32[SPELL_GROUPS];
		memcpy(SM_PRadius,inherit_from->SM_PRadius,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCost)
	{
		if(SM_PCost==0)
			SM_PCost = new int32[SPELL_GROUPS];
		memcpy(SM_PCost,inherit_from->SM_PCost,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FCost)
	{
		if(SM_FCost==0)
			SM_FCost = new int32[SPELL_GROUPS];
		memcpy(SM_FCost,inherit_from->SM_FCost,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FAdditionalTargets)
	{
		if(SM_FAdditionalTargets==0)
			SM_FAdditionalTargets = new int32[SPELL_GROUPS];
		memcpy(SM_FAdditionalTargets,inherit_from->SM_FAdditionalTargets,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PJumpReduce)
	{
		if(SM_PJumpReduce==0)
			SM_PJumpReduce = new int32[SPELL_GROUPS];
		memcpy(SM_PJumpReduce,inherit_from->SM_PJumpReduce,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FGlobalCooldown)
	{
		if(SM_FGlobalCooldown==0)
			SM_FGlobalCooldown = new int32[SPELL_GROUPS];
		memcpy(SM_FGlobalCooldown,inherit_from->SM_FGlobalCooldown,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PGlobalCooldown)
	{
		if(SM_PGlobalCooldown==0)
			SM_PGlobalCooldown = new int32[SPELL_GROUPS];
		memcpy(SM_PGlobalCooldown,inherit_from->SM_PGlobalCooldown,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PNonInterrupt)
	{
		if(SM_PNonInterrupt==0)
			SM_PNonInterrupt = new int32[SPELL_GROUPS];
		memcpy(SM_PNonInterrupt,inherit_from->SM_PNonInterrupt,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FPenalty)
	{
		if(SM_FPenalty==0)
			SM_FPenalty = new int32[SPELL_GROUPS];
		memcpy(SM_FPenalty,inherit_from->SM_FPenalty,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PPenalty)
	{
		if(SM_PPenalty==0)
			SM_PPenalty = new int32[SPELL_GROUPS];
		memcpy(SM_PPenalty,inherit_from->SM_PPenalty,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FCooldownTime)
	{
		if(SM_FCooldownTime==0)
			SM_FCooldownTime = new int32[SPELL_GROUPS];
		memcpy(SM_FCooldownTime,inherit_from->SM_FCooldownTime,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCooldownTime)
	{
		if(SM_PCooldownTime==0)
			SM_PCooldownTime = new int32[SPELL_GROUPS];
		memcpy(SM_PCooldownTime,inherit_from->SM_PCooldownTime,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FChanceOfSuccess)
	{
		if(SM_FChanceOfSuccess==0)
			SM_FChanceOfSuccess = new int32[SPELL_GROUPS];
		memcpy(SM_FChanceOfSuccess,inherit_from->SM_FChanceOfSuccess,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FAmptitude)
	{
		if(SM_FAmptitude==0)
			SM_FAmptitude = new int32[SPELL_GROUPS];
		memcpy(SM_FAmptitude,inherit_from->SM_FAmptitude,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PAmptitude)
	{
		if(SM_PAmptitude==0)
			SM_PAmptitude = new int32[SPELL_GROUPS];
		memcpy(SM_PAmptitude,inherit_from->SM_PAmptitude,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FRezist_dispell)
	{
		if(SM_FRezist_dispell==0)
			SM_FRezist_dispell = new int32[SPELL_GROUPS];
		memcpy(SM_FRezist_dispell,inherit_from->SM_FRezist_dispell,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PRezist_dispell)
	{
		if(SM_PRezist_dispell==0)
			SM_PRezist_dispell = new int32[SPELL_GROUPS];
		memcpy(SM_PRezist_dispell,inherit_from->SM_PRezist_dispell,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FCharges)
	{
		if(SM_FCharges==0)
			SM_FCharges = new int32[SPELL_GROUPS];
		memcpy(SM_FCharges,inherit_from->SM_FCharges,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCharges)
	{
		if(SM_PCharges==0)
			SM_PCharges = new int32[SPELL_GROUPS];
		memcpy(SM_PCharges,inherit_from->SM_PCharges,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FThreat)
	{
		if(SM_FThreat==0)
			SM_FThreat = new int32[SPELL_GROUPS];
		memcpy(SM_FThreat,inherit_from->SM_FThreat,sizeof(int)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PThreat)
	{
		if(SM_PThreat==0)
			SM_PThreat = new int32[SPELL_GROUPS];
		memcpy(SM_PThreat,inherit_from->SM_PThreat,sizeof(int)*SPELL_GROUPS);
	}
}

void CombatStatusHandler::TryToClearAttackTargets()
{
	AttackerMap::iterator i, i2;
	Unit * pt;
	
	if( m_Unit->IsPlayer() )
		static_cast<Player*>(m_Unit)->RemoveFlag(PLAYER_FLAGS, 0x100);


	for(i = m_attackTargets.begin(); i != m_attackTargets.end();)
	{
		i2 = i++;
		pt = m_Unit->GetMapMgr()->GetUnit(*i2);
		if(pt == NULL)
		{
			m_attackTargets.erase(i2);
			continue;
		}

		RemoveAttackTarget(pt);
		pt->CombatStatus.RemoveAttacker(m_Unit,m_Unit->GetGUID());
	}
}

void CombatStatusHandler::AttackersForgetHate()
{
	AttackerMap::iterator i, i2;
	Unit * pt;

	for(i = m_attackTargets.begin(); i != m_attackTargets.end();)
	{
		i2 = i++;
		pt = m_Unit->GetMapMgr()->GetUnit(*i2);
		if(pt == NULL)
		{
			m_attackTargets.erase(i2);
			continue;
		}

		if(pt->GetAIInterface())
			pt->GetAIInterface()->RemoveThreatByPtr(m_Unit);
	}
}

void Unit::CancelSpell(Spell * ptr)
{
/*
	if(ptr)
		ptr->cancel();
	else */
	if(m_currentSpell)
	{
		// this logically might seem a little bit twisted
		// crash situation : an already deleted spell will be called to get canceled by eventmanager
		// solution : We should not delay spell canceling more then second spell canceling.
		// problem : might remove spells that should not be removed. Not sure about it :(
		sEventMgr.RemoveEvents(this,EVENT_UNIT_DELAYED_SPELL_CANCEL);
		m_currentSpell->cancel();
	}
}

void Unit::EventStrikeWithAbility(uint64 guid, SpellEntry * sp, uint32 damage)
{
	Unit * victim = m_mapMgr ? m_mapMgr->GetUnit(guid) : NULL;
	if(victim)
		Strike( victim, RANGED, sp, 0, 0, 0, false, true );
}

void Unit::DispelAll(bool positive)
{
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[i]!=NULL)
			if((m_auras[i]->IsPositive()&&positive)||!m_auras[i]->IsPositive())
				m_auras[i]->Remove();
	}
}

/* bool Unit::RemoveAllAurasByMechanic (renamed from MechanicImmunityMassDispel)
- Removes all auras on this unit that are of a specific mechanic.
- Useful for things like.. Apply Aura: Immune Mechanic, where existing (de)buffs are *always supposed* to be removed.
- I'm not sure if this goes here under unit.
* Arguments:
	- uint32 MechanicType
		*

* Returns;
	- False if no buffs were dispelled, true if more than 0 were dispelled.
*/
bool Unit::RemoveAllAurasByMechanic( uint32 MechanicType , uint32 MaxDispel = -1 , bool HostileOnly = true )
{
	//sLog.outString( "Unit::MechanicImmunityMassDispel called, mechanic: %u" , MechanicType );
	uint32 DispelCount = 0;
	for(uint32 x = ( HostileOnly ? MAX_NEGATIVE_AURAS_EXTEDED_START : MAX_POSITIVE_AURAS_EXTEDED_START ) ; x < MAX_REMOVABLE_AURAS_END ; x++ ) // If HostileOnly = 1, then we use aura slots 40-56 (hostile). Otherwise, we use 0-56 (all)
		{
			if( DispelCount >= MaxDispel && MaxDispel > 0 )
				return true;

			if( m_auras[x] )
			{
					if( m_auras[x]->GetSpellProto()->MechanicsType == MechanicType ) // Remove all mechanics of type MechanicType (my english goen boom)
					{
						//sLog.outString( "Removed aura. [AuraSlot %u, SpellId %u]" , x , m_auras[x]->GetSpellId() );
						// TODO: Stop moving if fear was removed.
						m_auras[x]->Remove(); // EZ-Remove
						DispelCount ++;
					}
					else if( MechanicType == MECHANIC_ENSNARED ) // if got immunity for slow, remove some that are not in the mechanics
					{
						for( int i=0 ; i<3 ; i++ )
						{
							// SNARE + ROOT
							if( m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_DECREASE_SPEED || m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_ROOT )
							{
								m_auras[x]->Remove();
								break;
							}
						}
					}
			}
		}
	return ( DispelCount == 0 );
}

void Unit::RemoveAllMovementImpairing()
{
	for( uint32 x = MAX_NEGATIVE_AURAS_EXTEDED_START; x < MAX_REMOVABLE_AURAS_END; x++ )
	{
		if( m_auras[x] != NULL )
		{
			if( m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ROOTED
				|| m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ENSNARED
				|| m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_DAZED)

			{
				m_auras[x]->Remove();
			}
			else
			{
				for( int i = 0; i < 3; i++ )
				{
					if( m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_DECREASE_SPEED
					|| m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_ROOT )
					{
						m_auras[x]->Remove();
						break;
					}
				}
			}
		}
	}
}

void Unit::setAttackTimer(int32 time, bool offhand)
{
	if(!time)
		time = offhand ? m_uint32Values[UNIT_FIELD_BASEATTACKTIME+1] : m_uint32Values[UNIT_FIELD_BASEATTACKTIME];

	time = std::max(1000,float2int32(float(time)*GetFloatValue(UNIT_MOD_CAST_SPEED)));
	if(time>300000)		// just in case.. shouldn't happen though
		time=offhand ? m_uint32Values[UNIT_FIELD_BASEATTACKTIME+1] : m_uint32Values[UNIT_FIELD_BASEATTACKTIME];

	if(offhand)
		m_attackTimer_1 = getMSTime() + time;
	else
		m_attackTimer = getMSTime() + time;
}

bool Unit::isAttackReady(bool offhand)
{
	if(offhand)
		return (getMSTime() >= m_attackTimer_1) ? true : false;
	else
		return (getMSTime() >= m_attackTimer) ? true : false;
}

void Unit::ReplaceAIInterface(AIInterface *new_interface)
{
	delete m_aiInterface;	//be careful when you do this. Might screw unit states !
	m_aiInterface = new_interface;
}

void Unit::EventUpdateFlag()
{
	CombatStatus.UpdateFlag();
}

void Unit::EventModelChange()
{
	UnitModelSizeEntry  *newmodelhalfsize = NULL;

	//mounts are bigger then normal size
	if( GetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID ) )
		newmodelhalfsize = UnitModelSizeStorage.LookupEntry( GetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID ) );
	if( newmodelhalfsize == NULL )
		newmodelhalfsize = UnitModelSizeStorage.LookupEntry( GetUInt32Value( UNIT_FIELD_DISPLAYID ) );

	if( newmodelhalfsize )
	{
		ModelHalfSize = newmodelhalfsize->HalfSize;
//		if( IsCreature() && static_cast<Creature*>(this)->GetProto() )
//			ModelHalfSize *=  static_cast<Creature*>(this)->GetProto()->BoundingRadius;
	}
	else
		ModelHalfSize = 1.0f; //baaad, but it happens :(
}

void Unit::RemoveFieldSummon()
{
	uint64 guid = GetUInt64Value(UNIT_FIELD_SUMMON);
	if(guid && GetMapMgr())
	{
		Creature *summon = static_cast< Creature* >( GetMapMgr()->GetUnit(guid) );
		if (summon)
		{
			summon->RemoveFromWorld(false,true);
			summon->SafeDelete();
		}
		SetUInt64Value(UNIT_FIELD_SUMMON, 0);
	}
}

void Unit::AggroPvPGuards()
{
	Unit *tmpUnit;
	this->AquireInrangeLock();
	for(Object::InRangeSet::iterator i = GetInRangeSetBegin(); i != GetInRangeSetEnd(); ++i)
	{
		if((*i)->GetTypeId() == TYPEID_UNIT)
		{
			tmpUnit = static_cast< Unit* >(*i);
			if( tmpUnit->GetAIInterface() && tmpUnit->GetAIInterface()->m_isNeutralGuard && CalcDistance(tmpUnit) <= (50.0f * 50.0f) )
			{
				tmpUnit->GetAIInterface()->AttackReaction(this, 1, 0);
			}
		}
	}
	this->ReleaseInrangeLock();
}

//what is an Immobilize spell ? Have to add it later to spell effect handler
void Unit::EventStunOrImmobilize(Unit *proc_target, bool is_victim)
{
	if ( this == proc_target )
		return; //how and why would we stun ourselves

	int32 t_trigger_on_stun,t_trigger_on_stun_chance;
	if( is_victim == false )
	{
		t_trigger_on_stun = trigger_on_stun;
		t_trigger_on_stun_chance = trigger_on_stun_chance;
	}
	else
	{
		t_trigger_on_stun = trigger_on_stun_victim;
		t_trigger_on_stun_chance = trigger_on_stun_chance_victim;
	}

	if( t_trigger_on_stun )
	{
		if( t_trigger_on_stun_chance < 100 && !Rand( t_trigger_on_stun_chance ) )
			return;

		SpellEntry *spellInfo = dbcSpell.LookupEntry(t_trigger_on_stun);

		if(!spellInfo)
			return;

		Spell *spell = SpellPool.PooledNew();
		if (!spell)
			return;
		spell->Init(this, spellInfo ,true, NULL);
		SpellCastTargets targets;

		if ( spellInfo->procFlags & PROC_TARGET_SELF )
			targets.m_unitTarget = GetGUID();
		else if ( proc_target )
			targets.m_unitTarget = proc_target->GetGUID();
		else
			targets.m_unitTarget = GetGUID();
		spell->prepare(&targets);
	}
}

// Proc on chill effects (such as frostbolt slow effect)
void Unit::EventChill(Unit *proc_target, bool is_victim)
{
	if ( this == proc_target )
		return; //how and why would we chill ourselves

	int32 t_trigger_on_chill,t_trigger_on_chill_chance;
	if( is_victim == false )
	{
		t_trigger_on_chill = trigger_on_chill;
		t_trigger_on_chill_chance = trigger_on_chill_chance;
	}
	else
	{
		t_trigger_on_chill = trigger_on_chill_victim;
		t_trigger_on_chill_chance = trigger_on_chill_chance_victim;
	}

	if( t_trigger_on_chill )
	{
		if( t_trigger_on_chill_chance < 100 && !Rand( t_trigger_on_chill_chance ) )
			return;

		SpellEntry *spellInfo = dbcSpell.LookupEntry(t_trigger_on_chill);

		if(!spellInfo)
			return;

		Spell *spell = SpellPool.PooledNew();
		if (!spell)
			return;
		spell->Init(this, spellInfo ,true, NULL);
		SpellCastTargets targets;

		if ( spellInfo->procFlags & PROC_TARGET_SELF )
			targets.m_unitTarget = GetGUID();
		else if ( proc_target )
			targets.m_unitTarget = proc_target->GetGUID();
		else
			targets.m_unitTarget = GetGUID();
		spell->prepare(&targets);
	}
}

void Unit::RemoveExtraStrikeTarget(SpellEntry *spell_info)
{
	for(std::list<ExtraStrike*>::iterator i = m_extraStrikeTargets.begin();i != m_extraStrikeTargets.end();i++)
	{
		if((*i)->deleted == false && spell_info == (*i)->spell_info)
		{
			m_extrastriketargetc--;
			(*i)->deleted = true;
		}
	}
}

void Unit::AddExtraStrikeTarget(SpellEntry *spell_info, uint32 charges)
{
	for(std::list<ExtraStrike*>::iterator i = m_extraStrikeTargets.begin();i != m_extraStrikeTargets.end();i++)
	{
		//a pointer check or id check ...should be the same
		if(spell_info == (*i)->spell_info)
		{
			if ((*i)->deleted == true)
			{
				(*i)->deleted = false;
				m_extrastriketargetc++;
			}
			(*i)->charges = charges;
			return;
		}
	}

	ExtraStrike *es = new ExtraStrike;

	es->spell_info = spell_info;
	es->charges = charges;
	es->deleted = false;
	m_extraStrikeTargets.push_back(es);
	m_extrastriketargetc++;
}

uint32 Unit::DoDamageSplitTarget(uint32 res, uint32 school_type, bool melee_dmg)
{
	Unit * splittarget;
	uint32 splitdamage, tmpsplit;
	DamageSplitTarget * ds = m_damageSplitTarget;

	splittarget = (GetMapMgr() != NULL) ? GetMapMgr()->GetUnit( ds->m_target ) : NULL;
	if( splittarget != NULL && res > 0 ) {
		// calculate damage
		tmpsplit = ds->m_flatDamageSplit;
		if( tmpsplit > res)
			tmpsplit = res; // prevent < 0 damage
		splitdamage = tmpsplit;
		res -= tmpsplit;
		tmpsplit = float2int32( ds->m_pctDamageSplit * res );
		if( tmpsplit > res )
			tmpsplit = res;
		splitdamage += tmpsplit;
		res -= tmpsplit;

		if( splitdamage ) {
			splittarget->DealDamage(splittarget, splitdamage, 0, 0, 0);

			// Send damage log
			if (melee_dmg) {
				dealdamage sdmg;

				sdmg.full_damage = splitdamage;
				sdmg.resisted_damage = 0;
				sdmg.school_type = school_type;
				SendAttackerStateUpdate(this, splittarget, &sdmg, splitdamage, 0, 0, 0, ATTACK);
			} else {
				SendSpellNonMeleeDamageLog(this, splittarget, ds->m_spellId, splitdamage, static_cast<uint8>( school_type ), 0, 0, true, 0, 0, true);
			}
		}
	}

	return res;
}

void Unit::RemoveReflect( uint32 spellid, bool apply )
{
	/** 
	* Removes and deletes reflects from unit by spell id, does not remove aura which created it
	* In specific cases reflects can be created by a dummy spelleffect (eg. spell 28332 or 13043), then we need to remove it in ~unit
	*/
	for( std::list<struct ReflectSpellSchool*>::iterator i = m_reflectSpellSchool.begin(); i != m_reflectSpellSchool.end(); )
		if( spellid == (*i)->spellId )
		{
			delete *i;
			i = m_reflectSpellSchool.erase( i );
			//break; better check all list elements
		}
		else
			++i;

	if( apply && spellid == 23920 && IsPlayer() && HasAurasWithNameHash(SPELL_HASH_IMPROVED_SPELL_REFLECTION) )
	{
		Player *pPlayer = static_cast<Player*>(this);
		if( !pPlayer )
			return;

		Group * pGroup = pPlayer->GetGroup();

		if(pGroup != NULL)
		{
			int32 targets = 0;
			if( pPlayer->HasAura(59088) )
				targets = 2;
			else if( pPlayer->HasAura(59089) )
				targets = 4;

			pGroup->Lock();
			for(uint32 i = 0; i < pGroup->GetSubGroupCount(); ++i)
			{
				for(GroupMembersSet::iterator itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
				{
					Player * member = (*itr)->m_loggedInPlayer;
                    if( member == NULL || member == pPlayer || !member->IsInWorld() || !member->isAlive() || member->HasAura(59725) )
                         continue;
 
                    if( !IsInrange(pPlayer, member, 20) )
                        continue;
                    pPlayer->CastSpell( member, 59725, true );
                     targets -= 1;
				}
			}
			pGroup->Unlock();
		}
	}

	if( !apply && spellid == 59725 && IsPlayer() )
     {
		 Player *pPlayer = static_cast<Player*>(this);
		if( !pPlayer )
			return;

		Group * pGroup = pPlayer->GetGroup();
		if(pGroup != NULL)
		{
			pGroup->Lock();
			for(uint32 i = 0; i < pGroup->GetSubGroupCount(); ++i)
			{
				for(GroupMembersSet::iterator itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
				{
					if((*itr)->m_loggedInPlayer == NULL)
						continue;

					if( (*itr)->m_loggedInPlayer->HasAura(59725) )
						(*itr)->m_loggedInPlayer->RemoveAura(59725);
				}
			}
			pGroup->Unlock();
		}
	}
}

void Unit::SetPower(uint32 type, int32 value)
{
	uint32 maxpower = GetUInt32Value(UNIT_FIELD_MAXPOWER1 + type);
	if(value < 0)
		value = 0;
	else if(value > (int32)maxpower)
		value = maxpower;
	SetUInt32Value(UNIT_FIELD_POWER1 + type, value);
}

void Unit::SendPowerUpdate(bool self)
{
	uint32 amount = GetUInt32Value(UNIT_FIELD_POWER1 + GetPowerType()); //save the amount, so we send the same to the player and everyone else

	WorldPacket data( SMSG_POWER_UPDATE, 14 );
	FastGUIDPack( data, GetGUID() );
	data << (uint8)GetPowerType();
	data << amount;
//	This was added in revision 1726.  Is it necessary?  To me, it seems to just be sending the packet twice.
//	If it is needed for something, put it back in I guess.
//	CopyAndSendDelayedPacket(&data);
	SendMessageToSet( &data, self );

	//VLack: On 3.1.3, create and send a field update packet to everyone else, as this is the only way to update their GUI with the power values.
	WorldPacket * pkt=BuildFieldUpdatePacket(UNIT_FIELD_POWER1 + GetPowerType(), amount);
	SendMessageToSet(pkt, false);
	delete pkt;
}

void Unit::UpdatePowerAmm()
{
	if( !IsPlayer() )
		return;
	WorldPacket data( SMSG_POWER_UPDATE, 14 );
	FastGUIDPack( data, GetGUID() );
	data << uint8( GetPowerType() );
	data << GetUInt32Value( UNIT_FIELD_POWER1 + GetPowerType() );
	SendMessageToSet( &data, true );
}

void Unit::CastSpellOnCasterOnCritHit()
{
	if( HasAura( 54646 ) )
	{
		SpellEntry *spellInfo = dbcSpell.LookupEntry( 54646 );
		if(!spellInfo)
			return;

		Spell *spell = SpellPool.PooledNew();
		if (!spell)
			return;

		Unit *uCaster = NULL;
		if( spell->u_caster )
			uCaster = spell->u_caster;

		if( uCaster )
				uCaster->CastSpell( uCaster, 54648, true );
	}
}

void Unit::LiberationSceauPaladin(uint32 SealID, Unit * Target)
{
	if(!SealID) return;
	if(!Target) return;
	SpellEntry *SealEntry = dbcSpell.LookupEntry( SealID );
	if(!SealEntry) return;

	uint32 dmg = 0;
	switch(SealEntry->NameHash)
	{
	case SPELL_HASH_SEAL_OF_BLOOD:
		{
			uint32 mw = float2int32(GetFloatValue(UNIT_FIELD_MINDAMAGE));
			uint32 MW = float2int32(GetFloatValue(UNIT_FIELD_MAXDAMAGE));
			uint32 SP = GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 1);

			dmg = 0.11*GetAP() + 0.18*SP;
			dmg += 0.26*(MW - mw);

			uint32 dmgLimit = dmg*33/100;

			DealDamage(Target, dmg, 0, 0, SealID);
			ModUnsigned32Value(UNIT_FIELD_HEALTH, -dmgLimit);
		}break;
	case SPELL_HASH_SEAL_OF_CORRUPTION:
		{
			uint32 Stack = 0;
			uint32 SP = GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 1);

			dmg = 1+0.22*SP+0.14*GetAP();

			if(HasAura(53742))
				Stack = 1;

			dmg += dmg*Stack*0.1;
			DealDamage(Target, dmg, 0, 0, SealID);
		}break;
	case SPELL_HASH_SEAL_OF_JUSTICE:
		{
			uint32 SP = GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 1);
			dmg = 1+0.25*SP+0.16*GetAP();
			DealDamage(Target, dmg, 0, 0, SealID);
		}break;
	case SPELL_HASH_SEAL_OF_LIGHT:
		{
			uint32 SP = GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 1);
			dmg = 1+0.25*SP+0.16*GetAP();
			DealDamage(Target, dmg, 0, 0, SealID);
		}break;
	case SPELL_HASH_SEAL_OF_RIGHTEOUSNESS:
		{
			uint32 SP = GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 1);
			dmg = 1+0.2*GetAP()+0.32*SP;
			DealDamage(Target, dmg, 0, 0, SealID);
		}break;
	case SPELL_HASH_SEAL_OF_THE_MARTYR:
		{
			uint32 mw = float2int32(GetFloatValue(UNIT_FIELD_MINDAMAGE));
			uint32 MW = float2int32(GetFloatValue(UNIT_FIELD_MAXDAMAGE));
			uint32 SP = GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 1);

			dmg = 0.11*GetAP() + 0.18*SP;
			dmg += 0.26*(MW - mw);

			uint32 dmgLimit = dmg*33/100;

			DealDamage(Target, dmg, 0, 0, SealID);
			ModUnsigned32Value(UNIT_FIELD_HEALTH, -dmgLimit);
		}break;
	case SPELL_HASH_SEAL_OF_VENGEANCE:
		{
			uint32 Stack = 0;
			uint32 SP = GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 1);

			dmg = 1+0.22*SP+0.14*GetAP();

			if(HasAura(31803))
				Stack = 1;

			dmg += dmg*Stack*0.1;
			DealDamage(Target, dmg, 0, 0, SealID);
		}break;
	case SPELL_HASH_SEAL_OF_WISDOM:
		{
			uint32 SP = GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 1);
			dmg = 1+0.16*GetAP()+0.25*SP;
			DealDamage(Target, dmg, 0, 0, SealID);
		}break;
	case SPELL_HASH_SEAL_OF_COMMAND:
		{
			uint32 mw = float2int32(GetFloatValue(UNIT_FIELD_MINDAMAGE));
			uint32 MW = float2int32(GetFloatValue(UNIT_FIELD_MAXDAMAGE));
			uint32 SP = GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 1);

			dmg = 0.16*GetAP() + 0.25*SP;
			dmg += 0.24*(MW - mw);

			if(Target->IsStunned())
				dmg *= 2;

			DealDamage(Target, dmg, 0, 0, SealID);
		}break;
	}
}

Unit * Unit::CreateTemporaryInfernal(uint32 guardian_entry,uint32 duration,float angle, uint32 lvl, float x, float y, float z)
{
	CreatureProto * proto = CreatureProtoStorage.LookupEntry(guardian_entry);
	CreatureInfo * info = CreatureNameStorage.LookupEntry(guardian_entry);
	if(!proto || !info)
	{
		return NULL;
	}
	float m_fallowAngle=angle;
	Creature * p = GetMapMgr()->CreateCreature(guardian_entry);
	p->SetInstanceID(GetMapMgr()->GetInstanceID());
	p->Load(proto, x, y, z, 0.0f);

	if(static_cast<Player*>(this)->GetSummon() != 0)
	{
		Pet * old = static_cast<Player*>(this)->GetSummon();
		if(old)
			old->Dismiss();
	}
	if(static_cast<Player*>(this)->GetUInt64Value(UNIT_FIELD_CHARM))
	{
		Unit * _unit = static_cast<Player*>(this)->GetMapMgr()->GetUnit( static_cast<Player*>(this)->GetUInt64Value( UNIT_FIELD_CHARM ) );
		TO_CREATURE(_unit)->ExpireInferno(static_cast<Player*>(this));
	}
	TO_UNIT(p)->m_special_state |= UNIT_STATE_CHARM;
	TO_UNIT(p)->SetCharmTempVal( TO_UNIT(p)->GetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE ) );
	TO_UNIT(p)->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, static_cast<Player*>(this)->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
	TO_UNIT(p)->_setFaction();
	TO_UNIT(p)->UpdateOppFactionSet();
	TO_UNIT(p)->GetAIInterface()->Init(TO_UNIT(p), AITYPE_PET, MOVEMENTTYPE_NONE, static_cast<Player*>(this));
	TO_UNIT(p)->SetUInt64Value(UNIT_FIELD_CHARMEDBY, static_cast<Player*>(this)->GetGUID());
	static_cast<Player*>(this)->SetUInt64Value(UNIT_FIELD_CHARM, TO_UNIT(p)->GetGUID());
	//damn it, the other effects of enslaive demon will agro him on us anyway :S
	TO_UNIT(p)->GetAIInterface()->WipeHateList();
	TO_UNIT(p)->GetAIInterface()->WipeTargetList();
	TO_UNIT(p)->GetAIInterface()->SetNextTarget((Unit*)NULL);
	p->SetEnslaveCount(p->GetEnslaveCount() + 1);
	TO_UNIT(p)->GetAIInterface()->SetUnitToFollow(static_cast<Player*>(this));
	TO_UNIT(p)->GetAIInterface()->SetUnitToFollowAngle(3.14f);
	TO_UNIT(p)->GetAIInterface()->SetFollowDistance(3.0f);
	//plr_shared_from_this()->SetSummon( TO_PET(p) );
	if( static_cast<Player*>(this)->GetSession() ) // crashfix
	{
		WorldPacket data(SMSG_PET_SPELLS, 500);
		data << p->GetGUID();
		data << uint32(0x00000000) << uint32(0x00000101) << uint16(0x00000000);
		data << uint32(PET_SPELL_ATTACK);
		data << uint32(PET_SPELL_FOLLOW);
		data << uint32(PET_SPELL_STAY);
		for(int i = 0; i < 4; i++)
			data << uint32(0);
		data << uint32(PET_SPELL_AGRESSIVE);
		data << uint32(PET_SPELL_DEFENSIVE);
		data << uint32(PET_SPELL_PASSIVE);
		data << uint8(0);
		data << uint8(0);
		static_cast<Player*>(this)->GetSession()->SendPacket(&data);
		p->SetEnslaveSpell(1122);
	}
	p->PushToWorld(GetMapMgr());

	//<Player*>(this)->CastSpell(p, 61191, true);
	//p->CastSpell(p, 22703, true);

	sEventMgr.AddEvent(p, &Creature::ExpireInferno, static_cast<Player*>(this), EVENT_SUMMON_EXPIRE, duration, 1,0);
	return p;
	
}

void Unit::DealDamageWithPenance(uint32 spellId, uint32 amount)
{
	DealDamage(this, amount, 0, 0, spellId);
}

void Unit::StopChannel()
{
	SetUInt32Value(UNIT_FIELD_CHANNEL_OBJECT, 0);
	SetUInt32Value(UNIT_CHANNEL_SPELL, 0);
}