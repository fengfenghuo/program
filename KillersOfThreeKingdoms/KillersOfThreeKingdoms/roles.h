#pragma once
#include"common.h"
#include "cards.h"

typedef struct roles_info{
	uint32_t id;
	uint16_t identity;
	uint16_t blood;
	string name;
	bool sex;
	string power;
	uint16_t skill_num;
	string skill[SKILL_NUM];
}ROLESINFO;

typedef struct player {
	uint16_t role_num;
	bool is_robot;
	bool is_alive;
	bool is_play_sha;
	uint16_t status;
	uint32_t role_id;
	uint16_t max_blood;
	uint16_t cur_blood;
	string role_name;
	bool sex;
	string role_power;
	uint16_t cur_state;
	uint16_t max_cards;
	uint16_t cards_num;
	CLICARDS cur_cards[CARDS_NUM];
	uint16_t equip_num;
	CLICARDS equip_cards[CARDS_EQUIP_NUM];
	uint16_t judgment_num;
	CLICARDS judgment_cards[CARDS_JUDGEMENT_NUM];
}PLAYERINFO;