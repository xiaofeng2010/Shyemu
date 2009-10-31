-[[
       Multi functional NPC script.
       By Wolferine. Do not remove these credits, or claim this to be yours.
       
       WARNING:THIS SCRIPT REQUIRES LUAHYPARC!
]]

local NPC_ID = 11111


function MultiGossipOnTalk(pUnit, Event, player)
       pUnit::GossipCreateMenu(100, player, 0)
       pUnit:GossipMenuAddItem(0, "Change Gender.", 1, 0)
       pUnit:GossipMenuAddItem(0, "Reset Talents.", 2, 0)
       pUnit:GossipMenuAddItem(0, "I would like to see my bank.", 3, 0)
       PUnit:GossipMenuAddItem(0, "Remove Ressurection sickness.", 4, 0)
       pUnit:GossipMenuAdditem(0, "Set weather: Sunny.", 5, 0)
       pUnit:GossipMenuAddItem(0, "Set weather: Fog.", 6, 0)
       pUnit:GossipMenuAddItem(0, "Set weather: Rain.", 7, 0)
       pUnit:GossipMenuAddItem(0, "Set weather: Heavy rain.", 8, 0)
       pUnit:GossipMenuAddItem(0, "Set weather: Snow.", 9, 0)
       pUnit:GossipMenuAddItem(0, "Set weather: Sand Storm.", 10, 0)
       pUnit:GossipMenuAddItem(0, "Never mind.", 11, 0)
       pUnit:GossipSendMenu(player)
end

function MultiGossiponselect(pUnit, Event, player, id, intid, code, pMisc)
        if (intid == 1) then
                if (player:GetGender() == 0) then
                        player:SetGender(1)
                        player:SendBroadcastMessage("Gender set to Female, please relog to take effect.")
                        Unit:GossipComplete
else
                if (player:GetGender() == 1) then
                        player:SetGender(0)
                        player:SendBroadcastMessage("Gender set to Male, please relog to take effect.")
                        Unit:GossipComplete
                end
        end
end             

        if (intid == 2) then
                player:ResetTalents()
                player:SendBroadCastMessage("Talents reset")
                pUnit:GossipComplete()
         end

        if (intid == 3) then
                player:SendBankWindow(unit)
                pUnit:GossipComplete()
         end

if (intid == 4) then
                if (player:HasAura(15007) == true) then
                        player:SendBroadcastMessage("Resurrection Sickness has been removed.")
                        player:RemoveAura(15007)
                        Unit:GossipComplete()
                else
                        player:SendBroadcastMessage("You do not have Resurrection Sickness!")
                        Unit:GossipComplete()
                end
        end

if (intid == 5) then
                player:SetPlayerWeather(0, 1)
                pUnit:GossipComplete()
        end

if (intid == 6) then
                player:SetPlayerWeather(1, 1)
                pUnit:GossipComplete()
        end

if (intid == 7) then
                player:SetPlayerWeather(2, 1)
                pUnit:GossipComplete()
        end

if (intid == 8) then
                player:SetPlayerWeather(4, 1)
                pUnit:GossipComplete()
        end

if (intid == 9) then
                player:SetPlayerWeather(8, 1) 
                pUnit:GossipComplete()
       end

if (intid == 10) then
                player:SetPlayerWeather(16, 1)             
                pUnit:GossipComplete()
       end

if (GetLuaEngine() ~= "LuaHypArc") then --we gotta make sure they're using LuaHypArc!
        print("LuaEngine: Did not load 'Multifunctional - NPC' script - LuaHypArc not installed.")
        print("LuaEngine: Please visit http://luahyparc.zapto.org/ for more information.")
        end
end

RegisterUnitGossipEvent(NPC_ID, 1, "MultiGossipOnTalk")
RegisterUnitGossipEvent(NPC_ID, 2, "MultiGossiponselect")