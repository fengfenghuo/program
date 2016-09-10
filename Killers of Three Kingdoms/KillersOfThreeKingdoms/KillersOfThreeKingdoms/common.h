#pragma once

#include <iostream>
using namespace std;

#define CARDS_NUM 16
#define CARDS_EQUIP_NUM 4
#define CARDS_JUDGEMENT_NUM 4
#define SKILL_NUM 2

#define CARDS_BASIC 1
#define CARDS_STRATEGY 2
#define CARDS_STRATEGY_DELAY 3
#define CARDS_EQUIPMENT_WEAPON 4
#define CARDS_EQUIPMENT_ARMOR 5
#define CARDS_EQUIPMENT_HORSE_PLUS 6
#define CARDS_EQUIPMENT_HORSE_MINUS 7


uint8_t strToArray(const char *source, uint8_t *array);

std::string UTF8_To_string(const std::string & str);