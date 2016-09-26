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
	m_role_cur_count = m_roleCount;
	memset(m_piles_disvards, 0, sizeof(CLICARDS)*CARDS_TOTAL);
}

GameData::GameData(uint16_t role_count) {
	m_roleCount = role_count;
	m_role_cur_count = m_roleCount;
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
			<< setiosflags(ios::left) << setw(10) << m_piles_cards[i].name << m_piles_cards[i].id << "  :"
			<< setiosflags(ios::left) << setw(4) << m_piles_cards[i].points << "   ";
		if ((i + 1) % 5 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}

void GameData::viewPlayersStatus() {
	for (uint16_t i = 0; i < m_roleCount; i++) {
		cout << "[" << i << "]. " << m_players[i].playerRoleName() << "***" << viewRoleStatus(m_players[i].playerRoleStatus());
		cout << "   ��ݺţ�" << m_players[i].playerRoleNum() << "   �����ˣ�" << m_players[i].isRoleRobot() << endl;
	}
	cout << endl;
}

void GameData::viewRoleInfo(ROLESINFO * role) {
	cout << setiosflags(ios::left) << setw(5) << "���֣�" << setw(8) << role->name;
	cout << setiosflags(ios::left) << setw(5) << "  ������" << setw(3) << role->blood;
	cout << setiosflags(ios::left) << setw(5) << "  ������" << setw(3) << role->power << endl;

	for (uint16_t i = 0; i < role->skill_num; i++) {
		cout << setiosflags(ios::left) << setw(5) << "���ܣ�" << i + 1;
		cout << role->skill[i] << endl;
	}
	cout << endl;
}

void GameData::viewPlayersRole() {
	for (uint16_t i = 0; i < m_roleCount; i++) {
		cout << "��" << i << "��" << "��λ" << endl;
		m_players[i].viewRoleCard();
	}
}

void GameData::viewPlayerCards(uint16_t role_num) {
	cout << "����ƣ�" << endl;
	m_players[role_num].viewCurCards();
	m_players[role_num].viewEquipCards();
	m_players[role_num].viewJudgementCards();
}

/////////////////////////////////////////////////
uint16_t GameData::curRoleCount() {
	return m_role_cur_count;
}
/////////////////////////////////////////////////

bool GameData::setRoleCount(uint16_t role_count) {
	m_roleCount = role_count;
	return true;
}
PLAYERINFO* GameData::findPlayerInfoByNum(uint16_t role_num) {
	for (uint16_t i = 0; i < m_roleCount; i++) {
		if (m_players[i].playerRoleNum() == role_num) {
			return m_players[i].playerInfo();
		}
	}
	return NULL;
}

int GameData::generateStatus(uint16_t role_count) {
	uint16_t *roles_status = new uint16_t[role_count];

	memset(roles_status, 0, sizeof(uint16_t)*role_count);
	STATUSINFOMANAGEMENT status_man;

	STATUSINFO* status_info = status_man.findCardByNum(role_count);
	if (status_info == NULL) {
		return ERROR_SYSTEM_ERROR;
	}

	uint16_t master = status_info->master;
	uint16_t loyal = status_info->loyal;
	uint16_t guilty = status_info->guilty;
	uint16_t rebel = status_info->rebel;

	srand((unsigned)time(NULL));
	for (uint16_t i = 0; i < role_count; i++) {
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

	int player_statue = rand() % (status_info->loyal + status_info->guilty > 0 ? STATUS_NUM : STATUS_MIN_NUM) + 1;
	bool only_signal = true;

	uint16_t j = 0;
	while (roles_status[j] != STATUS_MASTER) {
		j++;
	}

	for (uint16_t i = 0; i < role_count; i++) {
		bool is_robot = true;
		if ((uint16_t)player_statue == roles_status[j] && only_signal == true) {
			player_statue = i;
			is_robot = false;
			only_signal = false;
		}

		if (!m_players[i].setRoleStatus(roles_status[j], j, is_robot)) {
			cout << "������ݴ���~" << endl;
			return ERROR_SYSTEM_ERROR;
		}
		j++;
		if (j == role_count) {
			j = 0;
		}
	}
	delete[]roles_status;
	return player_statue;
}

bool GameData::generateRoles() {
	ROLESINFOMANAGEMENT role_man;
	char roles[ROLES_TOTAL] = { 0 };
	uint16_t *roles_identity = new uint16_t[m_roleCount * ROLES_CHOOSE_NUM];

	uint16_t role_count = role_man.count();
	for (uint16_t i = 0; i < m_roleCount * ROLES_CHOOSE_NUM; i++) {
		uint16_t num = rand() % role_count + 1;
		while (roles[num - 1] == 1) {
			num = rand() % role_count + 1;
		}
		roles_identity[i] = num;
		roles[num - 1] = 1;
	}

	for (uint16_t j = 0; j < m_roleCount; j++) {
		ROLESINFO * role = NULL;
		if (m_players[j].isRoleRobot()) {
			uint16_t num = rand() % ROLES_CHOOSE_NUM + j * ROLES_CHOOSE_NUM;
			role = role_man.findRoleByIdentity(roles_identity[num]);
			if (role == NULL) {
				return false;
			}
			//m_players[j].setRoleInfo(role);
		}
		else {
			for (uint16_t k = 0; k < ROLES_CHOOSE_NUM; k++) {
				role = role_man.findRoleByIdentity(roles_identity[j * ROLES_CHOOSE_NUM + k]);
				if (role == NULL) continue;
				cout << "[" << k << "]" << endl;
				viewRoleInfo(role);
			}
			uint16_t in_num;

			while (true) {
				cout << "��ѡ���Ӧ��Ӣ�۱�ţ�";
				cin >> in_num;

				if (in_num < 0 && in_num >= ROLES_CHOOSE_NUM) {
					cout << "����������������룺";
				}
				else {
					break;
				}
			}

			role = role_man.findRoleByIdentity(roles_identity[j * ROLES_CHOOSE_NUM + in_num]);
			if (role == NULL) {
				return false;
			}
		}

		m_players[j].setRoleInfo(role);
	}

	delete[]roles_identity;
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

	srand((unsigned)time(NULL));

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

bool GameData::dealCards(uint16_t cards_count, uint16_t role_num) {
	if (m_cards_count < cards_count) {
		if (!shuffleCards()) {
			cout << "ϴ�Ƴ���Ŷ��" << endl;
			return false;
		}
	}

	bool success = m_players[role_num].drowCards(&m_piles_cards[m_cards_count - cards_count], cards_count);
	if (!success) {
		return false;
	}

	m_cards_count -= cards_count;
	return true;
}

bool GameData::dealCards(uint16_t cards_count, CLICARDS *cards) {
	if (m_cards_count < cards_count) {
		if (!shuffleCards()) {
			cout << "ϴ�Ƴ���Ŷ��" << endl;
			return false;
		}
	}

	for (uint16_t i = 0; i < cards_count; i++) {
		memcpy(cards, &m_piles_cards[--m_cards_count], sizeof(CLICARDS) * cards_count);
	}
	return true;
}

CLICARDS * GameData::playCards(uint16_t role_num) {
	if (m_players[role_num].roleCurState() != GAME_STAGE_PLAY) {
		cout << "���ܳ��ƣ��������ƽ׶�~" << endl;
		return NULL;
	}

	if (m_players[role_num].isRoleRobot()) {
		//robot
	}
	else {
		string in_str;
		while (true) {
			m_players[role_num].viewCurCards(true);
			m_players[role_num].viewEquipCards(false);
			m_players[role_num].viewJudgementCards(false);
			cout << "[99]. ������" << endl;
			cout << "��ĳ���ʱ�䣬��ѡ��Ҫ�����ƣ�";
			cin >> in_str;
			int index = strToInt(in_str);
			if (index >= 0 && index < ERROR_TARGET_ERROR) {
				return m_players[role_num].playCards((uint16_t)index);
			}
			else if (index == ERROR_TARGET_ERROR) {
				m_players[role_num].setRoleCurState(GAME_STAGE_DISCARDS);
				break;
			}
			else {
				int num = m_players[role_num].curCardIndex(in_str);
				if (num >= 0) {
					return m_players[role_num].playCards((uint16_t)num);
				}
				cout << "�����������������~" << endl;
			}
		}
	}
	return NULL;
}

CLICARDS * GameData::discardCards(uint16_t role_num) {
	if (m_players[role_num].isRoleRobot()) {
		//robot
		int i = m_players[role_num].cardCurNum();
		while (m_players[role_num].cardCurNum() > m_players[role_num].roleCurBlood()) {
			m_players[role_num].discardCards((uint16_t)--i);
		}
	}
	else {
		string in_str;
		while (m_players[role_num].cardCurNum() > m_players[role_num].roleCurBlood()) {
			m_players[role_num].viewCurCards(true);
			cout << "��ѡ��Ҫ�����ƣ�";
			cin >> in_str;
			int index = strToInt(in_str);
			if (index >= 0 && index < m_players[role_num].cardCurNum()) {
				return m_players[role_num].discardCards((uint16_t)index);
			}
			else {
				if (m_players[role_num].discardCards(in_str) == NULL) {
					cout << "�����������������~" << endl;
				}
			}
		}
	}
	return NULL;
}

int GameData::judgeCards(uint16_t role_num) {
	m_players[role_num].setRoleCurState(GAME_STAGE_PLAY);

	if (m_players[role_num].isJudgeCardEmpty()) {
		return 0;
	}

	for (uint16_t j = 0; j < m_players[role_num].cardJudgeNum(); j++) {
		CLICARDS * judge_card = m_players[role_num].judgeCardByIndex(j);
		if (judge_card == NULL) {
			cout << "û�ҵ�����ж��ƣ�~" << endl;
			return ERROR_SYSTEM_ERROR;
		}

		CLICARDS cards[ROLES_MAX_NUM] = { 0 };
		if (!dealCards(1, cards)) {
			cout << "���Ƴ�����~" << endl;
			return ERROR_SYSTEM_ERROR;
		}

		m_players[role_num].discardJudgementCards(j);

		if (judge_card->id == CARD_SHANDIAN) {
			if (cards[0].color == CARDS_COLOR_SPADE && cards[0].points >= 2 && cards[0].points <= 9) {
				cout << m_players[role_num].playerRoleName() << " �ж������硿 ����" << endl;
				return playerBloodReduce(role_num);
			}
			cout << m_players[role_num].playerRoleName() << " �ж������硿 ������" << endl;
			int i = 0;
			if (role_num + 1 < m_roleCount) {
				i = role_num + 1;
			}
			while (!m_players[i].isRoleAlive()) {
				i++;
			}
			m_players[i].judgementCard(judge_card);
			return 0;
		}

		if (judge_card->id == CARD_LEBUSISHU) {
			if (cards[0].color == CARDS_COLOR_HEART) {
				cout << m_players[role_num].playerRoleName() << " �ж����ֲ�˼�� ������" << endl;
				return 0;
			}
			cout << m_players[role_num].playerRoleName() << " �ж����ֲ�˼�� �������������ƽ׶�" << endl;
			m_players[role_num].setRoleCurState(GAME_STAGE_DISCARDS);
			return 0;
		}
	}
	return 0;
}

uint16_t GameData::roleAliveNum() {
	uint16_t num = 0;
	for (uint16_t i = 0; i < m_roleCount; i++) {
		if (m_players[i].isRoleAlive()) {
			num++;
		}
	}
	return num;
}

bool GameData::playerStartToPlay(uint16_t role_num) {
	return m_players[role_num].setRoleCurState(GAME_STAGE_JUDGE);
}

bool GameData::playerEndToPlay(uint16_t role_num) {
	return m_players[role_num].setRoleCurState(GAME_STAGE_END);
}

bool GameData::startingCards() {
	for (uint16_t i = 0; i < m_roleCount; i++) {
		bool success = m_players[i].drowCards(&m_piles_cards[CARDS_TOTAL - CARDS_STARTING - i * CARDS_STARTING], CARDS_STARTING);
		if (!success) {
			cout << i << "��λ��ȡ��ʼ���ƴ���" << endl;
			continue;
		}
		m_cards_count -= CARDS_STARTING;
	}
	return true;
}

bool GameData::endingCondition(uint16_t role_num) {
	bool rebel_alive = false;
	bool guilty_alive = false;
	for (uint16_t i = 1; i < m_roleCount; i++) {
		if (m_players[i].playerRoleStatus() == STATUS_REBEL && m_players[i].isRoleAlive()) {
			rebel_alive = true;
		}
		if (m_players[i].playerRoleStatus() == STATUS_GUILTY && m_players[i].isRoleAlive()) {
			guilty_alive = true;
		}
	}

	if (m_players[0].isRoleAlive()) {
		if (rebel_alive || guilty_alive) {
			return false;
		}

		cout << "�������ʤ��~" << endl;
		if (m_players[role_num].playerRoleStatus() == STATUS_MASTER || m_players[role_num].playerRoleStatus() == STATUS_LOYAL) {
			cout << "��ϲ�����������ӪӮ����ʤ��������" << endl;
		}
		else {
			cout << "���ź������������Ӫ���ˣ��ٽ�����������" << endl;
		}
		return true;
	}
	else {
		if (rebel_alive) {
			cout << "�������ʤ��~" << endl;
			if (m_players[role_num].playerRoleStatus() == STATUS_MASTER || m_players[role_num].playerRoleStatus() == STATUS_LOYAL) {
				cout << "���ź������������Ӫ���ˣ��ٽ�����������" << endl;
			}
			else {
				cout << "��ϲ�����������ӪӮ����ʤ��������" << endl;
			}
			return true;
		}

		if (guilty_alive && !rebel_alive) {
			cout << "�ڼ���ʤ��~" << endl;
			if (m_players[role_num].playerRoleStatus() == STATUS_GUILTY) {
				cout << "��ϲ�����������ӪӮ����ʤ��������" << endl;
			}
			else {
				cout << "���ź������������Ӫ���ˣ��ٽ�����������" << endl;
			}
			return true;
		}
	}
	return false;
}

int GameData::playerBloodReduce(uint16_t role_num) {
	if (!m_players[role_num].playerBloodReduce()) {
		cout << "������������" << endl;
		return ERROR_SYSTEM_ERROR;
	}

	if (m_players[role_num].roleCurBlood() == 0) {
		cout << m_players[role_num].playerRoleName() << "  ����~�����ҡ�~" << endl;
		for (uint16_t i = 0; i < m_role_cur_count; i++) {
			if (i == role_num) continue;
			if (m_players[i].isRoleRobot()) {
				//robot
				m_players[role_num].setRoleAlive();
				return ERROR_TARGET_DEAD;
			}
			else {
				cout << m_players[role_num].playerRoleName() << "  ����~���������ҡ�~���Ƿ�����ҡ���" << endl;
				int index = applyPlayCard(CARD_TAO, i);
				if (index >= 0) {
					cout << m_players[i].playerRoleName() << "���㣩�����š��ҡ�~" << endl;
					m_players[role_num].playerBloodAdd();
					m_players[i].discardCards((uint16_t)index);
				}
				else {
					m_players[role_num].setRoleAlive();
					return ERROR_TARGET_DEAD;
				}
			}
		}
	}
	return 0;
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
				cout << "������š�ɱ������ѡ��ɱ����Ŀ��:" << endl;
				int role = chooseTarget(m_players[role_num].damageRange(), role_num, false);
				if (role < 0) {
					return ERROR_SYSTEM_ERROR;
				}

				if (role == ERROR_TARGET_ERROR) {
					return 0;
				}

				if (applyDamage(CARD_SHA, role_num, (uint16_t)role) == 0) {
					return 0;
				}
				else {
					cout << m_players[role].playerRoleName() << "û����Ӧ��ɱ��~~" << endl;
					return playerBloodReduce(role);
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
			cout << "���Ʋ����������~" << endl;
			m_players[role_num].drowCards(card, 1);
			return 0;
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
				cout << "������š����Ӳ��š�����ѡ�񡾹��Ӳ��š���Ŀ��:" << endl;
				int role = chooseTarget(m_roleCount, role_num, false);
				if (role < 0) {
					return ERROR_SYSTEM_ERROR;
				}

				if (role == ERROR_TARGET_ERROR) {
					return 0;
				}

				if (applyCardRemove(CARD_GUOHECHAIQIAO, role_num, (uint16_t)role) == 0) {
					return 0;
				}
				cout << "˭֪�������ʲô��" << endl;
				return ERROR_SYSTEM_ERROR;
			}
			break;
		}
		case CARD_SHUNSHOUQIANYANG: {
			if (m_players[role_num].isRoleRobot()) {
				//robot
			}
			else {
				cout << "������š�˳��ǣ�򡿣���ѡ��˳��ǣ�򡿵�Ŀ��:" << endl;
				int role = chooseTarget(m_players[role_num].isHorseMinus() ? 2 : 1, role_num, false);
				if (role < 0) {
					return ERROR_SYSTEM_ERROR;
				}

				if (role == ERROR_TARGET_ERROR) {
					return 0;
				}

				if (applyCardRemove(CARD_SHUNSHOUQIANYANG, role_num, (uint16_t)role) == 0) {
					return 0;
				}
				else if (role < 0) {
					cout << "û�С�˳��ǣ�򡿵�Ŀ��~gg" << endl;
					return 0;
				}
				cout << "˭֪�������ʲô��" << endl;
				return ERROR_SYSTEM_ERROR;
			}
			break;
		}
		case CARD_JUEDOU: {
			if (m_players[role_num].isRoleRobot()) {
				//robot
			}
			else {
				cout << "������š�����������ѡ�񡾾�������Ŀ��:" << endl;
				int role = chooseTarget(m_roleCount, role_num, false);
				if (role < 0) {
					cout << "ѡ��ɶĿ�껹û�е�~gg" << endl;
					return ERROR_SYSTEM_ERROR;
				}
				if (role == ERROR_TARGET_ERROR) {
					return 0;
				}

				int index = applyCardDuel(role_num, role);
				if (index = ERROR_NO_RESPONSE) {
					return playerBloodReduce(role);
				}
				else if (index = ERROR_NO_ACTIVE) {
					return playerBloodReduce(role_num);
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
				cout << "������š��赽ɱ�ˡ�����ѡ�񡾽赽ɱ�ˡ���ʹ��Ŀ��:" << endl;
				int role_source = chooseTarget(m_roleCount, role_num, true);
				if (role_source < 0) {
					cout << "ѡ��ɶĿ�껹û�е�~gg" << endl;
					return ERROR_SYSTEM_ERROR;
				}
				if (role_source == ERROR_TARGET_ERROR) {
					return 0;
				}

				cout << "��ѡ��ɱ����Ŀ��:" << endl;
				int role_target = chooseTarget(m_players[role_source].damageRange(), role_num, false);
				if (role_target < 0) {
					cout << "ѡ��ɶĿ�껹û�е�~gg" << endl;
					return ERROR_SYSTEM_ERROR;
				}
				if (role_target == ERROR_TARGET_ERROR) {
					return 0;
				}

				if (m_players[role_source].isRoleRobot()) {
					if (!m_players[role_source].isCard_Sha()) {
						CLICARDS *card = m_players[role_source].equipWeapon();
						if (card == NULL) {
							cout << "�����e��" << endl;
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
					cout << m_players[role_num].playerRoleName() << "��" << m_players[role_source].playerRoleName() << "  ʹ�á��赶ɱ�ˡ� ɱ  " << m_players[role_target].playerRoleName() << "  �Ƿ����ɱ��" << endl;
					int index = applyPlayCard(CARD_SHA, role_target);
					if (index < 0) {
						return ERROR_SYSTEM_ERROR;
					}
					m_players[role_source].discardCards((uint16_t)index);
				}

				if (applyDamage(CARD_SHA, role_source, role_target) != 0) {
					cout << m_players[role_target].playerRoleName() << "û����Ӧ��ɱ��~~" << endl;
					return playerBloodReduce(role_target);
				}
				return 0;
			}
			break;
		}
		case CARD_WUZHONGSHENGYOU: {
			CLICARDS card[CARDS_DEALS] = { 0 };
			if (!dealCards(CARDS_DEALS, role_num)) {
				cout << "����Ҳ�����" << endl;
				return ERROR_SYSTEM_ERROR;
			}

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
				cout << "���Ƴ�����" << endl;
				return ERROR_SYSTEM_ERROR;
			}
			return applyCardDeals(card_num, cards);
		}
		default:
			cout << "���Ʋ����������~" << endl;
			m_players[role_num].drowCards(card, 1);
			return 0;
		}
	}
	else if (card->category == CARDS_CATEGORY_STRATEGY_DELAY) {
		switch (card->id)
		{
		case CARD_SHANDIAN: {
			if (!m_players[role_num].judgementCard(card)) {
				return ERROR_SYSTEM_ERROR;
			}
			return 0;
		}
		case CARD_LEBUSISHU: {
			int index = chooseTarget(m_roleCount, role_num, false);
			if (index < 0) {
				cout << "ѡ��ɶĿ�껹û�е�~" << endl;
				return ERROR_SYSTEM_ERROR;
			}
			if (index == ERROR_TARGET_ERROR) {
				return 0;
			}

			if (!m_players[index].judgementCard(card)) {
				return ERROR_SYSTEM_ERROR;
			}
			return 0;
		}
		default:
			cout << "���Ʋ����������~" << endl;
			m_players[role_num].drowCards(card, 1);
			return 0;
		}
	}
	else if (card->category == CARDS_CATEGORY_EQUIPMENT_WEAPON
		|| card->category == CARDS_CATEGORY_EQUIPMENT_ARMOR
		|| card->category == CARDS_CATEGORY_EQUIPMENT_HORSE_PLUS
		|| card->category == CARDS_CATEGORY_EQUIPMENT_HORSE_MINUS) {
		if (!m_players[role_num].equipCards(card)) {
			cout << "װ���Ƴ�����~" << endl;
			return ERROR_SYSTEM_ERROR;
		}
		return 0;
	}
	return ERROR_SYSTEM_ERROR;
}

////////////////////////////////
int GameData::chooseTarget(uint16_t distance, uint16_t role_num, bool need_weapon) {
	uint16_t num = 0;
	uint16_t roles[ROLES_MAX_NUM] = { 0 };

	for (uint16_t i = 0; i < m_roleCount; i++) {
		if (role_num == i) continue;
		uint16_t dis = (i > m_roleCount / 2) ? abs(role_num + m_roleCount - i) : abs(role_num - i);

		dis += m_players[i].isHorsePlus() ? 1 : 0;

		bool requir = true;
		if (need_weapon) {
			requir = m_players[role_num].equipWeapon() && requir;
		}

		if (dis <= distance && requir) {
			roles[num++] = i;
		}
	}

	if (num == 0) {
		cout << "�]��Ŀ�����ѡ��~" << endl;
		cout << endl;
		return ERROR_TARGET_ERROR;
	}

	for (uint16_t i = 0; i < num; i++) {
		cout << "[" << i << "]  " << m_players[roles[i]].playerRoleName() << endl;
	}

	string in_str;
	while (true) {
		cout << "��ѡ��Ŀ��~: ";
		cin >> in_str;

		int index = strToInt(in_str);
		if (index >= 0 && index < num) {
			return roles[index];;
		}
		else {
			for (uint16_t i = 0; i < num; i++) {
				if (in_str == m_players[roles[i]].playerRoleName()) {
					return roles[i];
				}
			}
			cout << "Ŀ���������������~" << endl;
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
		cout << "  �������ɱ�����Ƿ����������" << endl;
		index = applyPlayCard(card_id, target_num);
	}
	else {
		index = m_players[target_num].curCardIndex(card_id);
	}

	if (index >= 0) {
		//cout << m_players[target_num].playerRoleName() << "  ���ˡ�����~" << endl;
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
				cout << m_players[source_num].playerRoleName() << "�����š�����뷢�����Ƿ����������" << endl;
				index = applyPlayCard(CARD_SHAN, i);
			}
			else if (card_id == CARD_NANMANRUQIN) {
				cout << m_players[source_num].playerRoleName() << "�����š��������֡����Ƿ����ɱ����" << endl;
				index = applyPlayCard(CARD_SHA, i);
			}

			if (index < 0) {
				return ERROR_SYSTEM_ERROR;
			}
			cout << m_players[i].playerRoleName() << "  ����һ����~" << endl;
			m_players[i].discardCards((uint16_t)index);
		}
		else {
			if (card_id == CARD_WANGJIANQIFA) {
				if (!m_players[i].isCard_Shan()) {
					return playerBloodReduce(i);
				}
				else {
					m_players[i].discardCards((uint32_t)CARD_SHAN);
				}
			}
			else if (card_id == CARD_NANMANRUQIN) {
				if (!m_players[i].isCard_Sha()) {
					return playerBloodReduce(i);
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
	cout << "[99]. ������" << endl;
	string in_str;
	while (true) {
		cout << "��ѡ��Ҫ���Ŀ���!" << endl;
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
				cout << "����������������룡����" << endl;
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

	cout << "���� �� 0~" << cur_card_num - 1 << endl;
	if (equip_card_num != 0) {
		cout << "װ���� �� " << cur_card_num << "~" << cur_card_num + equip_card_num - 1 << endl;
	}

	if (judge_card_num != 0) {
		cout << "�ж��� �� " << cur_card_num + judge_card_num << "~" << cur_card_num + equip_card_num + judge_card_num - 1 << endl;
	}

	uint16_t in_str = 0;
	while (true) {
		cout << "��ѡ������Ŀ����~(0~" << cur_card_num + equip_card_num + judge_card_num - 1;
		cout << ")" << endl;
		cin >> in_str;

		if (in_str >= cur_card_num + equip_card_num + judge_card_num) {
			cout << "��ɶ������������ƣ�����������~" << endl;
		}
		else {
			break;
		}
	}

	if (in_str < cur_card_num) {
		CLICARDS * card = m_players[target_num].discardCards(in_str);
		if (card == NULL) {
			cout << "զ������������" << endl;
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
			cout << "զ������װ��������" << endl;
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
			cout << "զ�������ж�������" << endl;
			return ERROR_SYSTEM_ERROR;
		}

		if (card_id == CARD_SHUNSHOUQIANYANG) {
			return m_players[source_num].drowCards(card, 1) ? 0 : ERROR_SYSTEM_ERROR;
		}
		return 0;
	}
	else {
		cout << "��ѡ�˸�ʲô�ƣ�" << endl;
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
			cout << m_players[source_num].playerRoleName() << "����ʹ���ˡ��������������ɱ��~" << endl;
			int index = applyPlayCard(CARD_SHA, target_num);
			if (index >= 0) {
				m_players[target_num].discardCards((uint16_t)index);
			}
			else {
				return ERROR_NO_RESPONSE;
			}
		}

		cout << m_players[target_num].playerRoleName() << "����һ�š�ɱ����" << endl;

		if (m_players[source_num].isRoleRobot()) {
			m_players[source_num].playCards((uint32_t)CARD_SHA);
		}
		else {
			cout << "����Ҫ��һ�š�ɱ�����Ƿ����ɱ����" << endl;
			int index = applyPlayCard(CARD_SHA, source_num);
			if (index >= 0) {
				m_players[source_num].discardCards((uint16_t)index);
			}
			else {
				return ERROR_NO_ACTIVE;
			}
		}
		cout << m_players[source_num].playerRoleName() << "����һ�š�ɱ����" << endl;
	}

	if (m_players[target_num].isCard_Sha() && !m_players[source_num].isCard_Sha()) {
		cout << m_players[source_num].playerRoleName() << "������Ӧ����ɱ����" << endl;
		return ERROR_NO_ACTIVE;
	}

	if (!m_players[target_num].isCard_Sha() && m_players[source_num].isCard_Sha()) {
		cout << m_players[target_num].playerRoleName() << "������Ӧ����ɱ����" << endl;
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
		if (!m_players[i].isRoleAlive()) continue;
		if (m_players[i].isRoleRobot()) {
			index = 0;//robot
		}
		else {
			cout << "��ѡ��������~" << endl;
			string in_str;
			while (true) {
				cout << "��ѡ��Ҫ���Ŀ���!" << endl;
				cin >> in_str;
				index = strToInt(in_str);
				if (signal[index] != 0) {
					cout << "�����ѱ�ѡȡ��������ѡ��" << endl;
				}
			}
		}
		if (index == -1) {
			cout << "ѡ�Ƴ�����" << endl;
			continue;
		}
		m_players[i].drowCards(&cards[index], 1);
		signal[index] = 1;
	}
	return 0;
}