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

void WorldSession::HandleLearnTalentOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld())
		return;
	uint32 talent_id, requested_rank, unk;	
	recv_data >> talent_id >> requested_rank >> unk;

	
	unsigned int i;
	if (requested_rank > 4)
		return;
	
	TalentEntry * talentInfo = dbcTalent.LookupEntryForced(talent_id);
	if(!talentInfo)return;

	uint32 CurTalentPoints = _player->GetUInt32Value(PLAYER_CHARACTER_POINTS1);
	std::map<uint32, uint8> *talents = &_player->m_specs[_player->m_talentActiveSpec].talents;
	uint8 currentRank = 0;
	std::map<uint32, uint8>::iterator itr = talents->find(talent_id);
	if(itr != talents->end())
		currentRank = itr->second + 1;

	if(currentRank >= requested_rank + 1)
		return; // player already knows requested or higher rank for this talent
	

	uint32 RequiredTalentPoints = requested_rank + 1 - currentRank;
	if(CurTalentPoints < RequiredTalentPoints )
		return; // player doesn't have enough points to get this rank for this talent
	
	// Check if it requires another talent
	if (talentInfo->DependsOn > 0)
	{
		TalentEntry *depTalentInfo = NULL;
		depTalentInfo = dbcTalent.LookupEntryForced(talentInfo->DependsOn);
		if (depTalentInfo)
		{
			itr = talents->find(talentInfo->DependsOn);
			if(itr == talents->end())
				return;	// player doesn't have the talent this one depends on
			if(talentInfo->DependsOnRank > itr->second)
				return;	// player doesn't have the talent rank this one depends on
		}
	}

	// Check that the requested talent belongs to a tree from player's class
	uint32 tTree = talentInfo->TalentTree;
	uint32 cl = _player->getClass();

	for(i = 0; i < 3; ++i)
		if(tTree == TalentTreesPerClass[cl][i])
			break;

	if(i == 3)
	{
		// cheater!
		Disconnect();
		return;
	}

	// Find out how many points we have in this field
	uint32 spentPoints = 0;
	if (talentInfo->Row > 0)
	{
		for(itr = talents->begin(); itr != talents->end(); itr++)
		{
			TalentEntry *tmpTalent = dbcTalent.LookupEntryForced(itr->first);
			if (tmpTalent->TalentTree == tTree)
			{
				spentPoints += itr->second + 1;
			}
		}
	}

	uint32 spellid = talentInfo->RankID[requested_rank];
	if( spellid == 0 )
	{
		//OUT_DEBUG("Talent: %u Rank: %u = 0", talent_id, requested_rank);
		return;
	}

	if(spentPoints < (talentInfo->Row * 5))			 // Min points spent
	{
		return;
	}

	(*talents)[talent_id] = requested_rank;
	_player->SetUInt32Value(PLAYER_CHARACTER_POINTS1, CurTalentPoints - RequiredTalentPoints);
	// More cheat death hackage! :)
	if(spellid == 31330)
		_player->m_cheatDeathRank = 3;
	else if(spellid == 31329)
		_player->m_cheatDeathRank = 2;
	else if(spellid == 31328)
		_player->m_cheatDeathRank = 1;	 

	if(requested_rank > 0 )	// remove old rank aura
	{
		uint32 respellid = talentInfo->RankID[currentRank - 1];
		if(respellid)
		{
			_player->RemoveAura(respellid);
		}
	}

	_player->ApplyTalent(spellid);

	_player->smsg_TalentsInfo(false, talent_id, static_cast<uint8>( requested_rank ));
}
/*
void WorldSession::HandleLearnTalentOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) return;
 	 
	uint32 talent_id, requested_rank, unk;
	recv_data >> talent_id >> requested_rank >> unk;

	_player->LearnTalent(talent_id, requested_rank);

	_player->UpdateTalentInspectBuffer();
	_player->smsg_TalentsInfo(true, talent_id, requested_rank);
}*/

void Player::UpdateTalentInspectBuffer()
{
	memset(m_talentInspectBuffer, 0, TALENT_INSPECT_BYTES);

	uint32 talent_tab_pos = 0;
	uint32 talent_max_rank;
	uint32 talent_tab_id;
	uint32 talent_index;
	uint32 rank_index;
	uint32 rank_slot;
	uint32 rank_offset;
	uint32 i;

	for( i = 0; i < 3; ++i )
	{
		talent_tab_id = sWorld.InspectTalentTabPages[getClass()][i];

		for( uint32 j = 0; j < dbcTalent.GetNumRows(); ++j )
		{
			TalentEntry const* talent_info = dbcTalent.LookupRow( j );

			//OUT_DEBUG( "HandleInspectOpcode: i(%i) j(%i)", i, j );

			if( talent_info == NULL )
				continue;

			//OUT_DEBUG( "HandleInspectOpcode: talent_info->TalentTree(%i) talent_tab_id(%i)", talent_info->TalentTree, talent_tab_id );

			if( talent_info->TalentTree != talent_tab_id )
				continue;

			talent_max_rank = 0;
			for( uint32 k = 5; k > 0; --k )
			{
				//OUT_DEBUG( "HandleInspectOpcode: k(%i) RankID(%i) HasSpell(%i) TalentTree(%i) Tab(%i)", k, talent_info->RankID[k - 1], player->HasSpell( talent_info->RankID[k - 1] ), talent_info->TalentTree, talent_tab_id );
				if( talent_info->RankID[k - 1] != 0 && HasSpell( talent_info->RankID[k - 1] ) )
				{
					talent_max_rank = k;
					break;
				}
			}

			//OUT_DEBUG( "HandleInspectOpcode: RankID(%i) talent_max_rank(%i)", talent_info->RankID[talent_max_rank-1], talent_max_rank );

			if( talent_max_rank <= 0 )
				continue;

			talent_index = talent_tab_pos;

			std::map< uint32, uint32 >::iterator itr = sWorld.InspectTalentTabPos.find( talent_info->TalentID );

			if( itr != sWorld.InspectTalentTabPos.end() )
				talent_index += itr->second;
			//else
			//OUT_DEBUG( "HandleInspectOpcode: talent(%i) rank_id(%i) talent_index(%i) talent_tab_pos(%i) rank_index(%i) rank_slot(%i) rank_offset(%i)", talent_info->TalentID, talent_info->RankID[talent_max_rank-1], talent_index, talent_tab_pos, rank_index, rank_slot, rank_offset );

			rank_index = ( uint32( ( talent_index + talent_max_rank - 1 ) / 7 ) ) * 8  + ( uint32( ( talent_index + talent_max_rank - 1 ) % 7 ) );
			rank_slot = rank_index / 8;
			rank_offset = rank_index % 8;

			if( rank_slot < TALENT_INSPECT_BYTES )
			{
				uint32 v = (uint32)m_talentInspectBuffer[rank_slot];
				v |= ( 1 << rank_offset );
				m_talentInspectBuffer[rank_offset] |= v;
			};

		}

		std::map< uint32, uint32 >::iterator itr = sWorld.InspectTalentTabSize.find( talent_tab_id );

		if( itr != sWorld.InspectTalentTabSize.end() )
			talent_tab_pos += itr->second;

	}
}
void WorldSession::HandleUnlearnTalents( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) return;
	uint32 playerGold = GetPlayer()->GetUInt32Value( PLAYER_FIELD_COINAGE );
	uint32 price = GetPlayer()->CalcTalentResetCost(GetPlayer()->GetTalentResetTimes());

	if( playerGold < price ) return;

	GetPlayer()->SetTalentResetTimes(GetPlayer()->GetTalentResetTimes() + 1);
	GetPlayer()->SetUInt32Value( PLAYER_FIELD_COINAGE, playerGold - price );
	GetPlayer()->Reset_Talents();

/*	// Unlearn all talent spells
	WorldPacket data;
	std::list<uint32> *talentproto = GetPlayer()->getTalentproto();

	std::list<uint32>::iterator itr;
	for (itr = talentproto->begin(); itr != talentproto->end(); ++itr)
	{
		GetPlayer()->removeSpell((*itr));

		// Handled in removespell.
		//data.Initialize(SMSG_REMOVED_SPELL);
		//data << (*itr); 
		//SendPacket( &data );
	}
	talentproto->clear();
*/
}
/*void WorldSession::HandleUnlearnTalents( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) return;
	uint32 playerGold = GetPlayer()->GetUInt32Value( PLAYER_FIELD_COINAGE );
	uint32 price = GetPlayer()->CalcTalentResetCost(GetPlayer()->GetTalentResetTimes());

	if( playerGold < price ) return;

	GetPlayer()->SetTalentResetTimes(GetPlayer()->GetTalentResetTimes() + 1);
	GetPlayer()->SetUInt32Value( PLAYER_FIELD_COINAGE, playerGold - price );
	GetPlayer()->Reset_Talents();

	// Unlearn all talent spells
	WorldPacket data;
	std::list<uint32> *talentproto = GetPlayer()->getTalentproto();

	std::list<uint32>::iterator itr;
	for (itr = talentproto->begin(); itr != talentproto->end(); ++itr)
	{
		GetPlayer()->removeSpell((*itr));

		// Handled in removespell.
		//data.Initialize(SMSG_REMOVED_SPELL);
		//data << (*itr); 
		//SendPacket( &data );
	}
	talentproto->clear();

}*/

void WorldSession::HandleUnlearnSkillOpcode(WorldPacket& recv_data)
{
	if(!_player->IsInWorld()) return;
	uint32 skill_line;
	uint32 points_remaining=_player->GetUInt32Value(PLAYER_CHARACTER_POINTS2);
	recv_data >> skill_line;

	// Cheater detection
	// if(!_player->HasSkillLine(skill_line)) return;

	// Remove any spells within that line that the player has
	_player->RemoveSpellsFromLine(skill_line);
	
	// Finally, remove the skill line.
	_player->_RemoveSkillLine(skill_line);

	//added by Zack : This is probably wrong or already made elsewhere : restore skill learnability
	if(points_remaining==_player->GetUInt32Value(PLAYER_CHARACTER_POINTS2))
	{
		//we unlearned a skill so we enable a new one to be learned
		skilllineentry *sk=dbcSkillLine.LookupEntry(skill_line);
		if(!sk)
			return;
		if(sk->type==SKILL_TYPE_PROFESSION && points_remaining<2)
			_player->SetUInt32Value(PLAYER_CHARACTER_POINTS2,points_remaining+1);
	}
}
