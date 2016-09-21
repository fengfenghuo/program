#include "common.h"
#include "gameData.h"
#include <iomanip>

void menu() {
	cout << setiosflags(ios::right) << setw(32) << "三国杀——小游戏" << endl;
	cout << endl;
	cout << setiosflags(ios::right) << setw(40) << "**【1】.2人局  **  【2】.4人局**" << endl;
	cout << setiosflags(ios::right) << setw(40) << "**【3】.5人局  **  【4】.6人局**" << endl;
	cout << setiosflags(ios::right) << setw(40) << "**【5】.7人局  **  【6】.8人局**" << endl;
	cout << endl;
	cout << "请输入您所需的开局人数:" << endl;
}

void setGameRoleNum() {

}

int main() {
	menu();
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