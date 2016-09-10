#pragma once
#include"common.h"

typedef struct roles_info{
	uint32_t id;
	uint16_t blood;
	string name;
	string power;
	uint16_t skill_num;
	string skill[SKILL_NUM];
}ROLESINFO;