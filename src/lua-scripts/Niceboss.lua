function Patchwerk_OnCombat (Unit, Event)
speak = math.random (1,2)
if speak==1 then
Unit:SendChatMessage (14, 0, "Patchwerk want to play.")
Unit:PlaySoundToSet(8909)
if speak==2 then
Unit:SendChatMessage (14, 0, "Kel'Thuzad make Patchwerk his avatar of war!")
Unit:PlaySoundToSet(8910)
end
end
Unit:RegisterEvent ("Patchwerk_HatefulStrike", 1000, 0)
Unit:RegisterEvent ("Patchwerk_Frenzy", 5000, 0)
Unit:RegisterEvent ("Patchwerk_Berserk", 360000, 1)
end

function Patchwerk_HatefulStrike (Unit, Event)
Unit:FullCastSpellOnTarget (41926, Unit:GetClosestPlayer())
end

function Patchwerk_Frenzy (Unit, Event)
if Unit:GetHealthPct() =<5 then
Unit:FullCastSpell (28131)
Unit:RegisterEvent ("Patchwerk_SlimeBolt", 10000, 0)
end
end

function Patchwerk_SlimeBolt (Unit, Event)
Unit:FullCastSpellOnTarget (32309, Unit:GetRandomPlayer())
end

function Patchwerk_Berserk (Unit, Event)
Unit:FullCastSpell (26662)
end

function Patchwerk_OnLeave (Unit, Event)
Unit:RemoveEvents()
end

function Patchwerk_KilledTarget (Unit, Events)
Unit:SendChatMessage (14, 0, "No more play?")
Unit:PlaySoundToSet(8912)
end

function Patchwerk_OnDie (Unit, Event)
Unit:SentChatMessage (14, 0, "What happened to... Patch...")
Unit:PlaySoundToSet(8911)
Unit:RemoveEvents()
end

RegisterUnitEvent (16028, 1, "Patchwerk_OnCombat")
RegisterUnitEvent (16028, 2, "Patchwerk_OnLeave")
RegisterUnitEvent (16028, 3, "Patchwerk_KilledTarget")
RegisterUnitEvent (16028, 4, "Patchwerk_OnDie")