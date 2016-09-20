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

	bool chooseRoleCard(uint32_t *roles, uint16_t index);         //ѡ��Ӣ��
	bool chooseRoleCard(uint32_t *roles, string name);
	bool setRoleStatus(uint16_t status);                          //���ý�ɫ���
	bool drowCards(CLICARDS *cards, uint16_t card_count);         //�õ�����

	bool playerBloodAdd(uint16_t n = 1);                          //Ӣ�ۼ�����
	bool playerBloodReduce(uint16_t n = 1);                       //Ӣ�ۼ�����
	bool isplayerAlive();                                         //Ӣ���Ƿ���

	CLICARDS* playCards(uint16_t index);                          //����
	CLICARDS* playCards(string name);
	CLICARDS* playCards(uint32_t id);

	CLICARDS* discardCards(uint16_t index);                       //������
	CLICARDS* discardCards(string name);
	CLICARDS* discardCards(uint32_t id);

	CLICARDS* discardEquipCards(uint16_t index);                  //��װ����
	CLICARDS* discardJudgementCards(uint16_t index);              //���ж���

	CLICARDS* equipCards(uint16_t index);                         //װ����
	CLICARDS* equipCards(string name);
	CLICARDS* equipCards(uint32_t id);

	bool isRoleRobot();                                           //�ǲ��ǻ�����
	bool isCardCanPlay(uint32_t id);
	bool isCardCanEquip(uint32_t id);
	bool isCardCanEquip(uint16_t index);
	bool isHorsePlus();                                           //��û��+1��
	bool isHorseMinus();                                          //��û��-1��
	bool isCard_Sha();                                            //�Ƿ��С�ɱ��
	bool isCard_Shan();                                           //�Ƿ��С�����
	bool isCurCardEmpty();                                        //�Ƿ�������
	bool isJudgeCardEmpty();                                      //�Ƿ����ж���
	bool isEquipCardEmpty();                                      //�Ƿ���װ����
	
	uint16_t damageRange();                                       //�ɹ�����Χ
	uint16_t weaponRange();                                       //����������Χ
	uint16_t playerRoleNum();                                     //Ӣ����ݺ�
	string playerRoleName();                                      //Ӣ������
	uint16_t cardCurNum();                                        //������
	uint16_t cardEquipNum();                                      //װ������
	uint16_t cardJudgeNum();                                      //�ж�����
	CLICARDS* equipWeapon();                                      //װ������

	uint32_t curCardId(uint16_t index);                           //��index���Ƶ�ID
	int curCardIndex(string name);                                //����Ϊname�Ƶ�λ��
	int curCardIndex(uint32_t id);                                //IDΪid�Ƶ�λ��

	//δʵ��
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