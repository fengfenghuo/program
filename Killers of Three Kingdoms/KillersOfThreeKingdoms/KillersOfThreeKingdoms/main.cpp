#include "common.h"
#include "cardsManagement.h"

int main() {
	CARDSMANAGEMENT card;
	uint8_t count = card.count();
	CARDSINFO * card_info = card.at(0);
	
	cout << card_info->category << endl;
	return 0;
}