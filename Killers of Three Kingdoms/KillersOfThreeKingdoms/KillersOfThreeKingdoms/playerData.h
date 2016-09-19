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
	void viewRolesCard(uint16_t *roles_identity, uint16_t role_num = ROLES_CHOOSE_NUM);

	bool chooseRoleCard(uint32_t *roles, uint16_t index);
	bool chooseRoleCard(uint32_t *roles, string name);

	bool setRoleStatus(uint16_t status);
	bool isRoleRobot();

	string viewCardColor(CLICARDS card);

	bool drowCards(CLICARDS *cards, uint16_t card_count);

	CLICARDS* putOneCardByIndex(uint16_t index);
	CLICARDS* putOneCardByName(string name);
	CLICARDS* putOneCardById(uint32_t id);

	CLICARDS* playCards(uint16_t index);
	CLICARDS* playCards(string name);
	CLICARDS* playCards(uint32_t id);

	CLICARDS* discardCards(uint16_t index);
	CLICARDS* discardCards(string name);
	CLICARDS* discardCards(uint32_t id);

	CLICARDS* equipCards(uint16_t index);
	CLICARDS* equipCards(string name);
	CLICARDS* equipCards(uint32_t id);

	bool isCardCanPlay(uint32_t id);
	bool isCardCanEquip(uint32_t id);
	bool isCardCanEquip(uint16_t index);

	bool useRoleSkill(uint16_t index);
	bool useRoleSkill(uint32_t id);

	bool playerBloodAdd(uint16_t n = 1);
	bool playerBloodReduce(uint16_t n = 1);

	bool isHorsePlus();
	bool isHorseMinus();

	uint16_t weaponRange();
	uint16_t playerRoleNum();
	string playerRoleName();

	uint16_t damageRange();

	bool isCard_Sha();
	bool isCard_Shan();

	uint32_t curCardId(uint16_t index);
	int curCardIndex(string name);
	int curCardIndex(uint32_t id);

private:
	PLAYERINFO m_playerInfo;
};