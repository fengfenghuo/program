#include "common.h"
#include "cardsInfoManagement.h"
#include "rolesInfoManagement.h"

int main() {
	char s[] = "2,2,3,4,5,6,7,8,9,10,11,11";
	uint8_t array[20] = { 0 };
	int num = strToArray(s, array);

	cout << num << endl;
	for (int i = 0; i < num; i++) {
		cout << (int)array[i] << "  ";
	}
	/*CARDSINFOMANAGEMENT card;
	uint8_t count = card.count();
	CARDSINFO * card_info = card.at((uint32_t)count-1);
	
	cout << (int)card_info->category << endl;
	cout << card_info->name << endl;
	cout << card_info->desc << endl;

	rolesInfoManagement role;
	uint8_t role_count = role.count();
	ROLESINFO * role_info = role.at((uint32_t)role_count - 1);

	cout << role_info->id << endl;
	cout << role_info->name << endl;

	for (int i = 0; i < role_info->skill_num; i++) {
		cout << role_info->skill[i] << endl;
	}
	*/
	return 0;
}