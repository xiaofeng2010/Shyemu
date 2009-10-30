local Cooldown = 0;
NUM_MINUTES = 60*2;   --2 hours

function Music_OnGossipTalk(pUnit, event, player, pMisc)
pUnit:GossipCreateMenu(100, player, 1)
if ( os.difftime( os.time(), Cooldown ) < 60*NUM_MINUTES ) then
pUnit:GossipMenuAddItem(0, "This is still on cooldown. You have to wait"..( NUM_MINUTES - (os.difftime( os.time(), Cooldown) / 60)  ).." more minutes to play a song again.", 99, 0)
else
pUnit:GossipMenuAddItem(0, "*Rock*", 1, 0)
pUnit:GossipMenuAddItem(0, "*holy life -srinty bpeers*", 2, 0)
pUnit:GossipMenuAddItem(0, "*Drums*", 3, 0)
pUnit:GossipMenuAddItem(0, "*MURLOC*", 4, 0)
pUnit:GossipMenuAddItem(0, "Wooot? Illidan??", 5, 0)
end
pUnit:GossipSendMenu(player)
end


function Music_OnGossipSelect(pUnit, event, player, id, intid, code, pMisc)

if intid==99 then
pUnit:GossipComplete(player);
retur
n;
end

if ( os.difftime( os.time(), Cooldown ) < 60*NUM_MINUTES ) then
pUnit:SendChatMessage(14, 0, "You have to wait "..( NUM_MINUTES - (os.difftime( os.time(), Cooldown) / 60)  ).." more minutes to play a song again.")
return;
end

Cooldown = os.time();

if (intid == 1) then
pUnit:SendChatMessage(14, 0, "Rock this party DANCE everybody!")
pUnit:PlaySoundToSet(11803)
pUnit:GossipComplete(player)
end

if (intid == 2) then
pUnit:SendChatMessage(12, 0, "Make it HOT! in this club.....")
pUnit:PlaySoundToSet(11699)
pUnit:GossipComplete(player)
end

if (intid == 3) then
pUnit:PlaySoundToSet(11704)
pUnit:GossipComplete(player)
end

if (intid == 4) then
pUnit:SendChatMessage(12, 0, "Dont STOP move your body!")
pUnit:PlaySoundToSet(11802)
pUnit:GossipComplete(player)
end

if (intid == 5) then
pUnit:SendChatMessage(14, 0, "Everybody DANCE now!")
pUnit:PlaySoundToSet(11466)
pUnit:GossipComplete(player)
end
end

RegisterUnitGossipEvent(99028, 1, "Music_OnGossipTalk")
RegisterUnitGossipEvent(99028, 2, "Music_OnGossipSelect")