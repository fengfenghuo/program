#pragma once
#include "common.h"
#include "cards.h"
#include "roles.h"
#include "playerData.h"

class GameData {
public:
	GameData();
	GameData(uint16_t role_count);
	~GameData();

	bool setRoleCount(uint16_t role_count);
	int generateStatus(uint16_t role_count);
	bool generateRoles();
	bool shuffleCards();
	bool dealCards(uint16_t cards_count, uint16_t role_num);
	bool dealCards(uint16_t cards_count, CLICARDS *cards);
	int judgeCards(uint16_t role_num);
	CLICARDS * playCards(uint16_t role_num);
	CLICARDS * discardCards(uint16_t role_num);
	bool playerStartToPlay(uint16_t role_num);
	bool playerEndToPlay(uint16_t role_num);
	int applyCardPlay(CLICARDS *card, uint16_t role_num);
	PLAYERINFO* findPlayerInfoByNum(uint16_t role_num);
	uint16_t roleAliveNum();
	bool startingCards();
	bool endingCondition(uint16_t role_num);

	int playerBloodReduce(uint16_t role_num);
	//////////////////////////////////////////
	uint16_t curRoleCount();
	//////////////////////////////////////////
	//Ñ¡ÔñÄ¿±ê
	int chooseTarget(uint16_t distance, uint16_t role_num, bool need_weapon);
	int applyDamage(uint32_t card_id, uint16_t source_num, uint16_t target_num);
	int applyDamageAll(uint32_t card_id, uint16_t source_num);
	int applyPlayCard(uint32_t card_id, uint16_t target_num);
	int applyCardRemove(uint32_t card_id, uint16_t source_num, uint16_t target_num);
	int applyCardDuel(uint16_t source_num, uint16_t target_num);
	int applyCardDeals(uint16_t cards_count, CLICARDS * cards);
	//////////////////////////////////////////

	void viewPilesCards();
	void viewPlayersStatus();
	void viewRoleInfo(ROLESINFO * role);
	void viewPlayersRole();
	void viewPlayerCards(uint16_t role_num);

private:
	uint16_t m_roleCount;
	uint16_t m_role_cur_count;
	PlayerData *m_players;
	uint16_t m_cards_count;
	CLICARDS m_piles_cards[CARDS_TOTAL];
	uint16_t m_discards_count;
	CLICARDS m_piles_disvards[CARDS_TOTAL];
};