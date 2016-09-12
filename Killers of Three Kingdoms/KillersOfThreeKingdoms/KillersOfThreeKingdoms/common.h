#pragma once

#include <iostream>
using namespace std;

#define CARDS_NUM 16
#define CARDS_EQUIP_NUM 4
#define CARDS_JUDGEMENT_NUM 4
#define SKILL_NUM 2

#define CARDS_TOTAL 104

#define CARDS_COLOR_SPADE 1
#define CARDS_COLOR_PLUM 2
#define CARDS_COLOR_HEART 3
#define CARDS_COLOR_DIAMOND 4

#define CARDS_CATEGORY_BASIC 1
#define CARDS_CATEGORY_STRATEGY 2
#define CARDS_CATEGORY_STRATEGY_DELAY 3
#define CARDS_CATEGORY_EQUIPMENT_WEAPON 4
#define CARDS_CATEGORY_EQUIPMENT_ARMOR 5
#define CARDS_CATEGORY_EQUIPMENT_HORSE_PLUS 6
#define CARDS_CATEGORY_EQUIPMENT_HORSE_MINUS 7

#define ROLES_CHOOSE_NUM 3

#define STATUS_NUM 4  //�����
#define STATUS_MASTER 1 //����
#define STATUS_LOYAL 2  //�ҳ�
#define STATUS_GUILTY 3  //�ڼ�
#define STATUS_REBEL 4  //����

uint16_t strToArray(const char *source, uint16_t *array);

std::string UTF8_To_string(const std::string & str);