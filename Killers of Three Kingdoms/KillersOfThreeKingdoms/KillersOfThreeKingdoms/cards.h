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
	uint8_t hurt;
	uint8_t recover;
	uint8_t range;
	int distance;
	uint8_t type;
	string desc;
}CARDSINFO;

typedef struct cli_cards {
	uint32_t id;
	uint8_t category;
	uint8_t color;
	uint8_t points;
	string name;
	uint8_t hurt;
	uint8_t recover;
	uint8_t range;
	int distance;
	uint8_t type;
	string desc;
}CLICARDS;