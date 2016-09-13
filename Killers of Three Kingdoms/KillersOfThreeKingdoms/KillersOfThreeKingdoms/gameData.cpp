#include "gameData.h"
#include "cardsInfoManagement.h"
#include "rolesInfoManagement.h"
#include "statusInfoManagement.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>

GameData::GameData() {
	m_roleCount = 0;
	m_cards_count = 0;
	memset(m_piles_cards, 0, sizeof(CLICARDS)*CARDS_TOTAL);
	m_discards_count = 0;
	memset(m_piles_disvards, 0, sizeof(CLICARDS)*CARDS_TOTAL);
}

GameData::~GameData() {

}

void GameData::viewPilesCards() {
	for (uint16_t i = 0; i < CARDS_TOTAL; i++) {
		cout << setiosflags(ios::left) << setw(3) << i << "." 
			<<setiosflags(ios::left)  <<setw(10) <<m_piles_cards[i].name << "  :"
			<< setiosflags(ios::left) << setw(4) <<m_piles_cards[i].points << "   ";
		if ((i+1) % 5 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}

bool GameData::setRoleCount(uint16_t role_count) {
	m_roleCount = role_count;
	return true;
}

bool GameData::generateStatus(uint16_t role_count, uint16_t *roles_status) {
	memset(roles_status, 0, sizeof(uint16_t)*role_count);
	STATUSINFOMANAGEMENT status_man;

	STATUSINFO* status_info = status_man.findCardByNum(role_count);
	if (status_info == NULL) {
		return false;
	}

	uint16_t master = status_info->master;
	uint16_t loyal = status_info->loyal;
	uint16_t guilty = status_info->guilty;
	uint16_t rebel = status_info->rebel;

	for (uint16_t i = 0; i < role_count; i++) {
		srand((unsigned)time(NULL));
		int num = rand() % role_count;
		
		while (roles_status[num] != 0 && num < role_count
			&& (master != 0 || loyal != 0 || guilty != 0 || rebel != 0)) {
			if (num + 1 == role_count) {
				num = 0;
			}
			else {
				num++;
			}
		}

		if (master != 0) {
			roles_status[num] = STATUS_MASTER;
			--master;
		}
		else if (loyal != 0) {
			roles_status[num] = STATUS_LOYAL;
			--loyal;
		}
		else if (guilty != 0) {
			roles_status[num] = STATUS_GUILTY;
			--guilty;
		}
		else if (rebel != 0) {
			roles_status[num] = STATUS_REBEL;
			--rebel;
		}
	}
	return true;
}

bool GameData::generateRoles(uint16_t role_status, uint16_t *roles_identity) {
	ROLESINFOMANAGEMENT role_man;

	uint16_t role_count = role_man.count();
	for (uint16_t i = 0; i < m_roleCount * ROLES_CHOOSE_NUM; i++) {
		roles_identity[i] = rand() % role_count;
	}
	return true;
}

bool sameNameCopy(CLICARDS *cli_cards, CARDSINFO *card_info) {
	cli_cards->id = card_info->id;
	cli_cards->category = card_info->category;
	cli_cards->distance = card_info->distance;
	cli_cards->hurt = card_info->hurt;
	cli_cards->name = card_info->name;
	cli_cards->range = card_info->range;
	cli_cards->recover = card_info->recover;
	cli_cards->type = card_info->type;
	return true;
}

bool GameData::shuffleCards() {
	CARDSINFOMANAGEMENT cards_man;
	uint32_t cards_count = cards_man.count();

	uint16_t spade_count = 0;
	uint16_t plum_count = 0;
	uint16_t heart_count = 0;
	uint16_t diamond_count = 0;
	CARDSINFO * card_info = NULL;

	for (uint32_t i = 0, j = 0; i < CARDS_TOTAL, j < cards_count; i++) {
		if (spade_count == 0 && plum_count == 0 && heart_count == 0 && diamond_count == 0) {
			card_info = cards_man.at(j++);
			if (card_info == NULL) {
				return false;
			}
			spade_count = card_info->spade_num;
			plum_count = card_info->plum_num;
			heart_count = card_info->heart_num;
			diamond_count = card_info->diamond_num;
		}

		srand((unsigned)time(NULL));
		int num = rand() % CARDS_TOTAL;

		while (m_piles_cards[num].id != 0 && num < CARDS_TOTAL
			&& (spade_count != 0 || plum_count != 0 || heart_count != 0 || diamond_count != 0)) {
			if (num + 1 == CARDS_TOTAL) {
				num = 0;
			}
			else {
				num++;
			}
		}

		if (spade_count != 0) {
			sameNameCopy(&m_piles_cards[num], card_info);
			m_piles_cards[num].color = CARDS_COLOR_SPADE;
			m_piles_cards[num].points = card_info->spade[--spade_count];
		}
		else if (plum_count != 0) {
			sameNameCopy(&m_piles_cards[num], card_info);
			m_piles_cards[num].color = CARDS_COLOR_PLUM;
			m_piles_cards[num].points = card_info->plum[--plum_count];
		}
		else if (heart_count != 0) {
			sameNameCopy(&m_piles_cards[num], card_info);
			m_piles_cards[num].color = CARDS_COLOR_HEART;
			m_piles_cards[num].points = card_info->heart[--heart_count];
		}
		else if (diamond_count != 0) {
			sameNameCopy(&m_piles_cards[num], card_info);
			m_piles_cards[num].color = CARDS_COLOR_DIAMOND;
			m_piles_cards[num].points = card_info->diamond[--diamond_count];
		}
		m_cards_count ++;
		if (m_cards_count == CARDS_TOTAL) {
			break;
		}
	}
	return true;
}