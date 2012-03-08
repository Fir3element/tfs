function onChannelJoin(cid, channelId, users)
	if(channelId ~= CHANNEL_GUILD) then
		return true
	end
 
	local players = getOnlinePlayers()
	if (#players > 1) then
		for _, player in ipairs(players) do
			local pid = getPlayerByNameWildcard(player)
			if(getPlayerGuildId(pid) == getPlayerGuildId(cid)) then
				doPlayerSendChannelMessage(pid, "", "Player " .. getCreatureName(cid) .. " has entered the channel.", TALKTYPE_CHANNEL_HIGHLIGHT, CHANNEL_GUILD)
			end
		end
	end

	local guildId = getPlayerGuildId(cid)
	if(guildId and guildId ~= 0) then
		local guildMotd = getGuildMotd(guildId)
		if(guildMotd and guildMotd ~= "") then
			addEvent(doPlayerSendChannelMessage, 150, cid, "", "Message of the Day: " .. guildMotd, TALKTYPE_GAMEMASTER_CHANNEL, CHANNEL_GUILD)
		end
	end
	return true
end

function onChannelLeave(cid, channelId, users)
	if(channelId ~= CHANNEL_GUILD) then
		return true
	end

	for _, pid in users do
		doPlayerSendChannelMessage(pid, "", "Player " .. getCreatureName(cid) .. " has left the channel.", TALKTYPE_CHANNEL_HIGHLIGHT, CHANNEL_GUILD)
	end
	return true
end