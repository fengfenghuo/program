#include "common.h"
#include "cardsInfoManagement.h"
#include "rolesInfoManagement.h"

int main() {
	CARDSINFOMANAGEMENT card;
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
	
	return 0;
}