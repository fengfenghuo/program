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
			<< setiosflags(ios::left) << setw(10) << m_piles_cards[i].name << "  :"
			<< setiosflags(ios::left) << setw(4) << m_piles_cards[i].points << "   ";
		if ((i + 1) % 5 == 0) {
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
		m_cards_count++;
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

uint16_t GameData::roleAliveNum() {
	uint16_t num = 0;
	for (uint16_t i = 0; i < m_roleCount; i++) {
		if (m_players[i].isplayerAlive()) {
			num++;
		}
	}
	return num;
}

int GameData::applyCardPlay(CLICARDS *card, uint16_t role_num) {
	if (card == NULL) {
		return ERROR_SYSTEM_ERROR;
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
				int role = chooseTarget(m_players[role_num].damageRange(), role_num, false);
				if (applyDamage(CARD_SHA, role_num, (uint16_t)role) == 0) {
					return 0;
				}
				else {
					cout << m_players[role].playerRoleName() << "没有响应【杀】~~" << endl;
					if (m_players[role].playerBloodReduce()) {
						return 0;
					}
					return ERROR_SYSTEM_ERROR;
				}
			}
			break;
		}
		case CARD_TAO: {
			if (m_players[role_num].playerBloodAdd()) {
				return 0;
			}
			return ERROR_SYSTEM_ERROR;
		}
		default:
			break;
		}
	}
	else if (card->category == CARDS_CATEGORY_STRATEGY) {
		switch (card->id)
		{
		case CARD_GUOHECHAIQIAO: {
			if (m_players[role_num].isRoleRobot()) {
				//robot
			}
			else {
				cout << "你出了张【过河拆桥】，请选择【过河拆桥】的目标:" << endl;
				int role = chooseTarget(m_roleCount, role_num, false);
				if (applyCardRemove(CARD_GUOHECHAIQIAO, role_num, (uint16_t)role) == 0) {
					return 0;
				}
				cout << "谁知道你出了什么错！" << endl;
				return ERROR_SYSTEM_ERROR;
			}
			break;
		}
		case CARD_SHUNSHOUQIANYANG: {
			if (m_players[role_num].isRoleRobot()) {
				//robot
			}
			else {
				cout << "你出了张【顺手牵羊】，请选择【顺手牵羊】的目标:" << endl;
				int role = chooseTarget(m_players[role_num].isHorseMinus() ? 2 : 1, role_num, false);
				if (applyCardRemove(CARD_SHUNSHOUQIANYANG, role_num, (uint16_t)role) == 0) {
					return 0;
				}
				else if(role < 0){
					cout << "没有【顺手牵羊】的目标~gg" << endl;
					return 0;
				}
				cout << "谁知道你出了什么错！" << endl;
				return ERROR_SYSTEM_ERROR;
			}
			break;
		}
		case CARD_JUEDOU: {
			if (m_players[role_num].isRoleRobot()) {
				//robot
			}
			else {
				cout << "你出了张【决斗】，请选择【决斗】的目标:" << endl;
				int role = chooseTarget(m_roleCount, role_num, false);
				if (role < 0) {
					cout << "选的啥目标还没有的~gg" << endl;
					return ERROR_SYSTEM_ERROR;
				}
				int index = applyCardDuel(role_num, role);
				if (index = ERROR_NO_RESPONSE) {
					m_players[role].playerBloodReduce();
				}
				else if (index = ERROR_NO_ACTIVE) {
					m_players[role_num].playerBloodReduce();
				}
				else {
					return ERROR_SYSTEM_ERROR;
				}
			}
			break;
		}
		case CARD_JIEDAOSHAREN: {
			if (m_players[role_num].isRoleRobot()) {
				//robot
			}
			else {
				cout << "你出了张【借到杀人】，请选择【借到杀人】的使用目标:" << endl;
				int role_source = chooseTarget(m_roleCount, role_num, true);
				if (role_source < 0) {
					cout << "选的啥目标还没有的~gg" << endl;
					return ERROR_SYSTEM_ERROR;
				}

				cout << "请选择【杀】的目标:" << endl;
				int role_target = chooseTarget(m_players[role_source].damageRange(), role_num, false);
				if (role_target < 0) {
					cout << "选的啥目标还没有的~gg" << endl;
					return ERROR_SYSTEM_ERROR;
				}

				if (m_players[role_source].isRoleRobot()) {
					if (!m_players[role_source].isCard_Sha()) {
						CLICARDS *card = m_players[role_source].equipWeapon();
						if (card == NULL) {
							cout << "出大錯了" << endl;
							return ERROR_SYSTEM_ERROR;
						}
						if (!m_players[role_num].drowCards(card, 1)) {
							return ERROR_SYSTEM_ERROR;
						}
						return 0;
					}

					m_players[role_source].discardCards((uint32_t)CARD_SHA);
				}
				else {
					cout << m_players[role_num].playerRoleName() << "对" << m_players[role_source].playerRoleName() << "  使用【借刀杀人】 杀  " << m_players[role_target].playerRoleName() << "  是否出【杀】" << endl;
					int index = applyPlayCard(CARD_SHA, role_target);
					if (index < 0) {
						return ERROR_SYSTEM_ERROR;
					}
					m_players[role_source].discardCards((uint16_t)index);
				}

				if (applyDamage(CARD_SHA, role_source, role_target) != 0) {
					cout << m_players[role_target].playerRoleName() << "没有响应【杀】~~" << endl;
					if (m_players[role_target].playerBloodReduce()) {
						return 0;
					}
					return ERROR_SYSTEM_ERROR;
				}
				return 0;
			}
			break;
		}
		case CARD_WUZHONGSHENGYOU: {
			CLICARDS card[CARDS_DEALS] = {0};
			if (!dealCards(CARDS_DEALS, card)) {
				cout << "发牌也会出错？" << endl;
				return ERROR_SYSTEM_ERROR;
			}
			m_players[role_num].drowCards(card, CARDS_DEALS);
			return 0;
		}
		case CARD_WANGJIANQIFA: 
		case CARD_NANMANRUQIN: {
			if (applyDamageAll(card->id, role_num) != 0) {
				return ERROR_SYSTEM_ERROR;
			}
			return 0;
		}
		case CARD_TAOYUANJIEYI: {
			for (uint16_t i = 0; i < m_roleCount; i++) {
				m_players[i].playerBloodAdd();
			}
			return 0;
		}
		case CARD_WUGUFENGDENG: {
			uint16_t card_num = roleAliveNum();
			CLICARDS cards[ROLES_MAX_NUM] = { 0 };
			if (!dealCards(card_num, cards)) {
				cout << "发牌出错啦" << endl;
				return ERROR_SYSTEM_ERROR;
			}
			return applyCardDeals(card_num, cards);
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
int GameData::chooseTarget(uint16_t distance, uint16_t role_num, bool need_weapon) {
	uint16_t num = 0;
	uint16_t roles[ROLES_MAX_NUM] = { 0 };

	for (uint16_t i = 0; i < m_roleCount; i++) {
		uint16_t dis = (i > m_roleCount / 2) ? abs(role_num + m_roleCount - i) : abs(role_num - i);

		dis += m_players[i].isHorsePlus() ? 1 : 0;

		bool requir = true;
		if (need_weapon) {
			requir = m_players[role_num].equipWeapon() && requir;
		}

		if (dis < distance && requir) {
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
	return ERROR_SYSTEM_ERROR;
}

int GameData::applyDamage(uint32_t card_id, uint16_t source_num, uint16_t target_num) {
	if (target_num >= m_roleCount || source_num >= m_roleCount) {
		return ERROR_SYSTEM_ERROR;
	}

	if (!m_players[target_num].isCard_Shan()) {
		return ERROR_NO_RESPONSE;
	}

	int index = -1;
	if (!m_players[target_num].isRoleRobot()) {
		cout << m_players[source_num].playerRoleName();
		cout << "  对你出【杀】，是否出【闪】？" << endl;
		index = applyPlayCard(card_id, target_num);
	}
	else {
		index = m_players[target_num].curCardIndex(card_id);
	}

	if (index >= 0) {
		cout << m_players[source_num].playerRoleName() << "  出了【闪】~" << endl;
		m_players[target_num].discardCards((uint16_t)index);
		return 0;
	}
	return ERROR_SYSTEM_ERROR;
}

int GameData::applyDamageAll(uint32_t card_id, uint16_t source_num) {
	if (source_num >= m_roleCount) {
		return ERROR_SYSTEM_ERROR;
	}

	for (uint16_t i = 0; i < m_roleCount; i++) {
		if (i == source_num) continue;

		if (!m_players[i].isRoleRobot()) {
			int index = -1;
			if (card_id == CARD_WANGJIANQIFA) {
				cout << m_players[source_num].playerRoleName() << "出了张【万箭齐发】，是否出【闪】？" << endl;
				index = applyPlayCard(CARD_SHAN, i);
			}
			else if (card_id == CARD_NANMANRUQIN) {
				cout << m_players[source_num].playerRoleName() << "出了张【南蛮入侵】，是否出【杀】？" << endl;
				index = applyPlayCard(CARD_SHA, i);
			}

			if (index < 0) {
				return ERROR_SYSTEM_ERROR;
			}
			cout << m_players[i].playerRoleName() << "  出了一张牌~" << endl;
			m_players[i].discardCards((uint16_t)index);
		}
		else {
			if (card_id == CARD_WANGJIANQIFA) {
				if (!m_players[i].isCard_Shan()) {
					m_players[i].playerBloodReduce();
				}
				else {
					m_players[i].discardCards((uint32_t)CARD_SHAN);
				}
			}
			else if (card_id == CARD_NANMANRUQIN) {
				if (!m_players[i].isCard_Sha()) {
					m_players[i].playerBloodReduce();
				}
				else {
					m_players[i].discardCards((uint32_t)CARD_SHA);
				}
			}
		}
	}
	
	return 0;
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
		else if (index == CARDS_MAX_NUM) {
			return ERROR_NO_ACTIVE;
		}
		else {
			CARDSINFOMANAGEMENT card_man;
			CARDSINFO * card_info = card_man.findCardById(card_id);
			if (card_info && in_str == card_info->name && m_players[target_num].curCardIndex(in_str) >= 0) {
				return m_players[target_num].curCardIndex(in_str);
			}
			else {
				cout << "输入错误请重新输入！！！" << endl;
			}
		}
	}
	return ERROR_SYSTEM_ERROR;
}

int GameData::applyCardRemove(uint32_t card_id, uint16_t source_num, uint16_t target_num) {
	if (target_num >= m_roleCount || source_num >= m_roleCount) {
		return ERROR_SYSTEM_ERROR;
	}

	uint16_t cur_card_num = m_players[target_num].cardCurNum();
	uint16_t equip_card_num = m_players[target_num].cardEquipNum();
	uint16_t judge_card_num = m_players[target_num].cardJudgeNum();

	cout << "手牌 ：" << endl;
	m_players[target_num].viewCurCards();
	cout << "装备牌 ：" << endl;
	m_players[target_num].viewEquipCards(true, cur_card_num);
	cout << "判定牌 ：" << endl;
	m_players[target_num].viewJudgementCards(true, cur_card_num + equip_card_num);

	uint16_t in_str = 0;
	while (true) {
		cout << "请选择您的目标牌~(0~" << cur_card_num + equip_card_num + judge_card_num - 1;
		cout << ")" << endl;
		cin >> in_str;

		if (in_str >= cur_card_num + equip_card_num + judge_card_num) {
			cout << "你啥眼神？哪有这个牌，请重新输入~" << endl;
		}
	}

	if (in_str < cur_card_num) {
		CLICARDS * card = m_players[target_num].discardCards(in_str);
		if (card == NULL) {
			cout << "咋的弃错牌了呢" << endl;
			return ERROR_SYSTEM_ERROR;
		}

		if (card_id == CARD_SHUNSHOUQIANYANG) {
			return m_players[source_num].drowCards(card, 1) ? 0 : ERROR_SYSTEM_ERROR;
		}
		return 0;
	}
	else if (in_str >= cur_card_num && in_str < cur_card_num + equip_card_num) {
		CLICARDS * card = m_players[target_num].discardEquipCards((uint16_t)(in_str - cur_card_num));
		if (card == NULL) {
			cout << "咋的弃错装备牌了呢" << endl;
			return ERROR_SYSTEM_ERROR;
		}

		if (card_id == CARD_SHUNSHOUQIANYANG) {
			return m_players[source_num].drowCards(card, 1) ? 0 : ERROR_SYSTEM_ERROR;
		}
		return 0;
	}
	else if (in_str >= cur_card_num + equip_card_num && in_str < cur_card_num + equip_card_num + judge_card_num) {
		CLICARDS * card = m_players[target_num].discardJudgementCards((uint16_t)(in_str - cur_card_num - equip_card_num));
		if (card == NULL) {
			cout << "咋的弃错判定牌了呢" << endl;
			return ERROR_SYSTEM_ERROR;
		}

		if (card_id == CARD_SHUNSHOUQIANYANG) {
			return m_players[source_num].drowCards(card, 1) ? 0 : ERROR_SYSTEM_ERROR;
		}
		return 0;
	}
	else {
		cout << "你选了个什么牌？" << endl;
		return ERROR_SYSTEM_ERROR;
	}

	return ERROR_SYSTEM_ERROR;
}

int GameData::applyCardDuel(uint16_t source_num, uint16_t target_num) {
	if (target_num >= m_roleCount || source_num >= m_roleCount) {
		return ERROR_SYSTEM_ERROR;
	}

	while (m_players[target_num].isCard_Sha() && m_players[source_num].isCard_Sha()) {
		if (m_players[target_num].isRoleRobot()) {
			m_players[target_num].playCards((uint32_t)CARD_SHA);
		}
		else {
			cout << m_players[source_num].playerRoleName() << "对你使用了【决斗】，请出【杀】~" << endl;
			int index = applyPlayCard(CARD_SHA, target_num);
			if (index >= 0) {
				m_players[target_num].discardCards((uint16_t)index);
			}
			else {
				return ERROR_NO_RESPONSE;
			}
		}

		cout << m_players[target_num].playerRoleName() << "出了一张【杀】！" << endl;

		if (m_players[source_num].isRoleRobot()) {
			m_players[source_num].playCards((uint32_t)CARD_SHA);
		}
		else {
			cout << "您需要出一张【杀】，是否出【杀】？" << endl;
			int index = applyPlayCard(CARD_SHA, source_num);
			if (index >= 0) {
				m_players[source_num].discardCards((uint16_t)index);
			}
			else {
				return ERROR_NO_ACTIVE;
			}
		}
		cout << m_players[source_num].playerRoleName() << "出了一张【杀】！" << endl;
	}

	if (m_players[target_num].isCard_Sha() && !m_players[source_num].isCard_Sha()) {
		cout << m_players[target_num].playerRoleName() << "不再响应出【杀】！" << endl;
		return ERROR_NO_ACTIVE;
	}

	if (!m_players[target_num].isCard_Sha() && m_players[source_num].isCard_Sha()) {
		cout << m_players[source_num].playerRoleName() << "不再响应出【杀】！" << endl;
		return ERROR_NO_RESPONSE;
	}
	return ERROR_SYSTEM_ERROR;
}

int GameData::applyCardDeals(uint16_t cards_count, CLICARDS * cards) {
	int signal[ROLES_MAX_NUM] = { 0 };

	for (uint16_t i = 0; i < m_roleCount; i++) {
		for (uint16_t j = 0; j < cards_count; j++) {
			if (signal[j] == 0) {
				cout << "[" << j << "]  " << cards[j].name << "(" << viewCardColor(cards[j].points, cards[j].color) << ")" << endl;
			}
		}
		int index = -1;
		if (!m_players[i].isplayerAlive()) continue;
		if (m_players[i].isRoleRobot()) {
			//robot
		}
		else {
			cout << "请选择您的牌~" << endl;
			string in_str;
			while (true) {
				cout << "请选择要出的卡牌!" << endl;
				cin >> in_str;
				index = strToInt(in_str);
				if (signal[index] != 0) {
					cout << "该牌已被选取，请重新选择" << endl;
				}
			}
		}
		if (index == -1) {
			cout << "选牌出错了" << endl;
			continue;
		}
		m_players[i].drowCards(&cards[index], 1);
		signal[index] = 1;
	}
	return 0;
}