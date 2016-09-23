#include "common.h"
#include "gameData.h"
#include <iomanip>
#include <cstdlib>
#include <string>

void menu() {
	cout << setiosflags(ios::right) << setw(32) << "三国杀——小游戏" << endl;
	cout << endl;
	cout << setiosflags(ios::right) << setw(40) << "**【1】.2人局  **  【2】.4人局**" << endl;
	cout << setiosflags(ios::right) << setw(40) << "**【3】.5人局  **  【4】.6人局**" << endl;
	cout << setiosflags(ios::right) << setw(40) << "**【5】.7人局  **  【6】.8人局**" << endl;
	cout << setiosflags(ios::right) << setw(40) << "****      【0】.退出        ****" << endl;
	cout << endl;
	cout << "请输入您所需的开局人数（输入”0“退出游戏）:  " ;
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
		cout << "输入的人数有误，请重新输入：";
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
			cout << "结束游戏~ " << endl;
			return 0;
		}

		GameData gameData(role_num);
		gameData.shuffleCards();

		player_num = gameData.generateStatus(role_num);
		if (player_num < 0) {
			cout << "出错了，生成身份出错啦~" << endl;
			return ERROR_SYSTEM_ERROR;
		}

		PLAYERINFO * playerInfo = gameData.findPlayerInfoByNum(player_num);
		if (playerInfo == NULL) {
			cout << "你消失啦~，重新开始吧~" << endl;
			return ERROR_SYSTEM_ERROR;
		}
		cout << "你的身份是：" << viewRoleStatus(playerInfo->status) << "位于【" << playerInfo->role_num << "】号位" << endl;
		gameData.generateRoles();

		gameData.viewPlayersRole();
		gameData.startingCards();
		gameData.viewPlayerCards(player_num);

		cout << "游戏开始~" << endl;
		
		for (uint16_t i = 0; i < gameData.curRoleCount(); i++) {
			gameData.playerStartToPlay(i);
			if (!gameData.judgeCards(i)) {
				cout << "【" << i << "】号位判定牌错误" << endl;
				return ERROR_SYSTEM_ERROR;
			}

			if (!gameData.dealCards(CARDS_DEALS, i)) {
				cout << "【" << i << "】号位抓牌错误" << endl;
				return ERROR_SYSTEM_ERROR;
			}

			while (CLICARDS * cards = gameData.playCards(i)) {
				int signal = gameData.applyCardPlay(cards, i);
				if (signal != 0) {
					cout << "【" << i << "】号位出牌错误" << endl;
					return ERROR_SYSTEM_ERROR;
				}
			}

			gameData.discardCards(i);
			gameData.playerEndToPlay(i);
		}
	}
	
	/*uint16_t num = 0;
	cout << "请选择需要的人数：" << endl;
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