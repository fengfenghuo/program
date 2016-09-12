#pragma once
#include "common.h"

typedef struct cards_info {
	uint32_t id;
	uint8_t category;
	uint8_t spade_num;
	uint8_t spade[CARDS_NUM];
	uint8_t plum_num;
	uint8_t plum[CARDS_NUM];
	uint8_t heart_num;
	uint8_t heart[CARDS_NUM];
	uint8_t diamond_num;
	uint8_t diamond[CARDS_NUM];
	string name;
	uint16_t hurt;
	uint16_t recover;
	uint16_t range;
	int distance;
	uint8_t type;
	string desc;
}CARDSINFO;

typedef struct cli_cards {
	uint32_t id;
	uint8_t category;
	uint16_t color;
	string points;
	string name;
	uint16_t hurt;
	uint16_t recover;
	uint16_t range;
	int distance;
	uint8_t type;
}CLICARDS;

