#pragma once
#include "common.h"
#include "cards.h"
#include "roles.h"

class GameData {
public:
	GameData();
	~GameData();

	bool setRoleCount(uint16_t role_count);
	bool generateStatus(uint16_t role_count, uint16_t *roles);
	bool generateRoles(uint16_t role_status, uint16_t *roles_identity);
	bool shuffleCards();

	void viewPilesCards();

private:
	uint16_t m_roleCount;
	uint16_t m_cards_count;
	CLICARDS m_piles_cards[CARDS_TOTAL];
	uint16_t m_discards_count;
	CLICARDS m_piles_disvards[CARDS_TOTAL];
};