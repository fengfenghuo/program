#pragma once
#include "cards.h"
#include "roles.h"

class PlayerData {
public:
	PlayerData();
	~PlayerData();

	void viewCurCards(bool isShow = true, uint16_t start = 0);
	void viewEquipCards(bool isShow = true, uint16_t start = 0);
	void viewJudgementCards(bool isShow = true, uint16_t start = 0);
	void viewRoleCard();
	void viewRolesCard(uint32_t *roles, uint16_t role_num = ROLES_CHOOSE_NUM);
	void viewRolesCard(uint16_t *roles_identity, uint16_t role_num = ROLES_CHOOSE_NUM);

	bool setRoleInfo(ROLESINFO * roleInfo);                    //选择英雄
	bool setRoleAlive();                                       //选择英雄

	bool setRoleStatus(uint16_t status, uint16_t role_num, bool isRobot);       //设置角色身份
	bool setRoleCurState(uint16_t state);                         //设置角色当前状态
	bool drowCards(CLICARDS *cards, uint16_t card_count);         //得到手牌

	bool playerBloodAdd(uint16_t n = 1);                          //英雄加体力
	bool playerBloodReduce(uint16_t n = 1);                       //英雄减体力

	CLICARDS* playCards(uint16_t index);                          //出牌
	CLICARDS* playCards(string name);
	CLICARDS* playCards(uint32_t id);

	CLICARDS* discardCards(uint16_t index);                       //弃手牌
	CLICARDS* discardCards(string name);
	CLICARDS* discardCards(uint32_t id);

	bool judgementCard(CLICARDS *card);

	CLICARDS* discardEquipCards(uint16_t index);                  //弃装备牌
	CLICARDS* discardEquipCards(uint8_t category);                //弃装备牌
	CLICARDS* discardJudgementCards(uint16_t index);              //弃判定牌

	bool equipCards(CLICARDS *card);                               //装备牌

	CLICARDS* equipCardByCategory(uint8_t category);              //categor类型的装备
	PLAYERINFO * playerInfo();

	bool isRoleRobot();                                           //是不是机器人
	bool isRoleAlive();                                           //英雄是否存活
	bool isCardCanPlay(uint32_t id);
	bool isCardCanEquip(uint32_t id);
	bool isCardCanEquip(uint16_t index);
	bool isHorsePlus();                                           //有没有+1马
	bool isHorseMinus();                                          //有没有-1马
	bool isCard_Sha();                                            //是否有【杀】
	bool isCard_Shan();                                           //是否有【闪】
	bool isCard_Tao();                                            //是否有【桃】
	bool isCurCardEmpty();                                        //是否有手牌
	bool isJudgeCardEmpty();                                      //是否有判定牌
	bool isEquipCardEmpty();                                      //是否有装备牌
	
	uint16_t damageRange();                                       //可攻击范围
	uint16_t weaponRange();                                       //武器攻击范围
	uint16_t playerRoleNum();                                     //英雄身份号
	uint16_t playerRoleStatus();                                  //英雄身份
	string playerRoleName();                                      //英雄名字
	uint16_t cardCurNum();                                        //手牌数
	uint16_t cardEquipNum();                                      //装备牌数
	uint16_t cardJudgeNum();                                      //判定牌数
	CLICARDS* equipWeapon();                                      //装备武器
	uint16_t roleCurState();
	uint16_t roleCurBlood();

	uint32_t curCardId(uint16_t index);                           //第index手牌的ID
	int curCardIndex(string name);                                //名字为name牌的位置
	int curCardIndex(uint32_t id);                                //ID为id牌的位置
	CLICARDS* judgeCardByIndex(uint16_t index);                   //第index判定牌

	//未实现
	bool useRoleSkill(uint16_t index);
	bool useRoleSkill(uint32_t id);

	//////////////////////////////////////////////////////////////////////////////////
private:
	CLICARDS* putOneCardByIndex(uint16_t index);
	CLICARDS* putOneCardByName(string name);
	CLICARDS* putOneCardById(uint32_t id);

private:
	PLAYERINFO m_playerInfo;
};