#include "common.h"
#include "gameData.h"
#include <iomanip>

void menu() {
	cout << setiosflags(ios::right) << setw(32) << "����ɱ����С��Ϸ" << endl;
	cout << endl;
	cout << setiosflags(ios::right) << setw(40) << "**��1��.2�˾�  **  ��2��.4�˾�**" << endl;
	cout << setiosflags(ios::right) << setw(40) << "**��3��.5�˾�  **  ��4��.6�˾�**" << endl;
	cout << setiosflags(ios::right) << setw(40) << "**��5��.7�˾�  **  ��6��.8�˾�**" << endl;
	cout << endl;
	cout << "������������Ŀ�������:" << endl;
}

void setGameRoleNum() {

}

int main() {
	menu();
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