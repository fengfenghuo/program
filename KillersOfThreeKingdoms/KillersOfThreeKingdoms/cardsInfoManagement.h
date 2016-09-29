#pragma once
#include "cards.h"
#include "json\json.h"

typedef class cardsInfoManagement {
public:
	cardsInfoManagement();
	uint32_t count();
	CARDSINFO * at(uint32_t index);
	CARDSINFO * findCardById(uint32_t id);
	~cardsInfoManagement();
}CARDSINFOMANAGEMENT;

