//////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
//////////////////////////////////////////////////////////////////////
// Implementation of game protocol
//////////////////////////////////////////////////////////////////////
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//////////////////////////////////////////////////////////////////////

#ifndef __OTSERV_PROTOCOLGAME_H__
#define __OTSERV_PROTOCOLGAME_H__

#include <string>
#include "protocol.h"
#include "enums.h"
#include "creature.h"

enum connectResult_t
{
	CONNECT_SUCCESS = 1,
	CONNECT_TOMANYPLAYERS = 2,
	CONNECT_MASTERPOSERROR = 3,
	CONNECT_INTERNALERROR = 4
};

class NetworkMessage;
typedef boost::shared_ptr<NetworkMessage> NetworkMessage_ptr;
class Player;
class Game;
class House;
class Container;
class Tile;
class Connection;

class ProtocolGame : public Protocol
{
	public:
		// static protocol information
		enum {server_sends_first = true};
		enum {protocol_identifier = 0}; // Not required as we send first
		enum {use_checksum = true};
		static const char* protocol_name() {return "gameworld protocol";}

#ifdef __ENABLE_SERVER_DIAGNOSTIC__
		static uint32_t protocolGameCount;
#endif
		ProtocolGame(Connection_ptr connection);
		virtual ~ProtocolGame();

		virtual int32_t getProtocolId() {return 0x0A;}

		bool login(const std::string& name, uint32_t accnumber, const std::string& password, uint16_t operatingSystem, uint8_t gamemasterLogin);
		bool logout(bool displayEffect, bool forced);

		void setPlayer(Player* p);

	private:
		std::list<uint32_t> knownCreatureList;

		bool connect(uint32_t playerId);
		void disconnect();
		void disconnectClient(uint8_t error, const char* message);

		virtual void releaseProtocol();
		virtual void deleteProtocolTask();

		void checkCreatureAsKnown(uint32_t id, bool &known, uint32_t &removedKnown);

		bool canSee(int32_t x, int32_t y, int32_t z) const;
		bool canSee(const Creature*) const;
		bool canSee(const Position& pos) const;

		// we have all the parse methods
		virtual void parsePacket(NetworkMessage& msg);
		virtual void onRecvFirstMessage(NetworkMessage& msg);
		virtual void onConnect();
		bool parseFirstPacket(NetworkMessage& msg);

		//Parse methods
		void parseLogout(NetworkMessage& msg);
		void parseCancelMove(NetworkMessage& msg);

		void parseReceivePing(NetworkMessage& msg);
		void parseAutoWalk(NetworkMessage& msg);
		void parseMove(NetworkMessage& msg, Direction dir);
		void parseTurn(NetworkMessage& msg, Direction dir);

		void parseRequestOutfit(NetworkMessage& msg);
		void parseSetOutfit(NetworkMessage& msg);
		void parseSay(NetworkMessage& msg);
		void parseLookAt(NetworkMessage& msg);
		void parseFightModes(NetworkMessage& msg);
		void parseAttack(NetworkMessage& msg);
		void parseFollow(NetworkMessage& msg);

		void parseBugReport(NetworkMessage& msg);
		void parseDebugAssert(NetworkMessage& msg);

		void parseThrow(NetworkMessage& msg);
		void parseUseItemEx(NetworkMessage& msg);
		void parseBattleWindow(NetworkMessage& msg);
		void parseUseItem(NetworkMessage& msg);
		void parseCloseContainer(NetworkMessage& msg);
		void parseUpArrowContainer(NetworkMessage& msg);
		void parseUpdateTile(NetworkMessage& msg);
		void parseUpdateContainer(NetworkMessage& msg);
		void parseTextWindow(NetworkMessage& msg);
		void parseHouseWindow(NetworkMessage& msg);

		void parseLookInShop(NetworkMessage& msg);
		void parsePlayerPurchase(NetworkMessage& msg);
		void parsePlayerSale(NetworkMessage& msg);
		void parseCloseShop(NetworkMessage& msg);

		void parseQuestLog(NetworkMessage& msg);
		void parseQuestLine(NetworkMessage& msg);

		void parseInviteToParty(NetworkMessage& msg);
		void parseJoinParty(NetworkMessage& msg);
		void parseRevokePartyInvite(NetworkMessage& msg);
		void parsePassPartyLeadership(NetworkMessage& msg);
		void parseLeaveParty(NetworkMessage& msg);
		void parseEnableSharedPartyExperience(NetworkMessage& msg);

		void parseToggleMount(NetworkMessage& msg);

		void parseRuleViolationReport(NetworkMessage& msg);

		//trade methods
		void parseRequestTrade(NetworkMessage& msg);
		void parseLookInTrade(NetworkMessage& msg);
		void parseAcceptTrade(NetworkMessage& msg);
		void parseCloseTrade();

		//VIP methods
		void parseAddVip(NetworkMessage& msg);
		void parseRemoveVip(NetworkMessage& msg);

		void parseRotateItem(NetworkMessage& msg);

		//Channel tabs
		void parseCreatePrivateChannel(NetworkMessage& msg);
		void parseChannelInvite(NetworkMessage& msg);
		void parseChannelExclude(NetworkMessage& msg);
		void parseGetChannels(NetworkMessage& msg);
		void parseOpenChannel(NetworkMessage& msg);
		void parseOpenPriv(NetworkMessage& msg);
		void parseCloseChannel(NetworkMessage& msg);
		void parseCloseNpc(NetworkMessage& msg);

		//Send functions
		void sendChannelMessage(std::string author, std::string text, SpeakClasses type, uint8_t channel);
		void sendClosePrivate(uint16_t channelId);
		void sendCreatePrivateChannel(uint16_t channelId, const std::string& channelName);
		void sendChannelsDialog();
		void sendChannel(uint16_t channelId, const std::string& channelName);
		void sendOpenPrivateChannel(const std::string& receiver);
		void sendToChannel(const Creature* creature, SpeakClasses type, const std::string& text, uint16_t channelId);
		void sendIcons(int32_t icons);
		void sendFYIBox(const std::string& message);

		void sendDistanceShoot(const Position& from, const Position& to, uint8_t type);
		void sendMagicEffect(const Position& pos, uint8_t type);
		void sendAnimatedText(const Position& pos, uint8_t color, std::string text);
		void sendCreatureHealth(const Creature* creature);
		void sendSkills();
		void sendPing();
		void sendCreatureTurn(const Creature* creature, uint32_t stackpos);
		void sendCreatureSay(const Creature* creature, SpeakClasses type, const std::string& text, Position* pos = NULL);

		void sendCancel(const std::string& message);
		void sendCancelWalk();
		void sendChangeSpeed(const Creature* creature, uint32_t speed);
		void sendCancelTarget();
		void sendCreatureVisible(const Creature* creature, bool visible);
		void sendCreatureOutfit(const Creature* creature, const Outfit_t& outfit);
		void sendCreatureInvisible(const Creature* creature);
		void sendStats();
		void sendTextMessage(MessageClasses mclass, const std::string& message);
		void sendReLoginWindow();

		void sendTutorial(uint8_t tutorialId);
		void sendAddMarker(const Position& pos, uint8_t markType, const std::string& desc);

		void sendCreatureSkull(const Creature* creature);
		void sendCreatureShield(const Creature* creature);

		void sendShop(Npc* npc, const ShopInfoList& itemList);
		void sendCloseShop();
		void sendSaleItemList(const std::list<ShopInfo>& shop);
		void sendTradeItemRequest(const Player* player, const Item* item, bool ack);
		void sendCloseTrade();

		void sendTextWindow(uint32_t windowTextId, Item* item, uint16_t maxlen, bool canWrite);
		void sendTextWindow(uint32_t windowTextId, uint32_t itemId, const std::string& text);
		void sendHouseWindow(uint32_t windowTextId, House* house, uint32_t listId, const std::string& text);
		void sendOutfitWindow();

		void sendVIPLogIn(uint32_t guid);
		void sendVIPLogOut(uint32_t guid);
		void sendVIP(uint32_t guid, const std::string& name, bool isOnline);

		void sendCreatureLight(const Creature* creature);
		void sendWorldLight(const LightInfo& lightInfo);

		void sendCreatureSquare(const Creature* creature, SquareColor_t color);

		void sendSpellCooldown(uint8_t spellId, uint32_t time);
		void sendSpellGroupCooldown(SpellGroup_t groupId, uint32_t time);

		//tiles
		void sendAddTileItem(const Tile* tile, const Position& pos, uint32_t stackpos, const Item* item);
		void sendUpdateTileItem(const Tile* tile, const Position& pos, uint32_t stackpos, const Item* item);
		void sendRemoveTileItem(const Tile* tile, const Position& pos, uint32_t stackpos);
		void sendUpdateTile(const Tile* tile, const Position& pos);

		void sendAddCreature(const Creature* creature, const Position& pos, uint32_t stackpos, bool isLogin);
		void sendRemoveCreature(const Creature* creature, const Position& pos, uint32_t stackpos, bool isLogout);
		void sendMoveCreature(const Creature* creature, const Tile* newTile, const Position& newPos, uint32_t newStackPos,
			const Tile* oldTile, const Position& oldPos, uint32_t oldStackPos, bool teleport);

		//containers
		void sendAddContainerItem(uint8_t cid, const Item* item);
		void sendUpdateContainerItem(uint8_t cid, uint8_t slot, const Item* item);
		void sendRemoveContainerItem(uint8_t cid, uint8_t slot);

		void sendContainer(uint32_t cid, const Container* container, bool hasParent);
		void sendCloseContainer(uint32_t cid);

		//inventory
		void sendAddInventoryItem(slots_t slot, const Item* item);
		void sendUpdateInventoryItem(slots_t slot, const Item* item);
		void sendRemoveInventoryItem(slots_t slot);

		//messages
		void sendDamageMessage(MessageClasses mclass, const std::string& message, const Position& pos,
			uint32_t primaryDamage = 0, TextColor_t primaryColor = TEXTCOLOR_NONE,
			uint32_t secondaryDamage = 0, TextColor_t secondaryColor = TEXTCOLOR_NONE);
		void sendHealMessage(MessageClasses mclass, const std::string& message, const Position& pos, uint32_t heal, TextColor_t color);
		void sendExperienceMessage(MessageClasses mclass, const std::string& message, const Position& pos, uint32_t exp, TextColor_t color);

		//Help functions

		// translate a tile to clientreadable format
		void GetTileDescription(const Tile* tile, NetworkMessage_ptr msg);

		// translate a floor to clientreadable format
		void GetFloorDescription(NetworkMessage_ptr msg, int32_t x, int32_t y, int32_t z,
			int32_t width, int32_t height, int32_t offset, int32_t& skip);

		// translate a map area to clientreadable format
		void GetMapDescription(int32_t x, int32_t y, int32_t z,
			int32_t width, int32_t height, NetworkMessage_ptr msg);

		void AddMapDescription(NetworkMessage_ptr msg, const Position& pos);
		void AddTextMessage(NetworkMessage_ptr msg,MessageClasses mclass, const std::string& message);
		void AddAnimatedText(NetworkMessage_ptr msg, const Position& pos, uint8_t color, const std::string& text);
		void AddMagicEffect(NetworkMessage_ptr msg, const Position& pos, uint8_t type);
		void AddDistanceShoot(NetworkMessage_ptr msg, const Position& from, const Position& to, uint8_t type);
		void AddCreature(NetworkMessage_ptr msg, const Creature* creature, bool known, uint32_t remove);
		void AddPlayerStats(NetworkMessage_ptr msg);
		void AddCreatureSpeak(NetworkMessage_ptr msg, const Creature* creature, SpeakClasses type,
			std::string text, uint16_t channelId, Position* pos = NULL);
		void AddCreatureHealth(NetworkMessage_ptr msg, const Creature* creature);
		void AddCreatureOutfit(NetworkMessage_ptr msg, const Creature* creature, const Outfit_t& outfit);
		void AddCreatureInvisible(NetworkMessage_ptr msg, const Creature* creature);
		void AddPlayerSkills(NetworkMessage_ptr msg);
		void AddWorldLight(NetworkMessage_ptr msg, const LightInfo& lightInfo);
		void AddCreatureLight(NetworkMessage_ptr msg, const Creature* creature);

		//tiles
		void AddTileItem(NetworkMessage_ptr msg, const Position& pos, uint32_t stackpos, const Item* item);
		void AddTileCreature(NetworkMessage_ptr msg, const Position& pos, uint32_t stackpos, const Creature* creature);
		void UpdateTileItem(NetworkMessage_ptr msg, const Position& pos, uint32_t stackpos, const Item* item);
		void RemoveTileItem(NetworkMessage_ptr msg, const Position& pos, uint32_t stackpos);

		void MoveUpCreature(NetworkMessage_ptr msg, const Creature* creature,
			const Position& newPos, const Position& oldPos, uint32_t oldStackPos);
		void MoveDownCreature(NetworkMessage_ptr msg, const Creature* creature,
			const Position& newPos, const Position& oldPos, uint32_t oldStackPos);

		//container
		void AddContainerItem(NetworkMessage_ptr msg, uint8_t cid, const Item* item);
		void UpdateContainerItem(NetworkMessage_ptr msg, uint8_t cid, uint8_t slot, const Item* item);
		void RemoveContainerItem(NetworkMessage_ptr msg, uint8_t cid, uint8_t slot);

		//inventory
		void AddInventoryItem(NetworkMessage_ptr msg, slots_t slot, const Item* item);
		void UpdateInventoryItem(NetworkMessage_ptr msg, slots_t slot, const Item* item);
		void RemoveInventoryItem(NetworkMessage_ptr msg, slots_t slot);

		//shop
		void AddShopItem(NetworkMessage_ptr msg, const ShopInfo item);

		friend class Player;

		// Helper so we don't need to bind every time
		#define addGameTask(f, ...) addGameTaskInternal(boost::bind(f, &g_game, __VA_ARGS__))

		template<class FunctionType>
		void addGameTaskInternal(const FunctionType&);

		Player* player;

		int64_t m_nextPing;

		uint32_t eventConnect;

		bool m_debugAssertSent;
		bool m_acceptPackets;
};

#endif
