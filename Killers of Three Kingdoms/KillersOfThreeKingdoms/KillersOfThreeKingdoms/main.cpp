#include "common.h"
#include "gameData.h"
#include <iomanip>
#include <cstdlib>
#include <string>

void menu() {
	cout << setiosflags(ios::right) << setw(32) << "����ɱ����С��Ϸ" << endl;
	cout << endl;
	cout << setiosflags(ios::right) << setw(40) << "**��1��.2�˾�  **  ��2��.4�˾�**" << endl;
	cout << setiosflags(ios::right) << setw(40) << "**��3��.5�˾�  **  ��4��.6�˾�**" << endl;
	cout << setiosflags(ios::right) << setw(40) << "**��5��.7�˾�  **  ��6��.8�˾�**" << endl;
	cout << setiosflags(ios::right) << setw(40) << "****      ��0��.�˳�        ****" << endl;
	cout << endl;
	cout << "������������Ŀ������������롱0���˳���Ϸ��:  " ;
}

uint16_t setGameRoleNum() {
	uint16_t in_num = 0;
	while (true) {
		cin >> in_num;
		if (in_num >= 2 && in_num <= 8 && in_num != 3) {
			return in_num;
		}
		else if (in_num == 0) {
			return 0;
		}
		cout << "����������������������룺";
	}
	return 0;
}

int main() {
	while (true) {
		uint16_t role_num = 0;
		uint16_t player_num = 0;
		menu();
		role_num = setGameRoleNum();

		if (role_num == 0) {
			cout << "������Ϸ~ " << endl;
			return 0;
		}

		GameData gameData(role_num);
		gameData.shuffleCards();

		player_num = gameData.generateStatus(role_num);
		if (player_num < 0) {
			cout << "�����ˣ�������ݳ�����~" << endl;
			return ERROR_SYSTEM_ERROR;
		}

		PLAYERINFO * playerInfo = gameData.findPlayerInfoByNum(player_num);
		if (playerInfo == NULL) {
			cout << "����ʧ��~�����¿�ʼ��~" << endl;
			return ERROR_SYSTEM_ERROR;
		}
		cout << "�������ǣ�" << viewRoleStatus(playerInfo->status) << "λ�ڡ�" << playerInfo->role_num << "����λ" << endl;
		gameData.generateRoles();

		gameData.viewPlayersRole();
		gameData.startingCards();
		gameData.viewPlayerCards(player_num);

		cout << "��Ϸ��ʼ~" << endl;
		
		for (uint16_t i = 0; i < gameData.curRoleCount(); i++) {
			gameData.playerStartToPlay(i);
			if (!gameData.judgeCards(i)) {
				cout << "��" << i << "����λ�ж��ƴ���" << endl;
				return ERROR_SYSTEM_ERROR;
			}

			if (!gameData.dealCards(CARDS_DEALS, i)) {
				cout << "��" << i << "����λץ�ƴ���" << endl;
				return ERROR_SYSTEM_ERROR;
			}

			while (CLICARDS * cards = gameData.playCards(i)) {
				int signal = gameData.applyCardPlay(cards, i);
				if (signal != 0) {
					cout << "��" << i << "����λ���ƴ���" << endl;
					return ERROR_SYSTEM_ERROR;
				}
			}

			gameData.discardCards(i);
			gameData.playerEndToPlay(i);
		}
	}
	
	/*uint16_t num = 0;
	cout << "��ѡ����Ҫ��������" << endl;
	cin >> num;

	uint16_t *array = new uint16_t[num];
	
	GameData gm;
	gm.generateStatus(num, array);

	for (uint16_t i = 0; i < num; i++) {
		cout << array[i] << "  ";
	}
	gm.shuffleCards();
	gm.viewPilesCards();
*/
	return 0;
}