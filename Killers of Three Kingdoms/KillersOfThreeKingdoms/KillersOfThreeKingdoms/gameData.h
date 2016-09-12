#pragma once
#include "common.h"
#include "cards.h"
#include "roles.h"

class GameData {
public:
	GameData();
	~GameData();

	bool generateStatus(uint16_t role_count, uint16_t *roles);
	bool generateRoles(uint16_t role_status, uint32_t *roles);

};