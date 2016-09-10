#include "playerData.h"
#include "rolesInfoManagement.h"
#include "cardsInfoManagement.h"
#include <string>

PlayerData::PlayerData() {
	player_info.role_id = 0; 
	player_info.max_blood = 0;
	player_info.cur_blood = 0;
	player_info.role_name = '\0';
	player_info.role_power = '\0';
	player_info.cur_state = 0;
	player_info.max_cards = 0;
	player_info.cards_num = 0;
	memset(player_info.cur_cards, 0, sizeof(player_info.cur_cards));
	memset(player_info.equip_cards, 0, sizeof(player_info.equip_cards));
	memset(player_info.judgment_cards, 0, sizeof(player_info.judgment_cards));
	player_info.equip_num = 0;
	player_info.judgment_num = 0;
}

PlayerData::~PlayerData() {

}

string PlayerData::viewCardColor(CLICARDS card) {
	string card_color;
	switch (card.color)
	{
	case 0:
		card_color = "����  ";
		break;
	case 1:
		card_color = "÷��  ";
		break;
	case 2:
		card_color = "����  ";
		break;
	case 3:
		card_color = "����  ";
		break;
	default:
		card_color = "��ɫ����";
		return card_color;
	}
	card_color += card.points;
	return card_color;
}

void PlayerData::viewCurCards(bool isShow) {
	if (player_info.cards_num == 0) {
		if (isShow) {
			cout << "������" << endl;
		}
	}
	else {
		for (uint16_t i = 0; i < player_info.cards_num; i++) {
			cout << "[" << i << "]  " << player_info.cur_cards[i].name << "(" << viewCardColor(player_info.cur_cards[i]) << ")" << endl;
		}
	}
}

void PlayerData::viewEquipCards(bool isShow) {
	if (player_info.equip_num == 0) {
		if (isShow) {
			cout << "��װ����" << endl;
		}
	}
	else {
		for (uint16_t i = 0; i < player_info.equip_num; i++) {
			cout << "[" << i << "]  " << player_info.equip_cards[i].name << "(" << viewCardColor(player_info.equip_cards[i]) << ")" << endl;
		}
	}
}

void PlayerData::viewJudgementCards(bool isShow){
	if (player_info.judgment_num == 0) {
		if (isShow) {
			cout << "�����ж�����" << endl;
		}
	}
	else {
		for (uint16_t i = 0; i < player_info.judgment_num; i++) {
			cout << "[" << i << "]  " << player_info.judgment_cards[i].name << "(" << viewCardColor(player_info.judgment_cards[i]) << ")" << endl;
		}
	}
}
void PlayerData::viewRoleCard() {
	rolesInfoManagement role_man;
	ROLESINFO * roleInfo = role_man.findRoleById(player_info.role_id);

	if (roleInfo != NULL) {
		cout << "�佫����   " << roleInfo->name << endl;
		cout << "�佫����������  " << roleInfo->blood << endl;
		cout << "�佫��ǰ������  " << player_info.cur_blood << endl;
		cout << "�佫����������  " << roleInfo->power << endl;
		cout << "�佫���ܣ� " << endl;

		for (uint16_t i = 0; i < roleInfo->skill_num; i++) {
			cout << "[" << i << "]" << roleInfo->skill[i] << endl;
		}
	}
	else {
		cout << "�޴��佫��Ϣ" << endl;
	}
}

bool PlayerData::isCardCanPlay(uint32_t id) {
	CARDSINFOMANAGEMENT card_man;
	CARDSINFO * card_info = card_man.findCardById(id);

	if (card_info->category == CARDS_BASIC || card_info->category == CARDS_STRATEGY || card_info->category == CARDS_STRATEGY_DELAY) {
		return true;
	}

	return false;
}

bool PlayerData::isCardCanEquip(uint32_t id) {
	CARDSINFOMANAGEMENT card_man;
	CARDSINFO * card_info = card_man.findCardById(id);

	if (card_info->category == CARDS_EQUIPMENT_WEAPON || card_info->category == CARDS_EQUIPMENT_ARMOR || card_info->category == CARDS_EQUIPMENT_HORSE_MINUS || card_info->category == CARDS_EQUIPMENT_HORSE_PLUS) {
		for (uint16_t i = 0; i < player_info.equip_num; i++) {
			if (card_info->category == player_info.equip_cards[i].category) {
				return false;
			}
		}
		return true;
	}

	return false;
}

uint32_t PlayerData::playCards(uint16_t index) {
	if(player_info.cards_num == 0){
		cout << "�����ƿ�ʹ��" << endl;
		return 0;
	}

	if (index >= player_info.cards_num) {
		cout << "�޴���ŵ�����" << endl;
		return 0;
	}

	uint32_t card_id = 0;
	for (uint16_t i = 0; i < player_info.cards_num; i++) {
		if (index > i) continue;
		if (index == i) {
			card_id = player_info.cur_cards[i].id;
		}
		if (index == player_info.cards_num - 1) {
			card_id = player_info.cur_cards[index].id;
			break;
		}
		memcpy(&player_info.cur_cards[i], &player_info.cur_cards[i + 1], sizeof(player_info.cur_cards[i + 1]));
	}
	player_info.cards_num--;
	return card_id;
}

uint32_t PlayerData::playCards(string name) {
	if (player_info.cards_num == 0) {
		cout << "�����ƿ�ʹ��" << endl;
		return NULL;
	}

	int index = -1;

	for (uint16_t i = 0; i < player_info.cards_num; i++) {
		if (name == player_info.cur_cards[i].name) {
			index = i;
			break;
		}
	}

	if (index < 0) {
		cout << "�޴����ƿ�ʹ��" << endl;
		return NULL;
	}
	
	return playCards((uint16_t)index);
}

uint32_t PlayerData::playCards(uint32_t id){
	return id;
}

uint32_t PlayerData::discardCards(uint16_t index) {
	return playCards(index);
}

uint32_t PlayerData::discardCards(string name) {
	return playCards(name);
}

uint32_t PlayerData::discardCards(uint32_t id) {
	return id;
}

uint32_t PlayerData::equipCards(uint32_t id){
	if (!isCardCanEquip(id)) {
		cout << "�˿��Ʋ���װ����" << endl;
		return id;
	}
	return id;
}

uint16_t PlayerData::calcuteDistance(uint16_t role_number) {
	return 0;
}

bool PlayerData::useRoleSkill(uint16_t index) {
	return true;
}

bool PlayerData::useRoleSkill(uint32_t id) {
	return true;
}