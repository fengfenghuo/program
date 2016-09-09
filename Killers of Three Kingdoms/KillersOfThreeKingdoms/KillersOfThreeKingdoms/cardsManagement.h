#pragma once
#include "cards.h"
#include "json\json.h"

typedef class cardsManagement {
public:
	cardsManagement();
	uint32_t count();
	CARDSINFO * at(uint32_t index);
	~cardsManagement();
}CARDSMANAGEMENT;

