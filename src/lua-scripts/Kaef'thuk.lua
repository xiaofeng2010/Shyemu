function BossName_OnCombat(pUnit, Event)
pUnit:SendChatMessage(14, 0, "How dare you even come to Hyjal? This is my territory and i will protect it no matter what!")
pUnit:RegisterEvent("Phase_1", 1000, 0)
end

function BossName_OnDied(pUnit, Event)
pUnit:SendChatMessage(14,0, "I have died..Why don't you just understand that this is my territory? Well...I guees i was wrong about you...I didn't expect this from you!")
pUnit:RemoveEvents()
end

function BossName_LeaveCombat (pUnit, Event)
pUnit:SendChatMessage(14,0, "You have made the right choice....RUN AWAY AND NEVER RETURN!")
pUnit:RemoveEvents()
end

function Phase_1(pUnit, Event)
if pUnit:GetHealthPct() <= 75 then
pUnit:RemoveEvents()
pUnit:SendChatMessage(14, 0, "You don't seem to give up....I will force you to give up!!")
pUnit:RegisterEvent("FireBall", 35000, 0)
pUnit:RegisterEvent("Phase_2", 1000, 0)
end
end

function Phase_2(pUnit, Event)
if pUnit:GetHealthPct() <= 50 then
pUnit:RemoveEvents()
pUnit:SendChatMessage(14, 0, "you have yet to see my real powers....Die!!")
pUnit:RegisterEvent("ArcaneExplosion", 6000, 0)
end
end

function FireBall(pUnit, Event)
pUnit:CastSpellOnTarget(61909, pUnit:GetRandomPlayer(0))
end

function ArcaneExplosion(pUnit, Event)
pUnit:CastSpell(29973)
end

function Hodir_p5(pUnit, Event)
if pUnit:GetHealthPct() < 35 then
pUnit:RemoveEvents()
pUnit:SendChatMessage (12, 0, "How do you possibly think you stand a chance against me?")
pUnit:CastSpellOnTarget(16803, pUnit:GetRandomPlayer(0))
pUnit:RegisterEvent("Hodir_p6",1000, 0)
end
end

function Hodir_Phase6(Unit, Event)
if Unit:GetHealthPct() < 15 then
Unit:RegisterEvent("Hodir_5Spell1", 13000, 0)
Unit:RegisterEvent("Hodir_5Spell2", 14000, 0)
Unit:RegisterEvent("Hodir_5Spell3", 4000, 0)
end
end

function Hodir_Spell1(Unit, Event)
Unit:FullCastSpellOnTarget(54095, Unit:GetMainTank())
end

function Hodir_Spell2(Unit, Event)
Unit:CastSpell(36876)
end

function Hodir_Spell3(Unit, Event)
Unit:FullCastSpellOnTarget(55362, Unit:GetMainTank())
end

RegisterUnitEvent(96666, 1, "BossName_OnCombat")
RegisterUnitEvent(96666, 2, "BossName_OnLeaveCombat")
RegisterUnitEvent(96666, 4, "BossName_OnDied")