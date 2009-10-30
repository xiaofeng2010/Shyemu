local NpcID = YOURENTRYIDHERE

function Slik_OnSpawn(Unit, Event)
	local Slik = Unit -- This allows me to use Slik:IsMoving() etc, instead of Unit:IsMoving().
end

function Slik_OnCombat(Unit, Event)
	Slik:SendChatMessage(14, 0, "Time to D!e")
	Slik:RegisterEvent("Slik_TankCatcher", 1000, 5)
	Slik:RegisterEvent("Slik_IceLance", 1000, 5)
	Slik:RegisterEvent("Slik_DeepFreeze", 1000, 1)
	Slik:RegisterEvent("Slik_DeathRain", 1000, 1)
	Slik:RegisterEvent("Slik_Enraged", 1113, 1)
	Slik:RegisterEvent("Slik_Doomed", 1113, 1)
	Slik:RegisterEvent("Slik_Dead", 1113, 1)
end

function Slik_TankCatcher(Unit, Event)
	if Slik:IsMoving(Slik:GetMainTank()) then
		local Moving = 1
	else
		local Moving = 0
	end
end

function Slik_IceLance(Unit, Event)
	if (Moving == 1) then
		local plr = Slik:GetMainTank()
		Slik:FullCastSpellOnTarget(43427, plr)
	else
	end
end

function Slik_DeepFreeze
	if Slik:GetHealthPct() <= 75 then
		Slik:SendChatMessage(14, 0, "You Will Soon Perish")
			local tank = Slik:GetMainTank()
			local player = Slik:GetRandomPlayer(1)
			if player ~= nil then
				Slik:FullCastSpellOnTarget(58534, player)
			else
				Slik:FullCastSpellOnTarget(58534, tank)
			end
		end
end
	

function Slik_DeathRain(Unit, Event)
	if Slik:GetHealthPct() <= 50 then
		Slik:SendChatMessage(14, 0, "You Have Gotten Far, But You Will Not Last For Long")
		if Slik:IsInBack(Slik:GetRandomPlayer(0)) then
			local InBack = 1
		else
			local InBack = 0
		end
		if (InBack == 1) then
			local plr = Slik:GetRandomPlayer(0)
			Slik:FullCastSpellOnTarget(5, plr)
		else
		end
		if Slik:IsInFront(Slik:GetRandomPlayer(0)) then
			local InFront = 1
		else
			local InFront = 0
		end
		if (InFront == 1) then
			local plr = Slik:GetRandomPlayer(0)
			Slik:FullCastSpellOnTarget(5, plr)
		else
		end
		if Slik:IsStealthed(Slik:GetRandomPlayer(0)) then
			local Stealthed = 1
		else
			local Stealthed = 0
		end
		if (Stealthed == 1) then
			local plr = Slik:GetRandomPlayer(0)
			Slik:FullCastSpellOnTarget(5, plr)
		else
		end
	end
end

function Slik_Enraged(Unit, Event)
	if Slik:GetHealthPct() <= 25 then
		Slik:SendChatMessage(14, 0, "I will survive this fight!")
		Slik:SetScale(2.0)
		Slik:SendChatMessage(14, 0, "Your going down!")
		Slik:FullCastSpellOnTarget(47864, player)
		Slik:FullCastSpellOnTarget(47864, player)
		Slik:FullCastSpellOnTarget(64157, tank)
		local tank = Slik:GetMainTank()
		local player_with_mana = Slik:GetRandomPlayer(4)
		if player_with_mana ~= nil then
			Slik:FullCastSpellOnTarget(18502, player_with_mana)
		else
			Slik:FullCastSpellOnTarget(18502, tank)
		end
		local tank = Slik:GetMainTank()
		local player_long_range = Slik:GetRandomPlayer(3)
		if player_long_range ~= nil then
			Slik:FullCastSpellOnTarget(18502, player_long_range)
		else
			Slik:FullCastSpellOnTarget(18502, tank)
		end
	end
end

function Slik_Doomed(Unit, Event)
	if Slik:GetHealthPct() <= 5 then
		Slik:SendChatMessage(14, 0, "This is not possible! what if good takes over evil? I CAN'T LET THAT HAPPEN!")
		Slik:SetScale(3.4)
		Slik:FullCastSpellOnTarget(64157, tank)
		local tank = Slik:GetMainTank()
		local player = Slik:GetRandomPlayer(0)
		if player ~= nil then
			Slik:FullCastSpellOnTarget(64157, player)
		else
			Slik:FullCastSpellOnTarget(64157, tank)
		end
		local tank = Slik:GetMainTank()
		local player_med_range = Slik:GetRandomPlayer(2)
		if player_med_range ~= nil then
			Slik:FullCastSpellOnTarget(5, player_med_range)
		else
			Slik:FullCastSpellOnTarget(5, tank)
		end
		local tank = Slik:GetMainTank()
		local player_with_mana = Slik:GetRandomPlayer(4)
		if player_with_mana ~= nil then
			Slik:FullCastSpellOnTarget(5, player_with_mana)
		else
			Slik:FullCastSpellOnTarget(5, tank)
		end
		local tank = Slik:GetMainTank()
		local player_c_range = Slik:GetRandomPlayer(1)
		if player_c_range ~= nil then
			Slik:FullCastSpellOnTarget(64157, player_c_range)
		else
			Slik:FullCastSpellOnTarget(64157, tank)
		end
	end
end

function Slik_Death(Unit, Event)
	if Slik:GetHealthPct() <= 1 then
		Slik:SendChatMessage(12, 0, "So this is how it will end? You killing me? I can't let that happen!")
		Slik:SetScale(1.0)
	end
end

function Slik_OnKilledTarget(Unit, Event)
	Slik:SendChatMessage(14, 0, "Die!")
end

function Slik_OnLeaveCombat(Unit, Event)
	Slik:SendChatMessage(14, 0, "Wuss!")
	Slik:RemoveEvents()
end

function Slik_OnDied(Unit, Event)
	Slik:SendChatMessage(14, 0, "I can't stand a chance to win, against someone like you, you are gifted and you really are smart")
	Slik:RemoveEvents()
end

RegisterUnitEvent(NpcID, 1, "Slik_OnCombat")
RegisterUnitEvent(NpcID, 3, "Slik_OnKilledTarget")
RegisterUnitEvent(NpcID, 2, "Slik_OnLeaveCombat")
RegisterUnitEvent(NpcID, 4, "Slik_OnDied")
RegisterUnitEvent(NpcID, 18, "Slik_OnSpawn")