/*
 * shyemu MMORPG Server
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

#pragma once

#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
//#include <fstream>

#include "Common.h"
#include <Network/Network.h>

#include "../shyemu-shared/Log.h"
#include "../shyemu-shared/Util.h"
#include "../shyemu-shared/ByteBuffer.h"
#include "../shyemu-shared/Config/ConfigEnv.h"
#include <zlib.h>

#include "../shyemu-shared/Database/DatabaseEnv.h"
#include "../shyemu-shared/Database/DBCStores.h"
#include "../shyemu-shared/Database/dbcfile.h"

#include "../shyemu-shared/Auth/BigNumber.h"
#include "../shyemu-shared/Auth/Sha1.h"
#include "../shyemu-shared/Auth/WowCrypt.h"
#include "../shyemu-shared/CrashHandler.h"

#include "LogonOpcodes.h"
#include "../shyemu-logonserver/Main.h"
#include "../shyemu-world/NameTables.h"
#include "AccountCache.h"
#include "PeriodicFunctionCall_Thread.h"
#include "../shyemu-logonserver/AutoPatcher.h"
#include "../shyemu-logonserver/AuthSocket.h"
#include "../shyemu-logonserver/AuthStructs.h"
//#include "../shyemu-logonserver/LogonOpcodes.h"
#include "../shyemu-logonserver/LogonCommServer.h"
#include "../shyemu-logonserver/LogonConsole.h"
#include "../shyemu-shared/WorldPacket.h"

// database decl
extern Database* sLogonSQL;
