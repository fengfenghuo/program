#pragma once

#include <iostream>
using namespace std;

///////////////ERROR//////////////////
#define ERROR_SYSTEM_ERROR -1
#define ERROR_USE_WEAPEN 97
#define ERROR_TARGET_DEAD 98
#define ERROR_TARGET_ERROR 99
#define ERROR_NO_RESPONSE -2
#define ERROR_NO_ACTIVE -3

/////////////////////////////////

#define CARDS_NUM 16
#define CARDS_EQUIP_NUM 4
#define CARDS_JUDGEMENT_NUM 4
#define CARDS_MAX_NUM 99
#define SKILL_NUM 2
#define CARDS_DEALS 2
#define CARDS_STARTING 4

#define CARDS_TOTAL 108
#define ROLES_TOTAL 27

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
#define ROLES_MAX_NUM 8

#define STATUS_NUM 4      //最多身份数
#define STATUS_MIN_NUM 2  //最少身份数
#define STATUS_MASTER 1 //主公
#define STATUS_REBEL 2  //反贼
#define STATUS_LOYAL 3  //忠臣
#define STATUS_GUILTY 4  //内奸


#define GAME_STAGE_START 1 //准备
#define GAME_STAGE_JUDGE 2 //判定
#define GAME_STAGE_PLAY 3  //出牌
#define GAME_STAGE_DISCARDS 4  //弃牌
#define GAME_STAGE_END 0 //结束


#define CARD_SHA 101
#define CARD_SHAN 102
#define CARD_TAO 103
#define CARD_GUOHECHAIQIAO 201
#define CARD_SHUNSHOUQIANYANG 202
#define CARD_JUEDOU 203
#define CARD_JIEDAOSHAREN 204
#define CARD_WUZHONGSHENGYOU 205
#define CARD_WUXIEKEJI 206
#define CARD_WANGJIANQIFA 207
#define CARD_NANMANRUQIN 208
#define CARD_TAOYUANJIEYI 209
#define CARD_WUGUFENGDENG 210
#define CARD_SHANDIAN 301
#define CARD_LEBUSISHU 302
#define CARD_QILINGONG 401
#define CARD_ZHUGELIANNU 402
#define CARD_GUANSHIFU 403
#define CARD_FANGTIANHUAJI 404
#define CARD_CIXIONGSHUANGGUJIAN 405
#define CARD_HANBINGJIAN 406
#define CARD_QINGGANGJIAN 407
#define CARD_ZHANGBASHEMAO 408
#define CARD_QINGLONGYANJUEDAO 409
#define CARD_BAGUAZHEN 501
#define CARD_RENWANGDUN 502



uint16_t strToArray(const char *source, uint16_t *array);
bool arrIsInArray(uint16_t arr, uint16_t* array, uint16_t array_count);
bool arrIsInArray(uint16_t* arr, uint16_t arr_count, uint16_t* array, uint16_t array_count);
int strToInt(string source);
string viewCardColor(int point, uint16_t color);
string viewRoleStatus(uint16_t status);

bool isLaunchSkill();

std::string UTF8_To_string(const std::string & str);