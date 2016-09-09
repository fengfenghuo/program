#include "common.h"
#include "cardsManagement.h"

int main() {
	CARDSMANAGEMENT card;
	uint8_t count = card.count();
	CARDSINFO * card_info = card.at((uint32_t)count-1);
	
	cout << (int)card_info->category << endl;
	cout << card_info->name << endl;
	cout << card_info->desc << endl;
	return 0;
}