-- MySQL dump 10.11
--
-- Host: localhost    Database: shyemu_char
-- ------------------------------------------------------
-- Server version	5.1.37-community

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account_data`
--

DROP TABLE IF EXISTS `account_data`;
CREATE TABLE `account_data` (
  `acct` int(30) NOT NULL,
  `uiconfig0` blob,
  `uiconfig1` blob,
  `uiconfig2` blob,
  `uiconfig3` blob,
  `uiconfig4` blob,
  `uiconfig5` blob,
  `uiconfig6` blob,
  `uiconfig7` blob,
  `uiconfig8` blob,
  PRIMARY KEY (`acct`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `account_data`
--

LOCK TABLES `account_data` WRITE;
/*!40000 ALTER TABLE `account_data` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_forced_permissions`
--

DROP TABLE IF EXISTS `account_forced_permissions`;
CREATE TABLE `account_forced_permissions` (
  `login` varchar(50) NOT NULL,
  `permissions` varchar(100) NOT NULL,
  PRIMARY KEY (`login`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `account_forced_permissions`
--

LOCK TABLES `account_forced_permissions` WRITE;
/*!40000 ALTER TABLE `account_forced_permissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_forced_permissions` ENABLE KEYS */;
UNLOCK TABLES;


--
-- Table structure for table `arenateams`
--

DROP TABLE IF EXISTS `arenateams`;
CREATE TABLE `arenateams` (
  `id` int(30) NOT NULL,
  `type` int(30) NOT NULL,
  `leader` int(30) NOT NULL,
  `name` varchar(150) NOT NULL,
  `emblemstyle` int(40) NOT NULL,
  `emblemcolour` bigint(40) NOT NULL,
  `borderstyle` int(40) NOT NULL,
  `bordercolour` bigint(40) NOT NULL,
  `backgroundcolour` bigint(40) NOT NULL,
  `rating` int(30) NOT NULL,
  `data` varchar(150) NOT NULL,
  `ranking` int(30) NOT NULL,
  `player_data1` varchar(60) NOT NULL,
  `player_data2` varchar(60) NOT NULL,
  `player_data3` varchar(60) NOT NULL,
  `player_data4` varchar(60) NOT NULL,
  `player_data5` varchar(60) NOT NULL,
  `player_data6` varchar(60) NOT NULL,
  `player_data7` varchar(60) NOT NULL,
  `player_data8` varchar(60) NOT NULL,
  `player_data9` varchar(60) NOT NULL,
  `player_data10` varchar(60) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `arenateams`
--

LOCK TABLES `arenateams` WRITE;
/*!40000 ALTER TABLE `arenateams` DISABLE KEYS */;
/*!40000 ALTER TABLE `arenateams` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auctions`
--

DROP TABLE IF EXISTS `auctions`;
CREATE TABLE `auctions` (
  `auctionId` int(32) NOT NULL AUTO_INCREMENT,
  `auctionhouse` int(32) DEFAULT NULL,
  `item` bigint(10) DEFAULT NULL,
  `owner` bigint(10) DEFAULT NULL,
  `buyout` int(32) DEFAULT NULL,
  `time` int(32) DEFAULT NULL,
  `bidder` bigint(10) DEFAULT NULL,
  `bid` int(32) DEFAULT NULL,
  `deposit` int(32) DEFAULT NULL,
  PRIMARY KEY (`auctionId`),
  KEY `b` (`auctionhouse`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `auctions`
--

LOCK TABLES `auctions` WRITE;
/*!40000 ALTER TABLE `auctions` DISABLE KEYS */;
/*!40000 ALTER TABLE `auctions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `banned_names`
--

DROP TABLE IF EXISTS `banned_names`;
CREATE TABLE `banned_names` (
  `name` varchar(30) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `banned_names`
--

LOCK TABLES `banned_names` WRITE;
/*!40000 ALTER TABLE `banned_names` DISABLE KEYS */;
/*!40000 ALTER TABLE `banned_names` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `character_achievement`
--

DROP TABLE IF EXISTS `character_achievement`;
CREATE TABLE `character_achievement` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `achievement` int(10) unsigned NOT NULL DEFAULT '0',
  `date` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`,`achievement`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `character_achievement`
--

LOCK TABLES `character_achievement` WRITE;
/*!40000 ALTER TABLE `character_achievement` DISABLE KEYS */;
/*!40000 ALTER TABLE `character_achievement` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `character_achievement_progress`
--

DROP TABLE IF EXISTS `character_achievement_progress`;
CREATE TABLE `character_achievement_progress` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `criteria` int(10) unsigned NOT NULL DEFAULT '0',
  `counter` int(10) unsigned DEFAULT NULL,
  `date` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`,`criteria`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `character_achievement_progress`
--

LOCK TABLES `character_achievement_progress` WRITE;
/*!40000 ALTER TABLE `character_achievement_progress` DISABLE KEYS */;
/*!40000 ALTER TABLE `character_achievement_progress` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `characters`
--

DROP TABLE IF EXISTS `characters`;
CREATE TABLE `characters` (
  `guid` int(6) unsigned NOT NULL DEFAULT '0',
  `acct` int(20) unsigned NOT NULL DEFAULT '0',
  `name` varchar(21) NOT NULL DEFAULT '',
  `race` smallint(3) NOT NULL,
  `class` smallint(3) NOT NULL,
  `gender` tinyint(1) NOT NULL,
  `custom_faction` int(30) NOT NULL DEFAULT '0',
  `level` int(3) NOT NULL,
  `xp` int(30) NOT NULL,
  `active_cheats` int(10) unsigned NOT NULL DEFAULT '0',
  `exploration_data` longtext NOT NULL,
  `skills` longtext NOT NULL,
  `watched_faction_index` bigint(40) NOT NULL,
  `selected_pvp_title` int(30) NOT NULL,
  `available_pvp_titles` bigint(10) unsigned NOT NULL DEFAULT '0',
  `available_pvp_titles1` bigint(10) NOT NULL,
  `gold` int(30) NOT NULL,
  `ammo_id` int(30) NOT NULL,
  `available_prof_points` int(30) NOT NULL,
  `total_talent_points` int(30) NOT NULL,
  `current_hp` int(30) NOT NULL,
  `current_power` int(30) NOT NULL,
  `pvprank` int(30) NOT NULL,
  `bytes` int(30) NOT NULL,
  `bytes2` int(30) NOT NULL,
  `player_flags` int(30) NOT NULL,
  `player_bytes` int(30) NOT NULL,
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `mapId` int(8) unsigned NOT NULL DEFAULT '0',
  `zoneId` int(8) unsigned NOT NULL DEFAULT '0',
  `taximask` longtext NOT NULL,
  `banned` int(40) unsigned NOT NULL DEFAULT '0',
  `banReason` varchar(255) NOT NULL,
  `timestamp` int(30) DEFAULT NULL,
  `online` int(11) DEFAULT NULL,
  `bindpositionX` float NOT NULL DEFAULT '0',
  `bindpositionY` float NOT NULL DEFAULT '0',
  `bindpositionZ` float NOT NULL DEFAULT '0',
  `bindmapId` int(8) unsigned NOT NULL DEFAULT '0',
  `bindzoneId` int(8) unsigned NOT NULL DEFAULT '0',
  `isResting` int(3) NOT NULL DEFAULT '0',
  `restState` int(5) NOT NULL DEFAULT '0',
  `restTime` int(5) NOT NULL DEFAULT '0',
  `playedtime` text NOT NULL,
  `deathstate` int(5) NOT NULL DEFAULT '0',
  `TalentResetTimes` int(5) NOT NULL DEFAULT '0',
  `first_login` tinyint(1) NOT NULL DEFAULT '0',
  `forced_rename_pending` tinyint(1) NOT NULL DEFAULT '0',
  `arenaPoints` int(10) NOT NULL,
  `totalstableslots` int(10) unsigned NOT NULL DEFAULT '0',
  `instance_id` int(10) NOT NULL,
  `entrypointmap` int(10) NOT NULL,
  `entrypointx` float NOT NULL,
  `entrypointy` float NOT NULL,
  `entrypointz` float NOT NULL,
  `entrypointo` float NOT NULL,
  `entrypointinstance` int(10) NOT NULL,
  `taxi_path` int(10) NOT NULL,
  `taxi_lastnode` int(10) NOT NULL,
  `taxi_mountid` int(10) NOT NULL,
  `transporter` int(10) NOT NULL,
  `transporter_xdiff` float NOT NULL,
  `transporter_ydiff` float NOT NULL,
  `transporter_zdiff` float NOT NULL,
  `deleted_spells` longtext NOT NULL,
  `reputation` longtext NOT NULL,
  `auras` longtext NOT NULL,
  `finished_quests` longtext NOT NULL,
  `finisheddailies` longtext NOT NULL,
  `honorRolloverTime` int(30) NOT NULL DEFAULT '0',
  `killsToday` int(10) NOT NULL DEFAULT '0',
  `killsYesterday` int(10) NOT NULL DEFAULT '0',
  `killsLifeTime` int(10) NOT NULL DEFAULT '0',
  `honorToday` int(10) NOT NULL DEFAULT '0',
  `honorYesterday` int(10) NOT NULL DEFAULT '0',
  `honorPoints` int(10) NOT NULL DEFAULT '0',
  `difficulty` int(4) NOT NULL DEFAULT '0',
  `active_spec` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `specs_count` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `drunkValue` int(30) NOT NULL DEFAULT '0',
  `phase` int(10) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`guid`),
  KEY `acct` (`acct`),
  KEY `name` (`name`),
  KEY `b` (`banned`),
  KEY `c` (`online`),
  KEY `d` (`forced_rename_pending`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `characters`
--

LOCK TABLES `characters` WRITE;
/*!40000 ALTER TABLE `characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `characters_insert_queue`
--

DROP TABLE IF EXISTS `characters_insert_queue`;
CREATE TABLE `characters_insert_queue` (
  `insert_temp_guid` int(10) unsigned NOT NULL DEFAULT '0',
  `acct` int(10) unsigned NOT NULL DEFAULT '0',
  `name` varchar(21) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `race` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `class` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `gender` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `custom_faction` int(30) NOT NULL DEFAULT '0',
  `level` int(10) unsigned NOT NULL DEFAULT '0',
  `xp` int(10) unsigned NOT NULL DEFAULT '0',
  `exploration_data` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `skills` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `watched_faction_index` int(10) unsigned NOT NULL DEFAULT '0',
  `selected_pvp_title` int(10) unsigned NOT NULL DEFAULT '0',
  `available_pvp_titles` int(10) unsigned NOT NULL DEFAULT '0',
  `gold` int(10) unsigned NOT NULL DEFAULT '0',
  `ammo_id` int(10) unsigned NOT NULL DEFAULT '0',
  `available_prof_points` int(10) unsigned NOT NULL DEFAULT '0',
  `available_talent_points` int(10) unsigned NOT NULL DEFAULT '0',
  `current_hp` int(10) unsigned NOT NULL DEFAULT '0',
  `current_power` int(10) unsigned NOT NULL DEFAULT '0',
  `pvprank` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `bytes` int(10) unsigned NOT NULL DEFAULT '0',
  `bytes2` int(10) unsigned NOT NULL DEFAULT '0',
  `player_flags` int(10) unsigned NOT NULL DEFAULT '0',
  `player_bytes` int(10) unsigned NOT NULL DEFAULT '0',
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `mapId` int(10) unsigned NOT NULL DEFAULT '0',
  `zoneId` int(10) unsigned NOT NULL DEFAULT '0',
  `taximask` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `banned` int(40) NOT NULL,
  `banReason` varchar(50) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `timestamp` int(11) NOT NULL,
  `online` int(11) DEFAULT NULL,
  `bindpositionX` float NOT NULL DEFAULT '0',
  `bindpositionY` float NOT NULL DEFAULT '0',
  `bindpositionZ` float NOT NULL DEFAULT '0',
  `bindmapId` int(10) unsigned NOT NULL DEFAULT '0',
  `bindzoneId` int(10) unsigned NOT NULL DEFAULT '0',
  `isResting` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `restState` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `restTime` int(10) unsigned NOT NULL DEFAULT '0',
  `playedtime` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `deathstate` int(10) unsigned NOT NULL DEFAULT '0',
  `TalentResetTimes` int(10) unsigned NOT NULL DEFAULT '0',
  `first_login` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `forced_rename_pending` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `publicNote` varchar(32) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `officerNote` varchar(32) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `guildid` int(10) unsigned NOT NULL DEFAULT '0',
  `guildRank` int(10) unsigned NOT NULL DEFAULT '0',
  `arenaPoints` int(10) NOT NULL,
  `totalstableslots` int(10) unsigned NOT NULL DEFAULT '0',
  `instance_id` int(10) unsigned NOT NULL DEFAULT '0',
  `entrypointmap` int(10) unsigned NOT NULL DEFAULT '0',
  `entrypointx` float NOT NULL DEFAULT '0',
  `entrypointy` float NOT NULL DEFAULT '0',
  `entrypointz` float NOT NULL DEFAULT '0',
  `entrypointo` float NOT NULL DEFAULT '0',
  `entrypointinstance` int(10) unsigned NOT NULL DEFAULT '0',
  `taxi_path` int(10) unsigned NOT NULL DEFAULT '0',
  `taxi_lastnode` int(10) unsigned NOT NULL DEFAULT '0',
  `taxi_mountid` int(10) unsigned NOT NULL DEFAULT '0',
  `transporter` int(10) unsigned NOT NULL DEFAULT '0',
  `transporter_xdiff` float NOT NULL DEFAULT '0',
  `transporter_ydiff` float NOT NULL DEFAULT '0',
  `transporter_zdiff` float NOT NULL DEFAULT '0',
  `spells` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `deleted_spells` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `reputation` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `actions` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `auras` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `finished_quests` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `honorPointsToAdd` int(10) NOT NULL,
  `killsToday` int(10) unsigned NOT NULL DEFAULT '0',
  `killsYesterday` int(10) unsigned NOT NULL DEFAULT '0',
  `killsLifeTime` int(10) unsigned NOT NULL DEFAULT '0',
  `honorToday` int(10) unsigned NOT NULL DEFAULT '0',
  `honorYesterday` int(10) unsigned NOT NULL DEFAULT '0',
  `honorPoints` int(10) unsigned NOT NULL DEFAULT '0',
  `difficulty` int(10) unsigned NOT NULL DEFAULT '0',
  UNIQUE KEY `guid` (`insert_temp_guid`),
  KEY `acct` (`acct`),
  KEY `guildid` (`guildid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `characters_insert_queue`
--

LOCK TABLES `characters_insert_queue` WRITE;
/*!40000 ALTER TABLE `characters_insert_queue` DISABLE KEYS */;
/*!40000 ALTER TABLE `characters_insert_queue` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `charters`
--

DROP TABLE IF EXISTS `charters`;
CREATE TABLE `charters` (
  `charterId` int(30) NOT NULL,
  `charterType` int(30) NOT NULL DEFAULT '0',
  `leaderGuid` int(20) unsigned NOT NULL DEFAULT '0',
  `guildName` varchar(32) NOT NULL DEFAULT '',
  `itemGuid` bigint(40) unsigned NOT NULL DEFAULT '0',
  `signer1` int(10) unsigned NOT NULL DEFAULT '0',
  `signer2` int(10) unsigned NOT NULL DEFAULT '0',
  `signer3` int(10) unsigned NOT NULL DEFAULT '0',
  `signer4` int(10) unsigned NOT NULL DEFAULT '0',
  `signer5` int(10) unsigned NOT NULL DEFAULT '0',
  `signer6` int(10) unsigned NOT NULL DEFAULT '0',
  `signer7` int(10) unsigned NOT NULL DEFAULT '0',
  `signer8` int(10) unsigned NOT NULL DEFAULT '0',
  `signer9` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`charterId`),
  UNIQUE KEY `leaderGuid` (`leaderGuid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `charters`
--

LOCK TABLES `charters` WRITE;
/*!40000 ALTER TABLE `charters` DISABLE KEYS */;
/*!40000 ALTER TABLE `charters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `clientaddons`
--

DROP TABLE IF EXISTS `clientaddons`;
CREATE TABLE `clientaddons` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `crc` bigint(50) DEFAULT NULL,
  `banned` int(1) NOT NULL DEFAULT '0',
  `showinlist` int(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `index` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `clientaddons`
--

LOCK TABLES `clientaddons` WRITE;
/*!40000 ALTER TABLE `clientaddons` DISABLE KEYS */;
/*!40000 ALTER TABLE `clientaddons` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `command_overrides`
--

DROP TABLE IF EXISTS `command_overrides`;
CREATE TABLE `command_overrides` (
  `command_name` varchar(100) NOT NULL,
  `access_level` varchar(10) NOT NULL,
  PRIMARY KEY (`command_name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `command_overrides`
--

LOCK TABLES `command_overrides` WRITE;
/*!40000 ALTER TABLE `command_overrides` DISABLE KEYS */;
/*!40000 ALTER TABLE `command_overrides` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `corpses`
--

DROP TABLE IF EXISTS `corpses`;
CREATE TABLE `corpses` (
  `guid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `zoneId` int(11) NOT NULL DEFAULT '0',
  `mapId` int(11) NOT NULL DEFAULT '0',
  `instanceId` int(11) NOT NULL DEFAULT '0',
  `data` longtext NOT NULL,
  PRIMARY KEY (`guid`),
  KEY `b` (`instanceId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `corpses`
--

LOCK TABLES `corpses` WRITE;
/*!40000 ALTER TABLE `corpses` DISABLE KEYS */;
/*!40000 ALTER TABLE `corpses` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gm_tickets`
--

DROP TABLE IF EXISTS `gm_tickets`;
CREATE TABLE `gm_tickets` (
  `guid` int(11) NOT NULL,
  `playerGuid` int(11) NOT NULL,
  `name` varchar(200) NOT NULL DEFAULT '',
  `level` int(6) NOT NULL DEFAULT '0',
  `map` int(11) NOT NULL DEFAULT '0',
  `posX` float NOT NULL DEFAULT '0',
  `posY` float NOT NULL DEFAULT '0',
  `posZ` float NOT NULL DEFAULT '0',
  `message` text NOT NULL,
  `timestamp` text,
  `deleted` bit(1) NOT NULL DEFAULT b'0',
  `assignedto` int(11) NOT NULL DEFAULT '0',
  `comment` text NOT NULL,
  UNIQUE KEY `guid` (`guid`),
  UNIQUE KEY `guid_2` (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `gm_tickets`
--

LOCK TABLES `gm_tickets` WRITE;
/*!40000 ALTER TABLE `gm_tickets` DISABLE KEYS */;
/*!40000 ALTER TABLE `gm_tickets` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `groups`
--

DROP TABLE IF EXISTS `groups`;
CREATE TABLE `groups` (
  `group_id` int(30) NOT NULL,
  `group_type` tinyint(2) NOT NULL,
  `subgroup_count` tinyint(2) NOT NULL,
  `loot_method` tinyint(2) NOT NULL,
  `loot_threshold` tinyint(2) NOT NULL,
  `difficulty` int(30) NOT NULL DEFAULT '0',
  `assistant_leader` int(30) NOT NULL DEFAULT '0',
  `main_tank` int(30) NOT NULL DEFAULT '0',
  `main_assist` int(30) NOT NULL DEFAULT '0',
  `group1member1` int(50) NOT NULL,
  `group1member2` int(50) NOT NULL,
  `group1member3` int(50) NOT NULL,
  `group1member4` int(50) NOT NULL,
  `group1member5` int(50) NOT NULL,
  `group2member1` int(50) NOT NULL,
  `group2member2` int(50) NOT NULL,
  `group2member3` int(50) NOT NULL,
  `group2member4` int(50) NOT NULL,
  `group2member5` int(50) NOT NULL,
  `group3member1` int(50) NOT NULL,
  `group3member2` int(50) NOT NULL,
  `group3member3` int(50) NOT NULL,
  `group3member4` int(50) NOT NULL,
  `group3member5` int(50) NOT NULL,
  `group4member1` int(50) NOT NULL,
  `group4member2` int(50) NOT NULL,
  `group4member3` int(50) NOT NULL,
  `group4member4` int(50) NOT NULL,
  `group4member5` int(50) NOT NULL,
  `group5member1` int(50) NOT NULL,
  `group5member2` int(50) NOT NULL,
  `group5member3` int(50) NOT NULL,
  `group5member4` int(50) NOT NULL,
  `group5member5` int(50) NOT NULL,
  `group6member1` int(50) NOT NULL,
  `group6member2` int(50) NOT NULL,
  `group6member3` int(50) NOT NULL,
  `group6member4` int(50) NOT NULL,
  `group6member5` int(50) NOT NULL,
  `group7member1` int(50) NOT NULL,
  `group7member2` int(50) NOT NULL,
  `group7member3` int(50) NOT NULL,
  `group7member4` int(50) NOT NULL,
  `group7member5` int(50) NOT NULL,
  `group8member1` int(50) NOT NULL,
  `group8member2` int(50) NOT NULL,
  `group8member3` int(50) NOT NULL,
  `group8member4` int(50) NOT NULL,
  `group8member5` int(50) NOT NULL,
  `timestamp` int(30) NOT NULL,
  `instanceids` text NOT NULL,
  PRIMARY KEY (`group_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `groups`
--

LOCK TABLES `groups` WRITE;
/*!40000 ALTER TABLE `groups` DISABLE KEYS */;
/*!40000 ALTER TABLE `groups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `guild_bankitems`
--

DROP TABLE IF EXISTS `guild_bankitems`;
CREATE TABLE `guild_bankitems` (
  `guildId` int(30) NOT NULL,
  `tabId` int(30) NOT NULL,
  `slotId` int(30) NOT NULL,
  `itemGuid` int(30) NOT NULL,
  PRIMARY KEY (`guildId`,`tabId`,`slotId`),
  KEY `a` (`guildId`),
  KEY `b` (`tabId`),
  KEY `c` (`slotId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `guild_bankitems`
--

LOCK TABLES `guild_bankitems` WRITE;
/*!40000 ALTER TABLE `guild_bankitems` DISABLE KEYS */;
/*!40000 ALTER TABLE `guild_bankitems` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `guild_banklogs`
--

DROP TABLE IF EXISTS `guild_banklogs`;
CREATE TABLE `guild_banklogs` (
  `log_id` int(30) NOT NULL,
  `guildid` int(30) NOT NULL,
  `tabid` int(30) NOT NULL COMMENT 'tab 6 is money logs',
  `action` int(5) NOT NULL,
  `player_guid` int(30) NOT NULL,
  `item_entry` int(30) NOT NULL,
  `stack_count` int(30) NOT NULL,
  `timestamp` int(30) NOT NULL,
  PRIMARY KEY (`log_id`,`guildid`),
  KEY `a` (`guildid`),
  KEY `b` (`tabid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `guild_banklogs`
--

LOCK TABLES `guild_banklogs` WRITE;
/*!40000 ALTER TABLE `guild_banklogs` DISABLE KEYS */;
/*!40000 ALTER TABLE `guild_banklogs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `guild_banktabs`
--

DROP TABLE IF EXISTS `guild_banktabs`;
CREATE TABLE `guild_banktabs` (
  `guildId` int(30) NOT NULL,
  `tabId` int(30) NOT NULL,
  `tabName` varchar(200) NOT NULL,
  `tabIcon` varchar(200) NOT NULL,
  PRIMARY KEY (`guildId`,`tabId`),
  KEY `a` (`guildId`),
  KEY `b` (`tabId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `guild_banktabs`
--

LOCK TABLES `guild_banktabs` WRITE;
/*!40000 ALTER TABLE `guild_banktabs` DISABLE KEYS */;
/*!40000 ALTER TABLE `guild_banktabs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `guild_data`
--

DROP TABLE IF EXISTS `guild_data`;
CREATE TABLE `guild_data` (
  `guildid` int(30) NOT NULL,
  `playerid` int(30) NOT NULL,
  `guildRank` int(30) NOT NULL,
  `publicNote` varchar(300) NOT NULL,
  `officerNote` varchar(300) NOT NULL,
  `lastWithdrawReset` int(30) NOT NULL DEFAULT '0',
  `withdrawlsSinceLastReset` int(30) NOT NULL DEFAULT '0',
  `lastItemWithdrawReset0` int(30) NOT NULL DEFAULT '0',
  `itemWithdrawlsSinceLastReset0` int(30) NOT NULL DEFAULT '0',
  `lastItemWithdrawReset1` int(30) NOT NULL,
  `itemWithdrawlsSinceLastReset1` int(30) NOT NULL,
  `lastItemWithdrawReset2` int(30) NOT NULL,
  `itemWithdrawlsSinceLastReset2` int(30) NOT NULL,
  `lastItemWithdrawReset3` int(30) NOT NULL,
  `itemWithdrawlsSinceLastReset3` int(30) NOT NULL,
  `lastItemWithdrawReset4` int(30) NOT NULL,
  `itemWithdrawlsSinceLastReset4` int(30) NOT NULL,
  `lastItemWithdrawReset5` int(30) NOT NULL,
  `itemWithdrawlsSinceLastReset5` int(30) NOT NULL,
  KEY `a` (`guildid`),
  KEY `b` (`playerid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `guild_data`
--

LOCK TABLES `guild_data` WRITE;
/*!40000 ALTER TABLE `guild_data` DISABLE KEYS */;
/*!40000 ALTER TABLE `guild_data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `guild_logs`
--

DROP TABLE IF EXISTS `guild_logs`;
CREATE TABLE `guild_logs` (
  `log_id` int(30) NOT NULL,
  `guildid` int(30) NOT NULL,
  `timestamp` int(30) NOT NULL,
  `event_type` int(30) NOT NULL,
  `misc1` int(30) NOT NULL,
  `misc2` int(30) NOT NULL,
  `misc3` int(30) NOT NULL,
  PRIMARY KEY (`log_id`,`guildid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `guild_logs`
--

LOCK TABLES `guild_logs` WRITE;
/*!40000 ALTER TABLE `guild_logs` DISABLE KEYS */;
/*!40000 ALTER TABLE `guild_logs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `guild_ranks`
--

DROP TABLE IF EXISTS `guild_ranks`;
CREATE TABLE `guild_ranks` (
  `guildId` int(6) unsigned NOT NULL DEFAULT '0',
  `rankId` int(1) NOT NULL DEFAULT '0',
  `rankName` varchar(255) NOT NULL DEFAULT '',
  `rankRights` int(3) unsigned NOT NULL DEFAULT '0',
  `goldLimitPerDay` int(30) NOT NULL DEFAULT '0',
  `bankTabFlags0` int(30) NOT NULL DEFAULT '0',
  `itemStacksPerDay0` int(30) NOT NULL DEFAULT '0',
  `bankTabFlags1` int(30) NOT NULL DEFAULT '0',
  `itemStacksPerDay1` int(30) NOT NULL DEFAULT '0',
  `bankTabFlags2` int(30) NOT NULL DEFAULT '0',
  `itemStacksPerDay2` int(30) NOT NULL DEFAULT '0',
  `bankTabFlags3` int(30) NOT NULL DEFAULT '0',
  `itemStacksPerDay3` int(30) NOT NULL DEFAULT '0',
  `bankTabFlags4` int(30) NOT NULL DEFAULT '0',
  `itemStacksPerDay4` int(30) NOT NULL DEFAULT '0',
  `bankTabFlags5` int(30) NOT NULL DEFAULT '0',
  `itemStacksPerDay5` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`guildId`,`rankId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `guild_ranks`
--

LOCK TABLES `guild_ranks` WRITE;
/*!40000 ALTER TABLE `guild_ranks` DISABLE KEYS */;
/*!40000 ALTER TABLE `guild_ranks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `guilds`
--

DROP TABLE IF EXISTS `guilds`;
CREATE TABLE `guilds` (
  `guildId` bigint(20) NOT NULL AUTO_INCREMENT,
  `guildName` varchar(32) NOT NULL DEFAULT '',
  `leaderGuid` bigint(20) NOT NULL DEFAULT '0',
  `emblemStyle` int(10) NOT NULL DEFAULT '0',
  `emblemColor` int(10) NOT NULL DEFAULT '0',
  `borderStyle` int(10) NOT NULL DEFAULT '0',
  `borderColor` int(10) NOT NULL DEFAULT '0',
  `backgroundColor` int(10) NOT NULL DEFAULT '0',
  `guildInfo` varchar(300) NOT NULL DEFAULT '',
  `motd` varchar(300) NOT NULL DEFAULT '',
  `createdate` int(30) NOT NULL,
  `bankBalance` bigint(30) unsigned NOT NULL,
  PRIMARY KEY (`guildId`),
  UNIQUE KEY `guildId` (`guildId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `guilds`
--

LOCK TABLES `guilds` WRITE;
/*!40000 ALTER TABLE `guilds` DISABLE KEYS */;
/*!40000 ALTER TABLE `guilds` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `instanceids`
--

DROP TABLE IF EXISTS `instanceids`;
CREATE TABLE `instanceids` (
  `playerguid` int(11) unsigned NOT NULL DEFAULT '0',
  `mapid` int(11) unsigned NOT NULL DEFAULT '0',
  `mode` int(11) unsigned NOT NULL DEFAULT '0',
  `instanceid` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`playerguid`,`mapid`,`mode`),
  KEY `ix_instanceid` (`playerguid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Player / InstanceID - Reference Table';

--
-- Dumping data for table `instanceids`
--

LOCK TABLES `instanceids` WRITE;
/*!40000 ALTER TABLE `instanceids` DISABLE KEYS */;
/*!40000 ALTER TABLE `instanceids` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `instances`
--

DROP TABLE IF EXISTS `instances`;
CREATE TABLE `instances` (
  `id` int(30) NOT NULL,
  `mapid` int(30) NOT NULL,
  `creation` int(30) NOT NULL,
  `expiration` int(30) NOT NULL,
  `killed_npc_guids` text NOT NULL,
  `difficulty` int(30) NOT NULL,
  `creator_group` int(30) NOT NULL,
  `creator_guid` int(30) NOT NULL,
  `persistent` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `a` (`mapid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `instances`
--

LOCK TABLES `instances` WRITE;
/*!40000 ALTER TABLE `instances` DISABLE KEYS */;
/*!40000 ALTER TABLE `instances` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mailbox`
--

DROP TABLE IF EXISTS `mailbox`;
CREATE TABLE `mailbox` (
  `message_id` int(30) NOT NULL DEFAULT '0',
  `message_type` int(30) NOT NULL DEFAULT '0',
  `player_guid` int(30) NOT NULL DEFAULT '0',
  `sender_guid` int(30) NOT NULL DEFAULT '0',
  `subject` varchar(255) NOT NULL DEFAULT '',
  `body` longtext NOT NULL,
  `money` int(30) NOT NULL DEFAULT '0',
  `attached_item_guids` varchar(200) NOT NULL DEFAULT '',
  `cod` int(30) NOT NULL DEFAULT '0',
  `stationary` int(30) NOT NULL DEFAULT '0',
  `expiry_time` int(30) NOT NULL DEFAULT '0',
  `delivery_time` int(30) NOT NULL DEFAULT '0',
  `copy_made` int(30) NOT NULL DEFAULT '0',
  `read_flag` int(30) NOT NULL DEFAULT '0',
  `deleted_flag` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`message_id`),
  KEY `b` (`player_guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `mailbox`
--

LOCK TABLES `mailbox` WRITE;
/*!40000 ALTER TABLE `mailbox` DISABLE KEYS */;
/*!40000 ALTER TABLE `mailbox` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mailbox_insert_queue`
--

DROP TABLE IF EXISTS `mailbox_insert_queue`;
CREATE TABLE `mailbox_insert_queue` (
  `sender_guid` int(30) NOT NULL,
  `receiver_guid` int(30) NOT NULL,
  `subject` varchar(200) NOT NULL,
  `body` varchar(500) NOT NULL,
  `stationary` int(30) NOT NULL,
  `money` int(30) NOT NULL,
  `item_id` int(30) NOT NULL,
  `item_stack` int(30) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `mailbox_insert_queue`
--

LOCK TABLES `mailbox_insert_queue` WRITE;
/*!40000 ALTER TABLE `mailbox_insert_queue` DISABLE KEYS */;
/*!40000 ALTER TABLE `mailbox_insert_queue` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playeractionbars`
--

DROP TABLE IF EXISTS `playeractionbars`;
CREATE TABLE `playeractionbars` (
  `guid` int(64) unsigned NOT NULL,
  `spec` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `button` int(11) NOT NULL,
  `action` int(16) unsigned NOT NULL,
  `type` int(10) unsigned NOT NULL,
  `misc` int(10) unsigned NOT NULL,
  PRIMARY KEY (`guid`,`spec`,`button`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `playeractionbars`
--

LOCK TABLES `playeractionbars` WRITE;
/*!40000 ALTER TABLE `playeractionbars` DISABLE KEYS */;
/*!40000 ALTER TABLE `playeractionbars` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playercooldowns`
--

DROP TABLE IF EXISTS `playercooldowns`;
CREATE TABLE `playercooldowns` (
  `player_guid` int(30) NOT NULL,
  `cooldown_type` int(30) NOT NULL COMMENT '0 is spell, 1 is item, 2 is spell category',
  `cooldown_misc` int(30) NOT NULL COMMENT 'spellid/itemid/category',
  `cooldown_expire_time` int(30) NOT NULL COMMENT 'expiring time in unix epoch format',
  `cooldown_spellid` int(30) NOT NULL COMMENT 'spell that cast it',
  `cooldown_itemid` int(30) NOT NULL COMMENT 'item that cast it'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `playercooldowns`
--

LOCK TABLES `playercooldowns` WRITE;
/*!40000 ALTER TABLE `playercooldowns` DISABLE KEYS */;
/*!40000 ALTER TABLE `playercooldowns` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playerglyphs`
--

DROP TABLE IF EXISTS `playerglyphs`;
CREATE TABLE `playerglyphs` (
  `guid` int(10) unsigned NOT NULL,
  `spec` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `glyph1` smallint(5) unsigned DEFAULT NULL,
  `glyph2` smallint(5) unsigned DEFAULT NULL,
  `glyph3` smallint(5) unsigned DEFAULT NULL,
  `glyph4` smallint(5) unsigned DEFAULT NULL,
  `glyph5` smallint(5) unsigned DEFAULT NULL,
  `glyph6` smallint(5) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`,`spec`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `playerglyphs`
--

LOCK TABLES `playerglyphs` WRITE;
/*!40000 ALTER TABLE `playerglyphs` DISABLE KEYS */;
/*!40000 ALTER TABLE `playerglyphs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playeritems`
--

DROP TABLE IF EXISTS `playeritems`;
CREATE TABLE `playeritems` (
  `ownerguid` int(10) unsigned NOT NULL DEFAULT '0',
  `guid` bigint(10) NOT NULL AUTO_INCREMENT,
  `entry` int(10) unsigned NOT NULL DEFAULT '0',
  `wrapped_item_id` int(30) NOT NULL DEFAULT '0',
  `wrapped_creator` int(30) NOT NULL DEFAULT '0',
  `creator` int(10) unsigned NOT NULL DEFAULT '0',
  `count` int(10) unsigned NOT NULL DEFAULT '0',
  `charges` int(10) unsigned NOT NULL DEFAULT '0',
  `flags` int(10) unsigned NOT NULL DEFAULT '0',
  `randomprop` int(10) unsigned NOT NULL DEFAULT '0',
  `randomsuffix` int(10) NOT NULL,
  `itemtext` int(10) unsigned NOT NULL DEFAULT '0',
  `durability` int(10) unsigned NOT NULL DEFAULT '0',
  `containerslot` int(11) DEFAULT '-1',
  `slot` int(10) NOT NULL DEFAULT '0',
  `enchantments` longtext NOT NULL,
  PRIMARY KEY (`guid`),
  KEY `ownerguid` (`ownerguid`),
  KEY `itemtext` (`itemtext`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `playeritems`
--

LOCK TABLES `playeritems` WRITE;
/*!40000 ALTER TABLE `playeritems` DISABLE KEYS */;
/*!40000 ALTER TABLE `playeritems` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playeritems_insert_queue`
--

DROP TABLE IF EXISTS `playeritems_insert_queue`;
CREATE TABLE `playeritems_insert_queue` (
  `ownerguid` int(10) unsigned NOT NULL DEFAULT '0',
  `entry` int(10) unsigned NOT NULL DEFAULT '0',
  `wrapped_item_id` int(30) NOT NULL DEFAULT '0',
  `wrapped_creator` int(30) NOT NULL DEFAULT '0',
  `creator` int(10) unsigned NOT NULL DEFAULT '0',
  `count` int(10) unsigned NOT NULL DEFAULT '0',
  `charges` int(10) unsigned NOT NULL DEFAULT '0',
  `flags` int(10) unsigned NOT NULL DEFAULT '0',
  `randomprop` int(10) unsigned NOT NULL DEFAULT '0',
  `randomsuffix` int(30) NOT NULL,
  `itemtext` int(10) unsigned NOT NULL DEFAULT '0',
  `durability` int(10) unsigned NOT NULL DEFAULT '0',
  `containerslot` int(11) NOT NULL DEFAULT '-1' COMMENT 'couldnt find this being used in source',
  `slot` tinyint(4) NOT NULL DEFAULT '0',
  `enchantments` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  KEY `ownerguid` (`ownerguid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `playeritems_insert_queue`
--

LOCK TABLES `playeritems_insert_queue` WRITE;
/*!40000 ALTER TABLE `playeritems_insert_queue` DISABLE KEYS */;
/*!40000 ALTER TABLE `playeritems_insert_queue` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playerpets`
--

DROP TABLE IF EXISTS `playerpets`;
CREATE TABLE `playerpets` (
  `ownerguid` bigint(20) NOT NULL DEFAULT '0',
  `petnumber` int(11) NOT NULL DEFAULT '0',
  `name` varchar(21) NOT NULL DEFAULT '',
  `entry` int(10) unsigned NOT NULL DEFAULT '0',
  `fields` longtext CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `xp` int(11) NOT NULL DEFAULT '0',
  `active` tinyint(1) NOT NULL DEFAULT '0',
  `level` int(11) NOT NULL DEFAULT '0',
  `actionbar` varchar(200) NOT NULL DEFAULT '',
  `happinessupdate` int(11) NOT NULL DEFAULT '0',
  `summon` int(11) NOT NULL DEFAULT '0',
  `reset_time` int(10) unsigned NOT NULL DEFAULT '0',
  `reset_cost` int(10) NOT NULL DEFAULT '0',
  `spellid` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ownerguid`,`petnumber`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `playerpets`
--

LOCK TABLES `playerpets` WRITE;
/*!40000 ALTER TABLE `playerpets` DISABLE KEYS */;
/*!40000 ALTER TABLE `playerpets` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playerpetspells`
--

DROP TABLE IF EXISTS `playerpetspells`;
CREATE TABLE `playerpetspells` (
  `ownerguid` bigint(20) NOT NULL DEFAULT '0',
  `petnumber` int(4) NOT NULL DEFAULT '0',
  `spellid` int(4) NOT NULL DEFAULT '0',
  `flags` int(4) NOT NULL DEFAULT '0',
  KEY `a` (`ownerguid`),
  KEY `b` (`petnumber`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `playerpetspells`
--

LOCK TABLES `playerpetspells` WRITE;
/*!40000 ALTER TABLE `playerpetspells` DISABLE KEYS */;
/*!40000 ALTER TABLE `playerpetspells` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playerspells`
--

DROP TABLE IF EXISTS `playerspells`;
CREATE TABLE `playerspells` (
  `guid` int(10) unsigned NOT NULL,
  `spellid` int(10) unsigned NOT NULL,
  PRIMARY KEY (`guid`,`spellid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `playerspells`
--

LOCK TABLES `playerspells` WRITE;
/*!40000 ALTER TABLE `playerspells` DISABLE KEYS */;
/*!40000 ALTER TABLE `playerspells` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playersummons`
--

DROP TABLE IF EXISTS `playersummons`;
CREATE TABLE `playersummons` (
  `ownerguid` int(11) unsigned NOT NULL DEFAULT '0',
  `entry` int(11) unsigned NOT NULL DEFAULT '0',
  `name` varchar(64) NOT NULL,
  KEY `a` (`ownerguid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `playersummons`
--

LOCK TABLES `playersummons` WRITE;
/*!40000 ALTER TABLE `playersummons` DISABLE KEYS */;
/*!40000 ALTER TABLE `playersummons` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playersummonspells`
--

DROP TABLE IF EXISTS `playersummonspells`;
CREATE TABLE `playersummonspells` (
  `ownerguid` bigint(20) NOT NULL DEFAULT '0',
  `entryid` int(4) NOT NULL DEFAULT '0',
  `spellid` int(4) NOT NULL DEFAULT '0',
  KEY `a` (`ownerguid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `playersummonspells`
--

LOCK TABLES `playersummonspells` WRITE;
/*!40000 ALTER TABLE `playersummonspells` DISABLE KEYS */;
/*!40000 ALTER TABLE `playersummonspells` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playertalents`
--

DROP TABLE IF EXISTS `playertalents`;
CREATE TABLE `playertalents` (
  `guid` int(10) unsigned NOT NULL,
  `spec` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `tid` smallint(5) unsigned NOT NULL,
  `rank` tinyint(3) unsigned NOT NULL,
  PRIMARY KEY (`guid`,`spec`,`tid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `playertalents`
--

LOCK TABLES `playertalents` WRITE;
/*!40000 ALTER TABLE `playertalents` DISABLE KEYS */;
/*!40000 ALTER TABLE `playertalents` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `questlog`
--

DROP TABLE IF EXISTS `questlog`;
CREATE TABLE `questlog` (
  `player_guid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `quest_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `slot` int(20) unsigned NOT NULL DEFAULT '0',
  `time_left` bigint(20) NOT NULL DEFAULT '0',
  `explored_area1` bigint(20) unsigned NOT NULL DEFAULT '0',
  `explored_area2` bigint(20) unsigned NOT NULL DEFAULT '0',
  `explored_area3` bigint(20) unsigned NOT NULL DEFAULT '0',
  `explored_area4` bigint(20) unsigned NOT NULL DEFAULT '0',
  `mob_kill1` bigint(20) NOT NULL DEFAULT '0',
  `mob_kill2` bigint(20) NOT NULL DEFAULT '0',
  `mob_kill3` bigint(20) NOT NULL DEFAULT '0',
  `mob_kill4` bigint(20) NOT NULL DEFAULT '0',
  PRIMARY KEY (`player_guid`,`quest_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `questlog`
--

LOCK TABLES `questlog` WRITE;
/*!40000 ALTER TABLE `questlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `questlog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `server_settings`
--

DROP TABLE IF EXISTS `server_settings`;
CREATE TABLE `server_settings` (
  `setting_id` varchar(200) NOT NULL,
  `setting_value` int(50) NOT NULL,
  PRIMARY KEY (`setting_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `server_settings`
--

LOCK TABLES `server_settings` WRITE;
/*!40000 ALTER TABLE `server_settings` DISABLE KEYS */;
/*!40000 ALTER TABLE `server_settings` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `social_friends`
--

DROP TABLE IF EXISTS `social_friends`;
CREATE TABLE `social_friends` (
  `character_guid` int(30) NOT NULL,
  `friend_guid` int(30) NOT NULL,
  `note` varchar(100) NOT NULL,
  PRIMARY KEY (`character_guid`,`friend_guid`),
  KEY `a` (`character_guid`),
  KEY `b` (`friend_guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `social_friends`
--

LOCK TABLES `social_friends` WRITE;
/*!40000 ALTER TABLE `social_friends` DISABLE KEYS */;
/*!40000 ALTER TABLE `social_friends` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `social_ignores`
--

DROP TABLE IF EXISTS `social_ignores`;
CREATE TABLE `social_ignores` (
  `character_guid` int(30) NOT NULL,
  `ignore_guid` int(30) NOT NULL,
  PRIMARY KEY (`character_guid`,`ignore_guid`),
  KEY `a` (`character_guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `social_ignores`
--

LOCK TABLES `social_ignores` WRITE;
/*!40000 ALTER TABLE `social_ignores` DISABLE KEYS */;
/*!40000 ALTER TABLE `social_ignores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tutorials`
--

DROP TABLE IF EXISTS `tutorials`;
CREATE TABLE `tutorials` (
  `playerId` bigint(20) unsigned NOT NULL DEFAULT '0',
  `tut0` bigint(20) unsigned NOT NULL DEFAULT '0',
  `tut1` bigint(20) unsigned NOT NULL DEFAULT '0',
  `tut2` bigint(20) unsigned NOT NULL DEFAULT '0',
  `tut3` bigint(20) unsigned NOT NULL DEFAULT '0',
  `tut4` bigint(20) unsigned NOT NULL DEFAULT '0',
  `tut5` bigint(20) unsigned NOT NULL DEFAULT '0',
  `tut6` bigint(20) unsigned NOT NULL DEFAULT '0',
  `tut7` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`playerId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `tutorials`
--

LOCK TABLES `tutorials` WRITE;
/*!40000 ALTER TABLE `tutorials` DISABLE KEYS */;
/*!40000 ALTER TABLE `tutorials` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2009-10-29 21:44:07