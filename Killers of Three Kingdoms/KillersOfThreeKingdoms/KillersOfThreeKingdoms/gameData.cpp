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

GameData::GameData(uint16_t role_count) {
	m_roleCount = role_count;
	m_players = new PlayerData[role_count];
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

bool GameData::dealCards(uint16_t cards_count, CLICARDS * cards) {
	for (uint16_t i = 0; i < cards_count; i++) {
		memcpy(&cards[i], &m_piles_cards[--m_cards_count], sizeof(CLICARDS));
	}
	return true;
}

int GameData::applyCardPlay(CLICARDS *card, uint16_t role_num) {
	if (card == NULL) {
		return -1;
	}

	if (card->category == CARDS_CATEGORY_BASIC) {
		switch (card->id)
		{
		case CARD_SHA: {
			if (m_players[role_num].isRoleRobot()) {
				//robot
			}
			else {
				cout << "你出了张【杀】，请选择【杀】的目标:" << endl;
				int role = chooseTarget(m_players[role_num].damageRange(), role_num);
				if (applyDamage(CARD_SHA, role_num, (uint16_t)role) == 0) {
					return 0;
				}
				else {
					cout << m_players[role].playerRoleName() << "没有响应【杀】~~" << endl;
					if (m_players[role].playerBloodReduce()) {
						return 0;
					}
					return -1;
				}
			}
			break;
		}
		case CARD_TAO: {
			if (m_players[role_num].playerBloodAdd()) {
				return 0;
			}
			return -1;
		}
		default:
			break;
		}
	}
	else if (card->category == CARDS_CATEGORY_STRATEGY) {
		switch (card->id)
		{
		case CARD_GUOHECHAIQIAO: {
			break;
		}
		default:
			break;
		}
	}
	else if (card->category == CARDS_CATEGORY_STRATEGY_DELAY) {
		switch (card->id)
		{
		default:
			break;
		}
	}
	else if (card->category == CARDS_CATEGORY_EQUIPMENT_WEAPON) {
		switch (card->id)
		{
		default:
			break;
		}
	}
	else if (card->category == CARDS_CATEGORY_EQUIPMENT_ARMOR) {
		switch (card->id)
		{
		default:
			break;
		}
	}
	else if (card->category == CARDS_CATEGORY_EQUIPMENT_HORSE_PLUS) {
		switch (card->id)
		{
		default:
			break;
		}
	}
	else if (card->category == CARDS_CATEGORY_EQUIPMENT_HORSE_MINUS) {
		switch (card->id)
		{
		default:
			break;
		}
	}
}

////////////////////////////////
int GameData::chooseTarget(uint16_t distance, uint16_t role_num) {
	uint16_t num = 0;
	uint16_t roles[ROLES_MAX_NUM] = {0};

	for (uint16_t i = 0; i < m_roleCount; i++) {
		uint16_t dis = (i > m_roleCount / 2) ? abs(role_num + m_roleCount - i) : abs(role_num - i);

		dis += m_players[i].isHorsePlus() ? 1 : 0;

		if (dis < distance) {
			roles[num++] = i;
		}
	}

	for (uint16_t i = 0; i < num; i++) {
		cout << "[" << i << "]  " << m_players[roles[i]].playerRoleName() << endl;
	}

	string in_str;
	while (true) {
		cout << "请选择目标~: ";
		cin >> in_str;

		int index = strToInt(in_str);
		if (index >= 0 && index < num) {
			return index;
		}
		else {
			for (uint16_t i = 0; i < num; i++) {
				if (in_str == m_players[roles[i]].playerRoleName()) {
					return roles[i];
				}
			}
			cout << "目标错误请重新输入~" << endl;
		}
	}
	return -1;
}

int GameData::applyDamage(uint32_t card_id, uint16_t source_num, uint16_t target_num) {
	if (target_num >= m_roleCount || source_num >= m_roleCount) {
		return -1;
	}

	if (!m_players[target_num].isCard_Shan()) {
		return -1;
	}

	int index = -1;
	if (!m_players[target_num].isRoleRobot()) {
		cout << m_players[source_num].playerRoleName();
		cout << "  对你出【杀】，是否出【闪】？" << endl;
		m_players[target_num].viewCurCards(true);
		index = applyPlayCard(card_id, target_num);
	}
	else {
		index = m_players[target_num].curCardIndex(card_id);
	}

	if (index >= 0) {
		cout << m_players[source_num].playerRoleName() << "  出了【闪】~" << endl;
		m_players[target_num].playCards((uint16_t)index);
		return 0;
	}
	return -1;
}

int GameData::applyPlayCard(uint32_t card_id, uint16_t target_num) {
	m_players[target_num].viewCurCards(true);
	cout << "[99]. 不出牌" << endl;
	string in_str = 0;
	while (true) {
		cout << "请选择要出的卡牌!" << endl;
		cin >> in_str;
		int index = strToInt(in_str);
		if (m_players[target_num].curCardId(index) == card_id) {
			return index;
		}
		else if(index == CARDS_MAX_NUM){
			return -1;
		}
		else {
			CARDSINFOMANAGEMENT card_man;
			CARDSINFO * card_info = card_man.findCardById(card_id);
			if (card_info && in_str == card_info->name && m_players[target_num].curCardIndex(in_str) >= 0){
				return m_players[target_num].curCardIndex(in_str);
			}
			else {
				cout << "输入错误请重新输入！！！" << endl;
			}
		}
	}
	return -1;
}