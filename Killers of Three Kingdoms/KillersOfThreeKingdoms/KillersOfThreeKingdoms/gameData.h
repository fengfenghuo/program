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
	bool generateStatus(uint16_t role_count, uint16_t *roles);
	bool generateRoles(uint16_t role_status, uint16_t *roles_identity);
	bool shuffleCards();
	bool dealCards(uint16_t cards_count, CLICARDS * cards);
	int applyCardPlay(CLICARDS *card, uint16_t role_num);

	//////////////////////////////////////////
	//ѡ��Ŀ��
	int chooseTarget(uint16_t distance, uint16_t role_num);
	int applyDamage(uint32_t card_id, uint16_t source_num, uint16_t target_num);
	int applyPlayCard(uint32_t card_id, uint16_t target_num);
	//////////////////////////////////////////

	void viewPilesCards();

private:
	uint16_t m_roleCount;
	PlayerData *m_players;
	uint16_t m_cards_count;
	CLICARDS m_piles_cards[CARDS_TOTAL];
	uint16_t m_discards_count;
	CLICARDS m_piles_disvards[CARDS_TOTAL];
};