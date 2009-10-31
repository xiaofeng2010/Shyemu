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

#ifndef __STDAFX_H
#define __STDAFX_H

#pragma warning( disable : 4146 4244 4355 4390 )

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#define TO_CREATURE(ptr) static_cast<Creature*>(ptr) 
#define TO_PLAYER(ptr) static_cast<Player*>(ptr)
#define TO_OBJECT(ptr) static_cast<Object*>(ptr)
#define TO_UNIT(ptr) static_cast<Unit*>(ptr)
#define TO_PET(ptr) static_cast<Pet*>(ptr)


#include "Definitions.h"

#include <cstring>
#include <cstdlib>
#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
//#include <fstream>

#include "../shyemu-shared/Common.h"
#include "../shyemu-shared/MersenneTwister.h"
#include "../shyemu-shared/WorldPacket.h"
#include "../shyemu-shared/Log.h"
#include "../shyemu-shared/NGLog.h"
#include "../shyemu-shared/ByteBuffer.h"
#include "../shyemu-shared/StackBuffer.h"
#include "../shyemu-shared/Config/ConfigEnv.h"
#include "../shyemu-shared/crc32.h"
#include "../shyemu-shared/LocationVector.h"

#include <zlib.h>

#include "../shyemu-shared/Database/DatabaseEnv.h"
#include "../shyemu-shared/Database/DBCStores.h"
#include "../shyemu-shared/Database/dbcfile.h"

#include <Network/Network.h>

#include "../shyemu-shared/Auth/MD5.h"
#include "../shyemu-shared/Auth/BigNumber.h"
#include "../shyemu-shared/Auth/Sha1.h"
#include "../shyemu-shared/Auth/WowCrypt.h"
#include "../shyemu-shared/CrashHandler.h"
#include "../shyemu-shared/FastQueue.h"
#include "../shyemu-shared/CircularQueue.h"
#include "../shyemu-shared/Threading/RWLock.h"
#include "../shyemu-shared/Threading/Condition.h"
#include "../shyemu-shared/shyemu_getopt.h"

#ifdef WIN32
#include "printStackTrace.h"
//#include "StackTrace.h"
//#include "MapFile.h"
#endif

#include "UpdateFields.h"
#include "UpdateMask.h"
#include "Opcodes.h"

#include "Packets.h"

#include "../shyemu-shared/CallBack.h"
#include "WordFilter.h"
#include "EventMgr.h"
#include "EventableObject.h"
#include "Object.h"
#include "LootMgr.h"
#include "Unit.h"

#ifdef ENABLE_ACHIEVEMENTS
#include "AchievementMgr.h"
#endif
#include "AddonMgr.h"
#include "AIInterface.h"
#include "AreaTrigger.h"
#include "BattlegroundMgr.h"
#include "AlteracValley.h"
#include "ArathiBasin.h"
#include "EyeOfTheStorm.h"
#include "WorldState.h"
#include "CellHandler.h"
#include "Chat.h"
#include "Corpse.h"
#include "Quest.h"
#include "QuestMgr.h"
#include "Creature.h"
#include "DynamicObject.h"
#include "GameObject.h"
#include "Group.h"
#include "Guild.h"
#include "HonorHandler.h"
#include "ItemPrototype.h"
#include "Item.h"
#include "Container.h"
#include "AuctionHouse.h"
#include "AuctionMgr.h"
#include "LfgMgr.h"
#include "MailSystem.h"
#include "Map.h"
#include "MapCell.h"
#include "TerrainMgr.h"
#include "MiscHandler.h"
#include "NameTables.h"
#include "NPCHandler.h"
#include "Pet.h"
#include "WorldSocket.h"
#include "WorldSession.h"
#include "MapMgr.h"
#include "MapScriptInterface.h"
#include "Player.h"
#include "faction.h"
#include "Skill.h"
#include "SkillNameMgr.h"
#include "SpellNameHashes.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "TaxiMgr.h"
#include "TransporterHandler.h"
#include "StrandOfTheAncient.h"
#include "WarsongGulch.h"
#include "WeatherMgr.h"
#include "World.h"
#include "ItemInterface.h"
#include "Stats.h"
#include "WorldCreator.h"
#include "ObjectContainer.h"
#include "Vehicle.h"


#include "ObjectMgr.h"

#include "CThreads.h"
#include "ScriptMgr.h"

#include "Channel.h"
#include "ChannelMgr.h"
#include "ArenaTeam.h"
#include "Arenas.h"

#include "LogonCommClient.h"
#include "LogonCommHandler.h"
#include "MainServerDefines.h"
#include "WorldRunnable.h"

#include "../shyemu-shared/Storage.h"
#include "ObjectStorage.h"
#include "DatabaseCleaner.h"
#include "DayWatcherThread.h"
#include "CommonScheduleThread.h"
#include "VoiceChatHandler.h"
#include "LocalizationMgr.h"

#include "CollideInterface.h"

#include "Master.h"
#include "BaseConsole.h"
#include "CConsole.h"
//#define COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS 1
#include "SpeedDetector.h"
//#define PVP_REALM_MEANS_CONSTANT_PVP
#include "BufferPools/BufferPools.h"
#include "ProcCondHandler.h"
#endif


#ifndef WIN32
#include "UnixMetric.h"
#endif
