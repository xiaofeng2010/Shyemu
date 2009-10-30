/*
* shyemu MMORPG Server
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

pSpellEffect SpellEffectsHandler[TOTAL_SPELL_EFFECTS]={
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_NULL - 0
	&Spell::SpellEffectInstantKill,				//SPELL_EFFECT_INSTAKILL - 1
	&Spell::SpellEffectSchoolDMG,				//SPELL_EFFECT_SCHOOL_DAMAGE - 2
	&Spell::SpellEffectDummy,					//SPELL_EFFECT_DUMMY - 3
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_PORTAL_TELEPORT - 4
	&Spell::SpellEffectTeleportUnits,			//SPELL_EFFECT_TELEPORT_UNITS - 5
	&Spell::SpellEffectApplyAura,				//SPELL_EFFECT_APPLY_AURA - 6
	&Spell::SpellEffectEnvironmentalDamage,		//SPELL_EFFECT_ENVIRONMENTAL_DAMAGE - 7
	&Spell::SpellEffectPowerDrain,				//SPELL_EFFECT_POWER_DRAIN - 8
	&Spell::SpellEffectHealthLeech,				//SPELL_EFFECT_HEALTH_LEECH - 9
	&Spell::SpellEffectHeal,					//SPELL_EFFECT_HEAL - 10
	&Spell::SpellEffectBind,					//SPELL_EFFECT_BIND - 11
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_PORTAL - 12
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_RITUAL_BASE - 13
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_RITUAL_SPECIALIZE - 14
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL - 15
	&Spell::SpellEffectQuestComplete,			//SPELL_EFFECT_QUEST_COMPLETE - 16
	&Spell::SpellEffectWeapondamageNoschool,	//SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL - 17
	&Spell::SpellEffectResurrect,				//SPELL_EFFECT_RESURRECT - 18
	&Spell::SpellEffectAddExtraAttacks,			//SPELL_EFFECT_ADD_EXTRA_ATTACKS - 19
	&Spell::SpellEffectDodge,					//SPELL_EFFECT_DODGE - 20
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_EVADE - 21
	&Spell::SpellEffectParry,					//SPELL_EFFECT_PARRY - 22
	&Spell::SpellEffectBlock,					//SPELL_EFFECT_BLOCK - 23
	&Spell::SpellEffectCreateItem,				//SPELL_EFFECT_CREATE_ITEM - 24
	&Spell::SpellEffectWeapon,					//SPELL_EFFECT_WEAPON - 25
	&Spell::SpellEffectDefense,					//SPELL_EFFECT_DEFENSE - 26
	&Spell::SpellEffectPersistentAA,			//SPELL_EFFECT_PERSISTENT_AREA_AURA - 27
	&Spell::SpellEffectSummon,					//SPELL_EFFECT_SUMMON - 28
	&Spell::SpellEffectLeap,					//SPELL_EFFECT_LEAP - 29
	&Spell::SpellEffectEnergize,				//SPELL_EFFECT_ENERGIZE - 30
	&Spell::SpellEffectWeaponDmgPerc,			//SPELL_EFFECT_WEAPON_PERCENT_DAMAGE - 31
	&Spell::SpellEffectTriggerMissile,			//SPELL_EFFECT_TRIGGER_MISSILE - 32
	&Spell::SpellEffectOpenLock,				//SPELL_EFFECT_OPEN_LOCK - 33
	&Spell::SpellEffectTransformItem,			//SPELL_EFFECT_TRANSFORM_ITEM - 34
	&Spell::SpellEffectApplyAA,					//SPELL_EFFECT_APPLY_AREA_AURA - 35
	&Spell::SpellEffectLearnSpell,				//SPELL_EFFECT_LEARN_SPELL - 36
	&Spell::SpellEffectSpellDefense,			//SPELL_EFFECT_SPELL_DEFENSE - 37
	&Spell::SpellEffectDispel,					//SPELL_EFFECT_DISPEL - 38
	&Spell::SpellEffectLanguage,				//SPELL_EFFECT_LANGUAGE - 39
	&Spell::SpellEffectDualWield,				//SPELL_EFFECT_DUAL_WIELD - 40
	&Spell::SpellEffectSummonWild,				//SPELL_EFFECT_SUMMON_WILD - 41
	&Spell::SpellEffectSummonGuardian,			//SPELL_EFFECT_SUMMON_GUARDIAN - 42
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER - 43
	&Spell::SpellEffectSkillStep,				//SPELL_EFFECT_SKILL_STEP - 44
	&Spell::SpellEffectAddHonor,				//SPELL_ADD_HONOR - 45
	&Spell::SpellEffectSpawn,					//SPELL_EFFECT_SPAWN - 46
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_TRADE_SKILL - 47
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_STEALTH - 48
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_DETECT - 49
	&Spell::SpellEffectSummonObject,			//SPELL_EFFECT_SUMMON_OBJECT - 50
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_FORCE_CRITICAL_HIT - 51 NA
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_GUARANTEE_HIT - 52 NA
	&Spell::SpellEffectEnchantItem,				//SPELL_EFFECT_ENCHANT_ITEM - 53
	&Spell::SpellEffectEnchantItemTemporary,	//SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY - 54
	&Spell::SpellEffectTameCreature,			//SPELL_EFFECT_TAMECREATURE - 55
	&Spell::SpellEffectSummonPet,				//SPELL_EFFECT_SUMMON_PET	- 56
	&Spell::SpellEffectLearnPetSpell,			//SPELL_EFFECT_LEARN_PET_SPELL - 57
	&Spell::SpellEffectWeapondamage,			//SPELL_EFFECT_WEAPON_DAMAGE - 58
	&Spell::SpellEffectOpenLockItem,			//SPELL_EFFECT_OPEN_LOCK_ITEM - 59
	&Spell::SpellEffectProficiency,				//SPELL_EFFECT_PROFICIENCY - 60
	&Spell::SpellEffectSendEvent,				//SPELL_EFFECT_SEND_EVENT - 61
	&Spell::SpellEffectPowerBurn,				//SPELL_EFFECT_POWER_BURN - 62
	&Spell::SpellEffectThreat,					//SPELL_EFFECT_THREAT - 63
	&Spell::SpellEffectTriggerSpell,			//SPELL_EFFECT_TRIGGER_SPELL - 64
	&Spell::SpellEffectApplyAA,					//SPELL_EFFECT_APPLY_AREA_AURA2 - 65
	&Spell::SpellEffectPowerFunnel,				//SPELL_EFFECT_POWER_FUNNEL - 66
	&Spell::SpellEffectHealMaxHealth,			//SPELL_EFFECT_HEAL_MAX_HEALTH - 67
	&Spell::SpellEffectInterruptCast,			//SPELL_EFFECT_INTERRUPT_CAST - 68
	&Spell::SpellEffectDistract,				//SPELL_EFFECT_DISTRACT - 69
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_PULL - 70
	&Spell::SpellEffectPickpocket,				//SPELL_EFFECT_PICKPOCKET - 71
	&Spell::SpellEffectAddFarsight,				//SPELL_EFFECT_ADD_FARSIGHT - 72
	&Spell::SpellEffectSummonPossessed,			//SPELL_EFFECT_SUMMON_POSSESSED - 73
	&Spell::SpellEffectUseGlyph,				//SPELL_EFFECT_USE_GLYPH - 74
	&Spell::SpellEffectHealMechanical,			//SPELL_EFFECT_HEAL_MECHANICAL - 75
	&Spell::SpellEffectSummonObjectWild,		//SPELL_EFFECT_SUMMON_OBJECT_WILD - 76
	&Spell::SpellEffectScriptEffect,			//SPELL_EFFECT_SCRIPT_EFFECT - 77
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_ATTACK - 78
	&Spell::SpellEffectSanctuary,				//SPELL_EFFECT_SANCTUARY - 79
	&Spell::SpellEffectAddComboPoints,			//SPELL_EFFECT_ADD_COMBO_POINTS - 80
	&Spell::SpellEffectCreateHouse,				//SPELL_EFFECT_CREATE_HOUSE - 81
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_BIND_SIGHT - 82
	&Spell::SpellEffectDuel,					//SPELL_EFFECT_DUEL - 83
	&Spell::SpellEffectStuck,					//SPELL_EFFECT_STUCK - 84
	&Spell::SpellEffectSummonPlayer,			//SPELL_EFFECT_SUMMON_PLAYER - 85
	&Spell::SpellEffectActivateObject,			//SPELL_EFFECT_ACTIVATE_OBJECT - 86
	&Spell::SpellEffectSummonTotem,				//SPELL_EFFECT_SUMMON_TOTEM_SLOT1 - 87
	&Spell::SpellEffectSummonTotem,				//SPELL_EFFECT_SUMMON_TOTEM_SLOT2 - 88
	&Spell::SpellEffectSummonTotem,				//SPELL_EFFECT_SUMMON_TOTEM_SLOT3 - 89
	&Spell::SpellEffectSummonTotem,				//SPELL_EFFECT_SUMMON_TOTEM_SLOT4 - 90
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_THREAT_ALL - 91 UNUSED
	&Spell::SpellEffectEnchantHeldItem,			//SPELL_EFFECT_ENCHANT_HELD_ITEM - 92
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_SUMMON_PHANTASM - 93 OLD
	&Spell::SpellEffectSelfResurrect,			//SPELL_EFFECT_SELF_RESURRECT - 94
	&Spell::SpellEffectSkinning,				//SPELL_EFFECT_SKINNING - 95
	&Spell::SpellEffectCharge,					//SPELL_EFFECT_CHARGE - 96
	&Spell::SpellEffectSummonCritter,			//SPELL_EFFECT_SUMMON_CRITTER - 97
	&Spell::SpellEffectKnockBack,				//SPELL_EFFECT_KNOCK_BACK - 98
	&Spell::SpellEffectDisenchant,				//SPELL_EFFECT_DISENCHANT - 99
	&Spell::SpellEffectInebriate,				//SPELL_EFFECT_INEBRIATE - 100
	&Spell::SpellEffectFeedPet,					//SPELL_EFFECT_FEED_PET - 101
	&Spell::SpellEffectDismissPet,				//SPELL_EFFECT_DISMISS_PET - 102
	&Spell::SpellEffectReputation,				//SPELL_EFFECT_REPUTATION - 103
	&Spell::SpellEffectSummonObjectSlot,		//SPELL_EFFECT_SUMMON_OBJECT_SLOT1 - 104
	&Spell::SpellEffectSummonObjectSlot,		//SPELL_EFFECT_SUMMON_OBJECT_SLOT2 - 105
	&Spell::SpellEffectSummonObjectSlot,		//SPELL_EFFECT_SUMMON_OBJECT_SLOT3 - 106
	&Spell::SpellEffectSummonObjectSlot,		//SPELL_EFFECT_SUMMON_OBJECT_SLOT4 - 107
	&Spell::SpellEffectDispelMechanic,			//SPELL_EFFECT_DISPEL_MECHANIC - 108
	&Spell::SpellEffectSummonDeadPet,			//SPELL_EFFECT_SUMMON_DEAD_PET - 109
	&Spell::SpellEffectDestroyAllTotems,		//SPELL_EFFECT_DESTROY_ALL_TOTEMS - 110
	&Spell::SpellEffectDurabilityDamage,		//SPELL_EFFECT_DURABILITY_DAMAGE - 111
	&Spell::SpellEffectSummonDemon,				//SPELL_EFFECT_SUMMON_DEMON - 112
	&Spell::SpellEffectResurrectNew,			//SPELL_EFFECT_RESURRECT_NEW - 113
	&Spell::SpellEffectAttackMe,				//SPELL_EFFECT_ATTACK_ME - 114
	&Spell::SpellEffectDurabilityDamagePCT,		//SPELL_EFFECT_DURABILITY_DAMAGE_PCT - 115
	&Spell::SpellEffectSkinPlayerCorpse,		//SPELL_EFFECT_SKIN_PLAYER_CORPSE - 116
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_SPIRIT_HEAL - 117//Not used
	&Spell::SpellEffectSkill,					//SPELL_EFFECT_SKILL - 118
	&Spell::SpellEffectApplyPetAura,			//SPELL_EFFECT_APPLY_PET_AURA - 119
	&Spell::SpellEffectNULL,					//SPELL_EFFECT_TELEPORT_GRAVEYARD - 120//Not used
	&Spell::SpellEffectDummyMelee,				//SPELL_EFFECT_DUMMYMELEE	- 121
	&Spell::SpellEffectNULL,					// unknown - 122 //not used
	&Spell::SpellEffectFilming,					//SPELL_EFFECT_FILMING - 123 // http://www.thottbot.com/?sp=27998: flightpath
	&Spell::SpellEffectPlayerPull,				//SPELL_EFFECT_PLAYER_PULL - 124 - http://thottbot.com/e2312
	&Spell::SpellEffectReduceThreatPercent,		//SPELL_EFFECT_REDUCE_THREAT_PERCENT - 125 // Reduce Threat by % //http://www.thottbot.com/?sp=32835
	&Spell::SpellEffectSpellSteal,				//SPELL_EFFECT_SPELL_STEAL - 126 // Steal Beneficial Buff (Magic) //http://www.thottbot.com/?sp=30449
	&Spell::SpellEffectProspecting,				// unknown - 127 // Search 5 ore of a base metal for precious gems.  This will destroy the ore in the process.
	&Spell::SpellEffectApplyAura128,			// unknown - 128 // Adjust a stats by %: Mod Stat // ITS FLAT
	&Spell::SpellEffectNULL,					// unknown - 129 // Mod Dmg % (Spells)
	&Spell::SpellEffectRedirectThreat,			// unknown - 130 // http://www.thottbot.com/s34477
	&Spell::SpellEffectNULL,					// unknown - 131 // test spell
	&Spell::SpellEffectNULL,					// unknown - 132 // no spells
	&Spell::SpellEffectForgetSpecialization,	//SPELL_EFFECT_FORGET_SPECIALIZATION - 133 // http://www.thottbot.com/s36441 // I think this is a gm/npc spell
	&Spell::SpellEffectNULL,					// unknown - 134 // related to summoning objects and removing them, http://www.thottbot.com/s39161
	&Spell::SpellEffectNULL,					// unknown - 135 // no spells
	&Spell::SpellEffectNULL,					// unknown - 136 // http://www.thottbot.com/s41542 and http://www.thottbot.com/s39703
	&Spell::SpellEffectRestorePowerPct,			// Restore Power % - 137 // http://www.thottbot.com/s41542
	&Spell::SpellEffectNULL,					// unknown - 138 // related to superjump or even "*jump" spells http://www.thottbot.com/?e=Unknown%20138
	&Spell::SpellEffectNULL,					// unknown - 139 // no spells
	&Spell::SpellEffectTriggerSpell,			// triggers a spell from target back to caster - used at Malacrass f.e.
	&Spell::SpellEffectNULL,					// unknown - 141 // triggers spell, magic one,  (Mother spell) http://www.thottbot.com/s41065
	&Spell::SpellEffectTriggerSpellWithValue,	//SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE - 142 // triggers some kind of "Put spell on target" thing... (dono for sure) http://www.thottbot.com/s40872 and http://www.thottbot.com/s33076
	&Spell::SpellEffectNULL,					// unknown - 143 // Master -> demon effecting spell, http://www.thottbot.com/s25228 and http://www.thottbot.com/s35696
	&Spell::SpellEffectNULL,// unknown - 144
	&Spell::SpellEffectNULL,// unknown - 145
	&Spell::SpellEffectConvertInDeathRunes,// DrainSanglant
	&Spell::SpellEffectNULL,// Quest Fail - 147
	&Spell::SpellEffectNULL,// unknown - 148
	&Spell::SpellEffectNULL,// unknown - 149
	&Spell::SpellEffectNULL,// unknown - 150
	&Spell::SpellEffectTriggerSpell,// SPELL_EFFECT_TRIGGER_SPELL_2 - 151
	&Spell::SpellEffectNULL,// Summon Refer-a-Friend - 152
	&Spell::SpellEffectCreatePet,// Create tamed pet - 153
	&Spell::SpellEffectTeachTaxiPath,// "Teach" a taxi path - 154
	&Spell::SpellEffectDualWield2H,// DualWield2H (ex: Titan's Grip) - 155
	&Spell::SpellEffectEnchantItemPrismatic,// Add a socket to an armor/a weapon - 156
	&Spell::SpellEffectCreateItem2,	//157
	&Spell::SpellEffectMilling,// Milling - 158
	&Spell::SpellEffectRenamePet,// Allow pet rename - 159
	&Spell::SpellEffectNULL, //160
	&Spell::SpellEffectSetTalentSpecsCount, //161 Sets number of talent specs available to the player
	&Spell::SpellEffectActivateTalentSpec, //162 Activates one of talent specs
};

const char* SpellEffectNames[TOTAL_SPELL_EFFECTS] = {
	"INSTANT_KILL",              //    1
	"SCHOOL_DAMAGE",             //    2
	"DUMMY",                     //    3
	"PORTAL_TELEPORT",           //    4
	"TELEPORT_UNITS",            //    5
	"APPLY_AURA",                //    6
	"ENVIRONMENTAL_DAMAGE",      //    7
	"POWER_DRAIN",               //    8
	"HEALTH_LEECH",              //    9
	"HEAL",                      //    10
	"BIND",                      //    11
	"PORTAL",                    //    12
	"RITUAL_BASE",               //    13
	"RITUAL_SPECIALIZE",         //    14
	"RITUAL_ACTIVATE_PORTAL",    //    15
	"QUEST_COMPLETE",            //    16
	"WEAPON_DAMAGE_NOSCHOOL",    //    17
	"RESURRECT",                 //    18
	"ADD_EXTRA_ATTACKS",         //    19
	"DODGE",                     //    20
	"EVADE",                     //    21
	"PARRY",                     //    22
	"BLOCK",                     //    23
	"CREATE_ITEM",               //    24
	"WEAPON",                    //    25
	"DEFENSE",                   //    26
	"PERSISTENT_AREA_AURA",      //    27
	"SUMMON",                    //    28
	"LEAP",                      //    29
	"ENERGIZE",                  //    30
	"WEAPON_PERCENT_DAMAGE",     //    31
	"TRIGGER_MISSILE",           //    32
	"OPEN_LOCK",                 //    33
	"TRANSFORM_ITEM",            //    34
	"APPLY_AREA_AURA",           //    35
	"LEARN_SPELL",               //    36
	"SPELL_DEFENSE",             //    37
	"DISPEL",                    //    38
	"LANGUAGE",                  //    39
	"DUAL_WIELD",                //    40
	"SUMMON_WILD",               //    41
	"SUMMON_GUARDIAN",           //    42
	"TELEPORT_UNITS_FACE_CASTER",//    43
	"SKILL_STEP",                //    44
	"UNDEFINED_45",              //    45
	"SPAWN",                     //    46
	"TRADE_SKILL",               //    47
	"STEALTH",                   //    48
	"DETECT",                    //    49
	"SUMMON_OBJECT",             //    50
	"FORCE_CRITICAL_HIT",        //    51
	"GUARANTEE_HIT",             //    52
	"ENCHANT_ITEM",              //    53
	"ENCHANT_ITEM_TEMPORARY",    //    54
	"TAMECREATURE",              //    55
	"SUMMON_PET",                //    56
	"LEARN_PET_SPELL",           //    57
	"WEAPON_DAMAGE",             //    58
	"OPEN_LOCK_ITEM",            //    59
	"PROFICIENCY",               //    60
	"SEND_EVENT",                //    61
	"POWER_BURN",                //    62
	"THREAT",                    //    63
	"TRIGGER_SPELL",             //    64
	"HEALTH_FUNNEL",             //    65
	"POWER_FUNNEL",              //    66
	"HEAL_MAX_HEALTH",           //    67
	"INTERRUPT_CAST",            //    68
	"DISTRACT",                  //    69
	"PULL",                      //    70
	"PICKPOCKET",                //    71
	"ADD_FARSIGHT",              //    72
	"SUMMON_POSSESSED",          //    73
	"SUMMON_TOTEM",              //    74
	"HEAL_MECHANICAL",           //    75
	"SUMMON_OBJECT_WILD",        //    76
	"SCRIPT_EFFECT",             //    77
	"ATTACK",                    //    78
	"SANCTUARY",                 //    79
	"ADD_COMBO_POINTS",          //    80
	"CREATE_HOUSE",              //    81
	"BIND_SIGHT",                //    82
	"DUEL",                      //    83
	"STUCK",                     //    84
	"SUMMON_PLAYER",             //    85
	"ACTIVATE_OBJECT",           //    86
	"SUMMON_TOTEM_SLOT1",        //    87
	"SUMMON_TOTEM_SLOT2",        //    88
	"SUMMON_TOTEM_SLOT3",        //    89
	"SUMMON_TOTEM_SLOT4",        //    90
	"THREAT_ALL",                //    91
	"ENCHANT_HELD_ITEM",         //    92
	"SUMMON_PHANTASM",           //    93
	"SELF_RESURRECT",            //    94
	"SKINNING",                  //    95
	"CHARGE",                    //    96
	"SUMMON_CRITTER",            //    97
	"KNOCK_BACK",                //    98
	"DISENCHANT",                //    99
	"INEBRIATE",                 //    100
	"FEED_PET",                  //    101
	"DISMISS_PET",               //    102
	"REPUTATION",                //    103
	"SUMMON_OBJECT_SLOT1",       //    104
	"SUMMON_OBJECT_SLOT2",       //    105
	"SUMMON_OBJECT_SLOT3",       //    106
	"SUMMON_OBJECT_SLOT4",       //    107
	"DISPEL_MECHANIC",           //    108
	"SUMMON_DEAD_PET",           //    109
	"DESTROY_ALL_TOTEMS",        //    110
	"DURABILITY_DAMAGE",         //    111
	"SUMMON_DEMON",              //    112
	"RESURRECT_FLAT",            //    113
	"ATTACK_ME",                 //    114
	"DURABILITY_DAMAGE_PCT",     //    115
	"SKIN_PLAYER_CORPSE",        //    116
	"SPIRIT_HEAL",               //    117
	"SKILL",                     //    118
	"APPLY_PET_AURA",            //    119
	"TELEPORT_GRAVEYARD",        //    120
	"DUMMYMELEE",                //    121
	"UNKNOWN1",                  //    122
	"FILMING",                   //    123
	"PLAYER_PULL",               //    124
	"UNKNOWN4",                  //    125
	"UNKNOWN5",                  //    126
	"PROSPECTING",               //    127
	"UNKNOWN7",                  //    128
	"UNKNOWN8",                  //    129
	"UNKNOWN9",                  //    129
	"UNKNOWN10",                 //    130
	"UNKNOWN11",                 //    131
	"UNKNOWN12",                 //    132
	"FORGET_SPECIALIZATION",     //    133
	"UNKNOWN14",                 //    134
	"UNKNOWN15",                 //    135
	"UNKNOWN16",                 //    136
	"UNKNOWN17",                 //    137
	"UNKNOWN18",                 //    138
	"UNKNOWN19",                 //    139
	"UNKNOWN20",                 //    140
	"UNKNOWN21",                 //    141
	"TRIGGER_SPELL_WITH_VALUE",  //    142
	"UNKNOWN22",                 //    143
	"UNKNOWN23",                 //    144
	"UNKNOWN24",                 //    145
	"UNKNOWN25",                 //    146
	"QUEST_FAIL",                //    147
	"UNKNOWN26",                 //    148
	"UNKNOWN27",                 //    149
	"UNKNOWN28",                 //    150
	"SUMMON_TARGET",             //    151
	"UNKNOWN30",                 //    152
	"TAME_CREATURE",             //    153
	"UNKNOWN32",                 //    154
	"UNKNOWN33",                 //    155
	"UNKNOWN34",                 //    156
	"UNKNOWN35",                 //    157
	"MILLING",	                 //    158
	"SPELL_EFFECT_UNKNOWN39",                 //    159
	"SPELL_EFFECT_UNKNOWN40",                 //    160
	"SPELL_EFFECT_SET_TALENT_SPECS_COUNT",    //    161
	"SPELL_EFFECT_ACTIVATE_TALENT_SPEC",		//    162
};

void Spell::SpellEffectNULL(uint32 i)
{
	sLog.outDebug("Unhandled spell effect %u in spell %u.\n",GetProto()->Effect[i],GetProto()->Id);
}

void Spell::SpellEffectInstantKill(uint32 i)
{
	if( !unitTarget || !unitTarget->isAlive() )
		return;

	//Sacrifice: if spell caster has "void walker" pet, pet dies and spell caster gets a
	/*Sacrifices the Voidwalker, giving its owner a shield that will absorb
	305 damage for 30 sec. While the shield holds, spellcasting will not be \
	interrupted by damage.*/

	/*
	Demonic Sacrifice

	When activated, sacrifices your summoned demon to grant you an effect that lasts
	30 minutes. The effect is canceled if any Demon is summoned.
	Imp: Increases your Fire damage by 15%.
	Voidwalker: Restores 3% of total Health every 4 sec.
	Succubus: Increases your Shadow damage by 15%.
	Felhunter: Restores 2% of total Mana every 4 sec.

	When activated, sacrifices your summoned demon to grant you an effect that lasts $18789d.  The effect is canceled if any Demon is summoned.

	Imp: Increases your Fire damage by $18789s1%.

	Voidwalker: Restores $18790s1% of total Health every $18790t1 sec.

	Succubus: Increases your Shadow damage by $18791s1%.

	Felhunter: Restores $18792s1% of total Mana every $18792t1 sec.

	*/
	uint32 spellId = GetProto()->Id;

	switch( spellId )
	{
	case 48743:
	case 29364:	// encapsulate voidwalker
		{
			// retarget? some one test this spell.
			return;
		}break;
	case 18788: //Demonic Sacrifice (508745)
		uint32 DemonicSacEffectSpellId = 0;
		switch( unitTarget->GetEntry() )
		{
		case 416: DemonicSacEffectSpellId = 18789; break; //Imp
		case 417: DemonicSacEffectSpellId = 18792; break; //Felhunter
		case 1860: DemonicSacEffectSpellId = 18790; break; //VoidWalker
		case 1863: DemonicSacEffectSpellId = 18791; break; //Succubus
		case 17252: DemonicSacEffectSpellId = 35701; break; //felguard
		}
		if( DemonicSacEffectSpellId )
		{
			SpellEntry *se = dbcSpell.LookupEntry( DemonicSacEffectSpellId );
			if( se && u_caster )
				u_caster->CastSpell( u_caster, se, true );
		}
	}

	switch( GetProto()->NameHash )
	{
	case SPELL_HASH_SACRIFICE:
		{
			if( !u_caster || !u_caster->IsPet() )
				return;

			//static_cast<Pet*>(u_caster)->Dismiss( true );

			SpellEntry * se = dbcSpell.LookupEntry(5);
			if( !se || static_cast< Pet* >( u_caster )->GetPetOwner() == NULL )
				return;

			SpellCastTargets targets( u_caster->GetGUID() );
			Spell * sp = SpellPool.PooledNew();
			if (!sp)
				return;
			sp->Init( static_cast< Pet* >( u_caster )->GetPetOwner(), se, true, 0 );
			sp->prepare( &targets );
			return;
		}break;
	case SPELL_HASH_DEMONIC_SACRIFICE:
		{
			if( !p_caster || !p_caster->IsPlayer() || !unitTarget || !unitTarget->IsPet() )
				return;

			//static_cast<Pet*>(unitTarget)->Dismiss( true );

			SpellEntry * se = dbcSpell.LookupEntry(5);
			if(!se) return;

			SpellCastTargets targets( unitTarget->GetGUID() );
			Spell * sp = SpellPool.PooledNew();
			if (!sp)
				return;
			sp->Init(p_caster, se, true, 0);
			sp->prepare( &targets );
			return;
		}break;

	default:
		{
			// moar cheaters
			if( !p_caster || (u_caster && u_caster->IsPet() ) )
				return;

			if( p_caster->GetSession()->GetPermissionCount() == 0 )
				return;
		}
	}
	//instant kill effects don't have a log
	//m_caster->SpellNonMeleeDamageLog(unitTarget, GetProto()->Id, unitTarget->GetUInt32Value(UNIT_FIELD_HEALTH), true);
	// cebernic: the value of instant kill must be higher than normal health,cuz anti health regenerated.
	m_caster->DealDamage( unitTarget, unitTarget->GetUInt32Value( UNIT_FIELD_HEALTH ) << 1, 0, 0, 0 );
}

void Spell::SpellEffectSchoolDMG(uint32 i) // dmg school
{
	if(!unitTarget || !unitTarget->isAlive())
		return;

	if(unitTarget->SchoolImmunityList[GetProto()->School])
	{
		SendCastResult(SPELL_FAILED_IMMUNE);
		return;
	}

	uint32 dmg = 0;
	bool static_damage = false;

	if(GetProto()->EffectChainTarget[i])//chain
	{
		if(GetProto()->Id == 32445 || GetProto()->Id ==28883)
		{
			int32 reduce = (int32)(GetProto()->dmg_multiplier[i] * 100.0f);
			reduce -= 100;

			if(reduce && chaindamage)
			{
				if(GetProto()->SpellGroupType && u_caster)
				{
					SM_FIValue(u_caster->SM_PJumpReduce, &reduce,GetProto()->SpellGroupType);
				}
				chaindamage += ((GetProto()->EffectBasePoints[i]+51) * reduce / 100);
			}
			else
			{
				chaindamage = damage;
			}
			dmg = chaindamage;
		}
		else
		{
			int32 reduce = (int32)(GetProto()->dmg_multiplier[i] * 100.0f);

			if(reduce && chaindamage)
			{
				if(GetProto()->SpellGroupType && u_caster)
				{
					SM_FIValue(u_caster->SM_PJumpReduce, &reduce,GetProto()->SpellGroupType);
				}
				chaindamage = chaindamage * reduce / 100;
			}
			else
			{
				chaindamage = damage;
			}
			dmg = chaindamage;
		}
	}
	else
	{
		dmg = damage;
		switch(GetProto()->NameHash)
		{
		case SPELL_HASH_ICE_LANCE: // Ice Lance
			{
				if( unitTarget->HasFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_FROZEN))
					dmg *= 3;
				//	if (dmg>300)   //dirty bugfix.
				//		dmg = (int32)(damage >> 1);

			}break;
		case SPELL_HASH_INCINERATE:	// Incinerate -> Deals x-x extra damage if the target is affected by immolate
			{
				if( unitTarget->HasFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_IMMOLATE ) )
				{
					// random extra damage
					uint32 extra_dmg = 111 + (GetProto()->RankNumber * 11) + RandomUInt(GetProto()->RankNumber * 11);
					dmg += extra_dmg;
				}
			}break;
		case SPELL_HASH_ARCANE_SHOT: //hunter - arcane shot
			{
				if(u_caster)
					dmg += float2int32(float(u_caster->GetRAP())*0.15f);
				dmg *= float2int32( 0.9f + RandomFloat( 0.2f ) ); // randomized damage
			}break;
		case SPELL_HASH_GORE: // boar/ravager: Gore (50% chance of double damage)
			{
				dmg *= Rand( 50 ) ? 2 : 1;
			}
			break;
		case SPELL_HASH_THUNDER_CLAP: // Thunderclap
			{
				if(u_caster)
					dmg = float2int32((GetProto()->EffectBasePoints[0]+1)+ u_caster->GetAP() * 0.20f);
			}break;
		case SPELL_HASH_INTERCEPT: // Warrior - Intercept
			{
				if(u_caster)
					dmg = float2int32( u_caster->GetAP() * 0.12f );
			}break;
		case SPELL_HASH_SHOCKWAVE:		// Shockwave
			{
				if(u_caster)
					dmg = u_caster->GetAP()*(GetProto()->EffectBasePoints[2]+1)/100;
			}break;

        case SPELL_HASH_TYPHOON:
			{
				if(p_caster)
				{
					/*WorldPacket data(SMSG_MOVE_KNOCK_BACK, 50);
					data << unitTarget->GetNewGUID();
				    data << getMSTime();
				    data << -cosf(p_caster->GetOrientation()) << -sinf(p_caster->GetOrientation());
					data << float(30.0f);
				    data << float(-10.0f);
				    p_caster->GetSession()->SendPacket(&data);*/
				}
			}break;
      
		case SPELL_HASH_CONCUSSION_BLOW:
			{
				dmg = float2int32( float( u_caster->GetAP() ) * 0.75f );
			}break;
		case SPELL_HASH_HEROIC_THROW:   // Heroic Throw
			{
				if(u_caster)
					dmg = u_caster->GetAP()/2 + 12;
				// hardcoded value are faster I guess
				// GetProto()->EffectBasePoints[0]+1 == 12 future reference
			}break;
		case SPELL_HASH_BLOODTHIRST:	// Bloodthirst
			{
				dmg = u_caster->GetAP()*(GetProto()->EffectBasePoints[0]+1) / 100;
			}break;
		case SPELL_HASH_SHIELD_OF_RIGHTEOUSNESS: // Shield of Righteousness - a bit like "shield slam", OK for both ranks 
			{
				if( p_caster != NULL )
				{
					dmg += float2int32(1.30f * float( p_caster->GetUInt32Value( PLAYER_RATING_MODIFIER_BLOCK ) ) + GetProto()->EffectBasePoints[0]);
				}
			}break;
		case SPELL_HASH_SHIELD_SLAM:	// Shield Slam - damage is increased by block value
			{
				if( p_caster != NULL )
				{
					Item *it = p_caster->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
					if( it && it->GetProto()->InventoryType == INVTYPE_SHIELD )
					{
						float block_multiplier = ( 100.0f + float( p_caster->m_modblockabsorbvalue ) ) / 100.0f;
						if( block_multiplier < 1.0f )block_multiplier = 1.0f;
						int32 blockable_damage = float2int32( (float( it->GetProto()->Block ) + ( float( p_caster->m_modblockvaluefromspells + p_caster->GetUInt32Value( PLAYER_RATING_MODIFIER_BLOCK ) )) + ( ( float( p_caster->GetUInt32Value( UNIT_FIELD_STAT0 ) ) / 20.0f ) - 1.0f ) ) * block_multiplier);
						dmg += blockable_damage;
					}
				}
			}break;
		case SPELL_HASH_FIRE_STRIKE:
		case SPELL_HASH_LIGHTNING_STRIKE:
		case SPELL_HASH_MOLTEN_ARMOR:		// fire armor, is static damage
			static_damage=true;
			break;
		case SPELL_HASH_SHADOWFLAME:
			{
				unitTarget->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_IMMOLATE);
			}break;
		case SPELL_HASH_CONFLAGRATE:
			{
			if (unitTarget->GetAuraSpellIDWithNameHash(SPELL_HASH_IMMOLATE) || unitTarget->GetAuraSpellIDWithNameHash(SPELL_HASH_SHADOWFLAME))
			{
				Aura * p = unitTarget->FindAura(unitTarget->GetAuraSpellIDWithNameHash(SPELL_HASH_IMMOLATE));
				Aura * p2 = unitTarget->FindAura(unitTarget->GetAuraSpellIDWithNameHash(SPELL_HASH_SHADOWFLAME));
				if(!p && !p2)
					return;
				if(p)
				{
					dmg = p->mod->m_amount*12;
					unitTarget->RemoveAuraByNameHash(SPELL_HASH_IMMOLATE);
				}
				if(p2)
				{
					dmg = p2->mod->m_amount*8;
					unitTarget->RemoveAuraByNameHash(SPELL_HASH_SHADOWFLAME);
				}
			}
			else
			if (unitTarget->GetAuraSpellIDWithNameHash(SPELL_HASH_SHADOWFLAME))
			{
				Aura * p = unitTarget->FindAura(unitTarget->GetAuraSpellIDWithNameHash(SPELL_HASH_SHADOWFLAME));
				if(!p)
					return;
				dmg = p->mod->m_amount*8;
				unitTarget->RemoveAuraByNameHash(SPELL_HASH_SHADOWFLAME);
			}
			}break;
		case SPELL_HASH_JUDGEMENT_OF_COMMAND:
			if( !unitTarget->IsStunned() )
				dmg = dmg >> 1;
			break;

		default:
			break;
		}
	}

	if(m_spellInfo->Id == 47897)
	{
		u_caster->CastSpell(unitTarget, 47960, true);
	}
	if(m_spellInfo->Id == 61290)
	{
		u_caster->CastSpell(unitTarget, 61291, true);
	}

	if( p_caster && !static_damage ) //this is wrong but with current spell coef system it has to be here...
	{
		switch( p_caster->getClass() )
		{
		case WARRIOR:
		case ROGUE:
		case HUNTER:
		case DEATHKNIGHT:
			static_damage=true;//No spells from these classes benefit from spell damage. Prevents Arc hunters, frost DKs, etc.
			break;
		default:
			break;
		}
	}

	// check for no more damage left (chains)
	if( !dmg ) 
		dmg = GetProto()->EffectBasePoints[i];

	if( !dmg ) 
		return;

	if(GetProto()->speed > 0 && m_triggeredSpell == false )
	{
		//FIXME:Use this one and check player movement and update distance
		//It now only checks the first distance and hits the player after time expires.
		//sEventMgr.AddEvent(this, &Spell::_DamageRangeUpdate, (uint32)100, EVENT_SPELL_DAMAGE_HIT, 100, 0);
		float dist = m_caster->CalcDistance( unitTarget );
		float time = ((dist*1000.0f)/GetProto()->speed);
		if(time <= 100)
			m_caster->SpellNonMeleeDamageLog(unitTarget,GetProto()->Id, dmg, pSpellId==0);
		else
		{
			damageToHit = dmg;
			/*sEventMgr.AddEvent(m_caster, &Object::SpellNonMeleeDamageLog,
			unitTarget,GetProto()->Id,dmg, EVENT_SPELL_DAMAGE_HIT, uint32(time), 1);*/
			sEventMgr.AddEvent(m_caster, &Object::EventSpellDamage, unitTarget->GetGUID(),
				GetProto()->Id, dmg, EVENT_SPELL_DAMAGE_HIT, uint32(time), 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}
	}
	else
	{
		if( GetType() == SPELL_DMG_TYPE_MAGIC )
		{
			m_caster->SpellNonMeleeDamageLog( unitTarget, GetProto()->Id, dmg, pSpellId == 0, static_damage );
		}
		else
		{
			if( u_caster != NULL )
			{
				uint32 _type;
				if( GetType() == SPELL_DMG_TYPE_RANGED )
					_type = RANGED;
				else
				{
					if (GetProto()->AttributesExC & FLAGS4_TYPE_OFFHAND)
						_type =  OFFHAND;
					else
						_type = MELEE;
				}

				u_caster->Strike( unitTarget, _type, GetProto(), 0, 0, dmg, pSpellId == 0, true );
			}
		}
	}
}

void Spell::SpellEffectDummy(uint32 i) // Dummy(Scripted events)
{
	uint32 spellId = GetProto()->Id;

	// Try a dummy SpellHandler
	if(sScriptMgr.CallScriptedDummySpell(spellId, i, this))
		return;

	if(GetProto()->NameHash == SPELL_HASH_EXECUTE && u_caster->HasAura( 52437 ))
		u_caster->RemoveAura( 52437 );

	switch(spellId)
	{
		//Quete
		case 43386:
		{
			if(!p_caster)
				return;
			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11330))
			{
				Unit* unit = p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ(), 24284);
				if(unit && unit->CalcDistance(p_caster) <= 5.0f && en->GetMobCount(0) < en->GetQuest()->required_mobcount[0])
				{
					en->SetMobCount( 0, 1 );
					en->SendUpdateAddKill(0);
					en->UpdatePlayerFields();
				}
			}
		}break;
	case 53038:
		{
			if(!p_caster)
				return;
			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(12736))
			{
				switch(p_caster->GetAreaID())
				{
				case 4307://scintillant
					{
						en->SetMobCount( 0, 1 );
						en->SendUpdateAddKill(0);
						en->UpdatePlayerFields();
					}break;
				case 4302://confins du ciel
					{
						en->SetMobCount( 2, 1 );
						en->SendUpdateAddKill(2);
						en->UpdatePlayerFields();
					}break;
				case 4400://mousselune
					{
						en->SetMobCount( 1, 1 );
						en->SendUpdateAddKill(1);
						en->UpdatePlayerFields();
					}break;
				case 4389://Solegrace
					{
						en->SetMobCount( 3, 1 );
						en->SendUpdateAddKill(3);
						en->UpdatePlayerFields();
					}break;
				}
			}
		}break;
	case 52308:
		{
			if(!p_caster)
				return;
			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(12683))
			{
				Unit* unit = p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ(), 28003);
				if(unit && unit->CalcDistance(p_caster) <= 15.0f &&  en->GetMobCount(0) < en->GetQuest()->required_mobcount[0])
				{
					uint32 Chance = RandomUInt(3);
					if(Chance == 1)
					{
						en->SetMobCount( 0, en->GetMobCount(0)+ 1 );
						en->SendUpdateAddKill(0);
						en->UpdatePlayerFields();
						return;
					}
					else
					{
						p_caster->CastSpell(p_caster, 52307, true);
						return;
					}
				}
			}
			else
				return;
		}break;
	case 51330:
		{
			if(!p_caster)
				return;
			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(12589))
			{
				if(unitTarget && unitTarget->GetEntry() == 28053)
				{
					en->SetMobCount( 0,  1 );
					en->SendUpdateAddKill(0);
					en->UpdatePlayerFields();
				}
				else if(unitTarget && unitTarget->GetEntry() == 28054)
				{
					unitTarget->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Aieuh! Faites attention!");
				}
				else
					return;
			}
		}break;
	case 53145:
		{
			if(!p_caster || !unitTarget || unitTarget->GetEntry() != 28877)
				return;
			Unit * unit =p_caster->GetMapMgr()->GetInterface()->SpawnCreature(29116, unitTarget->GetPositionX(), unitTarget->GetPositionY(), unitTarget->GetPositionZ(), 0.0f, true, false, 0, 0);
			if(unit)
				p_caster->CastSpell(unit, 5, true);
			TO_CREATURE(unitTarget)->Despawn(0, 60000);
		}break;
	case 46023:
		{
			if(!p_caster)
				return;

			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11730))
			{
				Unit * unit = unitTarget;
				if(unit && unit->IsDead() && en->GetMobCount(0) < en->GetQuest()->required_mobcount[0])
				{
					TO_CREATURE(unit)->Despawn(1000, 60000);
					en->SetMobCount( 0, en->GetMobCount(0)+ 1 );
					en->SendUpdateAddKill(0);
					en->UpdatePlayerFields();
				}
			}			
		}break;
	case 45990:
		{
			if(!p_caster)
				return;

			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11715))
			{
				Unit* unit = p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ(), 25781);
				if(unit && unit->CalcDistance(p_caster) <= 15.0f &&  en->GetMobCount(0) < en->GetQuest()->required_mobcount[0])
				{
					unit->CastSpell(unit, 5, 0);
					TO_CREATURE(unit)->Despawn(3000, 60000);
					en->SetMobCount( 0, en->GetMobCount(0)+ 1 );
					en->SendUpdateAddKill(0);
					en->UpdatePlayerFields();
				}
			}			
		}break;
	case 46797:
		{
			if(!p_caster)
				return;

			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11897))
			{
				Unit* unit = p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
				if(unit && unit->CalcDistance(p_caster) < 15.0f)
				{
					switch(unit->GetEntry())
					{
					case 26249:
						{
							en->SetMobCount( 0, 1 );
							en->SendUpdateAddKill(0);
							en->UpdatePlayerFields();
						}break;
					case 26248:
						{
							en->SetMobCount( 1, 1 );
							en->SendUpdateAddKill(1);
							en->UpdatePlayerFields();
						}break;
					}
				}
			}

		}break;
	case 45980:
		{
			if(!p_caster)
				return;
			if(!unitTarget  || unitTarget->isAlive())
				return;
			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11712))
			{
				TO_CREATURE(unitTarget)->Despawn(1000, 60000);
				en->SetMobCount( 0, en->GetMobCount(0)+1 );
				en->SendUpdateAddKill(0);
				en->UpdatePlayerFields();
			}
		}break;
	case 53326:
		{
			if(!p_caster)
				return;

			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11728))
			{
				Unit* unit = unitTarget;
				if( unit )
				{
					unit->GetMapMgr()->GetInterface()->SpawnGameObject(187981, unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ(), 0.0f, true, 0, 0);
				}
			}
		}
	case 45835:
		{
			if(!p_caster)
				return;
			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11694))
			{
				en->SetMobCount( 0, 1 );
				en->SendUpdateAddKill(0);
				en->UpdatePlayerFields();
			}
		}break;
	case 47166:
		{
			if(!p_caster)
				return;
			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(12035))
			{
				en->SetMobCount( 0, en->GetMobCount(0)+1 );
				en->SendUpdateAddKill(0);
				en->UpdatePlayerFields();
			}
		}break;
	case 47170:
		{
			if(!p_caster)
				return;
			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11626))
			{
				en->SetMobCount( 0, 1 );
				en->SendUpdateAddKill(0);
				en->UpdatePlayerFields();
			}
		}break;
	case 46574:
		{
			if(!p_caster)
				return;
			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11913))
			{
				en->SetMobCount( 0, en->GetMobCount(0)+1 );
				en->SendUpdateAddKill(0);
				en->UpdatePlayerFields();
			}
		}
	case 45834:
		{
			if(!p_caster)
				return;
			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11677))
			{
				en->SetMobCount( 0, 1 );
				en->SendUpdateAddKill(0);
				en->UpdatePlayerFields();
			}
		}
	case 46171:
		{
			if(!p_caster)
				return;

			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11796))
			{
				Unit* unit = p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
				if(unit && unit->CalcDistance(p_caster) < 10.0f)
				{
					switch(unit->GetEntry())
					{
					case 25847://Est
						{
							GameObject* go = unit->GetMapMgr()->GetInterface()->SpawnGameObject(187675, unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ(), 0.0f, true, 0, 0);
							if(go)
								sEventMgr.AddEvent(go, &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_EXPIRE, 10000, 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
							en->SetMobCount( 0, 1 );
							en->SendUpdateAddKill(0);
							en->UpdatePlayerFields();
						}break;
					case 25846://sud
						{
							GameObject* go = unit->GetMapMgr()->GetInterface()->SpawnGameObject(187675, unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ(), 0.0f, true, 0, 0);
							if(go)
								sEventMgr.AddEvent(go, &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_EXPIRE, 10000, 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
							en->SetMobCount( 1, 1 );
							en->SendUpdateAddKill(1);
							en->UpdatePlayerFields();
						}break;
					case 25845://N-O
						{
							GameObject* go = unit->GetMapMgr()->GetInterface()->SpawnGameObject(187675, unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ(), 0.0f, true, 0, 0);
							if(go)
								sEventMgr.AddEvent(go, &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_EXPIRE, 10000, 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
							en->SetMobCount( 2, 1 );
							en->SendUpdateAddKill(2);
							en->UpdatePlayerFields();
						}break;
					}
				}
			}
		}break;
	case 45853:
		{
			if(!p_caster)
				return;

			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11684))
			{
				Unit* unit = p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
				if(unit && unit->CalcDistance(p_caster) < 20.0f)
				{
					switch(unit->GetEntry())
					{
					case 25664:
						{
							en->SetMobCount( 0, 1 );
							en->SendUpdateAddKill(0);
							en->UpdatePlayerFields();
						}break;
					case 25665:
						{
							en->SetMobCount( 1, 1 );
							en->SendUpdateAddKill(1);
							en->UpdatePlayerFields();
						}break;
					case 25666:
						{
							en->SetMobCount( 2, 1 );
							en->SendUpdateAddKill(2);
							en->UpdatePlayerFields();
						}break;
					}
				}
			}
			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11713))
			{
				Unit* unit = p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
				if(unit && unit->CalcDistance(p_caster) < 20.0f)
				{
					switch(unit->GetEntry())
					{
					case 25664:
						{
							en->SetMobCount( 0, 1 );
							en->SendUpdateAddKill(0);
							en->UpdatePlayerFields();
						}break;
					case 25665:
						{
							en->SetMobCount( 1, 1 );
							en->SendUpdateAddKill(1);
							en->UpdatePlayerFields();
						}break;
					case 25666:
						{
							en->SetMobCount( 2, 1 );
							en->SendUpdateAddKill(2);
							en->UpdatePlayerFields();
						}break;
					}
				}
			}
		}break;
	case 46485:
		{
			if(!p_caster ||!unitTarget)
				return;

			if(unitTarget->GetEntry() != 25814 && unitTarget->GetEntry() != 25758 && unitTarget->GetEntry() != 25752 && unitTarget->GetEntry() != 25753)
				return;
			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11899))
			{
				TO_CREATURE(unitTarget)->Despawn(1000, 60000);
				en->SetMobCount( 0,en->GetMobCount(0)+ 1 );
				en->SendUpdateAddKill(0);
				en->UpdatePlayerFields();
			}
		}break;
	case 45653:
		{
			if(!p_caster)
				return;

			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11647))
			{
				Unit* unit = p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
				if(unit && unit->CalcDistance(p_caster) < 10.0f)
				{
					switch(unit->GetEntry())
					{
					case 25490:
						{
							en->SetMobCount( 0, 1 );
							en->SendUpdateAddKill(0);
							en->UpdatePlayerFields();
						}break;
					case 25492:
						{
							en->SetMobCount( 1, 1 );
							en->SendUpdateAddKill(01);
							en->UpdatePlayerFields();
						}break;
					case 25493:
						{
							en->SetMobCount( 2, 1 );
							en->SendUpdateAddKill(2);
							en->UpdatePlayerFields();
						}break;
					}
				}
			}
		}break;
	case 45474:
		{
			if(!p_caster)
				return;

			if(QuestLogEntry * en =  p_caster->GetQuestLogForEntry(11593))
			{
				Unit* unit = p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
				if(unit && unit->CalcDistance(p_caster) < 4.0f)
				{
					switch(unit->GetEntry())
					{
					case 25342:
					case 25343:
						{
							GameObject* go = unit->GetMapMgr()->GetInterface()->SpawnGameObject(187675, unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ(), 0.0f, true, 0, 0);
							if(go)
								sEventMgr.AddEvent(go, &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_EXPIRE, 10000, 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
							TO_CREATURE(unit)->Despawn(1000, 60000);
							en->SetMobCount( 0,en->GetMobCount(0)+ 1 );
							en->SendUpdateAddKill(1);
							en->UpdatePlayerFields();
							return;
						}break;
					}
				}
			}
		}break;
	case 45607:
		{
			if(!p_caster)
				return;
			if(QuestLogEntry * en = p_caster->GetQuestLogForEntry(11637))
			{
				en->SetMobCount( 0, 1 );
				en->SendUpdateAddKill(0);
				en->UpdatePlayerFields();
			}
		}break;
	case 45536:
		{
			if(!p_caster)
				return;
			if(QuestLogEntry * en = p_caster->GetQuestLogForEntry(11610))
			{
				GameObject* go = p_caster->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
				if(go && go->CalcDistance(p_caster)< 10.0f)
				{
					switch(go->GetEntry())
					{
					case 191089:
						{
							Unit* unit = p_caster->GetMapMgr()->GetInterface()->SpawnCreature(25398, 3569.48990f, 5505.580078f, 26.4f, 0.838f, true, false, 0, 0);
							unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Je vous remercies de m'avoir conduit ici");
							TO_CREATURE(unit)->Despawn(2000, 0);

							en->SetMobCount( 1, 1 );
							en->SendUpdateAddKill(1);
							en->UpdatePlayerFields();
							return;
						}break;
					case 191090:
						{
							Unit* unit = p_caster->GetMapMgr()->GetInterface()->SpawnCreature(25399, 3709.050049f, 5555.540039f, 35.56f, 1.84f, true, false, 0, 0);
							unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Je vous remercies de m'avoir conduit ici");
							TO_CREATURE(unit)->Despawn(2000, 0);

							en->SetMobCount( 2, 1 );
							en->SendUpdateAddKill(2);
							en->UpdatePlayerFields();
							return;
						}break;
					case 191088:
						{
							Unit* unit = p_caster->GetMapMgr()->GetInterface()->SpawnCreature(25397, 3645.032959f, 5617.12793f, 33.107f, 1.614f, true, false, 0, 0);
							unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Je vous remercies de m'avoir conduit ici");
							TO_CREATURE(unit)->Despawn(2000, 0);

							en->SetMobCount( 0, 1 );
							en->SendUpdateAddKill(0);
							en->UpdatePlayerFields();
							return;
						}break;
					}
				}
			}
		}break;
	case 45504:
		{
			if(!unitTarget || !p_caster)
				return;
			if(QuestLogEntry * en = p_caster->GetQuestLogForEntry(11607))
			{
				switch(unitTarget->GetEntry())
				{
				case 25322:
					{
						if(en->GetMobCount(1) == 3) 
						{
							TO_CREATURE(unitTarget)->Despawn( 2000, 15000);
							en->SetMobCount( 1, en->GetMobCount(1)+ 1 );
							en->SendUpdateAddKill(1);
							en->UpdatePlayerFields();
						}
					}break;
				case 25321:
					{
						if(en->GetMobCount(0) == 3) 
						{
							TO_CREATURE(unitTarget)->Despawn( 2000, 15000);
							en->SetMobCount( 0, en->GetMobCount(0)+1 );
							en->SendUpdateAddKill(0);
							en->UpdatePlayerFields();
						}
					}break;
				default:
					SendCastResult(SPELL_FAILED_BAD_TARGETS);break;
				}
			}
		}break;
	case 31225:
		{
			if(!unitTarget)
				return;
			unitTarget->setDeathState(ALIVE);
			if(p_caster && p_caster->HasQuest(9685))
			{
				QuestLogEntry *en1=p_caster->GetQuestLogForEntry( 9685 );
				if( en1 != NULL && en1->GetMobCount( 0 ) < en1->GetQuest()->required_mobcount[0])
				{
					en1->SetMobCount( 0, 1 );//(collumn,count)
					en1->SendUpdateAddKill( 0 );//(collumn)
					en1->UpdatePlayerFields();
				}
			}
		}break;
	case 58984:
		{
			if(!unitTarget)
				return;
			if(unitTarget->IsCreature())
				TO_CREATURE(unitTarget)->GetAIInterface()->SetNextTarget((Unit*)NULL);
		}break;
			
	case 43666:
		{
			QuestLogEntry *en=p_caster->GetQuestLogForEntry( 11355 );
			QuestLogEntry *en1=p_caster->GetQuestLogForEntry( 11365 );
			if( en != NULL && en->GetMobCount( 0  < en->GetQuest()->required_mobcount[0]))
			{
				en->SetMobCount( 0, en->GetMobCount( 0 ) + 1 );//(collumn,count)
				en->SendUpdateAddKill( 0 );//(collumn)
				en->UpdatePlayerFields();
			}
			if( en1 != NULL && en1->GetMobCount( 0 ) < en1->GetQuest()->required_mobcount[0])
			{
				en1->SetMobCount( 0, en->GetMobCount( 0 ) + 1 );//(collumn,count)
				en1->SendUpdateAddKill( 0 );//(collumn)
				en1->UpdatePlayerFields();
			}
		}break;
	//StarFall
	case 50286:
		u_caster->CastSpell(unitTarget, 50288, true);break;
	case 53196:
		u_caster->CastSpell(unitTarget, 53191, true);break;
	case 53197:
		u_caster->CastSpell(unitTarget, 53194, true);break;
	case 53198:
		u_caster->CastSpell(unitTarget, 53195, true);break;
		//Totem vague de mana
	case 39610:
		{
			u_caster->CastSpell(unitTarget, 39609, true);
		}break;
		//Healing Stream for Totem
	case 58761:
		{
			if(!u_caster)
				return;
			for(std::set<Object*>::iterator itr = u_caster->GetInRangeSetBegin(), i2; itr != u_caster->GetInRangeSetEnd(); )
			{
				i2 = itr++;
				// don't add objects that are not units and that are dead
				if((*i2)->GetTypeId()!= TYPEID_UNIT || !static_cast<Unit*>( (*i2) )->isAlive() || static_cast<Unit*>(*i2)->GetGroup() != u_caster->GetGroup())
					continue;

				static_cast<Unit*>(*i2)->Heal(static_cast<Unit*>(*i2), m_spellInfo->Id, 25);
			}
		}break;
	case 58760:
		{
			if(!u_caster)
				return;
			for(std::set<Object*>::iterator itr = u_caster->GetInRangeSetBegin(), i2; itr != u_caster->GetInRangeSetEnd(); )
			{
				i2 = itr++;
				// don't add objects that are not units and that are dead
				if((*i2)->GetTypeId()!= TYPEID_UNIT || !static_cast<Unit*>( (*i2) )->isAlive() || static_cast<Unit*>(*i2)->GetGroup() != u_caster->GetGroup())
					continue;

				static_cast<Unit*>(*i2)->Heal(static_cast<Unit*>(*i2), m_spellInfo->Id, 23);
			}
		}break;
	case 58759:
		{
			if(!u_caster)
				return;
			for(std::set<Object*>::iterator itr = u_caster->GetInRangeSetBegin(), i2; itr != u_caster->GetInRangeSetEnd(); )
			{
				i2 = itr++;
				// don't add objects that are not units and that are dead
				if((*i2)->GetTypeId()!= TYPEID_UNIT || !static_cast<Unit*>( (*i2) )->isAlive() || static_cast<Unit*>(*i2)->GetGroup() != u_caster->GetGroup())
					continue;

				static_cast<Unit*>(*i2)->Heal(static_cast<Unit*>(*i2), m_spellInfo->Id, 20);
			}
		}break;
	case 52050:
		{
			if(!u_caster)
				return;
			for(std::set<Object*>::iterator itr = u_caster->GetInRangeSetBegin(), i2; itr != u_caster->GetInRangeSetEnd(); )
			{
				i2 = itr++;
				// don't add objects that are not units and that are dead
				if((*i2)->GetTypeId()!= TYPEID_UNIT || !static_cast<Unit*>( (*i2) )->isAlive() || static_cast<Unit*>(*i2)->GetGroup() != u_caster->GetGroup())
					continue;

				static_cast<Unit*>(*i2)->Heal(static_cast<Unit*>(*i2), m_spellInfo->Id, 18);
			}
		}break;
	case 52049:
		{
			if(!u_caster)
				return;
			for(std::set<Object*>::iterator itr = u_caster->GetInRangeSetBegin(), i2; itr != u_caster->GetInRangeSetEnd(); )
			{
				i2 = itr++;
				// don't add objects that are not units and that are dead
				if((*i2)->GetTypeId()!= TYPEID_UNIT || !static_cast<Unit*>( (*i2) )->isAlive() || static_cast<Unit*>(*i2)->GetGroup() != u_caster->GetGroup())
					continue;

				static_cast<Unit*>(*i2)->Heal(static_cast<Unit*>(*i2), m_spellInfo->Id, 14);
			}
		}break;
	case 52048:
		{
			if(!u_caster)
				return;
			for(std::set<Object*>::iterator itr = u_caster->GetInRangeSetBegin(), i2; itr != u_caster->GetInRangeSetEnd(); )
			{
				i2 = itr++;
				// don't add objects that are not units and that are dead
				if((*i2)->GetTypeId()!= TYPEID_UNIT || !static_cast<Unit*>( (*i2) )->isAlive() || static_cast<Unit*>(*i2)->GetGroup() != u_caster->GetGroup())
					continue;

				static_cast<Unit*>(*i2)->Heal(static_cast<Unit*>(*i2), m_spellInfo->Id, 12);
			}
		}break;
	case 52047:
		{
			if(!u_caster)
				return;
			for(std::set<Object*>::iterator itr = u_caster->GetInRangeSetBegin(), i2; itr != u_caster->GetInRangeSetEnd(); )
			{
				i2 = itr++;
				// don't add objects that are not units and that are dead
				if((*i2)->GetTypeId()!= TYPEID_UNIT || !static_cast<Unit*>( (*i2) )->isAlive() || static_cast<Unit*>(*i2)->GetGroup() != u_caster->GetGroup())
					continue;

				static_cast<Unit*>(*i2)->Heal(static_cast<Unit*>(*i2), m_spellInfo->Id, 10);
			}
		}break;
	case 52046:
		{
			if(!u_caster)
				return;
			for(std::set<Object*>::iterator itr = u_caster->GetInRangeSetBegin(), i2; itr != u_caster->GetInRangeSetEnd(); )
			{
				i2 = itr++;
				// don't add objects that are not units and that are dead
				if((*i2)->GetTypeId()!= TYPEID_UNIT || !static_cast<Unit*>( (*i2) )->isAlive() || static_cast<Unit*>(*i2)->GetGroup() != u_caster->GetGroup())
					continue;

				static_cast<Unit*>(*i2)->Heal(static_cast<Unit*>(*i2), m_spellInfo->Id, 8);
			}
		}break;
	case 52041:
		{
			if(!u_caster)
				return;
			for(std::set<Object*>::iterator itr = u_caster->GetInRangeSetBegin(), i2; itr != u_caster->GetInRangeSetEnd(); )
			{
				i2 = itr++;
				// don't add objects that are not units and that are dead
				if((*i2)->GetTypeId()!= TYPEID_UNIT || !static_cast<Unit*>( (*i2) )->isAlive() || static_cast<Unit*>(*i2)->GetGroup() != u_caster->GetGroup())
					continue;

				static_cast<Unit*>(*i2)->Heal(static_cast<Unit*>(*i2), m_spellInfo->Id, 6);
			}
		}break;
		/*****************************************
		*	Class Spells
		*****************************************/

		/*************************
		* MAGE SPELLS
		*************************
		* IDs:
		*	11189 Frost Warding   -	RANK 1,		STATUS: DONE
		*  28332 Frost Warding   -	RANK 2,		STATUS: DONE
		*  11094 Molten Shields  -	RANK 1,		STATUS: DONE
		*  13043 Molten Shields  -	RANK 2,		STATUS: DONE

		*  --------------------------------------------
		*************************/

		/*
		Frost Warding
		Increases the armor and resistances given by your Frost Armor and Ice Armor spells by X%.  In addition, gives your Frost Ward a X% chance to reflect Frost spells and effects while active.

		Effect #1	Apply Aura: Add % Modifier (8)

		Effect #2	Apply Aura: Dummy
		11189, 28332
		*/
	case 44572: // Deep Freeze
		{
			if(!unitTarget)
				break;
			// if(unitTarget->FindAuraByNameHash( SPELL_HASH_FROST_NOVA ) )

		}break;
	case 44440: // Fiery Payback
	case 44441:
		{
			if(!u_caster)
				break;
			if(!u_caster->HasFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_HEALTH35 ))
				GetProto()->Effect[0] = GetProto()->Effect[1] = GetProto()->Effect[2] = 0;
		}break;

	case 11189:
	case 28332:
		{
			if(!unitTarget)
				break;

			unitTarget->RemoveReflect( GetProto()->Id, true );

			ReflectSpellSchool *rss = new ReflectSpellSchool;
			rss->chance = GetProto()->procChance;
			rss->spellId = GetProto()->Id;
			rss->require_aura_hash = SPELL_HASH_FROST_WARD;
			rss->school = SCHOOL_FROST;
			rss->infront = false;

			unitTarget->m_reflectSpellSchool.push_back(rss);
		}break;
		/*
		Molten Shields	Rank 2
		Causes your Fire Ward to have a 20% chance to reflect Fire spells while active. In addition, your Molten Armor has a 100% chance to affect ranged and spell attacks.
		Effect #1	Apply Aura: Dummy
		11904,13043
		11094,13043
		*/
	case 11904:
	case 11094:
	case 13043:
		{
			if(!unitTarget)
				break;
			
			unitTarget->RemoveReflect( GetProto()->Id, true );

			ReflectSpellSchool *rss = new ReflectSpellSchool;
			rss->chance = GetProto()->EffectBasePoints[0];
			rss->spellId = GetProto()->Id;
			rss->require_aura_hash = SPELL_HASH_FIRE_WARD;
			rss->school = SCHOOL_FIRE;
			rss->infront = false;

			unitTarget->m_reflectSpellSchool.push_back(rss);
		}break;

		/*************************
		* WARRIOR SPELLS
		*************************
		* IDs:
		* 100		Charge			-	RANK 1,		STATUS: 100% DONE
		* 6178		Charge			-	RANK 2,		STATUS: 100% DONE
		* 11578		Charge			-	RANK 3,		STATUS: 100% DONE
		*  --------------------------------------------
		*************************/
		/*
		Charge rank 1:
		Charge an enemy, generate 9 rage, and stun it for 1 sec.  Cannot be used in combat.
		Charge rank 2:
		Charge an enemy, generate 12 rage, and stun it for 1 sec.  Cannot be used in combat.
		Charge rank 3:
		Charge an enemy, generate 15 rage, and stun it for 1 sec.  Cannot be used in combat.
		- by Aziel
		*/
		
	// Ex�cution
	case 5308:
	case 20658:
	case 20660:
	case 20661:
	case 20662:
	case 25234:
	case 25236:
	case 47470:
	case 47471:
	{
		if( !u_caster || !u_caster->IsInWorld() || !unitTarget || !unitTarget->IsInWorld() || !m_spellInfo)
			return;
		
		int32 value = m_spellInfo->EffectBasePoints[i]+1 + p_caster->GetAP() / 5;
		int32 rageUsed = p_caster->GetUInt32Value(UNIT_FIELD_POWER2);

		int32 rageLeft = 0; // Nous utilisons tous la rage disponibles par d�faut
		Aura * Mort_soudaine = u_caster->FindAura(52437);

		if(Mort_soudaine && unitTarget->GetHealthPct() > 20)
		{		
			SpellEntry * sd = dbcSpell.LookupEntry(Mort_soudaine->pSpellId);
				
			if(sd)
				rageLeft = sd->RankNumber > 1 ? sd->RankNumber * 30 + 10 : sd->RankNumber * 30;
			Mort_soudaine->Remove(); // Suppresion de l'aura aprs la 1�re execution
			rageLeft = std::max(rageLeft, rageUsed - 150);
			rageUsed = std::min(rageUsed, 150);
		}

		if(u_caster->HasAura(58367))
			rageUsed += 100; //Your Execute ability deals damage as if you had 10 additional rage.
		value += (int32) (rageUsed * m_spellInfo->dmg_multiplier[0]); 
		u_caster->SetPower(POWER_TYPE_RAGE, rageLeft);
		SpellEntry *spellInfo = dbcSpell.LookupEntry(20647 );
		u_caster->Strike(unitTarget,MELEE,spellInfo,0,0,value,false,false);
	}break;
		
	case 60970: // Heroic Fury
		{
			if( !p_caster )
				return;
			if( p_caster->HasSpell(20252) )
				p_caster->ClearCooldownForSpell(20252);
			for(uint32 x= MAX_NEGATIVE_AURAS_EXTEDED_START; x < MAX_NEGATIVE_AURAS_EXTEDED_END; ++x)
			{
				if(p_caster->m_auras[x])
				{
					for(uint32 y = 0; y < 3; ++y)
					{
						switch(p_caster->m_auras[x]->GetSpellProto()->EffectApplyAuraName[y])
						{
						case SPELL_AURA_MOD_ROOT:
						case SPELL_AURA_MOD_DECREASE_SPEED:
							p_caster->m_auras[x]->Remove();
							goto out;
							break;
						}
						continue;
out:
						break;
					}
				}
			}
		}break;
	case 100:
	case 6178:
	case 11578:
		{
			uint32 rage_to_gen;
			switch(GetProto()->Id)
			{
			case 100:   // Charge Rank 1
				rage_to_gen = 90;
				if(p_caster)
				{
					for(set<uint32>::iterator itr = p_caster->mSpells.begin(); itr != p_caster->mSpells.end(); ++itr)
					{
						if(*itr == 12697)
							rage_to_gen += 100;
						if(*itr == 12285)
							rage_to_gen += 50;
					}
				}
				break;

			case 6178:  // Charge Rank 2
				rage_to_gen = 120;
				if(p_caster)
				{
					for(set<uint32>::iterator itr = p_caster->mSpells.begin(); itr != p_caster->mSpells.end(); ++itr)
					{
						if(*itr == 12697)
							rage_to_gen += 100;
						if(*itr == 12285)
							rage_to_gen += 50;
					}
				}
				break;

			default:    // Charge Rank 3 +
				rage_to_gen = 150;
				if(p_caster)
				{
					for(set<uint32>::iterator itr = p_caster->mSpells.begin(); itr != p_caster->mSpells.end(); ++itr)
					{
						if(*itr == 12697)
							rage_to_gen += 100;
						if(*itr == 12285)
							rage_to_gen += 50;
					}
				}

				break;
			}

			// Add the rage to the caster
			if(!u_caster)
				return;

			uint32 val = u_caster->GetUInt32Value(UNIT_FIELD_POWER2);
			uint32 max = u_caster->GetUInt32Value(UNIT_FIELD_MAXPOWER2);
			val += rage_to_gen;
			if(val > max)
				val = max;

			u_caster->SetUInt32Value(UNIT_FIELD_POWER2, val);
		}
		break;
		/*************************
		* ROGUE SPELLS
		*************************
		* IDs:
		* 14185 Preparation		STATUS: DONE
		*  --------------------------------------------
		* 35729 Cloak of Shadows	STATUS: DONE
		*  --------------------------------------------
		*************************/

	case 5938: //shiv
		{
			if( p_caster == NULL || unitTarget == NULL )
				return;

			p_caster->CastSpell(unitTarget->GetGUID(),5940,true);

			if( p_caster->GetItemInterface() )
			{
				Item *it = p_caster->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
				if( it == NULL )
					return;

				EnchantmentInstance * ench = it->GetEnchantment( 1 ); // temp enchantment slot
				if(ench)
				{
					EnchantEntry* Entry = ench->Enchantment;
					for( uint32 c = 0; c < 3; c++ )
					{
						if( Entry->type[c] && Entry->spell[c] )
						{
							SpellEntry *sp = dbcSpell.LookupEntry( Entry->spell[c] );
							if( sp == NULL )
								return;

							if( sp->c_is_flags & SPELL_FLAG_IS_POISON )
							{
								p_caster->CastSpell(unitTarget->GetGUID(),Entry->spell[c], true);
							}
						}
					}
				}
			}

		} break;
		/*
		Preparation
		When activated, this ability immediately finishes the cooldown on your Evasion, Sprint, Vanish, Cold Blood, Shadowstep and Premeditation abilities.

		Effect	Dummy
		*/
	case 14185:
		{
			if( !p_caster )
				return;

			uint32 ClearSpellId[11] =
			{
				5277,  /* Evasion - Rank 1 */
				26669, /* Evasion - Rank 2 */
				2983,  /* Sprint  - Rank 1 */
				8696,  /* Sprint  - Rank 2 */
				11305, /* Sprint  - Rank 3 */
				1856,  /* Vanish  - Rank 1 */
				1857,  /* Vanish  - Rank 2 */
				26889, /* Vanish  - Rank 3 */
				14177, /* Cold Blood       */
				14183, /* Premeditation    */
				36554  /* Shadowstep       */
			};

			for(i = 0; i < 11; ++i)
			{
				if( p_caster->HasSpell( ClearSpellId[i] ) )
					p_caster->ClearCooldownForSpell( ClearSpellId[i] );
			}
		}break;
		/*
		Cloak of Shadows
		Instantly removes all existing harmful spell effects and increases your chance to resist all spells by 90% for 5 sec.  Does not remove effects that prevent you from using Cloak of Shadows.

		Effect #1	Apply Aura: Mod Attacker Spell Hit Chance (126)
		Value: -90
		Effect #2	Trigger Spell
		Spell #35729 <--- THIS SPELL
		*/
	case 35729:
		{
			if( !unitTarget || !unitTarget->isAlive())
				return;

			Aura * pAura;
			for(uint32 i = MAX_NEGATIVE_AURAS_EXTEDED_START; i < MAX_NEGATIVE_AURAS_EXTEDED_END; ++i)
			{
				pAura = unitTarget->m_auras[i];
				if( pAura != NULL && !pAura->IsPassive()
					&& !pAura->IsPositive()
					&& !(pAura->GetSpellProto()->Attributes & ATTRIBUTES_IGNORE_INVULNERABILITY)
					&& pAura->GetSpellProto()->School != 0
					)
					pAura->Remove();
			}
		}break;
		/*************************
		* DRUID SPELLS
		*************************
		* IDs:
		* 34297 Improved Leader of the Pack RANK 1		STATUS: DONE
		* 34300 Improved Leader of the Pack RANK 2		STATUS: DONE
		*  --------------------------------------------
		*************************/

		/*
		Improved Leader of the Pack
		Your Leader of the Pack ability also causes affected targets to have a X% chance to heal themselves for X% of their total health when they critically hit with a melee or ranged attack.  The healing effect cannot occur more than once every 6 sec.

		Effect #1	Apply Aura: Add Flat Modifier (12)
		Value: X
		Effect #2	Dummy
		Value: 100
		*/
	case 34297:
	case 34300:
		{
			if (!u_caster->IsPlayer())
				return;
			ProcTriggerSpell ILotP;
			ILotP.origId = 34299;
			ILotP.spellId = 34299;
			ILotP.procChance = 100;
			ILotP.procFlags = PROC_ON_CRIT_ATTACK | static_cast<uint32>(PROC_TARGET_SELF);
#ifndef NEW_PROCFLAGS
			ILotP.ProcType = 0;
#endif
			ILotP.procCharges = 0;
			ILotP.deleted = false;
			ILotP.caster = u_caster->GetGUID();
			ILotP.LastTrigger = 0;
			ILotP.groupRelation[0] = 0;
			ILotP.groupRelation[1] = 0;
			ILotP.groupRelation[2] = 0;
			u_caster->m_procSpells.push_back(ILotP);
		}break;
		/*************************
		* HUNTER SPELLS
		*************************
		* IDs:
		* 35029 Focused Fire RANK 1		STATUS: ToDo
		* 35030 Focused Fire RANK 2		STATUS: ToDo
		*  --------------------------------------------
		*************************/

		/*
		Focused Fire
		All damage caused by you is increased by 1% while your pet is active and the critical strike chance of your Kill Command ability is increased by 10%.

		Effect #1	Dummy
		Value: 1

		Effect #2	Apply Aura: Add Flat Modifier (7)
		Value: 10

		*/
		//	case 35029:
		//	case 35030:
		//		{
		//		}break;

		// Aspect of the Viper
		//	case 34074:
		// 		{
		// included in the dummy aura for simplicity
		// 		}break;

		/*************************
		* PALADIN SPELLS
		*************************
		* IDs:
		* 31789 Righteous Defense		STATUS: DONE
		*  --------------------------------------------
		* 18350 illumination			STATUS: DONE
		*  --------------------------------------------
		*************************/

		/*
		Righteous Defense
		Come to the defense of a friendly target, commanding up to 3 enemies attacking the target to attack the Paladin instead.

		Effect #1	Dummy
		Radius: 5 yards

		Effect #2	Trigger Spell
		Spell #31980
		*/
	case 31789:
		{
			//we will try to lure 3 enemies from our target
			if(!unitTarget || !u_caster)
				break;
			Unit *targets[3];
			int targets_got=0;
			for(std::set<Object*>::iterator itr = unitTarget->GetInRangeSetBegin(), i2; itr != unitTarget->GetInRangeSetEnd(); )
			{
				i2 = itr++;
				// don't add objects that are not units and that are dead
				if((*i2)->GetTypeId()!= TYPEID_UNIT || !static_cast<Unit*>( (*i2) )->isAlive())
					continue;

				Creature *cr= static_cast<Creature*>((*i2));
				if(cr->GetAIInterface()->GetNextTarget()==unitTarget)
					targets[targets_got++]=cr;
				if(targets_got==3)
					break;
			}
			for(int i=0;i<targets_got;i++)
			{
				//set threat to this target so we are the msot hated
				uint32 threat_to_him = targets[i]->GetAIInterface()->getThreatByPtr( unitTarget );
				uint32 threat_to_us = targets[i]->GetAIInterface()->getThreatByPtr(u_caster);
				int threat_dif = threat_to_him - threat_to_us;
				if(threat_dif>0)//should nto happen
					targets[i]->GetAIInterface()->modThreatByPtr(u_caster,threat_dif);
				targets[i]->GetAIInterface()->AttackReaction(u_caster,1,0);
				targets[i]->GetAIInterface()->SetNextTarget(u_caster);
			}
		}break;
		/*
		Illumination
		After getting a critical effect from your Flash of Light, Holy Light, or Holy Shock heal spell, gives you a X% chance to gain mana equal to 60% of the base cost of the spell.

		Effect #1	Apply Aura: Proc Trigger Spell
		Proc chance: 20%
		Spell #18350 <-- THIS SPELL
		Effect #2	Apply Aura: Override Class Scripts (2689)
		Value: 60
		*/
	case 18350:
		{
			switch( m_triggeredByAura==NULL ? pSpellId : m_triggeredByAura->GetSpellId() )
			{
			case 20210:
			case 20212:
			case 20213:
			case 20214:
			case 20215:
				{
					if( p_caster == NULL )
						return;
					SpellEntry * sp = p_caster->last_heal_spell ? p_caster->last_heal_spell : GetProto();
					p_caster->Energize( p_caster, 20272, 60 * u_caster->GetUInt32Value( UNIT_FIELD_BASE_MANA ) * sp->ManaCostPercentage / 10000, POWER_TYPE_MANA );
				}break;
			case 38443:
				{
					// Shaman - Skyshatter Regalia - Two Piece Bonus
					// it checks for earth, air, water, fire totems and triggers Totemic Mastery spell 38437.
					if(!p_caster) return;
					if(p_caster->m_TotemSlots[0] && p_caster->m_TotemSlots[1] && p_caster->m_TotemSlots[2] && p_caster->m_TotemSlots[3])
					{
						Aura *aur = AuraPool.PooledNew();
						if (!aur)
							return;
						aur->Init(dbcSpell.LookupEntry(38437), 5000, p_caster, p_caster, true);
						for( uint32 i=0; i<3; i++ )
							aur->AddMod( aur->GetSpellProto()->EffectApplyAuraName[i], aur->GetSpellProto()->EffectBasePoints[i]+1, aur->GetSpellProto()->EffectMiscValue[i], i );
						p_caster->AddAura(aur);
					}
				}break;
			default:
				return;
			}
		}break;
	//Judgements of the Wise
	case 54180:
		{
			if(!p_caster)
				break;

			p_caster->Energize(p_caster, 31930, uint32(0.15f*p_caster->GetUInt32Value(UNIT_FIELD_BASE_MANA)), POWER_TYPE_MANA );
			p_caster->CastSpell(p_caster, 57669, false);
		}break;

    // Disengage 
    case 781:
		{
	 		if(!p_caster)
				break;

			WorldPacket data(SMSG_MOVE_KNOCK_BACK, 50);
			data << p_caster->GetNewGUID();
		    data << getMSTime();
		    data << -cosf(p_caster->GetOrientation()) << -sinf(p_caster->GetOrientation());
			data << float(10.0f);
		    data << float(-10.0f);
		    p_caster->GetSession()->SendPacket(&data);
        }break;

		/*************************
		* PRIEST SPELLS
		*************************
		* IDs:
		* 34433 Shadowfiend	STATUS: ToDo
		*  --------------------------------------------
		*************************/
		/*
		Creates a shadowy fiend to attack the target.  Caster receives mana when the Shadowfiend deals damage.  Lasts 15 sec.
		Effect #1	Summon (19668)
		Effect #2	Trigger Spell
		Spell #41967 <--- THIS SPELL
		*/
		/*case 41967:
		{
		}break;
		*/
		// Penance
	case 47540:
		{
			if( unitTarget )
			{
				u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, unitTarget->GetGUID());
				u_caster->SetUInt32Value(UNIT_CHANNEL_SPELL, m_spellInfo->Id);
				sEventMgr.AddEvent(u_caster, &Unit::StopChannel, EVENT_UNK,2000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			}
			if( isAttackable( u_caster, unitTarget) )
				sEventMgr.AddEvent(unitTarget, &Unit::DealDamageWithPenance, m_spellInfo->Id, (uint32)240, EVENT_AURA_PERIODIC_HEAL,1000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			else
				sEventMgr.AddEvent(unitTarget, &Unit::Heal, unitTarget, m_spellInfo->Id, (uint32)756,EVENT_AURA_PERIODIC_HEAL,1000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}break;
	case 53005:
		{
			if( unitTarget )
			{
				u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, unitTarget->GetGUID());
				u_caster->SetUInt32Value(UNIT_CHANNEL_SPELL, m_spellInfo->Id);
				sEventMgr.AddEvent(u_caster, &Unit::StopChannel, EVENT_UNK,2000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			}
			if( isAttackable( u_caster, unitTarget) )
				sEventMgr.AddEvent(unitTarget, &Unit::DealDamageWithPenance, m_spellInfo->Id, (uint32)292, EVENT_AURA_PERIODIC_HEAL,1000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			else
				sEventMgr.AddEvent(unitTarget, &Unit::Heal, unitTarget, m_spellInfo->Id, (uint32)909,EVENT_AURA_PERIODIC_HEAL,1000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}break;
	case 53006:
		{
			if( unitTarget )
			{
				u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, unitTarget->GetGUID());
				u_caster->SetUInt32Value(UNIT_CHANNEL_SPELL, m_spellInfo->Id);
				sEventMgr.AddEvent(u_caster, &Unit::StopChannel, EVENT_UNK,2000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			}
			if( isAttackable( u_caster, unitTarget) )
				sEventMgr.AddEvent(unitTarget, &Unit::DealDamageWithPenance, m_spellInfo->Id, (uint32)333, EVENT_AURA_PERIODIC_HEAL,1000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			else
				sEventMgr.AddEvent(unitTarget, &Unit::Heal, unitTarget, m_spellInfo->Id, (uint32)1442,EVENT_AURA_PERIODIC_HEAL,1000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}break;
	case 53007:
		{
			if( unitTarget )
			{
				u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, unitTarget->GetGUID());
				u_caster->SetUInt32Value(UNIT_CHANNEL_SPELL, m_spellInfo->Id);
				sEventMgr.AddEvent(u_caster, &Unit::StopChannel, EVENT_UNK,2000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			}
			if( isAttackable( u_caster, unitTarget) )
				sEventMgr.AddEvent(unitTarget, &Unit::DealDamageWithPenance, m_spellInfo->Id, (uint32)375, EVENT_AURA_PERIODIC_HEAL,1000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			else
				sEventMgr.AddEvent(unitTarget, &Unit::Heal, unitTarget, m_spellInfo->Id, (uint32)1676,EVENT_AURA_PERIODIC_HEAL,1000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}break;
		// Holy Shock
	case 20473:
		{
			if( isAttackable( u_caster, unitTarget) )
				u_caster->DealDamage( unitTarget, 340, 0, 0, m_spellInfo->Id );
			else
				u_caster->Heal(unitTarget, 519, m_spellInfo->Id);
		}break;
	case 20929:
		{
			if( isAttackable( u_caster, unitTarget) )
				u_caster->DealDamage( unitTarget, 465, 0, 0, m_spellInfo->Id );
			else
				u_caster->Heal(unitTarget, 696, m_spellInfo->Id);
		}break;
	case 20930:
		{
			if( isAttackable( u_caster, unitTarget) )
				u_caster->DealDamage( unitTarget, 608, 0, 0, m_spellInfo->Id );
			else
				u_caster->Heal(unitTarget, 915, m_spellInfo->Id);
		}break;
	case 27174:
		{
			if( isAttackable( u_caster, unitTarget) )
				u_caster->DealDamage( unitTarget, 749, 0, 0, m_spellInfo->Id );
			else
				u_caster->Heal(unitTarget, 1149, m_spellInfo->Id);
		}break;
	case 33072:
		{
			if( isAttackable( u_caster, unitTarget) )
				u_caster->DealDamage( unitTarget, 978, 0, 0, m_spellInfo->Id );
			else
				u_caster->Heal(unitTarget, 1362, m_spellInfo->Id);
		}break;
	case 48824:
		{
			if( isAttackable( u_caster, unitTarget) )
				u_caster->DealDamage( unitTarget, 1129, 0, 0, m_spellInfo->Id );
			else
				u_caster->Heal(unitTarget, 2235, m_spellInfo->Id);
		}break;
	case 48825:
		{
			if( isAttackable( u_caster, unitTarget) )
				u_caster->DealDamage( unitTarget, 1402, 0, 0, m_spellInfo->Id );
			else
				u_caster->Heal(unitTarget, 2599, m_spellInfo->Id);
		}break;
		/*************************
		* SHAMAN SPELLS
		*************************
		* IDs:
		* NO SPELLS
		*  --------------------------------------------
		*************************/

		/*************************
		* WARLOCK SPELLS
		*************************
		* IDs:
		* 19028 Soul Link				STATUS: ToDo
		*  --------------------------------------------
		* 19028 soul link effect		STATUS: DONE
		*  --------------------------------------------
		*************************/

		/*
		Soul Link
		When active, 20% of all damage taken by the caster is taken by your Imp, Voidwalker, Succubus, Felhunter, Felguard, or enslaved demon instead.  That damage cannot be prevented.  In addition, both the demon and master will inflict 5% more damage.  Lasts as long as the demon is active and controlled.

		Effect	Dummy
		*/

		//	case 19028:
		//		{
		//		}break;

		/*
		Soul Link - EFFECT
		20% of damage taken by master is split with demon. All damage increased by 5%.
		*/
	case 48020:
		{
			if( !p_caster )
				return;
		
			GameObject * DemonicCircle = p_caster->GetMapMgr()->GetGameObject( p_caster->m_ObjectSlots[1] );
			if( DemonicCircle )
			{
				if( DemonicCircle->GetDistance2dSq(p_caster) > 40.0f )
					p_caster->SendCastResult(48020, SPELL_FAILED_OUT_OF_RANGE, 0, 0);
				else
					p_caster->SafeTeleport( DemonicCircle->GetMapId(), DemonicCircle->GetInstanceID(), DemonicCircle->GetPosition()); //ok, wat u fixed? u understand? yah thanks :D

			}
		}break;
	case 25228:
		{
			if(!u_caster || !u_caster->isAlive() || !unitTarget || !unitTarget->isAlive())
				return;
			uint32 pet_dmg = this->forced_basepoints[0]*20/100;
			if( pet_dmg )
			{
				unitTarget->ModUnsigned32Value(UNIT_FIELD_HEALTH,pet_dmg);
				unitTarget->DealDamage(u_caster,pet_dmg,0,0,25228,true);
			}
		}break;
	
	/************************
	Death Knight Spells
	*************************/
	case 48982: //Rune Tap
		 {
            p_caster->SetUInt32Value(UNIT_FIELD_HEALTH,( uint32 )((p_caster->GetUInt32Value(UNIT_FIELD_HEALTH))+(p_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH)) / 10 ));
	     }break;

	case 46584:
		{
			if(p_caster	!= NULL)
			{
				float x = p_caster->GetPositionX()+rand()%25;
				float y = p_caster->GetPositionY()+rand()%25;
				float z = p_caster->GetPositionZ();
				SpellEntry *ghoulSpell = dbcSpell.LookupEntryForced(52150);
				if(corpseTarget) // We are targeting a corpse.
				{
					x = corpseTarget->GetPositionX();
					y = corpseTarget->GetPositionY();
					z = corpseTarget->GetPositionZ();
				}
				p_caster->CastSpellAoF(x,y,z,ghoulSpell,true );
				CreatureInfo * ci = CreatureNameStorage.LookupEntry(26125);
				CreatureProto * cp = CreatureProtoStorage.LookupEntry(26125);
				if( !ci || !cp )
					return;

				LocationVector *vec = new LocationVector(x,y,z);
				Pet *summon = objmgr.CreatePet(26125);
				summon->SetPower( POWER_TYPE_ENERGY, (uint32)100 );
				summon->SetUInt32Value( UNIT_FIELD_POWER4, (uint32)100 );
				if(p_caster->HasSpell(52143))
				{
					summon->CreateAsSummon(26125, ci, NULL, p_caster, GetProto(), 6, 0, vec); // considered pet
					summon->AddSpell(dbcSpell.LookupEntry(47481), true); // Gnaw
					summon->AddSpell(dbcSpell.LookupEntry(47482), true); // Leap
					summon->AddSpell(dbcSpell.LookupEntry(47484), true); // Huddle
					summon->AddSpell(dbcSpell.LookupEntry(47468), true); // Claw
				}
				else
				{
					summon->CreateAsSummon(26125, ci, NULL, p_caster, GetProto(), 6, 120, vec); // 2 min duration
				}
				summon->CastSpell(summon,50142,true);
				if(vec) delete vec;

			}
		}break;
	case 49576: //Death grip
		{
			if(!u_caster || !u_caster->isAlive() || !unitTarget || !unitTarget->isAlive())
				return;

			if(unitTarget->IsPlayer())
			{

				Player *playerTarget = static_cast<Player*>(unitTarget);

				if(playerTarget->m_CurrentTransporter) // Blizzard screwed this up, so we won't.
					return;

				SpellEffectPlayerPull(i);

				return;
			}
			else
			{

				float posX, posY, posZ;
				float deltaX,deltaY;
				if(u_caster->GetPositionX() == 0.0f || u_caster->GetPositionY() == 0.0f)
					return;
				deltaX = u_caster->GetPositionX()-unitTarget->GetPositionX();
				deltaY = u_caster->GetPositionY()-unitTarget->GetPositionY();
				if(deltaX == 0.0f || deltaY == 0.0f)
					return;
				float d = sqrt(deltaX*deltaX+deltaY*deltaY)-u_caster->GetFloatValue(UNIT_FIELD_BOUNDINGRADIUS)-unitTarget->GetFloatValue(UNIT_FIELD_BOUNDINGRADIUS);
				float alpha = atanf(deltaY/deltaX);
				if(deltaX<0)
					alpha += float(M_PI);

				posX = d*cosf(alpha)+unitTarget->GetPositionX();
				posY = d*sinf(alpha)+unitTarget->GetPositionY();
				posZ = u_caster->GetPositionZ();

				uint32 time = uint32( (unitTarget->CalcDistance(m_caster) / ((unitTarget->m_runSpeed * 3.5) * 0.001f)) + 0.5);

				WorldPacket data(SMSG_MONSTER_MOVE, 60);
				data << unitTarget->GetNewGUID();
				data << uint8(0); //VLack: the usual change in SMSG_MONSTER_MOVE packets, initial idea from Mangos
				data << unitTarget->GetPositionX();
				data << unitTarget->GetPositionY();
				data << unitTarget->GetPositionZ();
				data << getMSTime();
				data << uint8(0x00);
				data << uint32(0x00001000);
				data << time;
				data << uint32(1);
				data << posX << posY << posZ;
				if(unitTarget->GetTypeId() == TYPEID_UNIT)
					unitTarget->GetAIInterface()->StopMovement(2000);

				unitTarget->SendMessageToSet(&data, true);

				unitTarget->SetPosition(posX,posY,posZ,alpha,true);
				unitTarget->addStateFlag(UF_ATTACKING);
				unitTarget->smsg_AttackStart( unitTarget );
				unitTarget->setAttackTimer(time, false);
				unitTarget->setAttackTimer(time, true);
				unitTarget->GetAIInterface()->taunt(u_caster,true);
			}
		}break;
		/*************************
		Non-Class spells
		- Done
		*************************/
		/*
		Poultryizer
		Turns the target into a chicken for 15 sec.   Well, that is assuming the transmogrification polarity has not been reversed...
		*/
	case 30507:
		{
			if( !unitTarget || !unitTarget->isAlive())
				return;

			u_caster->CastSpell(unitTarget->GetGUID(),30501,true);
		}break;
		/*
		Six Demon Bag
		Blasts enemies in front of you with the power of wind, fire, all that kind of thing!
		*/
	case 14537:
		{
			if( !unitTarget || !unitTarget->isAlive())
				return;

			uint32 ClearSpellId[6] = { 8401,8408,930,118,1680,10159 };
			int min = 1;
			uint32 effect = min + int( ((6-min)+1) * rand() / (RAND_MAX + 1.0) );

			u_caster->CastSpell(unitTarget, ClearSpellId[effect] ,true);
		}break;

	case 30427: // Extract Gas
		{
			bool check = false;
			uint32 cloudtype = 0;
			Creature *creature = 0;

			if(!p_caster)
				return;

			for(Object::InRangeSet::iterator i = p_caster->GetInRangeSetBegin(); i != p_caster->GetInRangeSetEnd(); ++i)
			{
				if((*i)->GetTypeId() == TYPEID_UNIT)
				{
					creature=static_cast<Creature *>((*i));
					cloudtype=creature->GetEntry();
					if(cloudtype == 24222 || cloudtype == 17408 || cloudtype == 17407 || cloudtype == 17378)
					{
						if(p_caster->GetDistance2dSq((*i)) < 400)
						{
							p_caster->SetSelection(creature->GetGUID());
							check = true;
							break;
						}
					}
				}
			}

			if(check)
			{
				uint32 item, count = 0;
				item = count = 3+(rand()%3);

				if (cloudtype==24222) item=22572;//-air
				if (cloudtype==17408) item=22576;//-mana
				if (cloudtype==17407) item=22577;//-shadow
				if (cloudtype==17378) item=22578;//-water

				Item *add = p_caster->GetItemInterface()->FindItemLessMax(item, count, false);
				if (!add)
				{
					ItemPrototype* proto = ItemPrototypeStorage.LookupEntry(item);
					SlotResult slotresult;

					slotresult = p_caster->GetItemInterface()->FindFreeInventorySlot(proto);
					if(!slotresult.Result)
					{
						p_caster->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, INV_ERR_INVENTORY_FULL);
						return;
					}
					Item * it=objmgr.CreateItem(item,p_caster);
					if (it==NULL)
						return;

					it->SetUInt32Value( ITEM_FIELD_STACK_COUNT, count);
					p_caster->GetItemInterface()->SafeAddItem(it,slotresult.ContainerSlot, slotresult.Slot);
					creature->Despawn(3500,creature->GetProto()->RespawnTime);
				}
				else
				{
					add->SetCount(add->GetUInt32Value(ITEM_FIELD_STACK_COUNT) + count);
					add->m_isDirty = true;
					creature->Despawn(3500,creature->GetProto()->RespawnTime);
				}
			}
		}break;

		//curse of agony(18230) = periodic damage increased in
		//flag 2031678
		/*	case 34120:
		{//steady shot
		if(unitTarget)
		if(unitTarget->IsDazed())
		{
		//			u_caster->SpellNonMeleeDamageLog(unitTarget,spellId,damage,false);
		u_caster->SpellNonMeleeDamageLog(unitTarget,spellId,damage,pSpellId==0);
		}

		}break;*/
	case 1454://life tap
	case 1455:
	case 1456:
	case 11687:
	case 11688:
	case 11689:
	case 27222:
	case 57946:
		{//converts base+1+spirit*x points of health into mana
			if(!p_caster || !playerTarget)
				return;

			uint32 mod;	// spirit bonus coefficient multiplied by 2
			if(m_spellInfo->Id == 1454) mod = 2;
			else if(m_spellInfo->Id == 1455) mod = 3;
			else if(m_spellInfo->Id == 1456) mod = 4;
			else if(m_spellInfo->Id == 11687) mod = 5;
			else mod = 6;

			uint32 damage = m_spellInfo->EffectBasePoints[i] + 1 + mod * playerTarget->GetUInt32Value(UNIT_FIELD_STAT4) / 2;
			if (damage >= playerTarget->GetUInt32Value(UNIT_FIELD_HEALTH))
				return;
			p_caster->DealDamage(playerTarget,damage,0,0,spellId);
			damage = damage * (100 + playerTarget->m_lifetapbonus) / 100;	// Apply improved life tap
			if(playerTarget->GetUInt32Value(UNIT_FIELD_POWER1)+damage > playerTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1))
				playerTarget->SetUInt32Value(UNIT_FIELD_POWER1,playerTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1));
			else
				playerTarget->SetUInt32Value(UNIT_FIELD_POWER1,playerTarget->GetUInt32Value(UNIT_FIELD_POWER1)+damage);
			SendHealManaSpellOnPlayer(p_caster, playerTarget, damage, POWER_TYPE_MANA);
		}break;
	case 28730: //Arcane Torrent (Mana)
		{
			// for each mana tap, gives you (2.17*level+9.136) mana
			if( !unitTarget || !p_caster)
				return;

			if(!unitTarget->isAlive() || unitTarget->getClass()==WARRIOR || unitTarget->getClass() == ROGUE)
				return;

			uint32 count = 0;
			for(uint32 x = MAX_NEGATIVE_AURAS_EXTEDED_START; x < MAX_NEGATIVE_AURAS_EXTEDED_END; ++x)
				if(unitTarget->m_auras[x] && unitTarget->m_auras[x]->GetSpellId() == 28734)
				{
					unitTarget->m_auras[x]->Remove();
					++count;
				}

				uint32 gain = (uint32)(count * (2.17*p_caster->getLevel()+9.136));
				p_caster->Energize( unitTarget, 28730, gain, POWER_TYPE_MANA );
		}break;
	case 974:
	case 32593:
	case 32594:
	case 49283:
	case 49284:
		{
			if(!pSpellId)
				return;
			SpellEntry *spellInfo = dbcSpell.LookupEntry(pSpellId);
			if(!spellInfo)
				return;
			uint32 heal32 = CalculateEffect(i,u_caster);
			unitTarget = u_caster;
			if(heal32)
				Heal(heal32);
		}break;
	case 20425: //Judgement of Command
	case 20961: //Judgement of Command
	case 20962: //Judgement of Command
	case 20967: //Judgement of Command
	case 20968: //Judgement of Command
	case 27172: //Judgement of Command
		{
			uint32 SpellID = GetProto()->EffectBasePoints[i]+1;
			Spell * spell = SpellPool.PooledNew();
			if (!spell)
				return;
			spell->Init(m_caster,dbcSpell.LookupEntry(SpellID),true,NULL);
			SpellCastTargets targets;
			targets.m_unitTarget = unitTarget->GetGUID();
			spell->prepare(&targets);
		}break;

	case 20577:// Cannibalize
		{
			if(!p_caster)
				return;
			bool check = false;
			float rad = GetRadius(i);
			rad *= rad;
			for(Object::InRangeSet::iterator i = p_caster->GetInRangeSetBegin(); i != p_caster->GetInRangeSetEnd(); ++i)
			{
				if((*i)->GetTypeId() == TYPEID_UNIT)
				{
					if(static_cast<Creature *>((*i))->getDeathState() == CORPSE)
					{
						CreatureInfo *cn = static_cast<Creature *>((*i))->GetCreatureInfo();
						if(cn && ( cn->Type == UNIT_TYPE_HUMANOID || cn->Type == UNIT_TYPE_UNDEAD ) )
						{
							if(p_caster->GetDistance2dSq((*i)) < rad)
							{
								check = true;
								break;
							}
						}

					}
				}
			}

			if(check)
			{
				p_caster->cannibalize = true;
				p_caster->cannibalizeCount = 0;
				sEventMgr.AddEvent(p_caster, &Player::EventCannibalize, uint32(7),
					EVENT_CANNIBALIZE, 2000, 5,0);
				p_caster->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_CANNIBALIZE);
			}
		}break;
	case 23074:// Arcanite Dragonling
	case 23075:// Mithril Mechanical Dragonling
	case 23076:// Mechanical Dragonling
	case 23133:// Gnomish Battle Chicken
		{
			uint32 spell_id;
			switch(GetProto()->Id)
			{
			case 23074: spell_id = 19804; break;
			case 23075: spell_id = 12749; break;
			case 23076: spell_id =  4073; break;
			case 23133: spell_id = 13166; break;
			default:
				return;
			}
			u_caster->CastSpell(u_caster,spell_id,true);
		}break;
	case 23725:// Gift of Life
		{
			if(!playerTarget)
				break;

			SpellCastTargets tgt;
			tgt.m_unitTarget = playerTarget->GetGUID();
			SpellEntry * inf = dbcSpell.LookupEntry(23782);
			Spell * spe = SpellPool.PooledNew();
			if (!spe)
				return;
			spe->Init(u_caster,inf,true,NULL);
			spe->prepare(&tgt);

		}break;
	case 12975:// Last Stand
		{
			if(!playerTarget)
				break;
			SpellCastTargets tgt;
			tgt.m_unitTarget = playerTarget->GetGUID();
			SpellEntry * inf =dbcSpell.LookupEntry(12976);
			Spell * spe = SpellPool.PooledNew();
			if (!spe)
				return;
			spe->Init(u_caster,inf,true,NULL);
			spe->prepare(&tgt);
		}break;
		/*************************
		Non-Class spells
		- ToDo
		*************************/
	case 6668:// Red Firework
		{
			// Shoots a firework into the air that bursts into a thousand red stars
		}break;
	case 8344:// Universal Remote
		{
			//FIXME:Allows control of a mechanical target for a short time.  It may not always work and may just root the machine or make it very very angry.  Gnomish engineering at its finest.
		}break;
	case 9976:// Polly Eats the E.C.A.C.
		{
			//FIX ME: Don't know what this does
		}break;
	case 10137:// Fizzule's Whistle
		{
			//FIXME:Blow on the whistle to let Fizzule know you're an ally
			//This item comes after a finish of quest at venture co.
			//You must whistle this every time you reach there to make Fizzule
			//ally to you.
		}break;
	case 11540:// Blue Firework
		{
			//Shoots a firework into the air that bursts into a thousand blue stars
		}break;
	case 11541:// Green Firework
		{
			//Shoots a firework into the air that bursts into a thousand green stars
		}break;
	case 11542:// Red Streaks Firework
		{
			//Shoots a firework into the air that bursts into a thousand red streaks
		}break;
	case 11543:// Red, White and Blue Firework
		{
			//Shoots a firework into the air that bursts into red, white and blue stars
		}break;
	case 11544:// Yellow Rose Firework
		{
			//Shoots a firework into the air that bursts in a yellow pattern
		}break;
	case 12151:// Summon Atal'ai Skeleton
		{
			//8324	Atal'ai Skeleton

			//FIXME:Add here remove in time event
		}break;
	case 13006:// Shrink Ray
		{
			//FIXME:Schematic is learned from the gnomish engineering trainer. The gnomish/gobblin engineering decision is made when you are lvl40+ and your engineering is 200+. Interestingly, however, when this item fails to shrink the target, it can do a variety of things, such as...
			//-Make you bigger (attack power +250)
			//-Make you smaller (attack power -250)
			//-Make them bigger (same effect as above)
			//-Make your entire party bigger
			//-Make your entire party smaller
			//-Make every attacking enemy bigger
			//-Make ever attacking enemy smaller
			//Works to your advantage for the most part (about 70% of the time), but don't use in high-pressure situations, unless you're going to die if you don't. Could tip the scales the wrong way.
			//Search for spells of this


			//13004 - grow <- this one
			//13010 - shrink <-this one
			//
		}break;
	case 13180:// Gnomish Mind Control Cap
		{
			// FIXME:Take control of humanoid target by chance(it can be player)
		}break;
	case 13278:// Gnomish Death Ray
		{
			// FIXME:The devices charges over time using your life force and then directs a burst of energy at your opponent
			//Drops life
		}break;
	case 13280:// Gnomish Death Ray
		{
			//FIX ME: Drop life
		}break;
	case 17816:// Sharp Dresser
		{
			//Impress others with your fashion sense
		}break;
	case 21343:// Snowball
		{
		}break;
	case 23645:// Hourglass Sand
		{
			//Indeed used at the Chromo fight in BWL. Chromo has a stunning debuff, uncleansable, unless you have hourglass sand. This debuff will stun you every 4 seconds, for 4 seconds. It is resisted a lot though. Mage's and other casters usually have to do this fight with the debuff on, healers, tanks and hunters will get some to cure themselves from the debuff
		}break;
	case 24325:// Pagle's Point Cast - Create Mudskunk Lure
		{
			//FIXME:Load with 5 Zulian Mudskunks, and then cast from Pagle's Point in Zul'Gurub
		}
	case 24392:// Frosty Zap
		{
			//FIXME:Your Frostbolt spells have a 6% chance to restore 50 mana when cast.
			//damage == 50
		}break;
	case 25822:// Firecrackers
		{
			//FIXME:Find firecrackers
		}break;
	case 26373:// Lunar Invitation
		{
			//FIX ME: Teleports the caster from within Greater Moonlight
		}break;
	case 26374:// Elune's Candle
		{
			//FIXME:Shoots a firework at target
		}break;
	case 26889:// Give Friendship Bracelet
		{
			//Give to a Heartbroken player to cheer them up
			//laugh emote
		}break;
	case 27662:// Throw Cupid's Dart
		{
			//FIXME:Shoot a player, and Kwee Q. Peddlefeet will find them! (Only works on players with no current critter pets.)
		}break;
	case 28414:// Call Ashbringer
		{
			//http://www.thottbot.com/?i=53974
		}break;
	case 28806:// Toss Fuel on Bonfire
		{
			//FIXME:Dont know what this dummy does
		}break;
	case 7669:// Bethor's Potion
		{
			// related to Hex of Ravenclaw,
			// its a dispell spell.
			//FIXME:Dont know what's the usage of this dummy
		}break;
	case 8283:// Snufflenose Command
		{
			//FIXME:Quest Blueleaf Tubers
			//For use on a Snufflenose Gopher
		}break;
	case 8913:// Sacred Cleansing
		{
			//FIXME:Removes the protective enchantments around Morbent Fel
			//Quest Morbent Fel
		}break;
	case 9962://Capture Treant
		{
			//Quest Treant Muisek
		}break;
	case 10113:// Flare Gun's flare
		{
			//FIXME:Quest Deep Cover
			//1543 may need to cast this
			//2 flares and the /salute
		}break;
	case 10617:// Release Rageclaw
		{
			//Quest Druid of the Claw
			//Use on the fallen body of Rageclaw
		}break;
	case 11402:// Shay's Bell
		{
			//FIXME:Quest Wandering Shay
			//Ring to call Shay back to you
		}break;
	case 11548:// Summon Spider God
		{
			//FIXME:Quest Summoning Shadra  (Elite)
			//Use at the Shadra'Alor Altar to summon the spider god
		}break;
	case 11610:// Gammerita Turtle Camera
		{
			//Quest The Super Snapper FX
		}break;
	case 11886:// Capture Wildkin
		{
			//Quest Testing the Vessel
			//Shrink and Capture a Fallen Wildkin
		}break;
	case 11887:// Capture Hippogryph
		{
			//FIXME:Same with 11888
			//Quest Hippogryph Muisek
		}break;
	case 11888:// Capture Faerie Dragon
		{
			//FIXME:Check Faerie Dragon Muisek is killed or not if its killed update quest
			//And allow create of fearie Dragon which is effect 1
			//Quest: Faerie Dragon Muisek
		}break;
	case 11889:// Capture Mountain Giant
		{
			//FIXME:Same with 11888
			//Quest: Mountain Giant Muisek
		}break;
	case 12189:// Summon Echeyakee
		{
			//3475	Echeyakee

			//FIXME:Quest Echeyakee
		}break;
	case 12283:// Xiggs Signal Flare
		{
			//Quest Signal for Pickup
			//To be used at the makeshift helipad in Azshara. It will summon Pilot Xiggs Fuselighter to pick up the tablet rubbings
		}break;
	case 12938:// Fel Curse
		{
			//FIXME:Makes near target killable(servants of Razelikh the Defiler)
		}break;
	case 14247:// Blazerunner Dispel
		{
			//FIXME:Quest Aquementas and some more
		}break;
	case 14250:// Capture Grark
		{
			//Quest Precarious Predicament
		}break;
	case 14813:// Rocknot's Ale
		{
			//you throw the mug
			//and the guy gets pissed well everyone gets pissed and he crushes the door so you can get past
			//maybe after like 30 seconds so you can get past.  but like I said I have never done it myself
			//so I am not 100% sure what happens.
		}break;
	case 15991://Revive Ringo
		{
			//Quest A Little Help From My Friends
			//Revive Ringo with water
		}break;
	case 15998:// Capture Worg Pup
		{
			//FIXME:Ends Kibler's Exotic Pets  (Dungeon) quest
		}break;
	case 16031:// Releasing Corrupt Ooze
		{
			//FIXME:Released ooze moves to master ooze and "Merged Ooze Sample"
			//occurs after some time.This item helps to finish quest
		}break;
	case 16378:// Temperature Reading
		{
			//FIXME:Quest Finding the Source
			//Take a reading of the temperature at a hot spot.
		}break;
	case 17166:// Release Umi's Yeti
		{
			//Quest Are We There, Yeti?
			//Select Umi's friend and click to release the Mechanical Yeti
		}break;
	case 17271:// Test Fetid Skull
		{
			//FIXME:Marauders of Darrowshire
			//Wave over a Fetid skull to test its resonance
		}break;
	case 18153:// Kodo Kombobulator
		{
			//FIXME:Kodo Roundup Quest
			//Kodo Kombobulator on any Ancient, Aged, or Dying Kodo to lure the Kodo to follow (one at a time)
		}break;
	case 19250:// Placing Smokey's Explosives
		{
			//This is something related to quest i think
		}break;
	case 19512:// Apply Salve
		{
			//FIXME:Cure a sickly animal afflicted by the taint of poisoning
		}break;
	case 20804:// Triage
		{
			//Quest Triage
			//Use on Injured, Badly Injured, and Critically Injured Soldiers
		}break;
	case 21050:// Melodious Rapture
		{
			//Quest Deeprun Rat Roundup
		}break;
	case 21332:// Aspect of Neptulon
		{
			//FIXME:Used on plagued water elementals in Eastern Plaguelands
			//Quest:Poisoned Water
		}break;
	case 21960:// Manifest Spirit
		{
			//FIXME:Forces the spirits of the first centaur Kahns to manifest in the physical world
			//thats a quest
			//its for maraudon i think
			//u use that on the spirit mobs
			//to release them
		}break;
	case 23359:// Transmogrify!
		{
			//Quest Zapped Giants
			//Zap a Feralas giant into a more manageable form
		}break;
	case 27184:// Summon Mor Grayhoof
		{
			//16044	Mor Grayhoof Trigger
			//16080	Mor Grayhoof

			//Related to quests The Left Piece of Lord Valthalak's Amulet  (Dungeon)
			//and The Right Piece of Lord Valthalak's Amulet  (Dungeon)
		}break;
	case 27190:// Summon Isalien
		{
			//16045	Isalien Trigger
			//16097	Isalien

			//Related to quests The Left Piece of Lord Valthalak's Amulet  (Dungeon)
			//and The Right Piece of Lord Valthalak's Amulet  (Dungeon)
		}break;
	case 27191:// Summon the remains of Jarien and Sothos
		{
			/*
			16046	Jarien and Sothos Trigger
			16101	Jarien
			16103	Spirit of Jarien

			16102	Sothos
			16104	Spirit of Sothos
			*/

			//Related to quests The Left Piece of Lord Valthalak's Amulet  (Dungeon)
			//and The Right Piece of Lord Valthalak's Amulet  (Dungeon)
		}break;
	case 27201:// Summon the spirit of Kormok
		{
			/*16047	Kormok Trigger
			16118	Kormok
			*/
			//Related to quests The Left Piece of Lord Valthalak's Amulet  (Dungeon)
			//and The Right Piece of Lord Valthalak's Amulet  (Dungeon)
		}break;
	case 27202:// Summon Lord Valthalak
		{
			/*
			16042	Lord Valthalak
			16048	Lord Valthalak Trigger
			16073	Spirit of Lord Valthalak

			*/
			//Related to quests The Left Piece of Lord Valthalak's Amulet  (Dungeon)
			//and The Right Piece of Lord Valthalak's Amulet  (Dungeon)
		}break;

	/*case 56671: // Spear of Hodir
		{
		    if(!u_caster->IsPlayer())  return;
			
		    if(apply && unitTarget && unitTarget->GetEntry() == 30275)
			{
			}
		}break;*/

	case 27203:// Summon the spirits of the dead at haunted locations
		{
			//Related to quests The Left Piece of Lord Valthalak's Amulet  (Dungeon)
			//and The Right Piece of Lord Valthalak's Amulet  (Dungeon)
		}break;
	case 27517:// Use this banner at the Arena in Blackrock Depths to challenge Theldren
		{
			//This is used to make Theldren spawn at the place where it used
			//I couldn't find theldrin, and his men in creature names database
			//Someone has to write this and this is related to The Challenge quest
			/*By moving to the center grate, you trigger the arena event.
			A random group of mobs (spiders, worms, bats, raptors) spawns,
			and you have to kill them. After the last one dies, and a small
			break, a boss mob spawns. Successfully completing this event
			turns the arena spectators from red to yellow*/
		}break;
	case 29858: //Soulshatter
		{
			if( !u_caster || !u_caster->isAlive() || !unitTarget || !unitTarget->isAlive() )
				return;

			u_caster->CastSpell(unitTarget, 32835, false);
		}break;

		/***Death Coil DK***/

	case 52375:
	case 49892:
	case 49893:
	case 49894:
	case 49895:
		{
			if( u_caster == NULL || unitTarget == NULL )
				return;
			if( spellId == 52375 )
				damage = damage * 2 / 5;
			if( isAttackable( u_caster, unitTarget, false ) )
				u_caster->SpellNonMeleeDamageLog( unitTarget, spellId, damage, true );
			else if( unitTarget->IsCreature() )
			{
				CreatureInfo * ci = static_cast< Creature* >( unitTarget )->GetCreatureInfo();
				if( ci && ci->Type == UNIT_TYPE_UNDEAD )
					u_caster->Heal( unitTarget, spellId, float2int32( damage * 1.5f ) );
			}
		}break;
	}
}

void Spell::SpellEffectTeleportUnits( uint32 i )  // Teleport Units
{
	if( !unitTarget )
	{
		return;
	}

	uint32 spellId = GetProto()->Id;

	// Try a dummy SpellHandler
	if( sScriptMgr.CallScriptedDummySpell( spellId, i, this ) )
	{
		return;
	}
	if(m_spellInfo->Id == 58867)
	{
		/* this is rather tricky actually. we have to calculate the orientation of the creature/player, and then calculate a little bit of distance behind that. */
		float ang;
		Unit * pTarget = unitTarget;

		if( pTarget->GetTypeId() == TYPEID_UNIT )
		{
			/* We're chasing a target. We have to calculate the angle to this target, this is our orientation. */
			ang = m_caster->calcAngle(m_caster->GetPositionX(), m_caster->GetPositionY(), pTarget->GetPositionX(), pTarget->GetPositionY());

			/* convert degree angle to radians */
			ang = ang * float(M_PI) / 180.0f;
		}
		else
		{
			/* Players orientation is sent in movement packets */
			ang = pTarget->GetOrientation();
		}

		// avoid teleporting into the model on scaled models
		const static float shadowstep_distance = 1.6f * unitTarget->GetModelHalfSize();
		float new_x = pTarget->GetPositionX() - (shadowstep_distance * cosf(ang));
		float new_y = pTarget->GetPositionY() - (shadowstep_distance * sinf(ang));
		float new_z = pTarget->GetPositionZ() + 0.1f;
		if (pTarget->GetMapMgr() && sWorld.Collision)
		{
			float z2 = CollideInterface.GetHeight(pTarget->GetMapId(), pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
			if( z2 == NO_WMO_HEIGHT )
				z2 = p_caster->GetMapMgr()->GetLandHeight(new_x, new_y);

			if( fabs( new_z - z2 ) < 10.0f )
				new_z = z2 + 1.0f;
		}
		
		/* Send a movement packet to "charge" at this target. Similar to warrior charge. */
		u_caster->RemoveFromWorld(false);
		u_caster->SetPosition(new_x, new_y, new_z, unitTarget->GetOrientation());
		u_caster->AddToWorld();
		
		return;
	}

	// Shadowstep
	if( m_spellInfo->NameHash == SPELL_HASH_SHADOWSTEP && p_caster && p_caster->IsInWorld() )
	{
		/* this is rather tricky actually. we have to calculate the orientation of the creature/player, and then calculate a little bit of distance behind that. */
		float ang;
		Unit * pTarget = unitTarget;
		if( pTarget == m_caster )
		{
			/* try to get a selection */
 			pTarget = m_caster->GetMapMgr()->GetUnit(p_caster->GetSelection());
//			if( (unitTarget == NULL ) || !isHostile(p_caster, unitTarget) || (unitTarget->CalcDistance(p_caster) > 25.0f)) //removed by Zack : no idea why hostile is used. Isattackable should give a wider solution range
			if( (pTarget == NULL ) || !isAttackable(p_caster, pTarget, !(m_spellInfo->c_is_flags & SPELL_FLAG_IS_TARGETINGSTEALTHED) ) || (pTarget->CalcDistance(p_caster) > 25.0f))
				return;
		}

		if( pTarget->GetTypeId() == TYPEID_UNIT )
		{
			if( pTarget->GetUInt64Value( UNIT_FIELD_TARGET ) != 0 )
			{
				/* We're chasing a target. We have to calculate the angle to this target, this is our orientation. */
				ang = m_caster->calcAngle(m_caster->GetPositionX(), m_caster->GetPositionY(), pTarget->GetPositionX(), pTarget->GetPositionY());

				/* convert degree angle to radians */
				ang = ang * float(M_PI) / 180.0f;
			}
			else
			{
				/* Our orientation has already been set. */
				ang = pTarget->GetOrientation();
			}
		}
		else
		{
			/* Players orientation is sent in movement packets */
			ang = pTarget->GetOrientation();
		}

		// avoid teleporting into the model on scaled models
		const static float shadowstep_distance = 1.6f * unitTarget->GetModelHalfSize();
		float new_x = pTarget->GetPositionX() - (shadowstep_distance * cosf(ang));
		float new_y = pTarget->GetPositionY() - (shadowstep_distance * sinf(ang));
		float new_z = pTarget->GetPositionZ() + 0.1f;
		if (pTarget->GetMapMgr() && sWorld.Collision)
		{
			float z2 = CollideInterface.GetHeight(pTarget->GetMapId(), pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
			if( z2 == NO_WMO_HEIGHT )
				z2 = p_caster->GetMapMgr()->GetLandHeight(new_x, new_y);

			if( fabs( new_z - z2 ) < 10.0f )
				new_z = z2 + 0.2f;
		}
		
		/* Send a movement packet to "charge" at this target. Similar to warrior charge. */
		p_caster->z_axisposition = 0.0f;
		p_caster->SafeTeleport(p_caster->GetMapId(), p_caster->GetInstanceID(), LocationVector(new_x, new_y, new_z, pTarget->GetOrientation()));
		
		return;
	}

	/* TODO: Remove Player From bg */

	if( unitTarget->GetTypeId() == TYPEID_PLAYER )
	{
		HandleTeleport(spellId, unitTarget);
	}
}

void Spell::SpellEffectApplyAura(uint32 i)  // Apply Aura
{
	if(!unitTarget)
		return;
	// can't apply stuns/fear/polymorph/root etc on boss
	if ( !playerTarget )
	{
		if (u_caster && (u_caster != unitTarget))
		{
			Creature * c = static_cast<Creature *>(unitTarget);
			if (c)
			{

				/*
				Charm (Mind Control, enslave demon): 1
				Confuse (Blind etc): 2
				Fear: 4
				Root: 8
				Silence : 16
				Stun: 32
				Sheep: 64
				Banish: 128
				Sap: 256
				Frozen : 512
				Ensnared 1024
				Sleep 2048
				Taunt (aura): 4096
				Decrease Speed (Hamstring) (aura): 8192
				Spell Haste (Curse of Tongues) (aura): 16384
				Interrupt Cast: 32768
				Mod Healing % (Mortal Strike) (aura): 65536
				Total Stats % (Vindication) (aura): 131072
				*/

				//Spells with Mechanic also add other ugly auras, but if the main aura is the effect --> immune to whole spell
				if (c->GetProto() && c->GetProto()->modImmunities)
				{
					bool immune = false;
					if (m_spellInfo->MechanicsType)
					{
						switch(m_spellInfo->MechanicsType)
						{
						case MECHANIC_CHARMED:
							if (c->GetProto()->modImmunities & 1)
								immune = true;
							break;
						case MECHANIC_DISORIENTED:
							if (c->GetProto()->modImmunities & 2)
								immune = true;
							break;
						case MECHANIC_FLEEING:
							if (c->GetProto()->modImmunities & 4)
								immune = true;
							break;
						case MECHANIC_ROOTED:
							if (c->GetProto()->modImmunities & 8)
								immune = true;
							break;
						case MECHANIC_SILENCED:
							if ( c->GetProto()->modImmunities & 16)
								immune = true;
							break;
						case MECHANIC_STUNNED:
							if (c->GetProto()->modImmunities & 32)
								immune = true;
							break;
						case MECHANIC_POLYMORPHED:
							if (c->GetProto()->modImmunities & 64)
								immune = true;
							break;
						case MECHANIC_BANISHED:
							if (c->GetProto()->modImmunities & 128)
								immune = true;
							break;
						case MECHANIC_SAPPED:
							if (c->GetProto()->modImmunities & 256)
								immune = true;
							break;
						case MECHANIC_FROZEN:
							if (c->GetProto()->modImmunities & 512)
								immune = true;
							break;
						case MECHANIC_ENSNARED:
							if (c->GetProto()->modImmunities & 1024)
								immune = true;
							break;
						case MECHANIC_ASLEEP:
							if (c->GetProto()->modImmunities & 2048)
								immune = true;
							break;
						}
					}
					if (!immune)
					{
						// Spells that do more than just one thing (damage and the effect) don't have a mechanic and we should only cancel the aura to be placed
						switch (m_spellInfo->EffectApplyAuraName[i])
						{
						case SPELL_AURA_MOD_CONFUSE:
							if (c->GetProto()->modImmunities & 2)
								immune = true;
							break;
						case SPELL_AURA_MOD_FEAR:
							if (c->GetProto()->modImmunities & 4)
								immune = true;
							break;
						case SPELL_AURA_MOD_TAUNT:
							if (c->GetProto()->modImmunities & 4096)
								immune = true;
							break;
						case SPELL_AURA_MOD_STUN:
							if (c->GetProto()->modImmunities & 32)
								immune = true;
							break;
						case SPELL_AURA_MOD_SILENCE:
							if ((c->GetProto()->modImmunities & 32768) || (c->GetProto()->modImmunities & 16))
								immune = true;
							break;
						case SPELL_AURA_MOD_DECREASE_SPEED:
							if (c->GetProto()->modImmunities & 8192)
								immune = true;
							break;
						case SPELL_AURA_INCREASE_CASTING_TIME_PCT:
							if (c->GetProto()->modImmunities & 16384)
								immune = true;
							break;
						case SPELL_AURA_MOD_LANGUAGE: //hacky way to prefer that the COT icon is set to mob
							if (c->GetProto()->modImmunities & 16384)
								immune = true;
							break;
						case SPELL_AURA_MOD_HEALING_DONE_PERCENT:
							if (c->GetProto()->modImmunities & 65536)
								immune = true;
							break;
						case SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE:
							if (c->GetProto()->modImmunities & 131072)
								immune = true;
							break;
						}
					}
					if (immune)
						return;
				}
			}
		}
	}

#ifdef GM_Z_DEBUG_DIRECTLY
	else {
		if( unitTarget->IsPlayer() && unitTarget->IsInWorld() && static_cast< Player* >( unitTarget )->GetSession() && static_cast< Player* >( unitTarget )->GetSession()->CanUseCommand('z')  ) {
			sChatHandler.BlueSystemMessage( static_cast< Player* >( unitTarget  )->GetSession(), "[%sSystem%s] |rSpell::SpellEffectApplyAura: %s EffectApplyAuraName [%u] .", MSG_COLOR_WHITE, MSG_COLOR_LIGHTBLUE, MSG_COLOR_SUBWHITE,
				i );
		}
	}
#endif

	// avoid map corruption.
	if(unitTarget->GetInstanceID() != m_caster->GetInstanceID())
		return;

	//check if we already have stronger aura
	Aura *pAura;

	std::map<uint32,Aura*>::iterator itr=unitTarget->tmpAura.find(GetProto()->Id);
	//if we do not make a check to see if the aura owner is the same as the caster then we will stack the 2 auras and they will not be visible client sided
	if(itr == unitTarget->tmpAura.end())
	{
		if( GetProto()->NameHash == SPELL_HASH_BLOOD_FRENZY && this->ProcedOnSpell )//Warrior's Blood Frenzy
			this->GetProto()->DurationIndex = this->ProcedOnSpell->DurationIndex;

		uint32 Duration = this->GetDuration();

		// Handle diminishing returns, if it should be resisted, it'll make duration 0 here.
		if(!(GetProto()->Attributes & ATTRIBUTES_PASSIVE)) // Passive
			::ApplyDiminishingReturnTimer(&Duration, unitTarget, GetProto());

		if(!Duration)
		{
			SendCastResult(SPELL_FAILED_IMMUNE);
			return;
		}

		pAura = AuraPool.PooledNew();
		if ( !pAura )
			return;
		if( g_caster && g_caster->GetUInt32Value(OBJECT_FIELD_CREATED_BY) && g_caster->m_summoner )
			pAura->Init( GetProto(), Duration, g_caster->m_summoner, unitTarget, m_triggeredSpell, i_caster );
		else
			pAura->Init( GetProto(), Duration, m_caster, unitTarget, m_triggeredSpell, i_caster );

		pAura->pSpellId = pSpellId; //this is required for triggered spells

		unitTarget->tmpAura[GetProto()->Id] = pAura;
	}
	else
	{
		pAura=itr->second;
	}
	pAura->AddMod( GetProto()->EffectApplyAuraName[i], damage, GetProto()->EffectMiscValue[i], i );

	switch( GetProto()->Id )
	{
	case 38177: // Blackwhelp Net
		{
			p_caster->CastSpell( unitTarget, 38178, true );
			static_cast<Creature*>(unitTarget)->Despawn( 1000, 360000 );
		} break;
	}

}

void Spell::SpellEffectEnvironmentalDamage(uint32 i)
{
	if(!playerTarget) return;

	if(unitTarget->SchoolImmunityList[GetProto()->School])
	{
		SendCastResult(SPELL_FAILED_IMMUNE);
		return;
	}
	//this is GO, not unit
	m_caster->SpellNonMeleeDamageLog(unitTarget,GetProto()->Id,damage, pSpellId==0);

	WorldPacket data(SMSG_ENVIRONMENTALDAMAGELOG, 13);
	data << unitTarget->GetGUID();
	data << uint8(DAMAGE_FIRE);
	data << uint32(damage);
	unitTarget->SendMessageToSet( &data, true );
}

void Spell::SpellEffectPowerDrain(uint32 i)  // Power Drain
{
	if(!unitTarget || !unitTarget->isAlive())
		return;

	uint32 powerField = UNIT_FIELD_POWER1+GetProto()->EffectMiscValue[i];
	uint32 curPower = unitTarget->GetUInt32Value(powerField);
	if( powerField == UNIT_FIELD_POWER1 && unitTarget->IsPlayer() )
	{
		Player* mPlayer = static_cast< Player* >( unitTarget );
		if( mPlayer->IsInFeralForm() )
			return;

		// Resilience - reduces the effect of mana drains by (CalcRating*2)%.
		damage *= float2int32( 1 - ( ( static_cast<Player*>(unitTarget)->CalcRating( PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE ) * 2 ) / 100.0f ) );
	}
	uint32 amt = damage + ( ( u_caster->GetDamageDoneMod( GetProto()->School ) * 80 ) / 100 );
	if(amt>curPower)
		amt=curPower;
	unitTarget->SetUInt32Value(powerField,curPower-amt);
	u_caster->Energize( u_caster, GetProto()->Id, amt, GetProto()->EffectMiscValue[i] );
}

void Spell::SpellEffectHealthLeech(uint32 i) // Health Leech
{
	if(!unitTarget || !unitTarget->isAlive())
		return;

	uint32 curHealth = unitTarget->GetUInt32Value(UNIT_FIELD_HEALTH);
	uint32 amt = damage;
	if(amt > curHealth)
	{
		amt = curHealth;
	}
	m_caster->DealDamage(unitTarget, damage, 0, 0, GetProto()->Id);

	uint32 playerCurHealth = m_caster->GetUInt32Value(UNIT_FIELD_HEALTH);
	uint32 playerMaxHealth = m_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);

	if(playerCurHealth + amt > playerMaxHealth)
	{
		m_caster->SetUInt32Value(UNIT_FIELD_HEALTH, playerMaxHealth);
	}
	else
	{
		m_caster->SetUInt32Value(UNIT_FIELD_HEALTH, playerCurHealth + amt);
	}
}

void Spell::SpellEffectHeal(uint32 i) // Heal
{
	if(p_caster)	
	{	
		// HACKY but with SM_FEffect2_bonus it doesnt work

		// Apply this only on targets, which have one of paladins auras
		if( unitTarget && (unitTarget->HasAurasWithNameHash(SPELL_HASH_DEVOTION_AURA) || unitTarget->HasAurasWithNameHash(SPELL_HASH_RETRIBUTION_AURA) ||
			unitTarget->HasAurasWithNameHash(SPELL_HASH_CONCENTRATION_AURA) || unitTarget->HasAurasWithNameHash(SPELL_HASH_CRUSADER_AURA) ||  unitTarget->HasAurasWithNameHash(SPELL_HASH_FIRE_RESISTANCE_AURA) ||
			unitTarget->HasAurasWithNameHash(SPELL_HASH_FROST_RESISTANCE_AURA) ||unitTarget->HasAurasWithNameHash(SPELL_HASH_SHADOW_RESISTANCE_AURA)) )		
		{
			if( p_caster->HasSpell( 20140 ) ) // Improved Devotion Aura Rank 3			
				damage = (int32)(damage * 1.06);		
			else if( p_caster->HasSpell( 20139 ) ) // Improved Devotion Aura Rank 2			
				damage = (int32)(damage * 1.04);		
			else if( p_caster->HasSpell( 20138 ) ) // Improved Devotion Aura Rank 1			
				damage = (int32)(damage * 1.02);
		}

		if( p_caster->HasSpell( 54943 ) && p_caster->HasAura( 20165 ) ) // Glyph of Seal of Light
			damage = (int32)(damage * 1.05); 

	}

	if(GetProto()->EffectChainTarget[i])//chain
	{
		if(!chaindamage)
		{
			chaindamage = damage;
			Heal((int32)chaindamage);
		}
		else
		{
			int32 reduce=GetProto()->EffectDieSides[i]+1;
			if(GetProto()->SpellGroupType && u_caster)
			{
				SM_FIValue(u_caster->SM_PJumpReduce,&reduce,GetProto()->SpellGroupType);
			}
			chaindamage -= (reduce * chaindamage) / 100;
			Heal((int32)chaindamage);
		}
	}
	else
	{
		//yep, the usual special case. This one is shaman talent : Nature's guardian
		//health is below 30%, we have a mother spell to get value from
		switch (GetProto()->Id)
		{
		case 31616:
			{
				if(unitTarget && unitTarget->IsPlayer() && pSpellId && unitTarget->GetHealthPct()<30)
				{
					//check for that 10 second cooldown
					SpellEntry *spellInfo = dbcSpell.LookupEntry(pSpellId );
					if(spellInfo)
					{
						//heal value is received by the level of current active talent :s
						//maybe we should use CalculateEffect(uint32 i) to gain SM benefits
						int32 value = 0;
						int32 basePoints = spellInfo->EffectBasePoints[i]+1;//+(m_caster->getLevel()*basePointsPerLevel);
						int32 randomPoints = spellInfo->EffectDieSides[i];
						if(randomPoints <= 1)
							value = basePoints;
						else
							value = basePoints + rand() % randomPoints;
						//the value is in percent. Until now it's a fixed 10%
						Heal(unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH)*value/100);
					}
				}
			}break;
			//Bloodthirst
		case 23880:
			{
				if(unitTarget)
				{
					Heal(unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH)/100);
				}
			}break;

		case 34299: //Druid: Improved Leader of the PAck
			{
				if (!unitTarget->IsPlayer() || !unitTarget->isAlive())
					break;

				Player* mPlayer = static_cast< Player* >( unitTarget );
				if( !mPlayer->IsInFeralForm() || (
					mPlayer->GetShapeShift() != FORM_CAT &&
					mPlayer->GetShapeShift() != FORM_BEAR &&
					mPlayer->GetShapeShift() != FORM_DIREBEAR ) )
					break;
				uint32 max = mPlayer->GetUInt32Value( UNIT_FIELD_MAXHEALTH );
				uint32 val = float2int32( ( ( mPlayer->FindAura( 34300 ) ) ? 0.04f : 0.02f ) * max );
				if (val)
					mPlayer->Heal(mPlayer,34299,(uint32)(val));
			}break;
		case 22845: // Druid: Frenzied Regeneration
			{
				if (!unitTarget->IsPlayer() || !unitTarget->isAlive())
					break;
				Player* mPlayer = static_cast< Player* >( unitTarget );
				if (!mPlayer->IsInFeralForm() ||
					(mPlayer->GetShapeShift() != FORM_BEAR &&
					mPlayer->GetShapeShift() != FORM_DIREBEAR))
					break;
				uint32 val = mPlayer->GetUInt32Value(UNIT_FIELD_POWER2);
				if (val>100)
					val = 100;
				uint32 HpPerPoint = float2int32((mPlayer->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) * 0.003f)); //0.3% of hp per point of rage
				uint32 heal = HpPerPoint * (val/10); //1 point of rage = 0.3% of max hp
				mPlayer->SetUInt32Value(UNIT_FIELD_POWER2,mPlayer->GetUInt32Value(UNIT_FIELD_POWER2)-val);
				if (val)
					mPlayer->Heal(mPlayer,22845,heal);
			}break;
		case 18562: //druid - swiftmend
			{
				if( unitTarget )
				{
					uint32 new_dmg = 0;
					//consume rejuvenetaion and regrowth
					Aura * taura = unitTarget->FindAuraByNameHash( SPELL_HASH_REGROWTH ); //Regrowth
					if( taura && taura->GetSpellProto())
					{
						uint32 amplitude = taura->GetSpellProto()->EffectAmplitude[1] / 1000;
						if( !amplitude )
							amplitude = 3;

						//our hapiness is that we did not store the aura mod amount so we have to recalc it
						Spell *spell = SpellPool.PooledNew();
						if (!spell)
							return;
						spell->Init(m_caster, taura->GetSpellProto(), false, NULL);
						uint32 healamount = spell->CalculateEffect( 1, unitTarget );
						SpellPool.PooledDelete( spell );
						spell = NULL;
						new_dmg = healamount * 18 / amplitude;

						unitTarget->RemoveAura( taura );

						//do not remove flag if we still can cast it again
						if( !unitTarget->HasAurasWithNameHash( SPELL_HASH_REJUVENATION ) )
						{
							unitTarget->RemoveFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_REJUVENATE );
							sEventMgr.RemoveEvents( unitTarget, EVENT_REJUVENATION_FLAG_EXPIRE );
						}
					}
					else
					{
						taura = unitTarget->FindAuraByNameHash( SPELL_HASH_REJUVENATION );//Rejuvenation
						if( taura  && taura->GetSpellProto() )
						{
							uint32 amplitude = taura->GetSpellProto()->EffectAmplitude[0] / 1000;
							if( !amplitude ) amplitude = 3;

							//our happiness is that we did not store the aura mod amount so we have to recalc it
							Spell *spell = SpellPool.PooledNew();
							if (!spell)
								return;
							spell->Init( m_caster, taura->GetSpellProto(), false, NULL );
							uint32 healamount = spell->CalculateEffect( 0, unitTarget );
							SpellPool.PooledDelete( spell );
							spell = NULL;
							new_dmg = healamount * 12 / amplitude;

							unitTarget->RemoveAura( taura );

							unitTarget->RemoveFlag( UNIT_FIELD_AURASTATE,AURASTATE_FLAG_REJUVENATE );
							sEventMgr.RemoveEvents( unitTarget,EVENT_REJUVENATION_FLAG_EXPIRE );
						}
					}

					if( new_dmg > 0 )
					{
						SpellEntry *spellInfo = dbcSpell.LookupEntry(18562);
						Spell *spell = SpellPool.PooledNew();
						if (!spell)
							return;
						spell->Init(unitTarget, spellInfo, true, NULL);
						spell->SetUnitTarget( unitTarget );
						spell->Heal( (int32)new_dmg );
					}
				}
			}break;
		case 20167: // Paladin: Seal of Light
			{
				damage = ((uint32)ceilf(u_caster->GetAP() * 0.15f)) + ((uint32)ceilf(u_caster->GetUInt32Value(PLAYER_FIELD_MOD_HEALING_DONE_POS) * 0.15f));
				Heal(damage);
			}break;
		case 19750:
		case 19939:
		case 19940:
		case 19941:
		case 19942:
		case 19943:
		case 27137:
		case 48784:
		case 48785:
			{
				if( u_caster && u_caster->HasAura(53601) )
					damage *= 2;
				Heal(damage);
			}break;
		default:
			Heal(damage);
			break;
		}
	}
}

void Spell::SpellEffectBind(uint32 i)
{
	if(!playerTarget || !playerTarget->isAlive() || !m_caster)
		return;

	WorldPacket data(45);
	uint32 areaid = playerTarget->GetZoneId();
	uint32 mapid = playerTarget->GetMapId();
	if(GetProto()->EffectMiscValue[i])
	{
		areaid = GetProto()->EffectMiscValue[i];
		AreaTable * at = dbcArea.LookupEntry(areaid);
		if(!at)
			return;
		mapid = at->mapId;
	}

	playerTarget->SetBindPoint(playerTarget->GetPositionX(), playerTarget->GetPositionY(), playerTarget->GetPositionZ(), mapid, areaid);

	data.Initialize(SMSG_BINDPOINTUPDATE);
	data << playerTarget->GetBindPositionX() << playerTarget->GetBindPositionY() << playerTarget->GetBindPositionZ() << playerTarget->GetBindMapId() << playerTarget->GetBindZoneId();
	playerTarget->GetSession()->SendPacket( &data );

	data.Initialize(SMSG_PLAYERBOUND);
	data << m_caster->GetGUID() << playerTarget->GetBindZoneId();
	playerTarget->GetSession()->SendPacket(&data);
}

void Spell::SpellEffectQuestComplete(uint32 i) // Quest Complete
{
	if ( !p_caster ) return;
	QuestLogEntry * en = p_caster->GetQuestLogForEntry( GetProto()->EffectMiscValue[i] );
	if ( en && !en->CanBeFinished() )
	{
		for(int i=0;i<4;i++)
		{
			if( en->GetQuest()->required_mob[i] != 0 )
			{
				en->SetMobCount( i, 1 );
				en->SendUpdateAddKill( i );
			}
		}

		en->UpdatePlayerFields();
		en->SendQuestComplete();
	}
}

//wand->
void Spell::SpellEffectWeapondamageNoschool(uint32 i) // Weapon damage + (no School)
{
	if(!unitTarget ||!u_caster)
		return;
	if( GetType() == SPELL_DMG_TYPE_RANGED && m_spellInfo->speed > 0.0f )
	{
		switch(m_spellInfo->Id)
		{
		case 53351:
			{
				damage = u_caster->GetRAP()*0.4 + 410;
				u_caster->Strike( unitTarget, RANGED, m_spellInfo, damage, 0, 0, false, true );
			}break;
		case 61005:
			{
				damage = u_caster->GetRAP()*0.4 + 500;
				u_caster->Strike( unitTarget, RANGED, m_spellInfo, damage, 0, 0, false, true );
			}break;
		case 61006:
			{
				damage = u_caster->GetRAP()*0.4 + 650;
				u_caster->Strike( unitTarget, RANGED, m_spellInfo, damage, 0, 0, false, true );
			}break;
		default:
			{
				u_caster->Strike( unitTarget, RANGED, m_spellInfo, damage, 0, 0, false, true );
			}break;
		}
	}
	else
	{
		u_caster->Strike( unitTarget, ( GetType() == SPELL_DMG_TYPE_RANGED ? RANGED : MELEE ), m_spellInfo, damage, 0, 0, false, true );
	}
}

void Spell::SpellEffectResurrect(uint32 i) // Resurrect (Flat)
{
	if(!playerTarget)
	{
		if(!corpseTarget)
		{
			// unit resurrection handler
			if(unitTarget)
			{
				if(unitTarget->GetTypeId()==TYPEID_UNIT && unitTarget->IsPet() && unitTarget->IsDead())
				{
					uint32 hlth = ((uint32)GetProto()->EffectBasePoints[i] > unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH)) ? unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH) : (uint32)GetProto()->EffectBasePoints[i];
					uint32 mana = ((uint32)GetProto()->EffectBasePoints[i] > unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1)) ? unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1) : (uint32)GetProto()->EffectBasePoints[i];

					if(!unitTarget->IsPet())
					{
						sEventMgr.RemoveEvents(unitTarget, EVENT_CREATURE_REMOVE_CORPSE);
					}
					else
					{
						sEventMgr.RemoveEvents(unitTarget, EVENT_PET_DELAYED_REMOVE);
						sEventMgr.RemoveEvents(unitTarget, EVENT_CREATURE_REMOVE_CORPSE);
					}
					unitTarget->SetUInt32Value(UNIT_FIELD_HEALTH, hlth);
					unitTarget->SetUInt32Value(UNIT_FIELD_POWER1, mana);
					unitTarget->SetUInt32Value(UNIT_DYNAMIC_FLAGS, 0);
					unitTarget->setDeathState(ALIVE);
					static_cast<Creature*>(unitTarget)->Tagged=false;
					static_cast<Creature*>(unitTarget)->TaggerGuid=false;
					static_cast<Creature*>(unitTarget)->loot.gold=0;
					static_cast<Creature*>(unitTarget)->loot.looters.clear();
					static_cast<Creature*>(unitTarget)->loot.items.clear();
				}
			}

			return;
		}
		playerTarget = objmgr.GetPlayer(corpseTarget->GetUInt32Value(CORPSE_FIELD_OWNER));
		if(!playerTarget) return;
	}

	if(playerTarget->isAlive() || !playerTarget->IsInWorld())
		return;

	uint32 health = GetProto()->EffectBasePoints[i];
	uint32 mana = GetProto()->EffectMiscValue[i];

	playerTarget->m_resurrectHealth = health;
	playerTarget->m_resurrectMana = mana;

	SendResurrectRequest(playerTarget);
	playerTarget->SetMovement(MOVE_UNROOT, 1);
}

void Spell::SpellEffectAddExtraAttacks(uint32 i) // Add Extra Attacks
{
	if(!u_caster)
		return;
	u_caster->m_extraattacks += damage;
}

void Spell::SpellEffectDodge(uint32 i)
{
	//i think this actually enables the skill to be able to dodge melee+ranged attacks
	//value is static and sets value directly which will be modified by other factors
	//this is only basic value and will be overwritten elsewhere !!!
	//	if(unitTarget->IsPlayer())
	//		unitTarget->SetFloatValue(PLAYER_DODGE_PERCENTAGE,damage);
}

void Spell::SpellEffectParry(uint32 i)
{
	if(unitTarget)
		unitTarget->setcanperry(true);
}

void Spell::SpellEffectBlock(uint32 i)
{
	//i think this actually enables the skill to be able to block melee+ranged attacks
	//value is static and sets value directly which will be modified by other factors
	//	if(unitTarget->IsPlayer())
	//		unitTarget->SetFloatValue(PLAYER_BLOCK_PERCENTAGE,damage);
}

void Spell::SpellEffectCreateItem(uint32 i) // Create item
{
	if(!unitTarget->IsPlayer()) return;

	Player *p_target = static_cast<Player*>(unitTarget);

	Item* newItem;
	Item *add;
	uint8 slot;
	SlotResult slotresult;

	skilllinespell* skill = objmgr.GetSpellSkill(GetProto()->Id);
	if( GetProto()->EffectItemType[i] == 0 )
		return;

		ItemPrototype *m_itemProto;
		m_itemProto = ItemPrototypeStorage.LookupEntry( GetProto()->EffectItemType[i] );
		if (!m_itemProto)
			return;

		uint32 item_count = damage;

		if (p_caster)
		{
			// potions learned by discovery variables
			uint32 cast_chance = 5;
			uint32 learn_spell = 0;

			// tailoring specializations get +1 cloth bonus
			switch(GetProto()->Id)
			{
			case 36686: //Shadowcloth
				if(p_caster->HasSpell(26801)) item_count += 1;
				break;
			case 26751: // Primal Mooncloth
				if(p_caster->HasSpell(26798)) item_count += 1;
				break;
			case 31373: //Spellcloth
				if(p_caster->HasSpell(26797)) item_count += 1;
				break;
			}

			if (skill && skill->skilline == SKILL_ALCHEMY)
			{
				//Potion Master
				if (strstr(m_itemProto->Name1, "Potion"))
				{
					if(p_caster->HasSpell(28675))
						while (Rand(20) && item_count<5) item_count++;

					// Super Rejuvenation Potion
					cast_chance = 2;
					learn_spell = 28586;
				}
				//Elixir Master
				if (strstr(m_itemProto->Name1, "Elixir") || strstr(m_itemProto->Name1, "Flask"))
				{
					if(p_caster->HasSpell(28677))
						while (Rand(20) && item_count<5) item_count++;

					uint32 spList[] = {28590,28587,28588,28591,28589};
					cast_chance = 2;
					learn_spell = spList[RandomUInt(4)];
				}
				//Transmutation Master
				if (m_spellInfo->Category == 310)
				{
					if (m_spellInfo->Id == 29688) //rate for primal might is lower than for anything else
					{
						if(p_caster->HasSpell(28672))
							while (Rand(40) && item_count<5) item_count++;
					}
					else
					{
						if(p_caster->HasSpell(28672))
							while (Rand(20) && item_count<5) item_count++;
					}

					uint32 spList[] = {28581,28585,28585,28584,28582,28580};
					cast_chance = 5;
					learn_spell = spList[RandomUInt(5)];
				}
			}

			//random discovery by crafter item id
			switch ( m_itemProto->ItemId )
			{
			case 22845: //Major Arcane Protection Potion
				{
					cast_chance = 20;
					learn_spell = 41458;
				}break;
			case 22841: //Major Fire Protection Potion
				{
					cast_chance = 20;
					learn_spell = 41500;
				}break;
			case 22842: //Major Frost Protection Potion
				{
					cast_chance = 20;
					learn_spell = 41501;
				}break;
			case 22847: //Major Holy Protection Potion
				{
					// there is none
				}break;
			case 22844: //Major Nature Protection Potion
				{
					cast_chance = 20;
					learn_spell = 41502;
				}break;
			case 22846: //Major Shadow Protection Potion
				{
					cast_chance = 20;
					learn_spell = 41503;
				}break;
			}

			if ( learn_spell && p_caster->getLevel() > 60 && !p_caster->HasSpell( learn_spell ) && Rand( cast_chance ) )
			{
				SpellEntry* _spellproto = dbcSpell.LookupEntry( learn_spell );
				if( _spellproto )
				{
					p_caster->BroadcastMessage( "%sDISCOVERY! You discovered the %s !|r", MSG_COLOR_YELLOW, _spellproto->Name );
					p_caster->addSpell( learn_spell );
				}
			}
		}

		// item count cannot be more than allowed in a single stack
		uint32 itemMaxStack = (p_target->ItemStackCheat) ? 0x7fffffff : m_itemProto->MaxCount;
		if( item_count > itemMaxStack )
			item_count = itemMaxStack;

		// item count cannot be more than item unique value
		if (m_itemProto->Unique && item_count > m_itemProto->Unique)
			item_count = m_itemProto->Unique;

		if(p_target->GetItemInterface()->CanReceiveItem(m_itemProto, item_count)) //reversed since it sends >1 as invalid and 0 as valid
		{
			SendCastResult(SPELL_FAILED_TOO_MANY_OF_ITEM);
			return;
		}

		slot = 0;
		add = p_target->GetItemInterface()->FindItemLessMax(GetProto()->EffectItemType[i],1, false);
		if (!add)
		{
			slotresult = p_target->GetItemInterface()->FindFreeInventorySlot(m_itemProto);
			if(!slotresult.Result)
			{
				SendCastResult(SPELL_FAILED_TOO_MANY_OF_ITEM);
				return;
			}

			newItem =objmgr.CreateItem(GetProto()->EffectItemType[i],p_target);
			if (!newItem)
				return;

			newItem->SetUInt64Value(ITEM_FIELD_CREATOR,m_caster->GetGUID());
			newItem->SetUInt32Value(ITEM_FIELD_STACK_COUNT, item_count);

			if (m_itemProto->RandomPropId)
			{
				RandomProps * iRandomProperty = lootmgr.GetRandomProperties(m_itemProto);
				if( !iRandomProperty )
					sLog.outError( "DB Error: Item %u has unknown RandomPropId %u", m_itemProto->ItemId, m_itemProto->RandomPropId );
				else
				{
					newItem->SetRandomProperty(iRandomProperty->ID);
					newItem->ApplyRandomProperties(false);
				}
			}
			if (m_itemProto->RandomSuffixId)
			{
				ItemRandomSuffixEntry * iRandomSuffix = lootmgr.GetRandomSuffix(m_itemProto);
				if( !iRandomSuffix)
					sLog.outError( "DB Error: Item %u has unknown RandomSuffixId %u", m_itemProto->ItemId, m_itemProto->RandomSuffixId );
				else
				{
					newItem->SetRandomSuffix(iRandomSuffix->id);
					newItem->ApplyRandomProperties(false);
				}
			}

			if(p_target->GetItemInterface()->SafeAddItem(newItem,slotresult.ContainerSlot, slotresult.Slot))
			{
				/*WorldPacket data(45);
				p_caster->GetSession()->BuildItemPushResult(&data, p_caster->GetGUID(), 1, item_count, GetProto()->EffectSpellGroupRelation[i] ,0,0xFF,1,0xFFFFFFFF);
				p_caster->SendMessageToSet(&data, true);*/
				p_target->GetSession()->SendItemPushResult(newItem,true,false,true,true,slotresult.ContainerSlot,slotresult.Slot,item_count);
			} else {
				newItem->DeleteMe();
			}
		}
		else
		{
			// scale item_count down if total stack will be more than 20
			if( (add->GetUInt32Value(ITEM_FIELD_STACK_COUNT) + item_count > 20) && !p_target->ItemStackCheat )
			{
				uint32 item_count_filled;
				item_count_filled = 20 - add->GetUInt32Value(ITEM_FIELD_STACK_COUNT);
				add->SetCount(20);
				add->m_isDirty = true;

				slotresult = p_target->GetItemInterface()->FindFreeInventorySlot(m_itemProto);
				if(!slotresult.Result)
					item_count = item_count_filled;
				else
				{
					newItem =objmgr.CreateItem(GetProto()->EffectItemType[i], p_target);
					if (!newItem)
						return;

					newItem->SetUInt64Value(ITEM_FIELD_CREATOR,m_caster->GetGUID());
					newItem->SetUInt32Value(ITEM_FIELD_STACK_COUNT, item_count - item_count_filled);
					if(!p_target->GetItemInterface()->SafeAddItem(newItem,slotresult.ContainerSlot, slotresult.Slot))
					{
						newItem->DeleteMe();
						item_count = item_count_filled;
					}
					else
						p_target->GetSession()->SendItemPushResult(newItem, true, false, true, true, slotresult.ContainerSlot, slotresult.Slot, item_count);
				}
			}
			else
			{
				add->SetCount(add->GetUInt32Value(ITEM_FIELD_STACK_COUNT) + item_count);
				add->m_isDirty = true;
				p_target->GetSession()->SendItemPushResult(add, true, false, true, false, (uint8)p_target->GetItemInterface()->GetBagSlotByGuid(add->GetGUID()), 0xFFFFFFFF, item_count);
			}

			/*WorldPacket data(45);
			p_caster->GetSession()->BuildItemPushResult(&data, p_caster->GetGUID(), 1, item_count, GetProto()->EffectSpellGroupRelation[i] ,0,0xFF,1,0xFFFFFFFF);
			p_caster->SendMessageToSet(&data, true);*/
		}
		if (p_caster && skill)
		{
			// skill up
			DetermineSkillUp( skill->skilline );

			// profession discoveries
			uint32 discovered_recipe = 0;
			std::set<ProfessionDiscovery*>::iterator itr = objmgr.ProfessionDiscoveryTable.begin();
			for ( ; itr != objmgr.ProfessionDiscoveryTable.end(); itr++ )
			{
				ProfessionDiscovery * pf = ( *itr );
				if ( pf && GetProto()->Id == pf->SpellId && p_caster->_GetSkillLineCurrent( skill->skilline ) >= pf->SkillValue && !p_caster->HasSpell( pf->SpellToDiscover ) && Rand( pf->Chance ) )
				{
					discovered_recipe = pf->SpellToDiscover;
					break;
				}
			}
			// if something discovered learn p_caster that recipe and broadcast message
			if ( discovered_recipe != 0 )
			{
				SpellEntry * se = dbcSpell.LookupEntry( discovered_recipe );
				if ( se )
				{
					p_caster->addSpell( discovered_recipe );
					WorldPacket * data;
					char msg[256];
					sprintf( msg, "%sDecouverte! %s a d�couvert comment cr�er %s.|r", MSG_COLOR_GOLD, p_caster->GetName(), se->Name );
					data = sChatHandler.FillMessageData( CHAT_MSG_SYSTEM, LANG_UNIVERSAL,  msg, p_caster->GetGUID(), 0 );
					p_caster->GetMapMgr()->SendChatMessageToCellPlayers( p_caster, data, 2, 1, LANG_UNIVERSAL, p_caster->GetSession() );
					delete data;
				}
			}
	}
}

void Spell::SpellEffectWeapon(uint32 i)
{
	if( !playerTarget )
		return;

	uint32 skill = 0;
	uint32 spell = 0;

	switch( this->GetProto()->Id )
	{
	case 201:    // one-handed swords
		{
			skill = SKILL_SWORDS;
		}break;
	case 202:   // two-handed swords
		{
			skill = SKILL_2H_SWORDS;
		}break;
	case 203:   // Unarmed
		{
			skill = SKILL_UNARMED;
		}break;
	case 199:   // two-handed maces
		{
			skill = SKILL_2H_MACES;
		}break;
	case 198:   // one-handed maces
		{
			skill = SKILL_MACES;
		}break;
	case 197:   // two-handed axes
		{
			skill = SKILL_2H_AXES;
		}break;
	case 196:   // one-handed axes
		{
			skill = SKILL_AXES;
		}break;
	case 5011: // crossbows
		{
			skill = SKILL_CROSSBOWS;
			spell = SPELL_RANGED_GENERAL;
		}break;
	case 227:   // staves
		{
			skill = SKILL_STAVES;
		}break;
	case 1180:  // daggers
		{
			skill = SKILL_DAGGERS;
		}break;
	case 200:   // polearms
		{
			skill = SKILL_POLEARMS;
		}break;
	case 15590: // fist weapons
		{
			skill = SKILL_UNARMED;
		}break;
	case 264:   // bows
		{
			skill = SKILL_BOWS;
			spell = SPELL_RANGED_GENERAL;
		}break;
	case 266: // guns
		{
			skill = SKILL_GUNS;
			spell = SPELL_RANGED_GENERAL;
		}break;
	case 2567:  // thrown
		{
			skill = SKILL_THROWN;
		}break;
	case 5009:  // wands
		{
			skill = SKILL_WANDS;
			spell = SPELL_RANGED_GENERAL;
		}break;
		//case 3386:  // spears
		//	skill = 0;   // ??!!
		//	break;
	default:
		{
			skill = 0;
			sLog.outDebug("WARNING: Could not determine skill for spell id %d (SPELL_EFFECT_WEAPON)", this->GetProto()->Id);
		}break;
	}

	// Don't add skills to players logging in.
	/*if((GetProto()->Attributes & ATTRIBUTES_PASSIVE) && playerTarget->m_TeleportState == 1)
	return;*/

	if(skill)
	{
		if(spell)
			playerTarget->addSpell(spell);

		// if we do not have the skill line
		if(!playerTarget->_HasSkillLine(skill))
		{
			playerTarget->_AddSkillLine(skill, 1, playerTarget->getLevel()*5);
		}
		else // unhandled.... if we have the skill line
		{
		}
	}
}

void Spell::SpellEffectDefense(uint32 i)
{
	//i think this actually enables the skill to be able to use defense
	//value is static and sets value directly which will be modified by other factors
	//this is only basic value and will be overwritten elsewhere !!!
	//	if(unitTarget->IsPlayer())
	//		unitTarget->SetFloatValue(UNIT_FIELD_RESISTANCES,damage);
}

void Spell::SpellEffectPersistentAA(uint32 i) // Persistent Area Aura
{
	if(m_AreaAura || !m_caster->IsInWorld())
		return;
	//create only 1 dyn object
	uint32 dur = GetDuration();
	float r = GetRadius(i);

	//Note: this code seems to be useless
	//this must be only source point or dest point
	//this AREA aura it's applied on area
	//it can'be on unit or self or item or object
	//uncomment it if I'm wrong
	//We are thinking in general so it might be useful later DK

	// grep: this is a hack!
	// our shitty dynobj system doesn't support GO casters, so we gotta
	// kinda have 2 summoners for traps that apply AA.
	DynamicObject * dynObj = m_caster->GetMapMgr()->CreateDynamicObject();

	if(g_caster && g_caster->m_summoner && !unitTarget)
	{
		Unit * caster = g_caster->m_summoner;
		dynObj->Create(caster, this, g_caster->GetPositionX(), g_caster->GetPositionY(),
			g_caster->GetPositionZ(), dur, r);
		m_AreaAura = true;
		return;
	}

	switch(m_targets.m_targetMask)
	{
	case TARGET_FLAG_SELF:
		{
			dynObj->Create(u_caster, this,	m_caster->GetPositionX(),
				m_caster->GetPositionY(), m_caster->GetPositionZ(), dur,r);
		}break;
	case TARGET_FLAG_UNIT:
		{
			if(!unitTarget||!unitTarget->isAlive())
				break;
			dynObj->Create( u_caster, this, unitTarget->GetPositionX(), unitTarget->GetPositionY(), unitTarget->GetPositionZ(),
				dur, r);
		}break;
	case TARGET_FLAG_OBJECT:
		{
			if(!unitTarget) break;
			if(!unitTarget->isAlive()) break;

			dynObj->Create(u_caster, this, unitTarget->GetPositionX(), unitTarget->GetPositionY(), unitTarget->GetPositionZ(),
				dur, r);
		}break;
	case TARGET_FLAG_SOURCE_LOCATION:
		{
			dynObj->SetInstanceID(m_caster->GetInstanceID());
			dynObj->Create(u_caster, this, m_targets.m_srcX,
				m_targets.m_srcY, m_targets.m_srcZ, dur,r);
		}break;
	case TARGET_FLAG_DEST_LOCATION:
		{
			dynObj->SetInstanceID(m_caster->GetInstanceID());
			dynObj->Create(u_caster?u_caster:g_caster->m_summoner, this,
				m_targets.m_destX, m_targets.m_destY, m_targets.m_destZ,dur,r);
		}break;
	default:
		return;
	}

	if(u_caster)
		if(GetProto()->ChannelInterruptFlags > 0)
		{
			u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT,dynObj->GetGUID());
			u_caster->SetUInt32Value(UNIT_CHANNEL_SPELL,GetProto()->Id);
		}
		m_AreaAura = true;
}

void Spell::SpellEffectSummon(uint32 i)
{
	switch(m_spellInfo->EffectMiscValueB[i])
	{
	case 63:
	case 81:
	case 82:
	case 83:
	case 121:	SpellEffectSummonTotem(i);		return;
	case 41:
	case 407:	SpellEffectSummonCritter(i);	return;
	case 61:
	case 669:
    case 881:         
    case 2301:  SpellEffectSummonGuardian(i);   return;  
    case 64:	SpellEffectSummonWild(i);		return;
	case 65:
	case 428:	SpellEffectSummonPossessed(i);	return;
	case 66:	SpellEffectSummonDemon(i);		return;
	//default:	SpellEffectSummonGuardian(i);	return;

	}
	if( !u_caster ) return;

	if(GetProto()->EffectMiscValue[i] != 24207) //Tempfix
		u_caster->RemoveFieldSummon();

	if(GetProto()->EffectMiscValue[i] == 89)
	{
		SpellEffectSummonGuardian(i);
		return;
	}

	if(GetProto()->EffectMiscValue[i] == 26125)
	{
		SpellEffectSummonGuardian(i);
		return;
	}

	if(GetProto()->EffectMiscValue[i] == 31216)
	{
		SpellEffectSummonGuardian(i);
		return;
	}

	if(GetProto()->EffectMiscValue[i] == 1964)
	{
		SpellEffectSummonGuardian(i);
		return;
	}

	/* This is for summon water elemental, etc */
	CreatureInfo * ci = CreatureNameStorage.LookupEntry(GetProto()->EffectMiscValue[i]);
	CreatureProto * cp = CreatureProtoStorage.LookupEntry(GetProto()->EffectMiscValue[i]);
	if( !ci || !cp )
		return;

	switch( GetProto()->EffectMiscValue[i] )
	{
	case 4277: // Eye of Kilrogg
		{
			SpellEffectSummonPossessed(i);
		}break;
	case 510:	// Water Elemental
		{
			Pet *summon = objmgr.CreatePet(GetProto()->EffectMiscValue[i]);
			summon->CreateAsSummon( GetProto()->EffectMiscValue[i], ci, NULL, p_caster, GetProto(), 1, GetDuration() );
			summon->AddSpell( dbcSpell.LookupEntry(31707), true );
			summon->AddSpell( dbcSpell.LookupEntry(33395), true );
		}break;
	case 29264: // Feral Spirit
		{
			/*
			Feral Spirit
			12% of base mana	30 yd range
			Instant cast		3 min cooldown
			Summons two Spirit Wolves under the command of the Shaman, lasting 45 sec.
			*/
			//First wolf
			Pet *summon = objmgr.CreatePet(GetProto()->EffectMiscValue[i]);
			summon->CreateAsSummon(GetProto()->EffectMiscValue[i], ci, NULL, p_caster, GetProto(), 4, GetDuration());

			//Second wolf
			Pet *summon2 = objmgr.CreatePet(GetProto()->EffectMiscValue[i]);
			summon2->CreateAsSummon(GetProto()->EffectMiscValue[i], ci, NULL, p_caster, GetProto(), 4, GetDuration());
			summon2->GetAIInterface()->SetUnitToFollow(p_caster);
			summon2->GetAIInterface()->SetUnitToFollowAngle(float(-(M_PI/2)));
			
			//Spells
			summon->AddSpell(dbcSpell.LookupEntry(58867), true); // Spirit Hunt
			summon->AddSpell(dbcSpell.LookupEntry(58875), true); // Spirit walk
			summon->AddSpell(dbcSpell.LookupEntry(58857), true); // Twin Howl
			summon->AddSpell(dbcSpell.LookupEntry(58861), true); // Spirit Bash
		}break;
	case 27893: // Dancing Rune Weapon
		{
			/*
			Dancing Rune Weapon
			40 Runic Power	30 yd range
			Instant	3 min cooldown
			Requires Melee Weapon
			Unleashes all available runic power to summon a second rune weapon
			that fights on its own for 10 sec plus 1 sec per 5 additional runic power,
			doing the same attacks as the Death Knight.
			*/
			uint32 duration = 10000;
			uint32 curPow = p_caster->GetUInt32Value(UNIT_FIELD_POWER7)+1;
			uint32 extradur = float2int32(duration+(curPow/50.0f));
			Item * item = p_caster->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
			uint32 mitemID = 0;
			if(item)
				mitemID = item->GetUInt32Value( OBJECT_FIELD_ENTRY );

			Pet *summon = objmgr.CreatePet(GetProto()->EffectMiscValue[i]);
			summon->CreateAsSummon(26125, ci, NULL, p_caster, GetProto(), 1, extradur );
			summon->SetUInt32Value(UNIT_FIELD_DISPLAYID, (uint32)15435);
			summon->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, mitemID );
			summon->SetUInt32Value(UNIT_FIELD_BASEATTACKTIME, item->GetProto()->Delay);
			summon->SetFloatValue(UNIT_FIELD_MINDAMAGE,(float)p_caster->GetDamageDoneMod(SCHOOL_NORMAL));
			summon->SetFloatValue(UNIT_FIELD_MAXDAMAGE,(float)p_caster->GetDamageDoneMod(SCHOOL_NORMAL));
			summon->GetAIInterface()->SetUnitToFollowAngle(float(-(M_PI/2)));
			p_caster->SetUInt32Value(UNIT_FIELD_POWER7,0); //Drains all runic power.
		}break;
	default:
		{
			Creature * pCreature = u_caster->GetMapMgr()->CreateCreature(cp->Id);
			ASSERT(pCreature != NULL);

			pCreature->Load(cp, u_caster->GetPositionX(), u_caster->GetPositionY(), u_caster->GetPositionZ());
			pCreature->_setFaction();
			pCreature->GetAIInterface()->Init(pCreature,AITYPE_PET,MOVEMENTTYPE_NONE,u_caster);
			pCreature->GetAIInterface()->SetUnitToFollow(u_caster);
			pCreature->GetAIInterface()->SetUnitToFollowAngle(float(-(M_PI/2)));
			pCreature->GetAIInterface()->SetFollowDistance(GetRadius(i));
			pCreature->SetUInt32Value(UNIT_FIELD_LEVEL, u_caster->getLevel());
			pCreature->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, u_caster->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
			pCreature->_setFaction();

			pCreature->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, u_caster->GetGUID());
			pCreature->SetUInt64Value(UNIT_FIELD_CREATEDBY, u_caster->GetGUID());
			u_caster->SetUInt64Value(UNIT_FIELD_SUMMON, pCreature->GetGUID());

			uint32 MiscValue = m_spellInfo->EffectMiscValue[i];
			if ( MiscValue == 19668 ) //shadowfiend
			{
				float parent_bonus = (float)(p_caster->GetDamageDoneMod(SCHOOL_SHADOW)*0.065f);
				pCreature->SetFloatValue(UNIT_FIELD_MINDAMAGE, pCreature->GetFloatValue(UNIT_FIELD_MINDAMAGE) + parent_bonus);
				pCreature->SetFloatValue(UNIT_FIELD_MAXDAMAGE, pCreature->GetFloatValue(UNIT_FIELD_MAXDAMAGE) + parent_bonus);
				pCreature->BaseDamage[0] += parent_bonus;
				pCreature->BaseDamage[1] += parent_bonus;
				Unit* uTarget = unitTarget;
				if( uTarget )
				{
					pCreature->GetAIInterface()->AttackReaction( uTarget, 1 );
					pCreature->GetAIInterface()->SetNextTarget( uTarget );
				}
			}
			if ( MiscValue == 24207 ) //Army of the dead ghoul.
			{
				float parent_bonus = (float)(p_caster->GetDamageDoneMod(SCHOOL_NORMAL)*0.04f);
				float pi_rand = ((int32)(rand()-RAND_MAX*0.5f)%15707)/10000.0f; // should be random enough.
				pCreature->SetFloatValue(UNIT_FIELD_MINDAMAGE, pCreature->GetFloatValue(UNIT_FIELD_MINDAMAGE) + parent_bonus);
				pCreature->SetFloatValue(UNIT_FIELD_MAXDAMAGE, pCreature->GetFloatValue(UNIT_FIELD_MAXDAMAGE) + parent_bonus);
				pCreature->GetAIInterface()->SetUnitToFollowAngle(pi_rand);
				pCreature->GetAIInterface()->SetFollowDistance(3.0f);
				float x,y,z;
				x = u_caster->GetPositionX()+rand()%20;
				y = u_caster->GetPositionY()+rand()%20;
				z = u_caster->GetPositionZ();
				pCreature->SetPosition(x,y,z,0.0f,true);
				pCreature->CastSpell(pCreature,50142,true);
			}

			if ( MiscValue == 31893 || MiscValue == 31894 || MiscValue == 31895 || MiscValue == 31896 || MiscValue == 31897 || MiscValue == 31883) //Light wells!
			{
				pCreature->CastSpell(pCreature, 59907, true);
				sEventMgr.AddEvent(pCreature, &Creature::SafeDelete, EVENT_CREATURE_REMOVE_CORPSE, 180000, 1, 0);
				break;
			}
			pCreature->PushToWorld(u_caster->GetMapMgr());
			if ( MiscValue == 19668 ) //shadowfiend
			{
				if( unitTarget )
				{
					Log.Notice("YOOO", "attaque");
					pCreature->GetAIInterface()->AttackReaction( unitTarget, 1 );
					pCreature->GetAIInterface()->SetNextTarget( unitTarget );
				}
			}
			sEventMgr.AddEvent(pCreature, &Creature::SafeDelete, EVENT_CREATURE_REMOVE_CORPSE, GetDuration(), 1, 0);
		}break;
	}
}

void Spell::SpellEffectLeap(uint32 i) // Leap
{
	float radius = GetRadius(i);
	// remove movement impeding auras
	u_caster->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN);
	// cebernic: 2008-10-11
	// thanks for the guys who gave the suggestions to my private forum(p2wow.com)
	// Blink works perfectly atm.Features:no traversed / never outspace falling:D / calc right everywhere even multi floors or underground / much blizzlike.
	// a couple hours i wasted, so it full tested.

	if (sWorld.Collision) {
		if(p_caster && p_caster->m_bg && !p_caster->m_bg->HasStarted()) // tempfix
			return;

		int _UNDERGROUND   = 0x2;
		int _COLLIDED      = 0x4;
		int _LAND_BREAK    = 0x8;
		int _POS_BREAK     = 0x10;
		int _BLOCK_BREAK   = 0x20;

		int flag=0;

		float newposX, newposY, newposZ;
		// init first variables
		float ori = m_caster->GetOrientation();
		float posX = m_caster->GetPositionX();
		float posY = m_caster->GetPositionY();
		float posZ = m_caster->GetPositionZ();
		if ( m_caster->GetMapMgr()->IsUnderground(posX,posY,posZ) )// make sure not eq.
			flag |= _UNDERGROUND;

		LocationVector src(posX,posY,posZ);
		LocationVector finaldest(posX,posY,posZ);


		uint8 steps = 20; // higher precision, but more performance waste, radius =20.0f may each 1y will be checked.
		float radius_steps = radius / steps;
		uint8 i =0;

		float _SharpCounter = 0.0f;
		for ( i = 1; i < steps; i++ )
		{
			newposX = posX + ( float(i) * radius_steps * cosf( ori ) );
			newposY = posY + ( float(i) * radius_steps * sinf( ori ) );
			newposZ =  m_caster->GetMapMgr()->GetFirstZWithCPZ(newposX,newposY,posZ);

			if ( newposZ != NO_WMO_HEIGHT ) flag |= _COLLIDED;
			if (flag & _COLLIDED){
				if ( newposZ == NO_WMO_HEIGHT ) { // been round 2
					flag |= _LAND_BREAK;
					break;
				}
			}else {
				newposZ = m_caster->GetMapMgr()->GetLandHeight(newposX,newposY);
			}

			if ( fabs( ( newposZ - finaldest.z ) / radius_steps ) > 1.0f ) {flag |= _POS_BREAK; break;} // too high


			LocationVector dest(newposX,newposY,newposZ);
			dest.o = ori;
			if ( i>1 && CollideInterface.GetFirstPoint( m_caster->GetMapId(),src, dest,dest, -1.5f ) ) {flag |= _BLOCK_BREAK; break;} // blocked then break;

			if ( newposZ > finaldest.z ){
				_SharpCounter = _SharpCounter+(newposZ - finaldest.z); // this value reserved for more extends.
			}

			//printf("x:%f y:%f z:%f counter%d sharp%f\n",newposX,newposY,newposZ,i,_SharpCounter );

			finaldest.x = newposX;
			finaldest.y = newposY;
			finaldest.z = newposZ;
		}


		/*if ( flag & _UNDERGROUND ) printf("_UNDERGROUND 1\n");
		if ( flag & _COLLIDED ) printf("_COLLIDED 1\n");
		if ( flag & _LAND_BREAK ) printf("_LAND_BREAK 1\n");
		if ( flag & _POS_BREAK ) printf("_POS_BREAK 1\n");
		if ( flag & _BLOCK_BREAK ) printf("_BLOCK_BREAK 1\n");*/


		if ( i <3 ) return; //wallhack?

		if ( !(flag & _UNDERGROUND) )
		{
			newposZ = m_caster->GetMapMgr()->GetLandHeight( finaldest.x,finaldest.y );
			if ( newposZ > finaldest.z ) finaldest.z = newposZ;
		}

		if ( !(flag&_COLLIDED) && (flag&_POS_BREAK) ) {
			// just test again ,landheight wasn't strictly, collision system better;p
			// so it makes you on falling.
			newposX = posX + ( ((float(i) * radius_steps)+0.5f) * cosf( m_caster->GetOrientation() ) );
			newposY = posY + ( ((float(i) * radius_steps)+0.5f) * sinf( m_caster->GetOrientation() ) );
			newposZ = m_caster->GetMapMgr()->GetLandHeight(newposX,newposY);
			if ( newposZ > finaldest.z ) finaldest.z = finaldest.z+4.0f; // taking big Z
		}

		finaldest.o = m_caster->GetOrientation();

		if(p_caster)
		{
			p_caster->blinked = true;
			p_caster->SafeTeleport( p_caster->GetMapId(), p_caster->GetInstanceID(), finaldest );
		}
		else
		{
			u_caster->SetPosition(finaldest, true);
		}
	} else {
		if(!p_caster) return;

		WorldPacket data(SMSG_MOVE_KNOCK_BACK, 50);
		data << p_caster->GetNewGUID();
		data << getMSTime();
		data << cosf(p_caster->GetOrientation()) << sinf(p_caster->GetOrientation());
		data << radius;
		data << float(-10.0f);
		p_caster->GetSession()->SendPacket(&data);
	}
}

void Spell::SpellEffectEnergize(uint32 i) // Energize
{
	if(!unitTarget || !unitTarget->isAlive())
		return;

	uint32 modEnergy = 0;
	switch( GetProto()->Id )
	{
	case 39609:
		{
			modEnergy = unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1)*0.06;
		}break;
	case 30824: // Shamanistic Rage
		modEnergy = damage*GetUnitTarget()->GetAP() / 100;
		break;
	case 31786: // Paladin - Spiritual Attunement
		if( ProcedOnSpell )
		{
			SpellEntry *motherspell = dbcSpell.LookupEntry(pSpellId);
			if(motherspell)
			{
				//heal amount from procspell (we only proceed on a heal spell)
				uint32 healamt = 0;
				if(ProcedOnSpell->Effect[0] == SPELL_EFFECT_HEAL || ProcedOnSpell->Effect[0] == SPELL_EFFECT_SCRIPT_EFFECT)
					healamt=ProcedOnSpell->EffectBasePoints[0]+1;
				else if(ProcedOnSpell->Effect[1] == SPELL_EFFECT_HEAL || ProcedOnSpell->Effect[1] == SPELL_EFFECT_SCRIPT_EFFECT)
					healamt=ProcedOnSpell->EffectBasePoints[1]+1;
				else if(ProcedOnSpell->Effect[2] == SPELL_EFFECT_HEAL || ProcedOnSpell->Effect[2] == SPELL_EFFECT_SCRIPT_EFFECT)
					healamt = ProcedOnSpell->EffectBasePoints[2]+1;
				modEnergy = (motherspell->EffectBasePoints[0]+1) * (healamt) / 100;
			}
		}
		break;
	case 20268: //Judgement of Wisdom
		modEnergy = uint32( 0.02f * unitTarget->GetUInt32Value(UNIT_FIELD_BASE_MANA) );
		break;
	case 2687: // Improved Bloodrage, dirty fix
		{
			modEnergy = damage;
			if( p_caster)
			{
				if( p_caster->mSpells.find(12818) != p_caster->mSpells.end() )
					modEnergy += 110; //60
				if( p_caster->mSpells.find(12301) != p_caster->mSpells.end() )
					modEnergy += 60; //30
			}
		}
		break;
	default:
		modEnergy = damage;
		break;
	}

	if( unitTarget->HasAura( 17619 ) )
	{
		modEnergy = uint32( modEnergy * 1.4f );
	}

	u_caster->Energize( unitTarget, GetProto()->Id, modEnergy, GetProto()->EffectMiscValue[i] );
}

void Spell::SpellEffectWeaponDmgPerc(uint32 i) // Weapon Percent damage
{
	if(!unitTarget || !u_caster) return;

	// Chevalier de la mort Spell Cod� dans SpellEffectDummyMelee
	if(SPELL_HASH_BLOOD_STRIKE || SPELL_HASH_HEART_STRIKE || SPELL_HASH_FROST_STRIKE || SPELL_HASH_PLAGUE_STRIKE || SPELL_HASH_DEATH_STRIKE || SPELL_HASH_SCOURGE_STRIKE || SPELL_HASH_OBLITERATE)
		return;

	if( GetType() == SPELL_DMG_TYPE_MAGIC )
	{
		float fdmg = (float)CalculateDamage( u_caster, unitTarget, MELEE, 0, GetProto() );
		uint32 dmg = float2int32(fdmg*(float(damage/100.0f)));
		u_caster->SpellNonMeleeDamageLog(unitTarget, GetProto()->Id, dmg, false, false, false);
	}
	else
	{
		uint32 _type;
		if( GetType() == SPELL_DMG_TYPE_RANGED )
			_type = RANGED;
		else
		{
			if (GetProto()->AttributesExC & 0x1000000)
				_type =  OFFHAND;
			else
				_type = MELEE;
		}

		switch(m_spellInfo->Id)
		{
		case 33876:
		case 33982:
		case 33983:
		case 48565:
		case 48566:
			{
				static_cast< Player* >( u_caster )->AddComboPoints( unitTarget->GetGUID(), 1 );
			}break;
		}
		u_caster->Strike( unitTarget, _type, GetProto(), add_damage, damage, 0, false, true );
	}
}

void Spell::SpellEffectTriggerMissile(uint32 i) // Trigger Missile
{
	//Used by mortar team
	//Triggers area affect spell at destinatiom
	if(!m_caster) return;

	uint32 spellid = GetProto()->EffectTriggerSpell[i];
	if(!spellid) return;

	SpellEntry *spInfo = dbcSpell.LookupEntry(spellid);
	if(!spInfo) return;

	float spellRadius = GetRadius(i);

	for(std::set<Object*>::iterator itr = m_caster->GetInRangeSetBegin(); itr != m_caster->GetInRangeSetEnd(); itr++ )
	{
		if(!((*itr)->IsUnit()) || !static_cast<Unit*>((*itr))->isAlive())
			continue;
		Unit *t= static_cast<Unit*>((*itr));

		float r;
		float d=m_targets.m_destX-t->GetPositionX();
		r = d*d;
		d = m_targets.m_destY-t->GetPositionY();
		r += d*d;
		d = m_targets.m_destZ-t->GetPositionZ();
		r += d*d;

		if(sqrt(r)> spellRadius) continue;

		if(!isAttackable(m_caster, static_cast<Unit*>(*itr)))//Fix Me: only enemy targets?
			continue;

		Spell * sp = SpellPool.PooledNew();
		if (!sp)
			return;
		sp->Init(m_caster,spInfo,true,NULL);
		SpellCastTargets tgt;
		tgt.m_unitTarget=(*itr)->GetGUID();
		sp->prepare(&tgt);
	}
}

void Spell::SpellEffectOpenLock(uint32 i) // Open Lock
{
	if(!p_caster) return;

	uint8 loottype = 0;

	uint32 locktype=GetProto()->EffectMiscValue[i];
	switch(locktype)
	{
	case LOCKTYPE_PICKLOCK:
		{
			uint32 v = 0;
			uint32 lockskill = p_caster->_GetSkillLineCurrent(SKILL_LOCKPICKING);

			if(itemTarget)
			{
				if(!itemTarget->locked)
					return;

				Lock *lock = dbcLock.LookupEntry( itemTarget->GetProto()->LockId );
				if(!lock) return;
				for(int i = 0; i<5; i++)
					if(lock->locktype[i] == 2 && lock->minlockskill[i] && lockskill >= lock->minlockskill[i])
					{
						v = lock->minlockskill[i];
						itemTarget->locked = false;
						itemTarget->SetFlag(ITEM_FIELD_FLAGS,4); // unlock
						DetermineSkillUp(SKILL_LOCKPICKING,v/5);
						break;
					}
			}
			else if(gameObjTarget)
			{
				GameObjectInfo *info = GameObjectNameStorage.LookupEntry(gameObjTarget->GetEntry());
				if(!info || gameObjTarget->GetByte(GAMEOBJECT_BYTES_1, 0) == 0) return;
				Lock *lock = dbcLock.LookupEntry( info->SpellFocus );
				if(lock == 0)
					return;

				for(int i=0;i<5;i++)
				{
					if(lock->locktype[i] == 2 && lock->minlockskill[i] && lockskill >= lock->minlockskill[i])
					{
						v = lock->minlockskill[i];
						gameObjTarget->SetUInt32Value(GAMEOBJECT_FLAGS, 0);
						gameObjTarget->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
						//Add Fill GO loot here
						if(gameObjTarget->loot.items.size() == 0)
						{
							lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetEntry(), gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->iInstanceMode ? true : false) : false);
							DetermineSkillUp(SKILL_LOCKPICKING,v/5); //to prevent free skill up
						}
						loottype = LOOT_CORPSE;
						//End of it
						break;
					}
				}
			}
		}
		break;
	case LOCKTYPE_HERBALISM:
		{
			if(!gameObjTarget) return;

			uint32 v = gameObjTarget->GetGOReqSkill();
			bool bAlreadyUsed = false;

			if(Rand(100.0f)) // 3% chance to fail//why?
			{
				if( static_cast< Player* >( m_caster )->_GetSkillLineCurrent( SKILL_HERBALISM ) < v )
				{
					//SendCastResult(SPELL_FAILED_LOW_CASTLEVEL);
					return;
				}
				else
				{
					if( gameObjTarget->loot.items.size() == 0 )
					{
						lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetEntry(), gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->iInstanceMode ? true : false) : false);
					}
					else
						bAlreadyUsed = true;
				}
				loottype = LOOT_SKINNING;
			}
			else
			{
				/*
				if(rand()%100 <= 30)
				{
				//30% chance to not be able to reskin on fail
				((Creature*)unitTarget)->Skinned = true;
				WorldPacket *pkt=unitTarget->BuildFieldUpdatePacket(UNIT_FIELD_FLAGS,0);
				static_cast< Player* >( m_caster )->GetSession()->SendPacket(pkt);
				delete pkt;

				}*/
				SendCastResult(SPELL_FAILED_TRY_AGAIN);
			}
			//Skill up
			if(!bAlreadyUsed) //Avoid cheats with opening/closing without taking the loot
				DetermineSkillUp(SKILL_HERBALISM,v/5);
		}
		break;
	case LOCKTYPE_MINING:
		{
			if(!gameObjTarget) return;

			uint32 v = gameObjTarget->GetGOReqSkill();
			bool bAlreadyUsed = false;

			if( Rand( 100.0f ) ) // 3% chance to fail//why?
			{
				if( static_cast< Player* >( m_caster )->_GetSkillLineCurrent( SKILL_MINING ) < v )
				{
					//SendCastResult(SPELL_FAILED_LOW_CASTLEVEL);
					return;
				}
				else if( gameObjTarget->loot.items.size() == 0 )
				{
					lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetEntry(), gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->iInstanceMode ? true : false) : false);
				}
				else
					bAlreadyUsed = true;

				loottype = LOOT_SKINNING;
			}
			else
			{
				SendCastResult(SPELL_FAILED_TRY_AGAIN);
			}
			//Skill up
			if(!bAlreadyUsed) //Avoid cheats with opening/closing without taking the loot
				DetermineSkillUp(SKILL_MINING, v/5);
		}
		break;
	case LOCKTYPE_SLOW_OPEN: // used for BG go's
		{
			if(!gameObjTarget ) return;
			if(p_caster && p_caster->m_bg)
				if(p_caster->m_bg->HookSlowLockOpen(gameObjTarget, p_caster, this))
					return;

			uint32 spellid = !gameObjTarget->GetInfo()->Unknown1 ? 23932 : gameObjTarget->GetInfo()->Unknown1;
			SpellEntry *en = dbcSpell.LookupEntry(spellid);
			Spell *sp = SpellPool.PooledNew();
			if (!sp)
				return;
			sp->Init(p_caster,en,true,NULL);
			SpellCastTargets tgt;
			tgt.m_unitTarget=gameObjTarget->GetGUID();
			sp->prepare(&tgt);
			return;
		}
		break;
	case LOCKTYPE_QUICK_CLOSE:
		{
			if(!gameObjTarget ) return;
			gameObjTarget->EventCloseDoor();
		}
		break;
	default://not profession
		{
			if(!gameObjTarget ) return;

			if( gameObjTarget->GetByte( GAMEOBJECT_BYTES_1, 1 ) == GAMEOBJECT_TYPE_GOOBER)
				CALL_GO_SCRIPT_EVENT(gameObjTarget, OnActivate)(static_cast<Player*>(p_caster));
				CALL_INSTANCE_SCRIPT_EVENT( gameObjTarget->GetMapMgr(), OnGameObjectActivate )( gameObjTarget, p_caster ); 

			if(sQuestMgr.OnActivateQuestGiver(gameObjTarget, p_caster))
				return;

			if(sQuestMgr.OnGameObjectActivate(p_caster, gameObjTarget))
			{
				p_caster->UpdateNearbyGameObjects();
				return;
			}

			if(gameObjTarget->loot.items.size() == 0)
			{
				lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetEntry(), gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->iInstanceMode ? true : false) : false);
			}
			loottype= LOOT_CORPSE ;
		}
		break;
	};
	if( gameObjTarget && gameObjTarget->GetByte( GAMEOBJECT_BYTES_1, 1 ) == GAMEOBJECT_TYPE_CHEST)
		static_cast< Player* >( m_caster )->SendLoot( gameObjTarget->GetGUID(), loottype );
}

void Spell::SpellEffectTransformItem(uint32 i)
{
	bool result;
	AddItemResult result2;

	if(!i_caster) return;
	uint32 itemid=GetProto()->EffectItemType[i];
	if(!itemid) return;

	//Save durability of the old item
	Player * owner=i_caster->GetOwner();
	uint32 dur= i_caster->GetUInt32Value(ITEM_FIELD_DURABILITY);
	//	int8 slot=owner->GetItemInterface()->GetInventorySlotByGuid(i_caster->GetGUID());
	//	uint32 invt=i_caster->GetProto()->InventoryType;

	result  = owner->GetItemInterface()->SafeFullRemoveItemByGuid(i_caster->GetGUID());
	if(!result)
	{
		//something went wrong if this happen, item doesn't exist, so it wasn't destroyed.
		return;
	}

	i_caster = NULL;

	Item *it = objmgr.CreateItem(itemid,owner);
	if (!it) return;

	it->SetDurability(dur);
	//additem

	//additem
	result2 = owner->GetItemInterface()->AddItemToFreeSlot(it);
	if(!result2) //should never get here
	{
		owner->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, INV_ERR_BAG_FULL);
		it->DeleteMe();
	}
}

void Spell::SpellEffectApplyAA(uint32 i) // Apply Area Aura
{
	if(!unitTarget || !unitTarget->isAlive()) return;
	if(u_caster != unitTarget) return;

	Aura * pAura;
	std::map<uint32,Aura*>::iterator itr=unitTarget->tmpAura.find(GetProto()->Id);
	if(itr==unitTarget->tmpAura.end())
	{
		pAura = AuraPool.PooledNew();
		if (!pAura)
			return;
		pAura->Init(GetProto(),GetDuration(),m_caster,unitTarget);

		unitTarget->tmpAura [GetProto()->Id]= pAura;

		float r = GetRadius(i);
		if(!sEventMgr.HasEvent(pAura, EVENT_AREAAURA_UPDATE))		/* only add it once */
			sEventMgr.AddEvent(pAura, &Aura::EventUpdateAA, r*r, EVENT_AREAAURA_UPDATE, 1000, 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

	}else
	{
		pAura = itr->second;
	}

	pAura->AddMod(GetProto()->EffectApplyAuraName[i],damage,GetProto()->EffectMiscValue[i],i);
}

void Spell::SpellEffectLearnSpell(uint32 i) // Learn Spell
{
	if(playerTarget == 0 && unitTarget && unitTarget->IsPet()) // something's wrong with this logic here.
	{
		// bug in target map fill?
		//playerTarget = m_caster->GetMapMgr()->GetPlayer((uint32)m_targets.m_unitTarget);
		SpellEffectLearnPetSpell(i);
		return;
	}

	if( GetProto()->Id == 483 || GetProto()->Id == 55884 )        // "Learning"
	{
		if( !i_caster || !p_caster ) return;

		uint32 spellid = 0;
		for(int i = 0; i < 5; ++i)
		{
			if( i_caster->GetProto()->Spells[i].Trigger == LEARNING && i_caster->GetProto()->Spells[i].Id != 0 )
			{
				spellid = i_caster->GetProto()->Spells[i].Id;
				break;
			}
		}

		if( !spellid || !dbcSpell.LookupEntryForced(spellid) ) return;

		// learn me!
		p_caster->addSpell( spellid );

		// no normal handler
		return;
	}

	if(playerTarget)
	{
		/*if(u_caster && isHostile(playerTarget, u_caster))
		return;*/

		uint32 spellToLearn = GetProto()->EffectTriggerSpell[i];
		playerTarget->addSpell(spellToLearn);

		if( spellToLearn == 2575 ) //hacky fix for mining from creatures
			playerTarget->addSpell( 32606 );

		if( spellToLearn == 2366 ) //hacky fix for herbalism from creatures
			playerTarget->addSpell( 32605 );

		//smth is wrong here, first we add this spell to player then we may cast it on player...
		SpellEntry *spellinfo = dbcSpell.LookupEntry(spellToLearn);
		//remove specializations
		switch(spellinfo->Id)
		{
		case 26801: //Shadoweave Tailoring
			playerTarget->removeSpell(26798, false, false, 0); //Mooncloth Tailoring
			playerTarget->removeSpell(26797, false, false, 0); //Spellfire Tailoring
			break;
		case 26798: // Mooncloth Tailoring
			playerTarget->removeSpell(26801, false, false, 0); //Shadoweave Tailoring
			playerTarget->removeSpell(26797, false, false, 0); //Spellfire Tailoring
			break;
		case 26797: //Spellfire Tailoring
			playerTarget->removeSpell(26801, false, false, 0); //Shadoweave Tailoring
			playerTarget->removeSpell(26798, false, false, 0); //Mooncloth Tailoring
			break;
		case 10656: //Dragonscale Leatherworking
			playerTarget->removeSpell(10658, false, false, 0); //Elemental Leatherworking
			playerTarget->removeSpell(10660, false, false, 0); //Tribal Leatherworking
			break;
		case 10658: //Elemental Leatherworking
			playerTarget->removeSpell(10656, false, false, 0); //Dragonscale Leatherworking
			playerTarget->removeSpell(10660, false, false, 0); //Tribal Leatherworking
			break;
		case 10660: //Tribal Leatherworking
			playerTarget->removeSpell(10656, false, false, 0); //Dragonscale Leatherworking
			playerTarget->removeSpell(10658, false, false, 0); //Elemental Leatherworking
			break;
		case 28677: //Elixir Master
			playerTarget->removeSpell(28675, false, false, 0); //Potion Master
			playerTarget->removeSpell(28672, false, false, 0); //Transmutation Maste
			break;
		case 28675: //Potion Master
			playerTarget->removeSpell(28677, false, false, 0); //Elixir Master
			playerTarget->removeSpell(28672, false, false, 0); //Transmutation Maste
			break;
		case 28672: //Transmutation Master
			playerTarget->removeSpell(28675, false, false, 0); //Potion Master
			playerTarget->removeSpell(28677, false, false, 0); //Elixir Master
			break;
		case 20219: //Gnomish Engineer
			playerTarget->removeSpell(20222, false, false, 0); //Goblin Engineer
			break;
		case 20222: //Goblin Engineer
			playerTarget->removeSpell(20219, false, false, 0); //Gnomish Engineer
			break;
		case 9788: //Armorsmith
			playerTarget->removeSpell(9787, false, false, 0); //Weaponsmith
			playerTarget->removeSpell(17039, false, false, 0); //Master Swordsmith
			playerTarget->removeSpell(17040, false, false, 0); //Master Hammersmith
			playerTarget->removeSpell(17041, false, false, 0); //Master Axesmith
			break;
		case 9787: //Weaponsmith
			playerTarget->removeSpell(9788, false, false, 0); //Armorsmith
			break;
		case 17041: //Master Axesmith
			playerTarget->removeSpell(9788, false, false, 0); //Armorsmith
			playerTarget->removeSpell(17040, false, false, 0); //Master Hammersmith
			playerTarget->removeSpell(17039, false, false, 0); //Master Swordsmith
			break;
		case 17040: //Master Hammersmith
			playerTarget->removeSpell(9788, false, false, 0); //Armorsmith
			playerTarget->removeSpell(17039, false, false, 0); //Master Swordsmith
			playerTarget->removeSpell(17041, false, false, 0); //Master Axesmith
			break;
		case 17039: //Master Swordsmith
			playerTarget->removeSpell(9788, false, false, 0); //Armorsmith
			playerTarget->removeSpell(17040, false, false, 0); //Master Hammersmith
			playerTarget->removeSpell(17041, false, false, 0); //Master Axesmith
			break;
		}
		for(uint32 i = 0; i<3; i++)
			if(spellinfo->Effect[i] == SPELL_EFFECT_WEAPON ||
				spellinfo->Effect[i] == SPELL_EFFECT_PROFICIENCY ||
				spellinfo->Effect[i] == SPELL_EFFECT_DUAL_WIELD )
			{
				Spell *sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init(unitTarget, spellinfo, true, NULL);
				SpellCastTargets targets;
				targets.m_unitTarget = unitTarget->GetGUID();
				targets.m_targetMask = 0x02;
				sp->prepare(&targets);
				break;
			}
			return;
	}

	// if we got here... try via pet spells..
	SpellEffectLearnPetSpell(i);
}

void Spell::SpellEffectSpellDefense(uint32 i)
{
	//used to enable this ability. We use it all the time ...
}

void Spell::SpellEffectDispel(uint32 i) // Dispel
{
	if(!u_caster || !unitTarget) return;

	Aura *aur;
	uint32 start, end;
	if(isAttackable(u_caster,unitTarget) || GetProto()->EffectMiscValue[i] == DISPEL_STEALTH ) // IsAttackable returns false for stealthed
	{
		start = MAX_POSITIVE_AURAS_EXTEDED_START;
		end = MAX_POSITIVE_AURAS_EXTEDED_END;
		if (unitTarget->SchoolImmunityList[GetProto()->School])
			return;
	}
	else
	{
		start = MAX_NEGATIVE_AURAS_EXTEDED_START;
		end = MAX_NEGATIVE_AURAS_EXTEDED_END;
	}

	WorldPacket data(SMSG_SPELLDISPELLOG, 16);

	bool finish = false;

	for(uint32 x = start; x<end; x++)
		if(unitTarget->m_auras[x])
		{
			bool AuraRemoved = false;
			aur = unitTarget->m_auras[x];
			//Nothing can dispel resurrection sickness;
			if(!aur->IsPassive() && !(aur->GetSpellProto()->Attributes & ATTRIBUTES_IGNORE_INVULNERABILITY))
			{
				if(GetProto()->DispelType == DISPEL_ALL)
				{
					unitTarget->HandleProc( PROC_ON_PRE_DISPELL_AURA_VICTIM , u_caster , GetProto(), aur->GetSpellId() );

					data.clear();
					data << m_caster->GetNewGUID();
					data << unitTarget->GetNewGUID();
					data << (uint32)1;//probably dispel type
					data << aur->GetSpellId();
					m_caster->SendMessageToSet( &data, true );
					unitTarget->RemoveAura( aur );
					/*
					RemoveAura calls Unit::RemoveAura
					Which then says:
						aur->Remove();
						return true;
					Can we please start reading. Thanks.
					*/
					//AuraRemoved = true;

					if(!--damage)
						// Just return, we're fucking done.
						//finish = true;
						return;
				}
				else if(aur->GetSpellProto()->DispelType == GetProto()->EffectMiscValue[i])
				{
					unitTarget->HandleProc( PROC_ON_PRE_DISPELL_AURA_VICTIM , u_caster , GetProto(), aur->GetSpellId() );

					data.clear();
					data << m_caster->GetNewGUID();
					data << unitTarget->GetNewGUID();
					data << (uint32)1;
					data << aur->GetSpellId();
					m_caster->SendMessageToSet(&data,true);
					unitTarget->RemoveAllAuras(aur->GetSpellProto()->Id,aur->GetCasterGUID());
					AuraRemoved = true;

					if(!--damage)
						finish = true;
				}

				if (AuraRemoved)
				{
					if( aur->GetSpellProto()->NameHash == SPELL_HASH_UNSTABLE_AFFLICTION )
					{
						SpellEntry *spellInfo = dbcSpell.LookupEntry(31117);
						if ( spellInfo )
						{
							Spell *spell = SpellPool.PooledNew();
							if (!spell)
								return;
							spell->Init(u_caster, spellInfo, true, NULL);
							spell->forced_basepoints[0] = (aur->GetSpellProto()->EffectBasePoints[0]+1)*9; //damage effect
							spell->ProcedOnSpell = GetProto();
							spell->pSpellId = aur->GetSpellId();
							SpellCastTargets targets;
							targets.m_unitTarget = u_caster->GetGUID();
							spell->prepare(&targets);
						}
					}
					/*else if ( aur->GetSpellProto()->NameHash == SPELL_HASH_LIFEBLOOM )
					{
					Spell* spell= new Spell(aur->GetCaster(), aur->GetSpellProto(), true, NULL);
					spell->SetUnitTarget( unitTarget );
					spell->Heal( aur->mod->m_amount );
					}*/
				}

			}
			if (finish)
				return;
		}
}

void Spell::SpellEffectLanguage(uint32 i)
{
	if(!playerTarget || !GetProto()->EffectMiscValue[i])
		return;

	uint32 skills[15][2] = {
	{ 0, 0 },
	{ SKILL_LANG_ORCISH, 669 },
	{ SKILL_LANG_DARNASSIAN, 671 },
	{ SKILL_LANG_TAURAHE, 670 },
	{ SKILL_LANG_DWARVEN, 672 },
	{ SKILL_LANG_COMMON, 668 },
	{ SKILL_LANG_DEMON_TONGUE, 815 },
	{ SKILL_LANG_TITAN, 816 },
	{ SKILL_LANG_THALASSIAN, 813 },
	{ SKILL_LANG_DRACONIC, 814 },
	{ 0, 0 },
	{ SKILL_LANG_GNOMISH, 7430 },
	{ SKILL_LANG_TROLL, 7431 },
	{ SKILL_LANG_GUTTERSPEAK, 17737 },
	{ SKILL_LANG_DRAENEI, 29932 },
	};

	if(skills[GetProto()->EffectMiscValue[i]][0])
	{
		playerTarget->_AddSkillLine(skills[GetProto()->EffectMiscValue[i]][0], 300, 300);   
		playerTarget->addSpell(skills[GetProto()->EffectMiscValue[i]][1]);
	}
}

void Spell::SpellEffectDualWield(uint32 i)
{
	if(m_caster->GetTypeId() != TYPEID_PLAYER) return;

	Player *pPlayer = static_cast< Player* >( m_caster );

	if( !pPlayer->_HasSkillLine( SKILL_DUAL_WIELD ) )
		pPlayer->_AddSkillLine( SKILL_DUAL_WIELD, 1, 1 );

	// Increase it by one
	//dual wield is 1/1 , it never increases it's not even displayed in skills tab

	//note: probably here must be not caster but unitVictim
}

void Spell::SpellEffectSummonWild(uint32 i)  // Summon Wild
{
	//these are some creatures that have your faction and do not respawn
	//number of creatures is actually dmg (the usual formula), sometimes =3 sometimes =1
	if( !u_caster || !u_caster->IsInWorld() ) return;

	uint32 cr_entry=GetProto()->EffectMiscValue[i];
	CreatureProto * proto = CreatureProtoStorage.LookupEntry(cr_entry);
	CreatureInfo * info = CreatureNameStorage.LookupEntry(cr_entry);
	if(!proto || !info)
	{
		sLog.outDetail("Warning : Missing summon creature template %u used by spell %u!",cr_entry,GetProto()->Id);
		return;
	}
	float x, y, z;
	if( m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION && m_targets.m_destX && m_targets.m_destY && m_targets.m_destZ )
	{
		x = m_targets.m_destX;
		y = m_targets.m_destY;
		z = m_targets.m_destZ;
	}
	else
	{
		x = u_caster->GetPositionX();
		y = u_caster->GetPositionY();
		z = u_caster->GetPositionZ();
	}
	for(int i=0;i<damage;i++)
	{
		float m_fallowAngle=-((float(M_PI)/2)*i);
		x += (GetRadius(i)*(cosf(m_fallowAngle+u_caster->GetOrientation())));
		y += (GetRadius(i)*(sinf(m_fallowAngle+u_caster->GetOrientation())));
		Creature * p = u_caster->GetMapMgr()->CreateCreature(cr_entry);
		//ASSERT(p);
		p->Load(proto, x, y, z);
		p->SetZoneId( m_caster->GetZoneId() );

		if ( p->GetProto() && p->GetProto()->Faction == 35 )
		{
			p->SetUInt64Value( UNIT_FIELD_SUMMONEDBY, m_caster->GetGUID() );
			p->SetUInt64Value( UNIT_FIELD_CREATEDBY, m_caster->GetGUID() );
			p->SetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE, u_caster->GetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE ) );
		}
		else
		{
			p->SetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE, proto->Faction );
		}

		p->m_faction = dbcFactionTemplate.LookupEntry(proto->Faction);
		if(p->m_faction)
			p->m_factionDBC = dbcFaction.LookupEntry(p->m_faction->Faction);
		p->PushToWorld(u_caster->GetMapMgr());
		//make sure they will be desummoned (roxor)
		sEventMgr.AddEvent(p, &Creature::SummonExpire, EVENT_SUMMON_EXPIRE, GetDuration(), 1,0);
	}
}

void Spell::SpellEffectSummonGuardian(uint32 i) // Summon Guardian
{
	GameObject * obj = NULL; //Snake trap part 1
	LocationVector * vec = NULL;

	if ( g_caster && g_caster->m_summoner)
	{
		u_caster = g_caster->m_summoner; //set the caster to the summoner unit
		obj = g_caster; //and keep the trap info
	}
	if( !u_caster ) return;

	uint32 cr_entry = GetProto()->EffectMiscValue[i];
	uint32 level = 0;

	if( GetProto()->c_is_flags & SPELL_FLAG_IS_INHERITING_LEVEL )
		level = u_caster->getLevel();
	/*if ( u_caster->GetTypeId()==TYPEID_PLAYER && itemTarget )
	{
	if (itemTarget->GetProto() && itemTarget->GetProto()->RequiredSkill == SKILL_ENGINERING)
	{
	uint32 skill202 = static_cast< Player* >( m_caster )->_GetSkillLineCurrent(SKILL_ENGINERING);
	if (skill202>0)
	{
	level = skill202/5;
	}
	}
	}*/
	if( m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION && m_targets.m_destX && m_targets.m_destY && m_targets.m_destZ )
	{
		vec = new LocationVector(m_targets.m_destX, m_targets.m_destY, m_targets.m_destZ);
	}

	if(GetProto()->Id == 29731 || GetProto()->Id == 1122 || cr_entry == 26125)
		damage = 1;

	float angle_for_each_spawn = -float(M_PI) * 2 / damage;
	for( int i = 0; i < damage; i++ )
	{
		float m_fallowAngle = angle_for_each_spawn * i;
		if(cr_entry == 89)
		{
			Unit *  un = u_caster->CreateTemporaryInfernal(cr_entry,GetDuration(),angle_for_each_spawn * 1,level, m_targets.m_srcX, m_targets.m_srcY, m_targets.m_srcZ	);
			//u_caster->CastSpell(un, 61191, true);	
		}
		else
		{
			Unit * un = u_caster->create_guardian(cr_entry,GetDuration(), m_fallowAngle, level, obj, vec );
			if( p_caster && p_caster->CombatStatus.IsInCombat())
				un->GetAIInterface()->AttackReaction(u_caster->GetMapMgr()->GetUnit(p_caster->GetSelection()), 1, 0);
			else if(u_caster->IsCreature() && u_caster->GetAIInterface()->GetNextTarget())
				un->GetAIInterface()->AttackReaction(u_caster->GetAIInterface()->GetNextTarget(), 0);;
		}
	}
	//if(cr_entry == 89)

	if (vec) delete vec;
	return;
}

void Spell::SpellEffectSkillStep(uint32 i) // Skill Step
{
	Player*target;
	if(m_caster->GetTypeId() != TYPEID_PLAYER)
	{
		// Check targets
		if( m_targets.m_unitTarget )
		{
			target = objmgr.GetPlayer((uint32)m_targets.m_unitTarget);
			if( !target ) return;
		}
		else return;
	}
	else
	{
		target = static_cast< Player* >( m_caster );
	}

	uint32 skill = GetProto()->EffectMiscValue[i];
	if( skill == 242 )
		skill = SKILL_LOCKPICKING; // somehow for lockpicking misc is different than the skill :s

	skilllineentry* sk = dbcSkillLine.LookupEntry( skill );

	if( !sk ) return;

	uint32 max = 1;
	switch( sk->type )
	{
	case SKILL_TYPE_PROFESSION:
	case SKILL_TYPE_SECONDARY:	max = damage * 75; break;
	case SKILL_TYPE_WEAPON:		max = 5 * target->getLevel(); break;
	case SKILL_TYPE_CLASS:
	case SKILL_TYPE_ARMOR:
		if( skill == SKILL_LOCKPICKING ) { max = damage * 75; }
		else { max = 1; }
		break;
	default: //u cant learn other types in game
		return;
	};

	if( target->_HasSkillLine( skill ) )
	{
		target->_ModifySkillMaximum( skill, max );
	}
	else
	{
		// Don't add skills to players logging in.
		/*if((GetProto()->Attributes & 64) && playerTarget->m_TeleportState == 1)
		return;*/

		if( sk->type == SKILL_TYPE_PROFESSION )
			target->ModUnsigned32Value( PLAYER_CHARACTER_POINTS2, -1 );

		if( skill == SKILL_RIDING )
			target->_AddSkillLine( skill, max, max );
		else
			target->_AddSkillLine( skill, 1, max );
	}
}

void Spell::SpellEffectAddHonor(uint32 i)
{
	if( !playerTarget ) return;

	uint32 val = GetProto()->EffectBasePoints[i];

	if( GetProto()->AttributesExB & FLAGS3_UNK4 )val /= 10;

	val += 1;

	HonorHandler::AddHonorPointsToPlayer( playerTarget, val );

	WorldPacket data(SMSG_PVP_CREDIT, 16);
	data << val;
	data << uint64(0);
	data << uint32(5);
	playerTarget->GetSession()->SendPacket(&data);
}

void Spell::SpellEffectSpawn(uint32 i)
{
	// this effect is mostly for custom teleporting
	switch(GetProto()->Id)
	{
	case 10418: // Arugal spawn-in spell , teleports it to 3 locations randomly sneaking players (bastard ;P)
		{
			if(!u_caster || u_caster->IsPlayer())
				return;

			static float coord[3][3]= {{-108.9034f,2129.5678f,144.9210f},{-108.9034f,2155.5678f,155.678f},{-77.9034f,2155.5678f,155.678f}};

			int i = (int)(rand()%3);
			u_caster->GetAIInterface()->SendMoveToPacket(coord[i][0],coord[i][1],coord[i][2],0.0f,0,u_caster->GetAIInterface()->getMoveFlags());
		}
	}
}

void Spell::SpellEffectSummonObject(uint32 i)
{
	if( !u_caster ) return;

	uint32 entry = GetProto()->EffectMiscValue[i];

	uint32 mapid = u_caster->GetMapId();
	float px = u_caster->GetPositionX();
	float py = u_caster->GetPositionY();
	float pz = u_caster->GetPositionZ();
	float orient = m_caster->GetOrientation();
	float posx = 0,posy = 0,posz = 0;

	if( entry == GO_FISHING_BOBBER && p_caster)
	{
		float co = cos( orient );
		float si = sin( orient );
		MapMgr * map = m_caster->GetMapMgr();
		Spell * spell = u_caster->GetCurrentSpell();

		float r;
		for( r = 20; r > 10; r-- )
		{
			posx = px + r * co;
			posy = py + r * si;
			if( !(map->GetWaterType( posx, posy ) & 1) )//water
				continue;
			posz = map->GetWaterHeight( posx, posy );
			if( posz > map->GetLandHeight( posx, posy ) )//water
				break;
		}

		posx = px + r * co;
		posy = py + r * si;

		// Todo / Fix me: This should be loaded / cached
		uint32 zone = p_caster->GetAreaID();
		if( zone == 0 ) // If the player's area ID is 0, use the zone ID instead
			zone = p_caster->GetZoneId();

		uint32 minskill;
		FishingZoneEntry *fishentry = FishingZoneStorage.LookupEntry( zone );
		if( !fishentry ) // Check database if there is fishing area / zone information, if not, return
			return;

		// Todo / Fix me: Add fishskill to the calculations
		minskill = fishentry->MinSkill;
		spell->SendChannelStart( 20000 ); // 30 seconds
		/*spell->SendSpellStart();
		spell->SendCastResult(SPELL_CANCAST_OK);
		spell->SendSpellGo ();*/

		GameObject *go = u_caster->GetMapMgr()->CreateGameObject(GO_FISHING_BOBBER);

		go->CreateFromProto( GO_FISHING_BOBBER, mapid, posx, posy, posz, orient );
		go->SetUInt32Value( GAMEOBJECT_FLAGS, 0 );
		go->SetByte( GAMEOBJECT_BYTES_1, 0, 0 );
		go->SetUInt64Value( OBJECT_FIELD_CREATED_BY, m_caster->GetGUID() );
		u_caster->SetUInt64Value( UNIT_FIELD_CHANNEL_OBJECT, go->GetGUID() );

		go->SetInstanceID( m_caster->GetInstanceID() );
		go->PushToWorld( m_caster->GetMapMgr() );

		if( lootmgr.IsFishable( zone ) ) // Only set a 'splash' if there is any loot in this area / zone
		{
			uint32 seconds = RandomUInt(17) + 2;
			sEventMgr.AddEvent( go, &GameObject::FishHooked, static_cast< Player* >( m_caster ), EVENT_GAMEOBJECT_FISH_HOOKED, seconds * 1000, 1, 0 );
		}
		sEventMgr.AddEvent( go, &GameObject::EndFishing, static_cast< Player* >( m_caster ),false, EVENT_GAMEOBJECT_END_FISHING, 20000, 1, 0 );
		p_caster->SetSummonedObject( go );
	}
	else
	{
		posx=px;
		posy=py;
		GameObjectInfo * goI = GameObjectNameStorage.LookupEntry(entry);
		if(!goI)
		{
			if( p_caster )
			{
				sChatHandler.BlueSystemMessage(p_caster->GetSession(), "non-existent gameobject %u tried to be created by SpellEffectSummonObject. Report to devs!", entry);
			}
			return;
		}
		if( m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION && m_targets.m_destX && m_targets.m_destY && m_targets.m_destZ )
		{
			posx = m_targets.m_destX;
			posy = m_targets.m_destY;
			pz = m_targets.m_destZ;
		}
		GameObject *go=m_caster->GetMapMgr()->CreateGameObject(entry);

		go->SetInstanceID(m_caster->GetInstanceID());
		go->CreateFromProto(entry,mapid,posx,posy,pz,orient);
		go->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		go->SetUInt64Value(OBJECT_FIELD_CREATED_BY,m_caster->GetGUID());
		go->PushToWorld(m_caster->GetMapMgr());
		sEventMgr.AddEvent(go, &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_EXPIRE, GetDuration(), 1,0);
		if ( entry == 17032 && p_caster) // this is a portal
		{
			// enable it for party only
			go->SetByte( GAMEOBJECT_BYTES_1, 0, 0 );
			//disable by default
			WorldPacket * pkt = go->BuildFieldUpdatePacket(GAMEOBJECT_BYTES_1, 1 << 24);
			SubGroup * pGroup = p_caster->GetGroup() ? p_caster->GetGroup()->GetSubGroup(p_caster->GetSubGroup()) : NULL;

			if ( pGroup )
			{
				p_caster->GetGroup()->Lock();
				for ( GroupMembersSet::iterator itr = pGroup->GetGroupMembersBegin(); itr != pGroup->GetGroupMembersEnd(); ++itr )
				{
					if( (*itr)->m_loggedInPlayer && m_caster != (*itr)->m_loggedInPlayer )
						(*itr)->m_loggedInPlayer->GetSession()->SendPacket( pkt );
				}
				p_caster->GetGroup()->Unlock();
			}
			delete pkt;
		}
		else if ( entry == 36727 || entry == 177193 || entry == 194108 ) // Portal of Summoning and portal of doom
		{
			if(!p_caster) return;

			//Player * pTarget = p_caster->GetMapMgr()->GetPlayer( p_caster->GetSelection() );
			Player * pTarget = objmgr.GetPlayer( (uint32)p_caster->GetSelection() );
			if ( !pTarget || !pTarget->IsInWorld() )
				return;
			go->m_ritualmembers[0] = p_caster->GetLowGUID();
			go->m_ritualcaster = p_caster->GetLowGUID();
			go->m_ritualtarget = pTarget->GetLowGUID();
			go->m_ritualspell = static_cast<uint16>( GetProto()->Id );
		}
		else if ( entry == 186811 || entry == 181622 ) // ritual of refreshment, ritual of souls
		{
			if(!p_caster) return;

			go->m_ritualmembers[0] = p_caster->GetLowGUID();
			go->m_ritualcaster = p_caster->GetLowGUID();
			go->m_ritualtarget = 0;
			go->m_ritualspell = static_cast<uint16>( GetProto()->Id );
		}
		else if ( entry == 186812 || entry == 181621 ) // Refreshment Table, Soulwell
		{
			go->charges = goI->sound1;
		}
		else//Lightwell,if there is some other type -- add it
		{
			go->charges = 5;//Max 5 charges
		}
		if(p_caster)
			p_caster->SetSummonedObject(go);//p_caster
	}
}

void Spell::SpellEffectEnchantItem(uint32 i) // Enchant Item Permanent
{
	if(!itemTarget || !p_caster) 
		return;

	// Vellums
	if( GetProto()->EffectItemType[i] && ( itemTarget->GetEntry() == 39349 || 
		itemTarget->GetEntry() == 39350 || itemTarget->GetEntry() == 43146 ||
		itemTarget->GetEntry() == 38682 || itemTarget->GetEntry() == 37602 || 
		itemTarget->GetEntry() == 43145 ))
	{
		uint32 itemid = GetProto()->EffectItemType[i];
		ItemPrototype * it = ItemPrototypeStorage.LookupEntry( itemid );
		if( it == NULL )
		{
			p_caster->GetSession()->SystemMessage("Item is missing, report this to devs. Entry: %u", itemid);
			return;
		}

		Item * pItem = objmgr.CreateItem( itemid, p_caster );
		if( pItem == NULL )
			return;

		p_caster->GetItemInterface()->RemoveItemAmt( itemTarget->GetEntry(), 1 );
		p_caster->GetItemInterface()->AddItemToFreeSlot( pItem );

		return;
	}

	EnchantEntry * Enchantment = dbcEnchant.LookupEntry(GetProto()->EffectMiscValue[i]);

	if(!Enchantment) 
		return;

	if(p_caster->GetSession()->GetPermissionCount() > 0)
		sGMLog.writefromsession(p_caster->GetSession(), "enchanted item for %s", itemTarget->GetOwner()->GetName());

	//remove other perm enchantment that was enchanted by profession
	itemTarget->RemoveProfessionEnchant();
	int32 Slot = itemTarget->AddEnchantment(Enchantment, 0, true, true, false, 0);
	if(Slot < 0)
		return; // Apply failed

	if( GetProto()->EffectItemType[i] == 0 || ( GetProto()->EffectItemType[i] != 0 && i_caster != NULL && GetProto()->EffectItemType[i] != i_caster->GetEntry()) )
		DetermineSkillUp(SKILL_ENCHANTING);
}

void Spell::SpellEffectEnchantItemTemporary(uint32 i)  // Enchant Item Temporary
{
	if(!itemTarget || !p_caster) return;
	uint32 Duration = damage > 1 ? damage : 3600;

	// don't allow temporary enchants unless we're the owner of the item
	if(itemTarget->GetOwner() != p_caster) return;

	EnchantEntry * Enchantment = dbcEnchant.LookupEntry(GetProto()->EffectMiscValue[i]);
	if(!Enchantment) return;

	itemTarget->RemoveEnchantment(1);
	int32 Slot = itemTarget->AddEnchantment(Enchantment, Duration, false, true, false, 1);
	if(Slot < 0) return; // Apply failed

	skilllinespell* skill = objmgr.GetSpellSkill(GetProto()->Id);
	if(skill)
		DetermineSkillUp(skill->skilline,itemTarget->GetProto()->ItemLevel);
}

void Spell::SpellEffectTameCreature(uint32 i)
{
	Creature* tame = ( ( unitTarget->GetTypeId() == TYPEID_UNIT ) ? static_cast< Creature* >( unitTarget ) : NULL );
	if( !tame ) return;

	// Remove target
	tame->GetAIInterface()->HandleEvent(EVENT_LEAVECOMBAT, p_caster, 0);
	Pet *pPet = objmgr.CreatePet( tame->GetEntry() );
	pPet->CreateAsSummon(tame->GetEntry(), tame->GetCreatureInfo(), tame, p_caster, NULL, 2, 0);
	tame->Despawn(0,tame->GetProto()? tame->GetProto()->RespawnTime:0);
}

void Spell::SpellEffectSummonPet(uint32 i) //summon - pet
{
	if( !p_caster ) return;

	if( GetProto()->Id == 883 )// "Call Pet" spell
	{
		if( p_caster->GetSummon() )
		{
			p_caster->GetSession()->SendNotification("You already have a pet summoned.");
			return;
		}

		uint32 petno = p_caster->GetUnstabledPetNumber();

		if( petno )
		{
			p_caster->SpawnPet(petno);
		}
		else
		{
			WorldPacket data(SMSG_AREA_TRIGGER_MESSAGE, 50);
			data << uint32(0) << "You do not have any pets to call." << uint8(0);
			p_caster->GetSession()->SendPacket(&data);
		}
		return;
	}

	//uint32 entryId = GetProto()->EffectMiscValue[i];

	//VoidWalker:torment, sacrifice, suffering, consume shadows
	//Succubus:lash of pain, soothing kiss, seduce , lesser invisibility
	//felhunter:	 Devour Magic,Paranoia,Spell Lock,	Tainted Blood

	// remove old pet
	Pet *old = static_cast< Player* >(m_caster)->GetSummon();
	if(old)
		old->Dismiss();

	CreatureInfo *ci = CreatureNameStorage.LookupEntry( GetProto()->EffectMiscValue[i] );
	if( ci )
	{
		if(p_caster->getClass() == WARLOCK)
		{
			//if demonic sacrifice auras are still active, remove them
			p_caster->RemoveAura(18789);
			p_caster->RemoveAura(18790);
			p_caster->RemoveAura(18791);
			p_caster->RemoveAura(18792);
			p_caster->RemoveAura(35701);
		}

		Pet *summon = objmgr.CreatePet( GetProto()->EffectMiscValue[i] );
		summon->CreateAsSummon( GetProto()->EffectMiscValue[i], ci, NULL, p_caster, GetProto(), 1, 0 );
	}
}

void Spell::SpellEffectLearnPetSpell(uint32 i)
{
	/*if(unitTarget && m_caster->GetTypeId() == TYPEID_PLAYER)
	{
	if(unitTarget->IsPet() && unitTarget->GetTypeId() == TYPEID_UNIT)
	{
	static_cast< Player* >(m_caster)->AddPetSpell(GetProto()->EffectTriggerSpell[i], unitTarget->GetEntry());
	}
	}*/

	if(unitTarget && unitTarget->IsPet() && p_caster)
	{
		Pet * pPet = static_cast<Pet*>( unitTarget );
		if(pPet->IsSummon())
			p_caster->AddSummonSpell(unitTarget->GetEntry(), GetProto()->EffectTriggerSpell[i]);

		pPet->AddSpell( dbcSpell.LookupEntry( GetProto()->EffectTriggerSpell[i] ), true );

		// Send Packet
		/*		WorldPacket data(SMSG_SET_EXTRA_AURA_INFO_OBSOLETE, 22);
		data << pPet->GetGUID() << uint8(0) << uint32(GetProto()->EffectTriggerSpell[i]) << uint32(-1) << uint32(0);
		p_caster->GetSession()->SendPacket(&data);*/
	}
}

void Spell::SpellEffectWeapondamage( uint32 i ) // Weapon damage +
{
	if( !unitTarget || !u_caster ) return;

	//Hackfix for Mangle
	if( GetProto()->NameHash == SPELL_HASH_MANGLE___CAT && u_caster->IsPlayer() )
		static_cast< Player* >( u_caster )->AddComboPoints( unitTarget->GetGUID(), 1 );

	// Hacky fix for druid spells where it would "double attack".
	if( GetProto()->Effect[2] == SPELL_EFFECT_WEAPON_PERCENT_DAMAGE || GetProto()->Effect[1] == SPELL_EFFECT_WEAPON_PERCENT_DAMAGE )
	{
		add_damage += damage;
		return;
	}

	uint32 _type;
	if( GetType() == SPELL_DMG_TYPE_RANGED )
		_type = RANGED;
	else
	{
		if (GetProto()->AttributesExC & 0x1000000)
			_type =  OFFHAND;
		else
			_type = MELEE;
	}
	u_caster->Strike( unitTarget, _type, GetProto(), damage, 0, 0, false, true );
}

void Spell::SpellEffectOpenLockItem(uint32 i)
{
	Unit* caster = u_caster;
	if(!caster && i_caster) caster = i_caster->GetOwner();

	if(!gameObjTarget || !gameObjTarget->IsInWorld()) return;

	if( caster && caster->IsPlayer() && sQuestMgr.OnGameObjectActivate( (static_cast<Player*>(caster)), gameObjTarget ) )
		static_cast<Player*>(caster)->UpdateNearbyGameObjects();

	CALL_GO_SCRIPT_EVENT(gameObjTarget, OnActivate)(static_cast<Player*>(caster));
	CALL_INSTANCE_SCRIPT_EVENT( gameObjTarget->GetMapMgr(), OnGameObjectActivate )( gameObjTarget, TO_PLAYER( caster ) ); 
	gameObjTarget->SetByte(GAMEOBJECT_BYTES_1, 0, 0);

	if( gameObjTarget->GetEntry() == 183146)
	{
		gameObjTarget->Despawn(0, 1);
		return;
	}

	if( gameObjTarget->GetByte( GAMEOBJECT_BYTES_1, 1 ) == GAMEOBJECT_TYPE_CHEST)
	{
		lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetEntry(), gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->iInstanceMode ? true : false) : false);
		if(gameObjTarget->loot.items.size() > 0)
		{
			static_cast<Player*>(caster)->SendLoot(gameObjTarget->GetGUID(),LOOT_CORPSE);
		}
	}

	// cebernic: atm doors works fine.
	if( gameObjTarget->GetByte( GAMEOBJECT_BYTES_1, 1 ) == GAMEOBJECT_TYPE_DOOR
		|| gameObjTarget->GetByte( GAMEOBJECT_BYTES_1, 1 ) == GAMEOBJECT_TYPE_GOOBER )
		gameObjTarget->SetUInt32Value(GAMEOBJECT_FLAGS, gameObjTarget->GetUInt32Value( GAMEOBJECT_FLAGS ) | 1);

	if(gameObjTarget->GetMapMgr()->GetMapInfo()->type==INSTANCE_NULL)//don't close doors for instances
		sEventMgr.AddEvent(gameObjTarget,&GameObject::EventCloseDoor, EVENT_GAMEOBJECT_DOOR_CLOSE,10000,1,0);

	sEventMgr.AddEvent(gameObjTarget, &GameObject::Despawn, (uint32)0, (uint32)1, EVENT_GAMEOBJECT_ITEM_SPAWN, 6*60*1000, 1, 0);
}

void Spell::SpellEffectProficiency(uint32 i)
{
	uint32 skill = 0;
	skilllinespell *skillability = objmgr.GetSpellSkill(GetProto()->Id);
	if (skillability)
		skill = skillability->skilline;
	skilllineentry *sk = dbcSkillLine.LookupEntry(skill);
	if(skill)
	{
		if(playerTarget)
		{
			if(playerTarget->_HasSkillLine(skill))
			{
				// Increase it by one
				// playerTarget->AdvanceSkillLine(skill);
			}
			else
			{
				// Don't add skills to players logging in.
				/*if((GetProto()->Attributes & 64) && playerTarget->m_TeleportState == 1)
				return;*/

				if(sk && sk->type == SKILL_TYPE_WEAPON)
					playerTarget->_AddSkillLine(skill, 1, 5*playerTarget->getLevel());
				else
					playerTarget->_AddSkillLine(skill, 1, 1);
			}
		}
	}
}

void Spell::SpellEffectSendEvent(uint32 i) //Send Event
{
	//This is mostly used to trigger events on quests or some places

	uint32 spellId = GetProto()->Id;

	// Try a dummy SpellHandler
	if(sScriptMgr.CallScriptedDummySpell(spellId, i, this)) return;

	switch(spellId)
	{

		// WSG Flags
	case 23333:
	case 23335:
		{
			if (p_caster && p_caster->m_bg) {

				if( p_caster->GetTeam() == 1 )
					p_caster->m_bg->SendChatMessage( CHAT_MSG_BG_EVENT_HORDE, p_caster->GetGUID(), "The Alliance flag was picked up by %s!", p_caster->GetName() );
				else
					p_caster->m_bg->SendChatMessage( CHAT_MSG_BG_EVENT_ALLIANCE, p_caster->GetGUID(), "The Horde flag was picked up by %s!", p_caster->GetName() );
			}
		}break;

		// Place Loot
	case 25720: // Places the Bag of Gold at the designated Drop-Off Point.
		{

		}break;

		// Item - Cleansing Vial DND
	case 29297: // Empty the vial near the Bones of Aggonar to cleanse the waters of their demonic taint.
		{
			QuestLogEntry *en=p_caster->GetQuestLogForEntry(9427);
			if(!en) return;
			en->SendQuestComplete();
		}break;

		//Warlock: Summon Succubus Quest
	case 8674:
	case 9223:
	case 9224:
		{
			CreatureInfo * ci = CreatureNameStorage.LookupEntry(5677);
			CreatureProto * cp = CreatureProtoStorage.LookupEntry(5677);
			if( !ci || !cp )
				return;

			Creature * pCreature = p_caster->GetMapMgr()->CreateCreature(cp->Id);
			pCreature->Load(cp, p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
			pCreature->_setFaction();
			pCreature->GetAIInterface()->Init(pCreature, AITYPE_AGRO,MOVEMENTTYPE_NONE);
			pCreature->GetAIInterface()->taunt(p_caster, true);
			pCreature->_setFaction();
			pCreature->PushToWorld(p_caster->GetMapMgr());
			sEventMgr.AddEvent(pCreature, &Creature::SafeDelete, EVENT_CREATURE_REMOVE_CORPSE,60000, 1, 0);
		}break;

		//Warlock: Summon Voidwalker Quest
	case 30208:
	case 9221:
	case 9222:
	case 7728:
		{
			CreatureInfo * ci = CreatureNameStorage.LookupEntry(5676);
			CreatureProto * cp = CreatureProtoStorage.LookupEntry(5676);
			if( !ci || !cp ) return;

			Creature * pCreature = p_caster->GetMapMgr()->CreateCreature(cp->Id);
			pCreature->Load(cp, p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
			pCreature->_setFaction();
			pCreature->GetAIInterface()->Init(pCreature, AITYPE_AGRO,MOVEMENTTYPE_NONE);
			pCreature->GetAIInterface()->taunt(p_caster, true);
			pCreature->_setFaction();
			pCreature->PushToWorld(p_caster->GetMapMgr());
			sEventMgr.AddEvent(pCreature, &Creature::SafeDelete, EVENT_CREATURE_REMOVE_CORPSE,60000, 1, 0);
		}break;

		//Warlock: Summon Felhunter Quest
	case 8712:
		{
			CreatureInfo * ci = CreatureNameStorage.LookupEntry(6268);
			CreatureProto * cp = CreatureProtoStorage.LookupEntry(6268);
			if( !ci || !cp )
				return;

			Creature * pCreature = p_caster->GetMapMgr()->CreateCreature(cp->Id);
			pCreature->Load(cp, p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
			pCreature->_setFaction();
			pCreature->GetAIInterface()->Init(pCreature, AITYPE_AGRO,MOVEMENTTYPE_NONE);
			pCreature->GetAIInterface()->taunt(p_caster, true);
			pCreature->_setFaction();
			pCreature->PushToWorld(p_caster->GetMapMgr());
			sEventMgr.AddEvent(pCreature, &Creature::SafeDelete, EVENT_CREATURE_REMOVE_CORPSE,60000, 1, 0);
		}break;

	}
}

void Spell::SpellEffectPowerBurn(uint32 i) // power burn
{
	if(!unitTarget || !unitTarget->isAlive() || unitTarget->GetPowerType() != POWER_TYPE_MANA)
		return;

	if( unitTarget->IsPlayer() )
	{
		Player* mPlayer = static_cast< Player* >( unitTarget );
		if( mPlayer->IsInFeralForm() )
			return;

		// Resilience - reduces the effect of mana drains by (CalcRating*2)%.
		damage *= float2int32( 1 - ( ( static_cast<Player*>(unitTarget)->CalcRating( PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE ) * 2 ) / 100.0f ) );
	}
	if ( this ) {
			int32 mult = damage;
			damage = mult * unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1) / 100;
			if (m_caster && m_caster->IsUnit() ) {
				Unit* caster = static_cast<Unit*> (this->m_caster);
				if ( (uint32) damage > caster->GetUInt32Value(UNIT_FIELD_MAXPOWER1) * (mult*2) / 100 ) 
					damage = caster->GetUInt32Value(UNIT_FIELD_MAXPOWER1) * (mult*2) / 100;
			}
 	}

	int32 mana = (int32)min( (int32)unitTarget->GetUInt32Value( UNIT_FIELD_POWER1 ), damage );
	unitTarget->ModUnsigned32Value(UNIT_FIELD_POWER1,-mana);

	m_caster->SpellNonMeleeDamageLog(unitTarget,GetProto()->Id, (uint32)(mana * GetProto()->EffectMultipleValue[i]), pSpellId == 0, true);
}

void Spell::SpellEffectThreat(uint32 i) // Threat
{
	if( !unitTarget || !unitTarget->isAlive() || !unitTarget->IsCreature() )
		return;

	int32 amount = GetProto()->EffectBasePoints[i];
	if (GetProto()->SpellGroupType) {
		SM_FIValue(u_caster->SM_FMiscEffect,&amount,GetProto()->SpellGroupType);
		SM_PIValue(u_caster->SM_PMiscEffect,&amount,GetProto()->SpellGroupType);
	}

	bool chck = unitTarget->GetAIInterface()->modThreatByPtr(u_caster, amount);
	if(!chck)
		unitTarget->GetAIInterface()->AttackReaction(u_caster,1,0);
}

void Spell::SpellEffectTriggerSpell(uint32 i) // Trigger Spell
{
	SpellEntry *entry = dbcSpell.LookupEntry( GetProto()->EffectTriggerSpell[i] );
	if( !entry ) 
		return;

	SpellCastTargets targets = m_targets;
	Spell *sp = SpellPool.PooledNew();
	if( !sp )
		return;
	sp->Init( m_caster, entry, true, NULL );
	sp->prepare( &targets );
}

void Spell::SpellEffectPowerFunnel(uint32 i) // Power Funnel
{
	if(!unitTarget || !unitTarget->isAlive() || !unitTarget->IsPet())
		return;

	//does not exist
}

void Spell::SpellEffectHealMaxHealth(uint32 i)   // Heal Max Health
{
	if( !unitTarget || !unitTarget->isAlive() )
		return;

	uint32 dif = unitTarget->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) - unitTarget->GetUInt32Value( UNIT_FIELD_HEALTH );
	if( !dif )
	{
		SendCastResult( SPELL_FAILED_ALREADY_AT_FULL_HEALTH );
		return;
	}

	if( unitTarget->GetTypeId() == TYPEID_PLAYER)
	{
		SendHealSpellOnPlayer( static_cast< Player* >( m_caster ), static_cast< Player* >( unitTarget ), dif, false );
	}
	unitTarget->ModUnsigned32Value( UNIT_FIELD_HEALTH, dif );
}

void Spell::SpellEffectInterruptCast(uint32 i) // Interrupt Cast
{
	// TODO: visual for affected player !!! 

	if(!unitTarget || !unitTarget->isAlive()) 
		return;

	if(!playerTarget)
	{
		if (u_caster && (u_caster != unitTarget))
		{
			unitTarget->GetAIInterface()->AttackReaction(u_caster, 1, m_spellInfo->Id);
			Creature *c = static_cast<Creature*>( unitTarget );
			if (c && c->GetProto() && c->GetProto()->modImmunities)
			{
				if (c->GetProto()->modImmunities & 32768)
					return;
			}
		}
	}

	uint32 school = 0;
	uint32 prevtype = 0;
	if(unitTarget->GetCurrentSpell())
	{
		prevtype = unitTarget->GetCurrentSpell()->GetProto()->PreventionType;

		if((GetProto()->InterruptFlags & CAST_INTERRUPT_ON_INTERRUPT_SCHOOL) && (prevtype == PREVENTION_TYPE_SILENCE))
		{
			school = unitTarget->GetCurrentSpell()->GetProto()->School;
		}

		unitTarget->GetCurrentSpell()->cancel();
	}

	if(school)//prevent from casts in this school
	{
		int32 duration = GetDuration();

		if(unitTarget->IsPlayer())
		{		
			// Check for interruption reducing talents
			int32 DurationModifier = static_cast< Player* >( unitTarget )->MechanicDurationPctMod[MECHANIC_INTERRUPTED];

			if(DurationModifier >= - 100)
				duration = (duration * (100 + DurationModifier)) / 100;
		}

		unitTarget->SchoolCastPrevent[school] = duration + getMSTime();

		if(unitTarget->IsPlayer())
		{
			TO_PLAYER(unitTarget)->SendPreventSchoolCast(school, duration + getMSTime());
		}
	}
	else if((GetProto()->InterruptFlags & CAST_INTERRUPT_ON_INTERRUPT_ALL) && (prevtype == PREVENTION_TYPE_SILENCE))
	{
		int32 duration = GetDuration();

		if(unitTarget->IsPlayer())
		{		
			// Check for interruption reducing talents
			int32 DurationModifier = static_cast< Player* >( unitTarget )->MechanicDurationPctMod[MECHANIC_INTERRUPTED];

			if(DurationModifier >= - 100)
				duration = (duration * (100 + DurationModifier)) / 100;
		}

		for( uint8 j = 0; j < 7; j++)
		{
			unitTarget->SchoolCastPrevent[j] = duration + getMSTime();
			if(unitTarget->IsPlayer())
			{
				TO_PLAYER(unitTarget)->SendPreventSchoolCast(j, duration + getMSTime());
			}
		}
	}
}

void Spell::SpellEffectDistract(uint32 i) // Distract
{
	//spellId 1725 Distract:Throws a distraction attracting the all monsters for ten sec's
	if(!unitTarget || !unitTarget->isAlive())
		return;

	if(m_targets.m_destX != 0.0f || m_targets.m_destY != 0.0f || m_targets.m_destZ != 0.0f)
	{
		//		unitTarget->GetAIInterface()->MoveTo(m_targets.m_destX, m_targets.m_destY, m_targets.m_destZ, 0);
		uint32 Stare_duration = GetDuration();
		if(Stare_duration > 30 * 60 * 1000)
			Stare_duration = 10000;//if we try to stare for more then a half an hour then better not stare at all :P (bug)
		float newo = unitTarget->calcRadAngle(unitTarget->GetPositionX(), unitTarget->GetPositionY(), m_targets.m_destX, m_targets.m_destY);
		unitTarget->GetAIInterface()->StopMovement(Stare_duration);
		unitTarget->SetFacing(newo);
	}

	//Smoke Emitter 164870
	//Smoke Emitter Big 179066
	//Unit Field Target of
}

void Spell::SpellEffectPickpocket(uint32 i) // pickpocket
{
	//Show random loot based on roll,
	if(!unitTarget || !p_caster || unitTarget->GetTypeId() != TYPEID_UNIT)
		return;

	Creature *target = static_cast<Creature*>( unitTarget );
	if(target->IsPickPocketed() || (target->GetCreatureInfo() && target->GetCreatureInfo()->Type != UNIT_TYPE_HUMANOID))
	{
		SendCastResult(SPELL_FAILED_TARGET_NO_POCKETS);
		return;
	}

	lootmgr.FillPickpocketingLoot(&static_cast<Creature*>(unitTarget)->loot,unitTarget->GetEntry());

	uint32 _rank = static_cast<Creature*>(unitTarget)->GetCreatureInfo() ? static_cast<Creature*>(unitTarget)->GetCreatureInfo()->Rank : 0;
	unitTarget->loot.gold = float2int32((_rank+1) * unitTarget->getLevel() * (RandomUInt(5) + 1) * sWorld.getRate(RATE_MONEY));

	p_caster->SendLoot(unitTarget->GetGUID(), LOOT_PICKPOCKETING );
	target->SetPickPocketed(true);
}

void Spell::SpellEffectAddFarsight(uint32 i) // Add Farsight
{
	if(!u_caster)
		return;

	float x = m_targets.m_destX;
	float y = m_targets.m_destY;
	float z = m_targets.m_destZ;
	if(x == 0)
		x = m_targets.m_srcX;
	if(y == 0)
		y = m_targets.m_srcY;
	if(z == 0)
		z = m_targets.m_srcZ;

	/*
	if( dynObj == NULL ) //i <3 burlex :P
	{
	delete dynObj;
	return;
	}
	*/
	DynamicObject * dyn = p_caster->GetMapMgr()->CreateDynamicObject();
	dyn->Create(u_caster, this, x, y, z, GetDuration(), GetRadius(i));

	dyn->SetUInt32Value(OBJECT_FIELD_TYPE, 65);
	dyn->SetUInt32Value(DYNAMICOBJECT_BYTES, 0x80000002);
	dyn->AddToWorld(p_caster->GetMapMgr());

	p_caster->SetUInt64Value(PLAYER_FARSIGHT, dyn->GetGUID());
	p_caster->GetMapMgr()->ChangeFarsightLocation(p_caster, dyn);
}

void Spell::SpellEffectSummonPossessed(uint32 i) // eye of kilrogg
{
	/*
	m_target->DisableAI();
	pCaster->SetUInt64Value(UNIT_FIELD_SUMMON, 0);
	m_target->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, 0);
	pCaster->SetUInt64Value(UNIT_FIELD_CHARM, m_target->GetGUID());
	m_target->SetUInt64Value(UNIT_FIELD_CHARMEDBY, pCaster->GetGUID());
	pCaster->SetUInt64Value(PLAYER_FARSIGHT, m_target->GetGUID());
	pCaster->m_CurrentCharm = ((Creature*)m_target);
	m_target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED_CREATURE);
	pCaster->m_noInterrupt = 1;
	pCaster->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);

	WorldPacket data(SMSG_CLIENT_CONTROL_UPDATE);
	data << m_target->GetNewGUID() << uint8(1);
	pCaster->GetSession()->SendPacket(&data);
	*/
	
	if( GetProto()->EffectMiscValue[i] == 4277)
	{
		Creature* NewSummon = m_caster->GetMapMgr()->CreateCreature(GetProto()->EffectMiscValue[i]);
		// Create
		NewSummon->SetInstanceID(m_caster->GetInstanceID());
		NewSummon->Create( "Eye of Kilrogg", m_caster->GetMapId(), m_caster->GetPositionX()+(3*(cos((float(M_PI)/2)+m_caster->GetOrientation()))), m_caster->GetPositionY()+(3*(cos((float(M_PI)/2)+m_caster->GetOrientation()))), m_caster->GetPositionZ(), m_caster->GetOrientation());

		// Fields
		NewSummon->SetUInt32Value(OBJECT_FIELD_ENTRY, GetProto()->EffectMiscValue[i]);
		NewSummon->SetUInt32Value(UNIT_FIELD_LEVEL,m_caster->GetUInt32Value(UNIT_FIELD_LEVEL));
		NewSummon->SetUInt32Value(UNIT_FIELD_DISPLAYID,  2421);
		NewSummon->SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, 2421);
		NewSummon->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, m_caster->GetGUID());
		NewSummon->SetUInt64Value(UNIT_FIELD_CREATEDBY, m_caster->GetGUID());
		NewSummon->SetUInt32Value(UNIT_FIELD_HEALTH, 12375);
		NewSummon->SetUInt32Value(UNIT_FIELD_MAXHEALTH, 12375);
		NewSummon->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, p_caster->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
		NewSummon->SetFloatValue(OBJECT_FIELD_SCALE_X,1.0f);

		if(p_caster->IsPvPFlagged())
			NewSummon->SetByteFlag(UNIT_FIELD_BYTES_2, 1, U_FIELD_BYTES_FLAG_PVP);
		if(p_caster->IsFFAPvPFlagged())
			NewSummon->SetByteFlag(UNIT_FIELD_BYTES_2, 1, U_FIELD_BYTES_FLAG_FFA_PVP);

		//Setting faction
		NewSummon->_setFaction();
		NewSummon->m_temp_summon=true;

		// Add To World
		NewSummon->PushToWorld(m_caster->GetMapMgr());

		// Force an update on the player to create this guid.
		p_caster->ProcessPendingUpdates();

		p_caster->m_eyeofkilrogg = NewSummon;

		//p_caster->SetUInt64Value(UNIT_FIELD_SUMMON, NewSummon->GetGUID());
		//p_caster->SetUInt64Value(PLAYER_FARSIGHT, NewSummon->GetGUID());
		//p_caster->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);
		p_caster->Possess(NewSummon);
	}
}

void Spell::SpellEffectUseGlyph(uint32 i)
{
	/*if( !p_caster ) return;

	uint32 g_new = m_spellInfo->EffectMiscValue[i];
	GlyphPropertyEntry * gp_new = dbcGlyphProperty.LookupEntry( g_new );
	if( !gp_new ) return;

	if( !( p_caster->GetUInt32Value( PLAYER_GLYPHS_ENABLED ) & ( 1 << m_glyphslot ) ) )
	{
		SendCastResult( SPELL_FAILED_GLYPH_SOCKET_LOCKED );
		return;
	}

	uint32 g_old = p_caster->GetUInt32Value( PLAYER_FIELD_GLYPHS_1 + m_glyphslot );
	if( g_old )
	{
		if( g_old == g_new )
			return;
		else
		{
			GlyphPropertyEntry * gp_old = dbcGlyphProperty.LookupEntry( g_old );
			if( gp_old )
				p_caster->RemoveAura( gp_old->SpellID );
			p_caster->SetUInt32Value( PLAYER_FIELD_GLYPHS_1 + m_glyphslot, 0 );
		}
	}

	GlyphSlotEntry * gs = dbcGlyphSlot.LookupEntry( p_caster->GetUInt32Value( PLAYER_FIELD_GLYPH_SLOTS_1 + m_glyphslot ) );
	if( gs )
	{
		if( gs->Type != gp_new->Type )
		{
			SendCastResult( SPELL_FAILED_INVALID_GLYPH );
			return;
		}
		p_caster->SetUInt32Value( PLAYER_FIELD_GLYPHS_1 + m_glyphslot, g_new );
		p_caster->CastSpell( p_caster, gp_new->SpellID, true );
	}*/
	if(!p_caster)
		return;
	uint8 result = p_caster->SetGlyph(m_glyphslot, m_spellInfo->EffectMiscValue[i]);
	if(result) // there was an error
		SendCastResult(result);
	else		// success, need to update client display
		p_caster->smsg_TalentsInfo(false, 0, 0);

}

void Spell::SpellEffectHealMechanical(uint32 i)
{
	if(!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT || static_cast<Creature*>(unitTarget)->GetCreatureInfo()->Type != UNIT_TYPE_MECHANICAL)
		return;

	Heal((int32)damage);
}

void Spell::SpellEffectSummonObjectWild(uint32 i)
{
	if(!u_caster) return;

	// spawn a new one
	GameObject *GoSummon = u_caster->GetMapMgr()->CreateGameObject(GetProto()->EffectMiscValue[i]);
	if(!GoSummon->CreateFromProto(GetProto()->EffectMiscValue[i],
		m_caster->GetMapId(), m_caster->GetPositionX()+1, m_caster->GetPositionY()+1, m_caster->GetPositionZ(), m_caster->GetOrientation() ))
	{
		delete GoSummon;
		return;
	}

	GoSummon->SetInstanceID(m_caster->GetInstanceID());
	GoSummon->SetUInt32Value(GAMEOBJECT_LEVEL, u_caster->getLevel());
	GoSummon->SetUInt64Value(OBJECT_FIELD_CREATED_BY, m_caster->GetGUID());
	GoSummon->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
	GoSummon->PushToWorld(u_caster->GetMapMgr());
	GoSummon->SetSummoned(u_caster);

	sEventMgr.AddEvent(GoSummon, &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_EXPIRE, GetDuration(), 1,0);
}

void Spell::SpellEffectScriptEffect(uint32 i) // Script Effect
{
	uint32 spellId = GetProto()->Id;

	// Try a dummy SpellHandler
	if(sScriptMgr.CallScriptedDummySpell(spellId, i, this))
		return;

	switch(spellId)
	{
	case 51770:
		{
			p_caster->CastSpell(p_caster, 51771, true);
		}break;
	case 53209:
		{
			if(unitTarget->HasAurasWithNameHash(SPELL_HASH_SERPENT_STING))
			{
				SpellEntry* se1 = dbcSpell.LookupEntry(unitTarget->HasAurasWithNameHash(SPELL_HASH_SERPENT_STING));
				uint32 dmg = se1->EffectBasePoints[0]*0.4;
				u_caster->DealDamage(unitTarget, dmg, 0, 0, 53209);
				u_caster->RemoveAura(unitTarget->HasAurasWithNameHash(SPELL_HASH_SERPENT_STING));
				u_caster->CastSpell(unitTarget, se1->Id, true);
			}
			if(unitTarget->HasAurasWithNameHash(SPELL_HASH_VIPER_STING))
			{
				SpellEntry* se1 = dbcSpell.LookupEntry(unitTarget->HasAurasWithNameHash(SPELL_HASH_VIPER_STING));
				uint32 dmg = se1->EffectBasePoints[0]*0.6;
				u_caster->Energize(u_caster, 53209, dmg, POWER_TYPE_MANA);
				u_caster->RemoveAura(unitTarget->HasAurasWithNameHash(SPELL_HASH_SERPENT_STING));
				u_caster->CastSpell(unitTarget, se1->Id, true);
			}
			if(unitTarget->HasAurasWithNameHash(SPELL_HASH_SCORPID_STING))
			{
				u_caster->CastSpell(unitTarget, 53359, true);
				SpellEntry* se1 = dbcSpell.LookupEntry(unitTarget->HasAurasWithNameHash(SPELL_HASH_SCORPID_STING));
				u_caster->CastSpell(unitTarget, se1->Id, true);
			}
		}break;
		// Arcane Missiles
		/*
		case 5143://Rank 1
		case 5144://Rank 2
		case 5145://Rank 3
		case 8416://Rank 4
		case 8417://Rank 5
		case 10211://Rank 6
		case 10212://Rank 7
		case 25345://Rank 8
		{
		if(m_tmpAffect == 0)
		{
		Affect* aff = new Affect(GetProto(),GetDuration(sSpellDuration.LookupEntry(GetProto()->DurationIndex)),m_GetGUID(),m_caster);
		m_tmpAffect = aff;
		}
		if(GetProto()->EffectBasePoints[0] < 0)
		m_tmpAffect->SetNegative();

		m_tmpAffect->SetPeriodicTriggerSpell(GetProto()->EffectTriggerSpell[0],GetProto()->EffectAmplitude[0],damage);
		}break;
		*/
		// Warlock Healthstones, just how much health does a lock need?
	case 6201:		// Minor Healthstone
		if (p_caster->HasSpell(18692))
		{
			CreateItem(19004);
			break;
		}
		if (p_caster->HasSpell(18693))
		{
			CreateItem(19005);
			break;
		}
		CreateItem(5512);
		break;
	case 6202:		// Lesser Healthstone
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(19007);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(19006);
			break;
		}
		CreateItem(5511);
		break;
	case 5699:		// Healthstone
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(19009);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(19008);
			break;
		}
		CreateItem(5509);
		break;
	case 11729:		// Greater Healthstone
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(19011);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(19010);
			break;
		}
		CreateItem(5510);
		break;
	case 11730:		// Major Healthstone
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(19013);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(19012);
			break;
		}
		CreateItem(9421);
		break;
	case 27230:		// Master Healthstone
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(22105);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(22104);
			break;
		}
		CreateItem(22103);
		break;
	case 47871:		// Demonic Healthstone
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(36891);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(36890);
			break;
		}
		CreateItem(36889);
		break;
	case 47878:		// Fel Healthstone
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(36894);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(36893);
			break;
		}
		CreateItem(36892);
		break;
	// Holy Light
	case 635:
	case 639:
	case 647:
	case 1026:
	case 1042:
	case 3472:
	case 10328:
	case 10329:
	case 25292:
	case 27135:
	case 27136:
	case 48781:
	case 48782:
	//Flash of light
	case 19750:
	case 19939:
	case 19940:
	case 19941:
	case 19942:
	case 19943:
	case 27137:
	case 48784:
	case 48785:
		if( u_caster->HasAura( 20216 ) )
			Heal((int32)damage, true);
		else
			Heal((int32)damage);
		break;

		// Judgement
	case 20271: //Light
	case 53407: //Justice
	case 53408: //Wisdom
		{
			if(!unitTarget || !p_caster) 
				return;

			if(u_caster->HasAura(20164))
				p_caster->Seal = 20164;
			else if(u_caster->HasAura(20165))
				p_caster->Seal = 20165;
			else if(u_caster->HasAura(20166))
				p_caster->Seal = 20166;

			if( p_caster->Seal )
			{
				u_caster->JugementID = m_spellInfo->Id; 
				u_caster->LiberationSceauPaladin(p_caster->Seal, unitTarget);
			}

			uint32 judge_extra = 0;
			// This is for handling specific Judgement's debuff application spells
			switch(m_spellInfo->Id)
			{
			case 20271:
				judge_extra = 20185;
				break;
			case 53407:
				judge_extra = 20184;
				break;
			case 53408:
				judge_extra = 20186;
				break;
			}
			p_caster->CastSpell( unitTarget, judge_extra, true );
		}break;

		//warlock - Master Demonologist
	case 23784:
		{
			if( !p_caster || !unitTarget)
				return; //can't imagine how this talent got to anybody else then a player casting on pet
			uint32 casted_spell_id = 0 ;
			uint32 inc_resist_by_level = 0 ;
			uint32 inc_resist_by_level_spell = 0 ;
			if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 416 ) //in case it is imp
				casted_spell_id = 23759 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1860 ) //VoidWalker
				casted_spell_id = 23760 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1863 ) //Succubus
				casted_spell_id = 23761 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 417 ) //Felhunter
			{
				casted_spell_id = 0 ;
				inc_resist_by_level_spell = 23762 ;
				inc_resist_by_level = 20 ;
			}
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 17252 ) //Felguard
			{
				casted_spell_id = 35702 ;
				inc_resist_by_level_spell = 23762 ;
				inc_resist_by_level = 10 ;
			}
			if( casted_spell_id )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init( p_caster, dbcSpell.LookupEntry( casted_spell_id ), true, NULL);
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init(unitTarget, dbcSpell.LookupEntry( casted_spell_id ), true, NULL);
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
			if( inc_resist_by_level_spell )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init(p_caster, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL);
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init(unitTarget, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL);
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
		}break;
	case 23830:
		{
			if( !p_caster  || !unitTarget)
				return; //can't imagine how this talent got to anybody else then a player casting on pet
			uint32 casted_spell_id = 0 ;
			uint32 inc_resist_by_level = 0 ;
			uint32 inc_resist_by_level_spell = 0 ;
			if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 416 ) //in case it is imp
				casted_spell_id = 23826 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1860 ) //VoidWalker
				casted_spell_id = 23841 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1863 ) //Succubus
				casted_spell_id = 23833 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 417 ) //Felhunter
			{
				casted_spell_id = 1 ;
				inc_resist_by_level_spell = 23837 ;
				inc_resist_by_level = 40 ;
			}
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 17252 ) //Felguard
			{
				casted_spell_id = 35703 ;
				inc_resist_by_level_spell = 23837 ;
				inc_resist_by_level = 20 ;
			}
			if( casted_spell_id )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init(p_caster, dbcSpell.LookupEntry( casted_spell_id ), true, NULL);
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init(unitTarget, dbcSpell.LookupEntry( casted_spell_id ), true, NULL);
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
			if( inc_resist_by_level_spell )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init(p_caster, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL);
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init(unitTarget, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL);
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
		}break;
	case 23831:
		{
			if( !p_caster || !unitTarget)
				return; //can't imagine how this talent got to anybody else then a player casting on pet
			uint32 casted_spell_id = 0 ;
			uint32 inc_resist_by_level = 0 ;
			uint32 inc_resist_by_level_spell = 0 ;
			if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 416 ) //in case it is imp
				casted_spell_id = 23827 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1860 ) //VoidWalker
				casted_spell_id = 23842 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1863 ) //Succubus
				casted_spell_id = 23834 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 417 ) //Felhunter
			{
				casted_spell_id = 0 ;
				inc_resist_by_level_spell = 23838 ;
				inc_resist_by_level = 60 ;
			}
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 17252 ) //Felguard
			{
				casted_spell_id = 35704 ;
				inc_resist_by_level_spell = 23838 ;
				inc_resist_by_level = 30 ;
			}
			if( casted_spell_id )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init(p_caster, dbcSpell.LookupEntry( casted_spell_id ), true, NULL);
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init(unitTarget, dbcSpell.LookupEntry( casted_spell_id ), true, NULL);
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
			if( inc_resist_by_level_spell )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init( p_caster, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init( unitTarget, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
		}break;
	case 23832:
		{
			if( !p_caster || !unitTarget)
				return; //can't imagine how this talent got to anybody else then a player casting on pet
			uint32 casted_spell_id = 0 ;
			uint32 inc_resist_by_level = 0 ;
			uint32 inc_resist_by_level_spell = 0 ;
			if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 416 ) //in case it is imp
				casted_spell_id = 23828 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1860 ) //VoidWalker
				casted_spell_id = 23843 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1863 ) //Succubus
				casted_spell_id = 23835 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 417 ) //Felhunter
			{
				casted_spell_id = 0 ;
				inc_resist_by_level_spell = 23839 ;
				inc_resist_by_level = 80 ;
			}
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 17252 ) //Felguard
			{
				casted_spell_id = 35705 ;
				inc_resist_by_level_spell = 23839 ;
				inc_resist_by_level = 40 ;
			}
			if( casted_spell_id )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init( p_caster, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init(  unitTarget, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
			if( inc_resist_by_level_spell )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init( p_caster, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init( unitTarget, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
		}break;
	case 34026: //Hunter: Kill Command
		{
			/* Disabled - Spell changed in patch 3.0.2
			// in this case unitTarget == pet
			if( p_caster == NULL || unitTarget == NULL || unitTarget->getDeathState() != ALIVE )
			return;

			AI_Spell* Sp = static_cast< Pet* >( unitTarget )->CreateAISpell( dbcSpell.LookupEntry( 34027 ) );

			Unit* tgt = p_caster->GetMapMgr()->GetUnit( p_caster->GetSelection() );

			if( tgt != NULL && isAttackable( p_caster, tgt ) )
			{
			unitTarget->GetAIInterface()->AttackReaction( tgt, 1 );
			unitTarget->GetAIInterface()->SetNextTarget( tgt );
			}
			else if( unitTarget->CombatStatus.GetPrimaryAttackTarget() == 0 )
			return;
			unitTarget->GetAIInterface()->SetNextSpell( Sp );
			//TODO: Kill Command - return to previous pet target after cast*/

		}break;
	case 35708:
		{
			if( !p_caster || !unitTarget)
				return; //can't imagine how this talent got to anybody else then a player casting on pet
			uint32 casted_spell_id = 0 ;
			uint32 inc_resist_by_level = 0 ;
			uint32 inc_resist_by_level_spell = 0 ;
			if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 416 ) //in case it is imp
				casted_spell_id = 23829 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1860 ) //VoidWalker
				casted_spell_id = 23844 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1863 ) //Succubus
				casted_spell_id = 23836 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 417 ) //Felhunter
			{
				casted_spell_id = 0 ;
				inc_resist_by_level_spell = 23840 ;
				inc_resist_by_level = 100 ;
			}
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 17252 ) //Felguard
			{
				casted_spell_id = 35706 ;
				inc_resist_by_level_spell = 23840 ;
				inc_resist_by_level = 50 ;
			}
			if( casted_spell_id )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init( p_caster, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init( unitTarget, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
			if( inc_resist_by_level_spell )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				if (!sp)
					return;
				sp->Init( p_caster, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				sp->Init( unitTarget, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
		}break;
	case 46642: // 5,000 Gold
		if( GetPlayerTarget() != NULL )
		{
			if( sWorld.GoldCapEnabled && ( GetPlayerTarget()->GetUInt32Value( PLAYER_FIELD_COINAGE ) + 50000000 ) > sWorld.GoldLimit )
			{
				GetPlayerTarget()->SetUInt32Value( PLAYER_FIELD_COINAGE, sWorld.GoldLimit );
				GetPlayerTarget()->GetItemInterface()->BuildInventoryChangeError( NULL, NULL, INV_ERR_TOO_MUCH_GOLD );
			}
			else
			{
				GetPlayerTarget()->SetUInt32Value( PLAYER_FIELD_COINAGE, GetPlayerTarget()->GetUInt32Value( PLAYER_FIELD_COINAGE ) + 50000000 );
			}
		}break;
	case 60893:
		//Northrend Alchemy research
		{
			skilllinespell* skill = objmgr.GetSpellSkill(GetProto()->Id);
			// skill up
			DetermineSkillUp( skill->skilline );

			// profession discoveries
			uint32 discovered_recipe = 0;
			std::set<ProfessionDiscovery*>::iterator itr = objmgr.ProfessionDiscoveryTable.begin();
			for ( ; itr != objmgr.ProfessionDiscoveryTable.end(); itr++ )
			{
				ProfessionDiscovery * pf = ( *itr );
				if ( pf && GetProto()->Id == pf->SpellId && p_caster->_GetSkillLineCurrent( skill->skilline ) >= pf->SkillValue && !p_caster->HasSpell( pf->SpellToDiscover ) && Rand( pf->Chance ) )
				{
					discovered_recipe = pf->SpellToDiscover;
					break;
				}
			}
			// if something discovered learn p_caster that recipe and broadcast message
			if ( discovered_recipe != 0 )
			{
				SpellEntry * se = dbcSpell.LookupEntry( discovered_recipe );
				if ( se )
				{
					p_caster->addSpell( discovered_recipe );
					WorldPacket * data;
					char msg[256];
					sprintf( msg, "%sDecouverte! %s a d�couvert comment cr�er %s.|r", MSG_COLOR_GOLD, p_caster->GetName(), se->Name );
					data = sChatHandler.FillMessageData( CHAT_MSG_SYSTEM, LANG_UNIVERSAL,  msg, p_caster->GetGUID(), 0 );
					p_caster->GetMapMgr()->SendChatMessageToCellPlayers( p_caster, data, 2, 1, LANG_UNIVERSAL, p_caster->GetSession() );
					delete data;
				}
			}
		}break;

	case 61288:
		// Minor Inscription Research
	case 61177:
		// Northrend Inscription Research
		{
			// http://www.wowwiki.com/Minor_Inscription_Research :
				// Minor Inscription Research is taught at 75 skill in Inscription.
				// When you perform this research, you have a very high chance of learning a new minor glyph recipe.
				// The chance to discover a new minor glyph is independent of your level, Inscription skill, and how many minor glyphs you already know.
				// The recipe has a 20-hour cooldown, similar to alchemical transmutes.

			// What is a "very high chance" ?  90% ?
			float chance = 90.0f;
			if( Rand(chance) )
			{
				// Type 0 = Major, 1 = Minor
				uint32 glyphType = (spellId == 61177) ? 0 : 1;
				skilllinespell* sls;
				uint32 num_sl = dbcSkillLineSpell.GetNumRows();
				std::vector<uint32> discoverableGlyphs;

				// how many of these are the right type (minor/major) of glyph, and learnable by the player
				for( uint32 idx = 0; idx < num_sl; ++idx )
				{
					sls = dbcSkillLineSpell.LookupRow(idx);
					if( sls->skilline == SKILL_INSCRIPTION && sls->next == 0 )
					{
						SpellEntry* se1 = dbcSpell.LookupEntry(sls->spell);
						if( se1 && se1->Effect[0] == SPELL_EFFECT_CREATE_ITEM )
						{
							ItemPrototype* itm = ItemPrototypeStorage.LookupEntry(se1->EffectItemType[0]);
							if( itm && (itm->Spells[0].Id != 0) )
							{
								SpellEntry* se2 = dbcSpell.LookupEntry( itm->Spells[0].Id );
								if( se2 && se2->Effect[0] == SPELL_EFFECT_USE_GLYPH )
								{
									GlyphPropertyEntry* gpe = dbcGlyphProperty.LookupEntry(se2->EffectMiscValue[0]);
									if( gpe && gpe->Type == glyphType )
									{
										if( !p_caster->HasSpell(sls->spell) )
										{
											discoverableGlyphs.push_back(sls->spell);
										}
									}
								}
							}
						}
					}
				}

				if( discoverableGlyphs.size() > 0 )
				{
					uint32 newGlyph = discoverableGlyphs.at( uint32(rand()) % discoverableGlyphs.size() );
					p_caster->addSpell(newGlyph);
				}
			}
		}
		break;
	case 24590: // Zandalarian Hero Badge
		if( u_caster != NULL )
		{
			for(int i=0;i<20;i++)
				u_caster->CastSpell(u_caster, 24575, true);
		}break;
	}
}

void Spell::SpellEffectSanctuary(uint32 i) // Stop all attacks made to you
{
	if(!u_caster) return;

	//warning this causes crashes !
	//	Object::InRangeSet::iterator itr = u_caster->GetInRangeOppFactsSetBegin();
	//	Object::InRangeSet::iterator itr_end = u_caster->GetInRangeOppFactsSetEnd();
	//use these instead
	Object::InRangeSet::iterator itr = u_caster->GetInRangeSetBegin();
	Object::InRangeSet::iterator itr_end = u_caster->GetInRangeSetEnd();
	Unit * pUnit;

	if(u_caster->IsPlayer())
		static_cast<Player*>(u_caster)->RemoveAllAuraType( SPELL_AURA_MOD_ROOT );

	for( ; itr != itr_end; ++itr )
		if( (*itr)->IsUnit() )
		{
			pUnit = static_cast<Unit*>(*itr);

			if( pUnit && pUnit->GetTypeId() == TYPEID_UNIT )
				pUnit->GetAIInterface()->RemoveThreatByPtr( unitTarget );
		}
}

void Spell::SpellEffectAddComboPoints(uint32 i) // Add Combo Points
{
	if(!p_caster) return;

	//if this is a procspell Ruthlessness (maybe others later)
	if(pSpellId && GetProto()->Id==14157)
	{
		//it seems this combo adding procspell is going to change combopoint count before they will get reset. We add it after the reset
		/* burlex - this is wrong, and exploitable.. :/ if someone uses this they will have unlimited combo points */
		//re-enabled this by Zack. Explained why it is used + rechecked to make sure initialization is good ...
		// while casting a spell talent will trigger upon the spell prepare faze
		// the effect of the talent is to add 1 combo point but when triggering spell finishes it will clear the extra combo point
		p_caster->m_spellcomboPoints += static_cast<int8>( damage );
		return;
	}
	p_caster->AddComboPoints(p_caster->GetSelection(), static_cast<uint8>( damage ));
}

void Spell::SpellEffectCreateHouse(uint32 i) // Create House
{


}

void Spell::SpellEffectDuel(uint32 i) // Duel
{
	if(!p_caster || !p_caster->isAlive())
		return;

	if (p_caster->IsStealth())
	{
		SendCastResult(SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED);
		return; // Player is stealth
	}
	if(!playerTarget || playerTarget == p_caster)
		return;

	/* not implemented yet
	TODO: dueling zones ? ( SPELL_FAILED_NO_DUELING )
	if (player->IsInvisible())
	{
	SendCastResult(SPELL_FAILED_CANT_DUEL_WHILE_INVISIBLE);
	return;
	}
	*/

	//Player *pTarget = sObjHolder.GetObject<Player>(player->GetSelection());	   //  hacky.. and will screw up if plr is deselected..
	if (!playerTarget)
	{
		SendCastResult(SPELL_FAILED_BAD_TARGETS);
		return; // invalid Target
	}
	if (!playerTarget->isAlive())
	{
		SendCastResult(SPELL_FAILED_TARGETS_DEAD);
		return; // Target not alive
	}
	if (playerTarget->hasStateFlag(UF_ATTACKING))
	{
		SendCastResult(SPELL_FAILED_TARGET_IN_COMBAT);
		return; // Target in combat with another unit
	}
	if (playerTarget->DuelingWith)
	{
		SendCastResult(SPELL_FAILED_TARGET_DUELING);
		return; // Already Dueling
	}

	p_caster->RequestDuel(playerTarget);
}

void Spell::SpellEffectStuck(uint32 i)
{
	if(!playerTarget || playerTarget != p_caster)
		return;

	sEventMgr.AddEvent(playerTarget,&Player::EventTeleport,playerTarget->GetBindMapId(),playerTarget->GetBindPositionX(),playerTarget->GetBindPositionY(),
		playerTarget->GetBindPositionZ(),EVENT_PLAYER_TELEPORT,50,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	/*
	playerTarget->SafeTeleport(playerTarget->GetBindMapId(), 0, playerTarget->GetBindPositionX(), playerTarget->GetBindPositionY(), playerTarget->GetBindPositionZ(), 3.14f);*/
}

void Spell::SpellEffectSummonPlayer(uint32 i)
{
	if( !playerTarget ) return;

	// vojta: from 2.4 players can be summoned on another map
	//if( m_caster->GetMapMgr()->GetMapInfo() && m_caster->GetMapMgr()->GetMapInfo()->type != INSTANCE_NULL && m_caster->GetMapId() != playerTarget->GetMapId())
	//	return;
	if ( m_caster->GetMapMgr()->GetMapInfo() && playerTarget->getLevel() < m_caster->GetMapMgr()->GetMapInfo()->minlevel ) // we need some blizzlike message that player needs level xx - feel free to add it ;)
		return;

	playerTarget->SummonRequest( m_caster->GetLowGUID(), m_caster->GetZoneId(), m_caster->GetMapId(), m_caster->GetInstanceID(), m_caster->GetPosition() );
}

void Spell::SpellEffectActivateObject(uint32 i) // Activate Object
{
	/*if(!p_caster)
	return;

	if(!gameObjTarget)
	return;

	gameObjTarget->SetUInt32Value(GAMEOBJECT_DYNAMIC, 1);

	sEventMgr.AddEvent(gameObjTarget, &GameObject::Deactivate, EVENT_GAMEOBJECT_DEACTIVATE, GetDuration(), 1);*/
}

void Spell::SpellEffectSummonTotem(uint32 i) // Summon Totem
{
	if(!p_caster) return;

	uint32 slot = 10;
	float x = p_caster->GetPositionX();
	float y = p_caster->GetPositionY();

	switch(m_spellInfo->EffectMiscValueB[i])
	{
	case 63: //Fire
		slot = 2;
		x -= 1.5f;
		y -= 1.5f;
		break;
	case 81: //Earth
		slot = 3;
		x -= 1.5f;
		y += 1.5f;
		break;
	case 82: //Water
		slot = 1;
		x += 1.5f;
		y -= 1.5f;
		break;
	case 83: //Air
		slot = 0;
		x += 1.5f;
		y += 1.5f;
		break;
	default:
		break;
	}

	if(slot > 3)
	{
		sLog.outDebug("Totem slot is : %u and max should be 3, i = %u , target = %u \n",slot,i,m_spellInfo->EffectImplicitTargetA[i]);
		return; // Just 4 totems
	}

	uint32 entry = GetProto()->EffectMiscValue[i];

	CreatureInfo* ci = CreatureNameStorage.LookupEntry(entry);
	if(!ci)
	{
		sLog.outDebug("Missing totem creature entry : %u \n",entry);
		return;
	}

	Creature * pTotem = p_caster->GetMapMgr()->CreateCreature(entry);

	// send the packet for the totem timer
	WorldPacket data(SMSG_TOTEM_CREATED, 17);
	data << uint8(slot);
	data << uint64(pTotem->GetGUID());
	data << uint32(GetDuration());
	data << uint32(GetProto()->Id);
	p_caster->GetSession()->SendPacket(&data);

	if(p_caster->m_TotemSlots[slot] != 0)
		p_caster->m_TotemSlots[slot]->TotemExpire();

	p_caster->m_TotemSlots[slot] = pTotem;
	pTotem->SetTotemOwner(p_caster);
	pTotem->SetTotemSlot(slot);

	float landh = p_caster->GetMapMgr()->GetLandHeight(x,y);
	float landdiff = landh - p_caster->GetPositionZ();

	if (fabs(landdiff)>15)
		pTotem->Create(ci->Name, p_caster->GetMapId(), x, y, p_caster->GetPositionZ(), p_caster->GetOrientation());
	else
		pTotem->Create(ci->Name, p_caster->GetMapId(), x, y, landh, p_caster->GetOrientation());

	uint32 displayID = 0;

	if( p_caster->GetTeamInitial() == 0 )
	{
		if ( ci->Female_DisplayID != 0 )
		{
			displayID = ci->Female_DisplayID; //this is the nice solution provided by emsy
		}
		else //this is the case when you are using a blizzlike db
		{
			if( ci->Male_DisplayID == 4587 )
				displayID = 19075;
			else if( ci->Male_DisplayID == 4588 )
				displayID = 19073;
			else if( ci->Male_DisplayID == 4589 )
				displayID = 19074;
			else if( ci->Male_DisplayID == 4590 )
				displayID = 19071;
			else if( ci->Male_DisplayID == 4683 )
				displayID = 19074;
			else
				displayID = ci->Male_DisplayID;
		}
	}
	else
	{
		displayID = ci->Male_DisplayID;
	}

	// Set up the creature.
	pTotem->SetUInt32Value(OBJECT_FIELD_ENTRY, entry);
	pTotem->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
	pTotem->SetUInt64Value(UNIT_FIELD_CREATEDBY, p_caster->GetGUID());
	pTotem->SetUInt32Value(UNIT_FIELD_HEALTH, damage);
	pTotem->SetUInt32Value(UNIT_FIELD_MAXHEALTH, damage);
	pTotem->SetUInt32Value(UNIT_FIELD_POWER3, p_caster->getLevel() * 30);
	pTotem->SetUInt32Value(UNIT_FIELD_MAXPOWER3, p_caster->getLevel() * 30);
	pTotem->SetUInt32Value(UNIT_FIELD_LEVEL, p_caster->getLevel());
	pTotem->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, p_caster->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
	pTotem->SetUInt32Value(UNIT_FIELD_BYTES_0, (1 << 8) | (2 << 16) | (1 << 24));
	pTotem->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED | UNIT_FLAG_SELF_RES);
	pTotem->SetUInt32Value(UNIT_FIELD_BASEATTACKTIME, 2000);
	pTotem->SetUInt32Value(UNIT_FIELD_BASEATTACKTIME+1, 2000);
	pTotem->SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 1.0f);
	pTotem->SetFloatValue(UNIT_FIELD_COMBATREACH, 1.0f);
	pTotem->SetUInt32Value(UNIT_FIELD_DISPLAYID, displayID);
	pTotem->SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, ci->Male_DisplayID); //blizzlike :P
	pTotem->SetFloatValue(UNIT_MOD_CAST_SPEED, 1.0f);
	pTotem->SetUInt32Value(UNIT_CREATED_BY_SPELL, GetProto()->Id);
	pTotem->SetUInt32Value(UNIT_FIELD_BYTES_2, 1 | (0x28 << 8));

	// Initialize faction stuff.
	pTotem->m_faction = p_caster->m_faction;
	pTotem->m_factionDBC = p_caster->m_factionDBC;

	if(m_spellInfo->Id == 6495)
		p_caster->GetTotemSentinelle = pTotem;

	if(ci->Id != 3968) //Exclude the sentry totem, it does not cast
	{
		// Obtain the spell we will be casting.
		SpellEntry * TotemSpell = ObjectMgr::getSingleton().GetTotemSpell(GetProto()->Id);

		if(TotemSpell == 0)
		{
			sLog.outDebug("Totem %u does not have any spells to cast, exiting\n",entry);
			return;
		}

		//added by Zack : Some shaman talents are cast on player but it should be inherited or something by totems
		pTotem->InheritSMMods(p_caster);

		// Totems get spell damage and healing bonus from the Shaman
		for(int school = 0; school<7; school++){
			pTotem->ModDamageDone[school] = (int32)(p_caster->GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS + school ) - (int32)p_caster->GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_NEG + school ));
			pTotem->HealDoneMod[school] = p_caster->HealDoneMod[school];
		}

		// Set up AI, depending on our spells.
		uint32 j;
		for( j = 0; j < 3; ++j )
		{
			if( TotemSpell->Effect[j] == SPELL_EFFECT_APPLY_AREA_AURA ||
				TotemSpell->Effect[j] == SPELL_EFFECT_APPLY_AREA_AURA2 ||
				TotemSpell->Effect[j] == SPELL_EFFECT_PERSISTENT_AREA_AURA ||
				TotemSpell->EffectApplyAuraName[j] == SPELL_AURA_PERIODIC_TRIGGER_SPELL )
			{
				break;
			}
		}
		// Setup complete. Add us to the world.
		pTotem->PushToWorld(m_caster->GetMapMgr());

		if(j != 3)
		{
			// We're an area aura. Simple. Disable AI and cast the spell.
			pTotem->DisableAI();
			pTotem->GetAIInterface()->totemspell = GetProto();

			Spell * pSpell = SpellPool.PooledNew();
			if (!pSpell)
				return;
			pSpell->Init(pTotem, TotemSpell, true, 0);

			SpellCastTargets targets;
			targets.m_destX = pTotem->GetPositionX();
			targets.m_destY = pTotem->GetPositionY();
			targets.m_destZ = pTotem->GetPositionZ();
			targets.m_targetMask = TARGET_FLAG_DEST_LOCATION;

			pSpell->prepare(&targets);
		}
		else
		{
			// We're a casting totem. Switch AI on, and tell it to cast this spell.
			pTotem->EnableAI();
			pTotem->GetAIInterface()->Init(pTotem, AITYPE_TOTEM, MOVEMENTTYPE_NONE, p_caster);
			pTotem->GetAIInterface()->totemspell = TotemSpell;
			int32 totemspelltimer = 3000, totemspelltime = 3000;	// need a proper resource for this.

			switch(TotemSpell->Id)
			{
			case 8167: //Poison Cleansing Totem
			case 8172: //Disease Cleansing Totem
				{
					if(TotemSpell->Id == 8167)
						TotemSpell = dbcSpell.LookupEntry( 8168 );	// Better to use this spell
					else
						TotemSpell = dbcSpell.LookupEntry( 8171 );
					pTotem->GetAIInterface()->totemspell = TotemSpell;
					totemspelltime =  5000;
					totemspelltimer = 0; //First tick done immediately
					break;
				}
			case 8146: //Tremor Totem
				{
					totemspelltime = 1000;
					totemspelltimer = 0; //First tick done immediately
					break;
				}
			case 8178: //Grounding Totem
			case 3600: //Earthbind Totem
				{
					totemspelltimer = 0; //First tick done immediately
					break;
				}
			case 8349: //Fire Nova Totem 1
			case 8502: //Fire Nova Totem 2
			case 8503: //Fire Nova Totem 3
			case 11306: //Fire Nova Totem 4
			case 11307: //Fire Nova Totem 5
			case 25535: //Fire Nova Totem 6
			case 25537: //Fire Nova Totem 7
			case 61650: //Fire Nova Totem 8
			case 61654: //Fire Nova Totem 9
				{
					totemspelltimer =  4000;
					// Improved Fire Totems
					SM_FIValue(p_caster->SM_FDur, &totemspelltimer, TotemSpell->SpellGroupType);
					totemspelltime = totemspelltimer;
					break;
				}
			default:break;
			}

			pTotem->GetAIInterface()->m_totemspelltimer = totemspelltimer;
			pTotem->GetAIInterface()->m_totemspelltime = totemspelltime;
		}

		//in case these are our elemental totems then we should set them up
		if(GetProto()->Id==2062)
			pTotem->GetAIInterface()->Event_Summon_EE_totem(GetDuration());
		else if(GetProto()->Id==2894)
			pTotem->GetAIInterface()->Event_Summon_FE_totem(GetDuration());
	}
	else
	{
		pTotem->PushToWorld(m_caster->GetMapMgr()); //Push the sentry totem...
		//p_caster->SetUInt64Value(PLAYER_FARSIGHT, pTotem->GetGUID()); //works but farsight bugs it
	}
	pTotem->GetAIInterface()->SetAllowedToEnterCombat(false);
	pTotem->GetAIInterface()->m_canMove = false;
	// Set up the deletion event. The totem needs to expire after a certain time, or upon its death.
	sEventMgr.AddEvent(pTotem, &Creature::TotemExpire, EVENT_TOTEM_EXPIRE, GetDuration(), 1,0);
}

void Spell::SpellEffectEnchantHeldItem( uint32 i )
{
	if( !playerTarget ) return;

	Item * item = playerTarget->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
	if( !item )
		return;

	uint32 Duration = 1800; // Needs to be found in dbc.. I guess?
	switch( GetProto()->NameHash )
	{
	case SPELL_HASH_WINDFURY_WEAPON: // Windfury Weapon Effect
		{
			Duration = 10;
		}
	case SPELL_HASH_FLAMETONGUE_WEAPON: // Flametongue Weapon Effect
		{
			Duration = 10;
		}
	}
	EnchantEntry * Enchantment = dbcEnchant.LookupEntry( GetProto()->EffectMiscValue[i] );

	if( !Enchantment )
		return;

	/* Windfury Totem removed in 3.0.2
	if (m_spellInfo->NameHash == SPELL_HASH_WINDFURY_TOTEM_EFFECT && item->HasEnchantmentOnSlot( 1 ) && item->GetEnchantment( 1 )->Enchantment != Enchantment) //dirty fix for Windfury totem not overwriting existing enchantments
	return;
	*/

	item->RemoveEnchantment( 1 );
	item->AddEnchantment( Enchantment, Duration, false, true, false, 1 );
}

void Spell::SpellEffectSelfResurrect(uint32 i)
{
	if(!p_caster || !unitTarget || playerTarget->isAlive()) return;

	uint32 mana;
	uint32 health;
	uint32 class_=unitTarget->getClass();

	switch(GetProto()->Id)
	{
	case 3026:
	case 20758:
	case 20759:
	case 20760:
	case 20761:
	case 27240:
		{
			health = GetProto()->EffectMiscValue[i];
			mana = -damage;
		}break;
	case 21169: //Reincarnation. Resurrect with 20% health and mana
		{
			int32 amt = 20;
			if( GetProto()->SpellGroupType)
			{
				SM_FIValue(unitTarget->SM_FMiscEffect,&amt,GetProto()->SpellGroupType);
				SM_PIValue(unitTarget->SM_PMiscEffect,&amt,GetProto()->SpellGroupType);
			}
			health = uint32((unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * amt) / 100);
			mana = uint32((unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1) * amt) / 100);
		}
		break;
	default:
		{
			if(damage < 0) return;
			health = uint32(unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * damage / 100);
			mana = uint32(unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1) * damage / 100);
		}break;
	}

	if(class_ == WARRIOR || class_ == ROGUE)
		mana=0;

	playerTarget->m_resurrectHealth = health;
	playerTarget->m_resurrectMana = mana;

	playerTarget->ResurrectPlayer();
	playerTarget->SetMovement(MOVE_UNROOT, 1);

	playerTarget->SetUInt32Value(PLAYER_SELF_RES_SPELL, 0);

	if(GetProto()->Id==21169)
		AddCooldown();
}

void Spell::SpellEffectSkinning(uint32 i)
{
	if( !unitTarget || !unitTarget->IsCreature() ) 
		return;

	Creature * cr = TO_CREATURE( unitTarget );
	uint32 skill = cr->GetRequiredLootSkill();
	uint32 sk = TO_PLAYER( m_caster )->_GetSkillLineCurrent( skill );
	uint32 lvl = cr->getLevel();

	if( ( sk >= lvl * 5 ) || ( ( sk + 100 ) >= lvl * 10 ) )
	{
		//Fill loot for Skinning
		lootmgr.FillSkinningLoot(&cr->loot,unitTarget->GetEntry());
		TO_PLAYER( m_caster )->SendLoot( unitTarget->GetGUID(), LOOT_SKINNING );

		//Not skinable again
		cr->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);
		cr->Skinned = true;

		if(cr->GetCreatureInfo()->Rank > 0)
			DetermineSkillUp(skill ,sk < lvl * 5 ? sk/5 : lvl, 2);
		else
			DetermineSkillUp(skill ,sk < lvl * 5 ? sk/5 : lvl, 1);
	}
	else
	{
		SendCastResult(SPELL_FAILED_TARGET_UNSKINNABLE);
	}
}

void Spell::SpellEffectCharge(uint32 i)
{
	if(!unitTarget || !unitTarget->isAlive()) return;
	if (u_caster->IsStunned() || u_caster->m_rooted || u_caster->IsPacified() || u_caster->IsFeared())
		return;

	float x, y, z;
	float dx,dy;
	//if(unitTarget->GetTypeId() == TYPEID_UNIT)
	//	if(unitTarget->GetAIInterface())
	//		unitTarget->GetAIInterface()->StopMovement(5000);
	if(unitTarget->GetPositionX() == 0.0f || unitTarget->GetPositionY() == 0.0f)
		return;
	dx=unitTarget->GetPositionX()-m_caster->GetPositionX();
	dy=unitTarget->GetPositionY()-m_caster->GetPositionY();
	if(dx == 0.0f || dy == 0.0f)
		return;
	float d = sqrt(dx*dx+dy*dy)-unitTarget->GetFloatValue(UNIT_FIELD_BOUNDINGRADIUS)-m_caster->GetFloatValue(UNIT_FIELD_BOUNDINGRADIUS);
	float alpha = atanf(dy/dx);
	if(dx<0)
		alpha += float(M_PI);

	x = d * cosf(alpha) + m_caster->GetPositionX();
	y = d * sinf(alpha) + m_caster->GetPositionY();
	z = unitTarget->GetPositionZ();

	uint32 time = uint32( (m_caster->CalcDistance(unitTarget) / ((m_caster->m_runSpeed * 3.5) * 0.001f)) + 0.5);

	WorldPacket data(SMSG_MONSTER_MOVE, 50);
	data << m_caster->GetNewGUID();
	data << uint8(0);
	data << m_caster->GetPositionX();
	data << m_caster->GetPositionY();
	data << m_caster->GetPositionZ();
	data << getMSTime();
	data << uint8(0x00);
	data << uint32(0x00001000);
	data << time;
	data << uint32(1);
	data << x << y << z;
	if(unitTarget->GetTypeId() == TYPEID_UNIT)
		unitTarget->GetAIInterface()->StopMovement(2000);

	u_caster->SendMessageToSet(&data, true);

	u_caster->SetPosition(x,y,z,alpha,true);
	u_caster->addStateFlag(UF_ATTACKING);
	u_caster ->smsg_AttackStart( unitTarget );
	u_caster->setAttackTimer(time, false);
	u_caster->setAttackTimer(time, true);

	// trigger an event to reset speedhack detection
	if( p_caster )
	{
		p_caster->EventAttackStart();
		p_caster->SpeedCheatDelay( time + 1000 );
		p_caster->z_axisposition = 0.0f;
	}
}

void Spell::SpellEffectSummonCritter(uint32 i)
{
	if(!u_caster || !u_caster->IsInWorld())
		return;

	uint32 SummonCritterID = GetProto()->EffectMiscValue[i];

	// GetProto()->EffectDieSides[i] has something to do with dismissing our critter
	// when it is 1, it means to just dismiss it if we already have it
	// when it is 0, it could mean to always summon a new critter, but there seems to be exceptions

	if(u_caster->critterPet)
	{
		// if we already have this critter, we will just dismiss it and return
		if(u_caster->critterPet->GetCreatureInfo() && u_caster->critterPet->GetCreatureInfo()->Id == SummonCritterID)
		{
			u_caster->critterPet->RemoveFromWorld(false,true);
			delete u_caster->critterPet;
			u_caster->critterPet = NULL;
			return;
		}
		// this is a different critter, so we will dismiss our current critter and then go on to summon the new one
		else
		{
			u_caster->critterPet->RemoveFromWorld(false,true);
			delete u_caster->critterPet;
			u_caster->critterPet = NULL;
		}
	}

	if(!SummonCritterID) return;

	CreatureInfo * ci = CreatureNameStorage.LookupEntry(SummonCritterID);
	CreatureProto * cp = CreatureProtoStorage.LookupEntry(SummonCritterID);

	if(!ci || !cp) return;

	Creature * pCreature = u_caster->GetMapMgr()->CreateCreature(SummonCritterID);
	pCreature->SetInstanceID(u_caster->GetMapMgr()->GetInstanceID());
	pCreature->Load(cp, m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ());
	pCreature->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 35);
	pCreature->_setFaction();
	pCreature->SetUInt32Value(UNIT_FIELD_LEVEL, 1);
	pCreature->GetAIInterface()->Init(pCreature,AITYPE_PET,MOVEMENTTYPE_NONE,u_caster);
	pCreature->GetAIInterface()->SetUnitToFollow(u_caster);
	pCreature->GetAIInterface()->SetUnitToFollowAngle(float(-(M_PI/2)));
	pCreature->GetAIInterface()->SetFollowDistance(GetRadius(i));
	pCreature->GetAIInterface()->disable_melee = true;
	pCreature->bInvincible = true;
	pCreature->PushToWorld(u_caster->GetMapMgr());
	u_caster->critterPet = pCreature;
}

void Spell::SpellEffectKnockBack(uint32 i)
{
	if(!playerTarget || !playerTarget->isAlive() || !m_caster || m_caster == playerTarget)
		return;

	float dx, dy;
	float value1 = float(GetProto()->EffectBasePoints[i]+1);
	float value2 = float(GetProto()->EffectMiscValue[i]);
	float proportion;
	value2 ? proportion = value1/value2 : proportion = 0;

	if(proportion)
	{
		value1 = value1 / (10 * proportion);
		value2 = value2 / 10 * proportion;
	}
	else
	{
		value2 = value1 / 10;
		value1 = 0.1f;
	}

	dx = sinf(m_caster->GetOrientation());
	dy = cosf(m_caster->GetOrientation());

	WorldPacket data(SMSG_MOVE_KNOCK_BACK, 50);
	data << unitTarget->GetNewGUID();
	data << getMSTime();
	data << dy << dx;
	data << value1;
	data << -value2;
	playerTarget->GetSession()->SendPacket(&data);
	//playerTarget->blinked = true;
	//playerTarget->SpeedCheatDelay(10000);
}

void Spell::SpellEffectDisenchant( uint32 i )
{
	if( !p_caster )
		return;

	Item* it = p_caster->GetItemInterface()->GetItemByGUID( m_targets.m_itemTarget );
	if( !it )
	{
		SendCastResult( SPELL_FAILED_CANT_BE_DISENCHANTED );
		return;
	}

	//Fill disenchanting loot
	p_caster->SetLootGUID( it->GetGUID() );
	if( !it->loot )
	{
		it->loot = new Loot;
		lootmgr.FillDisenchantingLoot( it->loot, it->GetEntry() );
	}

	Log.Debug( "SpellEffect", "Successfully disenchanted item %d", uint32( itemTarget->GetEntry() ) );
	p_caster->SendLoot( itemTarget->GetGUID(), LOOT_DISENCHANTING );

	//We can increase Enchanting skill up to 60
	uint32 skill = p_caster->_GetSkillLineCurrent( SKILL_ENCHANTING );
	if( skill && skill < 60 )
	{
		if( Rand( 100.0f - float( skill ) * 0.75f ) )
		{
			uint32 SkillUp = float2int32( 1.0f * sWorld.getRate( RATE_SKILLRATE ) );
			if( skill + SkillUp > 60 )
				SkillUp = 60 - skill;

			p_caster->_AdvanceSkillLine( SKILL_ENCHANTING, SkillUp );
		}
	}
	if( it == i_caster )
		i_caster = NULL;
}

void Spell::SpellEffectInebriate(uint32 i) // lets get drunk!
{
	if( playerTarget == NULL )
		return;

	// Drunkee!
	uint16 currentDrunk = playerTarget->GetDrunkValue();
	uint16 drunkMod = static_cast<uint16>(damage) * 256;
	if( currentDrunk + drunkMod > 0xFFFF )
		currentDrunk = 0xFFFF;
	else
		currentDrunk += drunkMod;
	playerTarget->SetDrunkValue( currentDrunk, i_caster ? i_caster->GetEntry() : 0 );
}

void Spell::SpellEffectFeedPet(uint32 i)  // Feed Pet
{
	// food flags and food level are checked in Spell::CanCast()
	if(!itemTarget || !p_caster)
		return;

	Pet *pPet = p_caster->GetSummon();
	if(!pPet)
		return;

	/**	Cast feed pet effect
	- effect is item level and pet level dependent, aura ticks are 35, 17, 8 (*1000) happiness
	- http://petopia.brashendeavors.net/html/articles/basics_feeding.shtml */
	int8 deltaLvl = static_cast<int8>(pPet->getLevel() - itemTarget->GetProto()->ItemLevel);
	damage /= 1000; //damage of Feed pet spell is 35000
	if(deltaLvl > 10) damage = damage >> 1;//divide by 2
	if(deltaLvl > 20) damage = damage >> 1;
	damage *= 1000;

	SpellEntry *spellInfo = dbcSpell.LookupEntry(GetProto()->EffectTriggerSpell[i]);
	Spell *sp = SpellPool.PooledNew();
	if (!sp)
		return;
	sp->Init(static_cast<Object*>(p_caster),spellInfo,true,NULL);
	sp->forced_basepoints[0] = damage;
	SpellCastTargets tgt;
	tgt.m_unitTarget=pPet->GetGUID();
	sp->prepare(&tgt);

	if(itemTarget->GetUInt32Value(ITEM_FIELD_STACK_COUNT)>1)
	{
		itemTarget->ModUnsigned32Value(ITEM_FIELD_STACK_COUNT, -1);
		itemTarget->m_isDirty=true;
	}
	else
	{
		p_caster->GetItemInterface()->SafeFullRemoveItemByGuid(itemTarget->GetGUID());
		itemTarget=NULL;
	}
}

void Spell::SpellEffectDismissPet(uint32 i)
{
	// remove pet.. but don't delete so it can be called later
	if(!p_caster) return;

	Pet *pPet = p_caster->GetSummon();
	if(!pPet) return;
	pPet->Remove( true, true );
}

void Spell::SpellEffectReputation(uint32 i)
{
	if(!playerTarget)
		return;

	//playerTarget->modReputation(GetProto()->EffectMiscValue[i], damage, true);
	playerTarget->ModStanding(GetProto()->EffectMiscValue[i], damage);
}

void Spell::SpellEffectSummonObjectSlot(uint32 i)
{
	if(!u_caster || !u_caster->IsInWorld())
		return;
	GameObject *GoSummon = NULL;

	uint32 slot=GetProto()->Effect[i] - SPELL_EFFECT_SUMMON_OBJECT_SLOT1;
	GoSummon = u_caster->m_ObjectSlots[slot] ? u_caster->GetMapMgr()->GetGameObject(u_caster->m_ObjectSlots[slot]) : 0;
	u_caster->m_ObjectSlots[slot] = 0;

	if( GoSummon )
	{
		if(GoSummon->GetInstanceID() != u_caster->GetInstanceID())
			GoSummon->ExpireAndDelete();
		else
		{
			if( GoSummon->IsInWorld() )
				GoSummon->RemoveFromWorld(true);
			delete GoSummon;
		}
	}


	// spawn a new one
	GoSummon = u_caster->GetMapMgr()->CreateGameObject(GetProto()->EffectMiscValue[i]);
	if(! GoSummon->CreateFromProto(GetProto()->EffectMiscValue[i], m_caster->GetMapId(), m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ(), m_caster->GetOrientation() ))
	{
		delete GoSummon;
		return;
	}

	GoSummon->SetUInt32Value(GAMEOBJECT_LEVEL, u_caster->getLevel());
	GoSummon->SetUInt64Value(OBJECT_FIELD_CREATED_BY, m_caster->GetGUID());
	GoSummon->SetInstanceID(m_caster->GetInstanceID());

	if(GoSummon->GetByte(GAMEOBJECT_BYTES_1, 1) == GAMEOBJECT_TYPE_TRAP)
	{
		GoSummon->invisible = true;
		GoSummon->invisibilityFlag = INVIS_FLAG_TRAP;
		GoSummon->charges = 1;
		GoSummon->checkrate = 1;
		sEventMgr.AddEvent(GoSummon, &GameObject::TrapSearchTarget, EVENT_GAMEOBJECT_TRAP_SEARCH_TARGET, 100, 0,0);
	}
	sEventMgr.AddEvent(GoSummon, &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_EXPIRE, GetDuration(), 1,0); 

	GoSummon->PushToWorld(m_caster->GetMapMgr());
	GoSummon->SetSummoned(u_caster);
	u_caster->m_ObjectSlots[slot] = GoSummon->GetUIdFromGUID();
}

void Spell::SpellEffectDispelMechanic(uint32 i)
{
	if( !unitTarget || !unitTarget->isAlive() )
		return;
	/* this was already working before...
	uint32 sMisc = GetProto()->EffectMiscValue[i];

	for( uint32 x = 0 ; x<MAX_AURAS ; x++ )
	{
	if( unitTarget->m_auras[x] && !unitTarget->m_auras[x]->IsPositive())
	{
	if( unitTarget->m_auras[x]->GetSpellProto()->MechanicsType == sMisc )
	unitTarget->m_auras[x]->Remove();
	}
	}
	*/
	unitTarget->RemoveAllAurasByMechanic( GetProto()->EffectMiscValue[i] , GetProto()->EffectBasePoints[i] , false );

	/*Shady: if it's about Daze spell - dismount should be done by RemoveAllAurasByMechanic.
	We don't need useless code or hackfixes here, so commented.*/
	//if( playerTarget && GetProto()->NameHash == SPELL_HASH_DAZED && playerTarget->IsMounted() )
	//	playerTarget->RemoveAura(playerTarget->m_MountSpellId);
}

void Spell::SpellEffectSummonDeadPet(uint32 i)
{//this is pet resurrect
	if(!p_caster)
		return;
	Pet *pPet = p_caster->GetSummon();
	if(pPet)
	{
		if( GetProto()->SpellGroupType)
		{
			SM_FIValue(p_caster->SM_FMiscEffect,&damage,GetProto()->SpellGroupType);
			SM_PIValue(p_caster->SM_PMiscEffect,&damage,GetProto()->SpellGroupType);
		}

		pPet->SetUInt32Value( UNIT_DYNAMIC_FLAGS, 0 );
		pPet->SetUInt32Value( UNIT_FIELD_HEALTH, ( uint32 )( ( pPet->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * damage ) / 100 ));
		pPet->setDeathState( ALIVE );
		pPet->GetAIInterface()->HandleEvent( EVENT_FOLLOWOWNER, pPet, 0 );
		sEventMgr.RemoveEvents( pPet, EVENT_PET_DELAYED_REMOVE );
		pPet->SendSpellsToOwner();
	}
}

/* This effect has 2 functions
* 1. It delete's all current totems from the player
* 2. It returns a percentage of the mana back to the player
*
* Bur kick my ass if this is not safe:P
*/

void Spell::SpellEffectDestroyAllTotems(uint32 i)
{
	/*if(!p_caster || !p_caster->IsInWorld()) return;

	float RetreivedMana = 0.0f;
	for(uint32 x=0;x<4;x++)
	{
		// atm totems are considered creatures
		if(p_caster->m_TotemSlots[x])
		{
			uint32 SpellID = p_caster->m_TotemSlots[x]->GetUInt32Value(UNIT_CREATED_BY_SPELL);
			SpellEntry * sp = dbcSpell.LookupEntry(SpellID);
			if (!sp)
				continue;

			float pts = float(GetProto()->EffectBasePoints[i]+1) / 100.0f;
			RetreivedMana += float(sp->manaCost) * pts;

			p_caster->m_TotemSlots[x]->TotemExpire();
		}

		if(p_caster->m_ObjectSlots[x])
		{
			GameObject * obj = p_caster->GetMapMgr()->GetGameObject(p_caster->m_ObjectSlots[x]);
			if(obj)
			{
				obj->ExpireAndDelete();
			}
			p_caster->m_ObjectSlots[x] = 0;
		}
	}

	p_caster->Energize( p_caster, GetProto()->Id, uint32( RetreivedMana ), POWER_TYPE_MANA );*/
	if(!p_caster || !p_caster->IsInWorld()) return;

	uint32 RetreivedMana = 0;
	for(uint32 x=0;x<4;x++)
	{
		// atm totems are considered creatures
		if(p_caster->m_TotemSlots[x])
		{
			uint32 SpellID = p_caster->m_TotemSlots[x]->GetUInt32Value(UNIT_CREATED_BY_SPELL);
			SpellEntry * sp = dbcSpell.LookupEntry(SpellID);
			if (!sp)
				continue;

			RetreivedMana += 0.25*(p_caster->GetUInt32Value(UNIT_FIELD_MAXPOWER1)*sp->ManaCostPercentage)/100;

			p_caster->m_TotemSlots[x]->TotemExpire();
		}

		if(p_caster->m_ObjectSlots[x])
		{
			GameObject * obj = p_caster->GetMapMgr()->GetGameObject(p_caster->m_ObjectSlots[x]);
			if(obj)
			{
				obj->ExpireAndDelete();
			}
			p_caster->m_ObjectSlots[x] = 0;
		}
	}

	if( RetreivedMana > 0 )
		p_caster->Energize(p_caster, m_spellInfo->Id, RetreivedMana, POWER_TYPE_MANA);
}

void Spell::SpellEffectSummonDemon(uint32 i)
{
	if(!p_caster/* ||  p_caster->getClass() != WARLOCK */) //summoning a demon shouldn't be warlock only, see spells 25005, 24934, 24810 etc etc
		return;
	Pet *pPet = p_caster->GetSummon();
	if(pPet)
	{
		pPet->Dismiss();
	}

	CreatureInfo *ci = CreatureNameStorage.LookupEntry(GetProto()->EffectMiscValue[i]);
	if(ci)
	{
		LocationVector *vec = NULL;
		if( m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION && m_targets.m_destX && m_targets.m_destY && m_targets.m_destZ )
		{
			vec = new LocationVector(m_targets.m_destX, m_targets.m_destY, m_targets.m_destZ);
		}
		pPet = objmgr.CreatePet( GetProto()->EffectMiscValue[i] );
		pPet->CreateAsSummon(GetProto()->EffectMiscValue[i], ci, NULL, p_caster, GetProto(), 1, 300000, vec);
		if (vec) delete vec;
	}
	//Create Enslave Aura if its inferno spell
	if(GetProto()->Id == 1122)
	{
		SpellEntry *spellInfo = dbcSpell.LookupEntry(11726);

		Spell *sp = SpellPool.PooledNew();
		if (!sp)
			return;
		sp->Init(static_cast<Object*>(pPet),spellInfo,true,NULL);
		SpellCastTargets tgt;
		tgt.m_unitTarget=pPet->GetGUID();
		sp->prepare(&tgt);
	}
}

void Spell::SpellEffectResurrectNew(uint32 i)
{
	//base p =hp,misc mana
	if(!playerTarget)
	{
		if(!corpseTarget)
		{
			// unit resurrection handler
			if(unitTarget)
			{
				if(unitTarget->GetTypeId()==TYPEID_UNIT && unitTarget->IsPet() && unitTarget->IsDead())
				{
					uint32 hlth = ((uint32)GetProto()->EffectBasePoints[i] > unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH)) ? unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH) : (uint32)GetProto()->EffectBasePoints[i];
					uint32 mana = ((uint32)GetProto()->EffectBasePoints[i] > unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1)) ? unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1) : (uint32)GetProto()->EffectBasePoints[i];

					if(!unitTarget->IsPet())
					{
						sEventMgr.RemoveEvents(unitTarget, EVENT_CREATURE_REMOVE_CORPSE);
					}
					else
					{
						sEventMgr.RemoveEvents(unitTarget, EVENT_PET_DELAYED_REMOVE);
						sEventMgr.RemoveEvents(unitTarget, EVENT_CREATURE_REMOVE_CORPSE);
					}
					unitTarget->SetUInt32Value(UNIT_FIELD_HEALTH, hlth);
					unitTarget->SetUInt32Value(UNIT_FIELD_POWER1, mana);
					unitTarget->SetUInt32Value(UNIT_DYNAMIC_FLAGS, 0);
					unitTarget->setDeathState(ALIVE);
					static_cast<Creature*>(unitTarget)->Tagged=false;
					static_cast<Creature*>(unitTarget)->TaggerGuid=false;
					static_cast<Creature*>(unitTarget)->loot.gold=0;
					static_cast<Creature*>(unitTarget)->loot.looters.clear();
					static_cast<Creature*>(unitTarget)->loot.items.clear();
				}
			}

			return;
		}
		playerTarget = objmgr.GetPlayer(corpseTarget->GetUInt32Value(CORPSE_FIELD_OWNER));
		if(!playerTarget) return;
	}

	if(playerTarget->isAlive() || !playerTarget->IsInWorld())
		return;
	//resurrect
	//playerTarget->resurrector = p_caster->GetLowGUID();
	playerTarget->m_resurrectMapId = p_caster->GetMapId();
	playerTarget->m_resurrectInstanceID = p_caster->GetInstanceID();
	playerTarget->m_resurrectPosition = p_caster->GetPosition();
	playerTarget->m_resurrectHealth = damage;
	playerTarget->m_resurrectMana = GetProto()->EffectMiscValue[i];

	SendResurrectRequest( playerTarget );
}

void Spell::SpellEffectAttackMe(uint32 i)
{
	if(!unitTarget || !unitTarget->isAlive())
		return;

	unitTarget->GetAIInterface()->AttackReaction(u_caster,1,0);
}

void Spell::SpellEffectSkinPlayerCorpse(uint32 i)
{
	Corpse * corpse = 0;
	if(!playerTarget)
	{
		// means we're "skinning" a corpse
		corpse = objmgr.GetCorpse((uint32)m_targets.m_unitTarget);  // hacky
	}
	else if(playerTarget->getDeathState() == CORPSE)	// repopped while we were casting
	{
		corpse = objmgr.GetCorpse(playerTarget->GetLowGUID());
	}

	if(!m_caster->IsPlayer())
		return;

	if(playerTarget && !corpse)
	{
		if(!playerTarget->m_bg || !playerTarget->IsDead())
			return;

		// Set all the lootable stuff on the player. If he repops before we've looted, we'll set the flags
		// on corpse then :p

		playerTarget->bShouldHaveLootableOnCorpse = false;
		playerTarget->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);
		playerTarget->SetFlag(UNIT_DYNAMIC_FLAGS, U_DYN_FLAG_LOOTABLE);

		// Send the loot.
		p_caster->SendLoot(playerTarget->GetGUID(), LOOT_SKINNING);

		// Send a message to the died player, telling him he has to resurrect at the graveyard.
		// Send an empty corpse location too, :P

		playerTarget->GetSession()->OutPacket(SMSG_PLAYER_SKINNED, 1, "\x00");
		playerTarget->GetSession()->OutPacket(MSG_CORPSE_QUERY, 1, "\x00");

		// don't allow him to spawn a corpse
		playerTarget->bCorpseCreateable = false;

		// and.. force him to the graveyard and repop him.
		playerTarget->RepopRequestedPlayer();

	}else if(corpse)
	{
		// find the corpses' owner
		Player * owner = objmgr.GetPlayer(corpse->GetUInt32Value(CORPSE_FIELD_OWNER));
		if(owner)
		{
			if(!owner->m_bg) return;

			owner->GetSession()->OutPacket(SMSG_PLAYER_SKINNED, 1, "\x00");
			owner->GetSession()->OutPacket(MSG_CORPSE_QUERY, 1, "\x00");
		}

		if(corpse->GetUInt32Value(CORPSE_FIELD_DYNAMIC_FLAGS) != 1)
			corpse->SetUInt32Value(CORPSE_FIELD_DYNAMIC_FLAGS, 1); // sets it so you can loot the plyr

		// remove skinnable flag
		corpse->SetUInt32Value(CORPSE_FIELD_FLAGS, 5);

		// remove owner association
		corpse->SetUInt64Value(CORPSE_FIELD_OWNER, 0);
		corpse->SetCorpseState(CORPSE_STATE_BONES);
		corpse->DeleteFromDB();
		objmgr.CorpseAddEventDespawn(corpse);

		// send loot
		p_caster->SendLoot(corpse->GetGUID(), LOOT_SKINNING);
	}
}

void Spell::SpellEffectSkill(uint32 i)
{
	// Used by professions only
	// Effect should be renamed in RequireSkill

	if ( !p_caster || p_caster->_GetSkillLineMax(GetProto()->EffectMiscValue[i]) >= uint32( damage * 75 ) )
		return;

	if ( p_caster->_HasSkillLine( GetProto()->EffectMiscValue[i]) )
		p_caster->_ModifySkillMaximum( GetProto()->EffectMiscValue[i], uint32( damage * 75 ) );
	else
		p_caster->_AddSkillLine( GetProto()->EffectMiscValue[i], 1, uint32( damage * 75 ) );
}

void Spell::SpellEffectApplyPetAura(uint32 i)
{
	SpellEffectApplyAura(i);
}

void Spell::SpellEffectDummyMelee( uint32 i ) // Normalized Weapon damage +
{
	if( !unitTarget || !u_caster )
		return;
	
	if( GetProto()->NameHash == SPELL_HASH_OVERPOWER && p_caster ) //warrior : overpower - let us clear the event and the combopoint count
	{
		p_caster->NullComboPoints(); //some say that we should only remove 1 point per dodge. Due to cooldown you can't cast it twice anyway..
		sEventMgr.RemoveEvents( p_caster, EVENT_COMBO_POINT_CLEAR_FOR_TARGET );
	}
	else if( GetProto()->NameHash == SPELL_HASH_DEVASTATE)
	{
		//count the number of sunder armors on target
		uint32 sunder_count=0;
		SpellEntry *spellInfo=dbcSpell.LookupEntry(25225);
		for(uint32 x = MAX_NEGATIVE_AURAS_EXTEDED_START; x < MAX_NEGATIVE_AURAS_EXTEDED_END; ++x)
			if(unitTarget->m_auras[x] && unitTarget->m_auras[x]->GetSpellProto()->NameHash==SPELL_HASH_SUNDER_ARMOR)
			{
				sunder_count++;
				spellInfo=unitTarget->m_auras[x]->GetSpellProto();
			}
			if(!spellInfo)
				return; //omg how did this happen ?
			//we should also cast sunder armor effect on target with or without dmg
			Spell *spell = SpellPool.PooledNew();
			if (!spell)
				return;
			spell->Init(u_caster, spellInfo ,true, NULL);
			spell->ProcedOnSpell = GetProto();
			spell->pSpellId=GetProto()->Id;
			SpellCastTargets targets(unitTarget->GetGUID());
			spell->prepare(&targets);
			if(!sunder_count)
				return; //no damage = no joy
			damage = damage*sunder_count;
	}
	
	//Hemorrhage
	if( p_caster && GetProto()->NameHash == SPELL_HASH_HEMORRHAGE )
		p_caster->AddComboPoints(p_caster->GetSelection(), 1);

	switch( GetProto()->Id )
	{
		// AMBUSH
		case 8676: add_damage = 77; return; break;			// r1
		case 8724: add_damage = 110; return; break;			// r2
		case 8725: add_damage = 138; return; break;			// r3
		case 11267: add_damage = 204; return; break;		// r4
		case 11268: add_damage = 253; return; break;		// r5
		case 11269: add_damage = 319; return; break;		// r6
		case 27441: add_damage = 369; return; break;		// r7
		case 48689: add_damage = 509; return; break;		// r8
		case 48690: add_damage = 770; return; break;		// r9
		case 48691: add_damage = 908; return; break;		// r10

		// BACKSTAB
		case 53: add_damage = 15; return; break;			// r1
		case 2589: add_damage = 30; return; break;			// r2
		case 2590: add_damage = 48; return; break;			// r3
		case 2591: add_damage = 69; return; break;			// r4
		case 8721: add_damage = 90; return; break;			// r5
		case 11279: add_damage = 135; return; break;		// r6
		case 11280: add_damage = 165; return; break;		// r7
		case 11281: add_damage = 210; return; break;		// r8
		case 25300: add_damage = 225; return; break;		// r9
		case 26863: add_damage = 255; return; break;		// r10
		case 48656: add_damage = 383; return; break;		// r11
		case 48657: add_damage = 465; return; break;		// r12
	}

	// rogue ambush etc
	for (uint32 x =0;x<3;x++)
		if(GetProto()->Effect[x] == SPELL_EFFECT_WEAPON_PERCENT_DAMAGE)
		{
			add_damage = damage * (GetProto()->EffectBasePoints[x]+1) /100;
		}

		//rogue - mutilate ads dmg if target is poisoned
		uint32 pct_dmg_mod = 100;
		if(	GetProto()->NameHash == SPELL_HASH_MUTILATE && unitTarget->IsPoisoned() )
			pct_dmg_mod = 120;

		uint32 _type;
		if( GetType() == SPELL_DMG_TYPE_RANGED )
			_type = RANGED;
		else
		{
			if (GetProto()->AttributesExC & 0x1000000)
				_type =  OFFHAND;
			else
				_type = MELEE;
		}
	switch( m_spellInfo->Id )	// Frappe de sang
	{
		// Rang 1
		case 45902:
			damage = 0 + 104;
			pct_dmg_mod = 40;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
		
		// Rang 2
		case 49926:
			damage = 0 + 118;
			pct_dmg_mod = 40;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
		
		// Rang 3
		case 49927:
			damage = 0 + 138.8;
			pct_dmg_mod = 40;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
		
		// Rang 4
		case 49928:
			damage = 0 + 164.4;
			pct_dmg_mod = 40;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
		
		// Rang 5
		case 49929:
			damage = 0 + 250;
			pct_dmg_mod = 40;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
		
		// Rang 6
		case 49930:
			damage = 0 + 305.6;
			pct_dmg_mod = 40;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
	}
	
	switch( m_spellInfo->Id )	// Frappe du Fl�au
	{
		// Rang 1
		case 55090:
			damage = 0 + 151.875;
			pct_dmg_mod = 45;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.11);
			}
			
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.11);
			}
			break;
			
		// Rang 2
		case 55265:
			damage = 0 + 186.75;
			pct_dmg_mod = 45;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.11);
			}
			
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.11);
			}
			break;
			
		// Rang 3
		case 55270:
			damage = 0 + 291.375;
			pct_dmg_mod = 45;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.11);
			}
			
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.11);
			}
			break;
			
		// Rang 4
		case 55271:
			damage = 0 + 357.188;
			pct_dmg_mod = 45;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.11);
			}
			
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.11);
			}
			break;
	}
		
	switch( m_spellInfo->Id )	// Frappe au coeur
	{
		// Rang 1
		case 55050:
			damage = 0 + 125;
			pct_dmg_mod = 50;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
		
		// Rang 2
		case 55258:
			damage = 0 + 142;
			pct_dmg_mod = 50;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
		
		// Rang 3
		case 55259:
			damage = 0 + 167;
			pct_dmg_mod = 50;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
		
		// Rang 4
		case 55260:
			damage = 0 + 197.5;
			pct_dmg_mod = 50;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
		
		// Rang 5
		case 55261:
			damage = 0 + 300.5;
			pct_dmg_mod = 50;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
		
		// Rang 6
		case 55262:
			damage = 0 + 368;
			pct_dmg_mod = 50;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
	}
	
	switch( m_spellInfo->Id )	// Frappe de peste
	{
		// Rang 1
		case 45462:
			damage = 0 + 62.5;
			pct_dmg_mod = 50;
			break;
		
		// Rang 2
		case 49917:
			damage = 0 + 75.5;
			pct_dmg_mod = 50;
			break;
			
		// Rang 3
		case 49918:
			damage = 0 + 89;
			pct_dmg_mod = 50;
			break;
		
		// Rang 4
		case 49919:
			damage = 0 + 108;
			pct_dmg_mod = 50;
			break;
		
		// Rang 5
		case 49920:
			damage = 0 + 157;
			pct_dmg_mod = 50;
			break;
		// Rang 6
		case 49921:
			damage = 0 + 189;
			pct_dmg_mod = 50;
			break;
	}
	
	switch( m_spellInfo->Id )	// Frappe de givre
	{
		// Rang 1
		case 49143:
			damage = 0 + 52.2;
			pct_dmg_mod = 60;
			break;
		// Rang 2
		case 51416:
			damage = 0 + 61.8;
			pct_dmg_mod = 60;
			break;
		// Rang 3
		case 51417:
			damage = 0 + 69;
			pct_dmg_mod = 60;
			break;
		// Rang 4
		case 51418:
			damage = 0 + 85.2;
			pct_dmg_mod = 60;
			break;
		// Rang 5
		case 51419:
			damage = 0 + 120.6;
			pct_dmg_mod = 60;
			break;
		// Rang 6
		case 55268:
			damage = 0 + 150;
			pct_dmg_mod = 60;
			break;
	}

	switch( m_spellInfo->Id )	// Frappe de mort
	{
		// Rang 1
		case 49998:
			damage = 0 + 84;
			pct_dmg_mod = 75;

			if(unitTarget->HasAura(55095))
			{
				uint32 gcurHealth = u_caster->GetUInt32Value(UNIT_FIELD_HEALTH);
				uint32 gmaxHealth = u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
				if((gcurHealth + (gmaxHealth * 0.05)) >= gmaxHealth)
				{
					u_caster->SetUInt32Value(UNIT_FIELD_HEALTH, gmaxHealth);
				}
				else
				{
					u_caster->ModUnsigned32Value(UNIT_FIELD_HEALTH, (gmaxHealth * 0.05));
				}
			}
			
			if(unitTarget->HasAura(55078))
			{
				uint32 gcurHealth = u_caster->GetUInt32Value(UNIT_FIELD_HEALTH);
				uint32 gmaxHealth = u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
				if((gcurHealth + (gmaxHealth * 0.05)) >= gmaxHealth)
				{
					u_caster->SetUInt32Value(UNIT_FIELD_HEALTH, gmaxHealth);
				}
				else
				{
					u_caster->ModUnsigned32Value(UNIT_FIELD_HEALTH, (gmaxHealth * 0.05));
				}
			}
			break;
			
		// Rang 2
		case 49999:
			damage = 0 + 97.5;
			pct_dmg_mod = 75;
			
			if(unitTarget->HasAura(55095))
			{
				uint32 gcurHealth = u_caster->GetUInt32Value(UNIT_FIELD_HEALTH);
				uint32 gmaxHealth = u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
				if((gcurHealth + (gmaxHealth * 0.05)) >= gmaxHealth)
				{
					u_caster->SetUInt32Value(UNIT_FIELD_HEALTH, gmaxHealth);
				}
				else
				{
					u_caster->ModUnsigned32Value(UNIT_FIELD_HEALTH, (gmaxHealth * 0.05));
				}
			}
			
			if(unitTarget->HasAura(55078))
			{
				uint32 gcurHealth = u_caster->GetUInt32Value(UNIT_FIELD_HEALTH);
				uint32 gmaxHealth = u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
				if((gcurHealth + (gmaxHealth * 0.05)) >= gmaxHealth)
				{
					u_caster->SetUInt32Value(UNIT_FIELD_HEALTH, gmaxHealth);
				}
				else
				{
					u_caster->ModUnsigned32Value(UNIT_FIELD_HEALTH, (gmaxHealth * 0.05));
				}
			}
			break;
			
		// Rang 3
		case 45463:
			damage = 0 + 123.75;
			pct_dmg_mod = 75;
			
			if(unitTarget->HasAura(55095))
			{
				uint32 gcurHealth = u_caster->GetUInt32Value(UNIT_FIELD_HEALTH);
				uint32 gmaxHealth = u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
				if((gcurHealth + (gmaxHealth * 0.05)) >= gmaxHealth)
				{
					u_caster->SetUInt32Value(UNIT_FIELD_HEALTH, gmaxHealth);
				}
				else
				{
					u_caster->ModUnsigned32Value(UNIT_FIELD_HEALTH, (gmaxHealth * 0.05));
				}
			}
			
			if(unitTarget->HasAura(55078))
			{
				uint32 gcurHealth = u_caster->GetUInt32Value(UNIT_FIELD_HEALTH);
				uint32 gmaxHealth = u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
				if((gcurHealth + (gmaxHealth * 0.05)) >= gmaxHealth)
				{
					u_caster->SetUInt32Value(UNIT_FIELD_HEALTH, gmaxHealth);
				}
				else
				{
					u_caster->ModUnsigned32Value(UNIT_FIELD_HEALTH, (gmaxHealth * 0.05));
				}
			}
			break;
			
		// Rang 4
		case 49923:
			damage = 0 + 187.5;
			pct_dmg_mod = 75;
			
			if(unitTarget->HasAura(55095))
			{
				uint32 gcurHealth = u_caster->GetUInt32Value(UNIT_FIELD_HEALTH);
				uint32 gmaxHealth = u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
				if((gcurHealth + (gmaxHealth * 0.05)) >= gmaxHealth)
				{
					u_caster->SetUInt32Value(UNIT_FIELD_HEALTH, gmaxHealth);
				}
				else
				{
					u_caster->ModUnsigned32Value(UNIT_FIELD_HEALTH, (gmaxHealth * 0.05));
				}
			}
			
			if(unitTarget->HasAura(55078))
			{
				uint32 gcurHealth = u_caster->GetUInt32Value(UNIT_FIELD_HEALTH);
				uint32 gmaxHealth = u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
				if((gcurHealth + (gmaxHealth * 0.05)) >= gmaxHealth)
				{
					u_caster->SetUInt32Value(UNIT_FIELD_HEALTH, gmaxHealth);
				}
				else
				{
					u_caster->ModUnsigned32Value(UNIT_FIELD_HEALTH, (gmaxHealth * 0.05));
				}
			}
			break;
			
		// Rang 5
		case 49924:
			damage = 0 + 222.75;
			pct_dmg_mod = 75;
			
			if(unitTarget->HasAura(55095))
			{
				uint32 gcurHealth = u_caster->GetUInt32Value(UNIT_FIELD_HEALTH);
				uint32 gmaxHealth = u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
				if((gcurHealth + (gmaxHealth * 0.05)) >= gmaxHealth)
				{
					u_caster->SetUInt32Value(UNIT_FIELD_HEALTH, gmaxHealth);
				}
				else
				{
					u_caster->ModUnsigned32Value(UNIT_FIELD_HEALTH, (gmaxHealth * 0.05));
				}
			}
			
			if(unitTarget->HasAura(55078))
			{
				uint32 gcurHealth = u_caster->GetUInt32Value(UNIT_FIELD_HEALTH);
				uint32 gmaxHealth = u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
				if((gcurHealth + (gmaxHealth * 0.05)) >= gmaxHealth)
				{
					u_caster->SetUInt32Value(UNIT_FIELD_HEALTH, gmaxHealth);
				}
				else
				{
					u_caster->ModUnsigned32Value(UNIT_FIELD_HEALTH, (gmaxHealth * 0.05));
				}
			}
			break;
	}
	
	switch( m_spellInfo->Id )	// An�antissement
	{
		// Rang 1
		case 49020:
			damage = 0 + 198.4;
			pct_dmg_mod = 80;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
			
		// Rang 2
		case 51423:
			damage = 0 + 244;
			pct_dmg_mod = 80;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
			
		// Rang 3
		case 51424:
			damage = 0 + 381.6;
			pct_dmg_mod = 80;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
			
		// Rang 4
		case 51425:
			damage = 0 + 467.2;
			pct_dmg_mod = 80;
			
			if(unitTarget->HasAura(55095))
			{
				damage += (damage*0.125);
			}
			if(unitTarget->HasAura(55078))
			{
				damage += (damage*0.125);
			}
			break;
	}
	u_caster->Strike( unitTarget, _type, GetProto(), damage, pct_dmg_mod, 0, false, true );
}

void Spell::SpellEffectFilming( uint32 i )
{
	if (!playerTarget || !playerTarget->isAlive() || !u_caster)
		return;

	if(playerTarget->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER))
		return;

	TaxiPath* taxipath = sTaxiMgr.GetTaxiPath(GetProto()->EffectMiscValue[0]);

	if( !taxipath )
		return;

	TaxiNode* taxinode = sTaxiMgr.GetTaxiNode( taxipath->GetSourceNode() );

	if( !taxinode )
		return;

	uint32 modelid =0;

	if( playerTarget->GetTeam() )
	{
		CreatureInfo* ci = CreatureNameStorage.LookupEntry( taxinode->horde_mount );
		if(!ci) return;
		modelid = ci->Male_DisplayID;
		if(!modelid) return;
	}
	else
	{
		CreatureInfo* ci = CreatureNameStorage.LookupEntry( taxinode->alliance_mount );
		if(!ci) return;
		modelid = ci->Male_DisplayID;
		if(!modelid) return;
	}

	playerTarget->DismissActivePet();
	playerTarget->TaxiStart( taxipath, modelid, 0 );
}

void Spell::SpellEffectPlayerPull( uint32 i )
{
	if( !unitTarget || !unitTarget->isAlive() || !unitTarget->IsPlayer() )
		return;

	Player* p_target = static_cast< Player* >( unitTarget );

	// calculate destination
	float pullD = p_target->CalcDistance( m_caster ) - p_target->GetFloatValue( UNIT_FIELD_BOUNDINGRADIUS ) - m_caster->GetFloatValue( UNIT_FIELD_BOUNDINGRADIUS ) - 1.0f;
	float pullO = p_target->calcRadAngle( p_target->GetPositionX(), p_target->GetPositionY(), m_caster->GetPositionX(), m_caster->GetPositionY() );
	float pullX = p_target->GetPositionX() + pullD * cosf( pullO );
	float pullY = p_target->GetPositionY() + pullD * sinf( pullO );
	float pullZ = m_caster->GetPositionZ() + 0.3f;
	uint32 time = uint32( pullD * 42.0f );

	p_target->SetOrientation( pullO );

	WorldPacket data( SMSG_MONSTER_MOVE, 60 );
	data << p_target->GetNewGUID();
	data << uint8(0);
	data << p_target->GetPositionX() << p_target->GetPositionY() << p_target->GetPositionZ();
	data << getMSTime();
	data << uint8( 4 );
	data << pullO;
	data << uint32( 0x00001000 );
	data << time;
	data << uint32( 1 );
	data << pullX << pullY << pullZ;

	p_target->SendMessageToSet( &data, true );
}

void Spell::SpellEffectReduceThreatPercent(uint32 i)
{
	if (!unitTarget || !unitTarget->IsCreature() || !u_caster || unitTarget->GetAIInterface()->getThreatByPtr(u_caster) == 0)
		return;

	unitTarget->GetAIInterface()->modThreatByPtr(u_caster, (int32)unitTarget->GetAIInterface()->getThreatByPtr(u_caster) * damage / 100);
}

void Spell::SpellEffectSpellSteal( uint32 i )
{
	if (!unitTarget || !u_caster || !unitTarget->isAlive())
		return;
	if(unitTarget->IsPlayer() && p_caster && p_caster != static_cast< Player* >(unitTarget))
	{
		if(static_cast< Player* >(unitTarget)->IsPvPFlagged())
			p_caster->SetPvPFlag();
	}

	Aura *aur;
	uint32 start, end;
	if(isAttackable(u_caster,unitTarget))
	{
		start=MAX_POSITIVE_AURAS_EXTEDED_START;
		end=MAX_POSITIVE_AURAS_EXTEDED_END;
	}
	else
		return;

	WorldPacket data(SMSG_SPELLDISPELLOG, 16);

	for(uint32 x=start;x<end;x++)
	{
		if (unitTarget->m_auras[x])
		{
			aur = unitTarget->m_auras[x];
			if(aur->GetSpellId() != 15007 && !aur->IsPassive()
				//				&& aur->IsPositive()	// Zack : We are only checking positive auras. There is no meaning to check again
				) //Nothing can dispel resurrection sickness
			{
				if(aur->GetSpellProto()->DispelType == DISPEL_MAGIC)
				{
					data.clear();
					data << m_caster->GetNewGUID();
					data << unitTarget->GetNewGUID();
					data << (uint32)1;
					data << aur->GetSpellId();
					m_caster->SendMessageToSet(&data,true);

					uint32 aurdur = ( aur->GetDuration()>120000 ? 120000 : aur->GetDuration() );
					Aura *aura = AuraPool.PooledNew();
					if (!aura)
						return;
					aura->Init(aur->GetSpellProto(), aurdur, u_caster, u_caster );
					uint32 aur_removed = unitTarget->RemoveAllAuraByNameHash( aur->GetSpellProto()->NameHash );
					for ( uint32 i = 0; i < 3; i++ )
					{
						if ( aura->GetSpellProto()->Effect[i] )
						{
							aura->AddMod( aura->GetSpellProto()->EffectApplyAuraName[i], aura->GetSpellProto()->EffectBasePoints[i]+1, aura->GetSpellProto()->EffectMiscValue[i], i );
						}
					}
					if( aura->GetSpellProto()->procCharges>0 )
					{
						Aura *aur;
						for(uint32 i = 0; i<aur_removed-1; i++)
						{
							aur = AuraPool.PooledNew();
							if (!aur)
								return;
							aur->Init(aura->GetSpellProto(), aurdur, u_caster, u_caster);
							u_caster->AddAura(aur);
						}
						if(!(aura->GetSpellProto()->procFlags & PROC_REMOVEONUSE))
						{
							SpellCharge charge;
							charge.count=aur_removed;
							charge.spellId=aura->GetSpellId();
							charge.ProcFlag=aura->GetSpellProto()->procFlags;
							charge.lastproc = 0;
							charge.procdiff = 0;
							u_caster->m_chargeSpells.insert(make_pair(aura->GetSpellId(),charge));
						}
					}
					u_caster->AddAura(aura);
					break;
				}
			}
		}
	}
}

void Spell::SpellEffectProspecting(uint32 i)
{
	if(!p_caster) return;

	if(!itemTarget) // this should never happen
	{
		SendCastResult(SPELL_FAILED_CANT_BE_PROSPECTED);
		return;
	}

	//Fill Prospecting loot
	p_caster->SetLootGUID(itemTarget->GetGUID());
	if( !itemTarget->loot )
	{
		itemTarget->loot = new Loot;
		lootmgr.FillProspectingLoot( itemTarget->loot , itemTarget->GetEntry());
	}

	if ( itemTarget->loot->items.size() > 0 )
	{
		Log.Debug("SpellEffect","Successfully prospected item %d", uint32(itemTarget->GetEntry()));
		p_caster->SendLoot( itemTarget->GetGUID(), LOOT_PROSPECTING );
	}
	else // this should never happen either
	{
		Log.Debug("SpellEffect","Prospecting failed, item %d has no loot", uint32(itemTarget->GetEntry()));
		SendCastResult(SPELL_FAILED_CANT_BE_PROSPECTED);
	}
}

void Spell::SpellEffectApplyAura128(uint32 i)
{
	if(GetProto()->EffectApplyAuraName[i] != 0)
		SpellEffectApplyAura(i);
}

void Spell::SpellEffectRedirectThreat(uint32 i)
{
	if (!p_caster || !unitTarget)
		return;

	if ((unitTarget->GetTypeId() == TYPEID_PLAYER && p_caster->GetGroup() != static_cast<Player *>(unitTarget)->GetGroup()) || (unitTarget->GetTypeId() == TYPEID_UNIT && !unitTarget->IsPet()))
		return;

	p_caster->SetMisdirectionTarget(unitTarget->GetGUID());
}

void Spell::SpellEffectForgetSpecialization(uint32 i)
{
	if (!playerTarget) return;

	uint32 spellid = GetProto()->EffectTriggerSpell[i];
	playerTarget->removeSpell( spellid, false, false, 0);

	sLog.outDebug("Player %u have forgot spell %u from spell %u ( caster: %u)", playerTarget->GetLowGUID(), spellid, GetProto()->Id, m_caster->GetLowGUID());
}

void Spell::SpellEffectRestorePowerPct(uint32 i)
{
	if( u_caster == NULL || unitTarget == NULL || !unitTarget->isAlive() )
		return;

	uint32 power = GetProto()->EffectMiscValue[i];
	if( power > POWER_TYPE_HAPPINESS )
	{
		sLog.outError("Unhandled power type %u in %s, report this line to devs.", power, __FUNCTION__ );
		return;
	}

	uint32 amount = damage * unitTarget->GetUInt32Value( UNIT_FIELD_MAXPOWER1 + power ) / 100;
	u_caster->Energize( unitTarget, GetProto()->Id, amount, power );
}

void Spell::SpellEffectTriggerSpellWithValue(uint32 i)
{
	if( !unitTarget) return;

	SpellEntry* TriggeredSpell = dbcSpell.LookupEntryForced(GetProto()->EffectTriggerSpell[i]);
	if( !TriggeredSpell )
		return;

	Spell *sp = SpellPool.PooledNew();
	if (!sp)
		return;
	sp->Init(m_caster, TriggeredSpell, true, NULL);

	for(uint32 x = 0; x<3; x++)
	{
		if( i == x )
			sp->forced_basepoints[x] = damage;	//prayer of mending should inherit heal bonus ?
		else
			sp->forced_basepoints[x] = TriggeredSpell->EffectBasePoints[i];

	}

	SpellCastTargets tgt(unitTarget->GetGUID());
	sp->prepare(&tgt);
}

void Spell::SpellEffectCreatePet(uint32 i)
{
	if( !playerTarget )
		return;

	if(playerTarget->GetSummon())
		playerTarget->GetSummon()->Remove( true, true );
	CreatureInfo *ci = CreatureNameStorage.LookupEntry( GetProto()->EffectMiscValue[i] );
	if( ci )
	{
		Pet *pPet = objmgr.CreatePet( GetProto()->EffectMiscValue[i] );
		pPet->CreateAsSummon( GetProto()->EffectMiscValue[i], ci, NULL, playerTarget, GetProto(), 1, 0 );
	}
}

void Spell::SpellEffectTeachTaxiPath( uint32 i )
{
	if( !playerTarget || !GetProto()->EffectTriggerSpell[i] )
		return;

	uint8 field = (uint8)((GetProto()->EffectTriggerSpell[i] - 1) / 32);
	uint32 submask = 1<<((GetProto()->EffectTriggerSpell[i]-1)%32);

	// Check for known nodes
	if (!(playerTarget->GetTaximask(field) & submask))
	{
		playerTarget->SetTaximask(field, (submask | playerTarget->GetTaximask(field)) );

		playerTarget->GetSession()->OutPacket(SMSG_NEW_TAXI_PATH);

		//Send packet
		WorldPacket update(SMSG_TAXINODE_STATUS, 9);
		update << uint64( 0 ) << uint8( 1 );
		playerTarget->GetSession()->SendPacket( &update );
	}
}

void Spell::SpellEffectDualWield2H( uint32 i )
{
	if( !playerTarget )
		return;

	playerTarget->DualWield2H = true;
}

void Spell::SpellEffectEnchantItemPrismatic(uint32 i)
{
	if(!itemTarget || !p_caster) return;
	EnchantEntry * Enchantment = dbcEnchant.LookupEntry(GetProto()->EffectMiscValue[i]);
	if(!Enchantment) return;

	itemTarget->RemoveEnchantment(0);
	int32 Slot = itemTarget->AddEnchantment(Enchantment, 0, true, true, false, 0);
	if(Slot < 0)
		return; // Apply failed
}

void Spell::SpellEffectCreateItem2(uint32 i) // Create item
{
	//TODO: This spell effect has also a misc value - meaning is unknown yet
	if( p_caster == NULL )
		return;

	uint32 new_item_id = GetProto()->EffectItemType[i];

	if( new_item_id != 0 )
	{
		// create item
		CreateItem( new_item_id );
	}
	else if( i_caster )
	{
		// provide player with item loot (clams)
		// TODO: Finish this
		/*if( !i_caster->loot )
		{
			i_caster->loot = new Loot;
			lootmgr.FillItemLoot( i_caster->loot, i_caster->GetEntry() );
		}
		p_caster->SetLootGUID( i_caster->GetGUID() );
		p_caster->SendLoot( i_caster->GetGUID(), LOOT_DISENCHANTING );
		*/	
	}
}

void Spell::SpellEffectMilling(uint32 i)
{
	if(!p_caster) return;

	if(!itemTarget) // this should never happen
	{
		SendCastResult(SPELL_FAILED_CANT_BE_PROSPECTED);
		return;
	}

	//Fill Prospecting loot
	p_caster->SetLootGUID(itemTarget->GetGUID());
	if( !itemTarget->loot )
	{
		itemTarget->loot = new Loot;
		lootmgr.FillMillingLoot( itemTarget->loot , itemTarget->GetEntry());
	}

	if ( itemTarget->loot->items.size() > 0 )
	{
		Log.Debug("SpellEffect","Successfully milled item %d", uint32(itemTarget->GetEntry()));
		p_caster->SendLoot( itemTarget->GetGUID(), LOOT_MILLING );
	}
	else // this should never happen either
	{
		Log.Debug("SpellEffect","Milling failed, item %d has no loot", uint32(itemTarget->GetEntry()));
		SendCastResult(SPELL_FAILED_CANT_BE_PROSPECTED);
	}
}

void Spell::SpellEffectRenamePet( uint32 i )
{
	if( !unitTarget || !unitTarget->IsPet() || 
		!static_cast<Pet*>(unitTarget)->GetPetOwner() || static_cast<Pet*>(unitTarget)->GetPetOwner()->getClass() != HUNTER )
		return;

	unitTarget->SetByte( UNIT_FIELD_BYTES_2, 2, 0x3 );
}

void Spell::SpellEffectSetTalentSpecsCount(uint32 i)
{
	if(!p_caster)
		return;

	if(p_caster->m_talentActiveSpec >= damage)
	{
		// activate primary spec
		p_caster->ApplySpec(0, false);
	}
	p_caster->m_talentSpecsCount = damage;
	

	// Send update
	p_caster->smsg_TalentsInfo(false, 0, 0);
}

void Spell::SpellEffectActivateTalentSpec(uint32 i)
{
	if(!p_caster)
		return;

	// 1 = primary, 2 = secondary
	p_caster->ApplySpec(uint8(damage - 1), false);

}

void Spell::SpellEffectConvertInDeathRunes(uint32 i)
{
	if(p_caster && p_caster->m_runes[0] != RUNE_RECHARGE)
	{
		p_caster->ConvertRune(0, RUNE_DEATH);
	}
	else if(p_caster && p_caster->m_runes[1] != RUNE_RECHARGE)
	{
		p_caster->ConvertRune(1, RUNE_DEATH);
	}
}

void Spell::SpellEffectDurabilityDamage(uint32 i)
{
    if(!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    int32 slot = GetProto()->EffectMiscValue[i];

	Item * pItem;
	Container * pContainer;
	uint32 j, k;

	// FIXME: some spells effects have value -1/-2
	// Possibly its mean -1 all player equipped items and -2 all items
    if(slot < 0)
    {
		for( k = 0; k < MAX_INVENTORY_SLOT; k++ )
		{
			pItem = p_caster->GetItemInterface()->GetInventoryItem( static_cast<uint16>( k ) );
			if( pItem != NULL )
			{
				if( pItem->IsContainer() )
				{
					pContainer = static_cast<Container*>( pItem );
					for( j = 0; j < pContainer->GetProto()->ContainerSlots; ++j )
					{
						pItem = pContainer->GetItem( static_cast<uint16>( j ) );
						if( pItem != NULL )
						{
							uint32 maxdur = pItem->GetDurabilityMax();
							uint32 olddur = pItem->GetDurability();
							uint32 newdur = (olddur) - (damage);

							if(newdur < 0)
								newdur = 0;

							if( newdur > maxdur )
								newdur = maxdur;

							pItem->SetDurability(newdur);
						}
					}
				}
				else
				{
					uint32 maxdur = pItem->GetDurabilityMax();
					uint32 olddur = pItem->GetDurability();
					uint32 newdur = (olddur) - (damage);

					if(newdur < 0)
						newdur = 0;

					if( newdur > maxdur )
						newdur = maxdur;

					// Apply / Disapply enchantements from this item
					pItem->SetDurability(newdur);
					if( newdur == 0 && olddur > 0 )
						p_caster->ApplyItemMods( pItem, static_cast<uint16>( k ), false );
					else if( newdur > 0 && olddur == 0 )
						p_caster->ApplyItemMods( pItem, static_cast<uint16>( k ), true );
				}
			}
		}
        return;
    }

    // invalid slot value
    if(slot >= INVENTORY_SLOT_BAG_END)
        return;

	pItem = p_caster->GetItemInterface()->GetInventoryItem( slot );
	if( pItem )
	{
		uint32 maxdur = pItem->GetDurabilityMax();
		uint32 olddur = pItem->GetDurability();
		uint32 newdur = (olddur) - (damage);

		if(newdur < 0)
			newdur = 0;

		if( newdur > maxdur )
			newdur = maxdur;

		pItem->SetDurability(newdur);

		// Apply / Disapply enchantements from this item
		if( newdur == 0 && olddur > 0 ) 
			p_caster->ApplyItemMods( pItem, slot, false );
		else if( newdur > 0 && olddur == 0 )
			p_caster->ApplyItemMods( pItem, slot, true );
	}
}

void Spell::SpellEffectDurabilityDamagePCT(uint32 i)
{
    if(!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    int32 slot = GetProto()->EffectMiscValue[i];

	Item * pItem;
	Container * pContainer;
	uint32 j, k;

    // FIXME: some spells effects have value -1/-2
    // Possibly its mean -1 all player equipped items and -2 all items
    if(slot < 0)
    {
		for( k = 0; k < MAX_INVENTORY_SLOT; k++ )
		{
			pItem = p_caster->GetItemInterface()->GetInventoryItem( static_cast<uint16>( k ) );
			if( pItem != NULL )
			{
				if( pItem->IsContainer() )
				{
					pContainer = static_cast<Container*>( pItem );
					for( j = 0; j < pContainer->GetProto()->ContainerSlots; ++j )
					{
						pItem = pContainer->GetItem( static_cast<uint16>( j ) );
						if( pItem != NULL )
						{
							uint32 maxdur = pItem->GetDurabilityMax();
							uint32 olddur = pItem->GetDurability();
							uint32 newdur = (olddur - (uint32)(maxdur * (damage/100.0)));

							if(newdur < 0)
								newdur = 0;

							if( newdur > maxdur )
								newdur = maxdur;

							pItem->SetDurability(newdur);
						}
					}
				}
				else
				{
					uint32 maxdur = pItem->GetDurabilityMax();
					uint32 olddur = pItem->GetDurability();
					uint32 newdur = (olddur - (uint32)(maxdur * (damage/100.0)));

					if(newdur < 0)
						newdur = 0;

					if( newdur > maxdur )
						newdur = maxdur;

					// Apply / Disapply enchantements from this item
					pItem->SetDurability(newdur);
					if( newdur == 0 && olddur > 0 )
						p_caster->ApplyItemMods( pItem, static_cast<uint16>( k ), false );
					else if( newdur > 0 && olddur == 0 )
						p_caster->ApplyItemMods( pItem, static_cast<uint16>( k ), true );
				}
			}
		}
        return;
    }

    // invalid slot value
    if(slot >= INVENTORY_SLOT_BAG_END)
        return;

    if(damage <= 0)
        return;

	pItem = p_caster->GetItemInterface()->GetInventoryItem( slot );
	if( pItem )
	{
		uint32 maxdur = pItem->GetDurabilityMax();
		uint32 olddur = pItem->GetDurability();
		uint32 newdur = (olddur - (uint32)(maxdur * (damage/100.0)));

		if(newdur < 0)
			newdur = 0;

		if( newdur > maxdur )
			newdur = maxdur;

		pItem->SetDurability(newdur);

		// Apply / Disapply enchantements from this item
		if( newdur == 0 && olddur > 0 ) 
			p_caster->ApplyItemMods( pItem, slot, false );
		else if( newdur > 0 && olddur == 0 )
			p_caster->ApplyItemMods( pItem, slot, true );
	}
}