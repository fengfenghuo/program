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

	bool setRoleInfo(ROLESINFO * roleInfo);                    //ѡ��Ӣ��
	bool setRoleAlive();                                       //ѡ��Ӣ��

	bool setRoleStatus(uint16_t status, uint16_t role_num, bool isRobot);       //���ý�ɫ���
	bool setRoleCurState(uint16_t state);                         //���ý�ɫ��ǰ״̬
	bool drowCards(CLICARDS *cards, uint16_t card_count);         //�õ�����

	bool playerBloodAdd(uint16_t n = 1);                          //Ӣ�ۼ�����
	bool playerBloodReduce(uint16_t n = 1);                       //Ӣ�ۼ�����

	CLICARDS* playCards(uint16_t index);                          //����
	CLICARDS* playCards(string name);
	CLICARDS* playCards(uint32_t id);

	CLICARDS* discardCards(uint16_t index);                       //������
	CLICARDS* discardCards(string name);
	CLICARDS* discardCards(uint32_t id);

	bool judgementCard(CLICARDS *card);

	CLICARDS* discardEquipCards(uint16_t index);                  //��װ����
	CLICARDS* discardEquipCards(uint8_t category);                //��װ����
	CLICARDS* discardJudgementCards(uint16_t index);              //���ж���

	bool equipCards(CLICARDS *card);                               //װ����

	CLICARDS* equipCardByCategory(uint8_t category);              //categor���͵�װ��
	PLAYERINFO * playerInfo();

	bool isRoleRobot();                                           //�ǲ��ǻ�����
	bool isRoleAlive();                                           //Ӣ���Ƿ���
	bool isCardCanPlay(uint32_t id);
	bool isCardCanEquip(uint32_t id);
	bool isCardCanEquip(uint16_t index);
	bool isHorsePlus();                                           //��û��+1��
	bool isHorseMinus();                                          //��û��-1��
	bool isCard_Sha();                                            //�Ƿ��С�ɱ��
	bool isCard_Shan();                                           //�Ƿ��С�����
	bool isCard_Tao();                                            //�Ƿ��С��ҡ�
	bool isCurCardEmpty();                                        //�Ƿ�������
	bool isJudgeCardEmpty();                                      //�Ƿ����ж���
	bool isEquipCardEmpty();                                      //�Ƿ���װ����
	
	uint16_t damageRange();                                       //�ɹ�����Χ
	uint16_t weaponRange();                                       //����������Χ
	uint16_t playerRoleNum();                                     //Ӣ����ݺ�
	uint16_t playerRoleStatus();                                  //Ӣ�����
	string playerRoleName();                                      //Ӣ������
	uint16_t cardCurNum();                                        //������
	uint16_t cardEquipNum();                                      //װ������
	uint16_t cardJudgeNum();                                      //�ж�����
	CLICARDS* equipWeapon();                                      //װ������
	uint16_t roleCurState();
	uint16_t roleCurBlood();

	uint32_t curCardId(uint16_t index);                           //��index���Ƶ�ID
	int curCardIndex(string name);                                //����Ϊname�Ƶ�λ��
	int curCardIndex(uint32_t id);                                //IDΪid�Ƶ�λ��
	CLICARDS* judgeCardByIndex(uint16_t index);                   //��index�ж���

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