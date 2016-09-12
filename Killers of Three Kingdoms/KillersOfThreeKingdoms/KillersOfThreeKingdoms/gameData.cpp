#include "gameData.h"
#include "cardsInfoManagement.h"
#include "rolesInfoManagement.h"
#include "statusInfoManagement.h"
#include <cstdlib>

GameData::GameData() {
	m_roleCount = 0;
}

GameData::~GameData() {

}

bool GameData::setRoleCount(uint16_t role_count) {
	m_roleCount = role_count;
	return true;
}

bool GameData::generateStatus(uint16_t role_count, uint16_t *roles_status) {
	memset(roles_status, 0, sizeof(uint16_t)*role_count);
	STATUSINFOMANAGEMENT status_man;

	STATUSINFO* status_info = status_man.findCardByNum(role_count);
	if (status_info == NULL) {
		return false;
	}

	uint16_t master = status_info->master;
	uint16_t loyal = status_info->loyal;
	uint16_t guilty = status_info->guilty;
	uint16_t rebel = status_info->rebel;

	for (uint16_t i = 0; i < role_count; i++) {
		int num = rand() % role_count;
		
		while (roles_status[num] != 0 && num < role_count
			&& (master != 0 || loyal != 0 || guilty != 0 || rebel != 0)) {
			if (num + 1 == role_count) {
				num = 0;
			}
			else {
				num++;
			}
		}

		if (master != 0) {
			roles_status[num] = STATUS_MASTER;
			--master;
		}
		else if (loyal != 0) {
			roles_status[num] = STATUS_LOYAL;
			--loyal;
		}
		else if (guilty != 0) {
			roles_status[num] = STATUS_GUILTY;
			--guilty;
		}
		else if (rebel != 0) {
			roles_status[num] = STATUS_REBEL;
			--rebel;
		}
	}
	return true;
}

bool GameData::generateRoles(uint16_t role_status, uint16_t *roles_identity) {
	ROLESINFOMANAGEMENT role_man;

	uint16_t role_count = role_man.count();
	for (uint16_t i = 0; i < m_roleCount * ROLES_CHOOSE_NUM; i++) {
		roles_identity[i] = rand() % role_count;
	}
	return true;
}