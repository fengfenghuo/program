#include "playerData.h"
#include "rolesInfoManagement.h"
#include "cardsInfoManagement.h"
#include <cstdlib>
#include <string>
#include <cmath>

PlayerData::PlayerData() {
	m_playerInfo.is_alive = true;
	m_playerInfo.role_id = 0; 
	m_playerInfo.max_blood = 0;
	m_playerInfo.cur_blood = 0;
	m_playerInfo.role_name = '\0';
	m_playerInfo.role_power = '\0';
	m_playerInfo.status = 0;
	m_playerInfo.cur_state = 0;
	m_playerInfo.max_cards = 0;
	m_playerInfo.cards_num = 0;
	memset(m_playerInfo.cur_cards, 0, sizeof(m_playerInfo.cur_cards));
	memset(m_playerInfo.equip_cards, 0, sizeof(m_playerInfo.equip_cards));
	memset(m_playerInfo.judgment_cards, 0, sizeof(m_playerInfo.judgment_cards));
	m_playerInfo.equip_num = 0;
	m_playerInfo.judgment_num = 0;
}

PlayerData::~PlayerData() {

}

void PlayerData::viewCurCards(bool isShow, uint16_t start) {
	if (m_playerInfo.cards_num == 0) {
		if (isShow) {
			cout << "������" << endl;
		}
	}
	else {
		for (uint16_t i = 0; i < m_playerInfo.cards_num; i++) {
			cout << "[" << i + start << "]  " << m_playerInfo.cur_cards[i].name << "(" << viewCardColor(m_playerInfo.cur_cards[i].points, m_playerInfo.cur_cards[i].color) << ")" << endl;
		}
	}
	cout << endl;
}

void PlayerData::viewEquipCards(bool isShow, uint16_t start) {
	cout << "װ������" << endl;
	if (m_playerInfo.equip_num == 0) {
		if (isShow) {
			cout << "��װ����" << endl;
		}
	}
	else {
		for (uint16_t i = 0; i < m_playerInfo.equip_num; i++) {
			cout << "[" << i + start << "]  " << m_playerInfo.equip_cards[i].name << "(" << viewCardColor(m_playerInfo.equip_cards[i].points, m_playerInfo.equip_cards[i].color) << ")" << endl;
		}
	}
	cout << endl;
}

void PlayerData::viewJudgementCards(bool isShow, uint16_t start){
	cout << "�ж�����" << endl;
	if (m_playerInfo.judgment_num == 0) {
		if (isShow) {
			cout << "�����ж�����" << endl;
		}
	}
	else {
		for (uint16_t i = 0; i < m_playerInfo.judgment_num; i++) {
			cout << "[" << i + start << "]  " << m_playerInfo.judgment_cards[i].name << "(" << viewCardColor(m_playerInfo.judgment_cards[i].points, m_playerInfo.judgment_cards[i].color) << ")" << endl;
		}
	}
	cout << endl;
}

void PlayerData::viewRoleCard() {
	rolesInfoManagement role_man;
	ROLESINFO * roleInfo = role_man.findRoleById(m_playerInfo.role_id);

	if (roleInfo != NULL) {
		cout << "�佫����   " << m_playerInfo.role_name << endl;
		if (m_playerInfo.status == STATUS_MASTER) {
			cout << "��  �ݣ�   " << viewRoleStatus(m_playerInfo.status) << endl;
		}
		else if (!isRoleRobot()) {
			cout << "������ݣ�  " << viewRoleStatus(m_playerInfo.status) << endl;
		}
		cout << "�佫����   " << m_playerInfo.role_name << endl;
		cout << "�佫����������  " << m_playerInfo.max_blood << endl;
		cout << "�佫��ǰ������  " << m_playerInfo.cur_blood << endl;
		cout << "�佫����������  " << m_playerInfo.role_power << endl;
		cout << "�佫���ܣ� " << endl;

		for (uint16_t i = 0; i < roleInfo->skill_num; i++) {
			cout << "[" << i << "]" << roleInfo->skill[i] << endl;
		}
		cout << endl;
	}
	else {
		cout << "�޴��佫��Ϣ" << endl;
	}
}

void PlayerData::viewRolesCard(uint32_t *roles, uint16_t role_num) {
	rolesInfoManagement role_man;

	for (uint16_t i = 0; i < role_num; i++) {
		ROLESINFO * roleInfo = role_man.findRoleById(roles[i]);
		if (roleInfo != NULL) {
			cout << "�佫��ţ� " << "[" << i << "]" << endl;
			cout << "�佫����   " << roleInfo->name << endl;
			cout << "�佫����������  " << roleInfo->blood << endl;
			cout << "�佫����������  " << roleInfo->power << endl;
			cout << "�佫���ܣ� " << endl;

			for (uint16_t j = 0; j < roleInfo->skill_num; j++) {
				cout << "[" << j << "]" << roleInfo->skill[j] << endl;
			}
		}
		else {
			cout << "�޴��佫��Ϣ" << endl;
		}
	}
}

void PlayerData::viewRolesCard(uint16_t *roles_identity, uint16_t role_num) {
	rolesInfoManagement role_man;

	for (uint16_t i = 0; i < role_num; i++) {
		ROLESINFO * roleInfo = role_man.findRoleByIdentity(roles_identity[i]);
		if (roleInfo != NULL) {
			cout << "�佫��ţ� " << "[" << i << "]" << endl;
			cout << "�佫����   " << roleInfo->name << endl;
			cout << "�佫����������  " << roleInfo->blood << endl;
			cout << "�佫����������  " << roleInfo->power << endl;
			cout << "�佫���ܣ� " << endl;

			for (uint16_t j = 0; j < roleInfo->skill_num; j++) {
				cout << "[" << j << "]" << roleInfo->skill[j] << endl;
			}
		}
		else {
			cout << "�޴��佫��Ϣ" << endl;
		}
	}
}

bool  PlayerData::setRoleInfo(ROLESINFO * roleInfo) {
	if (roleInfo != NULL) {
		m_playerInfo.max_blood = m_playerInfo.status == STATUS_MASTER ? roleInfo->blood + 1 : roleInfo->blood;
		m_playerInfo.cur_blood = m_playerInfo.max_blood;
		m_playerInfo.role_id = roleInfo->id;
		m_playerInfo.role_name = roleInfo->name;
		m_playerInfo.role_power = roleInfo->power;
		m_playerInfo.sex = roleInfo->sex;
		return true;
	}
	return false;
}

bool PlayerData::setRoleStatus(uint16_t status, uint16_t role_num, bool isRobot) {
	if (m_playerInfo.status == 0 && status >= STATUS_MASTER && status <= STATUS_NUM) {
		m_playerInfo.status = status;
		m_playerInfo.role_num = role_num;
		m_playerInfo.is_robot = isRobot;
		return true;
	}
	return false;
}

bool PlayerData::setRoleCurState(uint16_t state, bool is_play_sha) {
	if (state >= GAME_STAGE_END && state <= GAME_STAGE_DISCARDS) {
		m_playerInfo.cur_state = state;
		m_playerInfo.cur_state = is_play_sha;
	}
	return false;
}

bool PlayerData::setRoleAlive() {
	if (m_playerInfo.cur_blood != 0) {
		return false;
	}
	m_playerInfo.is_alive = false;
	return true;
}

uint16_t PlayerData::roleCurState() {
	return m_playerInfo.cur_state;
}

uint16_t PlayerData::roleCurBlood() {
	return m_playerInfo.cur_blood;
}

bool PlayerData::roleSex() {
	return m_playerInfo.sex;
}

bool PlayerData::isCardCanPlay(uint32_t id) {
	CARDSINFOMANAGEMENT card_man;
	CARDSINFO * card_info = card_man.findCardById(id);

	if (card_info->category == CARDS_CATEGORY_BASIC 
		|| card_info->category == CARDS_CATEGORY_STRATEGY 
		|| card_info->category == CARDS_CATEGORY_STRATEGY_DELAY) {
		return true;
	}

	return false;
}

bool PlayerData::isCardCanEquip(uint32_t id) {
	CARDSINFOMANAGEMENT card_man;
	CARDSINFO * card_info = card_man.findCardById(id);

	if (card_info->category == CARDS_CATEGORY_EQUIPMENT_WEAPON 
		|| card_info->category == CARDS_CATEGORY_EQUIPMENT_ARMOR 
		|| card_info->category == CARDS_CATEGORY_EQUIPMENT_HORSE_MINUS 
		|| card_info->category == CARDS_CATEGORY_EQUIPMENT_HORSE_PLUS) {
		for (uint16_t i = 0; i < m_playerInfo.equip_num; i++) {
			if (card_info->category == m_playerInfo.equip_cards[i].category) {
				return false;
			}
		}
		return true;
	}

	return false;
}

bool PlayerData::isCardCanEquip(uint16_t index) {
	if (m_playerInfo.cur_cards[index].category == CARDS_CATEGORY_EQUIPMENT_WEAPON
		|| m_playerInfo.cur_cards[index].category == CARDS_CATEGORY_EQUIPMENT_ARMOR
		|| m_playerInfo.cur_cards[index].category == CARDS_CATEGORY_EQUIPMENT_HORSE_MINUS
		|| m_playerInfo.cur_cards[index].category == CARDS_CATEGORY_EQUIPMENT_HORSE_PLUS) {
		for (uint16_t i = 0; i < m_playerInfo.equip_num; i++) {
			if (m_playerInfo.cur_cards[index].category == m_playerInfo.equip_cards[i].category) {
				return false;
			}
		}
		return true;
	}

	return false;
}

bool PlayerData::drowCards(CLICARDS *cards, uint16_t card_count) {
	if (cards == NULL || card_count <= 0) {
		return false;
	}
	for (uint16_t i = 0; i < card_count; i++) {
		memcpy(&m_playerInfo.cur_cards[m_playerInfo.cards_num++], &cards[i], sizeof(CLICARDS));
	}
	return true;
}

CLICARDS* PlayerData::playCards(uint16_t index) {
	if (m_playerInfo.cur_state != GAME_STAGE_PLAY) {
		cout << "��ǰ���ڳ��ƽ׶Σ����ܳ���" << endl;
		return NULL;
	}

	return putOneCardByIndex(index);
}

CLICARDS* PlayerData::playCards(string name) {
	if (m_playerInfo.cur_state != GAME_STAGE_PLAY) {
		cout << "��ǰ���ڳ��ƽ׶Σ����ܳ���" << endl;
		return NULL;
	}

	return putOneCardByName(name);
}

CLICARDS* PlayerData::playCards(uint32_t id){
	return putOneCardById(id);
}

CLICARDS* PlayerData::discardEquipCards(uint16_t index) {
	if (m_playerInfo.equip_num == 0) {
		cout << "��װ���ƿ���" << endl;
		return NULL;
	}

	if (index >= m_playerInfo.equip_num) {
		cout << "�޴���ŵ�װ����" << endl;
		return NULL;
	}

	CLICARDS *card = new CLICARDS;
	for (uint16_t i = 0; i < m_playerInfo.equip_num; i++) {
		if (index > i) continue;
		if (index == i) {
			memcpy(card, &m_playerInfo.equip_cards[index], sizeof(CLICARDS));
		}
		if (index == m_playerInfo.equip_num - 1) {
			memcpy(card, &m_playerInfo.equip_cards[index], sizeof(CLICARDS));
			break;
		}
		memcpy(&m_playerInfo.equip_cards[i], &m_playerInfo.equip_cards[i + 1], sizeof(m_playerInfo.equip_cards[i + 1]));
	}
	m_playerInfo.equip_num--;
	return card;
}

CLICARDS* PlayerData::discardJudgementCards(uint16_t index) {
	if (m_playerInfo.judgment_num == 0) {
		cout << "���ж��ƿ���" << endl;
		return NULL;
	}

	if (index >= m_playerInfo.judgment_num) {
		cout << "�޴���ŵ��ж���" << endl;
		return NULL;
	}

	CLICARDS *card = new CLICARDS;
	for (uint16_t i = 0; i < m_playerInfo.judgment_num; i++) {
		if (index > i) continue;
		if (index == i) {
			memcpy(card, &m_playerInfo.judgment_cards[index], sizeof(CLICARDS));
		}
		if (index == m_playerInfo.judgment_num - 1) {
			memcpy(card, &m_playerInfo.judgment_cards[index], sizeof(CLICARDS));
			break;
		}
		memcpy(&m_playerInfo.judgment_cards[i], &m_playerInfo.judgment_cards[i + 1], sizeof(m_playerInfo.judgment_cards[i + 1]));
	}
	m_playerInfo.judgment_num--;
	return card;
}

CLICARDS* PlayerData::discardCards(uint16_t index) {
	/*if (m_playerInfo.cur_state != GAME_STAGE_DISCARDS) {
	cout << "��ǰ�������ƽ׶Σ���������" << endl;
	return NULL;
	}*/
	return putOneCardByIndex(index);
}

CLICARDS* PlayerData::discardCards(string name) {
	/*if (m_playerInfo.cur_state != GAME_STAGE_DISCARDS) {
		cout << "��ǰ�������ƽ׶Σ���������" << endl;
		return NULL;
	}*/
	return putOneCardByName(name);
}

CLICARDS* PlayerData::discardCards(uint32_t id) {
	return putOneCardById(id);
}

bool PlayerData::equipCards(CLICARDS *card) {
	if (card->category != CARDS_CATEGORY_EQUIPMENT_WEAPON
		&& card->category != CARDS_CATEGORY_EQUIPMENT_ARMOR
		&& card->category != CARDS_CATEGORY_EQUIPMENT_HORSE_PLUS
		&& card->category != CARDS_CATEGORY_EQUIPMENT_HORSE_MINUS) {
		return false;
	}

	if (equipCardByCategory(card->category) != NULL) {
		discardEquipCards(card->category);
	}
	memcpy(&m_playerInfo.equip_cards[m_playerInfo.equip_num++], card, sizeof(CLICARDS));
	cout << m_playerInfo.role_name << "װ���ˡ�" << card->name << "��" << endl;
	return true;
}

bool PlayerData::judgementCard(CLICARDS *card) {
	if (card == NULL) {
		cout << "No this card" << endl;
		return false;
	}

	memcpy(&m_playerInfo.judgment_cards[m_playerInfo.judgment_num++], card, sizeof(CLICARDS));
	return true;
}

bool PlayerData::playerBloodAdd(uint16_t n) {
	if (m_playerInfo.cur_blood >= m_playerInfo.max_blood){
		return false;
	}
	m_playerInfo.cur_blood = m_playerInfo.cur_blood + n > m_playerInfo.max_blood ? m_playerInfo.max_blood : m_playerInfo.cur_blood + n;

	cout << playerRoleName() << "  ����һ������~" << endl;
	return true;
}

bool PlayerData::playerBloodReduce(uint16_t n){
	if (m_playerInfo.cur_blood <= 0) {
		return false;
	}

	m_playerInfo.cur_blood -= n;
	cout << playerRoleName() << "  ����һ������~" << endl;
	return true;
}

bool PlayerData::isRoleRobot() {
	return m_playerInfo.is_robot;
}

bool PlayerData::isRoleAlive() {
	return m_playerInfo.is_alive;
}

bool PlayerData::isHorsePlus() {
	for (int i = 0; i < m_playerInfo.equip_num; i++) {
		if (m_playerInfo.equip_cards[i].category == CARDS_CATEGORY_EQUIPMENT_HORSE_PLUS) {
			return true;
		}
	}
	return false;
}

bool PlayerData::isHorseMinus() {
	for (int i = 0; i < m_playerInfo.equip_num; i++) {
		if (m_playerInfo.equip_cards[i].category == CARDS_CATEGORY_EQUIPMENT_HORSE_MINUS) {
			return true;
		}
	}
	return false;
}

uint16_t PlayerData::weaponRange() {
	for (int i = 0; i < m_playerInfo.equip_num; i++) {
		if (m_playerInfo.equip_cards[i].category == CARDS_CATEGORY_EQUIPMENT_WEAPON) {
			return m_playerInfo.equip_cards[i].range;
		}
	}
	return 0;
}

string PlayerData::playerRoleName() {
	return m_playerInfo.role_name;
}

uint16_t PlayerData::playerRoleNum() {
	return m_playerInfo.role_num;
}

uint16_t PlayerData::playerRoleStatus() {
	return m_playerInfo.status;
}

uint16_t PlayerData::damageRange() {
	return 1 + weaponRange() + (isHorseMinus() ? 1 : 0);
}

bool PlayerData::isCard_Sha() {
	for (uint16_t i = 0; i < m_playerInfo.cards_num; i++) {
		if (m_playerInfo.cur_cards[i].id == CARD_SHA) {
			return true;
		}
	}
	return false;
}

bool PlayerData::isCard_Shan(){
	for (uint16_t i = 0; i < m_playerInfo.cards_num; i++) {
		if (m_playerInfo.cur_cards[i].id == CARD_SHAN) {
			return true;
		}
	}
	return false;
}

bool PlayerData::isCard_Tao() {
	for (uint16_t i = 0; i < m_playerInfo.cards_num; i++) {
		if (m_playerInfo.cur_cards[i].id == CARD_TAO) {
			return true;
		}
	}
	return false;
}

uint32_t PlayerData::curCardId(uint16_t index) {
	if (index >= m_playerInfo.cards_num) {
		return 0;
	}
	return m_playerInfo.cur_cards[index].id;
}

int PlayerData::curCardIndex(string name) {
	for (uint16_t i = 0; i < m_playerInfo.cards_num; i++) {
		if (name == m_playerInfo.cur_cards[i].name) {
			return i;
		}
	}
	return ERROR_SYSTEM_ERROR;
}

int PlayerData::curCardIndex(uint32_t id) {
	for (uint16_t i = 0; i < m_playerInfo.cards_num; i++) {
		if (id == m_playerInfo.cur_cards[i].id) {
			return i;
		}
	}
	return ERROR_SYSTEM_ERROR;
}

CLICARDS* PlayerData::judgeCardByIndex(uint16_t index) {
	if (index >= m_playerInfo.judgment_num) {
		return NULL;
	}

	return &m_playerInfo.judgment_cards[index];
}

bool PlayerData::isCurCardEmpty(){
	return m_playerInfo.cards_num == 0 ? true : false;
}

bool PlayerData::isJudgeCardEmpty() {
	return m_playerInfo.equip_num == 0 ? true : false;
}

bool PlayerData::isEquipCardEmpty() {
	return m_playerInfo.judgment_num == 0 ? true : false;
}

uint16_t PlayerData::cardCurNum() {
	return m_playerInfo.cards_num;
}

uint16_t PlayerData::cardEquipNum() {
	return m_playerInfo.equip_num;
}

uint16_t PlayerData::cardJudgeNum() {
	return m_playerInfo.judgment_num;
}

CLICARDS* PlayerData::equipWeapon() {
	for (uint16_t i = 0; i < m_playerInfo.equip_num; i++) {
		if (m_playerInfo.equip_cards[i].category == CARDS_CATEGORY_EQUIPMENT_WEAPON) {
			CLICARDS* weapen = &m_playerInfo.equip_cards[i];
			return weapen;
		}
	}
	return NULL;
}

CLICARDS* PlayerData::equipArmor() {
	for (uint16_t i = 0; i < m_playerInfo.equip_num; i++) {
		if (m_playerInfo.equip_cards[i].category == CARDS_CATEGORY_EQUIPMENT_ARMOR) {
			CLICARDS* armor = &m_playerInfo.equip_cards[i];
			return armor;
		}
	}
	return NULL;
}

CLICARDS* PlayerData::discardEquipCards(uint8_t category) {
	for (uint16_t i = 0; i < m_playerInfo.equip_num; i++) {
		if (m_playerInfo.equip_cards[i].category == category) {
			return discardEquipCards(i);
		}
	}
	return NULL;
}

CLICARDS* PlayerData::equipCardByCategory(uint8_t category){
	for (uint16_t i = 0; i < m_playerInfo.equip_num; i++) {
		if (m_playerInfo.equip_cards[i].category == category) {
			return &m_playerInfo.equip_cards[i];
		}
	}
	return NULL;
}

PLAYERINFO * PlayerData::playerInfo() {
	return &m_playerInfo;
}

/////////////////////////////////////////////////////
bool PlayerData::useRoleSkill(uint16_t index) {
	return true;
}

bool PlayerData::useRoleSkill(uint32_t id) {
	return true;
}

//////////////////////////////////////////////////////
CLICARDS* PlayerData::putOneCardByIndex(uint16_t index) {
	if (m_playerInfo.cards_num == 0) {
		cout << "�����ƿ�ʹ��" << endl;
		return NULL;
	}

	if (index >= m_playerInfo.cards_num) {
		cout << "�޴���ŵ�����" << endl;
		return NULL;
	}

	CLICARDS *card = new CLICARDS;
	for (uint16_t i = 0; i < m_playerInfo.cards_num; i++) {
		if (index > i) continue;
		if (index == i) {
			memcpy(card, &m_playerInfo.cur_cards[index], sizeof(CLICARDS));
		}
		if (index == m_playerInfo.cards_num - 1) {
			memcpy(card, &m_playerInfo.cur_cards[index], sizeof(CLICARDS));
			break;
		}
		memcpy(&m_playerInfo.cur_cards[i], &m_playerInfo.cur_cards[i + 1], sizeof(m_playerInfo.cur_cards[i + 1]));
	}
	m_playerInfo.cards_num--;

	//cout << playerRoleName() << "  ���" << "��" << card->name << "��" << endl;
	return card;
}

CLICARDS* PlayerData::putOneCardByName(string name) {
	if (m_playerInfo.cards_num == 0) {
		cout << "�����ƿ�ʹ��" << endl;
		return NULL;
	}

	int index = curCardIndex(name);

	if (index < 0) {
		cout << "�޴����ƿ�ʹ��" << endl;
		return NULL;
	}

	return putOneCardByIndex((uint16_t)index);
}

CLICARDS* PlayerData::putOneCardById(uint32_t id) {
	if (m_playerInfo.cards_num == 0) {
		cout << "�����ƿ�ʹ��" << endl;
		return NULL;
	}

	int index = curCardIndex(id);
	if (index < 0) {
		cout << "�޴����ƿ�ʹ��" << endl;
		return NULL;
	}

	return putOneCardByIndex((uint16_t)index);
}
