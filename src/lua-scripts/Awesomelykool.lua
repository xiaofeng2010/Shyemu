function HadesMinion_OnCombat(Unit, Event)
Unit:SendChatMessage(14, 0, "Be Prepared to Die Mortal!")
Unit:RegisterEvent("HadesMinion_Summon1", 120000, 3)
Unit:RegisterEvent("HadesMinion_Phase1", 10000, 1)
Unit:RegisterEvent("HadesMinion_Phase2", 10000, 1)
Unit:RegisterEvent("HadesMinion_Phase3", 10000, 1)
Unit:RegisterEvent("HadesMinion_Phase4", 10000, 1)
end

function HadesMinion_Phase1(Unit, Event)
if Unit:GetHealthPct() <= 75 then
Unit:SendChatMessage(14, 0, "Burn In Hell!")
Unit:FullCastSpellOnTarget(5, Unit:GetMainTank())
Unit:FullCastSpellOnTarget(5, Unit:GetRandomPlayer(1))
end
end

function HadesMinion_Phase2(Unit, Event)
if Unit:GetHealthPct() <= 50 then
Unit:SendChatMessage(14, 0, "Now You've Done It!")
Unit:FullCastSpellOnTarget(5, Unit:GetRandomPlayer(1))
end
end

function HadesMinion_Phase3(Unit, Event)
if Unit:GetHealthPct() <= 25 then
Unit:SetScale(1.5)
Unit:SendChatMessage(14, 0, "Now You Shall Feel My Wrath!")
Unit:FullCastSpellOnTarget(5, Unit:GetRandomPlayer(1))
Unit:FullCastSpellOnTarget(5, Unit:GetRandomPlayer(1))
Unit:FullCastSpellOnTarget(5, Unit:GetMainTank())
end
end

function HadesMinion_Phase4(Unit, Event)
if Unit:GetHealthPct() <= 1 then
Unit:SendChatMessage(14, 0, "How Can This Be?!")
end
end

function HadesMinion_Summon1(Unit, Event)
if Unit:GetHealthPct() <= 25 then
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(30416, x, y, z, o, 14, 120000)
end
end

function HadesMinion_OnKilledTarget(Unit, Event)
Unit:SendChatMessage(14, 0, "You Were Warned!")
end

function HadesMinion_OnLeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function HadesMinion_OnDied(Unit, Event)
Unit:RemoveEvents()
end

RegisterUnitEvent(9, 1, "HadesMinion_OnCombat")
RegisterUnitEvent(9, 2, "HadesMinion_OnKilledTarget")
RegisterUnitEvent(9, 3, "HadesMinion_OnLeaveCombat")
RegisterUnitEvent(9, 4, "HadesMinion_OnDied")