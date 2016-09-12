#include "playerData.h"
#include "rolesInfoManagement.h"
#include "cardsInfoManagement.h"
#include <string>
#include <cmath>

PlayerData::PlayerData() {
	player_info.role_id = 0; 
	player_info.max_blood = 0;
	player_info.cur_blood = 0;
	player_info.role_name = '\0';
	player_info.role_power = '\0';
	player_info.status = 0;
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
		card_color = "黑桃  ";
		break;
	case 1:
		card_color = "梅花  ";
		break;
	case 2:
		card_color = "红桃  ";
		break;
	case 3:
		card_color = "方块  ";
		break;
	default:
		card_color = "花色有误";
		return card_color;
	}
	card_color += card.points;
	return card_color;
}

void PlayerData::viewCurCards(bool isShow) {
	if (player_info.cards_num == 0) {
		if (isShow) {
			cout << "无手牌" << endl;
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
			cout << "无装备牌" << endl;
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
			cout << "无需判定的牌" << endl;
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
		cout << "武将名：   " << roleInfo->name << endl;
		cout << "武将上限体力：  " << roleInfo->blood << endl;
		cout << "武将当前体力：  " << player_info.cur_blood << endl;
		cout << "武将所属势力：  " << roleInfo->power << endl;
		cout << "武将技能： " << endl;

		for (uint16_t i = 0; i < roleInfo->skill_num; i++) {
			cout << "[" << i << "]" << roleInfo->skill[i] << endl;
		}
	}
	else {
		cout << "无此武将信息" << endl;
	}
}

void PlayerData::viewRolesCard(uint32_t *roles, uint16_t role_num) {
	rolesInfoManagement role_man;

	for (uint16_t i = 0; i < role_num; i++) {
		ROLESINFO * roleInfo = role_man.findRoleById(roles[i]);
		if (roleInfo != NULL) {
			cout << "武将编号： " << "[" << i << "]" << endl;
			cout << "武将名：   " << roleInfo->name << endl;
			cout << "武将上限体力：  " << roleInfo->blood << endl;
			cout << "武将所属势力：  " << roleInfo->power << endl;
			cout << "武将技能： " << endl;

			for (uint16_t j = 0; j < roleInfo->skill_num; j++) {
				cout << "[" << j << "]" << roleInfo->skill[j] << endl;
			}
		}
		else {
			cout << "无此武将信息" << endl;
		}
	}
}

bool  PlayerData::chooseRoleCard(uint32_t *roles, uint16_t index) {
	rolesInfoManagement role_man;
	ROLESINFO * roleInfo = role_man.findRoleById(roles[index]);

	if (roleInfo != NULL) {
		player_info.max_blood = player_info.status == STATUS_MASTER ? roleInfo->blood + 1 : roleInfo->blood;
		player_info.cur_blood = player_info.max_blood;
		player_info.role_id = roleInfo->id;
		player_info.role_name = roleInfo->name;
		player_info.role_power = roleInfo->power;
		return true;
	}
	return false;
}

bool PlayerData::chooseRoleCard(uint32_t *roles, string name) {
	return false;
}

bool PlayerData::setRoleStatus(uint16_t status) {
	if (player_info.status == 0 && status >= STATUS_MASTER && status <= STATUS_REBEL) {
		player_info.status = status;
		return true;
	}
	return false;
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

bool PlayerData::isCardCanEquip(uint16_t index) {
	if (player_info.cur_cards[index].category == CARDS_EQUIPMENT_WEAPON 
		|| player_info.cur_cards[index].category == CARDS_EQUIPMENT_ARMOR 
		|| player_info.cur_cards[index].category == CARDS_EQUIPMENT_HORSE_MINUS 
		|| player_info.cur_cards[index].category == CARDS_EQUIPMENT_HORSE_PLUS) {
		for (uint16_t i = 0; i < player_info.equip_num; i++) {
			if (player_info.cur_cards[index].category == player_info.equip_cards[i].category) {
				return false;
			}
		}
		return true;
	}

	return false;
}

uint32_t PlayerData::playCards(uint16_t index) {
	if(player_info.cards_num == 0){
		cout << "无手牌可使用" << endl;
		return 0;
	}

	if (index >= player_info.cards_num) {
		cout << "无此序号的手牌" << endl;
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
		cout << "无手牌可使用" << endl;
		return 0;
	}

	int index = -1;

	for (uint16_t i = 0; i < player_info.cards_num; i++) {
		if (name == player_info.cur_cards[i].name) {
			index = i;
			break;
		}
	}

	if (index < 0) {
		cout << "无此手牌可使用" << endl;
		return 0;
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

uint32_t PlayerData::equipCards(uint16_t index) {
	if (!isCardCanEquip(index)) {
		cout << "此卡牌不能装备！" << endl;
		return player_info.cur_cards[index].id;
	}

	memcpy(&player_info.equip_cards[player_info.equip_num++], &player_info.cur_cards[index], sizeof(player_info.cur_cards[index]));
	playCards(index);

	return player_info.equip_cards[player_info.equip_num-1].id;
}

uint32_t PlayerData::equipCards(string name) {
	if (player_info.cards_num == 0) {
		cout << "无手牌可装备" << endl;
		return 0;
	}

	int index = -1;

	for (uint16_t i = 0; i < player_info.cards_num; i++) {
		if (name == player_info.cur_cards[i].name) {
			index = i;
			break;
		}
	}

	if (index < 0) {
		cout << "无此手牌可装备" << endl;
		return 0;
	}

	return equipCards((uint16_t)index);
}

uint32_t PlayerData::equipCards(uint32_t id){
	return id;
}

bool PlayerData::playerBloodAdd(uint16_t n) {
	if (player_info.cur_blood >= player_info.max_blood){
		return false;
	}
	player_info.cur_blood = player_info.cur_blood + n > player_info.max_blood ? player_info.max_blood : player_info.cur_blood + n;

	return true;
}

bool PlayerData::playerBloodReduce(uint16_t n){
	if (player_info.cur_blood <= 0) {
		return false;
	}

	player_info.cur_blood--;
	return true;
}

bool PlayerData::useRoleSkill(uint16_t index) {
	return true;
}

bool PlayerData::useRoleSkill(uint32_t id) {
	return true;
}