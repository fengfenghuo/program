#pragma once
#include "cards.h"
#include "roles.h"

class PlayerData {
public:
	PlayerData();
	~PlayerData();

	void viewCurCards(bool isShow);
	void viewEquipCards(bool isShow);
	void viewJudgementCards(bool isShow);
	void viewRoleCard();
	void viewRolesCard(uint32_t *roles, uint16_t role_num = ROLES_CHOOSE_NUM);

	bool chooseRoleCard(uint32_t *roles, uint16_t index);
	bool chooseRoleCard(uint32_t *roles, string name);

	bool setRoleStatus(uint16_t status);

	string viewCardColor(CLICARDS card);

	uint32_t playCards(uint16_t index);
	uint32_t playCards(string name);
	uint32_t playCards(uint32_t id);

	uint32_t discardCards(uint16_t index);
	uint32_t discardCards(string name);
	uint32_t discardCards(uint32_t id);

	uint32_t equipCards(uint16_t index);
	uint32_t equipCards(string name);
	uint32_t equipCards(uint32_t id);

	bool isCardCanPlay(uint32_t id);
	bool isCardCanEquip(uint32_t id);
	bool isCardCanEquip(uint16_t index);

	bool useRoleSkill(uint16_t index);
	bool useRoleSkill(uint32_t id);

	bool playerBloodAdd(uint16_t n = 1);
	bool playerBloodReduce(uint16_t n = 1);

private:
	PLAYERINFO player_info;
};